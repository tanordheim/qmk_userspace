// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "halcyon.h"
#include "transactions.h"
#include "synchronization_util.h"

// Virtual module columns are not part of the 50 physical typing switches.
static const matrix_row_t typing_mask[MATRIX_ROWS] = {
    0x007E, 0x007E, 0x007F, 0x003F,
    0x007E, 0x007E, 0x007F, 0x003F,
};
static bool keys_held;
static uint32_t last_release;

#ifdef HLC_TFT_DISPLAY
#include "hlc_tft_display/hlc_tft_display.h"
#include "layers.h"
#include "thintel15.qff.h"
#include "wpm.h"
#include "../../../../elora/keymaps/tanordheim/bongo_cat_frames.h"

static matrix_row_t previous_matrix[MATRIX_ROWS];
static bool tap_pending;
static bool panel_power_valid;
static bool panel_on;
static bool rendered_valid;
#endif

static void scan_typing_keys(void) {
    bool held = false;
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        const matrix_row_t current = matrix_get_row(row) & typing_mask[row];
#ifdef HLC_TFT_DISPLAY
        if (current & ~previous_matrix[row]) {
            tap_pending = true;
        }
        previous_matrix[row] = current;
#endif
        held |= current != 0;
    }
    if (keys_held && !held) {
        last_release = timer_read32();
    }
    keys_held = held;
}

void matrix_scan_user(void) {
    scan_typing_keys();
}

void matrix_slave_scan_user(void) {
    scan_typing_keys();
}

static bool display_awake(void) {
    return keys_held || timer_elapsed32(last_release) < 60000 || last_input_activity_elapsed() < 60000;
}

bool module_housekeeping_task_user(void) {
    const bool awake = display_awake();
    if (!awake) {
        if (!is_keyboard_master()) {
            // Expire the cached level when a suspended master stops sending updates.
            split_shared_memory_lock();
            split_shmem->backlight_level = 0;
            split_shared_memory_unlock();
        }
        backlight_disable_noeeprom();
    } else if (is_keyboard_master()) {
        if (get_backlight_level() == 0) {
            backlight_level_noeeprom(BACKLIGHT_LEVELS);
        } else {
            backlight_enable_noeeprom();
        }
    }
#ifdef HLC_TFT_DISPLAY
    if (!panel_power_valid || panel_on != awake) {
        if (!qp_power(lcd, awake)) {
            panel_power_valid = false;
            return false;
        }
        panel_on = awake;
        panel_power_valid = true;
        if (awake) {
            rendered_valid = false;
        }
    }
#endif
    return true;
}

#ifdef HLC_TFT_DISPLAY
void suspend_power_down_user(void) {
    panel_power_valid = false;
}

void suspend_wakeup_init_user(void) {
    panel_power_valid = false;
}

enum pose {
    READY,
    IDLE,
    SLEEPING,
    LEFT_TAP,
    RIGHT_TAP,
};

typedef struct {
    uint8_t frame;
    enum pose pose;
    uint8_t layer;
    uint8_t wpm;
    uint8_t mods;
} display_state_t;

static painter_font_handle_t status_font;
static display_state_t rendered;

static display_state_t current_display_state(void) {
    static uint8_t tap_frame = 6;
    static bool tap_visible;
    static uint32_t tap_started;
    if (tap_pending) {
        tap_pending = false;
        tap_frame = tap_frame == 6 ? 7 : 6;
        tap_started = timer_read32();
        tap_visible = true;
    }

    display_state_t state = {
        .layer = get_highest_layer(layer_state | default_layer_state),
        .wpm = get_current_wpm(),
        .mods = get_mods() | get_weak_mods() | get_oneshot_mods() | get_oneshot_locked_mods(),
    };
    const uint32_t age = timer_elapsed32(last_release);
    if (keys_held || (tap_visible && timer_elapsed32(tap_started) < 100)) {
        state.frame = tap_frame;
        state.pose = tap_frame == 7 ? LEFT_TAP : RIGHT_TAP;
    } else {
        tap_visible = false;
        if (age < 750) {
            state.frame = 5;
            state.pose = READY;
        } else if (age < 15000) {
            state.frame = 4 - ((age - 750) / 150) % 5;
            state.pose = IDLE;
        } else {
            state.frame = 4;
            state.pose = SLEEPING;
        }
    }
    return state;
}

static const char *layer_name(uint8_t layer) {
    switch (layer) {
        case _QWERTY:   return "QWERTY";
        case _NAV:      return "NAV";
        case _SYM:      return "SYM";
        case _NUM:      return "NUM";
        case _FUNCTION: return "FUNCTION";
        case _ADJUST:   return "ADJUST";
        case _INTL:     return "INTL";
        default:        return "UNKNOWN";
    }
}

static const char *pose_name(enum pose pose) {
    switch (pose) {
        case READY:     return "READY";
        case IDLE:      return "IDLE";
        case SLEEPING:  return "SLEEPING";
        case LEFT_TAP:  return "LEFT TAP";
        case RIGHT_TAP: return "RIGHT TAP";
    }
    return "UNKNOWN";
}

static bool flush_surface(bool full_redraw) {
    return qp_surface_draw(lcd_surface, lcd, 0, 0, full_redraw) && qp_flush(lcd);
}

static bool draw_centered_text(const char *text, uint16_t y) {
    const int16_t width = qp_textwidth(status_font, text);
    if (width <= 0 || width > LCD_WIDTH - 16) {
        return false;
    }
    return qp_rect(lcd_surface, 8, y, LCD_WIDTH - 9, y + status_font->line_height - 1, HSV_BLACK, true) &&
           qp_drawtext_recolor(lcd_surface, (LCD_WIDTH - width) / 2, y, status_font, text, HSV_WHITE, HSV_BLACK) > 0;
}

static bool draw_modifiers(uint8_t mods) {
    const uint8_t masks[] = {MOD_MASK_SHIFT, MOD_MASK_CTRL, MOD_MASK_ALT, MOD_MASK_GUI};
    const char labels[] = "SCAG";
    for (uint8_t i = 0; i < ARRAY_SIZE(masks); i++) {
        const bool active = (mods & masks[i]) != 0;
        const uint16_t left = 8 + i * 32;
        const char text[] = {labels[i], '\0'};
        const int16_t width = qp_textwidth(status_font, text);
        if (width <= 0 || width > 23) {
            return false;
        }
        if (!qp_rect(lcd_surface, left, 220, left + 22, 237, 0, 0, active ? 255 : 0, true) ||
            qp_drawtext_recolor(lcd_surface, left + (23 - width) / 2, 220 + (18 - status_font->line_height) / 2, status_font, text,
                                0, 0, active ? 0 : 160, 0, 0, active ? 255 : 0) <= 0) {
            return false;
        }
    }
    return true;
}

static bool draw_frame(uint8_t frame) {
    uint8_t tile_index = 0;
    for (uint8_t row = 0; row < ARRAY_SIZE(bongo_line_x); row++) {
        uint8_t columns[48];
        const uint8_t width = bongo_line_len[row] * 6;
        for (uint8_t tile = 0; tile < bongo_line_len[row]; tile++) {
            const uint8_t glyph = pgm_read_byte(&bongo_line_data[frame][tile_index++]);
            for (uint8_t column = 0; column < 6; column++) {
                columns[tile * 6 + column] = pgm_read_byte(&bongofont[glyph * 6 + column]);
            }
        }
        for (uint8_t bit = 0; bit < 8; bit++) {
            uint8_t column = 0;
            while (column < width) {
                const bool ink = (columns[column] & (1 << bit)) != 0;
                uint8_t end = column + 1;
                while (end < width && ((columns[end] & (1 << bit)) != 0) == ink) {
                    end++;
                }
                const uint16_t x = 19 + 2 * (bongo_line_x[row] - 48 + column);
                const uint16_t y = 70 + 2 * (bongo_line_y[row] + bit);
                if (!qp_rect(lcd_surface, x, y, x + 2 * (end - column) - 1, y + 1, 0, 0, ink ? 255 : 0, true)) {
                    return false;
                }
                column = end;
            }
        }
    }
    return true;
}

static bool draw_background(void) {
    if (!qp_rect(lcd_surface, 0, 0, LCD_WIDTH - 1, LCD_HEIGHT - 1, HSV_BLACK, true) ||
        !qp_rect(lcd_surface, 8, 190, LCD_WIDTH - 9, 190, 0, 0, 100, true)) {
        return false;
    }
    // The desk ends stay outside the animated tile spans, as on Elora.
    for (uint8_t x = 0; x < 17; x++) {
        const uint16_t y = 70 + 2 * (31 - (x + 23) / 5);
        if (!qp_rect(lcd_surface, 3 + 2 * x, y, 4 + 2 * x, y + 1, HSV_WHITE, true)) {
            return false;
        }
    }
    for (uint8_t x = 51; x < 64; x++) {
        const uint16_t y = 70 + 2 * (15 - (x - 51) / 4);
        if (!qp_rect(lcd_surface, 3 + 2 * x, y, 4 + 2 * x, y + 1, HSV_WHITE, true)) {
            return false;
        }
    }
    return true;
}

static bool render_display(display_state_t state, bool redraw) {
    if (redraw && (!draw_background() || !flush_surface(true))) {
        return false;
    }
    // Separate transfers keep the dirty rectangle from spanning the whole screen.
    if ((redraw || state.frame != rendered.frame) && (!draw_frame(state.frame) || !flush_surface(false))) {
        return false;
    }
    if ((redraw || state.pose != rendered.pose) && (!draw_centered_text(pose_name(state.pose), 10) || !flush_surface(false))) {
        return false;
    }
    if (redraw || state.wpm != rendered.wpm) {
        char speed[] = "000 WPM";
        memcpy(speed, get_u8_str(state.wpm, '0'), 3);
        if (!draw_centered_text(speed, 168) || !flush_surface(false)) {
            return false;
        }
    }
    if ((redraw || state.layer != rendered.layer) && (!draw_centered_text(layer_name(state.layer), 199) || !flush_surface(false))) {
        return false;
    }
    if ((redraw || state.mods != rendered.mods) && (!draw_modifiers(state.mods) || !flush_surface(false))) {
        return false;
    }
    return true;
}

bool display_module_housekeeping_task_user(bool second_display) {
    (void)second_display;
    static uint32_t last_draw;
    if (!display_awake() || !panel_power_valid || !panel_on || timer_elapsed32(last_draw) < 100) {
        return false;
    }
    last_draw = timer_read32();
    if (!status_font) {
        status_font = qp_load_font_mem(font_thintel15);
        if (!status_font) {
            return false;
        }
    }
    const display_state_t state = current_display_state();
    const bool success = render_display(state, !rendered_valid);
    rendered_valid = success;
    if (success) {
        rendered = state;
    }
    return false;
}
#endif

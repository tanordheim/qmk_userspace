// Copyright 2024 splitkb.com (support@splitkb.com)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "keymap_norwegian.h"

// Host layout: Norwegian (no dead keys).

enum layers {
    _QWERTY = 0,
    _NAV,
    _SYM,
    _INTL,
    _FUNCTION,
    _ADJUST,
};

enum custom_keycodes {
    CK_CARET = SAFE_RANGE,
    CK_TILD,
};

#define SYM       MO(_SYM)
#define ESC_NAV   LT(_NAV, KC_ESC)
#define INTL      MO(_INTL)
#define FKEYS     MO(_FUNCTION)
#define ADJUST    MO(_ADJUST)
#define DICTATE   KC_F13

const key_override_t semicolon_shift_override    = ko_make_basic(MOD_MASK_SHIFT, NO_SCLN, NO_COLN);
const key_override_t comma_shift_override        = ko_make_basic(MOD_MASK_SHIFT, NO_COMM, NO_LABK);
const key_override_t dot_shift_override          = ko_make_basic(MOD_MASK_SHIFT, NO_DOT, NO_RABK);
const key_override_t questionmark_shift_override = ko_make_basic(MOD_MASK_SHIFT, NO_QUES, NO_BSLS);
const key_override_t plus_shift_override         = ko_make_basic(MOD_MASK_SHIFT, NO_PLUS, NO_GRV);
const key_override_t *key_overrides[] = {
    &semicolon_shift_override,
    &comma_shift_override,
    &dot_shift_override,
    &questionmark_shift_override,
    &plus_shift_override,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    uint16_t symbol;
    switch (keycode) {
        case CK_CARET: symbol = NO_CIRC; break;
        case CK_TILD:  symbol = NO_TILD; break;
        default: return true;
    }

    if (record->event.pressed) {
        const uint8_t mods = get_mods();
        const uint8_t weak_mods = get_weak_mods();
        del_mods(MOD_MASK_SHIFT);
        del_weak_mods(MOD_MASK_SHIFT);
        tap_code16(symbol);
        set_mods(mods);
        set_weak_mods(weak_mods);
        send_keyboard_report();
    }
    return false;
}

#ifdef OLED_ENABLE
#include "bongo_cat_frames.h"
#include "wpm.h"

// Elora shares shift-register bits with its encoders; only LAYOUT_myr switches count as typing.
static const matrix_row_t bongo_key_mask[MATRIX_ROWS] = {
    0x3F, 0xF0, 0xFF, 0xFF, 0xFF, 0x1F,
    0xFC, 0x0F, 0xFF, 0xFF, 0xFF, 0x1F,
};
static matrix_row_t bongo_previous_matrix[MATRIX_ROWS];
static bool        bongo_keys_held;
static bool        bongo_tap_pending;
static bool        bongo_tap_visible;
static uint8_t     bongo_tap_frame = 6;
static uint32_t    bongo_tap_started;
static uint32_t    bongo_last_release;

static void scan_bongo_keys(void) {
    bool held = false;
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        const matrix_row_t current = matrix_get_row(row) & bongo_key_mask[row];
        if (current & ~bongo_previous_matrix[row]) {
            bongo_tap_pending = true;
        }
        held |= current != 0;
        bongo_previous_matrix[row] = current;
    }
    if (bongo_keys_held && !held) {
        bongo_last_release = timer_read32();
    }
    bongo_keys_held = held;
}

void matrix_scan_user(void) {
    scan_bongo_keys();
}

void matrix_slave_scan_user(void) {
    scan_bongo_keys();
}

// The compact font preserves the prototype's 64-pixel-wide status layout.
static const uint8_t status_glyphs[][5] PROGMEM = {
    {2,5,7,5,5}, {6,5,6,5,6}, {3,4,4,4,3}, {6,5,5,5,6},
    {7,4,6,4,7}, {7,4,6,4,4}, {3,4,5,5,3}, {5,5,7,5,5},
    {7,2,2,2,7}, {1,1,1,5,2}, {5,5,6,5,5}, {4,4,4,4,7},
    {5,7,7,5,5}, {5,7,7,7,5}, {2,5,5,5,2}, {6,5,6,4,4},
    {2,5,5,7,3}, {6,5,6,5,5}, {3,4,2,1,6}, {7,2,2,2,2},
    {5,5,5,5,7}, {5,5,5,5,2}, {5,5,7,7,5}, {5,5,2,5,5},
    {5,5,2,2,2}, {7,1,2,4,7},
    {7,5,5,5,7}, {2,6,2,2,7}, {6,1,2,4,7}, {6,1,2,1,6},
    {5,5,7,1,1}, {7,4,6,1,6}, {3,4,6,5,2}, {7,1,2,2,2},
    {2,5,2,5,2}, {2,5,3,1,6}, {1,1,2,4,4},
};

static uint8_t status_glyph_row(char character, uint8_t row) {
    uint8_t index;
    if (character >= 'A' && character <= 'Z') {
        index = character - 'A';
    } else if (character >= '0' && character <= '9') {
        index = 26 + character - '0';
    } else if (character == '/') {
        index = 36;
    } else {
        return 0;
    }
    return pgm_read_byte(&status_glyphs[index][row]);
}

static void draw_status_text(const char *value, uint8_t x, uint8_t y) {
    for (; x + 3 < 64; x += 4) {
        const char character = *value ? *value++ : ' ';
        for (uint8_t row = 0; row < 6; row++) {
            const uint8_t bits = row < 5 ? status_glyph_row(character, row) : 0;
            for (uint8_t column = 0; column < 4; column++) {
                oled_write_pixel(x + column, y + row, column < 3 && (bits & (4 >> column)));
            }
        }
    }
}

static const char *oled_layer_name(void) {
    switch (get_highest_layer(layer_state | default_layer_state)) {
        case _QWERTY:   return "QWERTY";
        case _NAV:      return "NAV";
        case _SYM:      return "SYM";
        case _INTL:     return "INTL";
        case _FUNCTION: return "FUNCTION";
        case _ADJUST:   return "ADJUST";
        default:        return "UNKNOWN";
    }
}

static void draw_status_modifiers(void) {
    const uint8_t mods = get_mods() | get_weak_mods() | get_oneshot_mods() | get_oneshot_locked_mods();
    const uint8_t masks[] = {MOD_MASK_SHIFT, MOD_MASK_CTRL, MOD_MASK_ALT, MOD_MASK_GUI};
    const char labels[] = "SCAG";
    for (uint8_t i = 0; i < 4; i++) {
        const bool active = (mods & masks[i]) != 0;
        for (uint8_t y = 0; y < 8; y++) {
            const uint8_t bits = y >= 1 && y <= 5 ? status_glyph_row(labels[i], y - 1) : 0;
            for (uint8_t x = 0; x < 9; x++) {
                const bool ink = x >= 2 && x < 5 && (bits & (1 << (4 - x)));
                oled_write_pixel(3 + i * 14 + x, 118 + y, ink != active);
            }
        }
    }
}

static void draw_bongo_frame(uint8_t frame) {
    static uint8_t drawn_frame = UINT8_MAX;
    if (frame == drawn_frame) {
        return;
    }
    drawn_frame = frame;
    uint8_t tile_index = 0;
    for (uint8_t row = 0; row < ARRAY_SIZE(bongo_line_x); row++) {
        for (uint8_t tile = 0; tile < bongo_line_len[row]; tile++) {
            const uint8_t glyph = pgm_read_byte(&bongo_line_data[frame][tile_index++]);
            for (uint8_t column = 0; column < 6; column++) {
                const uint8_t bits = pgm_read_byte(&bongofont[glyph * 6 + column]);
                for (uint8_t bit = 0; bit < 8; bit++) {
                    oled_write_pixel(bongo_line_x[row] - 40 + tile * 6 + column, bongo_line_y[row] + 44 + bit, bits & (1 << bit));
                }
            }
        }
    }
}

bool oled_task_user(void) {
    if (last_input_activity_elapsed() >= 60000 && !bongo_keys_held && !bongo_tap_pending) {
        // Flushing queued blocks wakes the panel, so finish them before switching it off.
        oled_render_dirty(true);
        oled_off();
        return false;
    }
    oled_on();

    static bool initialized;
    if (!initialized) {
        oled_clear();
        for (uint8_t x = 4; x < 60; x++) {
            oled_write_pixel(x, 105, true);
        }
        for (uint8_t x = 0; x < 17; x++) {
            oled_write_pixel(x, 75 - (x + 23) / 5, true);
        }
        for (uint8_t x = 51; x < 64; x++) {
            oled_write_pixel(x, 59 - (x - 51) / 4, true);
        }
        initialized = true;
    }

    if (bongo_tap_pending) {
        bongo_tap_pending = false;
        bongo_tap_frame = bongo_tap_frame == 6 ? 7 : 6;
        bongo_tap_started = timer_read32();
        bongo_tap_visible = true;
    }

    uint8_t frame;
    const char *pose;
    if (bongo_keys_held || (bongo_tap_visible && timer_elapsed32(bongo_tap_started) < 100)) {
        frame = bongo_tap_frame;
        pose = frame == 7 ? "LEFT TAP" : "RIGHT TAP";
    } else {
        bongo_tap_visible = false;
        const uint32_t age = timer_elapsed32(bongo_last_release);
        if (age >= 15000) {
            frame = 4;
            pose = "SLEEPING";
        } else if (age >= 750) {
            frame = 4 - ((age - 750) / 150) % 5;
            pose = "IDLE";
        } else {
            frame = 5;
            pose = "READY";
        }
    }
    draw_bongo_frame(frame);
    draw_status_text(pose, 4, 4);
    char speed[] = "000 WPM";
    memcpy(speed, get_u8_str(get_current_wpm(), '0'), 3);
    draw_status_text(speed, 18, 98);
    draw_status_text(oled_layer_name(), 4, 110);
    draw_status_modifiers();
    return false;
}
#endif

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base Layer: QWERTY
 */
    [_QWERTY] = LAYOUT_myr(
     NO_PIPE , NO_1 ,  NO_2   ,  NO_3  ,   NO_4 ,   NO_5 ,          _______,     _______,           NO_6 ,  NO_7 ,  NO_8 ,   NO_9 ,  NO_0 , KC_BSPC,
     KC_TAB  , NO_Q ,  NO_W   ,  NO_E  ,   NO_R ,   NO_T ,          _______,     _______,           NO_Y ,  NO_U ,  NO_I ,   NO_O ,  NO_P , NO_PLUS,
     KC_LSFT , NO_A ,  NO_S   ,  NO_D  ,   NO_F ,   NO_G ,          _______,     _______,           NO_H ,  NO_J ,  NO_K ,   NO_L ,NO_SCLN, NO_QUOT,
     KC_LCTL , NO_Z ,  NO_X   ,  NO_C  ,   NO_V ,   NO_B , G(KC_U),G(KC_H),   G(KC_L),KC_I,  NO_N ,  NO_M ,NO_COMM, NO_DOT ,NO_MINS, NO_QUES,
                                 KC_LALT, KC_LGUI, ESC_NAV, KC_SPC ,  INTL  ,    ADJUST , KC_ENT ,  SYM  , FKEYS , KC_NO,

     _______, _______, _______, _______,           _______,                    _______, _______, _______, _______,           _______
    ),

/*
 * Nav Layer: Media, navigation
 */
    [_NAV] = LAYOUT_myr(
     _______, _______, _______, _______, _______, _______,           _______,     _______,           _______, _______, _______, _______, _______, _______,
     _______, _______, _______, _______, _______, _______,           _______,     _______,           KC_AGIN, KC_PSTE, KC_COPY,  KC_CUT, KC_UNDO, _______,
     _______, _______, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT,           _______,     _______,           KC_LEFT, KC_DOWN,  KC_UP , KC_RGHT,  KC_DEL, _______,
     _______, _______, _______, KC_MUTE, KC_MPLY, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP,  KC_END,  KC_INS, _______,
                                _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,

     _______, _______, _______, _______,           _______,                    _______, _______, _______, _______,           _______
    ),

/*
 * Symbol Layer
 */
    [_SYM] = LAYOUT_myr(
     DICTATE, _______, _______, _______, _______, _______,           _______,     _______,           _______, _______, _______, _______, _______, _______,
     _______, _______, _______, NO_LBRC, NO_LPRN, _______,           _______,     _______,           _______, NO_RPRN, NO_RBRC, _______,   NO_AT, _______,
     _______, _______, CK_CARET,_______, NO_LCBR, _______,           _______,     _______,           _______, NO_RCBR, _______, CK_TILD,  NO_DLR, _______,
     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,

     _______, _______, _______, _______,           _______,                    _______, _______, _______, _______,           _______
    ),

/*
 * International Layer
 */
    [_INTL] = LAYOUT_myr(
     _______, _______, _______, _______, _______, _______,           _______,     _______,           _______, _______, _______, _______, _______, _______,
     _______, _______, _______, _______, _______, _______,           _______,     _______,           _______, _______, _______, _______, NO_ARNG, _______,
     _______, _______, _______, _______, _______, _______,           _______,     _______,           NO_PND , NO_EURO, _______, NO_OSTR, NO_AE , _______,
     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,

     _______, _______, _______, _______,           _______,                    _______, _______, _______, _______,           _______
    ),

/*
 * Function Layer: Function keys
 */
    [_FUNCTION] = LAYOUT_myr(
     KC_F11 ,  KC_F1 ,  KC_F2 ,  KC_F3 ,  KC_F4 ,  KC_F5 ,           _______,     _______,            KC_F6 ,  KC_F7 ,  KC_F8 ,  KC_F9 , KC_F10 , KC_F12 ,
     _______, _______, _______, _______, _______, _______,           _______,     _______,           _______, _______, _______, _______, _______, _______,
     _______, _______, _______, _______, _______, _______,           _______,     _______,           _______, _______, _______, _______, _______, _______,
     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,

     _______, _______, _______, _______,           _______,                    _______, _______, _______, _______,           _______
    ),

/*
 * Adjust Layer: Firmware controls, RGB
 */
    [_ADJUST] = LAYOUT_myr(
     QK_BOOT, _______, _______, _______, _______, _______,           _______,     _______,           _______, _______, _______, _______, _______,  EE_CLR,
     _______, _______, _______, _______, _______, _______,           _______,     _______,           _______, _______, _______, _______, _______, _______,
     _______, _______, _______, _______, _______, _______,           _______,     _______,           RM_TOGG, RM_SATU, RM_HUEU, RM_VALU, RM_NEXT, _______,
     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RM_SATD, RM_HUED, RM_VALD, RM_PREV, _______,
                                _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,

     _______, _______, _______, _______,           _______,                    _______, _______, _______, _______,           _______
    ),
};

#include QMK_KEYBOARD_H
#include "keymap_norwegian.h"

enum layers {
    _PC = 0,      // plain Norwegian, PC mod order
    _MAC,         // plain Norwegian, Mac mod order
    _NAV,         // navigation (shared)
    _SYM_PC,      // symbol layer, PC keycodes
    _SYM_MAC,     // symbol layer, Mac keycodes
    _FUN,         // function keys (shared)
    _ADJ,         // adjust (shared)
};

enum custom_keycodes {
    CK_GRV = SAFE_RANGE, // ` (dead+space), shift=~ (dead+space)
    CK_TILD,             // ~ (dead+space)
    CK_CARET,            // ^ (dead+space)
    CK_SYM,              // activate correct SYM layer based on default layer
    CK_BSLS,             // \ (OS-aware), shift=` (dead+space)
};

// macOS-specific keycodes (differ from Linux/Windows Norwegian)
#define NOM_PIPE  ALGR(NO_7)
#define NOM_BSLS  S(ALGR(NO_7))
#define NOM_QUOT  KC_NUBS
#define NOM_LABK  KC_GRV
#define NOM_RABK  S(KC_GRV)
#define NOM_AT    KC_NUHS
#define NOM_DLR   KC_DLR
#define NOM_LCBR  S(ALGR(NO_8))
#define NOM_RCBR  S(ALGR(NO_9))
#define NOM_SECT  ALGR(NO_6)

// Dead key keycodes (same on both OSes)
#define DEAD_GRV   S(KC_EQL)
#define DEAD_TILD  ALGR(KC_RBRC)
#define DEAD_CARET S(KC_RBRC)

// Layer key aliases
#define NAV_ESC  LT(_NAV, KC_ESC)
#define FUN      MO(_FUN)
#define ADJ      MO(_ADJ)
#define DICTATE  KC_F13

// Key overrides (Mac-specific: shift+' should give * not §)
#define KO_NEG (MOD_MASK_CTRL | MOD_MASK_ALT | MOD_MASK_GUI)

const key_override_t ko_mac_quot_ast = ko_make_with_layers_negmods_and_options(
    MOD_MASK_SHIFT, NOM_QUOT, NO_ASTR, 1 << _MAC, KO_NEG, 0);
const key_override_t ko_mac_pipe_sect = ko_make_with_layers_negmods_and_options(
    MOD_MASK_SHIFT, NOM_PIPE, NOM_SECT, 1 << _MAC, KO_NEG, 0);

const key_override_t *key_overrides[] = {
    &ko_mac_quot_ast,
    &ko_mac_pipe_sect,
    NULL,
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_PC] = LAYOUT_iso_62(
        NO_PIPE, NO_1,    NO_2,    NO_3,    NO_4,    NO_5,    NO_6,    NO_7,    NO_8,    NO_9,    NO_0,    NO_PLUS, CK_BSLS, KC_BSPC,
        KC_TAB,  NO_Q,    NO_W,    NO_E,    NO_R,    NO_T,    NO_Y,    NO_U,    NO_I,    NO_O,    NO_P,    NO_ARNG, NO_DIAE,
        NAV_ESC, NO_A,    NO_S,    NO_D,    NO_F,    NO_G,    NO_H,    NO_J,    NO_K,    NO_L,    NO_OSTR, NO_AE,   NO_QUOT, KC_ENT,
        KC_LSFT, NO_LABK, NO_Z,    NO_X,    NO_C,    NO_V,    NO_B,    NO_N,    NO_M,    NO_COMM, NO_DOT,  NO_MINS,          KC_RSFT,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             CK_SYM,  KC_RALT, FUN,     ADJ),

    [_MAC] = LAYOUT_iso_62(
        NOM_PIPE,NO_1,    NO_2,    NO_3,    NO_4,    NO_5,    NO_6,    NO_7,    NO_8,    NO_9,    NO_0,    NO_PLUS, CK_BSLS, KC_BSPC,
        KC_TAB,  NO_Q,    NO_W,    NO_E,    NO_R,    NO_T,    NO_Y,    NO_U,    NO_I,    NO_O,    NO_P,    NO_ARNG, NO_DIAE,
        NAV_ESC, NO_A,    NO_S,    NO_D,    NO_F,    NO_G,    NO_H,    NO_J,    NO_K,    NO_L,    NO_OSTR, NO_AE,   NOM_QUOT,KC_ENT,
        KC_LSFT, NOM_LABK,NO_Z,    NO_X,    NO_C,    NO_V,    NO_B,    NO_N,    NO_M,    NO_COMM, NO_DOT,  NO_MINS,          KC_RSFT,
        KC_LCTL, KC_LALT, KC_LGUI,                            KC_SPC,                             CK_SYM,  KC_RALT, FUN,     ADJ),

    [_NAV] = LAYOUT_iso_62(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, KC_DEL,  KC_PGUP, KC_UP,   KC_PGDN, KC_INS,  _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_DEL,  KC_BSPC, _______, _______,
        _______, _______, KC_UNDO, KC_MUTE, KC_MPLY, KC_VOLU, KC_VOLD, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______,          _______,
        _______, _______, _______,                            _______,                             _______, _______, _______, _______),

    [_SYM_PC] = LAYOUT_iso_62(
        DICTATE, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, NO_LBRC, NO_LPRN, NO_HASH, CK_GRV,  NO_RPRN, NO_RBRC, NO_ASTR, NO_AT,   NO_PERC, _______,
        _______, _______, CK_CARET,NO_PLUS, NO_LCBR, NO_EQL,  NO_PIPE, NO_RCBR, NO_DQUO, CK_TILD, NO_DLR,  NO_AMPR, _______, _______,
        _______, _______, _______, _______, _______, NO_LABK, _______, _______, NO_RABK, _______, _______, _______,          _______,
        _______, _______, _______,                            _______,                             _______, _______, _______, _______),

    [_SYM_MAC] = LAYOUT_iso_62(
        DICTATE, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, NO_LBRC, NO_LPRN, NO_HASH, CK_GRV,  NO_RPRN, NO_RBRC, NO_ASTR, NOM_AT,  NO_PERC, _______,
        _______, _______, CK_CARET,NO_PLUS, NOM_LCBR,NO_EQL,  NOM_PIPE,NOM_RCBR,NO_DQUO, CK_TILD, NOM_DLR, NO_AMPR, _______, _______,
        _______, _______, _______, _______, _______, NOM_LABK,_______, _______, NOM_RABK,_______, _______, _______,          _______,
        _______, _______, _______,                            _______,                             _______, _______, _______, _______),

    [_FUN] = LAYOUT_iso_62(
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,
        _______, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, _______, _______, _______, _______, _______, _______, _______, _______,
        KC_ESC,  KC_MUTE, KC_MPLY, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______,                            _______,                             _______, _______, _______, _______),

    [_ADJ] = LAYOUT_iso_62(
        QK_BOOT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, EE_CLR,
        _______, _______, _______, _______, _______, _______, RM_TOGG, RM_SATU, RM_HUEU, RM_VALU, RM_NEXT, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, RM_SATD, RM_HUED, RM_VALD, RM_PREV, _______, _______, KC_PSCR,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______,                            _______,                             _______, _______, _______, _______),
};

const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM =
    LAYOUT_iso_62(
        'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R', 'R', 'R',      'R',
        '*', '*', '*',                  '*',                  '*', '*', '*', '*'
    );
// clang-format on

bool dip_switch_update_user(uint8_t index, bool active) {
    if (index == 0) {
        // active=true (Windows label) -> _PC. active=false (Mac label) -> _MAC.
        set_single_persistent_default_layer(active ? _PC : _MAC);
    }
    return false; // prevent keyboard-level handler from also switching layers
}

// Tap a dead key, plus space on Mac to commit it (PC/Linux layout has no dead keys).
static void tap_dead(uint16_t dead) {
    tap_code16(dead);
    if (get_highest_layer(default_layer_state) == _MAC) {
        tap_code(KC_SPC);
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    uint8_t mods = get_mods();

    switch (keycode) {

        // shift+¨ (NO_DIAE) -> literal ^ instead of dead circumflex
        case NO_DIAE:
            if (record->event.pressed && (mods & MOD_MASK_SHIFT)
                && !(mods & (MOD_MASK_CTRL | MOD_MASK_ALT | MOD_MASK_GUI))) {
                del_mods(MOD_MASK_SHIFT);
                tap_dead(DEAD_CARET);
                set_mods(mods);
                return false;
            }
            return true;

        // Activate the correct SYM layer based on default layer
        case CK_SYM:
            if (record->event.pressed) {
                layer_on(get_highest_layer(default_layer_state) == _MAC ? _SYM_MAC : _SYM_PC);
            } else {
                layer_off(_SYM_PC);
                layer_off(_SYM_MAC);
            }
            return false;

        // Backslash key: \ unshifted (OS-aware), ` shifted (dead+space on Mac)
        case CK_BSLS:
            if (record->event.pressed) {
                if (mods & MOD_MASK_SHIFT) {
                    del_mods(MOD_MASK_SHIFT);
                    tap_dead(DEAD_GRV);
                    set_mods(mods);
                } else {
                    bool mac = (get_highest_layer(default_layer_state) == _MAC);
                    register_code16(mac ? NOM_BSLS : NO_BSLS);
                }
            } else {
                unregister_code16(NOM_BSLS);
                unregister_code16(NO_BSLS);
            }
            return false;

        // Dead key custom keycodes (Mac appends space to commit; PC has no dead keys)
        case CK_GRV:
            if (!record->event.pressed) return false;
            if (mods & MOD_MASK_SHIFT) {
                del_mods(MOD_MASK_SHIFT);
                tap_dead(DEAD_TILD);
                set_mods(mods);
            } else {
                tap_dead(DEAD_GRV);
            }
            return false;

        case CK_TILD:
            if (!record->event.pressed) return false;
            del_mods(MOD_MASK_SHIFT);
            tap_dead(DEAD_TILD);
            set_mods(mods);
            return false;

        case CK_CARET:
            if (!record->event.pressed) return false;
            del_mods(MOD_MASK_SHIFT);
            tap_dead(DEAD_CARET);
            set_mods(mods);
            return false;
    }
    return true;
}

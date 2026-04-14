#include QMK_KEYBOARD_H
#include "keymap_norwegian.h"

enum layers {
    _BASE = 0,
    _NAV,
    _SYM,
    _INTL,
    _FUN,
    _ADJ,
};

enum custom_keycodes {
    CK_PIPE = SAFE_RANGE,
    CK_BSLS,
    CK_TILD,
    CK_GRV,
    CK_CARET,
    CK_AT,
    CK_DLR,
    CK_QUOT,
    CK_LABK,
    CK_RABK,
    CK_LCBR,
    CK_RCBR,
    CK_SCLN,
    CK_SECT,
    CK_EURO,
    CK_GAME,
};

// macOS-specific aliases (keys that differ from Linux/Windows Norwegian)
#define NOM_TILD  ALGR(KC_RBRC)
#define NOM_PIPE  ALGR(NO_7)
#define NOM_QUOT  KC_NUBS
#define NOM_LABK  KC_GRV
#define NOM_RABK  S(KC_GRV)
#define NOM_AT    KC_NUHS
#define NOM_CARET S(KC_RBRC)
#define NOM_BSLS  S(ALGR(NO_7))
#define NOM_DLR   KC_DLR
#define NOM_LCBR  S(ALGR(NO_8))
#define NOM_RCBR  S(ALGR(NO_9))
#define NOM_GRV   S(KC_EQL)
#define NOM_SECT  ALGR(NO_6)
#define NOM_EURO  S(ALGR(NO_4))

static bool is_macos = true;
static bool gaming_mode = false;

// Layer key aliases
#define NAV_ESC  LT(_NAV, KC_ESC)
#define CTL_A    LCTL_T(NO_A)
#define CTL_BSLS RCTL_T(KC_F24)  // tap intercepted in process_record_user as backslash
#define SYM      MO(_SYM)
#define INTL     MO(_INTL)
#define FUN      MO(_FUN)
#define ADJ      MO(_ADJ)

// Key overrides — only standard keycodes as replacements.
// Negative mods prevent firing when Cmd/Ctrl/Alt are held (preserves OS shortcuts).
#define KO_NEG (MOD_MASK_CTRL | MOD_MASK_ALT | MOD_MASK_GUI)

const key_override_t ko_7_ampr  = ko_make_with_layers_negmods_and_options(MOD_MASK_SHIFT, NO_7,    NO_AMPR, ~0, KO_NEG, 0);
const key_override_t ko_8_astr  = ko_make_with_layers_negmods_and_options(MOD_MASK_SHIFT, NO_8,    NO_ASTR, ~0, KO_NEG, 0);
const key_override_t ko_9_lprn  = ko_make_with_layers_negmods_and_options(MOD_MASK_SHIFT, NO_9,    NO_LPRN, ~0, KO_NEG, 0);
const key_override_t ko_0_rprn  = ko_make_with_layers_negmods_and_options(MOD_MASK_SHIFT, NO_0,    NO_RPRN, ~0, KO_NEG, 0);
const key_override_t ko_min_und = ko_make_with_layers_negmods_and_options(MOD_MASK_SHIFT, NO_MINS, NO_UNDS, ~0, KO_NEG, 0);
const key_override_t ko_eql_pls = ko_make_with_layers_negmods_and_options(MOD_MASK_SHIFT, NO_EQL,  NO_PLUS, ~0, KO_NEG, 0);
const key_override_t ko_amp_ast = ko_make_with_layers_negmods_and_options(MOD_MASK_SHIFT, NO_AMPR, NO_ASTR, ~0, KO_NEG, 0);
const key_override_t ko_sl_ques = ko_make_with_layers_negmods_and_options(MOD_MASK_SHIFT, NO_SLSH, NO_QUES, ~0, KO_NEG, 0);

const key_override_t *key_overrides[] = {
    &ko_7_ampr,  &ko_8_astr,  &ko_9_lprn,  &ko_0_rprn,
    &ko_min_und, &ko_eql_pls, &ko_amp_ast,  &ko_sl_ques,
    NULL,
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BASE] = LAYOUT_iso_62(
        CK_GRV,  NO_1,    NO_2,    NO_3,    NO_4,    NO_5,    NO_6,    NO_7,    NO_8,    NO_9,    NO_0,    NO_MINS, NO_EQL,  KC_BSPC,
        KC_TAB,  NO_Q,    NO_W,    NO_E,    NO_R,    NO_T,    NO_Y,    NO_U,    NO_I,    NO_O,    NO_P,    NO_AMPR, CK_AT,
        NAV_ESC, CTL_A,   NO_S,    NO_D,    NO_F,    NO_G,    NO_H,    NO_J,    NO_K,    NO_L,    CK_SCLN, CK_QUOT, CTL_BSLS,KC_ENT,
        KC_LSFT, NO_HASH, NO_Z,    NO_X,    NO_C,    NO_V,    NO_B,    NO_N,    NO_M,    NO_COMM, NO_DOT,  NO_SLSH,          KC_RSFT,
        KC_LCTL, KC_LALT, KC_LGUI,                            KC_SPC,                             SYM,     INTL,    FUN,     ADJ),

    [_NAV] = LAYOUT_iso_62(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, KC_DEL,  KC_PGUP, KC_UP,   KC_PGDN, KC_INS,  _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_DEL,  KC_BSPC, _______, _______,
        _______, _______, KC_UNDO, KC_MUTE, KC_MPLY, KC_VOLU, KC_VOLD, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______,          _______,
        _______, _______, _______,                            _______,                             _______, _______, _______, _______),

    [_SYM] = LAYOUT_iso_62(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, NO_LPRN, NO_RPRN, NO_LBRC, NO_RBRC, _______, _______, CK_GRV,  NO_HASH, NO_ASTR, CK_AT,   NO_PERC, _______,
        _______, CK_CARET,NO_MINS, NO_PLUS, NO_EQL,  _______, _______, CK_PIPE, CK_QUOT, CK_TILD, NO_AMPR, CK_BSLS, CK_DLR,  _______,
        _______, _______, CK_LCBR, CK_RCBR, CK_LABK, _______, _______, CK_RABK, _______, _______, _______, _______,          _______,
        _______, _______, _______,                            _______,                             _______, _______, _______, _______),

    [_INTL] = LAYOUT_iso_62(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, CK_SECT, _______, _______, _______, _______, _______, _______, _______, _______, _______, NO_ARNG, _______,
        _______, NO_PND,  _______, CK_EURO, _______, _______, _______, _______, _______, _______, NO_OSTR, NO_AE,   _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______,                            _______,                             _______, _______, _______, _______),

    [_FUN] = LAYOUT_iso_62(
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,
        _______, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, KC_MUTE, KC_MPLY, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______,                            _______,                             _______, _______, _______, _______),

    [_ADJ] = LAYOUT_iso_62(
        QK_BOOT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, EE_CLR,
        _______, _______, _______, _______, _______, _______, RM_TOGG, RM_SATU, RM_HUEU, RM_VALU, RM_NEXT, _______, _______,
        _______, CK_GAME, _______, _______, _______, _______, _______, RM_SATD, RM_HUED, RM_VALD, RM_PREV, _______, _______, _______,
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
        is_macos = !active;
    }
    return false; // prevent keyboard-level handler from switching default layer
}

// Helper: check if ONLY shift is held (no ctrl/alt/gui)
static bool shift_only(uint8_t mods) {
    return (mods & MOD_MASK_SHIFT) && !(mods & (MOD_MASK_CTRL | MOD_MASK_ALT | MOD_MASK_GUI));
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    uint8_t mods = get_mods();

    switch (keycode) {

        // --- Gaming mode toggle ---

        case CK_GAME:
            if (record->event.pressed) {
                gaming_mode = !gaming_mode;
            }
            return false;

        // --- Gaming mode: disable HRM on A ---

        case LCTL_T(NO_A):
            if (gaming_mode) {
                record->event.pressed ? register_code(KC_A) : unregister_code(KC_A);
                return false;
            }
            return true;

        // --- Left Alt/GUI swap for Linux/Windows (preserves RALT/AltGr) ---

        case KC_LALT:
            if (!is_macos) {
                record->event.pressed ? register_code(KC_LGUI) : unregister_code(KC_LGUI);
                return false;
            }
            return true;

        case KC_LGUI:
            if (!is_macos) {
                record->event.pressed ? register_code(KC_LALT) : unregister_code(KC_LALT);
                return false;
            }
            return true;

        // --- Number row: US shift emulation (only when shift alone is held) ---

        case NO_2:
            if (record->event.pressed && shift_only(mods)) {
                del_mods(MOD_MASK_SHIFT);
                register_code16(is_macos ? NOM_AT : NO_AT);
                set_mods(mods);
                return false;
            }
            if (!record->event.pressed) unregister_code16(is_macos ? NOM_AT : NO_AT);
            return true;

        case NO_4:
            if (record->event.pressed && shift_only(mods)) {
                del_mods(MOD_MASK_SHIFT);
                register_code16(is_macos ? NOM_DLR : NO_DLR);
                set_mods(mods);
                return false;
            }
            if (!record->event.pressed) unregister_code16(is_macos ? NOM_DLR : NO_DLR);
            return true;

        case NO_6:
            if (record->event.pressed && shift_only(mods)) {
                del_mods(MOD_MASK_SHIFT);
                tap_code16(is_macos ? NOM_CARET : NO_CIRC);
                tap_code(KC_SPC);
                set_mods(mods);
                return false;
            }
            return true;

        case NO_HASH:
            if (record->event.pressed && shift_only(mods)) {
                del_mods(MOD_MASK_SHIFT);
                tap_code16(is_macos ? NOM_TILD : NO_TILD);
                tap_code(KC_SPC);
                set_mods(mods);
                return false;
            }
            return true;

        case NO_COMM:
            if (record->event.pressed && shift_only(mods)) {
                del_mods(MOD_MASK_SHIFT);
                register_code16(is_macos ? NOM_LABK : NO_LABK);
                set_mods(mods);
                return false;
            }
            if (!record->event.pressed) unregister_code16(is_macos ? NOM_LABK : NO_LABK);
            return true;

        case NO_DOT:
            if (record->event.pressed && shift_only(mods)) {
                del_mods(MOD_MASK_SHIFT);
                register_code16(is_macos ? NOM_RABK : NO_RABK);
                set_mods(mods);
                return false;
            }
            if (!record->event.pressed) unregister_code16(is_macos ? NOM_RABK : NO_RABK);
            return true;

        // --- Custom keycodes with shift variants ---

        case CK_AT:
            if (record->event.pressed) {
                if (mods & MOD_MASK_SHIFT) {
                    del_mods(MOD_MASK_SHIFT);
                    register_code16(NO_EXLM);
                    set_mods(mods);
                } else {
                    register_code16(is_macos ? NOM_AT : NO_AT);
                }
            } else {
                unregister_code16(is_macos ? NOM_AT : NO_AT);
                unregister_code16(NO_EXLM);
            }
            return false;

        case CK_BSLS:
            record->event.pressed ? register_code16(is_macos ? NOM_BSLS : NO_BSLS)
                                  : unregister_code16(is_macos ? NOM_BSLS : NO_BSLS);
            return false;

        case CK_QUOT:
            if (record->event.pressed) {
                if (mods & MOD_MASK_SHIFT) {
                    del_mods(MOD_MASK_SHIFT);
                    register_code16(is_macos ? NOM_QUOT : NO_QUOT);
                    set_mods(mods);
                } else {
                    register_code16(NO_DQUO);
                }
            } else {
                unregister_code16(NO_DQUO);
                unregister_code16(is_macos ? NOM_QUOT : NO_QUOT);
            }
            return false;

        case CK_SCLN:
            if (record->event.pressed) {
                if (mods & MOD_MASK_SHIFT) {
                    del_mods(MOD_MASK_SHIFT);
                    register_code16(NO_COLN);
                    set_mods(mods);
                } else {
                    register_code16(NO_SCLN);
                }
            } else {
                unregister_code16(NO_SCLN);
                unregister_code16(NO_COLN);
            }
            return false;

        // --- RCTL_T tap: backslash, shift=pipe. Hold: RCtrl. ---

        case RCTL_T(KC_F24):
            if (record->tap.count > 0) {
                if (record->event.pressed) {
                    if (mods & MOD_MASK_SHIFT) {
                        del_mods(MOD_MASK_SHIFT);
                        register_code16(is_macos ? NOM_PIPE : NO_PIPE);
                        set_mods(mods);
                    } else {
                        register_code16(is_macos ? NOM_BSLS : NO_BSLS);
                    }
                } else {
                    unregister_code16(is_macos ? NOM_BSLS : NO_BSLS);
                    unregister_code16(is_macos ? NOM_PIPE : NO_PIPE);
                }
                return false;
            }
            return true;

        // --- Simple dispatch (register/unregister for key repeat) ---

        case CK_PIPE:
            record->event.pressed ? register_code16(is_macos ? NOM_PIPE : NO_PIPE)
                                  : unregister_code16(is_macos ? NOM_PIPE : NO_PIPE);
            return false;

        case CK_DLR:
            record->event.pressed ? register_code16(is_macos ? NOM_DLR : NO_DLR)
                                  : unregister_code16(is_macos ? NOM_DLR : NO_DLR);
            return false;

        case CK_LABK:
            record->event.pressed ? register_code16(is_macos ? NOM_LABK : NO_LABK)
                                  : unregister_code16(is_macos ? NOM_LABK : NO_LABK);
            return false;

        case CK_RABK:
            record->event.pressed ? register_code16(is_macos ? NOM_RABK : NO_RABK)
                                  : unregister_code16(is_macos ? NOM_RABK : NO_RABK);
            return false;

        case CK_LCBR:
            record->event.pressed ? register_code16(is_macos ? NOM_LCBR : NO_LCBR)
                                  : unregister_code16(is_macos ? NOM_LCBR : NO_LCBR);
            return false;

        case CK_RCBR:
            record->event.pressed ? register_code16(is_macos ? NOM_RCBR : NO_RCBR)
                                  : unregister_code16(is_macos ? NOM_RCBR : NO_RCBR);
            return false;

        case CK_SECT:
            record->event.pressed ? register_code16(is_macos ? NOM_SECT : NO_SECT)
                                  : unregister_code16(is_macos ? NOM_SECT : NO_SECT);
            return false;

        case CK_EURO:
            record->event.pressed ? register_code16(is_macos ? NOM_EURO : NO_EURO)
                                  : unregister_code16(is_macos ? NOM_EURO : NO_EURO);
            return false;

        // --- Dead keys (tap only, no repeat) ---

        case CK_TILD:
            if (!record->event.pressed) return false;
            del_mods(MOD_MASK_SHIFT);
            tap_code16(is_macos ? NOM_TILD : NO_TILD);
            tap_code(KC_SPC);
            set_mods(mods);
            return false;

        case CK_GRV:
            if (!record->event.pressed) return false;
            if (mods & MOD_MASK_SHIFT) {
                del_mods(MOD_MASK_SHIFT);
                tap_code16(is_macos ? NOM_TILD : NO_TILD);
                tap_code(KC_SPC);
                set_mods(mods);
            } else {
                tap_code16(is_macos ? NOM_GRV : NO_GRV);
                tap_code(KC_SPC);
            }
            return false;

        case CK_CARET:
            if (!record->event.pressed) return false;
            del_mods(MOD_MASK_SHIFT);
            tap_code16(is_macos ? NOM_CARET : NO_CIRC);
            tap_code(KC_SPC);
            set_mods(mods);
            return false;
    }
    return true;
}

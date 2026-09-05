// Copyright 2024 splitkb.com (support@splitkb.com)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "keymap_norwegian.h"

enum layers {
    _QWERTY = 0,
    _NAV,
    _SYM,
    _NUM,
    _FUNCTION,
    _ADJUST,
    _INTL,
};

enum custom_keycodes {
    CK_ELLP = SAFE_RANGE,
};

#define NAV_ESC LT(_NAV, KC_ESC)
#define SYM MO(_SYM)
#define NUM MO(_NUM)
#define FKEYS MO(_FUNCTION)
#define ADJUST MO(_ADJUST)
#define INTL MO(_INTL)

#define DPRV G(KC_PGDN)
#define DNXT G(KC_PGUP)

// Linux Norwegian AltGr outputs.
#define LNX_EURO ALGR(NO_E)
#define LNX_REGD ALGR(NO_R)
#define LNX_YEN ALGR(NO_6)
#define LNX_DEG S(ALGR(NO_0))
#define LNX_PI ALGR(NO_P)
#define LNX_COPY ALGR(NO_C)
#define LNX_ENDASH ALGR(NO_MINS)

const key_override_t slash_shift_override = ko_make_basic(MOD_MASK_SHIFT, NO_SLSH, NO_BSLS);
const key_override_t symbol_grave_shift_override = ko_make_with_layers(MOD_MASK_SHIFT, NO_GRV, NO_TILD, 1UL << _SYM);
const key_override_t symbol_left_bracket_shift_override = ko_make_with_layers(MOD_MASK_SHIFT, NO_LBRC, NO_LCBR, 1UL << _SYM);
const key_override_t symbol_right_bracket_shift_override = ko_make_with_layers(MOD_MASK_SHIFT, NO_RBRC, NO_RCBR, 1UL << _SYM);
const key_override_t symbol_quote_shift_override = ko_make_with_layers(MOD_MASK_SHIFT, NO_QUOT, NO_QUOT, 1UL << _SYM);

const key_override_t *key_overrides[] = {
    &slash_shift_override,
    &symbol_grave_shift_override,
    &symbol_left_bracket_shift_override,
    &symbol_right_bracket_shift_override,
    &symbol_quote_shift_override,
    NULL,
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
      KC_TAB,  NO_Q,    NO_W,    NO_E,    NO_R,    NO_T,                                      NO_Y,    NO_U,    NO_I,    NO_O,    NO_P,    NO_ARNG,
      KC_LSFT, NO_A,    NO_S,    NO_D,    NO_F,    NO_G,                                      NO_H,    NO_J,    NO_K,    NO_L,    NO_OSTR, NO_AE,
      KC_LCTL, NO_Z,    NO_X,    NO_C,    NO_V,    NO_B,    DPRV, ADJUST,        INTL, DNXT,  NO_N,    NO_M,    NO_COMM, NO_DOT,  NO_MINS, NO_SLSH,
                                 KC_LALT, KC_LGUI, NAV_ESC, KC_SPC, FKEYS,        KC_BSPC, KC_ENT, SYM, NUM, KC_APP
    ),

    [_NAV] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                                    KC_INS,  KC_HOME, KC_PGDN, KC_PGUP, KC_END,  C(KC_Z),
      _______, _______, _______, _______, _______, _______,                                    KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_DEL,  KC_BSPC,
      _______, _______, _______, _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______
    ),

    [_SYM] = LAYOUT(
      _______, _______, _______, NO_LBRC, NO_LPRN, NO_HASH,                                    NO_GRV,  NO_RPRN, NO_RBRC, NO_ASTR, NO_AT,   NO_PERC,
      _______, _______, NO_CIRC, NO_EXLM, NO_LCBR, NO_EQL,                                     NO_PIPE, NO_RCBR, NO_DQUO, NO_TILD, NO_DLR,  NO_AMPR,
      _______, _______, NO_LABK, NO_PLUS, _______, _______, _______, _______,      _______, _______, _______, _______, NO_QUOT, NO_RABK, _______, _______,
                                 _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______
    ),

    [_NUM] = LAYOUT(
      _______, _______, NO_7,    NO_8,    NO_9,    NO_ASTR,                                    _______, _______, _______, _______, _______, _______,
      _______, NO_PERC, NO_4,    NO_5,    NO_6,    NO_EQL,                                     _______, _______, _______, _______, _______, _______,
      _______, NO_PLUS, NO_1,    NO_2,    NO_3,    NO_MINS, _______, _______,      _______, _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, NO_0,    _______,      _______, _______, _______, _______, _______
    ),

    [_FUNCTION] = LAYOUT(
      _______, KC_F12,  KC_F7,   KC_F8,   KC_F9,   _______,                                    _______, _______, _______, _______, _______, _______,
      _______, KC_F11,  KC_F4,   KC_F5,   KC_F6,   _______,                                    KC_MUTE, KC_MPRV, KC_MPLY, KC_MNXT, KC_VOLD, KC_VOLU,
      _______, KC_F10,  KC_F1,   KC_F2,   KC_F3,   _______, _______, _______,      _______, _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______
    ),

    [_ADJUST] = LAYOUT(
      QK_BOOT, _______, _______, _______, _______, _______,                                    RM_TOGG, RM_SATU, RM_HUEU, RM_VALU, RM_NEXT, EE_CLR,
      _______, _______, _______, _______, _______, _______,                                    _______, RM_SATD, RM_HUED, RM_VALD, RM_PREV, KC_PSCR,
      _______, _______, _______, _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______
    ),

    [_INTL] = LAYOUT(
      _______, _______, _______, LNX_EURO,LNX_REGD,_______,                                    LNX_YEN, _______, _______, LNX_DEG, LNX_PI,  _______,
      _______, _______, _______, _______, _______, _______,                                    _______, _______, _______, NO_PND,  _______, _______,
      _______, _______, _______, LNX_COPY,_______, _______, _______, _______,      _______, _______, _______, NO_MICR,  _______, CK_ELLP, LNX_ENDASH,_______,
                                 _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______
    ),
};
// clang-format on

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode != CK_ELLP) {
        return true;
    }
    if (!record->event.pressed) {
        return false;
    }

    uint8_t mods = get_mods();
    if (mods & MOD_MASK_SHIFT) {
        del_mods(MOD_MASK_SHIFT);
        tap_code16(ALGR(NO_DOT));
        set_mods(mods);
    } else {
        tap_code16(ALGR(NO_QUOT));
    }
    return false;
}

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_QWERTY]  = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_NAV]     = { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______) },
    [_SYM]     = { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______) },
    [_NUM]     = { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______) },
    [_FUNCTION]= { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______) },
    [_ADJUST]  = { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______) },
    [_INTL]    = { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______) },
};
#endif

#if defined(HALCYON_ENABLE)
const uint16_t left_halcyon_buttons[10][5] = {
    [_QWERTY]   = { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO },
    [_NAV]      = { _______, _______, _______, _______, _______ },
    [_SYM]      = { _______, _______, _______, _______, _______ },
    [_NUM]      = { _______, _______, _______, _______, _______ },
    [_FUNCTION] = { _______, _______, _______, _______, _______ },
    [_ADJUST]   = { _______, _______, _______, _______, _______ },
    [_INTL]     = { _______, _______, _______, _______, _______ },
};

const uint16_t right_halcyon_buttons[10][5] = {
    [_QWERTY]   = { KC_MPLY, KC_NO, KC_NO, KC_NO, KC_NO },
    [_NAV]      = { _______, _______, _______, _______, _______ },
    [_SYM]      = { _______, _______, _______, _______, _______ },
    [_NUM]      = { _______, _______, _______, _______, _______ },
    [_FUNCTION] = { _______, _______, _______, _______, _______ },
    [_ADJUST]   = { _______, _______, _______, _______, _______ },
    [_INTL]     = { _______, _______, _______, _______, _______ },
};
#endif

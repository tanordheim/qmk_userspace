// Copyright 2024 splitkb.com (support@splitkb.com)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "keymap_norwegian.h"
#include "layers.h"

// Host layout: Norwegian (no dead keys).

enum custom_keycodes {
    CK_CARET = SAFE_RANGE,
    CK_TILD,
};

#define ESC_NAV LT(_NAV, KC_ESC)
#define SYM MO(_SYM)
#define NUM MO(_NUM)
#define FKEYS MO(_FUNCTION)
#define ADJUST MO(_ADJUST)
#define INTL MO(_INTL)
#define DICTATE KC_F13

const key_override_t semicolon_shift_override = ko_make_basic(MOD_MASK_SHIFT, NO_SCLN, NO_COLN);
const key_override_t comma_shift_override = ko_make_basic(MOD_MASK_SHIFT, NO_COMM, NO_LABK);
const key_override_t dot_shift_override = ko_make_basic(MOD_MASK_SHIFT, NO_DOT, NO_RABK);
const key_override_t slash_shift_override = ko_make_basic(MOD_MASK_SHIFT, NO_SLSH, NO_PIPE);
const key_override_t questionmark_shift_override = ko_make_basic(MOD_MASK_SHIFT, NO_QUES, NO_EXLM);
const key_override_t quote_shift_override = ko_make_basic(MOD_MASK_SHIFT, NO_QUOT, NO_DQUO);
const key_override_t plus_shift_override = ko_make_basic(MOD_MASK_SHIFT, NO_PLUS, NO_GRV);

const key_override_t *key_overrides[] = {
    &semicolon_shift_override,
    &comma_shift_override,
    &dot_shift_override,
    &slash_shift_override,
    &questionmark_shift_override,
    &quote_shift_override,
    &plus_shift_override,
    NULL,
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
      KC_TAB,    NO_Q,      NO_W,      NO_E,      NO_R,      NO_T,                            NO_Y,      NO_U,      NO_I,      NO_O,      NO_P,      KC_BSPC,
      KC_LSFT,   NO_A,      NO_S,      NO_D,      NO_F,      NO_G,                            NO_H,      NO_J,      NO_K,      NO_L,      NO_SCLN,   NO_QUOT,
      KC_LCTL,   NO_Z,      NO_X,      NO_C,      NO_V,      NO_B,      G(KC_U),   G(KC_H),   G(KC_L),   G(KC_I),   NO_N,      NO_M,      NO_COMM,   NO_DOT,    NO_SLSH,   NO_QUES,
                                 KC_LALT,   KC_LGUI,   ESC_NAV,   KC_SPC,    INTL,            ADJUST,    KC_ENT,    SYM,       NUM,       FKEYS
    ),

    [_NAV] = LAYOUT(
      _______,   _______,   _______,   _______,   _______,   _______,                         KC_AGIN,   KC_PSTE,   KC_COPY,   KC_CUT,    KC_UNDO,   _______,
      _______,   _______,   KC_MPRV,   KC_VOLD,   KC_VOLU,   KC_MNXT,                         KC_LEFT,   KC_DOWN,   KC_UP,     KC_RGHT,   KC_DEL,    _______,
      _______,   _______,   _______,   KC_MUTE,   KC_MPLY,   _______,   _______,   _______,   _______,   _______,   KC_HOME,   KC_PGDN,   KC_PGUP,   KC_END,    KC_INS,    _______,
                                 _______,   _______,   _______,   _______,   _______,         _______,   _______,   _______,   _______,   _______
    ),

    [_SYM] = LAYOUT(
      _______,   _______,   NO_GRV,    NO_LBRC,   NO_LPRN,   NO_ASTR,                         _______,   NO_RPRN,   NO_RBRC,   _______,   NO_AT,     _______,
      _______,   NO_PERC,   CK_CARET,  NO_AMPR,   NO_LCBR,   NO_EQL,                          _______,   NO_RCBR,   _______,   CK_TILD,   NO_DLR,    _______,
      DICTATE,   NO_PLUS,   NO_SECT,   NO_HASH,   NO_UNDS,   NO_MINS,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   NO_BSLS,   _______,
                                 _______,   _______,   _______,   _______,   _______,         _______,   _______,   _______,   _______,   _______
    ),

    [_NUM] = LAYOUT(
      _______,   NO_SLSH,   NO_7,      NO_8,      NO_9,      NO_ASTR,                         _______,   _______,   _______,   _______,   _______,   _______,
      _______,   NO_PERC,   NO_4,      NO_5,      NO_6,      NO_EQL,                          _______,   _______,   _______,   _______,   _______,   _______,
      _______,   NO_PLUS,   NO_1,      NO_2,      NO_3,      NO_MINS,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,
                                 _______,   _______,   _______,   NO_0,      _______,         _______,   _______,   _______,   _______,   _______
    ),

    [_FUNCTION] = LAYOUT(
      _______,   _______,   KC_F7,     KC_F8,     KC_F9,     KC_F13,                          _______,   _______,   _______,   _______,   _______,   _______,
      _______,   _______,   KC_F4,     KC_F5,     KC_F6,     KC_F12,                          _______,   _______,   _______,   _______,   _______,   _______,
      _______,   KC_F10,    KC_F1,     KC_F2,     KC_F3,     KC_F11,    _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,
                                 _______,   _______,   _______,   _______,   _______,         _______,   _______,   _______,   _______,   _______
    ),

    [_ADJUST] = LAYOUT(
      QK_BOOT,   _______,   _______,   _______,   _______,   _______,                         _______,   _______,   _______,   _______,   _______,   EE_CLR,
      _______,   _______,   _______,   _______,   _______,   _______,                         RM_TOGG,   RM_SATU,   RM_HUEU,   RM_VALU,   RM_NEXT,   _______,
      _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   RM_SATD,   RM_HUED,   RM_VALD,   RM_PREV,   _______,
                                 _______,   _______,   _______,   _______,   _______,         _______,   _______,   _______,   _______,   _______
    ),

    [_INTL] = LAYOUT(
      _______,   _______,   _______,   _______,   _______,   _______,                         _______,   _______,   _______,   _______,   NO_ARNG,   _______,
      _______,   _______,   _______,   _______,   _______,   _______,                         NO_PND,    ALGR(NO_E),_______,   NO_OSTR,   NO_AE,     _______,
      _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,
                                 _______,   _______,   _______,   _______,   _______,         _______,   _______,   _______,   _______,   _______
    ),
};
// clang-format on

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

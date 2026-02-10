// Copyright 2024 splitkb.com (support@splitkb.com)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "keymap_norwegian.h"
#include "sendstring_norwegian.h"

enum layers {
    _COLEMAK_DH = 0,
    _QWERTY,
    _NAV,
    _SYM,
    _NUM,
    _INTL,
    _FUNCTION,
    _ADJUST,
};


const int TRACKPAD_SENSITIVITY_DIVISOR = 2;

// Aliases for readability
#define COLEMAK   DF(_COLEMAK_DH)
#define QWERTY    DF(_QWERTY)

#define SYM       MO(_SYM)
#define NAV       MO(_NAV)
#define NUM       MO(_NUM)
#define INTL      MO(_INTL)
#define FKEYS     MO(_FUNCTION)
#define ADJUST    MO(_ADJUST)

#define ESC_NAV   LT(_NAV, KC_ESC)
#define NOM_TILD  ALGR(KC_RBRC)
#define NOM_PIPE  ALGR(NO_7)
#define NOM_QUOT  KC_NUBS
#define NOM_LABK  KC_GRV
#define NOM_RABK  S(KC_GRV)
#define NOM_AT    KC_NUHS
#define NOM_CARET S(KC_RBRC)
#define NOM_BSLS  S(ALGR(NO_7))
#define NOM_DLR   KC_DLR
#define NOM_LBRC  ALGR(NO_8)
#define NOM_RBRC  ALGR(NO_9)
#define NOM_LCBR  S(ALGR(NO_8))
#define NOM_RCBR  S(ALGR(NO_9))
#define DPRV      G(KC_PGDN)
#define DNXT      G(KC_PGUP)

// Key overrides
// const key_override_t pipe_shift_override = ko_make_basic(MOD_MASK_SHIFT, NOM_PIPE, NOM_TILD);
// const key_override_t n2_shift_override = ko_make_basic(MOD_MASK_SHIFT, NO_2, NOM_AT);
// const key_override_t n6_shift_override = ko_make_basic(MOD_MASK_SHIFT, NO_6, NOM_CARET);
// const key_override_t n7_shift_override = ko_make_basic(MOD_MASK_SHIFT, NO_7, NO_AMPR);
// const key_override_t n9_shift_override = ko_make_basic(MOD_MASK_SHIFT, NO_9, NO_LPRN);
// const key_override_t n0_shift_override = ko_make_basic(MOD_MASK_SHIFT, NO_0, NO_RPRN);
// const key_override_t eql_shift_override = ko_make_basic(MOD_MASK_SHIFT, NO_EQL, NO_PLUS);
const key_override_t semicolon_shift_override = ko_make_basic(MOD_MASK_SHIFT, NO_SCLN, NO_COLN);
const key_override_t dblquote_shift_override = ko_make_basic(MOD_MASK_SHIFT, NO_DQUO, NOM_QUOT);
const key_override_t comma_shift_override = ko_make_basic(MOD_MASK_SHIFT, NO_COMM, NOM_LABK);
const key_override_t dot_shift_override = ko_make_basic(MOD_MASK_SHIFT, NO_DOT, NOM_RABK);
const key_override_t slash_shift_override = ko_make_basic(MOD_MASK_SHIFT, NO_SLSH, NOM_BSLS);
const key_override_t questionmark_shift_override = ko_make_basic(MOD_MASK_SHIFT, NO_QUES, NO_EXLM);
const key_override_t *key_overrides[] = {
    // &pipe_shift_override,
    // &n2_shift_override,
    // &n6_shift_override,
    // &n7_shift_override,
    // &n9_shift_override,
    // &n0_shift_override,
    // &eql_shift_override,
	&semicolon_shift_override,
    &dblquote_shift_override,
    &comma_shift_override,
    &dot_shift_override,
    &slash_shift_override,
    &questionmark_shift_override,
};

// Combos
const uint16_t PROGMEM lprn_colemak_combo[] = {NO_F, NO_P, COMBO_END};
const uint16_t PROGMEM lprn_qwerty_combo[] = {NO_E, NO_R, COMBO_END};
const uint16_t PROGMEM rprn_colemak_combo[] = {NO_L, NO_U, COMBO_END};
const uint16_t PROGMEM rprn_qwerty_combo[] = {NO_U, NO_I, COMBO_END};
const uint16_t PROGMEM lcbr_colemak_combo[] = {NO_S, NO_T, COMBO_END};
const uint16_t PROGMEM lcbr_qwerty_combo[] = {NO_D, NO_F, COMBO_END};
const uint16_t PROGMEM rcbr_colemak_combo[] = {NO_N, NO_E, COMBO_END};
const uint16_t PROGMEM rcbr_qwerty_combo[] = {NO_H, NO_J, COMBO_END};
const uint16_t PROGMEM lbrc_colemak_combo[] = {NO_C, NO_D, COMBO_END};
const uint16_t PROGMEM lbrc_qwerty_combo[] = {NO_C, NO_V, COMBO_END};
const uint16_t PROGMEM rbrc_colemak_combo[] = {NO_H, NO_COMM, COMBO_END};
const uint16_t PROGMEM rbrc_qwerty_combo[] = {NO_M, NO_COMM, COMBO_END};

enum combo_events {
    LPRN_COLEMAK,
    LPRN_QWERTY,
    RPRN_COLEMAK,
    RPRN_QWERTY,
    LCBR_COLEMAK,
    LCBR_QWERTY,
    RCBR_COLEMAK,
    RCBR_QWERTY,
    LBRC_COLEMAK,
    LBRC_QWERTY,
    RBRC_COLEMAK,
    RBRC_QWERTY,
};

combo_t key_combos[] = {
    [LPRN_COLEMAK] = COMBO(lprn_colemak_combo, NO_LPRN),
    [LPRN_QWERTY] = COMBO(lprn_qwerty_combo, NO_LPRN),
    [RPRN_COLEMAK] = COMBO(rprn_colemak_combo, NO_RPRN),
    [RPRN_QWERTY] = COMBO(rprn_qwerty_combo, NO_RPRN),
    [LCBR_COLEMAK] = COMBO(lcbr_colemak_combo, NOM_LCBR),
    [LCBR_QWERTY] = COMBO(lcbr_qwerty_combo, NOM_LCBR),
    [RCBR_COLEMAK] = COMBO(rcbr_colemak_combo, NOM_RCBR),
    [RCBR_QWERTY] = COMBO(rcbr_qwerty_combo, NOM_RCBR),
    [LBRC_COLEMAK] = COMBO(lbrc_colemak_combo, NOM_LBRC),
    [LBRC_QWERTY] = COMBO(lbrc_qwerty_combo, NOM_LBRC),
    [RBRC_COLEMAK] = COMBO(rbrc_colemak_combo, NOM_RBRC),
    [RBRC_QWERTY] = COMBO(rbrc_qwerty_combo, NOM_RBRC),
};


bool combo_should_trigger(uint16_t combo_index, combo_t *combo, uint16_t keycode, keyrecord_t *record) {
    uint8_t base_layer = get_highest_layer(default_layer_state);

    switch (combo_index) {
        case LPRN_COLEMAK:
        case RPRN_COLEMAK:
        case LCBR_COLEMAK:
        case RCBR_COLEMAK:
        case LBRC_COLEMAK:
        case RBRC_COLEMAK:
            return base_layer == _COLEMAK_DH;
        case LPRN_QWERTY:
        case RPRN_QWERTY:
        case LCBR_QWERTY:
        case RCBR_QWERTY:
        case LBRC_QWERTY:
        case RBRC_QWERTY:
            return base_layer == _QWERTY;
    }
    return false;
}

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base Layer: Colemak DH
 */
    [_COLEMAK_DH] = LAYOUT_split_3x6_5_hlc(
     KC_TAB  , NO_Q ,  NO_W   ,  NO_F  ,   NO_P ,   NO_B ,                                        NO_J,   NO_L ,  NO_U ,   NO_Y ,NO_SCLN, KC_BSPC,
     KC_LSFT , NO_A ,  NO_R   ,  NO_S  ,   NO_T ,   NO_G ,                                        NO_M,   NO_N ,  NO_E ,   NO_I ,  NO_O , NO_DQUO,
     KC_LCTL , NO_Z ,  NO_X   ,  NO_C  ,   NO_D ,   NO_V ,  DPRV  ,KC_CAPS,     FKEYS  ,  DNXT  , NO_K,   NO_H ,NO_COMM, NO_DOT ,NO_SLSH, NO_QUES,
                                KC_LALT, KC_LGUI, ESC_NAV, KC_SPC ,  INTL ,     ADJUST , KC_ENT , SYM ,   NUM , KC_APP,
     KC_MUTE, KC_NO,  KC_NO, KC_NO, KC_NO,                                                                KC_MUTE, KC_NO, KC_NO, KC_NO, KC_NO
    ),

/*
 * Base Layer: QWERTY
 */
    [_QWERTY] = LAYOUT_split_3x6_5_hlc(
     KC_TAB  , NO_Q ,  NO_W   ,  NO_E  ,   NO_R ,   NO_T ,                                        NO_Y,   NO_U ,  NO_I ,   NO_O ,  NO_P , KC_BSPC,
     KC_LSFT , NO_A ,  NO_S   ,  NO_D  ,   NO_F ,   NO_G ,                                        NO_H,   NO_J ,  NO_K ,   NO_L ,NO_SCLN, NO_DQUO,
     KC_LCTL , NO_Z ,  NO_X   ,  NO_C  ,   NO_V ,   NO_B ,  DPRV  ,KC_CAPS,     FKEYS  ,  DNXT  , NO_N,   NO_M ,NO_COMM, NO_DOT ,NO_SLSH, NO_QUES,
                                KC_LALT, KC_LGUI, ESC_NAV, KC_SPC , INTL   ,    ADJUST , KC_ENT , SYM ,   NUM  ,KC_APP,
     KC_MUTE, KC_NO,  KC_NO, KC_NO, KC_NO,                                                                KC_MUTE, KC_NO, KC_NO, KC_NO, KC_NO
    ),

/*
 * Nav Layer: Media, navigation
 */
    [_NAV] = LAYOUT_split_3x6_5_hlc(
      _______, _______, _______, _______, _______, _______,                                     KC_AGIN, KC_PSTE, KC_COPY,  KC_CUT, KC_UNDO, _______,
      _______, _______, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT,                                     KC_LEFT, KC_DOWN,  KC_UP , KC_RGHT,  KC_DEL, _______,
      _______, _______, _______, KC_MUTE, KC_MPLY, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP,  KC_END,  KC_INS, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,

      _______, _______, _______, _______, _______,                                                       _______, _______, _______, _______, _______
    ),

/*
 * Sym Layer: Numbers and symbols
 */
    [_SYM] = LAYOUT_split_3x6_5_hlc(
      _______,NOM_PIPE,  NO_GRV, NO_BSLS, NO_HASH, NO_ASTR,                                     _______, _______, _______, _______, _______, _______,
      _______, NO_PERC, NO_CIRC, NO_AMPR, NOM_DLR,  NO_EQL,                                     _______, _______, _______, _______, _______, _______,
      _______, NO_PLUS,NOM_TILD,  NOM_AT, NO_UNDS, NO_MINS, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,

      _______, _______, _______, _______, _______,                                                       _______, _______, _______, _______, _______
    ),

/*
 * Number
 */
    [_NUM] = LAYOUT_split_3x6_5_hlc(
      _______, _______, KC_KP_7, KC_KP_8, KC_KP_9, NO_ASTR,                                     _______, _______, _______, _______, _______, _______,
      _______, NO_PERC, KC_KP_4, KC_KP_5, KC_KP_6,  NO_EQL,                                     _______, _______, _______, _______, _______, _______,
      _______, NO_PLUS, KC_KP_1, KC_KP_2, KC_KP_3, NO_MINS, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, KC_KP_0, _______, _______, _______, _______, _______, _______, _______,

      _______, _______, _______, _______, _______,                                                       _______, _______, _______, _______, _______
    ),

/*
 * International Layer
 */
    [_INTL] = LAYOUT_split_3x6_5_hlc(
      _______, _______, _______, _______, _______, _______,                                     NO_SECT, _______, _______, _______, NO_ARNG, _______,
      _______, _______, _______, _______, _______, _______,                                     _______, NO_PND , NO_EURO, NO_OSTR,  NO_AE , _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,

      _______, _______, _______, _______, _______,                                                       _______, _______, _______, _______, _______
    ),

/*
 * Function Layer: Function keys
 */
    [_FUNCTION] = LAYOUT_split_3x6_5_hlc(
      _______,  KC_F12,  KC_F7,   KC_F8 ,  KC_F9 , _______,                                     _______, _______, _______, _______, _______, _______,
      _______,  KC_F11,  KC_F4 ,  KC_F5 ,  KC_F6 , _______,                                     _______, _______, _______, _______, _______, _______,
      _______,  KC_F10,  KC_F1 ,  KC_F2 ,  KC_F3 , _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
     _______, _______,  _______, _______, _______,                                                       _______, _______, _______, _______, _______
    ),

/*
 * Adjust Layer: Default layer settings, RGB
 */
    [_ADJUST] = LAYOUT_split_3x6_5_hlc(
      _______, _______, _______, COLEMAK, _______, _______,                                    _______, _______, _______, _______, _______, _______,
      _______, _______, _______, QWERTY , _______, _______,                                    RM_TOGG, RM_SATU, RM_HUEU, RM_VALU, RM_NEXT, _______,
      _______, _______, _______, _______, _______, _______,_______, _______, _______, _______, _______, RM_SATD, RM_HUED, RM_VALD, RM_PREV, _______,
                                 _______, _______, _______,_______, _______, _______, _______, _______, _______, _______,
     _______, _______,  _______, _______, _______,                                                      _______, _______, _______, _______, _______
    ),

// /*
//  * Halcyon Layer template
//  *
//  * ,-------------------------------------------.                              ,-------------------------------------------.
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
//  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        `----------------------------------'  `----------------------------------'
//  * ,-----------------------------------.                                              ,-----------------------------------.
//  * |      |      |       |      |      |                                              |      |      |       |      |      |
//  * `-----------------------------------'                                              `-----------------------------------'
//  */
//     [_LAYERINDEX] = LAYOUT_split_3x6_5_hlc(
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//
//       _______, _______, _______, _______, _______,                                                       _______, _______, _______, _______, _______
//     ),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU),  ENCODER_CCW_CW(KC_VOLD, KC_VOLU),  ENCODER_CCW_CW(KC_PGUP, KC_PGDN),  ENCODER_CCW_CW(KC_PGUP, KC_PGDN)  },
    [1] = { ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______)  },
    [2] = { ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______)  },
    [3] = { ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______)  },
    [4] = { ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______)  },
    [5] = { ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______)  },
    [6] = { ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______)  },
    [7] = { ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______)  }
};
#endif

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    // reduce the movement speed of the cursor
    mouse_report.x = mouse_report.x / TRACKPAD_SENSITIVITY_DIVISOR;
    mouse_report.y = mouse_report.y / TRACKPAD_SENSITIVITY_DIVISOR;
    return mouse_report;
}

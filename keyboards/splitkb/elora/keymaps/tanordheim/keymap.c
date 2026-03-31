// Copyright 2024 splitkb.com (support@splitkb.com)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "keymap_norwegian.h"
#include "sendstring_norwegian.h"

enum layers {
    _QWERTY = 0,
    _NAV,
    _SYM,
    _NUM,
    _INTL,
    _FUNCTION,
    _ADJUST,
};

// Aliases for readability
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
const key_override_t semicolon_shift_override    = ko_make_basic(MOD_MASK_SHIFT, NO_SCLN, NO_COLN);
const key_override_t dblquote_shift_override     = ko_make_basic(MOD_MASK_SHIFT, NO_DQUO, NOM_QUOT);
const key_override_t comma_shift_override        = ko_make_basic(MOD_MASK_SHIFT, NO_COMM, NOM_LABK);
const key_override_t dot_shift_override          = ko_make_basic(MOD_MASK_SHIFT, NO_DOT,  NOM_RABK);
const key_override_t slash_shift_override        = ko_make_basic(MOD_MASK_SHIFT, NO_SLSH, NOM_BSLS);
const key_override_t questionmark_shift_override = ko_make_basic(MOD_MASK_SHIFT, NO_QUES, NO_EXLM);
const key_override_t *key_overrides[] = {
    &semicolon_shift_override,
    &dblquote_shift_override,
    &comma_shift_override,
    &dot_shift_override,
    &slash_shift_override,
    &questionmark_shift_override,
};

// Combos
const uint16_t PROGMEM lprn_combo[] = {NO_E, NO_R, COMBO_END};
const uint16_t PROGMEM rprn_combo[] = {NO_U, NO_I, COMBO_END};
const uint16_t PROGMEM lcbr_combo[] = {NO_D, NO_F, COMBO_END};
const uint16_t PROGMEM rcbr_combo[] = {NO_H, NO_J, COMBO_END};
const uint16_t PROGMEM lbrc_combo[] = {NO_C, NO_V, COMBO_END};
const uint16_t PROGMEM rbrc_combo[] = {NO_M, NO_COMM, COMBO_END};

enum combo_events {
    LPRN,
    RPRN,
    LCBR,
    RCBR,
    LBRC,
    RBRC,
};

combo_t key_combos[] = {
    [LPRN] = COMBO(lprn_combo, NO_LPRN),
    [RPRN] = COMBO(rprn_combo, NO_RPRN),
    [LCBR] = COMBO(lcbr_combo, NOM_LCBR),
    [RCBR] = COMBO(rcbr_combo, NOM_RCBR),
    [LBRC] = COMBO(lbrc_combo, NOM_LBRC),
    [RBRC] = COMBO(rbrc_combo, NOM_RBRC),
};

// OLED
#ifdef OLED_ENABLE
static void render_layer_state(void) {
    switch (get_highest_layer(layer_state | default_layer_state)) {
        case _QWERTY:   oled_write_P(PSTR("QWRT"), false); break;
        case _NAV:      oled_write_P(PSTR("NAV "), false); break;
        case _SYM:      oled_write_P(PSTR("SYM "), false); break;
        case _NUM:      oled_write_P(PSTR("NUM "), false); break;
        case _INTL:     oled_write_P(PSTR("INTL"), false); break;
        case _FUNCTION: oled_write_P(PSTR("FUNC"), false); break;
        case _ADJUST:   oled_write_P(PSTR("ADJ "), false); break;
        default:        oled_write_P(PSTR("??? "), false); break;
    }
}

static void render_mod_state(void) {
    uint8_t mods = get_mods() | get_oneshot_mods();
    oled_write_P(mods & MOD_MASK_SHIFT ? PSTR("SFT ") : PSTR("    "), false);
    oled_write_P(mods & MOD_MASK_CTRL  ? PSTR("CTL ") : PSTR("    "), false);
    oled_write_P(mods & MOD_MASK_ALT   ? PSTR("ALT ") : PSTR("    "), false);
    oled_write_P(mods & MOD_MASK_GUI   ? PSTR("GUI ") : PSTR("    "), false);
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        render_layer_state();
        render_mod_state();
        return false;
    }
    return true;
}
#endif

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base Layer: QWERTY
 */
    [_QWERTY] = LAYOUT_myr(
     KC_F13 ,  NO_1 ,  NO_2   ,  NO_3  ,   NO_4 ,   NO_5 ,          _______,     _______,           NO_6 ,  NO_7 ,  NO_8 ,   NO_9 ,  NO_0 , _______,
     KC_TAB  , NO_Q ,  NO_W   ,  NO_E  ,   NO_R ,   NO_T ,          _______,     _______,           NO_Y ,  NO_U ,  NO_I ,   NO_O ,  NO_P , KC_BSPC,
     KC_LSFT , NO_A ,  NO_S   ,  NO_D  ,   NO_F ,   NO_G ,          _______,     _______,           NO_H ,  NO_J ,  NO_K ,   NO_L ,NO_SCLN, NO_DQUO,
     KC_LCTL , NO_Z ,  NO_X   ,  NO_C  ,   NO_V ,   NO_B ,   DPRV  ,KC_CAPS,     FKEYS  ,  DNXT  ,  NO_N ,  NO_M ,NO_COMM, NO_DOT ,NO_SLSH, NO_QUES,
                                 KC_LALT, KC_LGUI, ESC_NAV, KC_SPC ,  INTL  ,    ADJUST , KC_ENT ,  SYM  ,  NUM  , KC_APP,

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
 * Sym Layer: Numbers and symbols
 */
    [_SYM] = LAYOUT_myr(
     _______, _______, _______, _______, _______, _______,           _______,     _______,           _______, _______, _______, _______, _______, _______,
     _______,NOM_PIPE,  NO_GRV, NO_BSLS, NO_HASH, NO_ASTR,           _______,     _______,           _______, _______, _______, _______, _______, _______,
     _______, NO_PERC, NO_CIRC, NO_AMPR, NOM_DLR,  NO_EQL,           _______,     _______,           _______, _______, _______, _______, _______, _______,
     _______, NO_PLUS,NOM_TILD,  NOM_AT, NO_UNDS, NO_MINS, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,

     _______, _______, _______, _______,           _______,                    _______, _______, _______, _______,           _______
    ),

/*
 * Number
 */
    [_NUM] = LAYOUT_myr(
     _______, _______, _______, _______, _______, _______,           _______,     _______,           _______, _______, _______, _______, _______, _______,
     _______, _______, KC_KP_7, KC_KP_8, KC_KP_9, NO_ASTR,           _______,     _______,           _______, _______, _______, _______, _______, _______,
     _______, NO_PERC, KC_KP_4, KC_KP_5, KC_KP_6,  NO_EQL,           _______,     _______,           _______, _______, _______, _______, _______, _______,
     _______, NO_PLUS, KC_KP_1, KC_KP_2, KC_KP_3, NO_MINS, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                _______, _______, KC_KP_0, _______, _______, _______, _______, _______, _______, _______,

     _______, _______, _______, _______,           _______,                    _______, _______, _______, _______,           _______
    ),

/*
 * International Layer
 */
    [_INTL] = LAYOUT_myr(
     _______, _______, _______, _______, _______, _______,           _______,     _______,           _______, _______, _______, _______, _______, _______,
     _______, _______, _______, _______, _______, _______,           _______,     _______,           NO_SECT, _______, _______, _______, NO_ARNG, _______,
     _______, _______, _______, _______, _______, _______,           _______,     _______,           _______, NO_PND , NO_EURO, NO_OSTR,  NO_AE , _______,
     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,

     _______, _______, _______, _______,           _______,                    _______, _______, _______, _______,           _______
    ),

/*
 * Function Layer: Function keys
 */
    [_FUNCTION] = LAYOUT_myr(
     _______, _______, _______, _______, _______, _______,           _______,     _______,           _______, _______, _______, _______, _______, _______,
     _______,  KC_F12,  KC_F7 ,  KC_F8 ,  KC_F9 , _______,           _______,     _______,           _______, _______, _______, _______, _______, _______,
     _______,  KC_F11,  KC_F4 ,  KC_F5 ,  KC_F6 , _______,           _______,     _______,           _______, _______, _______, _______, _______, _______,
     _______,  KC_F10,  KC_F1 ,  KC_F2 ,  KC_F3 , _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,

     _______, _______, _______, _______,           _______,                    _______, _______, _______, _______,           _______
    ),

/*
 * Adjust Layer: Default layer settings, RGB
 */
    [_ADJUST] = LAYOUT_myr(
     _______, _______, _______, _______, _______, _______,           _______,     _______,           _______, _______, _______, _______, _______, _______,
     _______, _______, _______, _______, _______, _______,           _______,     _______,           _______, _______, _______, _______, _______, _______,
     _______, _______, _______, _______, _______, _______,           _______,     _______,           RM_TOGG, RM_SATU, RM_HUEU, RM_VALU, RM_NEXT, _______,
     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RM_SATD, RM_HUED, RM_VALD, RM_PREV, _______,
                                _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,

     _______, _______, _______, _______,           _______,                    _______, _______, _______, _______,           _______
    ),
};

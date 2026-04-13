#include QMK_KEYBOARD_H
#include "keymap_norwegian.h"

enum layers {
    _PROG = 0,
    _GAMING,
    _NAV,
    _SYM_MAC,
    _SYM_LINUX,
    _FUN,
    _ADJUST,
};

enum custom_keycodes {
    CK_SYM = SAFE_RANGE,
    CK_PIPE,  // tap=|  shift=` (dead grave + space)
    CK_BSLS,  // tap=\  shift=´ (dead acute + space)
    CK_TILD,  // tap=~ (dead tilde + space)  shift=*
    CK_GRV,   // ` (dead grave + space)
};

// macOS-specific aliases (keys that differ from Linux/Windows Norwegian)
#define NOM_TILD  ALGR(KC_RBRC)
#define NOM_PIPE  ALGR(NO_7)
#define NOM_APOS  KC_NUBS            // ' on macOS
#define NOM_LABK  KC_GRV             // < on macOS
#define NOM_RABK  S(KC_GRV)          // > on macOS
#define NOM_AT    KC_NUHS            // @ on macOS
#define NOM_BSLS  S(ALGR(NO_7))     // backslash on macOS
#define NOM_DLR   KC_DLR
#define NOM_LBRC  ALGR(NO_8)
#define NOM_RBRC  ALGR(NO_9)
#define NOM_LCBR  S(ALGR(NO_8))
#define NOM_RCBR  S(ALGR(NO_9))

static bool is_macos = true;

// Layer key aliases
#define NAV     MO(_NAV)
#define FUN     MO(_FUN)
#define ADJST   MO(_ADJUST)

// Combos (programming layer only)
const uint16_t PROGMEM lprn_combo[] = {NO_E, NO_R, COMBO_END};
const uint16_t PROGMEM rprn_combo[] = {NO_U, NO_I, COMBO_END};
const uint16_t PROGMEM lcbr_combo[] = {NO_D, NO_F, COMBO_END};
const uint16_t PROGMEM rcbr_combo[] = {NO_J, NO_K, COMBO_END};
const uint16_t PROGMEM lbrc_combo[] = {NO_C, NO_V, COMBO_END};
const uint16_t PROGMEM rbrc_combo[] = {NO_M, NO_COMM, COMBO_END};

enum combo_events {
    CMB_LPRN,
    CMB_RPRN,
    CMB_LCBR,
    CMB_RCBR,
    CMB_LBRC,
    CMB_RBRC,
};

combo_t key_combos[] = {
    [CMB_LPRN] = COMBO(lprn_combo, NO_LPRN),
    [CMB_RPRN] = COMBO(rprn_combo, NO_RPRN),
    [CMB_LCBR] = COMBO(lcbr_combo, NOM_LCBR),
    [CMB_RCBR] = COMBO(rcbr_combo, NOM_RCBR),
    [CMB_LBRC] = COMBO(lbrc_combo, NOM_LBRC),
    [CMB_RBRC] = COMBO(rbrc_combo, NOM_RBRC),
};

bool combo_should_trigger(uint16_t combo_index, combo_t *combo, uint16_t keycode, keyrecord_t *record) {
    return layer_state_is(_PROG);
}

// Key overrides (programming layer only)
const key_override_t scln_override = ko_make_with_layers(MOD_MASK_SHIFT, NO_SCLN, NO_COLN, 1 << _PROG);
const key_override_t dquo_override = ko_make_with_layers(MOD_MASK_SHIFT, NO_DQUO, NOM_APOS, 1 << _PROG);
const key_override_t at_override   = ko_make_with_layers(MOD_MASK_SHIFT, NOM_AT, NO_HASH, 1 << _PROG);
const key_override_t dash_override = ko_make_with_layers(MOD_MASK_SHIFT, NO_MINS, NO_UNDS, 1 << _PROG);
const key_override_t slsh_override = ko_make_with_layers(MOD_MASK_SHIFT, NO_SLSH, NO_AMPR, 1 << _PROG);
const key_override_t comm_override = ko_make_with_layers(MOD_MASK_SHIFT, NO_COMM, NOM_LABK, 1 << _PROG);
const key_override_t dot_override  = ko_make_with_layers(MOD_MASK_SHIFT, NO_DOT, NOM_RABK, 1 << _PROG);
const key_override_t ques_override = ko_make_with_layers(MOD_MASK_SHIFT, NO_QUES, NO_EXLM, 1 << _PROG);
const key_override_t *key_overrides[] = {
    &scln_override,
    &dquo_override,
    &at_override,
    &dash_override,
    &slsh_override,
    &comm_override,
    &dot_override,
    &ques_override,
    NULL,
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /*
     * Layer 0: Programming (macOS)
     *
     * ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────────┐
     * │ |`  │ 1!  │ 2"  │ 3#  │ 4¤  │ 5%  │ 6&  │ 7/  │ 8(  │ 9)  │ 0=  │ +?  │ \´  │  BKSP   │
     * ├─────┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──────┤
     * │  TAB   │ Q   │ W   │ E   │ R   │ T   │ Y   │ U   │ I   │ O   │ P   │ ~*  │ ?!  │      │
     * ├────────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┘  ENT │
     * │  ESC    │ A   │ S   │ D   │ F   │ G   │ H   │ J   │ K   │ L   │ ;:  │ "'  │ @#       │
     * ├────┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴──────────┤
     * │LSFT│ -_  │ Z   │ X   │ C   │ V   │ B   │ N   │ M   │ ,<  │ .>  │ /&  │    RSFT       │
     * ├────┼─────┼─────┼─────────────────────────────┼─────┼─────┼─────┼─────────────────────┤
     * │LCTL│LGUI │LALT │            SPACE             │ SYM │ NAV │ FUN │         ADJ           │
     * └────┴─────┴─────┴─────────────────────────────┴─────┴─────┴─────┴─────────────────────┘
     *
     * Combos:  E+R → (   U+I → )   D+F → {   J+K → }   C+V → [   M+, → ]
     */
    [_PROG] = LAYOUT_iso_62(
        CK_PIPE, NO_1,    NO_2,    NO_3,    NO_4,    NO_5,    NO_6,    NO_7,    NO_8,    NO_9,    NO_0,    NO_PLUS, CK_BSLS,  KC_BSPC,
        KC_TAB,  NO_Q,    NO_W,    NO_E,    NO_R,    NO_T,    NO_Y,    NO_U,    NO_I,    NO_O,    NO_P,    CK_TILD, NO_QUES,
        KC_ESC,  NO_A,    NO_S,    NO_D,    NO_F,    NO_G,    NO_H,    NO_J,    NO_K,    NO_L,    NO_SCLN, NO_DQUO, NOM_AT,   KC_ENT,
        KC_LSFT, NO_MINS, NO_Z,    NO_X,    NO_C,    NO_V,    NO_B,    NO_N,    NO_M,    NO_COMM, NO_DOT,  NO_SLSH,           KC_RSFT,
        KC_LCTL, KC_LALT, KC_LGUI,                            KC_SPC,                             CK_SYM,  NAV,     FUN,       ADJST),

    /*
     * Layer 1: Gaming (Linux/Windows)
     * Standard Norwegian ISO, no overrides or combos.
     * Number row matches programming layer.
     */
    [_GAMING] = LAYOUT_iso_62(
        NO_PIPE, NO_1,    NO_2,    NO_3,    NO_4,    NO_5,    NO_6,    NO_7,    NO_8,    NO_9,    NO_0,    NO_PLUS, NO_BSLS,  KC_BSPC,
        KC_TAB,  NO_Q,    NO_W,    NO_E,    NO_R,    NO_T,    NO_Y,    NO_U,    NO_I,    NO_O,    NO_P,    NO_ARNG, NO_DIAE,
        KC_ESC,  NO_A,    NO_S,    NO_D,    NO_F,    NO_G,    NO_H,    NO_J,    NO_K,    NO_L,    NO_OSTR, NO_AE,   NO_QUOT,  KC_ENT,
        KC_LSFT, NO_LABK, NO_Z,    NO_X,    NO_C,    NO_V,    NO_B,    NO_N,    NO_M,    NO_COMM, NO_DOT,  NO_MINS,           KC_RSFT,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             CK_SYM,  NAV,     FUN,       ADJST),

    /*
     * Layer 2: NAV
     * Left hand: navigation. Right hand: home row mods.
     */
    [_NAV] = LAYOUT_iso_62(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        _______, KC_DEL,  KC_PGUP, KC_UP,   KC_PGDN, KC_INS,  KC_AGIN, KC_PSTE, KC_COPY, KC_CUT,  KC_UNDO, XXXXXXX, XXXXXXX,
        XXXXXXX, KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,  XXXXXXX, KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI, XXXXXXX, XXXXXXX, XXXXXXX,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          _______,
        _______, _______, _______,                            _______,                             _______, _______, _______,   _______),

    /*
     * Layer 3: SYM_MAC (macOS symbols using NOM_* aliases)
     * Callum-style brackets: open left, close right.
     * ^ and $ on F and J for Vim navigation.
     */
    [_SYM_MAC] = LAYOUT_iso_62(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_DEL,
        _______, NOM_LBRC,NOM_LCBR,NO_LPRN, NOM_LABK,NO_HASH, NO_ASTR, NOM_RABK,NO_RPRN, NOM_RCBR,NOM_RBRC,NO_ARNG, XXXXXXX,
        XXXXXXX, NO_MINS, NO_PLUS, NO_EQL,  NO_CIRC, NO_AMPR, NOM_PIPE,NOM_DLR, NO_PERC, NOM_AT,  NO_OSTR, NO_AE,   NOM_BSLS, XXXXXXX,
        _______, CK_GRV,  NOM_TILD,NO_EXLM, NO_UNDS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,           _______,
        _______, _______, _______,                            _______,                             _______, _______, _______,   _______),

    /*
     * Layer 4: SYM_LINUX (Linux/Windows symbols using standard NO_* keycodes)
     * Same layout as SYM_MAC but with Linux-compatible keycodes.
     */
    [_SYM_LINUX] = LAYOUT_iso_62(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_DEL,
        _______, NO_LBRC, NO_LCBR, NO_LPRN, NO_LABK, NO_HASH, NO_ASTR, NO_RABK, NO_RPRN, NO_RCBR, NO_RBRC, NO_ARNG, XXXXXXX,
        XXXXXXX, NO_MINS, NO_PLUS, NO_EQL,  NO_CIRC, NO_AMPR, NO_PIPE, NO_DLR,  NO_PERC, NO_AT,   NO_OSTR, NO_AE,   NO_BSLS,  XXXXXXX,
        _______, NO_GRV,  NO_TILD, NO_EXLM, NO_UNDS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,           _______,
        _______, _______, _______,                            _______,                             _______, _______, _______,   _______),

    /*
     * Layer 5: FUN
     * F-keys on number row. Media on left hand. Right hand home row mods.
     */
    [_FUN] = LAYOUT_iso_62(
        XXXXXXX, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  XXXXXXX,
        _______, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, KC_MUTE, KC_MPLY, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI, XXXXXXX, XXXXXXX, XXXXXXX,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          _______,
        _______, _______, _______,                            _______,                             _______, _______, _______,   _______),

    /*
     * Layer 6: ADJUST
     * Bootloader and EEPROM clear on corners. RGB controls on right hand.
     */
    [_ADJUST] = LAYOUT_iso_62(
        QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, EE_CLR,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RM_TOGG, RM_SATU, RM_HUEU, RM_VALU, RM_NEXT, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RM_SATD, RM_HUED, RM_VALD, RM_PREV, XXXXXXX, XXXXXXX, XXXXXXX,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          _______,
        _______, _______, _______,                            _______,                             _______, _______, _______,   _______),
};
// clang-format on

// DIP switch: toggle between programming (macOS) and gaming (Linux)
bool dip_switch_update_user(uint8_t index, bool active) {
    if (index == 0) {
        is_macos = !active;
    }
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode == CK_SYM) {
        if (record->event.pressed) {
            layer_on(is_macos ? _SYM_MAC : _SYM_LINUX);
        } else {
            layer_off(_SYM_MAC);
            layer_off(_SYM_LINUX);
        }
        return false;
    }

    if (!record->event.pressed) return true;

    uint8_t mods = get_mods();
    bool shifted = mods & MOD_MASK_SHIFT;

    switch (keycode) {
        case CK_PIPE: // tap=| shift=`
            if (shifted) {
                del_mods(MOD_MASK_SHIFT);
                tap_code16(S(KC_EQL));
                tap_code(KC_SPC);
                set_mods(mods);
            } else {
                tap_code16(NOM_PIPE);
            }
            return false;

        case CK_BSLS: // tap=\ shift=´
            if (shifted) {
                del_mods(MOD_MASK_SHIFT);
                tap_code(KC_EQL);
                tap_code(KC_SPC);
                set_mods(mods);
            } else {
                tap_code16(NOM_BSLS);
            }
            return false;

        case CK_TILD: // tap=~ shift=*
            if (shifted) {
                tap_code16(NO_ASTR);
            } else {
                del_mods(MOD_MASK_SHIFT);
                tap_code16(NOM_TILD);
                tap_code(KC_SPC);
                set_mods(mods);
            }
            return false;

        case CK_GRV: // ` (dead grave + space)
            del_mods(MOD_MASK_SHIFT);
            tap_code16(S(KC_EQL));
            tap_code(KC_SPC);
            set_mods(mods);
            return false;
    }
    return true;
}

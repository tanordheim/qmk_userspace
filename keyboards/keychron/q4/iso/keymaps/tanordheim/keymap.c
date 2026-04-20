#include QMK_KEYBOARD_H
#include "keymap_norwegian.h"

enum layers {
    _MAC = 0,
    _LNX,
    _GAMING,
    _NAV,
    _SYM_MAC,
    _SYM_LNX,
    _INTL_MAC,
    _INTL_LNX,
    _FUN,
    _ADJ,
    _GAME_NAV,
};

enum custom_keycodes {
    CK_GRV = SAFE_RANGE, // ` (dead+space), shift=~ (dead+space)
    CK_TILD,             // ~ (dead+space)
    CK_CARET,            // ^ (dead+space)
    CK_GAME,             // gaming mode toggle
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
#define NOM_EURO  S(ALGR(NO_4))

// Dead key keycodes (same on both OSes)
#define DEAD_GRV   S(KC_EQL)
#define DEAD_TILD  ALGR(KC_RBRC)
#define DEAD_CARET S(KC_RBRC)

static bool dip_is_mac = true;
static bool gaming_active = false;

// Layer key aliases
#define NAV_ESC  LT(_NAV, KC_ESC)
#define CTL_A    LCTL_T(NO_A)
#define CTL_BSLS RCTL_T(KC_F24)
#define SYM_MAC  MO(_SYM_MAC)
#define SYM_LNX  MO(_SYM_LNX)
#define INTL_MAC MO(_INTL_MAC)
#define INTL_LNX MO(_INTL_LNX)
#define FUN      MO(_FUN)
#define ADJ      MO(_ADJ)
#define GAME_NAV MO(_GAME_NAV)

// Key overrides
#define KO_NEG (MOD_MASK_CTRL | MOD_MASK_ALT | MOD_MASK_GUI)
#define KO_MAC (1 << _MAC)
#define KO_LNX (1 << _LNX)
#define KO_CODING (KO_MAC | KO_LNX)

// Shared overrides (same keycodes on both OSes)
const key_override_t ko_7_ampr    = ko_make_with_layers_negmods_and_options(MOD_MASK_SHIFT, NO_7,     NO_AMPR, KO_CODING, KO_NEG, 0);
const key_override_t ko_8_astr    = ko_make_with_layers_negmods_and_options(MOD_MASK_SHIFT, NO_8,     NO_ASTR, KO_CODING, KO_NEG, 0);
const key_override_t ko_9_lprn    = ko_make_with_layers_negmods_and_options(MOD_MASK_SHIFT, NO_9,     NO_LPRN, KO_CODING, KO_NEG, 0);
const key_override_t ko_0_rprn    = ko_make_with_layers_negmods_and_options(MOD_MASK_SHIFT, NO_0,     NO_RPRN, KO_CODING, KO_NEG, 0);
const key_override_t ko_min_und   = ko_make_with_layers_negmods_and_options(MOD_MASK_SHIFT, NO_MINS,  NO_UNDS, KO_CODING, KO_NEG, 0);
const key_override_t ko_eql_pls   = ko_make_with_layers_negmods_and_options(MOD_MASK_SHIFT, NO_EQL,   NO_PLUS, KO_CODING, KO_NEG, 0);
const key_override_t ko_amp_ast   = ko_make_with_layers_negmods_and_options(MOD_MASK_SHIFT, NO_AMPR,  NO_ASTR, KO_CODING, KO_NEG, 0);
const key_override_t ko_sl_ques   = ko_make_with_layers_negmods_and_options(MOD_MASK_SHIFT, NO_SLSH,  NO_QUES, KO_CODING, KO_NEG, 0);
const key_override_t ko_scln_coln = ko_make_with_layers_negmods_and_options(MOD_MASK_SHIFT, NO_SCLN,  NO_COLN, KO_CODING, KO_NEG, 0);

// Mac-specific overrides
const key_override_t ko_m_2_at    = ko_make_with_layers_negmods_and_options(MOD_MASK_SHIFT, NO_2,     NOM_AT,    KO_MAC, KO_NEG, 0);
const key_override_t ko_m_4_dlr   = ko_make_with_layers_negmods_and_options(MOD_MASK_SHIFT, NO_4,     NOM_DLR,   KO_MAC, KO_NEG, 0);
const key_override_t ko_m_comm_lt = ko_make_with_layers_negmods_and_options(MOD_MASK_SHIFT, NO_COMM,  NOM_LABK,  KO_MAC, KO_NEG, 0);
const key_override_t ko_m_dot_gt  = ko_make_with_layers_negmods_and_options(MOD_MASK_SHIFT, NO_DOT,   NOM_RABK,  KO_MAC, KO_NEG, 0);
const key_override_t ko_m_dquo_qt = ko_make_with_layers_negmods_and_options(MOD_MASK_SHIFT, NO_DQUO,  NOM_QUOT,  KO_MAC, KO_NEG, 0);
const key_override_t ko_m_at_exl  = ko_make_with_layers_negmods_and_options(MOD_MASK_SHIFT, NOM_AT,   NO_EXLM,   KO_MAC, KO_NEG, 0);

// Linux-specific overrides
const key_override_t ko_l_2_at    = ko_make_with_layers_negmods_and_options(MOD_MASK_SHIFT, NO_2,     NO_AT,     KO_LNX, KO_NEG, 0);
const key_override_t ko_l_4_dlr   = ko_make_with_layers_negmods_and_options(MOD_MASK_SHIFT, NO_4,     NO_DLR,    KO_LNX, KO_NEG, 0);
const key_override_t ko_l_comm_lt = ko_make_with_layers_negmods_and_options(MOD_MASK_SHIFT, NO_COMM,  NO_LABK,   KO_LNX, KO_NEG, 0);
const key_override_t ko_l_dot_gt  = ko_make_with_layers_negmods_and_options(MOD_MASK_SHIFT, NO_DOT,   NO_RABK,   KO_LNX, KO_NEG, 0);
const key_override_t ko_l_dquo_qt = ko_make_with_layers_negmods_and_options(MOD_MASK_SHIFT, NO_DQUO,  NO_QUOT,   KO_LNX, KO_NEG, 0);
const key_override_t ko_l_at_exl  = ko_make_with_layers_negmods_and_options(MOD_MASK_SHIFT, NO_AT,    NO_EXLM,   KO_LNX, KO_NEG, 0);

// Shift+Backspace = Ctrl+Alt+D (Claude dictate)
const key_override_t ko_bspc_dict = ko_make_with_layers_negmods_and_options(MOD_MASK_SHIFT, KC_BSPC, LCTL(LALT(KC_D)), KO_CODING, KO_NEG, 0);

const key_override_t *key_overrides[] = {
    &ko_7_ampr,    &ko_8_astr,    &ko_9_lprn,    &ko_0_rprn,
    &ko_min_und,   &ko_eql_pls,   &ko_amp_ast,   &ko_sl_ques,   &ko_scln_coln,
    &ko_m_2_at,    &ko_m_4_dlr,   &ko_m_comm_lt, &ko_m_dot_gt,  &ko_m_dquo_qt, &ko_m_at_exl,
    &ko_l_2_at,    &ko_l_4_dlr,   &ko_l_comm_lt, &ko_l_dot_gt,  &ko_l_dquo_qt, &ko_l_at_exl,
    &ko_bspc_dict,
    NULL,
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_MAC] = LAYOUT_iso_62(
        CK_GRV,  NO_1,    NO_2,    NO_3,    NO_4,    NO_5,    NO_6,    NO_7,    NO_8,    NO_9,    NO_0,    NO_MINS, NO_EQL,  KC_BSPC,
        KC_TAB,  NO_Q,    NO_W,    NO_E,    NO_R,    NO_T,    NO_Y,    NO_U,    NO_I,    NO_O,    NO_P,    NO_AMPR, NOM_AT,
        NAV_ESC, CTL_A,   NO_S,    NO_D,    NO_F,    NO_G,    NO_H,    NO_J,    NO_K,    NO_L,    NO_SCLN, NO_DQUO, CTL_BSLS,KC_ENT,
        KC_LSFT, NO_HASH, NO_Z,    NO_X,    NO_C,    NO_V,    NO_B,    NO_N,    NO_M,    NO_COMM, NO_DOT,  NO_SLSH,          KC_RSFT,
        KC_LCTL, KC_LALT, KC_LGUI,                            KC_SPC,                             SYM_MAC, INTL_MAC,FUN,     ADJ),

    [_LNX] = LAYOUT_iso_62(
        CK_GRV,  NO_1,    NO_2,    NO_3,    NO_4,    NO_5,    NO_6,    NO_7,    NO_8,    NO_9,    NO_0,    NO_MINS, NO_EQL,  KC_BSPC,
        KC_TAB,  NO_Q,    NO_W,    NO_E,    NO_R,    NO_T,    NO_Y,    NO_U,    NO_I,    NO_O,    NO_P,    NO_AMPR, NO_AT,
        NAV_ESC, CTL_A,   NO_S,    NO_D,    NO_F,    NO_G,    NO_H,    NO_J,    NO_K,    NO_L,    NO_SCLN, NO_DQUO, CTL_BSLS,KC_ENT,
        KC_LSFT, NO_HASH, NO_Z,    NO_X,    NO_C,    NO_V,    NO_B,    NO_N,    NO_M,    NO_COMM, NO_DOT,  NO_SLSH,          KC_RSFT,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             SYM_LNX, INTL_LNX,FUN,     ADJ),

    [_GAMING] = LAYOUT_iso_62(
        NO_PIPE, NO_1,    NO_2,    NO_3,    NO_4,    NO_5,    NO_6,    NO_7,    NO_8,    NO_9,    NO_0,    NO_PLUS, NO_BSLS, KC_BSPC,
        KC_TAB,  NO_Q,    NO_W,    NO_E,    NO_R,    NO_T,    NO_Y,    NO_U,    NO_I,    NO_O,    NO_P,    NO_ARNG, NO_DIAE,
        KC_ESC,  NO_A,    NO_S,    NO_D,    NO_F,    NO_G,    NO_H,    NO_J,    NO_K,    NO_L,    NO_OSTR, NO_AE,   NO_QUOT, KC_ENT,
        KC_LSFT, NO_LABK, NO_Z,    NO_X,    NO_C,    NO_V,    NO_B,    NO_N,    NO_M,    NO_COMM, NO_DOT,  NO_MINS,          KC_RSFT,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             GAME_NAV,_______, FUN,     ADJ),

    [_NAV] = LAYOUT_iso_62(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, KC_DEL,  KC_PGUP, KC_UP,   KC_PGDN, KC_INS,  _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_DEL,  KC_BSPC, _______, _______,
        _______, _______, KC_UNDO, KC_MUTE, KC_MPLY, KC_VOLU, KC_VOLD, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______,          _______,
        _______, _______, _______,                            _______,                             _______, _______, _______, _______),

    [_SYM_MAC] = LAYOUT_iso_62(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, NO_LPRN, NO_RPRN, NO_LBRC, NO_RBRC, _______, _______, CK_GRV,  NO_HASH, NO_ASTR, NOM_AT,  NO_PERC, _______,
        _______, CK_CARET,NO_MINS, NO_PLUS, NO_EQL,  _______, _______, NOM_PIPE,NO_DQUO, CK_TILD, NO_AMPR, NOM_BSLS,NOM_DLR, _______,
        _______, _______, NOM_LCBR,NOM_RCBR,NOM_LABK,_______, _______, NOM_RABK,_______, _______, _______, _______,          _______,
        _______, _______, _______,                            _______,                             _______, _______, _______, _______),

    [_SYM_LNX] = LAYOUT_iso_62(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, NO_LPRN, NO_RPRN, NO_LBRC, NO_RBRC, _______, _______, CK_GRV,  NO_HASH, NO_ASTR, NO_AT,   NO_PERC, _______,
        _______, CK_CARET,NO_MINS, NO_PLUS, NO_EQL,  _______, _______, NO_PIPE, NO_DQUO, CK_TILD, NO_AMPR, NO_BSLS, NO_DLR,  _______,
        _______, _______, NO_LCBR, NO_RCBR, NO_LABK, _______, _______, NO_RABK, _______, _______, _______, _______,          _______,
        _______, _______, _______,                            _______,                             _______, _______, _______, _______),

    [_INTL_MAC] = LAYOUT_iso_62(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, NOM_SECT,_______, _______, _______, _______, _______, _______, _______, _______, _______, NO_ARNG, _______,
        _______, NO_PND,  _______, NOM_EURO,_______, _______, _______, _______, _______, _______, NO_OSTR, NO_AE,   _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______,                            _______,                             _______, _______, _______, _______),

    [_INTL_LNX] = LAYOUT_iso_62(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, NO_SECT, _______, _______, _______, _______, _______, _______, _______, _______, _______, NO_ARNG, _______,
        _______, NO_PND,  _______, NO_EURO, _______, _______, _______, _______, _______, _______, NO_OSTR, NO_AE,   _______, _______,
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

    [_GAME_NAV] = LAYOUT_iso_62(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, KC_UP,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
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
        dip_is_mac = !active;
        if (!gaming_active) {
            set_single_persistent_default_layer(dip_is_mac ? _MAC : _LNX);
        }
    }
    return false;
}

static bool shift_only(uint8_t mods) {
    return (mods & MOD_MASK_SHIFT) && !(mods & (MOD_MASK_CTRL | MOD_MASK_ALT | MOD_MASK_GUI));
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    uint8_t mods = get_mods();
    bool on_coding = (get_highest_layer(default_layer_state) != _GAMING);

    switch (keycode) {

        // --- Gaming mode toggle ---

        case CK_GAME:
            if (record->event.pressed) {
                gaming_active = !gaming_active;
                if (gaming_active) {
                    set_single_persistent_default_layer(_GAMING);
                } else {
                    set_single_persistent_default_layer(dip_is_mac ? _MAC : _LNX);
                }
            }
            return false;

        // --- Dead key number row overrides (same both OSes, coding layers only) ---

        case NO_6:
            if (record->event.pressed && shift_only(mods) && on_coding) {
                del_mods(MOD_MASK_SHIFT);
                tap_code16(DEAD_CARET);
                tap_code(KC_SPC);
                set_mods(mods);
                return false;
            }
            return true;

        case NO_HASH:
            if (record->event.pressed && shift_only(mods) && on_coding) {
                del_mods(MOD_MASK_SHIFT);
                tap_code16(DEAD_TILD);
                tap_code(KC_SPC);
                set_mods(mods);
                return false;
            }
            return true;

        // --- RCTL_T tap: backslash, shift=pipe ---

        case RCTL_T(KC_F24):
            if (record->tap.count > 0) {
                bool mac = (get_highest_layer(default_layer_state) == _MAC);
                if (record->event.pressed) {
                    if (mods & MOD_MASK_SHIFT) {
                        del_mods(MOD_MASK_SHIFT);
                        register_code16(mac ? NOM_PIPE : NO_PIPE);
                        set_mods(mods);
                    } else {
                        register_code16(mac ? NOM_BSLS : NO_BSLS);
                    }
                } else {
                    unregister_code16(NOM_BSLS);
                    unregister_code16(NO_BSLS);
                    unregister_code16(NOM_PIPE);
                    unregister_code16(NO_PIPE);
                }
                return false;
            }
            return true;

        // --- Dead key custom keycodes (same both OSes) ---

        case CK_GRV:
            if (!record->event.pressed) return false;
            if (mods & MOD_MASK_SHIFT) {
                del_mods(MOD_MASK_SHIFT);
                tap_code16(DEAD_TILD);
                tap_code(KC_SPC);
                set_mods(mods);
            } else {
                tap_code16(DEAD_GRV);
                tap_code(KC_SPC);
            }
            return false;

        case CK_TILD:
            if (!record->event.pressed) return false;
            del_mods(MOD_MASK_SHIFT);
            tap_code16(DEAD_TILD);
            tap_code(KC_SPC);
            set_mods(mods);
            return false;

        case CK_CARET:
            if (!record->event.pressed) return false;
            del_mods(MOD_MASK_SHIFT);
            tap_code16(DEAD_CARET);
            tap_code(KC_SPC);
            set_mods(mods);
            return false;
    }
    return true;
}

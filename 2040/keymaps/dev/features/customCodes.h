#pragma once

#include QMK_KEYBOARD_H

//
// ┌─────────────────────────────────────────────────┐
// │ LAYERS                                              │
// └─────────────────────────────────────────────────┘
//
// MOUSE should be last to always be the higher active whenever the cursor is moving
enum custom_layers { L_QWERTY = 0, L_COLEMAK, L_COLEMAK_DH, L_NAV, L_NUM, L_SYM, L_MATH, L_GREEK, L_ADJUST, L_MOUSE };

//
// ┌─────────────────────────────────────────────────┐
// │ CUSTOM KEYCODE                                      │
// └─────────────────────────────────────────────────┘
//
enum custom_keycodes {
// Leader
#ifdef VIA_ENABLE
    C_CHORD = USER00,
#else
    C_CHORD = SAFE_RANGE,
#endif
    // Repeat
    REPEAT,
    // Symbols requiring a dead key
    C_TILD,
    C_QUOT,
    C_DQUOT,
    C_GRV,
    // Wrapper for mod tap interception
    C_EURO,
    C_X,
    C_V,
    C_LDESK,
    C_RDESK,
    C_GA,
    C_GP,
    // Diacritics
    C_A_GRV,
    C_E_GRV,
    C_U_GRV,
    C_C_CED,
    // Sequences
    S_CENTER,
    S_CLIP_HISTORY,
    // Swappers
    SW_CTAB,
    SW_ATAB,
    // Combo layer
    ML_MOUSE,
    ML_ADJUST,
    // Switcher of layer (not timer)
    SWITCH_SYM,
    SWITCH_NUM,
    SWITCH_NAV
};

//
// ┌─────────────────────────────────────────────────┐
// │ ALIAS                                               │
// └─────────────────────────────────────────────────┘
//
// Shortcuts
#define KCU_COMMENT C(KC_SLSH)
#define KCU_LEFT_DESK C(A(KC_LEFT))
#define KCU_RIGHT_DESK C(A(KC_RIGHT))
// Diacritics
#define KCU_C_CEDILLA RALT(KC_COMM) // ç
#define KCU_E_ACUTE RALT(KC_E)      // é
// Symbols
#define KCU_COPYRIGHT RALT(KC_C)    // ©
#define KCU_EURO RALT(KC_5)         // €
#define KCU_POUND RALT(KC_DLR)      // £
#define KCU_DEGREE S(RALT(KC_SCLN)) // °

//
// ┌─────────────────────────────────────────────────┐
// │ TAP ALIAS                                           │
// └─────────────────────────────────────────────────┘
//
// Diacritics
#define TAP_E_GRAVE                \
    tap_key_with_mods(KC_GRV, 0U); \
    tap_code16(KC_E); // è
#define TAP_U_GRAVE                \
    tap_key_with_mods(KC_GRV, 0U); \
    tap_code16(KC_U); // ù
#define TAP_A_GRAVE                \
    tap_key_with_mods(KC_GRV, 0U); \
    tap_code16(KC_A); // à

// Symbols
#define TAP_GRAVE_ACCENT tap_undead_key(KC_GRV);  // `
#define TAP_TILD tap_undead_key(S(KC_GRV));       // ~
#define TAP_SIMPLE_QUOTE tap_undead_key(KC_QUOT); // '
#define TAP_DOUBLE_QUOTE tap_undead_key(KC_DQUO); // "

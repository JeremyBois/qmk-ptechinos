#pragma once

#include QMK_KEYBOARD_H

//
// ┌─────────────────────────────────────────────────┐
// │ LAYERS                                              │
// └─────────────────────────────────────────────────┘
//
enum custom_layers { L_QWERTY = 0, L_COLEMAK, L_NAV, L_MOUSE, L_NUM, L_SYM, L_MATH, L_GREEK, L_ADJUST };

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
    // Symbols
    C_EURO,
    C_POUND,
    C_COPYRIGHT,
    C_DEG,
    C_TILD,
    C_QUOT,
    C_DQUOT,
    C_GRV,
    // Wrapper for mod tap interception
    C_Y,
    C_Z,
    C_X,
    C_C,
    C_V,
    C_SLSH,
    C_LDESK,
    C_RDESK,
    C_GA,
    C_GP,
    // Diacritics
    C_A_GRV,
    C_E_ACU,
    C_E_GRV,
    C_C_CED,
    C_U_GRV,
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
// Diacritics
#define TAP_E_GRAVE                \
    tap_key_with_mods(KC_GRV, 0U); \
    tap_code16(KC_E); // è
#define TAP_U_GRAVE                \
    tap_key_with_mods(KC_GRV, 0U); \
    tap_code16(KC_U); // ù
#define TAP_A_GRAVE                \
    tap_key_with_mods(KC_GRV, 0U); \
    tap_code16(KC_A);                            // à
#define TAP_C_CEDILLA tap_code16(RALT(KC_COMM)); // ç
#define TAP_E_ACUTE tap_code16(RALT(KC_E));      // é

// Symbols
#define TAP_COPYRIGHT tap_code16(RALT(KC_C));      // ©
#define TAP_EURO tap_code16(RALT(KC_5));           // €
#define TAP_POUND tap_code16(RALT(KC_DLR));        // £
#define TAP_GRAVE_ACCENT tap_undead_key(KC_GRV);   // `
#define TAP_CIRCUMFLEX_ACCENT tap_code16(KC_CIRC); // ^
#define TAP_TILD tap_undead_key(S(KC_GRV));        // ~
#define TAP_SIMPLE_QUOTE tap_undead_key(KC_QUOT);  // '
#define TAP_DOUBLE_QUOTE tap_undead_key(KC_DQUO);  // "
#define TAP_DEGREE tap_code16(S(RALT(KC_SCLN)));   // °

// Shortcuts
#define TAP_UNDO tap_code16(C(KC_Z));
#define TAP_REDO tap_code16(C(KC_Y));
#define TAP_COPY tap_code16(C(KC_C));
#define TAP_CUT tap_code16(C(KC_X));
#define TAP_PASTE tap_code16(C(KC_V));
#define TAP_COMMENT tap_code16(C(KC_SLSH));
#define TAP_LEFT_DESK tap_code16(C(A(KC_LEFT)));
#define TAP_RIGHT_DESK tap_code16(C(A(KC_RIGHT)));

#pragma once

#include QMK_KEYBOARD_H

//
// ┌─────────────────────────────────────────────────┐
// │ LAYERS                                              │
// └─────────────────────────────────────────────────┘
//
enum custom_layers { L_DEFAULT = 0, L_COLEMAK, L_ERGOL, L_NAV, L_MOUSE, L_NUM, L_SYM, L_ADJUST };

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
#define C_UNDO C(KC_Z)
#define C_REDO C(KC_Y)
#define C_COPY C(KC_C)
#define C_CUT C(KC_X)
#define C_PASTE C(KC_V)
#define C_COMMENT C(KC_SLSH)

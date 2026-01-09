#pragma once

#include QMK_KEYBOARD_H
#include "quantum_keycodes.h"
#include "features/key_utility.h"

//
// ┌─────────────────────────────────────────────────┐
// │ LAYERS                                              │
// └─────────────────────────────────────────────────┘
//
// MOUSE should be last to always be the higher active whenever the cursor is moving
enum custom_layers { L_BASE = 0, L_QWERTY, L_NAV, L_NUM, L_MATH, L_GREEK, L_DIA, L_SYM, L_ADJUST, L_POINTER, L_MOUSE };

//
// ┌─────────────────────────────────────────────────┐
// │ CUSTOM KEYCODE                                      │
// └─────────────────────────────────────────────────┘
//
enum custom_keycodes {
#ifdef VIA_ENABLE
    C_CHORD = USER00,
#else
    C_CHORD = SAFE_RANGE,
#endif
    // // Repeat
    // REPEAT,
    // Avoid conflicting mode tap
    C_UNDS, // KC_MINS  and  KC_UNDS --> S(KC_MINS)
    C_PLUS, // KC_EQUAL and  KC_PLUS --> S(KC_EQUAL)
    C_PERC, // KC_5     and  KC_PERC --> S(KC_5)
    C_AT,   // KC_2     and  KC_AT   --> S(KC_2)
    C_LABK, // KC_COMMA and  KC_LABK --> S(KC_COMMA)
    C_RABK, // KC_DOT   and  KC_RABK --> S(KC_DOT)
    C_QUES, // KC_SLASH and  KC_QUES --> S(KC_SLASH)
    // Symbols requiring a dead key
    C_TILD,
    C_QUOT,
    C_DQUOT,
    C_FLQUOT,
    C_FRQUOT,
    C_GRV,
    // Wrapper for mod tap interception
    C_EURO,
    C_POUND,
    C_DEGREE,
    C_Y,
    C_Z,
    C_C,
    C_X,
    C_V,
    C_PSCR,
    C_LDESK,
    C_RDESK,
    C_GP,
    C_CW,
    // Ligatures
    C_AE_LIG,
    C_OE_LIG,
    // Diacritics
    C_E_ACUTE,
    C_E_TRE,
    C_A_CIR,
    C_E_CIR,
    C_I_CIR,
    C_O_CIR,
    C_U_CIR,
    C_A_GRV,
    C_E_GRV,
    C_U_GRV,
    C_C_CED,
    // Sequences
    S_CENTER,
    S_CLIP_HISTORY,
    S_EQ_EQ,
    S_EXLM_EQ,
    S_LESS_EQ,
    S_GREATER_EQ,
    S_RIGHT_ARROW,
    S_DRIGHT_ARROW,
    S_DLEFT_ARROW,
    S_RIGHT_FAT_ARROW,
    // Swappers
    SW_CTAB,
    SW_ATAB,
    // Layers
    ML_BASE,
    ML_NUM,
    ML_ADJUST,
    ML_MOUSE,
    SWITCH_SFT,
    SWITCH_DIA,
    SWITCH_SYM,
    SWITCH_NUM,
    SWITCH_NAV,
    // Caps word lock
    CW_LOCK_TOGG,
};

//
// ┌─────────────────────────────────────────────────┐
// │ ALIAS                                               │
// └─────────────────────────────────────────────────┘
//
// Shortcuts
#define KCU_COMMENT C(KC_SLSH)
// Non latin
#define KCU_AE_LIG RALT(KC_Z) // æ
#define KCU_OE_LIG RALT(KC_K) // œ
// Symbols
#define KCU_COPYRIGHT RALT(KC_C)    // ©
#define KCU_EURO RALT(KC_5)         // €
#define KCU_POUND RALT(KC_DLR)      // £
#define KCU_FLQUOT RALT(KC_LBRC)    // « “
#define KCU_FRQUOT RALT(KC_RBRC)    // » ”
#define KCU_DEGREE S(RALT(KC_SCLN)) // °
// Trick to detect tap vs hold on custom layer/mod handling
#define LT_SWITCH_SFT LT(0, SWITCH_SFT)
#define LT_SWITCH_NUM LT(0, SWITCH_NUM)
#define LT_SWITCH_NAV LT(0, SWITCH_NAV)
#define LT_SWITCH_SYM LT(0, SWITCH_SYM)
#define LT_SWITCH_DIA LT(0, SWITCH_DIA)

//
// ┌─────────────────────────────────────────────────┐
// │ TAP ALIAS                                           │
// └─────────────────────────────────────────────────┘

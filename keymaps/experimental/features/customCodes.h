#pragma once

//
// ***
// LAYER SETTINGS
// ***
//
enum custom_layers { _DEFAULT = 0, _COLEMAK, _ERGOL, _NAV, _NUM, _SYM, _ADJUST };

//
// ***
// CUSTOM KEYCODE HANDLING
// ***
//
enum custom_keycodes {
#ifdef VIA_ENABLE
    C_GRV = USER00,
#else
    C_GRV = SAFE_RANGE,
#endif
    C_TILD,
    C_QUOT,
    C_DQUOT,
    C_DEG,
    C_CHORD,   // LEADER key
    C_Z,
    C_X,
    C_C,
    C_V,
    C_SLSH,
    C_A_GRV,
    C_E_ACU,
    C_E_GRV,
    C_C_CED,
    C_U_GRV,
    SW_CTAB,   // Ctrl-tab
    SW_ATAB,   // Alt-tab
    ML_ADJUST, // Combo to move to ADJUST layer
    // SHIFT_DEFAULT, // LSFT_T(TO(DEFAULT))
    OSL_SYM,   // One shot layer without timer
    OSL_NUM,   //
    MHL_NAV,    // On move/hold layer without timer
    MHL_NUM    //
};

//
// ALIAS
//

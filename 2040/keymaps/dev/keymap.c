#include QMK_KEYBOARD_H

#include "keycodes.h"
#include "quantum.h"
#include "quantum_keycodes.h"
#include "process_keycode/process_unicodemap.h"

#include "2040.h"
#include "config.h"

#include "features/customCodes.h"
#include "g/keymap_combo.h"

#include "features/encoder.h"
#include "features/utility.h"
#include "features/swapper.h"
#include "features/switcher.h"
#include "features/auto_mouse.h"

#ifdef CONSOLE_ENABLE
#    include "print.h"
#endif // CONSOLE_ENABLE


void auto_mouse_reset(void);

//
// ┌─────────────────────────────────────────────────┐
// │ UNICODE                                             │
// └─────────────────────────────────────────────────┘
//

enum unicode_names {
    // Greek (lower / upper)
    GA = 0,
    S_GA,
    GB,
    S_GB,
    GC,
    S_GC,
    GD,
    S_GD,
    GE,
    S_GE,
    GF,
    S_GF,
    GG,
    S_GG,
    GH,
    S_GH,
    GI,
    S_GI,
    GK,
    S_GK,
    GL,
    S_GL,
    GM,
    S_GM,
    GN,
    S_GN,
    GO,
    S_GO,
    GP,
    S_GP,
    GQ,
    S_GQ,
    GR,
    S_GR,
    GS,
    S_GS,
    GT,
    S_GT,
    GU,
    S_GU,
    GW,
    S_GW,
    GX,
    S_GX,
    GY,
    S_GY,
    GZ,
    S_GZ,
    // Math
    M_PERP,
    M_SIM,
    M_PROP,
    M_PARTIAL,
    M_DIFF,
    M_UNION,
    M_NOT_IN,
    M_NOT_EXISTS,
    M_NOT_SUCH_AT,
    M_LOGIC_AND,
    M_TENSOR_PRODUCT,
    M_EMPTY,
    M_LARROW,
    M_INF,
    M_INTERSECTION,
    M_IN,
    M_EXISTS,
    M_SUCH_THAT,
    M_LOGIC_OR,
    M_PARALLEL,
    M_SUM,
    M_PRODUCT,
    M_FORALL,
    M_COMPOSE,
    M_IMPLIES,
    M_EQUIVALENT_TO,
    M_LOWER_EQ,
    M_LARGER_EQ,
    M_DOT,
    M_RATIONAL,
    M_NATURAL,
    M_REAL,
    M_INTEGER,
    M_COMPLEXE,
};

// Assigned based on pronunciation and then shape
const uint32_t PROGMEM unicode_map[] = {
    // GREEK
    [GA]   = 0x03B1, // Alpha Α α
    [S_GA] = 0x0391, //
    [GB]   = 0x03B2, // Beta Β β
    [S_GB] = 0x0392, //
    [GG]   = 0x03B3, // Gamma Γ γ
    [S_GG] = 0x0393, //
    [GD]   = 0x03B4, // Delta Δ δ
    [S_GD] = 0x0394, //
    [GE]   = 0x03B5, // Epsilon Ε ε
    [S_GE] = 0x0395, //
    [GZ]   = 0x03B6, // Zeta Ζ ζ
    [S_GZ] = 0x0396, //
    [GH]   = 0x03B7, // Eta Η η
    [S_GH] = 0x0397, //
    [GQ]   = 0x03B8, // Theta Θ θ
    [S_GQ] = 0x0398, //
    [GI]   = 0x03B9, // Iota Ι ι
    [S_GI] = 0x0399, //
    [GK]   = 0x03BA, // Kappa Κ κ
    [S_GK] = 0x039A, //
    [GL]   = 0x03BB, // Lambda Λ λ
    [S_GL] = 0x039B, //
    [GM]   = 0x03BC, // Mu Μ μ
    [S_GM] = 0x039C, //
    [GN]   = 0x03BD, // Nu Ν ν
    [S_GN] = 0x039D, //
    [GX]   = 0x03BE, // Xi Ξ ξ
    [S_GX] = 0x039E, //
    [GO]   = 0x03BF, // Omicron Ο ο
    [S_GO] = 0x039F, //
    [GP]   = 0x03C0, // Pi Π π
    [S_GP] = 0x03A0, //
    [GR]   = 0x03C1, // Rho Ρ ρ
    [S_GR] = 0x03A1, //
    [GS]   = 0x03C3, // Sigma Σ σ
    [S_GS] = 0x03A3, //
    [GT]   = 0x03C4, // Tau Τ τ
    [S_GT] = 0x03A4, //
    [GU]   = 0x03C5, // Upsilon Υ υ
    [S_GU] = 0x03A5, //
    [GF]   = 0x03C6, // Phi Φ φ
    [S_GF] = 0x03A6, //
    [GC]   = 0x03C7, // Chi Χ χ
    [S_GC] = 0x03A7, //
    [GY]   = 0x03C8, // Psi Ψ ψ
    [S_GY] = 0x03A8, //
    [GW]   = 0x03C9, // Omega Ω ω
    [S_GW] = 0x03A9, //
    // MATH
    [M_PERP]           = 0x27C2, // ⊥
    [M_SIM]            = 0x2248, // ≈
    [M_PROP]           = 0x221D, // ∝
    [M_PARTIAL]        = 0x2202, // ∂
    [M_DIFF]           = 0x2260, // ≠
    [M_INTERSECTION]   = 0x2229, // ∩
    [M_UNION]          = 0x222A, // ∪
    [M_EXISTS]         = 0x2203, // ∃
    [M_NOT_EXISTS]     = 0x2204, // ∄
    [M_IN]             = 0x2208, // ∈
    [M_NOT_IN]         = 0x2209, // ∉
    [M_SUCH_THAT]      = 0x220B, // ∋
    [M_NOT_SUCH_AT]    = 0x220C, // ∌
    [M_LOGIC_AND]      = 0x2227, // ∧
    [M_LOGIC_OR]       = 0x2228, // ∨
    [M_TENSOR_PRODUCT] = 0x2297, // ⊗
    [M_EMPTY]          = 0x2205, // ∅
    [M_LARROW]         = 0x2192, // →
    [M_INF]            = 0x221E, // ∞
    [M_PARALLEL]       = 0x2225, // ∥
    [M_SUM]            = 0x2211, // ∑
    [M_PRODUCT]        = 0x220F, // ∏
    [M_FORALL]         = 0x2200, // ∀
    [M_COMPOSE]        = 0x2218, // ∘
    [M_DOT]            = 0x22C5, // ⋅
    [M_IMPLIES]        = 0x21D2, // ⇒
    [M_EQUIVALENT_TO]  = 0x21D4, // ⇔
    [M_LOWER_EQ]       = 0x2264, // ≤
    [M_LARGER_EQ]      = 0x2265, // ≥
    [M_RATIONAL]       = 0x211A, // ℚ
    [M_NATURAL]        = 0x2115, // ℕ
    [M_REAL]           = 0x211D, // ℝ
    [M_INTEGER]        = 0x2124, // ℤ
    [M_COMPLEXE]       = 0x2102, // ℂ
};

//
// ┌─────────────────────────────────────────────────┐
// │ LAYOUTS                                             │
// └─────────────────────────────────────────────────┘
//
// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * QWERTY
     *        ,-----------------------------------.                    ,-----------------------------------.
     *        |       |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  | PSCR  |
     * ,------+-------+------+------+------+------|                    |------+------+------+------+-------+-------.
     * |      |   A   |   S  |   D  |   F  |   G  |                    |   H  |   J  |   K  |   L  |   P   |       |
     * |      | SHIFT |      |      |      |      |-------.    ,-------|      |      |      |      | SHIFT |       |
     * `------+-------+------+------+------+------|       |    |       |------+------+------+------+-------+-------'
     *        |   Z   |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   Q   |
     *        |       | LALT |      |      |      |       |    |       |      |      |      | LALT | RALT  |
     *        `-----------------------------------/      /      \      \-----------------------------------'
     *                       |   NAV  | Space  | /  NUM /        \ SYM  \ |  Enter |  DEF   |
     *                       |   NAV  | LCtrl  |/  NUM /          \ SYM  \|  RCtrl |        |
     *                       `--------'--------'------'            '------'--------'--------'
     */
    [L_QWERTY] = LAYOUT(
                     KC_Q, KC_W, KC_E, KC_R, KC_T,        KC_Y, KC_U, KC_I, KC_O, KC_PSCR,
    XXXXXXX, LSFT_T(KC_A), KC_S, KC_D, KC_F, KC_G,        KC_H, KC_J, KC_K, KC_L, RSFT_T(KC_P), XXXXXXX,
      KC_Z, LALT_T(KC_X), KC_C, KC_V, KC_B, XXXXXXX,    XXXXXXX, KC_N, KC_M,  KC_COMM, LALT_T(KC_DOT), RALT_T(KC_Q),
             SWITCH_NAV, LCTL_T(KC_SPC), SWITCH_NUM,    SWITCH_SYM, RCTL_T(KC_ENT), TO(L_QWERTY)
    ),

    /*
     * COLEMAK
     * https://colemak.com/
     *        ,-----------------------------------.                    ,-----------------------------------.
     *        |       |   W  |   F  |   P  |   G  |                    |   J  |   L  |   U  |   Y  |  PSCR |
     * ,------+-------+------+------+------+------|                    |------+------+------+------+-------+-------.
     * |      |   A   |   R  |   S  |   T  |   D  |                    |   H  |   N  |   E  |   I  |   O   |       |
     * |      | SHIFT |      |      |      |      |-------.    ,-------|      |      |      |      | SHIFT |       |
     * `------+-------+------+------+------+------|       |    |       |------+------+------+------+-------+-------'
     *        |   Z   |   X  |   C  |   V  |   B  |-------|    |-------|   K  |   M  |   ,  |   .  |   Q   |
     *        |       | LALT |      |      |      |       |    |       |      |      |      | LALT | RALT  |
     *        `-----------------------------------/       /     \       \----------------------------------'
     *                       |   NAV  | Space  | /  NUM  /       \ SYM   \ |  Enter |  DEF  |
     *                       |   NAV  | LCtrl  |/  NUM  /         \ SYM   \|  RCtrl |       |
     *                       `--------'--------'-------'           '-------'--------'-------'
     */
    [L_COLEMAK] = LAYOUT(
                      KC_Q, KC_W, KC_F, KC_P, KC_G,        KC_J, KC_L, KC_U, KC_Y, _______,
     XXXXXXX, LSFT_T(KC_A), KC_R, KC_S, KC_T, KC_D,        KC_H, KC_N, KC_E, KC_I, RSFT_T(KC_O), XXXXXXX,
       KC_Z, LALT_T(KC_X), KC_C, KC_V, KC_B, _______,    _______, KC_K, KC_M, KC_COMM, LALT_T(KC_DOT), RALT_T(KC_Q),
                           _______, _______, _______,    _______, _______, _______
    ),
    /*
     * COLEMAK-DH
     * https://colemakmods.github.io/
     *        ,-----------------------------------.                    ,-----------------------------------.
     *        |       |   W  |   F  |   P  |   B  |                    |   J  |   L  |   U  |   Y  |  PSCR |
     * ,------+-------+------+------+------+------|                    |------+------+------+------+-------+-------.
     * |      |   A   |   R  |   S  |   T  |   G  |                    |   M  |   N  |   E  |   I  |   O   |       |
     * |      | SHIFT |      |      |      |      |-------.    ,-------|      |      |      |      | SHIFT |       |
     * `------+-------+------+------+------+------|       |    |       |------+------+------+------+-------+-------'
     *        |   Z   |   X  |   C  |   D  |   V  |-------|    |-------|   K  |   H  |   ,  |   .  |   Q   |
     *        |       | LALT |      |      |      |       |    |       |      |      |      | LALT | RALT  |
     *        `-----------------------------------/       /     \       \----------------------------------'
     *                       |   NAV  | Space  | /  NUM  /       \ SYM   \ |  Enter |  DEF  |
     *                       |   NAV  | LCtrl  |/  NUM  /         \ SYM   \|  RCtrl |       |
     *                       `--------'--------'-------'           '-------'--------'-------'
     */
    [L_COLEMAK_DH] = LAYOUT(
                      KC_Q, KC_W, KC_F, KC_P, KC_B,        KC_J, KC_L, KC_U, KC_Y, _______,
     XXXXXXX, LSFT_T(KC_A), KC_R, KC_S, KC_T, KC_G,        KC_M, KC_N, KC_E, KC_I, RSFT_T(KC_O), XXXXXXX,
       KC_Z, LALT_T(KC_X), KC_C, KC_D, KC_V, _______,    _______, KC_K, KC_H, KC_COMM, LALT_T(KC_DOT), RALT_T(KC_Q),
                           _______, _______, _______,    _______, _______, _______
    ),
    /*
     * NAV
     *  - Arrows | End / Begin | Top / Bottom
     * Left --> Useful with mouse (right hand) + Used with NAV active
     *   - Moving between workspace with one hand (required to be able to use drag and drop)
     *   - Screen scrolling with one hand
     *        ,------------------------------------.                    ,-----------------------------------.
     *        |       | WH_L | WH_U | WH_R  | PgUp |                    |Clip_H| Home |  Up  | End  | PSCR  |
     * ,------+-------+------+------+-------+------|                    |------+------+------+------+-------+-------.
     * |      | ATab  | MB2  | WH_D |  MB1  | PgDo |                    |  MB4 | Left | Down | Right|  MB5  |       |
     * |      | SHIFT |      |      |       |      |-------.    ,-------|      |      |      |      | SHIFT |       |
     * `------+-------+------+------+------ +------|       |    |       |------+------+------+------+-------+-------'
     *        |       | LDesk|Center| RDesk |      |-------|    |-------| Redo | Undo | Copy | Paste| Cut   |
     *        |       | LALT |      |       |      |       |    |       |      |      |      | LALT | RALT  |
     *        `------------------------------------/      /      \      \-----------------------------------'
     *                      |   NAV   | Space  | /  NUM  /        \ SYM  \ |  Enter |  DEF   |
     *                      |   NAV   | LCtrl  |/  NUM  /          \ SYM  \|  RCtrl |        |
     *                      `---------'--------'-------'            '------'--------'--------'
     */
    [L_NAV] = LAYOUT(
                 XXXXXXX, KC_WH_L, KC_WH_U, KC_WH_R, KC_PGUP,        S_CLIP_HISTORY, KC_HOME, KC_UP, KC_END, _______,
XXXXXXX, LSFT_T(SW_ATAB), KC_BTN2, KC_WH_D, KC_BTN1, KC_PGDN,        KC_BTN4, KC_LEFT, KC_DOWN, KC_RGHT, LSFT_T(KC_BTN5), XXXXXXX,
  XXXXXXX, LALT_T(C_LDESK), S_CENTER, C_RDESK, XXXXXXX, _______,    _______, C(KC_Y), C(KC_Z), C(KC_C), LALT_T(C_V), RALT_T(C_X),
                                     _______, _______, _______,    _______, _______, _______
    ),
    /*
     * MOUSE
     *         ,-----------------------------------.                    ,-----------------------------------.
     *         |      |  MB4 |  MB3 |  MB5  |RCPI_U|                    | LCPI_U|  MB5 |  MB3 |  MB4 | PSCR |
     * ,-------|------+------+------+-------+------+                    |-------+------+------+------+------------.
     * |       | ATab |  MB2 |RScrol|  MB1  |RCPI_D|                    | LCPI_D|  MB1 | LScro|  MB2 | ATab |     |
     * |       | SHIFT|      |      |       |      |-------.    ,-------|       |      |      |      | SHIFT|     |
     * `-------+------+------+------+-------+------|  PSCR |    |       |-------+------+------+------+------------'
     *         | Cut  | Paste| Copy | Undo  | Redo |-------|    |-------|  Redo | Undo | Copy | Paste| Cut  |
     *         |      | LALT |      |       |      |       |    |       |       |      |      | LALT | RALT |
     *         `-----------------------------------/      /      \      \-----------------------------------'
     *                      |   NAV   | Space  | /  NUM  /        \ SYM  \ |  Enter |  DEF   |
     *                      |   NAV   | LCtrl  |/  NUM  /          \ SYM  \|  RCtrl |        |
     *                      `---------'--------'-------'            '------'--------'--------'
     */
    #if defined(POINTING_DEVICE_ENABLE)
      [L_MOUSE] = LAYOUT(
                        XXXXXXX, KC_BTN4, KC_BTN3, KC_BTN5, PR_CPI_UP,       PL_CPI_UP, KC_BTN5, KC_BTN3, KC_BTN4, _______,
XXXXXXX, LSFT_T(SW_ATAB), KC_BTN2, PR_DS_TOOGLE, KC_BTN1, PR_CPI_DOWN,       PL_CPI_DOWN, KC_BTN1, PL_DS_TOOGLE, KC_BTN2, LSFT_T(SW_ATAB), XXXXXXX,
                C(KC_X), LALT_T(C_V), C(KC_C), C(KC_Z), C(KC_Y), _______,   _______, C(KC_Y), C(KC_Z), C(KC_C), LALT_T(C_V), RALT_T(C_X),
                                              _______, _______, _______,   _______, _______, _______
    ),
      #else
      [L_MOUSE] = LAYOUT(
                  XXXXXXX, KC_BTN4, KC_BTN3, KC_BTN5, XXXXXXX,         XXXXXXX, KC_BTN4, KC_BTN3, KC_BTN5, XXXXXXX,
 XXXXXXX, LSFT_T(SW_ATAB), KC_BTN2, XXXXXXX, KC_BTN1, XXXXXXX,         XXXXXXX, KC_BTN1, XXXXXXX, KC_BTN2, LSFT_T(SW_ATAB), XXXXXXX,
        C(KC_X), LALT_T(C_V), C(KC_C), C(KC_Z), C(KC_Y), _______,     _______, C(KC_Y), C(KC_Z), C(KC_C), LALT_T(C_V), RALT_T(C_X),
                                      _______, _______, _______,     _______, _______, _______
    ),
      #endif
    /* NUM
     *        ,------------------------------------.                    ,-----------------------------------.
     *        |   ©   |  F9  |  F8  |  F7  |  F11  |                    |  F11 |   7  |   8  |   9  | PSCR  |
     * ,------+-------+------+------+------+-------|                    |------+------+------+------+-------+------.
     * |      |   F10 |  F3  |  F2  |  F1  |   ,   |                    |   .  |   1  |   2  |   3  |   0   |      |
     * |      | SHIFT |      |      |      |       |-------.    ,-------|      |      |      |      | SHIFT |      |
     * `------+-------+------+------+------+-------|       |    |       |------+------+------+------+-------+------'
     *        |   £   |  F6  |  F5  |  F4  |  F12  |-------|    |-------|  F12 |   4  |   5  |   6  |   €   |
     *        |       | LALT |      |      |       |       |    |       |      |      |      | LALT |  RALT |
     *        `------------------------------------/      /      \      \-----------------------------------'
     *                       |   NAV   | Space  | /  NUM /        \ SYM  \ |  Enter |  DEF   |
     *                       |   NAV   | LCtrl  |/  NUM /          \ SYM  \|  RCTRL |        |
     *                       `---------'--------'------'            '------'--------'--------'
     */
    [L_NUM] = LAYOUT(
               KCU_COPYRIGHT,  KC_F9, KC_F8, KC_F7, KC_F11,       KC_F11, KC_7, KC_8, KC_9, _______,
    XXXXXXX, LSFT_T(KC_F10), KC_F3, KC_F2, KC_F1, KC_COMMA,       KC_DOT,   KC_1,  KC_2,  KC_3, RSFT_T(KC_0), XXXXXXX,
    KCU_POUND, LALT_T(KC_F6), KC_F5, KC_F4,  KC_F12, _______,   _______, KC_F12,  KC_4,  KC_5,  LALT_T(KC_6), RALT_T(C_EURO),
                                   _______, _______, _______,   _______, _______, _______
    ),
    /* SYM
     *
     *        ,------------------------------------.                    ,------------------------------------.
     *        | GREEK |   :  |  #   |  ;   |  ` ~  |                    |   %   |   &  |   *  |   ?  | MATH  |
     * ,------+-------+------+------+------+-------|                    |-------+------+------+------+-------+------.
     * |      |   `…  |   à  |  _   |  é   |   /   |                    |   \   |   è  |   '  |   !  |  ^…   |      |
     * |      | SHIFT |      |      |      |       |-------.    ,-------|       |      |      |      | SHIFT |      |
     * `------+-------+------+------+------+-------|       |    |       |-------+------+------+------+-------+------'
     *        |   |   | = ×  |  -   |  + ÷ |  "…   |-------|    |-------|  '…   |   @  |   "  |   $  |   ç   |
     *        |       |      |      |      |       |       |    |       |       |      |      |      |  RALT |
     *        `------------------------------------/      /      \      \------------------------------------'
     *                       |   NAV   | Space  | /  NUM /        \ SYM  \ |  Enter |  DEF    |
     *                       |   NAV   | LCtrl  |/  NUM /          \ SYM  \|  LCtrl |         |
     *                       `---------'--------'------'            '------'--------'---------'
     *
     */
    [L_SYM] = LAYOUT(
                           TO(L_GREEK), KC_COLN, KC_HASH, KC_SCLN, C_GRV,      KC_PERC, KC_AMPR, KC_ASTR, KC_QUES, TO(L_MATH),
XXXXXXX, LSFT_T(KC_GRV), C_A_GRV, KC_UNDS, KCU_E_ACUTE, KC_SLSH, KC_BSLS,      C_E_GRV, C_QUOT, KC_EXLM, RSFT_T(KC_CIRC), XXXXXXX,
                       KC_PIPE, KC_EQL, KC_MINS, KC_PLUS, KC_DQUO, _______,   _______, KC_QUOT, KC_AT, C_DQUOT, KC_DLR, RALT_T(C_C_CED),
                                                 _______, _______, _______,   _______, _______, _______
    ),
     /*
     * MATH
     *        ,-----------------------------------.                    ,-----------------------------------.
     *        |   ⊥   |  ≈   |  ∝  |   ∂  |   ≠  |                    |   ∧  |  ∉   |  ∄  |  ∅   |   ∞   |
     * ,------+-------+------+------+------+------|                    |------+------+------+------+-------+-------.
     * |      |   ⊗   |  →  |  ⇒   |  ⇔  |   °  |                    |   ⋅  |  ∈   |  ∃   |  ≤   |   ≥   |       |
     * |      |       |      |      |      |      |-------.    ,-------|      |      |      |      |       |       |
     * `------+-------+------+------+------+------|       |    |       |------+------+------+------+-------+-------'
     *        |   ∥   |  ∑   |  ∏   |  ∀   |   ∘  |-------|    |-------|  ℕ   | ℤ   |   ℚ  |  ℝ   |  ℂ   |
     *        |       |      |      |      |      |       |    |       |      |      |      |      |       |
     *        `-----------------------------------/      /      \      \-----------------------------------'
     *                       |   NAV  | Space  | /  NUM /        \ SYM  \ |  Enter |  DEF   |
     *                       |   NAV  | LCtrl  |/  NUM /          \ SYM  \|  RCtrl |        |
     *                       `--------'--------'------'            '------'--------'--------'
     */
    [L_MATH] = LAYOUT(
                                UM(M_PERP), UM(M_SIM), UM(M_PROP), UM(M_PARTIAL), UM(M_DIFF),       UM(M_LOGIC_AND), UM(M_NOT_IN), UM(M_NOT_EXISTS), UM(M_EMPTY), UM(M_INF),
 XXXXXXX, UM(M_TENSOR_PRODUCT), UM(M_LARROW), UM(M_IMPLIES), UM(M_EQUIVALENT_TO), KCU_DEGREE,       UM(M_DOT), UM(M_IN), UM(M_EXISTS), UM(M_LOWER_EQ), UM(M_LARGER_EQ), XXXXXXX,
                UM(M_PARALLEL), UM(M_SUM), UM(M_PRODUCT), UM(M_FORALL), UM(M_COMPOSE), _______,   _______, UM(M_NATURAL), UM(M_INTEGER), UM(M_RATIONAL), UM(M_REAL), UM(M_COMPLEXE),
                                                                     _______, _______, _______,   _______, _______, _______
    ),
    /*
     * GREEK (Qwerty based position (letter pronunciation then shape))
     *        ,-----------------------------------.                    ,-----------------------------------.
     *        |       |  Ω ω |  Ε ε |  Ρ ρ | Τ τ  |                    |  Ψ ψ |  Υ υ |  Ι ι |  Ο ο |       |
     * ,------+-------+------+------+------+------|                    |------+------+------+------+-------+-------.
     * |      |  Α α  |  Σ σ |  Δ δ |  Φ φ | Γ γ  |                    |  Η η |      |  Κ κ |  Λ λ |  Π π  |       |
     * |      | Shift |      |      |      |      |-------.    ,-------|      |      |      |      | Shift |       |
     * `------+-------+------+------+------+------|       |    |       |------+------+------+------+-------+-------'
     *        |  Ζ ζ  |  Ξ ξ |  Χ χ |      | Β β  |-------|    |-------|  Ν ν |  Μ μ |      |      | Θ θ   |
     *        |       |      |      |      |      |       |    |       |      |      |      |      |       |
     *        `-----------------------------------/      /      \      \-----------------------------------'
     *                       |   NAV  | Space  | /  NUM /        \ SYM  \ |  Enter |  DEF   |
     *                       |   NAV  | LCtrl  |/  NUM /          \ SYM  \|  RCtrl |        |
     *                       `--------'--------'------'            '------'--------'--------'
     */
      [L_GREEK] = LAYOUT(
         UP(GQ, S_GQ), UP(GW, S_GW), UP(GE, S_GE), UP(GR, S_GR), UP(GT, S_GT),       UP(GY, S_GY), UP(GU, S_GU), UP(GI, S_GI), UP(GO, S_GO), _______,
XXXXXXX, LSFT_T(C_GA), UP(GS, S_GS), UP(GD, S_GD), UP(GF, S_GF), UP(GG, S_GG),       UP(GH, S_GH), XXXXXXX, UP(GK, S_GK), UP(GL, S_GL), RSFT_T(C_GP), XXXXXXX,
       UP(GZ, S_GZ), UP(GX, S_GX), UP(GC, S_GC), XXXXXXX, UP(GB, S_GB), _______,   _______, UP(GN, S_GN), UP(GM, S_GM),  XXXXXXX, XXXXXXX, UP(GQ, S_GQ),
                                                      _______, _______, _______,   _______, _______, _______
    ),
    /* ADJUST
     *         ,-----------------------------------.                    ,------------------------------------.
     *         |RGB_MO|hue ^ |sat ^ | bri ^|  BRIU |                    | VOLU  | MRWD  | STOP  | MFFD |      |
     * ,-------|------+------+------+------+-------+                    |-------+-------+-------+------+------------.
     * |       |RGB_TO|hue_dn|sat_dn|bri_dn|  BRID |                    | VOLD  | PREV  | PLAY  | NEXT |EEPRST|RESET|
     * |       |      |      |      |      |       |-------.    ,-------|       |       |       |      |      |     |
     * `-------+------+------+------+------+-------|       |    |       |-------+-------+-------+------+------------'
     *         |      | U_M  | U_L  | U_W  | U_WC  |-------|    |-------|QWERTY |COLEMAK|COLEMAK|      |DEBUG |
     *         |      |      |      |      |       |       |    |       |       |       |   DH  |      |      |
     *         `-----------------------------------/      /      \      \-------------------------------------'
     *                       |         |        | /      /        \      \ |        |   DEF     |
     *                       |         |        |/      /          \      \|        |           |
     *                       `---------'--------'------'            '------'--------'-----------'
     */
      [L_ADJUST] = LAYOUT(
              RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, KC_BRIU,        KC_VOLU, KC_MRWD, KC_MEDIA_STOP, KC_MFFD, XXXXXXX,
     XXXXXXX, RGB_TOG, RGB_HUD, RGB_SAD, RGB_VAD, KC_BRID,        KC_VOLD, KC_MPRV, KC_MPLY, KC_MNXT, EE_CLR, QK_BOOT,
         XXXXXXX, UC_MAC, UC_LINX, UC_WIN, UC_WINC, XXXXXXX,    XXXXXXX, DF(L_QWERTY), DF(L_COLEMAK), DF(L_COLEMAK_DH), XXXXXXX, QK_DEBUG_TOGGLE,
                                  XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, _______
    )
    };
// clang-format on

//
// ┌─────────────────────────────────────────────────┐
// │ COMBOS                                              │
// └─────────────────────────────────────────────────┘
//
/*
 *        ,-----------------------------------.                    ,----------------------------------.
 *        |-------|       ESCAPE       |      |                    |      |      LAUNCHER      |------|
 * ,------+-------+ [«   +  {“  +   (  +------|                    |------+  )   +  }”  +  ]»  +------+------.
 * |      |       |            TAB            |-------.    ,-------|      |    BACK    DEL     |      |      |
 * `------+-------+------+------+------+------|       |    |       |------+------+------+------+------+------'
 *        |       |    GUI   COMMENT   |      |-------|    |-------|      |    CAPS    GUI            |
 *        `-----------------------------------/      /      \      \----------------------------------'
 *                     |        |          | / ADJ- /        \ -UST \ |        |        |
 *                     |        |          |/      /          \      \|        |        |
 *                     `-------------------'------'            '------'-----------------'
 */

uint16_t get_combo_term(uint16_t index, combo_t* combo) {
    switch (index) {
        // Home / Tight combos
        case tab:
        case back:
        case del:
        case launcher:
        case escape_l:
        case caps:
        case comment:
            return COMBO_TERM;
        // Modifier combos
        case gui_l:
        case gui_r:
            return COMBO_TERM + 20;
        // Two hands combos
        case adjust:
            return COMBO_TERM + 20;
        // Vertical combos
        case curly_l: // { “
        case curly_r: // } ”
        case round_l:
        case round_r:
        case square_l: // [ «
        case square_r: // ] »
            return COMBO_TERM + 40;
        default:
            return COMBO_TERM;
    }
}

bool get_combo_must_tap(uint16_t index, combo_t* combo) {
    switch (index) {
        case escape_l:
        case caps:
        case comment:
        case launcher:
        case back:
        case del:
        case round_l:
        case round_r:
        case square_l:
        case square_r:
        case gui_l:
        case gui_r:
            // Quick roll is allowed
            return false;
        case curly_l:
        case curly_r:
        case tab:
        case adjust:
        default:
            // Avoid roll to still be able to use mouse keys / game arrows keys
            return true;
    }
}

//
// ┌─────────────────────────────────────────────────┐
// │ LAYER / SWAPPER                                     │
// └─────────────────────────────────────────────────┘
//
// Custom swappers
bool swapper_atab_active = false;
// Custom layer switchers
switcher_state switcher_sym_state = os_up_unqueued;
switcher_state switcher_num_state = os_up_unqueued;
switcher_state switcher_nav_state = os_up_unqueued;

bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
        case TO(L_QWERTY):
        case KC_ESC:
            return true;
        default:
            return false;
    }
}

bool is_oneshot_layer_cancel_key(uint16_t keycode) {
    switch (keycode) {
        case TO(L_QWERTY):
        case SWITCH_NAV:
        case SWITCH_SYM:
        case SWITCH_NUM:
        case KC_ESC:
            return true;
        default:
            return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
        // Modifiers
        case QK_MODS ... QK_MODS_MAX:
        // Mod taps
        case QK_MOD_TAP ... QK_MOD_TAP_MAX:
            return true;

        // Layers
        case TO(L_QWERTY):
        case SWITCH_NAV:
        case SWITCH_SYM:
        case SWITCH_NUM:
            return true;

        default:
            return false;
    }
}

bool is_oneshot_layer_ignored_press(uint16_t keycode) {
    switch (keycode) {
        // Some modifiers
        case KC_RIGHT_ALT:
        // Mod taps
        case QK_MOD_TAP ... QK_MOD_TAP_MAX:
            return true;
        default:
            return false;
    }
}

//
// ┌─────────────────────────────────────────────────┐
// │ CUSTOM KEYCODE HANDLING                             │
// └─────────────────────────────────────────────────┘
//
bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    // Swapper on one key (no timer)
    update_swapper(&swapper_atab_active, KC_LALT, KC_TAB, LSFT_T(SW_ATAB), keycode, record);

    // Custom layer change (no timer)
    update_oneshot_layer(&switcher_sym_state, L_SYM, SWITCH_SYM, keycode, record);
    update_oneshot_layer(&switcher_num_state, L_NUM, SWITCH_NUM, keycode, record);
    update_move_hold_layer(&switcher_nav_state, L_NAV, SWITCH_NAV, keycode, record);

    // Custom keycodes
    bool let_qmk_handle_it = true;
    switch (keycode) {
        // Handle dead keys sequences
        case C_GRV:
            if (record->event.pressed) {
                TAP_GRAVE_ACCENT
                let_qmk_handle_it = false;
            }
            break;
        case C_TILD:
            if (record->event.pressed) {
                TAP_TILD
                let_qmk_handle_it = false;
            }
            break;
        case C_QUOT:
            if (record->event.pressed) {
                TAP_SIMPLE_QUOTE
                let_qmk_handle_it = false;
            }
            break;
        case C_DQUOT:
            if (record->event.pressed) {
                TAP_DOUBLE_QUOTE
                let_qmk_handle_it = false;
            }
            break;
        case C_A_GRV:
            if (record->event.pressed) {
                TAP_A_GRAVE
                let_qmk_handle_it = false;
            }
            break;
        case C_E_GRV:
            if (record->event.pressed) {
                TAP_E_GRAVE
                let_qmk_handle_it = false;
            }
            break;
        case C_U_GRV:
            if (record->event.pressed) {
                TAP_U_GRAVE
                let_qmk_handle_it = false;
            }
            break;
        // Handle normal sequences
        case S_CENTER:
            if (record->event.pressed) {
                // Press Ctrl(K, C) to center the window arround the cursor
                register_code(KC_LCTL);
                tap_code16(KC_K);
                tap_code16(KC_C);
                unregister_code(KC_LCTL);
                let_qmk_handle_it = false;
            }
            break;
        case S_CLIP_HISTORY:
            if (record->event.pressed) {
                // Press Ctrl(K, V), Down to show copy history and select first row
                register_code(KC_LCTL);
                tap_code16(KC_K);
                tap_code16(KC_V);
                unregister_code(KC_LCTL);
                tap_code16(KC_DOWN);
                let_qmk_handle_it = false;
            }
            break;
        // Disable hold behavior for some keys
        case C_RDESK:
            if (record->event.pressed) {
                tap_code16(KCU_RIGHT_DESK);
                let_qmk_handle_it = false;
            }
            break;
        // https://docs.qmk.fm/#/mod_tap?id=intercepting-mod-taps
        // Intercept to send key with modifier on tap
        case RALT_T(C_X):
            if (record->tap.count && record->event.pressed) {
                tap_code16(C(KC_X));
                let_qmk_handle_it = false;
            }
            break;
        case RALT_T(C_C_CED):
            if (record->tap.count && record->event.pressed) {
                tap_code16(KCU_C_CEDILLA);
                let_qmk_handle_it = false;
            }
            break;
        case RALT_T(C_EURO):
            if (record->tap.count && record->event.pressed) {
                tap_code16(KCU_EURO);
                let_qmk_handle_it = false;
            }
            break;
        case LALT_T(C_V):
            if (record->tap.count && record->event.pressed) {
                tap_code16(C(KC_V));
                let_qmk_handle_it = false;
            }
            break;
        case LALT_T(C_LDESK):
            if (record->tap.count && record->event.pressed) {
                tap_code16(KCU_LEFT_DESK);
                let_qmk_handle_it = false;
            }
            break;
        case RSFT_T(C_GP):
            if (record->tap.count && record->event.pressed) {
                process_unicodemap(UP(GP, S_GP), record);
                let_qmk_handle_it = false;
            }
            break;
        case LSFT_T(C_GA):
            if (record->tap.count && record->event.pressed) {
                process_unicodemap(UP(GA, S_GA), record);
                let_qmk_handle_it = false;
            }
            break;
        case LSFT_T(KC_CIRC):
        case RSFT_T(KC_CIRC):
            // Required to avoid to input 6 when combined with mod-tap
            if (record->tap.count && record->event.pressed) {
                tap_code16(KC_CIRC);
                let_qmk_handle_it = false;
            }
            break;
        // Handle special layers
        case TO(L_QWERTY):
            // Force modifiers to cancel (should not be neccessary but just to be safe)
            clear_mods();
#if defined(POINTING_DEVICE_ENABLE) && defined(PTECHINOS_AUTO_MOUSE_LAYER)
            // Force end of mouse layer
            auto_mouse_set_inactive();
            auto_mouse_reset();
#endif
            break;
        case ML_ADJUST:
            if (record->event.pressed) {
                // Force modifiers to cancel (should not be neccessary but just to be safe)
                clear_mods();
#if defined(POINTING_DEVICE_ENABLE) && defined(PTECHINOS_AUTO_MOUSE_LAYER)
                // Force end of mouse layer
                auto_mouse_set_inactive();
                auto_mouse_reset();
#endif
                // ADJUST layer from combo
                layer_move(L_ADJUST);
                let_qmk_handle_it = false;
            }
            break;
    }

#if defined(POINTING_DEVICE_ENABLE) && defined(PTECHINOS_AUTO_MOUSE_LAYER)
    // Auto mouse feature processing
    auto_mouse_on_process_record(keycode, record);
#endif

    // Return false to ignore further processing of key
    // Return true to let qmk handles it
    return let_qmk_handle_it;
};

//
// ┌─────────────────────────────────────────────────┐
// │ CAPS WORD                                           │
// └─────────────────────────────────────────────────┘
//
bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
            add_weak_mods(MOD_BIT(KC_LSFT)); // Apply shift to next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
        case KC_MINS:
        case LSFT_T(KC_CIRC):
            return true;

        // Changing layers continue Caps Word, without shifting.
        // Except when moving back to default layer
        case SWITCH_NUM:
        case SWITCH_SYM:
        case SWITCH_NAV:
            return true;

        default:
            return false; // Deactivate Caps Word.
    }
}

//
// ┌─────────────────────────────────────────────────┐
// │ MOD tap                                             │
// └─────────────────────────────────────────────────┘
//

// get_hold_on_other_key_press as precedence (activated earlier) over get_permissive_hold
// true  --> trigger hold
// false --> trigger tap

#if defined(PERMISSIVE_HOLD_PER_KEY)
bool get_permissive_hold(uint16_t keycode, keyrecord_t* record) {
    if (record->event.key.row == 3) {
        // Bottom row mods
        return true;
    }
    switch (keycode) {
        case MT(MOD_LCTL, KC_SPC):
            // Immediately select the hold action when another key is tapped.
            return true;
        default:
            // Do not select the hold action when another key is tapped.
            return false;
    }
}
#endif

#if defined(HOLD_ON_OTHER_KEY_PRESS_PER_KEY)
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case MT(MOD_RCTL, KC_ENT):
            // Hold
            return true;
        default:
            // Do not select the hold action when another key is tapped.
            return false;
    }
}
#endif

//
// ┌─────────────────────────────────────────────────┐
// │ AUTO MOUSE (PTECHINOS)                              │
// └─────────────────────────────────────────────────┘
//

#if defined(POINTING_DEVICE_ENABLE) && defined(PTECHINOS_AUTO_MOUSE_LAYER)
void pointing_device_init_user(void) {
    auto_mouse_set_layer(L_MOUSE);
    auto_mouse_set_enabled(true);
}

bool auto_mouse_should_exit_user(uint16_t keycode, keyrecord_t* record) {
    bool should_exit = false;
    switch (keycode) {
        // Switching a layer should terminate the auto mouse layer
        case SWITCH_SYM:
        case SWITCH_NUM:
        case SWITCH_NAV:
            should_exit = true;
            break;
        default:
            break;
    }

    return should_exit;
}

#    if defined(SPLIT_POINTING_ENABLE)
#        if defined(POINTING_DEVICE_COMBINED)
report_mouse_t pointing_device_task_combined_user(report_mouse_t left_report, report_mouse_t right_report) {
    report_mouse_t report = pointing_device_combine_reports(left_report, right_report);
    auto_mouse_on_pointing_device_task(report);
    return report;
}
#        elif defined(POINTING_DEVICE_LEFT)
report_mouse_t pointing_device_task_user(report_mouse_t report) {
    auto_mouse_on_pointing_device_task(report);
    return report;
}
#        elif defined(POINTING_DEVICE_RIGHT)
report_mouse_t pointing_device_task_user(report_mouse_t report) {
    auto_mouse_on_pointing_device_task(report);
    return report;
}
#        else
#            error "You need to define the side(s) the pointing device is on. POINTING_DEVICE_COMBINED / POINTING_DEVICE_LEFT / POINTING_DEVICE_RIGHT"
#        endif
#    else
report_mouse_t pointing_device_task_user(report_mouse_t report) {
    if (!is_keyboard_master()) return report;

    auto_mouse_on_pointing_device_task(report);
    return report;
}
#    endif

void auto_mouse_reset(void) {
    // Switch to mousing mode
    if (ptechinos_is_pointer_dragscroll_enabled(PTECHINOS_RIGHT)) {
        ptechinos_set_pointer_as_mousing(PTECHINOS_RIGHT);
    }
    if (ptechinos_is_pointer_dragscroll_enabled(PTECHINOS_LEFT)) {
        ptechinos_set_pointer_as_mousing(PTECHINOS_LEFT);
    }
}
#endif

//
// ┌─────────────────────────────────────────────────┐
// │ DEBUG                                               │
// └─────────────────────────────────────────────────┘
//
#if defined(CONSOLE_ENABLE)
void keyboard_post_init_user(void) {
    debug_enable = true;
    // debug_matrix   = true;
    // debug_keyboard = true;
    // debug_mouse    = true;
}
#endif

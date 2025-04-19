#include "_wait.h"
#include "action.h"
#include "action_layer.h"
#include "action_util.h"
#include "caps_word.h"
#include "keymap_us.h"
#include "modifiers.h"
#include QMK_KEYBOARD_H
#include "keycodes.h"
#include "quantum.h"
#include "quantum_keycodes.h"

#if defined(UNICODEMAP_ENABLE)
#    include "process_keycode/process_unicodemap.h"
#endif

#include "2040.h"
#include "config.h"

#include "features/customCodes.h"
#include "g/keymap_combo.h"

#include "features/encoder.h"
#include "features/swapper.h"
#include "features/switcher.h"

#if defined(POINTING_DEVICE_ENABLE) && defined(PTECHINOS_AUTO_MOUSE_ENABLE)
#    include "features/auto_mouse.h"
#endif

#ifdef CONSOLE_ENABLE
#    include "print.h"
#endif // CONSOLE_ENABLE

//
// ┌─────────────────────────────────────────────────┐
// │ UNICODE                                             │
// └─────────────────────────────────────────────────┘
//

#if defined(UNICODEMAP_ENABLE)
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
#endif

//
// ┌─────────────────────────────────────────────────┐
// │ LAYOUTS                                             │
// └─────────────────────────────────────────────────┘
//
// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * v1(graphite) https://cyanophage.github.io/playground.html?layout=%27ldwbyfou%2F%3Bnrtsgkheai-xqmcvjp%2C.z
     * v2(graphite) https://cyanophage.github.io/playground.html?layout=%5Cldwbyfou%5C%5Cnrtsgkmeai%2Fxqpcvjh%2C.z
     * v3(custom) https://cyanophage.github.io/playground.html?layout=qldybzfouj%5Cnrtsgkmeai%2Fxwpcv%5Ch%2C.%5C
     * v4(custom) https://cyanophage.github.io/playground.html?layout=qldybzfouj\nrtsgkmeai%2Fxwpcv%27h%2C.%3B
     * v5(custom) https://cyanophage.github.io/playground.html?layout=qldwbyfou%252F%253Bnrtsgkmeai-xjpcvzh%252C.'
     * v6(custom) https://cyanophage.github.io/playground.html?layout=qldwbyfou%252F%253Bnrtsgkmeia-xjpcvzh%252C.'
     *        ,-----------------------------------.                    ,-----------------------------------.
     *        |   Q   |   L  |   D  |   W  |   B  |                    |   Y  |   F  |   O  |   U  | Mouse |
     * ,------+-------+------+------+------+------|                    |------+------+------+------+-------+-------.
     * |      |   N   |   R  |   T  |   S  |   G  |                    |   K  |   M  |   E  |   I  |   A   |       |
     * |      |       |      |      |      |      |-------.    ,-------|      |      |      |      |       |       |
     * `------+-------+------+------+------+------|       |    |       |------+------+------+------+-------+-------'
     *        |   X   |   J  |   P  |   C  |   V  |-------|    |-------|   Z  |   H  |   ,  |   .  |       |
     *        |       | LAlt |LShift| LCtrl|      |       |    |       |      |RCtrl |RShift| LAlt | RAlt  |
     *        `-----------------------------------/       /     \       \----------------------------------'
     *                       |   NAV  | Space  | /  NUM  /       \ SYM   \ |   SFT  |  DIA  |
     *                       |   NAV  |        |/  NUM  /         \ SYM   \|        |  DEF  |
     *                       `--------'--------'-------'           '-------'--------'-------'
     */
    [L_BASE] = LAYOUT(
                        KC_Q, KC_L, KC_D, KC_W, KC_B,                      KC_Y, KC_F, KC_O, KC_U, ML_MOUSE,
               XXXXXXX, KC_N, KC_R, KC_T, KC_S, KC_G,                      KC_K, KC_M, KC_E, KC_I, KC_A, XXXXXXX,
KC_X, LALT_T(KC_J), LSFT_T(KC_P), LCTL_T(KC_C), KC_V, XXXXXXX,    XXXXXXX, KC_Z, RCTL_T(KC_H), RSFT_T(KC_COMM), LALT_T(KC_DOT), KC_RALT,
                         LT_SWITCH_NAV, KC_SPC, LT_SWITCH_NUM,    LT_SWITCH_SYM, LT_SWITCH_SFT, LT_SWITCH_DIA
    ),
    /*
     * QWERTY
     *        ,-----------------------------------.                    ,-----------------------------------.
     *        |   Q   |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  | Mouse |
     * ,------+-------+------+------+------+------|                    |------+------+------+------+-------+-------.
     * |      |   A   |   S  |   D  |   F  |   G  |                    |   H  |   J  |   K  |   L  |   P   |       |
     * |      |       |      |      |      |      |-------.    ,-------|      |      |      |      |       |       |
     * `------+-------+------+------+------+------|       |    |       |------+------+------+------+-------+-------'
     *        |   Z   |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |       |
     *        | RAlt  | LAlt |LShift| LCtrl|      |       |    |       |      |RCtrl |RShift| LAlt | RAlt  |
     *        `-----------------------------------/      /      \      \-----------------------------------'
     *                       |   NAV  | Space  | /  NUM /        \ SYM  \ |   SFT  |   DIA  |
     *                       |   NAV  |        |/  NUM /          \ SYM  \|        |        |
     *                       `--------'--------'------'            '------'--------'--------'
     */
    [L_QWERTY] = LAYOUT(
                                KC_Q, KC_W, KC_E, KC_R, KC_T,                       KC_Y, KC_U, KC_I, KC_O, _______,
                       XXXXXXX, KC_A, KC_S, KC_D, KC_F, KC_G,                       KC_H, KC_J, KC_K, KC_L, KC_P, XXXXXXX,
RALT_T(KC_Z), LALT_T(KC_X), LSFT_T(KC_C), LCTL_T(KC_V), KC_B, _______,     _______, KC_N, RCTL_T(KC_M), RSFT_T(KC_COMM), LALT_T(KC_DOT), KC_RALT,
                                            _______, _______, _______,     _______, _______, _______
    ),
    /*
     * COLEMAK-DH
     * https://colemakmods.github.io/
     *        ,-----------------------------------.                    ,------------------------------------.
     *        |   Q   |   W  |   F  |   P  |   B  |                    |   J  |   L  |   U   |   Y  | Mouse |
     * ,------+-------+------+------+------+------|                    |------+------+-------+------+-------+-------.
     * |      |   A   |   R  |   S  |   T  |   G  |                    |   M  |   N  |   E   |   I  |   O   |       |
     * |      |       |      |      |      |      |-------.    ,-------|      |      |       |      |       |       |
     * `------+-------+------+------+------+------|       |    |       |------+------+-------+------+-------+-------'
     *        |   Z   |   X  |   C  |   D  |   V  |-------|    |-------|   K  |   H  |   ,   |   .  |       |
     *        | RAlt  | LAlt |LShift| LCtrl|      |       |    |       |      |RCtrl |RShift | LAlt | RAlt  |
     *        `-----------------------------------/       /     \       \-----------------------------------'
     *                       |   NAV  | Space  | /  NUM  /       \ SYM   \ |   SFT  | DIA    |
     *                       |   NAV  |        |/  NUM  /         \ SYM   \|        |        |
     *                       `--------'--------'-------'           '-------'--------'--------'
     */
    [L_COLEMAK_DH] = LAYOUT(
                                KC_Q, KC_W, KC_F, KC_P, KC_B,                      KC_J, KC_L, KC_U, KC_Y, _______,
                       XXXXXXX, KC_A, KC_R, KC_S, KC_T, KC_G,                      KC_M, KC_N, KC_E, KC_I, KC_O, XXXXXXX,
RALT_T(KC_Z), LALT_T(KC_X), LSFT_T(KC_C), LCTL_T(KC_D), KC_V, _______,    _______, KC_K, RCTL_T(KC_H), RSFT_T(KC_COMM), LALT_T(KC_DOT), KC_RALT,
                                            _______, _______, _______,    _______, _______, _______
    ),
    /*
     * NAV
     *  - Arrows | End / Begin | Top / Bottom
     * Left --> Useful with mouse (right hand) + Used with NAV active
     *   - Moving between workspace with one hand (required to be able to use drag and drop)
     *   - Screen scrolling with one hand
     *        ,------------------------------------.                    ,-----------------------------------.
     *        |COMMENT|  MB2 | WH_U |  MB1  | PgUp |                    |  MB5 | Home |  Up  | End  | Mouse |
     * ,------+-------+------+------+-------+------|                    |------+------+------+------+-------+-------.
     * |      | ATab  |  Tab | WH_D | Enter | PgDo |                    |  MB4 | Left | Down | Right| Clip_H |       |
     * |      |       |      |      |       |      |-------.    ,-------|      |      |      |      |       |       |
     * `------+-------+------+------+------ +------|       |    |       |------+------+------+------+-------+-------'
     *        | CTab  | LDesk|Center| RDesk | PSCR |-------|    |-------| Redo | Undo | Copy | Paste| Cut   |
     *        |       | LAlt |LShift| LCtrl |      |       |    |       |      |RCtrl |RShift| LAlt | RAlt  |
     *        `------------------------------------/      /      \      \-----------------------------------'
     *                      |   NAV   | Space  | /  NUM  /        \ SYM  \ |   SFT  | DIA    |
     *                      |   NAV   |        |/  NUM  /          \ SYM  \|        |        |
     *                      `---------'--------'-------'            '------'--------'--------'
     */
    [L_NAV] = LAYOUT(
                     KCU_COMMENT, KC_BTN2, MS_WHLU, KC_BTN1, KC_PGUP,                      KC_BTN5, KC_HOME, KC_UP, KC_END, _______,
                  XXXXXXX, SW_ATAB, KC_TAB, MS_WHLD, KC_ENT, KC_PGDN,                      KC_BTN4, KC_LEFT, KC_DOWN, KC_RGHT, S_CLIP_HISTORY, XXXXXXX,
SW_CTAB, LALT_T(C_LDESK), LSFT_T(S_CENTER), LCTL_T(C_RDESK), KC_PSCR, _______,    _______, C(KC_Y), RCTL_T(C_Z), RSFT_T(C_C), LALT_T(C_V), RALT_T(C_X),
                                                    _______, _______, _______,    _______, _______, _______
    ),



#if defined(POINTING_DEVICE_ENABLE)
    #if defined(PTECHINOS_POINTING_DEVICE_ENABLE)
      /*
       * POINTING DEVICE
       *         ,-----------------------------------.                    ,------------------------------------.
       *         |      |  MB4 |  MB3 |  MB5  |RCPI_U|                    | LCPI_U|  MB5 |  MB3 |  MB4 |       |
       * ,-------|------+------+------+-------+------+                    |-------+------+------+------+--------------.
       * |       | ATab |  MB2 |RScrol|  MB1  |RCPI_D|                    | LCPI_D|  MB1 | LScro|  MB2 | ATab  |      |
       * |       |      |      |      |       |      |-------.    ,-------|       |      |      |      |       |      |
       * `-------+------+------+------+-------+------|       |    |       |-------+------+------+------+--------------'
       *         | Cut  | Paste| Copy | Undo  | Redo |-------|    |-------|  Redo | Undo | Copy | Paste| Cut   |
       *         | RAlt | LAlt |LShift| LCtrl |      |       |    |       |       |RCtrl |RShift| LAlt | RAlt  |
       *         `-----------------------------------/      /      \      \------------------------------------'
       *                      |   NAV   | Space  | /  NUM  /        \ SYM  \ |  Enter | DEF    |
       *                      |   NAV   |        |/  NUM  /          \ SYM  \|        |        |
       *                      `---------'--------'-------'            '------'--------'--------'
       */
      [L_POINTER] = LAYOUT(
                        XXXXXXX, KC_BTN4, KC_BTN3, KC_BTN5, PR_CPI_UP,                      PL_CPI_UP, KC_BTN5, KC_BTN3, KC_BTN4, _______,
        XXXXXXX, SW_ATAB, KC_BTN2, PR_DS_TOOGLE, KC_BTN1, PR_CPI_DOWN,                      PL_CPI_DOWN, KC_BTN1, PL_DS_TOOGLE, KC_BTN2, SW_ATAB, XXXXXXX,
          RALT_T(C_X), LALT_T(C_V), LSFT_T(C_C), LCTL_T(C_Z), C(KC_Y), _______,    _______, C(KC_Y), RCTL_T(C_Z), RSFT_T(C_C), LALT_T(C_V), RALT_T(C_X),
                                                     _______, _______, _______,    _______, _______, _______
    ),
      #else
      [L_POINTER] = LAYOUT(
                 XXXXXXX, KC_BTN4, KC_BTN3, KC_BTN5, XXXXXXX,                      XXXXXXX, KC_BTN5, KC_BTN3, KC_BTN4, _______,
        XXXXXXX, SW_ATAB, KC_BTN2, XXXXXXX, KC_BTN1, XXXXXXX,                      XXXXXXX, KC_BTN1, XXXXXXX, KC_BTN2, SW_ATAB, XXXXXXX,
 RALT_T(C_X), LALT_T(C_V), LSFT_T(C_C), LCTL_T(C_Z), C(KC_Y), _______,    _______, C(KC_Y), RCTL_T(C_Z), RSFT_T(C_C), LALT_T(C_V), RALT_T(C_X),
                                            _______, _______, _______,    _______, _______, _______
    ),
      #endif
#endif
      /*
       * MOUSE
       *        ,------------------------------------.                    ,-----------------------------------.
       *        |       |  MB2 | WH_U |  MB1  | PgUp |                    |  MB5 | Home | MS_U | End  |       |
       * ,------+-------+------+------+-------+------|                    |------+------+------+------+-------+-------.
       * |      | ATab  | WH_L | WH_D |  WH_R | PgDo |                    |  MB4 | MS_L | MS_D | MS_R |Clip_H |       |
       * |      |       |      |      |       |      |-------.    ,-------|      |      |      |      |       |       |
       * `------+-------+------+------+------ +------|       |    |       |------+------+------+------+-------+-------'
       *        |  Acc0 |      |      |       | Acc1 |-------|    |-------| Redo | Undo | Copy | Paste| Cut   |
       *        | RAlt  | LAlt |LShift| LCtrl |      |       |    |       |      |RCtrl |RShift| LAlt | RAlt  |
       *        `------------------------------------/      /      \      \-----------------------------------'
       *                      |   NAV   | Space  | /  NUM  /        \ SYM  \ |   SFT  | DEF    |
       *                      |   NAV   |        |/  NUM  /          \ SYM  \|        |        |
       *                      `---------'--------'-------'            '------'--------'--------'
       */

      [L_MOUSE] = LAYOUT(
                 XXXXXXX, KC_BTN2, KC_WH_U, KC_BTN1, KC_PGUP,                     KC_BTN5, KC_HOME, MS_UP, KC_END, XXXXXXX,
        XXXXXXX, SW_ATAB, KC_WH_L, KC_WH_D, KC_WH_R, KC_PGDN,                     KC_BTN4, MS_LEFT, MS_DOWN, MS_RGHT, S_CLIP_HISTORY, XXXXXXX,
                  MS_ACL0,KC_LALT, KC_LSFT, KC_LCTL, MS_ACL1, _______,   _______, C(KC_Y), RCTL_T(C_Z), RSFT_T(C_C), LALT_T(C_V), RALT_T(C_X),
                                            _______, _______, _______,   _______, _______, _______
    ),
    /* NUM
     * This layer contains
     *   - numbers as a numpad
     *   - F keys with a layout optimize for programming
     * F10 F11 F12 → Commons F keys on the home row
     * 1 2 3 0     → Most used digits on the home row
     * . ,         → Avoid moving back to default layer to tap them
     * £ €         → Generic currencies on the same layer
     *
     *        ,------------------------------------.                    ,-----------------------------------.
     *        |   £   |  F2  |  F3  |  F4  |  F5   |                    |   °  |   7  |   8  |   9  |   0   |
     * ,------+-------+------+------+------+-------|                    |------+------+------+------+-------+------.
     * |      |   F1  |  F10 |  F11 | F12  |  NUM  |                    |   .  |   1  |   2  |   3  |   0   |      |
     * |      |       |      |      |      | PERMA |-------.    ,-------|      |      |      |      |       |      |
     * `------+-------+------+------+------+-------|       |    |       |------+------+------+------+-------+------'
     *        |   €   |  F6  |  F7  |  F8  |  F9   |-------|    |-------|   ,  |   4  |   5  |   6  |   0   |
     *        | RAlt  | LAlt |LShift| LCtrl|       |       |    |       |      | RCtrl|RShift| LAlt | RAlt  |
     *        `------------------------------------/      /      \      \-----------------------------------'
     *                       |   NAV   | Space  | /  NUM /        \ SYM  \ |   SFT  | DEF    |
     *                       |   NAV   |        |/  NUM /          \ SYM  \|        |        |
     *                       `---------'--------'------'            '------'--------'--------'
     */
       [L_NUM] = LAYOUT(
                                     KCU_POUND,  KC_F2, KC_F3, KC_F4, KC_F5,                     KCU_DEGREE, KC_7, KC_8, KC_9, KC_0,
                             XXXXXXX, KC_F1, KC_F10, KC_F11, KC_F12, ML_NUM,                     KC_DOT, KC_1, KC_2, KC_3, KC_0, XXXXXXX,
         RALT_T(C_EURO), LALT_T(KC_F6), LSFT_T(KC_F7), LCTL_T(KC_F8), KC_F9, _______,   _______, KC_COMM, RCTL_T(KC_4), RSFT_T(KC_5), LALT_T(KC_6), RALT_T(KC_0),
                                                           _______, _______, _______,   _______, _______, _______
    ),
    /* DIA
     * This layer contains text related symbols and french diacritics
     * ^… `… '… "…   → left  → Easy to combine with vowels on the right
     * '             → left  → Most common pattern is `Consonant->'->Vowel`
     * " `           → left  → Below and above ' for memonic
     * _             → left  → Used a lot with snake_case naming
     * -             → left  → Same place as in SYM layer
     * ç             → left  → Easy to combine with `a` to get "ça" in french
     * é è           → right → Follow /\ orientation for memonic
     * â û ô         → right → Under respective letters for memonic
     * à             → right → Easy to combine with `l` to get "là" in french
     *        ,------------------------------------.                    ,------------------------------------.
     *        | GREEK |   î  |   `  |   ~  |  `…   |                    |       |   û  |   ô  |   ù  |  MATH |
     * ,------+-------+------+------+------+-------|                    |-------+------+------+------+-------+------.
     * |      |   ^…  |   ê  |   '  |   _  |  "…   |                    |       |   é  |   è  |   à  |   â   |      |
     * |      |       |      |      |      |       |-------.    ,-------|       |      |      |      |       |      |
     * `------+-------+------+------+------+-------|       |    |       |-------+------+------+------+-------+------'
     *        |       |   -  |   "  |   ç  |  '…   |-------|    |-------|   æ   |      |  « “ |  » ” |   œ   |
     *        |       |      |LShift| LCtrl|       |       |    |       |       | RCtrl|RShift|      |       |
     *        `------------------------------------/      /      \      \------------------------------------'
     *                       |   NAV   | Space  | /  NUM /        \ SYM  \ |   SFT  |  DIA    |
     *                       |   NAV   |        |/  NUM /          \ SYM  \|        |  DIA    |
     *                       `---------'--------'------'            '------'--------'---------'
     */
    [L_DIA] = LAYOUT(
                   TO(L_GREEK), C_I_CIR, C_GRV, C_TILD, KC_GRV,                     XXXXXXX, C_U_CIR, C_O_CIR, C_U_GRV, TO(L_MATH),
           XXXXXXX, KC_CIRC, C_E_CIR, C_QUOT, KC_UNDS, KC_DQUO,                     XXXXXXX, C_E_ACUTE, C_E_GRV, C_A_GRV, C_A_CIR, XXXXXXX,
  XXXXXXX, KC_MINUS, LSFT_T(C_DQUOT), LCTL_T(C_C_CED), KC_QUOT, _______,   _______, KCU_AE_LIG, KC_RCTL, RSFT_T(C_FLQUOT), KCU_FRQUOT, KCU_OE_LIG,
                                              _______, _______, _______,   _______, _______, _______
    ),
    /* SYM
     * This layer contains
     *   - symbols with a layout optimize for programming
     *   - access to rarely used symbols (greek letters and unicode symbols)
     * | + - =     → Easy rollin += -= |=, easy repeat for ++ -- == ||, combine with numbers on the right side
     * / \         → Facing each other on each side (/\ memonic)
     * { ( [ ] ) } → Facing each other, easy to roll and repeat
     * : # ;       → Easy to reach and repeat (markdown ##, cpp ::, ocaml ;;)
     * & *         → Not used a lot and rarely repeated
     *             → Move to advanced layers (MATH and GREEK)
     *
     *        ,------------------------------------.                    ,------------------------------------.
     *        | GREEK |   [  |  ]   |  #   |       |                    |   %   |   &  |   *  |   $  |  MATH |
     * ,------+-------+------+------+------+-------|                    |-------+------+------+------+-------+------.
     * |      |   {   |   (  |  )   |  }   |   /   |                    |   \   |  :   |   ;  |   !  |   ?   |      |
     * |      |       |      |      |      |       |-------.    ,-------|       |      |      |      |       |      |
     * `------+-------+------+------+------+-------|       |    |       |-------+------+------+------+-------+------'
     *        |   |   |   -  |  + ÷ |  = × |  ==   |-------|    |-------|       |  @   |   <  |   >  |       |
     *        |       |      |LShift| LCtrl|       |       |    |       |       |RCtrl |RShift|      |       |
     *        `------------------------------------/      /      \      \------------------------------------'
     *                       |   NAV   | Space  | /  NUM /        \ SYM  \ |   SFT  |  DIA    |
     *                       |   NAV   |        |/  NUM /          \ SYM  \|        |  DIA    |
     *                       `---------'--------'------'            '------'--------'---------'
     */
    [L_SYM] = LAYOUT(
                    TO(L_GREEK), KC_LBRC, KC_RBRC, KC_HASH, XXXXXXX,                     KC_PERC, KC_AMPR, KC_ASTR, KC_DLR, TO(L_MATH),
               XXXXXXX, KC_LCBR, KC_LPRN, KC_RPRN, KC_RCBR, KC_SLSH,                     KC_BSLS, KC_COLN, KC_SCLN, KC_EXLM, KC_QUES, XXXXXXX,
          KC_PIPE, KC_MINS, LSFT_T(C_PLUS), LCTL_T(KC_EQL), S_EQ_EQ, _______,   _______, XXXXXXX, RCTL_T(C_AT), RSFT_T(C_LABK), KC_RABK, XXXXXXX,
                                                   _______, _______, _______,   _______, _______, _______
    ),
#if defined(UNICODEMAP_ENABLE)
     /*
     * MATH
     *        ,-----------------------------------.                    ,-----------------------------------.
     *        |   ⊥   |  ≈   |  ∝  |   ∂  |   ≠  |                    |   ∧  |  ∉   |  ∄  |  ∅   |   ∞   |
     * ,------+-------+------+------+------+------|                    |------+------+------+------+-------+-------.
     * |      |   ⊗   |  →  |  ⇒   |  ⇔  |   ∘  |                    |   ⋅  |  ∈   |  ∃   |  ≤   |   ≥   |       |
     * |      |       |      |      |      |      |-------.    ,-------|      |      |      |      |       |       |
     * `------+-------+------+------+------+------|       |    |       |------+------+------+------+-------+-------'
     *        |   ∥   |  ∑   |  ∏   |  ∀   |      |-------|    |-------|  ℕ   | ℤ   |   ℚ  |  ℝ   |  ℂ   |
     *        |       |      |      |      |      |       |    |       |      |      |      |      |       |
     *        `-----------------------------------/      /      \      \-----------------------------------'
     *                       |   NAV  | Space  | /  NUM /        \ SYM  \ |   SFT  | DEF    |
     *                       |   NAV  |        |/  NUM /          \ SYM  \|        |       |
     *                       `--------'--------'------'            '------'--------'--------'
     */
    [L_MATH] = LAYOUT(
                                  UM(M_PERP), UM(M_SIM), UM(M_PROP), UM(M_PARTIAL), UM(M_DIFF),                     UM(M_LOGIC_AND), UM(M_NOT_IN), UM(M_NOT_EXISTS), UM(M_EMPTY), UM(M_INF),
XXXXXXX, UM(M_TENSOR_PRODUCT), UM(M_LARROW), UM(M_IMPLIES), UM(M_EQUIVALENT_TO), UM(M_COMPOSE),                     UM(M_DOT), UM(M_IN), UM(M_EXISTS), UM(M_LOWER_EQ), UM(M_LARGER_EQ), XXXXXXX,
                      UM(M_PARALLEL), UM(M_SUM), UM(M_PRODUCT), UM(M_FORALL), XXXXXXX, _______,            _______, UM(M_NATURAL), UM(M_INTEGER), UM(M_RATIONAL), UM(M_REAL), UM(M_COMPLEXE),
                                                                     _______, _______, _______,            _______, _______, _______
    ),
    /*
     * GREEK (Base on base layer letter positions, letter pronunciation then shape)
     *        ,-----------------------------------.                    ,-----------------------------------.
     *        |  Θ θ |  Λ λ |  Δ δ |  Ω ω |  Β β |                    |  Ψ ψ |  Φ φ |  Ο ο |  Υ υ |       |
     * ,------+-------+------+------+------+------|                    |------+------+------+------+-------+-------.
     * |      |  Ν ν  |  Ρ ρ |  Τ τ |  Σ σ |  Γ γ |                    |  Κ κ |  Μ μ |  Ε ε |  Α α |  Ι ι  |       |
     * |      |       |      |      |      |      |-------.    ,-------|      |      |      |      |       |       |
     * `------+-------+------+------+------+------|       |    |       |------+------+------+------+-------+-------'
     *        |  Ξ ξ  |  Θ θ |  Π π |  Χ χ |      |-------|    |-------|  Ζ ζ |  Η η |      |      |       |
     *        |       |      |LShift|      |      |       |    |       |      |      |RShift|      |       |
     *        `-----------------------------------/      /      \      \-----------------------------------'
     *                       |   NAV  | Space  | /  NUM /        \ SYM  \ |   SFT  | DEF    |
     *                       |   NAV  |        |/  NUM /          \ SYM  \|        |       |
     *                       `--------'--------'------'            '------'--------'--------'
     */
      [L_GREEK] = LAYOUT(
         UP(GQ, S_GQ), UP(GL, S_GL), UP(GD, S_GD), UP(GW, S_GW), UP(GB, S_GB),                     UP(GY, S_GY), UP(GF, S_GF), UP(GO, S_GO), UP(GU, S_GU), XXXXXXX,
XXXXXXX, UP(GN, S_GN), UP(GR, S_GR), UP(GT, S_GT), UP(GS, S_GS), UP(GG, S_GG),                     UP(GK, S_GK), UP(GM, S_GM), UP(GE, S_GE), UP(GA, S_GA), UP(GI, S_GI), XXXXXXX,
              UP(GX, S_GX), UP(GQ, S_GQ), LSFT_T(C_GP), UP(GC, S_GC), XXXXXXX, _______,   _______, UP(GZ, S_GZ), UP(GH, S_GH),  KC_RSFT, XXXXXXX, XXXXXXX,
                                                             _______, _______, _______,   _______, _______, _______
    ),
#endif
    /* ADJUST
     *         ,-----------------------------------.                    ,-------------------------------------.
     *         |      |hue ^ |sat ^ | bri ^|  BRIU |                    | VOLU  | MRWD  | STOP  | MFFD |      |
     * ,-------|------+------+------+------+-------+                    |-------+-------+-------+------+------------.
     * |       |RGB_TO|hue_dn|sat_dn|bri_dn|  BRID |                    | VOLD  | PREV  | PLAY  | NEXT |VOLMUT|     |
     * |       |      |      |      |      |       |-------.    ,-------|       |       |       |      |      |     |
     * `-------+------+------+------+------+-------|       |    |       |-------+-------+-------+------+------------'
     *         |RGB_MO| U_M  |  U_W | U_WC |  U_L  |-------|    |-------| BASE  |QWERTY | DEBUG |RESET |EEPRST|
     *         |      |      |      |      |       |       |    |       |       |       |       |      |      |
     *         `-----------------------------------/      /      \      \-------------------------------------'
     *                       |         |        | /      /        \      \ |        |   DEF     |
     *                       |         |        |/      /          \      \|        |           |
     *                       `---------'--------'------'            '------'--------'-----------'
     */
      [L_ADJUST] = LAYOUT(
         XXXXXXX, RGB_HUI, RGB_SAI, RGB_VAI, KC_BRIU,                         KC_VOLU, KC_MRWD, KC_MEDIA_STOP, KC_MFFD, XXXXXXX,
XXXXXXX, RGB_TOG, RGB_HUD, RGB_SAD, RGB_VAD, KC_BRID,                         KC_VOLD, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, XXXXXXX,
           RGB_MOD, UC_MAC, UC_WIN, UC_WINC, UC_LINX, XXXXXXX,       XXXXXXX, DF(L_BASE), DF(L_QWERTY), QK_DEBUG_TOGGLE, QK_BOOT, EE_CLR,
                                    XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX, ML_BASE
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
 *        |-------|      |    ESCAPE   |      |                    |      |     RESET    |      |------|
 * ,------+-------+------+------+------+------|                    |------+-------+------+------+------+------.
 * |      |       |      |     TAB  COMMENT   |-------.    ,-------|     CAPS    BACK   DEL     |      |      |
 * `------+-------+------+------+------+------|       |    |       |------+-------+------+------+------+------'
 *        |       |    GUI      |      |      |-------|    |-------|      |       |     GUI     |      |
 *        `-----------------------------------/      /      \      \-----------------------------------'
 *                     |        |          | / ADJ- /        \ -UST \ |        |        |
 *                     |        |          |/      /          \      \|        |        |
 *                     `-------------------'------'            '------'-----------------'
 */

uint16_t get_combo_term(uint16_t index, combo_t* combo) {
    switch (index) {
        // Default
        case comment:
        case caps:
            return COMBO_TERM;
        // Tight combos
        case escape_l:
        case reset:
        case tab:
        case back:
        case del:
            return COMBO_TERM / 2;
        // Modifier combos
        case gui_l:
        case gui_r:
            return COMBO_TERM + 20;
        // Two hands combos
        case adjust:
            return COMBO_TERM + 20;
        // // Vertical combos
        // case curly_lb: // { “
        // case curly_rb: // } ”
        // case round_lb:
        // case round_rb:
        // case square_lb: // [ «
        // case square_rb: // ] »
        //     return COMBO_TERM + 40;
        default:
            return COMBO_TERM;
    }
}

bool get_combo_must_tap(uint16_t index, combo_t* combo) {
    switch (index) {
        case gui_l:
        case gui_r:
        case back:
        case del:
            // Quick roll is allowed
            return false;
        // case curly_l:
        // case curly_r:
        // case round_l:
        // case round_r:
        // case square_l:
        // case square_r:
        //     // Quick roll is allowed to avoid putting letters inside
        //     return false;
        case tab:
        case caps:
        case escape_l:
        case comment:
        case adjust:
        default:
            // Roll is part of the typing process and combo should not make it harder
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
bool swapper_ctab_active = false;

// Custom layer switchers
switcher_state switcher_shift_state  = os_up_unqueued;
switcher_state switcher_sym_state    = os_up_unqueued;
switcher_state switcher_dia_state    = os_up_unqueued;
switcher_state switcher_num_state    = os_up_unqueued;
switcher_state switcher_nav_state    = os_up_unqueued;
layer_state_t  switcher_layer_backup = 0;

bool is_oneshot_cancel_key(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case TO(0):
        case ML_BASE:
        case ML_ADJUST:
        case ML_MOUSE:
        case KC_ESC:
            return true;
        case RSFT_T(ML_BASE):
        case LSFT_T(ML_BASE):
        case LALT_T(ML_BASE):
            // Pressed and tap
            return record->tap.count;
        default:
            return false;
    }
}

bool is_oneshot_layer_cancel_key(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case TO(0):
        case ML_BASE:
        case ML_NUM:
        case ML_ADJUST:
        case ML_MOUSE:
        case SWITCH_NAV:
        case SWITCH_SYM:
        case SWITCH_NUM:
        case SWITCH_DIA:
        case LT_SWITCH_NAV:
        case LT_SWITCH_SYM:
        case LT_SWITCH_NUM:
        case LT_SWITCH_DIA:
        case KC_ESC:
            return true;
        case RSFT_T(ML_BASE):
        case LSFT_T(ML_BASE):
        case LALT_T(ML_BASE):
            // Pressed and tap
            return record->tap.count;
        default:
            return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        // Modifiers
        case QK_MODS ... QK_MODS_MAX:
        // Mod taps
        case QK_MOD_TAP ... QK_MOD_TAP_MAX:
            // Holds
            return !record->tap.count;

        // Layers
        case SWITCH_NAV:
        case SWITCH_SYM:
        case SWITCH_NUM:
        case SWITCH_DIA:
        case LT_SWITCH_NAV:
        case LT_SWITCH_SYM:
        case LT_SWITCH_NUM:
        case LT_SWITCH_DIA:
            return true;
        default:
            return false;
    }
}

bool is_oneshot_layer_ignored_press(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        // Some modifiers
        case KC_RIGHT_ALT:
        case KC_LEFT_ALT:
            // Holds
            return !record->tap.count;
        // Mod taps
        case QK_MOD_TAP ... QK_MOD_TAP_MAX:
            // Holds
            return !record->tap.count;
        default:
            return false;
    }
}

//
// ┌─────────────────────────────────────────────────┐
// │ CUSTOM KEYCODE HANDLING                             │
// └─────────────────────────────────────────────────┘
//

void clear_keyboard_state(void) {
    // Reset caps word
    caps_word_off();
    // Force modifiers to cancel (should not be neccessary but just to be safe)
    clear_mods();
    clear_weak_mods();

#if defined(POINTING_DEVICE_ENABLE) && defined(PTECHINOS_AUTO_MOUSE_ENABLE)
    // Force end of mouse layer
    auto_mouse_set_inactive();
#endif
}

void post_process_record_user(uint16_t keycode, keyrecord_t* record) {
    update_oneshot(&switcher_shift_state, KC_LSFT, LT_SWITCH_SFT, keycode, record);

    // Layer off is delayed to let QMK handle the keycode before leaving the layer
    // However the layer will still be active when the next process_record_user will be called
    // resulting in incorrect layer state for custom keycode handling
    // fg:
    // Without custom post_process_record_user
    //  - layer off --> tap(LT_SWITCH_DIA)       --> layer active
    //  - layer on  --> tap(m)                   --> layer active --> é
    //  - layer on  --> tap(e)                   --> layer off    --> è
    //  - layer off --> tap(e)                   --> layer off    --> e
    // Handle any pending layer_off in post_process_record_user
    //  - layer off --> tap(LT_SWITCH_DIA)       --> layer active
    //  - layer on  --> post_process_record_user --> layer off
    //  - layer on  --> tap(m)                   --> layer active --> é
    //  - layer off --> tap(e)                   --> layer off    --> e
    update_oneshot_layer(&switcher_sym_state, L_SYM, LT_SWITCH_SYM, keycode, record);
    update_oneshot_layer(&switcher_dia_state, L_DIA, LT_SWITCH_DIA, keycode, record);
    update_oneshot_layer(&switcher_num_state, L_NUM, LT_SWITCH_NUM, keycode, record);
}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    // dprintf("Keycode %d --> Is Tap: %d\n", keycode,  record->tap.count);

    // Swapper on one key (no timer)
    update_swapper(&swapper_atab_active, KC_LALT, KC_TAB, SW_ATAB, keycode, record);
    update_swapper(&swapper_ctab_active, KC_LCTL, KC_TAB, SW_CTAB, keycode, record);

    // Custom mods (no timer)
    update_oneshot(&switcher_shift_state, KC_LSFT, LT_SWITCH_SFT, keycode, record);

    // Custom layer change (no timer)
    update_oneshot_layer(&switcher_sym_state, L_SYM, LT_SWITCH_SYM, keycode, record);
    update_oneshot_layer(&switcher_dia_state, L_DIA, LT_SWITCH_DIA, keycode, record);
    update_oneshot_layer(&switcher_num_state, L_NUM, LT_SWITCH_NUM, keycode, record);

    update_move_hold_layer(&switcher_nav_state, L_NAV, LT_SWITCH_NAV, keycode, record, &switcher_layer_backup);

    // Custom keycodes
    bool    let_qmk_handle_it = true;
    uint8_t mods              = get_mods() | get_weak_mods() | get_oneshot_mods();
    bool    shiftPressed      = is_caps_word_on() ^ (is_mod_active(mods, MOD_LSFT) || is_mod_active(mods, MOD_LSFT));
    // dprintf("Keycode: 0x%04X | Mods: 0x%02X | ShiftPressed: %s\n", keycode, mods, shiftPressed ? "true" : "false");

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
        case C_E_ACUTE: // é
            if (record->event.pressed) {
                if (shiftPressed)
                    tap_code16(S(RALT(KC_E)));
                else
                    tap_code16(RALT(KC_E));
                let_qmk_handle_it = false;
            }
            break;
        case C_A_GRV: // à
            if (record->event.pressed) {
                tap_with_dead_key_with_mods(KC_GRV, KC_A, 0U, shiftPressed);
                let_qmk_handle_it = false;
            }
            break;
        case C_E_GRV: // è
            if (record->event.pressed) {
                tap_with_dead_key_with_mods(KC_GRV, KC_E, 0U, shiftPressed);
                let_qmk_handle_it = false;
            }
            break;
        case C_U_GRV: // ù
            if (record->event.pressed) {
                tap_with_dead_key_with_mods(KC_GRV, KC_U, 0U, shiftPressed);
                let_qmk_handle_it = false;
            }
            break;
        case C_A_CIR: // â
            if (record->event.pressed) {
                tap_with_dead_key_with_mods(KC_CIRC, KC_A, MOD_MASK_SHIFT, shiftPressed);
                let_qmk_handle_it = false;
            }
            break;
        case C_E_CIR: // ê
            if (record->event.pressed) {
                tap_with_dead_key_with_mods(KC_CIRC, KC_E, MOD_MASK_SHIFT, shiftPressed);
                let_qmk_handle_it = false;
            }
            break;
        case C_I_CIR: // î
            if (record->event.pressed) {
                tap_with_dead_key_with_mods(KC_CIRC, KC_I, MOD_MASK_SHIFT, shiftPressed);
                let_qmk_handle_it = false;
            }
            break;
        case C_O_CIR: // ô
            if (record->event.pressed) {
                tap_with_dead_key_with_mods(KC_CIRC, KC_O, MOD_MASK_SHIFT, shiftPressed);
                let_qmk_handle_it = false;
            }
            break;
        case C_U_CIR: // û
            if (record->event.pressed) {
                tap_with_dead_key_with_mods(KC_CIRC, KC_U, MOD_MASK_SHIFT, shiftPressed);
                let_qmk_handle_it = false;
            }
            break;
        case C_E_TRE: // ë
            if (record->event.pressed) {
                tap_with_dead_key_with_mods(KC_DQUO, KC_E, MOD_MASK_SHIFT, shiftPressed);
                let_qmk_handle_it = false;
            }
            break;
        // Handle normal sequences
        case S_CENTER:
            if (record->event.pressed) {
                // Press Ctrl(K, C) to center the window arround the cursor
                register_code16(KC_LCTL);
                tap_code16(KC_K);
                wait_ms(1);
                tap_code16(KC_C);
                unregister_code16(KC_LCTL);
                let_qmk_handle_it = false;
            }
            break;
        case S_CLIP_HISTORY:
            if (record->event.pressed) {
                // Press Ctrl(K, V), Down to show copy history and select first row
                register_code16(KC_LCTL);
                tap_code16(KC_K);
                wait_ms(1);
                tap_code16(KC_V);
                unregister_code16(KC_LCTL);
                tap_code16(KC_DOWN);
                let_qmk_handle_it = false;
            }
            break;
        case S_EQ_EQ:
            if (record->event.pressed) {
                tap_code16(KC_EQUAL);
                tap_code16(KC_EQUAL);
                let_qmk_handle_it = false;
            }
            break;
        case S_EXLM_EQ:
            if (record->event.pressed) {
                tap_code16(KC_EXLM);
                tap_code16(KC_EQUAL);
                let_qmk_handle_it = false;
            }
            break;
        case S_LESS_EQ:
            if (record->event.pressed) {
                tap_code16(S(KC_COMMA));
                tap_code16(KC_EQUAL);
                let_qmk_handle_it = false;
            }
            break;
        case S_GREATER_EQ:
            if (record->event.pressed) {
                tap_code16(S(KC_DOT));
                tap_code16(KC_EQUAL);
                let_qmk_handle_it = false;
            }
            break;
        case S_RIGHT_ARROW:
            if (record->event.pressed) {
                tap_code16(KC_MINS);
                tap_code16(S(KC_DOT));
                let_qmk_handle_it = false;
            }
            break;
        // https://docs.qmk.fm/#/mod_tap?id=intercepting-mod-taps
        // Intercept to send key with modifier on tap
        // Shortcuts
        case RCTL_T(C_Z):
        case LCTL_T(C_Z):
            // Allow repeat action on OS
            if (record->tap.count) {
                if (record->event.pressed) {
                    register_code16(C(KC_Z));
                } else {
                    unregister_code16(C(KC_Z));
                }
                let_qmk_handle_it = false;
            }
            break;
        case RALT_T(C_X):
            if (record->tap.count && record->event.pressed) {
                tap_code16(C(KC_X));
                let_qmk_handle_it = false;
            }
            break;
        case LALT_T(C_V):
            if (record->tap.count && record->event.pressed) {
                tap_code16(C(KC_V));
                let_qmk_handle_it = false;
            }
            break;
        case RSFT_T(C_C):
        case LSFT_T(C_C):
            if (record->tap.count && record->event.pressed) {
                tap_code16(C(KC_C));
                let_qmk_handle_it = false;
            }
            break;
        case LALT_T(C_LDESK):
            if (record->tap.count && record->event.pressed) {
                tap_code16(KCU_LEFT_DESK);
                let_qmk_handle_it = false;
            }
            break;
        case LCTL_T(C_RDESK):
            if (record->tap.count && record->event.pressed) {
                tap_code16(KCU_RIGHT_DESK);
                let_qmk_handle_it = false;
            }
            break;
        case LSFT_T(S_CENTER):
            if (record->tap.count && record->event.pressed) {
                // Press Ctrl(K, C) to center the window arround the cursor
                register_code16(KC_LCTL);
                tap_code16(KC_K);
                wait_ms(1);
                tap_code16(KC_C);
                unregister_code16(KC_LCTL);
                let_qmk_handle_it = false;
            }
            break;
        // Caps word
        case RALT_T(C_CW):
            if (record->tap.count && record->event.pressed) {
                caps_word_on();
                let_qmk_handle_it = false;
            }
            break;
#if defined(KEY_OVERRIDE_ENABLE)
        // Overrides
        case RCTL_T(KC_LBRC):
            // Allow repeat action on OS
            if (record->tap.count) {
                if (record->event.pressed) {
                    register_code16(KC_LBRC);
                } else {
                    unregister_code16(KC_LBRC);
                }
                let_qmk_handle_it = false;
            }
            break;
        case RSFT_T(KC_RBRC):
            // Allow repeat action on OS
            if (record->tap.count) {
                if (record->event.pressed) {
                    register_code16(KC_RBRC);
                } else {
                    unregister_code16(KC_RBRC);
                }
                let_qmk_handle_it = false;
            }
            break;
#endif
        // Non latin letters
        case LCTL_T(C_C_CED):
        case RCTL_T(C_C_CED):
            // Allow repeat action on OS
            if (record->tap.count) {
                if (record->event.pressed) {
                    register_code16(KCU_C_CEDILLA);
                } else {
                    unregister_code16(KCU_C_CEDILLA);
                }
                let_qmk_handle_it = false;
            }
            break;
#if defined(UNICODEMAP_ENABLE)
        case LSFT_T(C_GP):
        case RSFT_T(C_GP):
            if (record->tap.count && record->event.pressed) {
                process_unicodemap(UP(GP, S_GP), record);
                let_qmk_handle_it = false;
            }
            break;
#endif
        // Symbols
        case RSFT_T(C_LABK):
            // Allow repeat action on OS
            if (record->tap.count) {
                if (record->event.pressed) {
                    register_code16(KC_LABK);
                } else {
                    unregister_code16(KC_LABK);
                }
                let_qmk_handle_it = false;
            }
            break;
        case RCTL_T(C_AT):
            // Allow repeat action on OS
            if (record->tap.count) {
                if (record->event.pressed) {
                    register_code16(KC_AT);
                } else {
                    unregister_code16(KC_AT);
                }
                let_qmk_handle_it = false;
            }
            break;
        case RSFT_T(C_FLQUOT):
            // Allow repeat action on OS
            if (record->tap.count) {
                if (record->event.pressed) {
                    register_code16(KCU_FLQUOT);
                } else {
                    unregister_code16(KCU_FLQUOT);
                }
                let_qmk_handle_it = false;
            }
            break;
        case LSFT_T(C_DQUOT):
        case RSFT_T(C_DQUOT):
            if (record->tap.count && record->event.pressed) {
                TAP_DOUBLE_QUOTE
                let_qmk_handle_it = false;
            }
            break;
        case LSFT_T(C_PLUS):
            // Allow repeat action on OS
            if (record->tap.count) {
                if (record->event.pressed) {
                    register_code16(KC_PLUS);
                } else {
                    unregister_code16(KC_PLUS);
                }
                let_qmk_handle_it = false;
            }
            break;
        case RALT_T(C_QUOT):
            if (record->tap.count && record->event.pressed) {
                TAP_SIMPLE_QUOTE;
                let_qmk_handle_it = false;
            }
            break;
        case RALT_T(C_EURO):
            if (record->tap.count && record->event.pressed) {
                tap_code16(KCU_EURO);
                let_qmk_handle_it = false;
            }
            break;
        case RALT_T(C_POUND):
            if (record->tap.count && record->event.pressed) {
                tap_code16(KCU_POUND);
                let_qmk_handle_it = false;
            }
            break;
        case RALT_T(KC_PIPE):
            // Allow repeat action on OS
            if (record->tap.count) {
                if (record->event.pressed) {
                    register_code16(KC_PIPE);
                } else {
                    unregister_code16(KC_PIPE);
                }
                let_qmk_handle_it = false;
            }
            break;
            break;
        // Custom layer handling (hold and tap)
        case SWITCH_NAV:
        case SWITCH_SYM:
        case SWITCH_NUM:
        case SWITCH_DIA:
        case SWITCH_SFT:
        case LT_SWITCH_NAV:
        case LT_SWITCH_SYM:
        case LT_SWITCH_NUM:
        case LT_SWITCH_DIA:
        case LT_SWITCH_SFT:
            let_qmk_handle_it = false;
            break;
        case ML_NUM:
            if (record->event.pressed) {
                layer_move(L_NUM);
                let_qmk_handle_it = false;
            }
            break;
        case LSFT_T(ML_BASE):
        case LALT_T(ML_BASE):
        case RSFT_T(ML_BASE):
            // Intercept a press
            if (record->tap.count && record->event.pressed) {
                // Back to HOME layer
                layer_move(0);
                clear_keyboard_state();
                let_qmk_handle_it = false;
            }
            break;
        case ML_MOUSE:
            // Intercept a press
            if (record->event.pressed) {
                layer_move(L_MOUSE);
                clear_keyboard_state();
                let_qmk_handle_it = false;
            }
            break;
        case ML_BASE:
            // Intercept a press
            if (record->event.pressed) {
                // Back to HOME layer
                layer_move(0);
                clear_keyboard_state();
                let_qmk_handle_it = false;
            }
            break;
        case ML_ADJUST:
            // Intercept a press
            if (record->event.pressed) {
                // Go to ADJUST layer
                layer_move(L_ADJUST);
                clear_keyboard_state();
                let_qmk_handle_it = false;
            }
            break;
    }

#if defined(POINTING_DEVICE_ENABLE) && defined(PTECHINOS_AUTO_MOUSE_ENABLE)
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
#if defined(CAPS_WORD_ENABLE)
bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
        // Diacritics
        case RALT(KC_Z):
        case RALT(KC_K):
        case RALT(KC_COMM):
            add_weak_mods(MOD_BIT(KC_LSFT)); // Apply shift to next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
        case KC_MINS:
        case KC_CIRC:
        // Diacritics
        case KC_GRV:
        case KC_DQUO:
        case KC_QUOT:
            return true;

        // Changing layers continue Caps Word, without shifting.
        // Except when moving back to default layer
        case SWITCH_NAV:
        case SWITCH_SYM:
        case SWITCH_NUM:
        case SWITCH_DIA:
        case LT_SWITCH_NAV:
        case LT_SWITCH_SYM:
        case LT_SWITCH_NUM:
        case LT_SWITCH_DIA:
            return true;
        default:
            return false; // Deactivate Caps Word.
    }
}
#endif

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
        case MT(MOD_RSFT, KC_ENT):
        case MT(MOD_LSFT, KC_ENT):
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
        case LCTL_T(C_RDESK):
        case RSFT_T(ML_BASE):
        case LSFT_T(ML_BASE):
        case LALT_T(ML_BASE):
            // Hold
            return true;
        default:
            // Do not select the hold action until another key is tapped.
            return false;
    }
}
#endif

//
// ┌─────────────────────────────────────────────────┐
// │ AUTO MOUSE (PTECHINOS)                              │
// └─────────────────────────────────────────────────┘
//

#if defined(POINTING_DEVICE_ENABLE) && defined(PTECHINOS_AUTO_MOUSE_ENABLE)
void pointing_device_init_user(void) {
    auto_mouse_set_layer(L_POINTER);
    auto_mouse_set_enabled(true);
}

bool auto_mouse_should_exit_user(uint16_t keycode, keyrecord_t* record) {
    bool should_exit = false;
    switch (keycode) {
        // Switching a layer should terminate the auto mouse layer
        case SWITCH_NAV:
        case SWITCH_SYM:
        case SWITCH_NUM:
        case SWITCH_DIA:
        case LT_SWITCH_NAV:
        case LT_SWITCH_SYM:
        case LT_SWITCH_NUM:
        case LT_SWITCH_DIA:
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
    auto_mouse_on_pointing_device_task(&report);
    return report;
}
#        elif defined(POINTING_DEVICE_LEFT)
report_mouse_t pointing_device_task_user(report_mouse_t report) {
    auto_mouse_on_pointing_device_task(&report);
    return report;
}
#        elif defined(POINTING_DEVICE_RIGHT)
report_mouse_t pointing_device_task_user(report_mouse_t report) {
    auto_mouse_on_pointing_device_task(&report);
    return report;
}
#        else
#            error "You need to define the side(s) the pointing device is on. POINTING_DEVICE_COMBINED / POINTING_DEVICE_LEFT / POINTING_DEVICE_RIGHT"
#        endif
#    else
report_mouse_t pointing_device_task_user(report_mouse_t report) {
    if (!is_keyboard_master()) return report;

    auto_mouse_on_pointing_device_task(&report);
    return report;
}
#    endif

void auto_mouse_on_layer_inactive(auto_mouse_data_t* context) {
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
// │ KEY OVERRIDES                                               │
// └─────────────────────────────────────────────────┘
//
#if defined(KEY_OVERRIDE_ENABLE)
// {}
const key_override_t seven_key_override  = ko_make_basic(MOD_MASK_SHIFT, KC_7, KC_LCBR);
const key_override_t height_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_8, KC_RCBR);
// ()
const key_override_t one_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_1, KC_LPRN);
const key_override_t two_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_2, KC_RPRN);
// []
const key_override_t four_key_override = ko_make_basic(MOD_MASK_SHIFT, RCTL_T(KC_4), RCTL_T(KC_LBRC));
const key_override_t five_key_override = ko_make_basic(MOD_MASK_SHIFT, RSFT_T(KC_5), RSFT_T(KC_RBRC));

// This globally defines all key overrides to be used
const key_override_t* key_overrides[] = {&seven_key_override, &height_key_override, &one_key_override, &two_key_override, &four_key_override, &five_key_override};
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

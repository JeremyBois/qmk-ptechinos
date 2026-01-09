#include <stdbool.h>
#include <stdint.h>

#include "keymap_us.h"
#include "modifiers.h"
#include "quantum_keycodes_legacy.h"
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
#include "features/key_utility.h"
#include "g/keymap_combo.h"

#include "features/encoder.h"
#include "features/swapper.h"
#include "features/switcher.h"

#if defined(CAPS_WORD_LOCK_ENABLE)
#    include "features/capsword.h"
#endif

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
     * v7(custom) https://cyanophage.github.io/playground.html?layout=qldfbkuoyj%5Cnrtsg%252Cmeia-xwpcvzh'.
     *  - Bad SFS           --> W_L and F_C and H_U/U_H
     *  - Bad  J'A
     *  - Bad pinky scissor --> WN (rare)
     *  - Good ' on main layer
     *  - Good F on right side feels good for FAI FAU
     *  - Good Better equilibrium (right movement is reduced)
     * v8(custom) https://cyanophage.github.io/playground.html?layout=qldwbkfuo%252C%5Cnrtsgymiea-xjpcvzh'.%253B%252F%5E
     *  - Bad FAU and MAU are not better with pinky scissor removed
     *  - Bad? E on ring seems exhausting (and I also tap top pinky with it already)
     *  - Good Y on home row for MY or .Y
     * v9(custom) https://cyanophage.github.io/playground.html?layout=qldfbkuoy%252C%5Cnrtsgjmeia-xwpcvzh'.%252F%253B%5E
     *  - Good Y above for YOU and MY without alternate typing
     *  - Good J on home row for JE J'A
     *  - Good , is fast to type with ring
     *        ,-----------------------------------.                    ,-----------------------------------.
     *        |   Q   |   L  |   D  |   F  |   B  |                    |  K œ |   U  |   O  |   J  |   ,   |
     * ,------+-------+------+------+------+------|                    |------+------+------+------+-------+-------.
     * | LSft |   N   |   R  |   T  |   S  |   G  |                    |   Y  |   M  |   E  |   I  |   A   |  RSft |
     * | LSft |       |      |      |      |      |-------.    ,-------|      |      |      |      |       |  RSft |
     * `------+-------+------+------+------+------|       |    |       |------+------+------+------+-------+-------'
     *        |   X   |   W  |   P  |   C  |   V  |-------|    |-------|  Z æ |   H  |   '  |   .  |   _   |
     *        |  LGui | LAlt |LShift| LCtrl| RAlt |       |    |       | RAlt |RCtrl |RShift| LAlt | LGui  |
     *        `-----------------------------------/       /     \       \----------------------------------'
     *                       |   NAV  | Space  | /  NUM  /       \ SYM   \ |  Enter |  DIA  |
     *                       |   NAV  |        |/  NUM  /         \ SYM   \|   GUI  |  DEF  |
     *                       `--------'--------'-------'           '-------'--------'-------'
     *
     */
    [L_BASE] = LAYOUT(
                                        KC_Q, KC_L, KC_D, KC_F, KC_B,                      KC_K, KC_U, KC_O, KC_J, KC_COMM,
                               KC_LSFT, KC_N, KC_R, KC_T, KC_S, KC_G,                      KC_Y, KC_M, KC_E, KC_I, KC_A, KC_RSFT,
LGUI_T(KC_X), LALT_T(KC_W), LSFT_T(KC_P), LCTL_T(KC_C), RALT_T(KC_V), XXXXXXX,    XXXXXXX, RALT_T(KC_Z), RCTL_T(KC_H), RSFT_T(C_QUOT), LALT_T(KC_DOT), LGUI_T(C_UNDS),
                                         LT_SWITCH_NAV, KC_SPC, LT_SWITCH_NUM,    LT_SWITCH_SYM, LGUI_T(KC_ENT), LT_SWITCH_DIA
    ),
    /*
     * QWERTY
     *        ,-----------------------------------.                    ,-----------------------------------.
     *        |   Q   |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   _   |
     * ,------+-------+------+------+------+------|                    |------+------+------+------+-------+-------.
     * | LSft |   A   |   S  |   D  |   F  |   G  |                    |   H  |   J  |   K  |   L  |   P   | RSft  |
     * | LSft |       |      |      |      |      |-------.    ,-------|      |      |      |      |       | RSft  |
     * `------+-------+------+------+------+------|       |    |       |------+------+------+------+-------+-------'
     *        |   Z   |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   _   |
     *        | LGui  | LAlt |LShift| LCtrl| RAlt |       |    |       | RAlt |RCtrl |RShift| LAlt | LGui  |
     *        `-----------------------------------/      /      \      \-----------------------------------'
     *                       |   NAV  | Space  | /  NUM /        \ SYM  \ |  Enter |   DIA  |
     *                       |   NAV  |        |/  NUM /          \ SYM  \|   GUI  |        |
     *                       `--------'--------'------'            '------'--------'--------'
     */
    [L_QWERTY] = LAYOUT(
                                        KC_Q, KC_W, KC_E, KC_R, KC_T,                       KC_Y, KC_U, KC_I, KC_O, KC_UNDS,
                               _______, KC_A, KC_S, KC_D, KC_F, KC_G,                       KC_H, KC_J, KC_K, KC_L, KC_P, _______,
LGUI_T(KC_Z), LALT_T(KC_X), LSFT_T(KC_C), LCTL_T(KC_V), RALT_T(KC_B), _______,     _______, RALT_T(KC_N), RCTL_T(KC_M), RSFT_T(KC_COMM), LALT_T(KC_DOT), LGUI_T(C_UNDS),
                                                    _______, _______, _______,     _______, _______, _______
    ),
    /*
     * NAV
     * Activation On the left hand to be used with the mouse
     *   - Workspaces navigation (allow drag and drop of windows)
     *   - Scrolling (View or Mouvement)
     *   - Enter / C-Enter / CS-Enter
     *   - Tab  / A-Tab    / AS-Tab
     * Right hand:
     *   - Fast text navigation (home/end + arrows + Prev/Next)
     *   - Common shortcuts (Undo, Redo, ...)
     *        ,------------------------------------.                    ,-----------------------------------.
     *        |COMMENT| WH_L | WH_U | WH_R  | PgUp |                    |Clip_H| Home |  Up  | End  | Mouse |
     * ,------+-------+------+------+-------+------|                    |------+------+------+------+-------+-------.
     * | LSft | ATab  |  Tab | WH_D | Enter | PgDo |                    |  MB4 | Left | Down | Right|  MB5  | RSft  |
     * | LSft |       |      |      |       |      |-------.    ,-------|      |      |      |      |       | RSft  |
     * `------+-------+------+------+------ +------|       |    |       |------+------+------+------+-------+-------'
     *        | LGui  | LDesk|Center| RDesk | PSCR |-------|    |-------| Redo | Undo | Copy | Paste| Cut   |
     *        | LGui  | LAlt |LShift| LCtrl | RAlt |       |    |       | RAlt |RCtrl |RShift| LAlt | LGui  |
     *        `------------------------------------/      /      \      \-----------------------------------'
     *                      |   NAV   | Space  | /  NUM  /        \ SYM  \ |  Enter | DIA    |
     *                      |   NAV   |        |/  NUM  /          \ SYM  \|   GUI  |        |
     *                      `---------'--------'-------'            '------'--------'--------'
     *
     */
    [L_NAV] = LAYOUT(
                              KCU_COMMENT, MS_WHLL, MS_WHLU, MS_WHLR, KC_PGUP,                      S_CLIP_HISTORY, KC_HOME, KC_UP, KC_END, ML_MOUSE,
                           _______, SW_ATAB, KC_TAB, MS_WHLD, KC_ENT, KC_PGDN,                      MS_BTN4, KC_LEFT, KC_DOWN, KC_RGHT, MS_BTN5, _______,
  KC_LGUI, LALT_T(C_LDESK), LSFT_T(S_CENTER), LCTL_T(C_RDESK), RALT_T(C_PSCR), _______,    _______, RALT_T(C_Y), RCTL_T(C_Z), RSFT_T(C_C), LALT_T(C_V), LGUI_T(C_X),
                                                             _______, _______, _______,    _______, _______, _______
    ),



#if defined(POINTING_DEVICE_ENABLE)
    #if defined(PTECHINOS_POINTING_DEVICE_ENABLE)
      /*
       * POINTING DEVICE
       *         ,------------------------------------.                    ,------------------------------------.
       *         |COMMENT|  MB4 |  MB3 |  MB5  |RCPI_U|                    | LCPI_U|  MB5 |  MB3 |  MB4 |       |
       * ,-------|-------+------+------+-------+------+                    |-------+------+------+------+--------------.
       * | LSft  | ATab  |  MB2 |RScrol|  MB1  |RCPI_D|                    | LCPI_D|  MB1 | LScro|  MB2 | ATab  | RSft |
       * | LSft  |       |      |      |       |      |-------.    ,-------|       |      |      |      |       | RSft |
       * `-------+-------+------+------+-------+------|       |    |       |-------+------+------+------+--------------'
       *         | Cut   | Paste| Copy | Undo  | Redo |-------|    |-------|  Redo | Undo | Copy | Paste| Cut   |
       *         | LGui  | LAlt |LShift| LCtrl | RAlt |       |    |       |  RAlt |RCtrl |RShift| LAlt | LGui  |
       *         `------------------------------------/       /     \      \------------------------------------'
       *                        |   NAV   | Space  | /  NUM  /       \ SYM  \ |  Enter | DIA    |
       *                        |   NAV   |        |/  NUM  /         \ SYM  \|   GUI  | DIA    |
       *                        `---------'--------'-------'           '------'--------'--------'
       */
      [L_POINTER] = LAYOUT(
                        KCU_COMMENT, MS_BTN4, MS_BTN3, MS_BTN5, PR_CPI_UP,                      PL_CPI_UP, MS_BTN5, MS_BTN3, MS_BTN4, XXXXXXX,
            _______, SW_ATAB, MS_BTN2, PR_DS_TOOGLE, MS_BTN1, PR_CPI_DOWN,                      PL_CPI_DOWN, MS_BTN1, PL_DS_TOOGLE, MS_BTN2, SW_ATAB, _______,
          LGUI_T(C_X), LALT_T(C_V), LSFT_T(C_C), LCTL_T(C_Z), RALT_T(C_Y), _______,    _______, RALT_T(C_Y), RCTL_T(C_Z), RSFT_T(C_C), LALT_T(C_V), LGUI_T(C_X),
                                                         _______, _______, _______,    _______, _______, _______
    ),
      #else
      [L_POINTER] = LAYOUT(
                 KCU_COMMENT, MS_BTN4, MS_BTN3, MS_BTN5, XXXXXXX,                      XXXXXXX, MS_BTN5, MS_BTN3, MS_BTN4, XXXXXXX,
            _______, SW_ATAB, MS_BTN2, XXXXXXX, MS_BTN1, XXXXXXX,                      XXXXXXX, MS_BTN1, XXXXXXX, MS_BTN2, SW_ATAB, _______,
 LGUI_T(C_X), LALT_T(C_V), LSFT_T(C_C), LCTL_T(C_Z), RALT_T(C_Y), _______,    _______, RALT_T(C_Y), RCTL_T(C_Z), RSFT_T(C_C), LALT_T(C_V), LGUI_T(C_X),
                                                _______, _______, _______,    _______, _______, _______
    ),
      #endif
#endif
      /*
       * MOUSE
       *        ,------------------------------------.                    ,-----------------------------------.
       *        |COMMENT| WH_L | WH_U |  WH_R | PgUp |                    |Clip_H| Home | MS_U | End  |       |
       * ,------+-------+------+------+-------+------|                    |------+------+------+------+-------+-------.
       * | LSft | ATab  |  MB2 | WH_D |  MB1  | PgDo |                    |  MB4 | MS_L | MS_D | MS_R |  MB5  | RSft  |
       * | LSft |       |      |      |       |      |-------.    ,-------|      |      |      |      |       | RSft  |
       * `------+-------+------+------+------ +------|       |    |       |------+------+------+------+-------+-------'
       *        | LGui  | Acc0 | Acc1 | Acc2  | RAlt |-------|    |-------| Redo | Undo | Copy | Paste| Cut   |
       *        | LGui  | LAlt |LShift| LCtrl | RAlt |       |    |       | RAlt |RCtrl |RShift| LAlt | LGui  |
       *        `------------------------------------/      /      \      \-----------------------------------'
       *                      |   NAV   | Space  | /  NUM  /        \ SYM  \ |  Enter | DIA    |
       *                      |   NAV   |        |/  NUM  /          \ SYM  \|   GUI  | DIA    |
       *                      `---------'--------'-------'            '------'--------'--------'
       */

      [L_MOUSE] = LAYOUT(
                     KCU_COMMENT, MS_WHLL, MS_WHLU, MS_WHLR, KC_PGUP,                     S_CLIP_HISTORY, KC_HOME, MS_UP, KC_END, XXXXXXX,
                _______, SW_ATAB, MS_BTN2, MS_WHLD, MS_BTN1, KC_PGDN,                     MS_BTN4, MS_LEFT, MS_DOWN, MS_RGHT, MS_BTN5, _______,
 KC_LGUI, LALT_T(MS_ACL0), LSFT_T(MS_ACL1), LCTL_T(MS_ACL2), KC_RALT, _______,   _______, RALT_T(C_Y), RCTL_T(C_Z), RSFT_T(C_C), LALT_T(C_V), LGUI_T(C_X),
                                                    _______, _______, _______,   _______, _______, _______
    ),
    /* NUM
     * This layer contains
     *   - numbers as a numpad
     *   - F keys with a layout optimize for programming
     * . ,         → Commons symbols at the same place in both BASE and NUM layer
     * F10 F11 F12 → Debugging keys
     * 1 2 3 0     → Most used digits on the home row
     * £ €         → Generic currencies on the same layer
     * F U         → Common number suffix in programming
     *
     *        ,------------------------------------.                    ,-----------------------------------.
     *        |   F1  |  F2  |  F3  |  F4  |  F5   |                    |   F  |  7 ½ |  8 ¾ |  9   |   ,   |
     * ,------+-------+------+------+------+-------|                    |------+------+------+------+-------+------.
     * | LSft | NUM_P | F10  |  F11 |  F12 | NUM_P |                    |   0  |  4 £ |  5 € |  6 ¼ |   .   | RSft |
     * | LSft |       |      |      |      |       |-------.    ,-------|      |      |      |      |       | RSft |
     * `------+-------+------+------+------+-------|       |    |       |------+------+------+------+-------+------'
     *        |       |  F6  |  F7  |  F8  |  F9   |-------|    |-------|   U  |  1 ¡ |  2 ² |  3 ³ |   _   |
     *        | LGui  | LAlt |LShift| LCtrl|  RAlt |       |    |       | RAlt | RCtrl|RShift| LAlt | LGui  |
     *        `------------------------------------/      /      \      \-----------------------------------'
     *                       |   NAV   | Space  | /  NUM /        \ SYM  \ |  Enter | DEF    |
     *                       |   NAV   |        |/  NUM /          \ SYM  \|   GUI  |        |
     *                       `---------'--------'------'            '------'--------'--------'
     */
       [L_NUM] = LAYOUT(
                                  KC_F1,  KC_F2, KC_F3, KC_F4, KC_F5,                     KC_F, KC_7, KC_8, KC_9, KC_COMM,
                     _______, ML_NUM, KC_F10, KC_F11, KC_F12, ML_NUM,                     KC_0, KC_4, KC_5, KC_6, KC_DOT, _______,
 KC_LGUI, LALT_T(KC_F6), LSFT_T(KC_F7), LCTL_T(KC_F8), RALT_T(KC_F9), _______,   _______, RALT_T(KC_U), RCTL_T(KC_1), RSFT_T(KC_2), LALT_T(KC_3), LGUI_T(C_UNDS),
                                                    _______, _______, _______,   _______, _______, _______
    ),
    /* DIA
     * This layer contains
     *   - text related symbols and french diacritics
     *   - greek letters
     *   - unicode symbols
     * ^… `… '… "…   → left  → Easy to combine with vowels on the right
     * `             → left  → Easier to reach above than below
     * _             → left  → Used a lot with snake_case naming
     * -             → left  → Same place as in SYM layer
     * ç             → left  → Easy to combine with `a` to get "ça" in french
     * é è           → right → Follow /\ orientation for memonic
     * â             → left  → Avoid `t`, `h`, `m` columns
     * û             → right → Avoid `o` column
     * î             → right → Avoid `t`, `g` columns
     * ô             → right → Increase alternation
     * ù             → right → Only in `où` in french --> Roll
     * à             → right → Combine well with `l` or space
     *        ,------------------------------------.                    ,------------------------------------.
     *        |       |   ~  |   `  |   ç  |  `…   |                    | GREEK |   û  |   ô  |   ù  |  MATH |
     * ,------+-------+------+------+------+-------|                    |-------+------+------+------+-------+------.
     * | LSft |   $   |  ^…  |   "  |   #  |  "…   |                    |       |   é  |   è  |   ê  |   â   | RSft |
     * | LSft |       |      |      |      |       |-------.    ,-------|       |      |      |      |       | RSft |
     * `------+-------+------+------+------+-------|       |    |       |-------+------+------+------+-------+------'
     *        |       |   _  |   '  |   à  |  '…   |-------|    |-------|       |      |  « “ |  » ” |   _   |
     *        |  LGui | LAlt |LShift| LCtrl|       |       |    |       |       | RCtrl|RShift| LAlt |  LGui |
     *        `------------------------------------/      /      \      \------------------------------------'
     *                       |   NAV   | Space  | /  NUM /        \ SYM  \ |  Enter |  DIA    |
     *                       |   NAV   |        |/  NUM /          \ SYM  \|   GUI  |  DIA    |
     *                       `---------'--------'------'            '------'--------'---------'
     *
     */
    [L_DIA] = LAYOUT(
                             XXXXXXX, C_TILD, C_GRV, C_C_CED, KC_GRV,                     TO(L_GREEK), C_U_CIR, C_O_CIR, C_U_GRV, TO(L_MATH),
                  _______, KC_DLR, KC_CIRC, C_DQUOT, KC_HASH, KC_DQUO,                     XXXXXXX, C_E_ACUTE, C_E_GRV, C_E_CIR, C_A_CIR, _______,
   KC_LGUI, LALT_T(C_UNDS), LSFT_T(C_QUOT), LCTL_T(C_A_GRV), KC_QUOT, _______,   _______, XXXXXXX, KC_RCTL, RSFT_T(C_FLQUOT), LALT_T(C_FRQUOT), LGUI_T(C_UNDS),
                                                    _______, _______, _______,   _______, _______, _______
    ),
    /* SYM
     * This layer contains
     *   - symbols with a layout optimize for programming
     *   - greek letters
     *   - unicode symbols
     * | + - =     → Easy roll += -= |=, easy repeat for ++ -- == ||, combine with numbers on the right side
     * / \         → Facing each other on each side (/\ memonic)
     * { ( [ ] ) } → Facing each other, easy to roll and repeat
     * : # ;       → Easy to reach and repeat (markdown ##, cpp ::, ocaml ;;)
     * & *         → Not used a lot and rarely repeated
     *             → Move to advanced layers (MATH and GREEK)
     *
     *        ,------------------------------------.                    ,------------------------------------.
     *        |   [   |   {  |   }  |  ]   |   :   |                    | GREEK |   %  |   <  |   >  |  MATH |
     * ,------+-------+------+------+------+-------|                    |-------+------+------+------+-------+------.
     * | LSft |   $   |   (  |  )   |  ;   |   /   |                    |   \   |   &  |   *  |   !  |   ?   | RSft |
     * | LSft |       |      |      |      |       |-------.    ,-------|       |      |      |      |       | RSft |
     * `------+-------+------+------+------+-------|       |    |       |-------+------+------+------+-------+------'
     *        |   |   |   -  |  + ÷ | = ×  |   °   |-------|    |-------|       |   @  |      |      |   _   |
     *        | LGui  | LAlt |LShift| LCtrl|  RAlt |       |    |       |  RAlt |RCtrl |RShift| LAlt |  LGui |
     *        `------------------------------------/      /      \      \------------------------------------'
     *                       |   NAV   | Space  | /  NUM /        \ SYM  \ |  Enter |  DIA    |
     *                       |   NAV   |        |/  NUM /          \ SYM  \|   GUI  |  DIA    |
     *                       `---------'--------'------'            '------'--------'---------'
     *
     */
    [L_SYM] = LAYOUT(
                                KC_LBRC, KC_LCBR, KC_RCBR, KC_RBRC, KC_COLON,                     TO(L_GREEK), KC_PERC, C_LABK, C_RABK, TO(L_MATH),
                               _______, KC_DLR, KC_LPRN, KC_RPRN, KC_SCLN, KC_SLSH,                     KC_BSLS, KC_AMPR, KC_ASTR, KC_EXLM, KC_QUES, _______,
LGUI_T(KC_PIPE), LALT_T(KC_MINS), LSFT_T(C_PLUS), LCTL_T(KC_EQL), RALT_T(C_DEGREE), _______,   _______, KC_RALT, LCTL_T(C_AT), KC_RSFT, KC_LALT, LGUI_T(C_UNDS),
                                                                  _______, _______, _______,   _______, _______, _______
    ),
#if defined(UNICODEMAP_ENABLE)
     /*
     * MATH
     *        ,-----------------------------------.                    ,-----------------------------------.
     *        |   ⊥   |  ≈   |  ∝   |   ∂  |   ≠  |                    |   ∧  |  ∉   |  ∄   |  ∅   |   ∞   |
     * ,------+-------+------+------+------+------|                    |------+------+------+------+-------+-------.
     * | LSft |   ⊗   |  →   |  ⇒   |  ⇔   |   ∘  |                    |   ⋅  |  ∈   |  ∃   |  ≤   |   ≥   | RSft  |
     * | LSft |       |      |      |      |      |-------.    ,-------|      |      |      |      |       | RSft  |
     * `------+-------+------+------+------+------|       |    |       |------+------+------+------+-------+-------'
     *        |   ∥   |  ∑   |  ∏   |  ∀   |      |-------|    |-------|  ℕ   |  ℤ   |   ℚ  |  ℝ   |  ℂ    |
     *        |       |      |      |      |      |       |    |       |      |      |      |      |       |
     *        `-----------------------------------/      /      \      \-----------------------------------'
     *                       |   NAV  | Space  | /  NUM /        \ SYM  \ |  Enter | DEF    |
     *                       |   NAV  |        |/  NUM /          \ SYM  \|   GUI  |        |
     *                       `--------'--------'------'            '------'--------'--------'
     */
    [L_MATH] = LAYOUT(
                                  UM(M_PERP), UM(M_SIM), UM(M_PROP), UM(M_PARTIAL), UM(M_DIFF),                     UM(M_LOGIC_AND), UM(M_NOT_IN), UM(M_NOT_EXISTS), UM(M_EMPTY), UM(M_INF),
_______, UM(M_TENSOR_PRODUCT), UM(M_LARROW), UM(M_IMPLIES), UM(M_EQUIVALENT_TO), UM(M_COMPOSE),                     UM(M_DOT), UM(M_IN), UM(M_EXISTS), UM(M_LOWER_EQ), UM(M_LARGER_EQ), _______,
                               UM(M_PARALLEL), UM(M_SUM), UM(M_PRODUCT), UM(M_FORALL), XXXXXXX, _______,   _______, UM(M_NATURAL), UM(M_INTEGER), UM(M_RATIONAL), UM(M_REAL), UM(M_COMPLEXE),
                                                                              _______, _______, _______,   _______, _______, _______
    ),
    /*
     * GREEK (Base on base layer letter positions, letter pronunciation then shape)
     *        ,-----------------------------------.                    ,-----------------------------------.
     *        |  Θ θ |  Λ λ |  Δ δ |  Ω ω |  Β β  |                    |  Ψ ψ |  Φ φ |  Ο ο |  Υ υ |       |
     * ,------+-------+------+------+------+------|                    |------+------+------+------+-------+-------.
     * | LSft |  Ν ν  |  Ρ ρ |  Τ τ |  Σ σ |  Γ γ |                    |  Κ κ |  Μ μ |  Ε ε |  Α α |  Ι ι  | RSft  |
     * | LSft |       |      |      |      |      |-------.    ,-------|      |      |      |      |       | RSft  |
     * `------+-------+------+------+------+------|       |    |       |------+------+------+------+-------+-------'
     *        |  Ξ ξ  |  Θ θ |  Π π |  Χ χ |      |-------|    |-------|  Ζ ζ |  Η η |      |      |       |
     *        |       |      |LShift|      |      |       |    |       |      |      |RShift|      |       |
     *        `-----------------------------------/      /      \      \-----------------------------------'
     *                       |   NAV  | Space  | /  NUM /        \ SYM  \ |  Enter | DEF    |
     *                       |   NAV  |        |/  NUM /          \ SYM  \|   GUI  |        |
     *                       `--------'--------'------'            '------'--------'--------'
     */
      [L_GREEK] = LAYOUT(
         UP(GQ, S_GQ), UP(GL, S_GL), UP(GD, S_GD), UP(GW, S_GW), UP(GB, S_GB),                     UP(GY, S_GY), UP(GF, S_GF), UP(GO, S_GO), UP(GU, S_GU), XXXXXXX,
_______, UP(GN, S_GN), UP(GR, S_GR), UP(GT, S_GT), UP(GS, S_GS), UP(GG, S_GG),                     UP(GK, S_GK), UP(GM, S_GM), UP(GE, S_GE), UP(GA, S_GA), UP(GI, S_GI), _______,
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
         XXXXXXX, UG_HUEU, UG_SATU, UG_VALU, KC_BRIU,                         KC_VOLU, KC_MRWD, KC_MEDIA_STOP, KC_MFFD, XXXXXXX,
XXXXXXX, UG_TOGG, UG_HUED, UG_SATD, UG_VALD, KC_BRID,                         KC_VOLD, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, XXXXXXX,
           UG_NEXT, UC_MAC, UC_WIN, UC_WINC, UC_LINX, XXXXXXX,       XXXXXXX, DF(L_BASE), DF(L_QWERTY), QK_DEBUG_TOGGLE, QK_BOOT, EE_CLR,
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
 *        |-------|      |    ESCAPE   |      |                    |      |     RESET  CAPS     |------|
 * ,------+-------+------+------+------+------|                    |------+-------+------+------+------+------.
 * |      |       |      |      |      |      |-------.    ,-------|            BACK    DEL     |      |      |
 * `------+-------+------+------+------+------|       |    |       |------+-------+------+------+------+------'
 *        |       |      |      |      |      |-------|    |-------|      |       |      |      |      |
 *        `-----------------------------------/      /      \      \-----------------------------------'
 *                     |        |          | / ADJ- /        \ -UST \ |        |        |
 *                     |        |          |/      /          \      \|        |        |
 *                     `-------------------'------'            '------'-----------------'
 */

uint16_t get_combo_term(uint16_t index, combo_t* combo) {
    switch (index) {
        // Tight combos
        case escape_l:
        case reset:
        case back:
        case del:
        case caps:
            return COMBO_TERM / 2;
        // Two hands combos
        case adjust:
            return COMBO_TERM + 20;
        default:
            return COMBO_TERM;
    }
}

bool get_combo_must_tap(uint16_t index, combo_t* combo) {
    switch (index) {
        case back:
        case del:
        case caps:
            // Quick roll is allowed
            return false;
        case escape_l:
        case reset:
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
// bool swapper_ctab_active = false;

// Custom layer switchers
// switcher_state switcher_shift_state  = os_up_unqueued;
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
        case KC_ESC:
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
            return true;
        case RSFT_T(ML_BASE):
        case LSFT_T(ML_BASE):
        case LALT_T(ML_BASE):
        case LALT_T(ML_NUM):
        case LGUI_T(ML_NUM):
            // Pressed and Released (tapped)
            return record->tap.count;
        default:
            return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
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
        // Modifiers can be used inside the layer if held
        case KC_LEFT_CTRL:
        case KC_LEFT_SHIFT:
        case KC_LEFT_ALT:
        case KC_LEFT_GUI:
        case KC_RIGHT_CTRL:
        case KC_RIGHT_SHIFT:
        case KC_RIGHT_ALT:
        case KC_RIGHT_GUI:
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

bool is_oneshot_delayed_deactivation(uint16_t keycode) {
    switch (keycode) {
        // Extract base keycode out of modified keycode
        // fg: LCTL(KC_2) --> KC_2
        case QK_MODS ... QK_MODS_MAX:
            keycode = QK_MODS_GET_BASIC_KEYCODE(keycode);
            break;
        // Get the base tapping keycode out layer-tap key
        // fg: LT(0, KC_2) --> KC_2
        case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
        case QK_ONE_SHOT_LAYER ... QK_ONE_SHOT_LAYER_MAX:
            keycode = QK_LAYER_TAP_GET_TAP_KEYCODE(keycode);
            break;
        // Get the base tapping keycode out mod-tap key
        // fg: MT(MOD_LSFT, KC_2) --> KC_2
        case QK_MOD_TAP ... QK_MOD_TAP_MAX:
            keycode = QK_MOD_TAP_GET_TAP_KEYCODE(keycode);
            break;
        default:
            break;
    }

    switch (keycode) {
        // No delay when we handle the key manually
        case C_E_ACUTE:
        case C_E_GRV:
        case C_E_CIR:
        case C_E_TRE:
        case C_A_GRV:
        case C_A_CIR:
        case C_U_GRV:
        case C_U_CIR:
        case C_I_CIR:
        case C_O_CIR:
        case C_C_CED:
        case C_TILD:
            return false;
        // Delaying the layer off when QMK is responsible for key handling
        // to make sure OSL is used as reference
        // case KC_GRV:
        // case KC_CIRC:
        // case KC_DQUO:
        // case KC_QUOT:
        default:
            return true;
    }
}

//
// ┌─────────────────────────────────────────────────┐
// │ CUSTOM KEYCODE HANDLING                             │
// └─────────────────────────────────────────────────┘
//
//

void clear_keyboard_state(void) {
// Reset caps word
#if defined(CAPS_WORD_LOCK_ENABLE)
    caps_word_lock_disable();
#endif

#if defined(POINTING_DEVICE_ENABLE) && defined(PTECHINOS_AUTO_MOUSE_ENABLE)
    // Force end of mouse layer
    auto_mouse_set_inactive();
#endif

    // Force modifiers to cancel (should not be neccessary but just to be safe)
    clear_mods_state();
    sync_mods_state();
}

void post_process_record_user(uint16_t keycode, keyrecord_t* record) {
    // update_oneshot(&switcher_shift_state, KC_LSFT, LT_SWITCH_SFT, keycode, record);

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

    // // Get Row / Col indexes
    // int column = record->event.key.col;
    // int row    = record->event.key.row;
    // dprintf("process_record_user - (Row, Col) = (%d, %d)\n", row, column);

#if defined(CAPS_WORD_LOCK_ENABLE)
    process_caps_word_lock(keycode, record);
#endif

    // Swapper on one key (no timer)
    update_swapper(&swapper_atab_active, KC_LALT, KC_TAB, SW_ATAB, keycode, record);
    // update_swapper(&swapper_ctab_active, KC_LCTL, KC_TAB, SW_CTAB, keycode, record);

    // // Custom mods (no timer)
    // update_oneshot(&switcher_shift_state, KC_LSFT, LT_SWITCH_SFT, keycode, record);

    // Custom layer change (no timer)
    update_oneshot_layer(&switcher_sym_state, L_SYM, LT_SWITCH_SYM, keycode, record);
    update_oneshot_layer(&switcher_dia_state, L_DIA, LT_SWITCH_DIA, keycode, record);
    update_oneshot_layer(&switcher_num_state, L_NUM, LT_SWITCH_NUM, keycode, record);

    update_move_hold_layer(&switcher_nav_state, L_NAV, LT_SWITCH_NAV, keycode, record, &switcher_layer_backup);

    // Backup for modifiers
    sync_mods_state();

    // Custom keycodes
    bool let_qmk_handle_it = true;
    switch (keycode) {
        // Non latin letters
        case C_GRV:
            let_qmk_handle_it = !tap_dead_key_sequence(record, keycode, KC_GRV, KC_SPC, MOD_MASK_SHIFT);
            break;
        case C_TILD:
            let_qmk_handle_it = !tap_dead_key_sequence(record, keycode, KC_TILD, KC_SPC, MOD_MASK_SHIFT);
            break;
        case LSFT_T(C_QUOT):
        case RSFT_T(C_QUOT):
        case C_QUOT:
            // Let shift be applied to make it possible to get undead ' or "
            let_qmk_handle_it = !tap_dead_key_sequence(record, keycode, KC_QUOT, KC_SPC, 0u);
            break;
        case C_DQUOT:
        case RSFT_T(C_DQUOT):
            let_qmk_handle_it = !tap_dead_key_sequence(record, keycode, KC_DQUO, KC_SPC, MOD_MASK_SHIFT);
            break;
        case LCTL_T(C_A_GRV): // à
        case C_A_GRV:         // à
            let_qmk_handle_it = !tap_dead_key_sequence(record, keycode, KC_GRV, KC_A, MOD_MASK_SHIFT);
            break;
        case C_E_GRV: // è
            let_qmk_handle_it = !tap_dead_key_sequence(record, keycode, KC_GRV, KC_E, MOD_MASK_SHIFT);
            break;
        case C_U_GRV: // ù
            let_qmk_handle_it = !tap_dead_key_sequence(record, keycode, KC_GRV, KC_U, MOD_MASK_SHIFT);
            break;
        case C_A_CIR: // â
            let_qmk_handle_it = !tap_dead_key_sequence(record, keycode, KC_CIRCUMFLEX, KC_A, MOD_MASK_SHIFT);
            break;
        case C_E_CIR: // ê
            let_qmk_handle_it = !tap_dead_key_sequence(record, keycode, KC_CIRCUMFLEX, KC_E, MOD_MASK_SHIFT);
            break;
        case C_I_CIR:         // î
        case RCTL_T(C_I_CIR): // î
            let_qmk_handle_it = !tap_dead_key_sequence(record, keycode, KC_CIRCUMFLEX, KC_I, MOD_MASK_SHIFT);
            break;
        case C_O_CIR: // ô
            let_qmk_handle_it = !tap_dead_key_sequence(record, keycode, KC_CIRCUMFLEX, KC_O, MOD_MASK_SHIFT);
            break;
        case C_U_CIR: // û
            let_qmk_handle_it = !tap_dead_key_sequence(record, keycode, KC_CIRCUMFLEX, KC_U, MOD_MASK_SHIFT);
            break;
        case C_E_TRE: // ë
            let_qmk_handle_it = !tap_dead_key_sequence(record, keycode, KC_DQUO, KC_E, MOD_MASK_SHIFT);
            break;
        case C_E_ACUTE: // é
            let_qmk_handle_it = !tap_key_with_mods(record, keycode, KC_E, MOD_BIT_RALT);
            break;
        case C_C_CED:         // ç
        case LCTL_T(C_C_CED): // ç
            let_qmk_handle_it = !tap_key_with_mods(record, keycode, KC_COMM, MOD_BIT_RALT);
            break;
        // Sequences
        case S_CENTER:
        case LSFT_T(S_CENTER):
            // Press Ctrl(K, C) to center the window arround the cursor
            let_qmk_handle_it = !tap_two_key_sequence(record, keycode, KC_K, KC_C, MOD_BIT_LCTRL);
            break;
        case S_CLIP_HISTORY:
            // Press Ctrl(K, V) to show copy history
            let_qmk_handle_it = !tap_two_key_sequence(record, keycode, KC_K, KC_V, MOD_BIT_LCTRL);
            break;
        case S_EQ_EQ:
            // ==
            let_qmk_handle_it = !tap_two_key_sequence(record, keycode, KC_EQUAL, KC_EQUAL, 0U);
            break;
        case S_EXLM_EQ:
            // !=
            let_qmk_handle_it = !tap_two_key_sequence(record, keycode, KC_EXLM, KC_EQUAL, 0U);
            break;
        case S_LESS_EQ:
            // <=
            let_qmk_handle_it = !tap_two_key_sequence(record, keycode, S(KC_COMMA), KC_EQUAL, 0U);
            break;
        case S_GREATER_EQ:
            // >=
            let_qmk_handle_it = !tap_two_key_sequence(record, keycode, S(KC_DOT), KC_EQUAL, 0U);
            break;
        case S_RIGHT_FAT_ARROW:
            // =>
            let_qmk_handle_it = !tap_two_key_sequence(record, keycode, KC_EQUAL, S(KC_DOT), 0U);
            break;
        case RALT_T(S_RIGHT_ARROW):
        case S_RIGHT_ARROW:
            // ->
            let_qmk_handle_it = !tap_two_key_sequence(record, keycode, KC_MINS, S(KC_DOT), 0U);
            break;
        case RSFT_T(S_DLEFT_ARROW):
        case S_DLEFT_ARROW:
            // <--
            let_qmk_handle_it = !tap_three_key_sequence(record, keycode, S(KC_COMMA), KC_MINS, KC_MINS, 0U);
            break;
        case LALT_T(S_DRIGHT_ARROW):
        case S_DRIGHT_ARROW:
            // -->
            let_qmk_handle_it = !tap_three_key_sequence(record, keycode, KC_MINS, KC_MINS, S(KC_DOT), 0U);
            break;
        // Shortcuts
        case RALT_T(C_Y):
            let_qmk_handle_it = !tap_key_with_mods(record, keycode, KC_Y, MOD_BIT_LCTRL);
            break;
        case RCTL_T(C_Z):
        case LCTL_T(C_Z):
            let_qmk_handle_it = !tap_key_with_mods(record, keycode, KC_Z, MOD_BIT_LCTRL);
            break;
        case LGUI_T(C_X):
            let_qmk_handle_it = !tap_key_with_mods(record, keycode, KC_X, MOD_BIT_LCTRL);
            break;
        case LALT_T(C_V):
            let_qmk_handle_it = !tap_key_with_mods(record, keycode, KC_V, MOD_BIT_LCTRL);
            break;
        case RSFT_T(C_C):
        case LSFT_T(C_C):
            let_qmk_handle_it = !tap_key_with_mods(record, keycode, KC_C, MOD_BIT_LCTRL);
            break;
        case RALT_T(C_PSCR):
            let_qmk_handle_it = !tap_key_with_mods(record, keycode, KC_PSCR, 0u);
            break;
        case LALT_T(C_LDESK):
            let_qmk_handle_it = !tap_key_with_mods(record, keycode, KC_PAGE_DOWN, MOD_BIT_LGUI);
            break;
        case LCTL_T(C_RDESK):
            let_qmk_handle_it = !tap_key_with_mods(record, keycode, KC_PAGE_UP, MOD_BIT_LGUI);
            break;
            // Caps word
#if defined(CAPS_WORD_LOCK_ENABLE)
        case CW_LOCK_TOGG:
            if (record->event.pressed) {
                // dprintf("Capslock - CW_LOCK_TOGG (enter) - Status : %s\n", is_caps_word_lock_on() ? "on" : "off");
                caps_word_lock_enable();
                // dprintf("Capslock - CW_LOCK_TOGG (exit) - Status : %s\n", is_caps_word_lock_on() ? "on" : "off");
                let_qmk_handle_it = false;
            }
            break;
#endif
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
        case LALT_T(KC_QUES): // ?
            let_qmk_handle_it = !tap_key_with_mods(record, keycode, KC_SLSH, MOD_BIT_LSHIFT);
            break;
        case LALT_T(KC_DLR):  // $
            let_qmk_handle_it = !tap_key_with_mods(record, keycode, KC_4, MOD_BIT_LSHIFT);
            break;
        case C_UNDS:
        case LALT_T(C_UNDS):
        case LGUI_T(C_UNDS):
            let_qmk_handle_it = !tap_key_with_mods(record, keycode, KC_MINS, MOD_BIT_LSHIFT);
            break;
        case C_LABK:
        case LGUI_T(C_LABK):
        case RSFT_T(C_LABK):
            let_qmk_handle_it = !tap_key_with_mods(record, keycode, KC_COMMA, MOD_BIT_LSHIFT);
            break;
        case C_RABK:
        case RALT_T(C_RABK):
        case LALT_T(C_RABK):
            let_qmk_handle_it = !tap_key_with_mods(record, keycode, KC_DOT, MOD_BIT_LSHIFT);
            break;
        case LALT_T(C_AT):
        case LCTL_T(C_AT):
            let_qmk_handle_it = !tap_key_with_mods(record, keycode, KC_2, MOD_BIT_LSHIFT);
            break;
       case RALT_T(C_DEGREE):
            let_qmk_handle_it = !tap_key_with_mods(record, keycode, KC_SCLN, MOD_BIT_LSHIFT | MOD_BIT_RALT);
            break;
        case RALT_T(KC_PERC):
            let_qmk_handle_it = !tap_key_with_mods(record, keycode, KC_5, MOD_BIT_LSHIFT);
            break;
        case LSFT_T(C_PLUS):
            let_qmk_handle_it = !tap_key_with_mods(record, keycode, KC_EQUAL, MOD_BIT_LSHIFT);
            break;
        case LGUI_T(KC_PIPE):
            let_qmk_handle_it = !tap_key_with_mods(record, keycode, KC_BACKSLASH, MOD_BIT_LSHIFT);
            break;
        case RSFT_T(C_FLQUOT):
            let_qmk_handle_it = !tap_key_with_mods(record, keycode, KC_LBRC, MOD_BIT_RALT);
            break;
        case LALT_T(C_FRQUOT):
            let_qmk_handle_it = !tap_key_with_mods(record, keycode, KC_RBRC, MOD_BIT_RALT);
            break;
        case C_EURO: // €
        case RALT_T(C_EURO): // €
        case LGUI_T(C_EURO): // €
            let_qmk_handle_it = !tap_key_with_mods(record, keycode, KC_5, MOD_BIT_RALT);
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
        case LALT_T(ML_NUM):
        case LGUI_T(ML_NUM):
            // Intercept a press
            if (record->tap.count && record->event.pressed) {
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
        case ML_NUM:
            if (record->event.pressed) {
                layer_move(L_NUM);
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
#if defined(CAPS_WORD_LOCK_ENABLE)
void process_caps_word_lock(uint16_t keycode, const keyrecord_t* record) {
    sync_caps_word_lock_on();

    // Update caps word state
    if (is_caps_word_lock_on()) {
        switch (keycode) {
            // Layers can be held or tapped
            case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
                return;
            // Allow to filter modified keycode from its base keycode
            // fg: LCTL(KC_2) --> KC_2
            case QK_MODS ... QK_MODS_MAX:
                break;
            // Get the base tapping keycode out layer-tap key
            // fg: LT(0, KC_2) --> KC_2
            case QK_ONE_SHOT_LAYER ... QK_ONE_SHOT_LAYER_MAX:
                // Earlier return if this has not been considered tapped yet
                if (record->tap.count == 0) {
                    return;
                }
                keycode = QK_LAYER_TAP_GET_TAP_KEYCODE(keycode);
                break;
            // Get the base tapping keycode out mod-tap key
            // fg: MT(MOD_LSFT, KC_2) --> KC_2
            case QK_MOD_TAP ... QK_MOD_TAP_MAX:
                // Earlier return if this has not been considered tapped yet
                if (record->tap.count == 0) {
                    return;
                }
                keycode = QK_MOD_TAP_GET_TAP_KEYCODE(keycode);
                break;
            default:
                break;
        }

        switch (keycode) {
            // Keycodes to shift
            // Custom keycodes
            case C_E_ACUTE:
            case C_E_GRV:
            case C_E_CIR:
            case C_E_TRE:
            case C_A_GRV:
            case C_A_CIR:
            case C_U_GRV:
            case C_U_CIR:
            case C_I_CIR:
            case C_O_CIR:
            case C_C_CED:
            // Letters
            case KC_A ... KC_Z:
                if (record->event.pressed) {
                    if (get_oneshot_mods() & MOD_MASK_SHIFT) {
                        caps_word_lock_disable();
                        add_oneshot_mods(MOD_MASK_SHIFT);
                    }
                }
            // Keycodes that continue caps word but shouldn't get shifted
            case CW_LOCK_TOGG:
            // Movements
            case KC_BSPC:
            case KC_DEL:
            // Numbers
            case KC_1 ... KC_0:
            // Symbols
            case KC_MINS:
            case KC_PIPE:
            case KC_UNDS:
            case C_UNDS:
            // Dead keys for diacritics
            case KC_GRV:
            case KC_CIRCUMFLEX:
            case KC_DQUO:
            case KC_QUOT:
                // If chording mods, disable caps word
                if (record->event.pressed && (get_mods() != MOD_LSFT) && (get_mods() != 0)) {
                    caps_word_lock_disable();
                }
                break;
            // Any other keycode should automatically disable caps
            default:
                if (record->event.pressed && !(get_oneshot_mods() & MOD_MASK_SHIFT)) {
                    caps_word_lock_disable();
                }
                break;
        }
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
    // Immediately select the hold action when another key is tapped (pressed and released)
    // while mod tap key is still pressed down or marked as hold
    // Avoid waiting for tapping term to perform an hold
    // Allow to favor hold earlier than default behavior but not hold_on_other_key_press
    switch (keycode) {
        // Fast mod on thumb
        case MT(MOD_LSFT, KC_ENT):
        case MT(MOD_LGUI, KC_ENT):
        // Avoid side effect if not sure
        case LCTL_T(C_RDESK):
        case LALT_T(C_LDESK):
        case LALT_T(ML_NUM):
        case LGUI_T(ML_NUM):
            return false;
        // Make it possible to quickly tap shortcut with OSL
        case LT_SWITCH_NUM:
        case LT_SWITCH_NAV:
        case LT_SWITCH_SYM:
        case LT_SWITCH_DIA:
            return false;
        // Prefer tap
        case LALT_T(MS_ACL0):
        case LSFT_T(MS_ACL1):
        case LCTL_T(MS_ACL2):
        default:
            break;
    }

    int column = record->event.key.col;
    int row    = record->event.key.row;

    // Bottom row (Left == 2  Right == 6)
    if (row == 2 || row == 6) {
        if (column == 2) {
            // Active permissive hold only for shift
            return true;
        }
    }

    // Do not select the hold action until another key is tapped.
    return false;
}
#endif

#if defined(HOLD_ON_OTHER_KEY_PRESS_PER_KEY)
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t* record) {
    // Immediately select the hold action when another key is pressed down (not waiting for release)
    // while mod tap key is still pressed down or marked as hold
    // Avoid waiting for tapping term to perform an hold
    // Allow to favor hold earlier than permissive hold or default behavior
    switch (keycode) {
        // Avoid side effect if not sure
        case LCTL_T(C_RDESK):
        case LALT_T(C_LDESK):
        case LALT_T(ML_NUM):
        case LGUI_T(ML_NUM):
        // Make it possible to quickly tap shortcut with OSL
        case LT_SWITCH_NUM:
        case LT_SWITCH_NAV:
        case LT_SWITCH_SYM:
        case LT_SWITCH_DIA:
            return false;
        // Prefer tap
        case LALT_T(MS_ACL0):
        case LSFT_T(MS_ACL1):
        case LCTL_T(MS_ACL2):
        default:
            break;
    }

    // Do not select the hold action when another key is tapped.
    return false;
}
#endif


#if defined(FLOW_TAP_TERM)
bool is_flow_tap_key(uint16_t keycode) {
    // Disable Flow Tap on hotkeys
    // if ((get_mods() & (MOD_MASK_CG | MOD_BIT_LALT)) != 0) {
    if (get_mods() != 0) {
        return false;
    }

    // Allow shifting keys during flow
    if ((QK_MOD_TAP_GET_MODS(keycode) & (MOD_LSFT | MOD_RSFT)) != 0)
    {
        return false;
    }

    switch (get_tap_keycode(keycode)) {
        // Default
        case KC_A ... KC_Z:
        case KC_SPC:
        case KC_DOT:
        case KC_COMM:
        case KC_SCLN:
        case KC_SLSH:
            return true;
            break;
        // Diacritics (french)
        case C_E_ACUTE:
        case C_E_GRV:
        case C_E_CIR:
        case C_E_TRE:
        case C_A_GRV:
        case C_A_CIR:
        case C_U_GRV:
        case C_U_CIR:
        case C_I_CIR:
        case C_O_CIR:
        case C_C_CED:
            return true;
            break;
        default:
            break;
    }

    return false;
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

    // Default to mousing mode on right
    ptechinos_set_pointer_as_mousing(PTECHINOS_RIGHT);

    // Default to scrolling mode on left
    ptechinos_set_pointer_as_dragscroll(PTECHINOS_LEFT);
}

bool auto_mouse_should_exit_user(uint16_t keycode, keyrecord_t* record) {
    bool should_exit = false;
    switch (keycode) {
        // Switching a layer should terminate the auto mouse layer
        case TO(0):
        case ML_BASE:
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
            should_exit = true;
            break;
        case RSFT_T(ML_BASE):
        case LSFT_T(ML_BASE):
        case LALT_T(ML_BASE):
            // Pressed and tap
            return record->tap.count;
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
    // Switch to mousing mode on right
    if (ptechinos_is_pointer_dragscroll_enabled(PTECHINOS_RIGHT)) {
        ptechinos_set_pointer_as_mousing(PTECHINOS_RIGHT);
    }
    // Switch to scroll mode on left
    if (ptechinos_is_pointer_mousing_enabled(PTECHINOS_LEFT)) {
        ptechinos_set_pointer_as_dragscroll(PTECHINOS_LEFT);
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

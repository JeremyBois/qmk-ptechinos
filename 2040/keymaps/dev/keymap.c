#include "config.h"
#include "quantum_keycodes.h"

#include QMK_KEYBOARD_H

#include "features/customCodes.h"
#include "g/keymap_combo.h"

#include "features/encoder.h"
#include "features/utility.h"
#include "features/swapper.h"
#include "features/switcher.h"
#include "features/repeat.h"

#ifdef CONSOLE_ENABLE
#    include "print.h"
#endif // CONSOLE_ENABLE

//
// ┌─────────────────────────────────────────────────┐
// │ LAYOUTS                                         │
// └─────────────────────────────────────────────────┘
//
// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * QWERTY
     *        ,-----------------------------------.                    ,-----------------------------------.
     *        |       |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  | PSCR  |
     * ,------+-------+------+------+------+------|                    |------+------+------+------+-------+-------.
     * |  Q   |   A   |   S  |   D  |   F  |   G  |                    |   H  |   J  |   K  |   L  |   P   | MOUSE |
     * |      | Shift |      |      |      |      |-------.    ,-------|      |      |      |      | Shift |       |
     * `------+-------+------+------+------+------| MUTE  |    | PSCR  |------+------+------+------+-------+-------'
     *        |   Z   |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /   |
     *        |       | LALT |      |      |      |       |    |       |      |      |      | LALT  | Ralt  |
     *        `-----------------------------------/      /      \      \-----------------------------------'
     *                       |   NAV  | Space  | /  NUM /        \ SYM  \ |  Enter |  DEF   |
     *                       |   NAV  | LCtrl  |/  NUM /          \ SYM  \|  RCtrl |        |
     *                       `--------'--------'------'            '------'--------'--------'
     */
    [L_DEFAULT] = LAYOUT(
           KC_MUTE, KC_W, KC_E, KC_R, KC_T,      KC_Y, KC_U, KC_I, KC_O, KC_PSCR,
KC_Q, LSFT_T(KC_A), KC_S, KC_D, KC_F, KC_G,      KC_H, KC_J, KC_K, KC_L, RSFT_T(KC_P), TO(_MOUSE),
      KC_Z, LALT_T(KC_X), KC_C, KC_V, KC_B, KC_MUTE,    KC_PSCR, KC_N, KC_M,  KC_COMM, LALT_T(KC_DOT), RALT_T(KC_SLSH),
           SWITCH_NAV, LCTL_T(KC_SPC), SWITCH_NUM,    SWITCH_SYM, RCTL_T(KC_ENT), TO(L_DEFAULT)
    ),

    /*
     * COLEMAK
     * https://colemak.com/
     *        ,-----------------------------------.                    ,-----------------------------------.
     *        |       |   W  |   F  |   P  |   G  |                    |   J  |   L  |   U  |   Y  |       |
     * ,------+-------+------+------+------+------|                    |------+------+------+------+-------+-------.
     * |  Q   |   A   |   R  |   S  |   T  |   D  |                    |   H  |   N  |   E  |   I  |   O   | MOUSE |
     * |      | Shift |      |      |      |      |-------.    ,-------|      |      |      |      | Shift |       |
     * `------+-------+------+------+------+------|  MUTE |    | PSCR  |------+------+------+------+-------+-------'
     *        |   Z   |   X  |   C  |   V  |   B  |-------|    |-------|   K  |   M  |   ,  |   .  |   /   |
     *        |       | LALT |      |      |      |       |    |       |      |      |      | LALT  | Ralt  |
     *        `-----------------------------------/       /     \       \----------------------------------'
     *                       |   NAV  | Space  | /  NUM  /       \ SYM   \ |  Enter |  DEF  |
     *                       |   NAV  | LCtrl  |/  NUM  /         \ SYM   \|  LCtrl |       |
     *                       `--------'--------'-------'           '-------'--------'-------'
     */
    [L_COLEMAK] = LAYOUT(
           KC_MUTE, KC_W, KC_F, KC_P, KC_G,      KC_J, KC_L, KC_U, KC_Y, KC_PSCR,
KC_Q, LSFT_T(KC_A), KC_R, KC_S, KC_T, KC_D,      KC_H, KC_N, KC_E, KC_I, RSFT_T(KC_O), _______,
      KC_Z, LALT_T(KC_X), KC_C, KC_V, KC_B, KC_MUTE,    KC_PSCR, KC_K, KC_M, KC_COMM, LALT_T(KC_DOT), RALT_T(KC_SLSH),
                  _______, _______, _______,    _______, _______, _______
    ),

    /*
     * ErgoL (COLEMAK for english / french)
     * https://ergol.org/
     *        ,------------------------------------.                    ,-----------------------------------.
     *        |       |   O  |   U  |   D   |   W  |                    |   B  |   M  |   F  |   P  |       |
     * ,------+-------+------+------+-------+------|                    |------+------+------+------+-------+-------.
     * |  Q   |   A   |   S  |   R  |   T   |   Y  |                    |   H  |   N  |   E  |   I  |   G   | MOUSE |
     * |      | Shift |      |      |       |      |-------.    ,-------|      |      |      |      | Shift |       |
     * `------+-------+------+------+-------+------|  MUTE |    | PSCR  |------+------+------+------+-------+-------'
     *        |   Z   |   X  |   C  |   V   |   K  |-------|    |-------|   J  |   L  |   ,  |   .  |   /   |
     *        |       | LALT |      |       |      |       |    |       |      |      |      | LALT | Ralt  |
     *        `------------------------------------/      /      \      \-----------------------------------'
     *                       |    NAV  | Space  | /  NUM /        \ SYM  \ |  Enter |  DEF   |
     *                       |    NAV  | LCtrl  |/  NUM /          \ SYM  \|  LCtrl |        |
     *                       `---------'--------'------'            '------'--------'--------'
     */
    [L_ERGOL] = LAYOUT(
              _______, KC_O, KC_U, KC_D, KC_W,      KC_B, KC_M, KC_F, KC_P, _______,
   KC_Q, LSFT_T(KC_A), KC_S, KC_R, KC_T, KC_Y,      KC_H, KC_N, KC_E, KC_I, RSFT_T(KC_G), _______,
 KC_Z, LALT_T(KC_X), KC_C, KC_V, KC_K, KC_MUTE,    KC_PSCR, KC_J, KC_L, KC_COMM, LALT_T(KC_DOT), RALT_T(KC_SLSH),
                     _______, _______, _______,    _______, _______, _______
    ),

    /* NAV
     *        ,------------------------------------.                    ,-----------------------------------.
     *        |       | WH_L |  MU  | WH_R  | PgUp |                    | WH_U | Home |  Up  | End  |       |
     * ,------+-------+------+------+-------+------|                    |------+------+------+------+-------+------.
     * | CTab | ATab  |  ML  |  MD  |  MR   | PgDo |                    | WH_D | Left | Down | Right|  MB4  | MB5  |
     * |      | Shift |      |      |       |      |-------.    ,-------|      |      |      |      | Shift |      |
     * `------+-------+------+------+------ +------|  MUTE |    | PSCR  |------+------+------+------+-------+------'
     *        |  Undo | Cut  | Copy | Paste |LDesk |-------|    |-------|RDesk | MB1  | MB2  | MB3  |  Com  |
     *        |       | LALT |      |       |      |       |    |       |      |      |      | LALT |  Ralt |
     *        `------------------------------------/      /      \      \-----------------------------------'
     *                      |   NAV   | Space  | /  NUM  /        \ SYM  \ |  Enter |  DEF   |
     *                      |   NAV   | LCtrl  |/  NUM  /          \ SYM  \|  LCtrl |        |
     *                      `---------'--------'-------'            '------'--------'--------'
     */
    [L_NAV] = LAYOUT(
                 _______, KC_WH_L, KC_MS_U, KC_WH_R, KC_PGUP,      KC_WH_U, KC_HOME, KC_UP, KC_END, _______,
SW_CTAB, LSFT_T(SW_ATAB), KC_MS_L, KC_MS_D, KC_MS_R, KC_PGDN,      KC_WH_D, KC_LEFT, KC_DOWN, KC_RGHT, RSFT_T(KC_BTN4), KC_BTN5,
           C_Z, LALT_T(C_X), C_C, C_V, C(A(KC_LEFT)), _______,    _______, C(A(KC_RIGHT)), KC_BTN1, KC_BTN2, LALT_T(KC_BTN3), RALT_T(C_SLSH),
                                    _______, _______, _______,    _______, _______, _______

    ),

    /* NUM
     *        ,------------------------------------.                    ,-----------------------------------.
     *        |       |  F6  |  F7  |  F8  |  F9   |                    |  F10 |  F1  |  F2  |  F3  |       |
     * ,------+-------+------+------+------+-------|                    |------+------+------+------+-------+------.
     * |  F5  |   5   |   6  |   7  |   8  |   9   |                    |  0   |   1  |   2  |   3  |   4   |  F4  |
     * |      | Shift |      |      |      |       |-------.    ,-------|      |      |      |      | Shift | RCTRL|
     * `------+-------+------+------+------+-------|  MUTE |    | PSCR  |------+------+------+------+-------+------'
     *        |  Undo | Cut  | Copy |Paste |       |-------|    |-------|  F11 |  F12 |  ,   |  .   |   /   |
     *        |       | LALT |      |      |       |       |    |       |      |      |      | LALT |  Ralt |
     *        `------------------------------------/      /      \      \-----------------------------------'
     *                       |   NAV   | Space  | /  NUM /        \ SYM  \ |  Enter |  DEF   |
     *                       |   NAV   | LCtrl  |/  NUM /          \ SYM  \|  LCtrl |        |
     *                       `---------'--------'------'            '------'--------'--------'
     */
    [_NUM] = LAYOUT(
                     _______, KC_F6, KC_F7, KC_F8, KC_F9,     KC_F10, KC_F1, KC_F2, KC_F3, _______,
 KC_F5,   LSFT_T(KC_5), KC_6,     KC_7,    KC_8,    KC_9,     KC_0,   KC_1,  KC_2,  KC_3, RSFT_T(KC_4), RCTL_T(KC_F4),
 C_Z, LALT_T(C_X),  C_C,  C_V,  XXXXXXX, _______, _______,   KC_F11, KC_F12, KC_COMM, LALT_T(KC_DOT), RALT_T(KC_SLSH),
                                _______, _______, _______,   _______, _______, _______
    ),
    /* SYM
     *
     *        ,------------------------------------.                    ,------------------------------------.
     *        |       |   :  |  #   |  ;   |   `   |                    |   %   |   &  |   *  |   ?  |       |
     * ,------+-------+------+------+------+-------|                    |-------+------+------+------+-------+------.
     * |  °   |   `…  |   à  |  -   |  é   |   /   |                    |   \   |   è  |   '  |   !  |  ^…   |   €  |
     * |      | Shift |      |      |      |       |-------.    ,-------|       |      |      |      | Shift |      |
     * `------+-------+------+------+------+-------|  MUTE |    | PSCR  |-------+------+------+------+-------+------'
     *        |   |   |   =  |  _   |  +   |  "…   |-------|    |-------|  '…   |   @  |   "  |   $  |   ç   |
     *        |       |      |      |      |       |       |    |       |       |      |      |      |       |
     *        `------------------------------------/      /      \      \------------------------------------'
     *                       |   NAV   | Space  | /  NUM /        \ SYM  \ |  Enter |  DEF    |
     *                       |   NAV   | LCtrl  |/  NUM /          \ SYM  \|  LCtrl |         |
     *                       `---------'--------'------'            '------'--------'---------'
     *
     */
    [L_SYM] = LAYOUT(
                       _______, KC_COLN, KC_HASH, KC_SCLN,   C_GRV,     KC_PERC, KC_AMPR, KC_ASTR, KC_QUES, _______,
C_DEG, LSFT_T(KC_GRV), C_A_GRV, KC_MINS, C_E_ACU, KC_SLSH, KC_BSLS,     C_E_GRV, C_QUOT, KC_EXLM, RSFT_T(KC_CIRC), RALT(KC_5),
                KC_PIPE, KC_EQL, KC_UNDS, KC_PLUS, KC_DQUO, _______,   _______, KC_QUOT, KC_AT, C_DQUOT, KC_DLR, C_C_CED,
                                          _______, _______, _______,   _______, _______, _______
    ),
    /* MOUSE
     *         ,-----------------------------------.                    ,-----------------------------------.
     *         |      |      |      |      | RCPI_U|                    | LCPI_U|      |      |      |      |
     * ,-------|------+------+------+------+-------+                    |-------+------+------+------+------------.
     * |       |      |  MB2 |  MB3 |  MB1 | RCPI_D|                    | LCPI_D| MB1  |  MB3 |  MB2 |      |     |
     * |       |      |      |      |      |       |-------.    ,-------|       |      |      |      |      |     |
     * `-------+------+------+------+------+-------|       |    |       |-------+------+------+------+------------'
     *         |      |      |      |      |       |-------|    |-------|       |      |      |      |      |
     *         |      |      |      |      |       |       |    |       |       |      |      |      |      |
     *         `-----------------------------------/      /      \      \-----------------------------------'
     *                       |         | RScroll| /      /        \      \ | LScroll|  DEF    |
     *                       |         |        |/      /          \      \|        |         |
     *                       `---------'--------'------'            '------'--------'---------'
     */
    #if defined(SPLIT_POINTING_ENABLE)
      [_MOUSE] = LAYOUT(
           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, PR_CPI_UP,       PL_CPI_UP, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
XXXXXXX, XXXXXXX, KC_BTN2, KC_BTN3, KC_BTN1, PR_CPI_DOWN,       PL_CPI_DOWN, KC_BTN1, KC_BTN3, KC_BTN2, XXXXXXX, XXXXXXX,
     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                           XXXXXXX, PR_DS_TOOGLE, XXXXXXX,     XXXXXXX, PL_DS_TOOGLE, _______
    ),
      #else
        [_MOUSE] = LAYOUT(
             XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, KC_BTN2, KC_BTN3, KC_BTN1, XXXXXXX,       XXXXXXX, KC_BTN1, KC_BTN3, KC_BTN2, XXXXXXX, XXXXXXX,
     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, _______
          ),
      #endif
    /* ADJUST
     *         ,-----------------------------------.                    ,-----------------------------------.
     *         |      |hue ^ |sat ^ | bri ^|  BRIU |                    | VOLU  | MRWD | STOP | MFFD |      |
     * ,-------|------+------+------+------+-------+                    |-------+------+------+------+------------.
     * |       |      |hue_dn|sat_dn|bri_dn|  BRID |                    | VOLD  | PREV | PLAY | NEXT |EEPRST|RESET|
     * |       |      |      |      |      |       |-------.    ,-------|       |      |      |      |      |     |
     * `-------+------+------+------+------+-------|       |    |       |-------+------+------+------+------------'
     *         |RGB_TO|RGB_MO|      |      |QWERTY |-------|    |-------|COLEMAK|ERGOL |      |      |DEBUG |
     *         |      |      |      |      |       |       |    |       |       |      |      |      |      |
     *         `-----------------------------------/      /      \      \-----------------------------------'
     *                       |         |        | /      /        \      \ |        |  DEF    |
     *                       |         |        |/      /          \      \|        |         |
     *                       `---------'--------'------'            '------'--------'---------'
     */
      [L_ADJUST] = LAYOUT(
             XXXXXXX, RGB_HUI, RGB_SAI, RGB_VAI, KC_BRIU,        KC_VOLU, KC_MRWD, KC_MEDIA_STOP, KC_MFFD, XXXXXXX,
    XXXXXXX, XXXXXXX, RGB_HUD, RGB_SAD, RGB_VAD, KC_BRID,        KC_VOLD, KC_MPRV, KC_MPLY, KC_MNXT, EE_CLR, QK_BOOT,
RGB_TOG, RGB_MOD, XXXXXXX, XXXXXXX, DF(L_DEFAULT), XXXXXXX,      XXXXXXX, DF(L_COLEMAK), DF(L_ERGOL), XXXXXXX, XXXXXXX, QK_DEBUG_TOGGLE,
                                XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX, XXXXXXX, _______
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
 * ,------+-------+  [   +   {  +   (  +------|                    |------+  )   +   }  +   ]  +------+------.
 * |      |       |    REPEAT  TAB            |-------.    ,-------|      |    BACK    DEL     |      |      |
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
        case repeat:
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
        case curly_l:
        case curly_r:
        case round_l:
        case round_r:
        case square_l:
        case square_r:
            return COMBO_TERM + 30;
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
        case repeat:
        default:
            // Avoid noise on hold (mouse keys / game arrows keys)
            return true;
    }
}

//
// ┌─────────────────────────────────────────────────┐
// │ LAYER / SWAPPER                                     │
// └─────────────────────────────────────────────────┘
//
// Custom swappers
bool swapper_ctab_active = false;
bool swapper_atab_active = false;

// Custom layer switchers
switcher_state switcher_sym_state = os_up_unqueued;
switcher_state switcher_num_state = os_up_unqueued;
switcher_state switcher_nav_state = os_up_unqueued;

bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
        case TO(L_DEFAULT):
        case KC_ESC:
            return true;
        default:
            return false;
    }
}

bool is_oneshot_layer_cancel_key(uint16_t keycode) {
    switch (keycode) {
        case TO(L_DEFAULT):
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
        case TO(L_DEFAULT):
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
        // Modifiers
        case QK_MODS ... QK_MODS_MAX:
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
    bool swapper_handled = update_swapper(&swapper_atab_active, KC_LALT, KC_TAB, LSFT_T(SW_ATAB), keycode, record);
    swapper_handled &= update_swapper(&swapper_atab_active, KC_LALT, KC_TAB, RSFT_T(SW_ATAB), keycode, record);
    swapper_handled |= update_swapper(&swapper_ctab_active, KC_LCTL, KC_TAB, SW_CTAB, keycode, record);

    // Custom layer change (no timer)
    bool switch_key_not_handled = update_oneshot_layer(&switcher_sym_state, L_SYM, SWITCH_SYM, keycode, record);
    switch_key_not_handled &= update_oneshot_layer(&switcher_num_state, L_NUM, SWITCH_NUM, keycode, record);
    switch_key_not_handled &= update_move_hold_layer(&switcher_nav_state, L_NAV, SWITCH_NAV, keycode, record);

    // Keys does not need further processing
    if (!switch_key_not_handled) return false;

    // Discard key used to end a swapper but first let switchers perform their updates
    if (swapper_handled) return false;

    // Custom keycodes
    switch (keycode) {
        // Custom shortcuts
        case (C_Z):
            if (record->event.pressed) {
                tap_code16(C_UNDO);
                return false;
            }
            break;
        case (C_Y):
            if (record->event.pressed) {
                tap_code16(C_REDO);
                return false;
            }
            break;
        case (C_C):
            if (record->event.pressed) {
                tap_code16(C_COPY);
                return false;
            }
            break;
        case (C_X):
            if (record->event.pressed) {
                tap_code16(C_CUT);
                return false;
            }
            break;
        case (C_V):
            if (record->event.pressed) {
                tap_code16(C_PASTE);
                return false;
            }
            break;
        // Symbols
        case C_GRV:
            if (record->event.pressed) {
                // Handle dead key to print ` or ~
                tap_undead_key(KC_GRV);
                return false;
            }
            break;
        case C_TILD:
            if (record->event.pressed) {
                // Handle dead key to print ~
                tap_undead_key(S(KC_GRV));
                return false;
            }
            break;
        case C_QUOT:
            if (record->event.pressed) {
                // Handle dead key to print ' or "
                tap_undead_key(KC_QUOT);
                return false;
            }
            break;
        case C_DQUOT:
            if (record->event.pressed) {
                // Handle dead key to print "
                tap_undead_key(KC_DQUO);
                return false;
            }
            break;
        case C_DEG:
            if (record->event.pressed) {
                // °
                tap_code16(S(ALGR(KC_SCLN)));
                return false;
            }
            break;
        case C_A_GRV:
            if (record->event.pressed) {
                // à
                tap_key_with_mods(KC_GRV, 0U);
                tap_code16(KC_A);
                return false;
            }
            break;
        case C_E_ACU:
            if (record->event.pressed) {
                // é
                tap_code16(ALGR(KC_E));
                return false;
            }
            break;
        case C_E_GRV:
            if (record->event.pressed) {
                // è
                tap_key_with_mods(KC_GRV, 0U);
                tap_code16(KC_E);
                return false;
            }
            break;
        case C_C_CED:
            if (record->event.pressed) {
                // ç
                tap_code16(ALGR(KC_COMM));
                return false;
            }
            break;
        case C_U_GRV:
            if (record->event.pressed) {
                // ù
                tap_key_with_mods(KC_GRV, 0U);
                tap_code16(KC_U);
                return false;
            }
            break;
        // https://docs.qmk.fm/#/mod_tap?id=intercepting-mod-taps
        // Intercept to send key with modifier on tap
        case RALT_T(C_SLSH):
            if (record->tap.count && record->event.pressed) {
                tap_code16(C_SLSH);
                return false;
            }
            break;
        case LALT_T(C_X):
            if (record->tap.count && record->event.pressed) {
                tap_code16(C_X);
                return false;
            }
            break;
        case LSFT_T(KC_CIRC):
        case RSFT_T(KC_CIRC):
            // Required to avoid to input 6 when combined with mod-tap
            if (record->tap.count && record->event.pressed) {
                tap_code16(KC_CIRC); // Send C(KC_CIRC) on tap
                return false;
            }
            break;
        case TO(L_DEFAULT):
        case TO(L_ADJUST):
            // Force modifiers to cancel (should not be neccessary but just to be safe)
            clear_mods();
            break;
        case ML_MOUSE:
            if (record->event.pressed) {
                // MOUSE layer from combo
                // Force modifiers to cancel (should not be neccessary but just to be safe)
                clear_mods();
                layer_move(L_MOUSE);
                dprintf("MOUSE");
                return false;
            }
            break;
        case ML_ADJUST:
            if (record->event.pressed) {
                // ADJUST layer from combo
                // Force modifiers to cancel (should not be neccessary but just to be safe)
                clear_mods();
                layer_move(L_ADJUST);
                return false;
            }
            break;
    }

    // Repeat
    process_repeat_key(keycode, record, REPEAT);

    // Return false to ignore further processing of key
    // Return true to let qmk handles it
    return true;
};

//
// ┌─────────────────────────────────────────────────┐
// │ CAPS WORD                                       │
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
// │ AUTO MOUSE                                  │
// └─────────────────────────────────────────────────┘
//

// @TODO
// Avoid triggering the layer even for a tiny movement
// Solved (in part) by https://github.com/qmk/qmk_firmware/pull/21398
// The only issue with this implementation is that threshold

#if defined(POINTING_DEVICE_ENABLE) && defined(POINTING_DEVICE_AUTO_MOUSE_ENABLE)
void pointing_device_init_user(void) {
    set_auto_mouse_layer(L_MOUSE);
    set_auto_mouse_enable(true);
}

/**
 * @brief Defined keymap/user level callback for adding keyrecords as mouse keys
 */
bool is_mouse_record_user(uint16_t keycode, keyrecord_t* record) {
    // @IMPORTANT
    // pointing_device_auto_mouse.is_mouse_record has been altered
    // Avoid hard coded IS_MOUSEKEY(keycode) to trigger the layer
    // @IMPORTANT

    // Avoid moving to L_MOUSE layer using a mouse key
    if (IS_LAYER_OFF(L_MOUSE)) {
        return false;
    }

    // Add custom keys from the L_MOUSE layer that continue the auto mouse feature
    switch (keycode) {
        case C_Z:
        case LALT_T(C_X):
        case C_X:
        case C_C:
        case C_V:
        case C_Y:
            return true;
    }

    // Finally include all mouse keys as in original QMK is_mouse_record
    return IS_MOUSEKEY(keycode);
}

#endif

//
// ┌─────────────────────────────────────────────────┐
// │ DEBUG                                                │
// └─────────────────────────────────────────────────┘
//
#if defined(CONSOLE_ENABLE)
void keyboard_post_init_user(void) {
    debug_enable = true;
    // debug_matrix=true;
    debug_keyboard = true;
    debug_mouse    = true;
}
#endif

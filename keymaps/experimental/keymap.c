#include "config.h"
#include QMK_KEYBOARD_H
#include "features/customCodes.h"
#include "g/keymap_combo.h"

#include "features/encoder.h"
#include "features/utility.h"
#include "features/swapper.h"
#include "features/switcher.h"

//
// ***
// LAYOUT
// ***
//
// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * QWERTY
     *        ,-----------------------------------.                    ,-----------------------------------.
     *        |-------|   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |-------|
     * ,------+-------+------+------+------+------|                    |------+------+------+------+-------+------.
     * |  Q   |   A   |   S  |   D  |   F  |   G  |                    |   H  |   J  |   K  |   L  |   P   |Enter |
     * |      | Shift |      |      |      |      |-------.    ,-------|      |      |      |      | Shift |RCtrl |
     * `------+-------+------+------+------+------| MUTE  |    | PSCR  |------+------+------+------+-------+------'
     *        |   Z   |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /   |
     *        |  GUI  |  Alt |      |      |      |       |    |       |      |      |      | Alt  | Ralt  |
     *        `-----------------------------------/      /      \      \-----------------------------------'
     *                       |   NAV  | Space  | /  NUM /        \ SYM  \ |  Enter |  DEF   |
     *                       |   NAV  | Ctrl   |/  NUM /          \ SYM  \|  Ctrl  |        |
     *                       `-----------------'------'            '------'-----------------'
     */
    [_DEFAULT] = LAYOUT(
                    KC_W, KC_E, KC_R, KC_T,            KC_Y, KC_U, KC_I, KC_O,
KC_Q, LSFT_T(KC_A), KC_S, KC_D, KC_F, KC_G,            KC_H, KC_J, KC_K, KC_L, LSFT_T(KC_P), RCTL_T(KC_ENT),
      LGUI_T(KC_Z), LALT_T(KC_X), KC_C, KC_V, KC_B, KC_MUTE,
                                      KC_PSCR, KC_N, KC_M,  KC_COMM, LALT_T(KC_DOT), RALT_T(KC_SLSH),
             MHL_NAV, LCTL_T(KC_SPC), OSL_NUM,          OSL_SYM, LCTL_T(KC_ENT), TO(_DEFAULT)
    ),

    /*
     * COLEMAK
     * https://colemak.com/
     *        ,------------------------------------.                    ,-----------------------------------.
     *        |-------|   W  |   F  |   P  |   G   |                    |   J  |   L  |   U  |   Y  |-------|
     * ,------+-------+------+------+------+-------|                    |------+------+------+------+-------+------.
     * |  Q   |   A   |   R  |   S  |   T  |   D   |                    |   H  |   N  |   E  |   I  |   O   |Enter |
     * |      | Shift |      |      |      |       |-------.    ,-------|      |      |      |      | Shift |RCtrl |
     * `------+-------+------+------+------+-------|  MUTE |    | PSCR  |------+------+------+------+-------+------'
     *        |   Z   |   X  |   C  |   V  |   B   |-------|    |-------|   K  |   M  |   ,  |   .  |   /   |
     *        |  GUI  |  Alt |      |      |       |       |    |       |      |      |      | Alt  | Ralt  |
     *        `------------------------------------/      /      \       \----------------------------------'
     *                       |   NAV  | Space  | /  NUM  /        \ SYM  \ |  Enter |  DEF   |
     *                       |   NAV  | Ctrl   |/  NUM  /          \ SYM  \|  Ctrl  |        |
     *                       `-----------------'-------'            '------'-----------------'
     */
    [_COLEMAK] = LAYOUT(
                    KC_W, KC_F, KC_P, KC_G,            KC_J, KC_L, KC_U, KC_Y,
KC_Q, LSFT_T(KC_A), KC_R, KC_S, KC_T, KC_D,            KC_H, KC_N, KC_E, KC_I, LSFT_T(KC_O), RCTL_T(KC_ENT),
      LGUI_T(KC_Z), LALT_T(KC_X), KC_C, KC_V, KC_B, KC_MUTE,
                                       KC_PSCR, KC_K, KC_M, KC_COMM, LALT_T(KC_DOT), RALT_T(KC_SLSH),
                    _______, _______, _______,         _______, _______, _______
    ),

    /*
     * ErgoL (COLEMAK for english / french)
     * https://ergol.org/
     *        ,------------------------------------.                    ,-----------------------------------.
     *        |-------|   O  |   U  |   D  |   W   |                    |   B  |   M  |   F  |   P  |-------|
     * ,------+-------+------+------+------+-------|                    |------+------+------+------+-------+------.
     * |  Q   |   A   |   S  |   R  |   T  |   Y   |                    |   H  |   N  |   E  |   I  |   G   |Enter |
     * |      | Shift |      |      |      |       |-------.    ,-------|      |      |      |      | Shift |RCtrl |
     * `------+-------+------+------+------+-------|  MUTE |    | PSCR  |------+------+------+------+-------+------'
     *        |   Z   |   X  |   C  |   V  |   K   |-------|    |-------|   J  |   L  |   ,  |   .  |   /   |
     *        |  GUI  |  Alt |      |      |       |       |    |       |      |      |      | Alt  | Ralt  |
     *        `------------------------------------/      /      \       \----------------------------------'
     *                       |   NAV  | Space  | /  NUM  /        \ SYM  \ |  Enter |  DEF   |
     *                       |   NAV  | Ctrl   |/  NUM  /          \ SYM  \|  Ctrl  |        |
     *                       `-----------------'-------'            '------'-----------------'
     */
    [_ERGOL] = LAYOUT(
                    KC_O, KC_U, KC_D, KC_W,            KC_B, KC_M, KC_F, KC_P,
KC_Q, LSFT_T(KC_A), KC_S, KC_R, KC_T, KC_Y,            KC_H, KC_N, KC_E, KC_I, LSFT_T(KC_G), RCTL_T(KC_ENT),
      LGUI_T(KC_Z), LALT_T(KC_X), KC_C, KC_V, KC_K, KC_MUTE,
                                       KC_PSCR, KC_J, KC_L, KC_COMM, LALT_T(KC_DOT), RALT_T(KC_SLSH),
                    _______, _______, _______,         _______, _______, _______
    ),

    /* NAV
     *        ,-----------------------------------.                    ,----------------------------------.
     *        |------| WH_L |  MU  | WH_R  | PgUp |                    | WH_U | Home |  Up  | End  |------|
     * ,------+------+------+------+-------+------|                    |------+------+------+------+------+------.
     * | CTab | ATab |  ML  |  MD  |  MR   | PgDo |                    | WH_D | Left | Down | Right| MB4 |  MB5  |
     * |      | Shift|      |      |       |      |-------.    ,-------|      |      |      |      | Shift|      |
     * `------+------+------+------+-------+------|  MUTE |    | PSCR  |------+------+------+------+------+------'
     *        | Undo | Cut  | Copy | Paste |LDesk |-------|    |-------|RDesk | MB1  | MB2  | MB3  | Com  |
     *        | GUI  |  Alt |      |       |      |       |    |       |      |      |      | Alt  | Ralt |
     *        `-----------------------------------/      /      \      \----------------------------------'
     *                      |   NAV   | Space  | /  NUM /        \ SYM  \ |  Enter |  DEF   |
     *                      |   NAV   | Ctrl   |/  NUM /          \ SYM  \|  Ctrl  |        |
     *                      `------------------'------'            '------'-----------------'
     */
    [_NAV] = LAYOUT(
                          KC_WH_L, KC_MS_U, KC_WH_R, KC_PGUP,       KC_WH_U, KC_HOME, KC_UP, KC_END,
SW_CTAB, LSFT_T(SW_ATAB), KC_MS_L, KC_MS_D, KC_MS_R, KC_PGDN,       KC_WH_D, KC_LEFT, KC_DOWN, KC_RGHT, LSFT_T(KC_BTN4), KC_BTN5,
         LGUI_T(C_Z), LALT_T(C_X), C_C, C_V, C(A(KC_LEFT)), _______,
                                              _______, C(A(KC_RIGHT)), KC_BTN1, KC_BTN2, LALT_T(KC_BTN3), RALT_T(C_SLSH),
                                 _______, _______, _______,         _______, _______, _______

    ),

    /* NUM
     *        ,-----------------------------------.                    ,----------------------------------.
     *        |------|  F6  |  F7  |  F8  |  F9   |                    |  F10 |  F1  |  F2  |  F3  |------|
     * ,------+------+------+------+------+-------|                    |------+------+------+------+------+------.
     * |  F5  |  5   |   6  |   7  |   8  |   9   |                    |  0   |   1  |   2  |   3  |   4  |  F4  |
     * |      | Shift|      |      |      |       |-------.    ,-------|      |      |      |      | Shift|      |
     * `------+------+------+------+------+-------|  MUTE |    | PSCR  |------+------+------+------+------+------'
     *        | Undo | Cut  | Copy |Paste |       |-------|    |-------|  F11 |  F12 |  ,   |  .   |  /   |
     *        | GUI  |  Alt |      |      |       |       |    |       |      |      |      | Alt  | Ralt |
     *        `-----------------------------------/      /      \      \----------------------------------'
     *                      |   NAV   | Space  | /  NUM /        \ SYM  \ |  Enter |  DEF   |
     *                      |   NAV   | Ctrl   |/  NUM /          \ SYM  \|  Ctrl  |        |
     *                      `------------------'------'            '------'-----------------'
     */
    [_NUM] = LAYOUT(
                     KC_F6, KC_F7, KC_F8, KC_F9,           KC_F10, KC_F1, KC_F2, KC_F3,
KC_F5, LSFT_T(KC_5), KC_6, KC_7, KC_8, KC_9,               KC_0,   KC_1,  KC_2,  KC_3, LSFT_T(KC_4), KC_F4,
        LGUI_T(C_Z), LALT_T(C_X), C_C, C_V, XXXXXXX, _______,
                                          _______, KC_F11, KC_F12, KC_COMM, LALT_T(KC_DOT), RALT_T(KC_SLSH),
                    _______, _______, _______,         _______, _______, _______
    ),
    /* SYM
     *
     *        ,-----------------------------------.                    ,-----------------------------------.
     *        |------|   :  |  #   |  ;   |   `   |                    |   %   |   &  |   *  |   ?  |------|
     * ,------+------+------+------+------+-------|                    |-------+------+------+------+------+------.
     * |  °   |  `…  |   à  |  -   |  é   |   /   |                    |   \   |   è  |   '  |   !  |  ^…  |   €  |
     * |      | Shift|      |      |      |       |-------.    ,-------|       |      |      |      | Shift|      |
     * `------+------+------+------+------+-------|  MUTE |    | PSCR  |-------+------+------+------+------+------'
     *        |  |   |   =  |  _   |  +   |  "…   |-------|    |-------|  '…   |   @  |   "  |   $  |   ç  |
     *        |      |      |      |      |       |       |    |       |       |      |      |      |      |
     *        `-------------------------------- --/      /      \      \-----------------------------------'
     *                      |   NAV   | Space  | /  NUM /        \ SYM  \ |  Enter |  DEF   |
     *                      |   NAV   | Ctrl   |/  NUM /          \ SYM  \|  Ctrl  |        |
     *                      `------------------'------'            '------'-----------------'
     *
     */
    [_SYM] = LAYOUT(
                       KC_COLN, KC_HASH, KC_SCLN,   C_GRV,     KC_PERC, KC_AMPR, KC_ASTR, KC_QUES,
C_DEG, LSFT_T(KC_GRV), C_A_GRV, KC_MINS, C_E_ACU, KC_SLSH,     KC_BSLS, C_E_GRV, C_QUOT, KC_EXLM, LSFT_T(KC_CIRC), RALT(KC_5),
       KC_PIPE, KC_EQL, KC_UNDS, KC_PLUS, KC_DQUO, _______,
                                                   _______, KC_QUOT, KC_AT, C_DQUOT, KC_DLR, C_C_CED,
                       _______, _______, _______,                   _______, _______, _______
    ),

    /* ADJUST
     *         ,--------------------------------------.                    ,-----------------------------------.
     *         |------|hue ^  |sat ^  | bri ^ |  BRIU |                    | VOLU  | MRWD | STOP | MFFD |------|
     * ,-------|------+-------+-------+-------+-------+                    |-------+------+------+------+------------.
     * |       |      |hue_dn |sat_dn |bri_dn |  BRID |-------.    ,-------| VOLD  | PREV | PLAY | NEXT |EEPRST|     |
     * |       |      |       |       |       |       |-------.    ,-------|       |      |      |      |      |     |
     * `-------+------+-------+-------+-------+-------|       |    |       |-------+------+------+------+------------'
     *         |RGB_TO|RGB_MO |       |       |QWERTY |-------|    |-------|COLEMAK|ERGOL |      |DEBUG |RESET |
     *         |      |       |       |       |       |       |    |       |       |      |      |      |      |
     *         `-------------------------------------/       /      \      \-----------------------------------'
     *                       |        |           | /       /        \      \ |        |  DEF   |
     *                       |        |           |/       /          \      \|        |        |
     *                       `--------------------'-------'            '------'-----------------'
     */
      [_ADJUST] = LAYOUT(
         RGB_HUI, RGB_SAI, RGB_VAI, KC_BRIU,           KC_VOLU, KC_MRWD, KC_MEDIA_STOP, KC_MFFD,
XXXXXXX, XXXXXXX, RGB_HUD, RGB_SAD, RGB_VAD, KC_BRID,  KC_VOLD, KC_MPRV, KC_MPLY, KC_MNXT, EEP_RST, XXXXXXX,
         RGB_TOG, RGB_MOD, XXXXXXX, XXXXXXX, DF(_DEFAULT), XXXXXXX,
                                                   XXXXXXX, DF(_COLEMAK), DF(_ERGOL), XXXXXXX, DEBUG, RESET,
           XXXXXXX, XXXXXXX, XXXXXXX,                 XXXXXXX, XXXXXXX, _______
    )
    };
// clang-format on

//
// ***
// COMBOS
// ***
//
/*
 *        ,-----------------------------------.                    ,----------------------------------.
 *        |-------|       ESCAPE       |      |                    |          LAUNCHER         |------|
 * ,------+-----  [  --  {  --  ( -----|------|                    |------|----  )  --  }  --  ]  ----+------.
 * |      |       |    ENTER    TAB   CAPS    |-------.    ,-------|    CAPS   BACK    DEL     |      |      |
 * `------+-------+------+------+------+------|       |    |       |------+------+------+------+------+------'
 *        |       |      |      |      |      |-------|    |-------|      |      |      |      |      |
 *        `-----------------------------------/      /      \      \----------------------------------'
 *                     |        |          | / ADJ- /        \ -UST \ |        |  DEF   |
 *                     |        |          |/      /          \      \|        |        |
 *                     `-------------------'------'            '------'-----------------'
 */

uint16_t get_combo_term(uint16_t index, combo_t* combo) {
    switch (index) {
        // Home / Tight combos
        case tab:
        case enter:
        case back:
        case del:
        case launcher:
        case escape_l:
        case caps:
        case caps_bis:
            return COMBO_TERM;
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
        case caps_bis:
        case launcher:
        case back:
        case del:
        case round_l:
        case round_r:
        case square_l:
        case square_r:
            // Quick roll is allowed
            return false;
        case curly_l:
        case curly_r:
        case tab:
        case enter:
        case adjust:
        default:
            // Avoid noise on hold (mouse keys / game arrows keys)
            return true;
    }
}

//
// ***
// TAP HOLD
// ***
//

//
// ***
// CUSTOM KEYCODE HANDLING
// ***
//

// Custom swappers
bool sw_ctab_active = false;
bool sw_atab_active = false;

// Custom layer switchers
oneshot_state osl_sym_state = os_up_unqueued;
oneshot_state osl_num_state = os_up_unqueued;
oneshot_state mhl_nav_state = os_up_unqueued;
oneshot_state mhl_num_state = os_up_unqueued;

bool is_oneshot_cancel_key(uint16_t keycode) {
    // Escape and moved layer
    switch (keycode) {
        case TO(_DEFAULT):
        case KC_ESC:
            return true;
        default:
            return false;
    }
}

bool is_oneshot_layer_cancel_key(uint16_t keycode) {
    switch (keycode) {
        case TO(_DEFAULT):
        case MHL_NAV:
        case MHL_NUM:
        case OSL_SYM:
        case OSL_NUM:
        case KC_ESC:
            return true;
        default:
            return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
        case TO(_DEFAULT):
        case MHL_NAV:
        case MHL_NUM:
        case OSL_SYM:
        case OSL_NUM:
        // Modifiers
        case KC_LCTL:
        case KC_RCTL:
        case KC_LALT:
        case KC_RALT:
        case KC_LGUI:
        case KC_LSFT:

        // Allow mod-tap on one shot layers
        case LSFT_T(KC_5):
        case LSFT_T(KC_4):
        case LSFT_T(KC_GRV):
        case LSFT_T(KC_CIRC):
        case LSFT_T(KC_O):
        case LSFT_T(KC_P):
        case LSFT_T(KC_BTN4):

        case LALT_T(C_X):
        case LALT_T(KC_DOT):
        case LALT_T(KC_BTN3):

        case LGUI_T(KC_Z):
        case LGUI_T(C_Z):

        case RALT_T(C_SLSH):
        case RALT_T(KC_SLSH):
            return true;
        default:
            return false;
    }
}

bool is_oneshot_mod_key(uint16_t keycode) {
    switch (keycode) {
        // Could be useful to add support for sticky modifiers
        // on a one shot layer --> Register modifier then exit the layer
        default:
            return false;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    // Swapper on one key (no timer)
    bool discard_swapper_key = update_swapper(&sw_ctab_active, KC_LCTL, KC_TAB, SW_CTAB, keycode, record);
    discard_swapper_key |= update_swapper(&sw_atab_active, KC_LALT, KC_TAB, LSFT_T(SW_ATAB), keycode, record);

    // Custom layer change (no timer)
    bool notHandled = update_oneshot_layer(&osl_sym_state, _SYM, OSL_SYM, keycode, record);
    notHandled      = update_oneshot_layer(&osl_num_state, _NUM, OSL_NUM, keycode, record);
    // notHandled = update_move_hold_layer(&mhl_num_state, _NUM, MHL_NUM, keycode, record);
    notHandled = update_move_hold_layer(&mhl_nav_state, _NAV, MHL_NAV, keycode, record);

    if (!notHandled) {
        return false;
    }

    // Discard keys used to end a swapper
    if (discard_swapper_key) {
        return false;
    }

    // Custom keycodes
    switch (keycode) {
        // https://docs.qmk.fm/#/mod_tap?id=intercepting-mod-taps
        // Intercept to send key with modifier on tap
        case LGUI_T(C_Z):
            if (record->tap.count && record->event.pressed) {
                tap_code16(C(KC_Z)); // Send C(KC_Z) on tap
                return false;
            }
            break;
        case LALT_T(C_X):
            if (record->tap.count && record->event.pressed) {
                tap_code16(C(KC_X)); // Send C(KC_X) on tap
                return false;
            }
            break;
        case RALT_T(C_SLSH):
            if (record->tap.count && record->event.pressed) {
                tap_code16(C(KC_SLSH)); // Send C(KC_SLSH) on tap
                return false;
            }
            break;
        case LSFT_T(KC_GRV):
            // Required to avoid to input \ when combined with mod-tap
            if (record->tap.count && record->event.pressed) {
                tap_code16(KC_GRV); // Send C(KC_GRV) on tap
                return false;
            }
            break;
        case LSFT_T(KC_CIRC):
            // Required to avoid to input 6 when combined with mod-tap
            if (record->tap.count && record->event.pressed) {
                tap_code16(KC_CIRC); // Send C(KC_CIRC) on tap
                return false;
            }
            break;
        case (C_C):
            if (record->event.pressed) {
                tap_code16(C(KC_C)); // Send C(KC_C) on tap
                return false;
            }
            break;
        case (C_V):
            if (record->event.pressed) {
                tap_code16(C(KC_V)); // Send C(KC_V) on tap
                return false;
            }
            break;
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
        case TO(_DEFAULT):
        case TO(_ADJUST):
            // Force modifiers to cancel (should not be neccessary but just to be safe)
            clear_mods();
            break;
        case ML_ADJUST:
            if (record->event.pressed) {
                // ADJUST layer from combo
                // Force modifiers to cancel (should not be neccessary but just to be safe)
                clear_mods();
                layer_move(_ADJUST);
                return false;
            }
            break;
    }

    // Return false to ignore further processing of key
    // Return true to let qmk handles it
    return true;
};

//
// ***
// CAPS WORDS
// ***
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
        case LSFT_T(KC_GRV):
            return true;

        // Custom one shot layer
        case OSL_NUM:
        case OSL_SYM:
            return true;

        default:
            return false; // Deactivate Caps Word.
    }
}

#include "config.h"
#include QMK_KEYBOARD_H
#include "features/customCodes.h"
#include "g/keymap_combo.h"

#include "features/encoder.h"
#include "features/utility.h"
#include "features/swapper.h"
#include "features/switcher.h"
#include "features/leader.h"

//
// ***
// LAYOUT
// ***
//

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * QWERTY
     * ,-------------------------------------------.                    ,------------------------------------------.
     * |      |       |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |       |      |
     * |------+-------+------+------+------+------|                    |------+------+------+------+-------+------|
     * |  Q   |   A   |   S  |   D  |   F  |   G  |                    |   H  |   J  |   K  |   L  |LEADER |   P  |
     * |      | Shift |      |      |      |      |-------.    ,-------|      |      |      |      | Shift |      |
     * |------+-------+------+------+------+------| MUTE  |    | PSCR  |------+------+------+------+-------+------|
     * |      |   Z   |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /   |      |
     * |      |  GUI  |  Alt |      |      |      |       |    |       |      |      |      | Alt  | Ralt  |      |
     * `------------------------------------------/       /     \      \------------------------------------------'
     *                       |   NAV  | Space  | /  NUM  /       \ SYM  \ |  Enter |  DEF   |
     *                       |   NAV  | Ctrl   |/  NUM  /         \ SYM  \|  Ctrl  |        |
     *                       `-----------------'-------'           '------'-----------------'
     */
    [_DEFAULT] = LAYOUT(
                    KC_W, KC_E, KC_R, KC_T,            KC_Y, KC_U, KC_I, KC_O,
KC_Q, LSFT_T(KC_A), KC_S, KC_D, KC_F, KC_G,            KC_H, KC_J, KC_K, KC_L, LSFT_T(C_CHORD), KC_P,
      LGUI_T(KC_Z), LALT_T(KC_X), KC_C, KC_V, KC_B, KC_MUTE,
                                      KC_PSCR, KC_N, KC_M,  KC_COMM, LALT_T(KC_DOT), RALT_T(KC_SLSH),
             MHL_NAV, LCTL_T(KC_SPC), OSL_NUM,          OSL_SYM, RCTL_T(KC_ENT), TO(_DEFAULT)
    ),

    /*
     * COLEMAK (TODO)
     * ,-------------------------------------------.                    ,------------------------------------------.
     * |      |       |   W  |   F  |   P  |   G   |                    |   J  |   L  |   U  |   Y  |   O   |      |
     * |------+-------+------+------+------+-------|                    |------+------+------+------+-------+------|
     * |  Q   |   A   |   R  |   S  |   T  |   D   |                    |   H  |   N  |   E  |   I  | LEADER|  O   |
     * |      | Shift |      |      |      |       |-------.    ,-------|      |      |      |      | Shift |      |
     * |------+-------+------+------+------+-------|  MUTE |    | PSCR  |------+------+------+------+-------+------|
     * |      |   Z   |   X  |   C  |   V  |   B   |-------|    |-------|   K  |   M  |   ,  |   .  |   /   |      |
     * |      |  GUI  |  Alt |      |      |       |       |    |       |      |      |      | Alt  | Ralt  |      |
     * `-------------------------------------------/      /      \       \------------------------------------------'
     *                       |   NAV  | Space  | /  NUM  /        \ SYM  \ |  Enter |  DEF   |
     *                       |   NAV  | Ctrl   |/  NUM  /          \ SYM  \|  Ctrl  |        |
     *                       `-----------------'-------'            '------'-----------------'
     */
    [_COLEMAK] = LAYOUT(
                    KC_W, KC_F, KC_P, KC_G,            KC_J, KC_L, KC_U, KC_Y,
KC_Q, LSFT_T(KC_A), KC_R, KC_S, KC_T, KC_D,            KC_H, KC_N, KC_E, KC_I, LSFT_T(C_CHORD), KC_O,
      LGUI_T(KC_Z), LALT_T(KC_X), KC_C, KC_V, KC_B, KC_MUTE,
                                       KC_PSCR, KC_K, KC_M, KC_COMM, LALT_T(KC_DOT), RALT_T(KC_SLSH),
                    _______, _______, _______,         _______, _______, _______
    ),

    /* NAV
     * ,------------------------------------------.                    ,-----------------------------------------.
     * |      | CTab | WH_L |  MU  | WH_R  | WH_U |                    | PgUp | Home |  Up  | End  | MB5  |      |
     * |------+------+------+------+-------+------|                    |------+------+------+------+------+------|
     * | CTab | ATab |  ML  |  MD  |  MR   | WH_D |                    | PgDo | Left | Down | Right|  MB4 |  MB5 |
     * |      | Shift|      |      |       |      |-------.    ,-------|      |      |      |      | Shift|      |
     * |------+------+------+------+-------+------|  MUTE |    | PSCR  |------+------+------+------+------+------|
     * |      | Undo | Cut  | Copy | Paste |LDesk |-------|    |-------|RDesk | MB1  | MB2  | MB3  | Com  |      |
     * |      | GUI  |  Alt |      |       |      |       |    |       |      |      |      | Alt  | Ralt |      |
     * `------------------------------------------/       /     \      \-----------------------------------------'
     *                      |   NAV   | Space  | /  NUM  /       \ SYM  \ |  Enter |  DEF   |
     *                      |   NAV   | Ctrl   |/  NUM  /         \ SYM  \|  Ctrl  |        |
     *                      `------------------'-------'           '------'-----------------'
     */
    [_NAV] = LAYOUT(
                          KC_WH_L, KC_MS_U, KC_WH_R, KC_WH_U,       KC_PGUP, KC_HOME, KC_UP, KC_END,
SW_CTAB, LSFT_T(SW_ATAB), KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D,       KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, LSFT_T(KC_BTN4), KC_BTN5,
         LGUI_T(C_Z), LALT_T(C_X), C_C, C_V, C(A(KC_LEFT)), _______,
                                              _______, C(A(KC_RIGHT)), KC_BTN1, KC_BTN2, LALT_T(KC_BTN3), RALT_T(C_SLSH),
                                 _______, _______, _______,         _______, _______, _______

    ),

    /* NUM
     * ,------------------------------------------.                    ,-----------------------------------------.
     * |      |      |  F1  |  F2  |  F3  |  F4   |                    |  F5  |  F6  |  F7  |  F8  |      |      |
     * |------+------+------+------+------+-------|                    |------+------+------+------+------+------|
     * | F10  |  0   |   1  |   2  |   3  |   4   |                    |   5  |   6  |   7  |   8  |  9   |  F9  |
     * |      | Shift|      |      |      |       |-------.    ,-------|      |      |      |      | Shift|      |
     * |------+------+------+------+------+-------|  MUTE |    | PSCR  |------+------+------+------+------+------|
     * |      | Undo | Cut  | Copy |Paste |       |-------|    |-------|  F11 |  F12 |  ,   |  .   |  /   |      |
     * |      | GUI  |  Alt |      |      |       |       |    |       |      |      |      | Alt  | Ralt |      |
     * `------------------------------------------/       /     \      \-----------------------------------------'
     *                      |   NAV   | Space  | /  NUM  /       \ SYM  \ |  Enter |  DEF   |
     *                      |   NAV   | Ctrl   |/  NUM  /         \ SYM  \|  Ctrl  |        |
     *                      `------------------'-------'           '------'-----------------'
     */
    [_NUM] = LAYOUT(
                      KC_F1, KC_F2, KC_F3, KC_F4,      KC_F5, KC_F6, KC_F7, KC_F8,
KC_F10, LSFT_T(KC_0), KC_1, KC_2, KC_3, KC_4,          KC_5, KC_6, KC_7, KC_8, LSFT_T(KC_9), KC_F9,
        LGUI_T(C_Z), LALT_T(C_X), C_C, C_V, XXXXXXX, _______,
                                          _______, KC_F11, KC_F12, KC_COMM, LALT_T(KC_DOT), RALT_T(KC_SLSH),
                    _______, _______, _______,         _______, _______, _______

    ),

    /* SYM
     * ,------------------------------------------.                    ,-----------------------------------------.
     * |      |      |  @   |  #   |  $   |   %   |                    |  ^   |   &  |  *   |   !  |      |      |
     * |------+------+------+------+------+-------|                    |------+------+------+------+------+------|
     * |  `   |  |   |  -   |  +   |  '   |   <   |                    |  [   |  {   |  (   |   ;  |   :  |ADJUST|
     * |      | Shift|      |      |      |       |-------.    ,-------|      |      |      |      | Shift|      |
     * |------+------+------+------+------+-------|  MUTE |    | PSCR  |------+------+------+------+------+------|
     * |      |  ~   |  _   |  =   |  "   |   >   |-------|    |-------|  ]   |  }   |  )   |   ?  |   \  |      |
     * |      | GUI  |  Alt |      |      |       |       |    |       |      |      |      | Alt  | Ralt |      |
     * `------------------------------------------/       /     \      \-----------------------------------------'
     *                      |   NAV   | Space  | /  NUM  /       \ SYM  \ |  Enter |  DEF   |
     *                      |   NAV   | Ctrl   |/  NUM  /         \ SYM  \|  Ctrl  |        |
     *                      `------------------'-------'           '------'-----------------'
     */
    [_SYM] = LAYOUT(
                        KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC,   KC_AMPR, KC_ASTR, KC_EXLM,
C_GRV, LSFT_T(KC_PIPE), KC_MINS, KC_PLUS, C_QUOT, KC_LT,            KC_LBRC, KC_LCBR, KC_LPRN, KC_SCLN, LSFT_T(KC_COLN), TO(_ADJUST),
       LGUI_T(C_TILD), LALT_T(KC_UNDS), KC_EQL, C_DQUOT, KC_GT, _______,
                                                  _______, KC_RBRC, KC_RCBR, KC_RPRN, LALT_T(KC_QUES),  RALT_T(KC_BSLS),
                       _______, _______, _______,                   _______, _______, _______

    ),

    /* ADJUST
     * ,---------------------------------------------.                    ,-----------------------------------------.
     * |       |      |hue ^ |sat ^  | bri ^ |  BRIU |                    | VOLU  | MRWD | STOP | MFFD |      |      |
     * |-------|------+------+-------+-------+-------+                    |-------+------+------+------+------------+|
     * |       |      |huedn |satdn  |bridn  |  BRID |-------.    ,-------| VOLD  | PREV | PLAY | NEXT |EEPRST|      |
     * |-------+------+------+-------+-------+-------|       |    |       |-------+------+------+------+------------+|
     * |       |RGB_TO|RGB_MO|       |       |QWERTY |-------|    |-------|COLEMAK|      |      |DEBUG |RESET |      |
     * `--------------------------------------------/       /      \      \-----------------------------------------'
     *                       |        |          | /       /        \      \ |        |  DEF   |
     *                       |        |          |/       /          \      \|        |        |
     *                       `-------------------'-------'            '------'-----------------'
     */
      [_ADJUST] = LAYOUT(
         RGB_HUI, RGB_SAI, RGB_VAI, KC_BRIU,           KC_VOLU, KC_MRWD, KC_MEDIA_STOP, KC_MFFD,
XXXXXXX, XXXXXXX, RGB_HUD, RGB_SAD, RGB_VAD, KC_BRID,  KC_VOLD, KC_MPRV, KC_MPLY, KC_MNXT, EEP_RST, XXXXXXX,
         RGB_TOG, RGB_MOD, XXXXXXX, XXXXXXX, DF(_DEFAULT), XXXXXXX,
                                                   XXXXXXX, DF(_COLEMAK), XXXXXXX, XXXXXXX, DEBUG, RESET,
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
 * ,------------------------------------------.                    ,-----------------------------------------.
 * |  x   |       |      |      |      |      |                    |      |      |      |      |      |   x  |
 * |------+-------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |       |      |     TAB     |      |-------.    ,-------|      |    BACK    DEL     |      |      |
 * |------+-------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |  x   |       |      |      |      |      |-------|    |-------|      |      |      |      |      |   x  |
 * `------------------------------------------/       /     \      \-----------------------------------------'
 *                     |        |          | /       /       \      \ |        |  DEF   |
 *                     |        |          |/       /         \      \|        |        |
 *                     `-------------------'-------'           '------'-----------------'
 */

uint16_t get_combo_term(uint16_t index, combo_t* combo) {
    switch (index) {
        // Home / Tight combos
        case tab:
        case tab_bis:
        case back:
        case del:
        case escape_l:
            return COMBO_TERM;
        case launcher:
        case caps:
            // Should be quick enough to avoid impacting normal typing
            return COMBO_TERM - 20;
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
        case launcher_bis:
        case back:
        case del:
            return false;
        case tab:
        case tab_bis:
        default:
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
oneshot_state osl_symbol_state = os_up_unqueued;
oneshot_state osl_numpad_state = os_up_unqueued;
oneshot_state mhl_nav_state    = os_up_unqueued;

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
        case OSL_SYM:
        case OSL_NUM:
        // Modifiers
        case KC_LCTL:
        case KC_RCTL:
        case KC_LALT:
        case KC_RALT:
        case KC_LGUI:
        case KC_LSFT:
        // Allow modifier on one shot layer
        // User define keycode required special handling
        case LALT_T(C_X):
        case LGUI_T(C_Z):
        case RALT_T(C_SLSH):
        case LGUI_T(C_TILD):
        // Non default required special handling
        case LSFT_T(KC_0):
        case LSFT_T(KC_9):
        case LALT_T(KC_DOT):
        case LSFT_T(KC_BTN4):
        case LALT_T(KC_QUES):
        case LALT_T(KC_UNDS):
        case RALT_T(KC_BSLS):
        case LSFT_T(KC_COLN):
        case LSFT_T(KC_PIPE):
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
    // Process leader key sequences (no timer)
    if (!process_leader(keycode, record)) {
        return false;
    }

    // Swapper on one key (no timer)
    bool discard_swapper_key = update_swapper(&sw_ctab_active, KC_LCTL, KC_TAB, SW_CTAB, keycode, record);
    discard_swapper_key |= update_swapper(&sw_atab_active, KC_LALT, KC_TAB, LSFT_T(SW_ATAB), keycode, record);

    // Custom layer change (no timer)
    bool notHandled = update_oneshot_layer(&osl_symbol_state, _SYM, OSL_SYM, keycode, record);
    notHandled      = update_oneshot_layer(&osl_numpad_state, _NUM, OSL_NUM, keycode, record);
    notHandled      = update_move_hold_layer(&mhl_nav_state, _NAV, MHL_NAV, keycode, record);

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
        case LSFT_T(C_CHORD):
            if (record->tap.count && record->event.pressed) {
                start_leading();
                return false;
            }
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
        case LSFT_T(KC_BTN4):
            if (record->tap.count && record->event.pressed) {
                tap_code16(KC_BTN4); // Send KC_BTN4 on tap
                return false;
            }
            break;
        case RALT_T(C_SLSH):
            if (record->tap.count && record->event.pressed) {
                tap_code16(C(KC_SLSH)); // Send C(KC_SLSH) on tap
                return false;
            }
            break;
        case LGUI_T(C_TILD):
            if (record->tap.count && record->event.pressed) {
                tap_undead_key(S(KC_GRV)); // Send C(KC_SLSH) on tap
                return false;
            }
            break;
        case LALT_T(KC_QUES):
            if (record->tap.count && record->event.pressed) {
                tap_code16(KC_QUES); // Send C(KC_SLSH) on tap
                return false;
            }
            break;
        case LALT_T(KC_UNDS):
            if (record->tap.count && record->event.pressed) {
                tap_code16(KC_UNDS); // Send C(KC_SLSH) on tap
                return false;
            }
            break;
        case RALT_T(KC_BSLS):
            if (record->tap.count && record->event.pressed) {
                tap_code16(KC_BSLS); // Send C(KC_SLSH) on tap
                return false;
            }
            break;
        case LSFT_T(KC_COLN):
            if (record->tap.count && record->event.pressed) {
                tap_code16(KC_COLN); // Send C(KC_SLSH) on tap
                return false;
            }
            break;
        case LSFT_T(KC_PIPE):
            if (record->tap.count && record->event.pressed) {
                tap_code16(KC_PIPE); // Send C(KC_SLSH) on tap
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
        case TO(_DEFAULT):
        case TO(_ADJUST):
            // Force modifiers to cancel (should not be neccessary but just to be safe)
            clear_mods();
    }

    // Return false to ignore further processing of key
    // Return true to let qmk handles it
    return true;
};

//
// Leader
//
void* leader_start_func(uint16_t keycode) {
    switch (keycode) {
        case KC_T: // Colemak
        case KC_F: // Qwerty
            // é
            tap_code16(ALGR(KC_E));
            break;
        case KC_E:
            // è
            tap_key_with_mods(KC_GRV, 0U);
            tap_code16(KC_E);
            break;
        case KC_U:
            // ù
            tap_key_with_mods(KC_GRV, 0U);
            tap_code16(KC_U);
            break;
        case KC_A:
            // à
            tap_key_with_mods(KC_GRV, 0U);
            tap_code16(KC_A);
            break;
        case KC_P: // Colemak
        case KC_R: // Qwerty
            // ë
            tap_code16(S(KC_QUOT));
            tap_code16(KC_E);
            break;
        case KC_Y:
            // ÿ
            tap_code16(S(KC_QUOT));
            tap_code16(KC_Y);
            break;
        case KC_C:
            // ç
            tap_code16(ALGR(KC_COMM));
            break;
        case KC_SPC:
            tap_code16(KC_TAB);
            break;
        default:
            return NULL;
    }

    return NULL;
}

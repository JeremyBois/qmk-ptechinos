#include "repeat.h"

// ----
// Mainly extracted from kapJI user code
// https://gist.github.com/NotGate/3e3d8ab81300a86522b2c2549f99b131
// ----

// Used to extract the basic tapping keycode from a dual-role key.
// Example: GET_TAP_KC(MT(MOD_RSFT, KC_E)) == KC_E
#define GET_TAP_KC(dual_role_key) dual_role_key & 0xFF

uint16_t last_keycode    = KC_NO;
uint8_t  last_modifier   = 0;
uint16_t pressed_keycode = KC_NO;

void process_repeat_key(uint16_t keycode, const keyrecord_t *record, uint16_t repeatKeycode) {
    if (keycode != repeatKeycode) {
        // Early return when holding down a pure layer key
        // to retain modifiers
        switch (keycode) {
            case QK_DEF_LAYER ... QK_DEF_LAYER_MAX:
            case QK_MOMENTARY ... QK_MOMENTARY_MAX:
            case QK_LAYER_MOD ... QK_LAYER_MOD_MAX:
            case QK_ONE_SHOT_LAYER ... QK_ONE_SHOT_LAYER_MAX:
            case QK_TOGGLE_LAYER ... QK_TOGGLE_LAYER_MAX:
            case QK_TO ... QK_TO_MAX:
            case QK_LAYER_TAP_TOGGLE ... QK_LAYER_TAP_TOGGLE_MAX:
            case QK_MODS ... QK_MODS_MAX:
                return;
        }
        if (record->event.pressed) {
            last_modifier = get_mods() | get_oneshot_mods();
            switch (keycode) {
                case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
                case QK_MOD_TAP ... QK_MOD_TAP_MAX:
                    last_keycode = GET_TAP_KC(keycode);
                    break;
                default:
                    last_keycode = keycode;
                    break;
            }
        }
    } else {
        // keycode == repeatKeycode
        // Handle custom keycode detection when using mod tap
        // https://docs.qmk.fm/#/mod_tap?id=intercepting-mod-taps
        switch (keycode) {
            case QK_MOD_TAP ... QK_MOD_TAP_MAX:
                if (record->tap.count) {
                    if (record->event.pressed) {
                        pressed_keycode = last_keycode;
                        register_mods(last_modifier);
                        register_code16(pressed_keycode);
                        unregister_mods(last_modifier);
                    } else {
                        unregister_code16(pressed_keycode);
                    }
                }
                break;
            default:
                if (record->event.pressed) {
                    pressed_keycode = last_keycode;
                    register_mods(last_modifier);
                    register_code16(pressed_keycode);
                    unregister_mods(last_modifier);
                } else {
                    unregister_code16(pressed_keycode);
                }
                break;
        }
    }
}

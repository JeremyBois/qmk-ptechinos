#include "_wait.h"
#include "action_util.h"
#include "quantum_keycodes.h"
#include "host.h"
#include "quantum.h"

#include "key_utility.h"
#include "customCodes.h"

#include "capsword.h"

#if defined(LOG_CAPS_WORDS)
#    define log_caps_word(fmt, ...)      \
        do {                             \
            dprintf(fmt, ##__VA_ARGS__); \
        } while (0)
#else
#    define log_caps_word(fmt, ...)
#endif

static bool caps_word_lock_on;

bool is_caps_word_lock_on(void) { return caps_word_lock_on; }

void sync_caps_word_lock_on(void)
{
    if (host_keyboard_led_state().caps_lock) {
        caps_word_lock_on = true;
    }
    log_caps_word("Capslock - sync_caps_word_lock_on - Status : %s\n", caps_word_lock_on ? "on" : "off");
}

void caps_word_lock_enable(void) {
    caps_word_lock_on = true;
    if (!(host_keyboard_led_state().caps_lock)) {
        tap_code(KC_CAPS);
    }
    log_caps_word("Capslock - caps_word_lock_enable - Status : %s\n", caps_word_lock_on ? "on" : "off");
}

void caps_word_lock_disable(void) {
    caps_word_lock_on = false;
    unregister_mods(MOD_MASK_SHIFT);
    // Make sure OS is up to date before calling it
    wait_ms(KEY_CAPS_LOCK_DELAY);
    if (host_keyboard_led_state().caps_lock) {
        tap_code(KC_CAPS);
    }
    log_caps_word("Capslock - caps_word_lock_disable - Status : %s\n", caps_word_lock_on ? "on" : "off");
}

__attribute__((weak)) void process_caps_word_lock(uint16_t keycode, const keyrecord_t* record) {
    sync_caps_word_lock_on();

    // Update caps word state
    if (is_caps_word_lock_on()) {
        switch (keycode) {
            case QK_MOD_TAP ... QK_MOD_TAP_MAX:
            case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
            case QK_ONE_SHOT_LAYER ... QK_ONE_SHOT_LAYER_MAX:
                // Earlier return if this has not been considered tapped yet
                if (record->tap.count == 0) {
                    return;
                }
                // Get the base tapping keycode of a mod- or layer-tap key
                keycode = get_tap_key(keycode);
                break;
            default:
                break;
        }

        switch (keycode) {
            // Keycodes to shift
            // Letters
            case KC_A ... KC_Z:
                if (record->event.pressed) {
                    if (get_oneshot_mods() & MOD_MASK_SHIFT) {
                        caps_word_lock_disable();
                        add_oneshot_mods(MOD_MASK_SHIFT);
                    }
                }
            // Keycodes that enable caps word but shouldn't get shifted
            case CW_LOCK_TOGG:
            // Movements
            case KC_BSPC:
            case KC_DEL:
            // Numbers
            case KC_1 ... KC_0:
            // Symbols
            case KC_LPRN:
            case KC_RPRN:
            case KC_MINS:
            case KC_PIPE:
            case KC_UNDS:
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

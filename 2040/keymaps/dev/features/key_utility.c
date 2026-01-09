#include "action.h"
#include "action_util.h"
#include "modifiers.h"
#include "quantum.h"

#include "key_utility.h"
#include <stdint.h>

// Keep track of active mods to be able to force shift/unshift keys
static uint8_t mod_state         = 0U;
static uint8_t oneshot_mod_state = 0U;
static uint8_t weak_mod_state    = 0U;

// Backup modifier state
void sync_mods_state(void) {
    mod_state         = get_mods();
    oneshot_mod_state = get_oneshot_mods();
    weak_mod_state    = get_weak_mods();
}

// Revert modifiers state
void reset_mods_state(void) {
    set_mods(mod_state);
    set_oneshot_mods(oneshot_mod_state);
    set_weak_mods(weak_mod_state);
}

// Remove all modifiers
void clear_mods_state(void) {
    clear_mods();
    clear_weak_mods();
    clear_oneshot_mods();
}

// Remove any modifier from the current state
// mods can be any packed modifier like MOD_MASK_SHIFT
void del_mods_state(uint8_t mods) {
    if (mods) {
        del_mods(mods);
        del_oneshot_mods(mods);
        del_weak_mods(mods);
    }
}

bool tap_dead_key_sequence(const keyrecord_t* record, uint16_t trigger, uint16_t dead, uint16_t key, uint8_t deadMask) {
    // For some reasons record record->keycode != keycode in process_record_user
    // Maybe this is due to using custom keycode for mod tap ?
    // ? https://docs.qmk.fm/#/mod_tap?id=intercepting-mod-taps
    switch (trigger) {
        case QK_MODS ... QK_MODS_MAX:
        case QK_MOD_TAP ... QK_MOD_TAP_MAX:
        case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
        case QK_ONE_SHOT_LAYER ... QK_ONE_SHOT_LAYER_MAX:
            // Earlier return if this has not been considered tapped yet
            if (record->tap.count == 0) {
                return false;
            }
            break;
        default:
            break;
    }

    // Avoid registering a modifier is not needed
    // Add delay to please some app like Remote desktop
    if (record->event.pressed) {
        if (deadMask) {
            del_mods_state(deadMask);
            tap_code16(dead);
            wait_ms(KEY_SEQ_DELAY);
            reset_mods_state();
            tap_code(key);
        } else {
            tap_code16(dead);
            wait_ms(KEY_SEQ_DELAY);
            tap_code(key);
        }
        return true;
    }

    return false;
}

bool tap_two_key_sequence(const keyrecord_t* record, uint16_t trigger, uint16_t first, uint16_t second, uint8_t mods) {
    const uint16_t keys[] = {first, second};

    return tap_key_sequence(record, trigger, keys, 2, mods);
}

bool tap_three_key_sequence(const keyrecord_t* record, uint16_t trigger, uint16_t first, uint16_t second, uint16_t third, uint8_t mods) {
    const uint16_t keys[] = {first, second, third};

    return tap_key_sequence(record, trigger, keys, 3, mods);
}

bool tap_key_sequence(const keyrecord_t* record, uint16_t trigger, const uint16_t* keys, uint8_t num_keys, uint8_t mods) {
    // Validation
    if (num_keys == 0 || keys == NULL) {
        return false;
    }

    // For some reasons record record->keycode != keycode in process_record_user
    // Maybe this is due to using custom keycode for mod tap ?
    // ? https://docs.qmk.fm/#/mod_tap?id=intercepting-mod-taps
    switch (trigger) {
        case QK_MODS ... QK_MODS_MAX:
        case QK_MOD_TAP ... QK_MOD_TAP_MAX:
        case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
        case QK_ONE_SHOT_LAYER ... QK_ONE_SHOT_LAYER_MAX:
            // Earlier return if this has not been considered tapped yet
            if (record->tap.count == 0) {
                return false;
            }
            break;
        default:
            break;
    }

    // Add delay to please some app like Remote desktop
    if (record->event.pressed) {
        register_weak_mods(mods);
        for (uint8_t i = 0; i < num_keys; ++i) {
            tap_code16(keys[i]);
            wait_ms(KEY_SEQ_DELAY);
        }
        unregister_weak_mods(mods);
        return true;
    }

    return false;
}


bool tap_key_with_mods(const keyrecord_t* record, uint16_t trigger, uint16_t key, uint8_t mods) {
    // For some reasons record record->keycode != keycode in process_record_user
    // ? Maybe this is due to using custom keycode for mod tap ?
    // https://docs.qmk.fm/#/mod_tap?id=intercepting-mod-taps
    switch (trigger) {
        case QK_MODS ... QK_MODS_MAX:
        case QK_MOD_TAP ... QK_MOD_TAP_MAX:
        case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
        case QK_ONE_SHOT_LAYER ... QK_ONE_SHOT_LAYER_MAX:
            // Earlier return if this has not been considered tapped yet
            if (record->tap.count == 0) {
                return false;
            }
            break;
        default:
            break;
    }

    // Avoid registering a modifier is not needed
    // Add delay to please some app like Remote desktop
    if (record->event.pressed) {
        if (mods) {
            register_weak_mods(mods);
            wait_ms(KEY_SEQ_DELAY);
        }
        register_code16(key);
    } else {
        unregister_code16(key);
        if (mods) {
            unregister_weak_mods(mods);
        }
    }

    return true;
}

bool is_weak_mod_active(uint8_t mod) {
    return (get_weak_mods() & mod) == mod;
}

bool is_oneshot_mod_active(uint8_t mods, uint8_t mod) {
    return (get_oneshot_mods() & mod) == mod;
}

bool is_mod_active(uint8_t mods, uint8_t mod) {
    return (mods & mod) == mod;
}
#include "action_layer.h"
#include "action_tapping.h"
#include "action_util.h"

#include "quantum.h"
#include "switcher.h"

__attribute__((weak)) bool is_oneshot_mod_key(uint16_t keycode) {
    return false;
}

__attribute__((weak)) bool is_oneshot_cancel_key(uint16_t keycode, keyrecord_t* record) {
    return false;
}

__attribute__((weak)) bool is_oneshot_layer_cancel_key(uint16_t keycode, keyrecord_t* record) {
    return false;
}

__attribute__((weak)) bool is_oneshot_ignored_key(uint16_t keycode, keyrecord_t* record) {
    return false;
}

__attribute__((weak)) bool is_oneshot_layer_ignored_press(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        // Mod taps
        case QK_MOD_TAP ... QK_MOD_TAP_MAX:
            // Holds
            return !record->tap.count;
        default:
            return false;
    }
}

void update_oneshot(switcher_state* state, uint16_t mod, uint16_t trigger, uint16_t keycode, keyrecord_t* record) {
    if (keycode == trigger) {
        if (record->event.pressed) {
            // Trigger keydown
            if (*state == os_up_unqueued) {
                register_code(mod);
            }
            *state = os_down_unused;
        } else {
            // Trigger keyup
            switch (*state) {
                case os_down_unused:
                    // If we didn't use the mod while trigger was held, queue it.
                    *state = os_up_queued;
                    break;
                case os_down_used:
                    // If we did use the mod while trigger was held, unregister it.
                    *state = os_up_unqueued;
                    unregister_code(mod);
                    break;
                default:
                    break;
            }
        }
    } else {
        if (record->event.pressed) {
            if (is_oneshot_cancel_key(keycode, record) && *state != os_up_unqueued) {
                // Cancel oneshot on designated cancel keydown.
                *state = os_up_unqueued;
                unregister_code(mod);
            }
        } else {
            if (!is_oneshot_ignored_key(keycode, record)) {
                // On non-ignored keyup, consider the oneshot used.
                switch (*state) {
                    case os_down_unused:
                        *state = os_down_used;
                        break;
                    case os_up_queued:
                        *state = os_up_unqueued;
                        unregister_code(mod);
                        break;
                    default:
                        break;
                }
            }
        }
    }
}

void update_oneshot_layer(switcher_state* state, uint16_t layer, uint16_t trigger, uint16_t keycode, keyrecord_t* record) {
    if (keycode == trigger) {
        if (record->event.pressed) {
            // Trigger keydown
            if (*state == os_up_unqueued) {
                layer_on(layer);
            }
            if (record->tap.count) {
                // Make layer permanent on tap
                dprintf("OSL - Trigger key down (tap) (on?), layer: %d, os_%d -> os_up_queued\n", layer, *state);
                *state = os_up_queued;
            } else {
                // Wait for keyup event to decide if we must make layer permanent or not
                dprintf("OSL - Trigger key down (hold) (on?), layer: %d, os_%d -> os_down_unused\n", layer, *state);
                *state = os_down_unused;
            }
            dprintf("OSL - Trigger key down (on?), layer active: %d\n", layer_state_is(layer));
        } else {
            // Trigger keyup
            switch (*state) {
                case os_down_unused:
                    // If we didn't use the layer while trigger was held
                    // we assume user want to cancel the layer switch
                    *state = os_up_unqueued;
                    layer_off(layer);
                    dprintf("OSL - Trigger key up (off), layer: %d, os_down_unused -> os_up_unqueued\n", layer);
                    break;
                case os_down_used:
                    // If we did use the layer while trigger was held, turn it off.
                    *state = os_up_unqueued;
                    layer_off(layer);
                    dprintf("OSL - Trigger key up (off), layer: %d, os_down_used -> os_up_unqueued\n", layer);
                    break;
                default:
                    dprintf("OSL - Trigger key up, layer: %d\n", layer);
                    break;
            }
        }
    } else {
        if (record->event.pressed) {
            if (is_oneshot_layer_cancel_key(keycode, record) && *state != os_up_unqueued) {
                // Cancel oneshot layer on designated cancel keydown.
                dprintf("OSL - Other key down. Cancel (off), layer: %d, os_%d -> os_up_unqueued\n", layer, *state);
                *state = os_up_unqueued;
                layer_off(layer);
                return;
            }
            if (is_oneshot_layer_ignored_press(keycode, record) && *state != os_up_unqueued) {
                dprintf("OSL - Other key down. Ignored key press, layer: %d, \n", layer);
                return;
            }
            uint8_t key_layer = read_source_layers_cache(record->event.key);
            if (key_layer == layer) {
                // On non-ignored keydown, consider the oneshot used.
                switch (*state) {
                    case os_down_unused:
                        *state = os_down_used;
                        dprintf("OSL - Other key down, layer: %d, os_down_unused -> os_down_used\n", layer);
                        break;
                    case os_up_queued:
                        if (is_oneshot_mod_key(keycode)) {
                            *state = os_up_unqueued;
                            layer_off(layer);
                            dprintf("OSL - Other key down. Oneshot mod key (off), layer: %d, os_up_queued -> os_up_unqueued\n", layer);
                        } else {
                            // layer_off is delayed to let QMK handle the key
                            // layer_off(layer);
                            *state = os_up_queued_used;
                            dprintf("OSL - Other key down, layer: %d, os_up_queued -> os_up_queued_used\n", layer);
                        }
                        break;
                    case os_up_queued_used:
                        *state = os_up_unqueued;
                        layer_off(layer);
                        dprintf("OSL - Other key down (off), layer: %d, os_up_queued_used -> os_up_unqueued\n", layer);
                        break;
                    default:
                        break;
                }
            }
        } else {
            // Ignore key ups from other layers
            uint8_t key_layer = read_source_layers_cache(record->event.key);
            if (key_layer == layer) {
                // On non-ignored keyup, consider the oneshot used.
                switch (*state) {
                    case os_up_queued:
                        *state = os_up_unqueued;
                        layer_off(layer);
                        dprintf("OSL - Other key up (off), layer: %d, os_up_queued -> os_up_unqueued\n", layer);
                        break;
                    case os_up_queued_used:
                        *state = os_up_unqueued;
                        layer_off(layer);
                        dprintf("OSL - Other key up (off), layer: %d, os_up_queued_used -> os_up_unqueued\n", layer);
                        break;
                    default:
                        break;
                }
            }
        }
    }
}

void update_move_hold_layer(switcher_state* state, uint16_t layer, uint16_t trigger, uint16_t keycode, keyrecord_t* record, layer_state_t* layer_memory) {
    if (keycode == trigger) {
        if (record->event.pressed) {
            if (!layer_state_is(layer)) {
                // Keep track of previous stack
                *layer_memory = layer_state;
            } else {
                // Revert to base layer in this case
                // Avoids reverting to last layer move
                *layer_memory = 0;
            }

            // Force move to layer to avoid beeing layer order dependent
            layer_move(layer);

            // dprintf("Trigger keyup --> Is Tap: %d\n", record->tap.count);
            if (record->tap.count) {
                // Make layer permanent on tap
                dprintf("MHL - Trigger key down (tap) (on), layer: %d, os_%d -> os_up_queued\n", *state, layer);
                *state = os_up_queued;
            } else {
                // Wait for keyup event to decide if we must make layer permanent or not
                dprintf("MHL - Trigger key down (hold) (on?), layer: %d, os_%d -> os_down_unused\n", *state, layer);
                *state = os_down_unused;
            }
        } else {
            // Trigger keyup
            switch (*state) {
                case os_down_unused:
                    // If we didn't use the layer while trigger was held
                    // we assume user want to cancel the layer switch
                    *state = os_up_unqueued;
                    // Combine current layers and saved ones (cleared when layer move() was used)
                    // Then erase switcher layer before setting the new state
                    // layer_state_set((*layer_memory) & ~((layer_state_t)1 << layer));
                    layer_state_set((layer_state | (*layer_memory)) & ~((layer_state_t)1 << layer));
                    dprintf("MHL - Trigger key up (off), layer: %d, os_down_unused -> os_up_unqueued\n", layer);
                    break;
                case os_down_used:
                    // If we did use the layer while trigger was held, turn it off.
                    *state = os_up_unqueued;
                    // Combine current layers and saved ones (cleared when layer move() was used)
                    // Then erase switcher layer before setting the new state
                    // layer_state_set((*layer_memory) & ~((layer_state_t)1 << layer));
                    layer_state_set((layer_state | (*layer_memory)) & ~((layer_state_t)1 << layer));
                    dprintf("MHL - Trigger key up (off), layer: %d, os_down_used -> os_up_unqueued\n", layer);
                    break;
                default:
                    dprintf("MHL - Trigger key up, layer: %d\n", layer);
                    break;
            }
        }
    } else {
        uint8_t key_layer = read_source_layers_cache(record->event.key);
        dprintf("MHL - Other key, layer: %d, key_layer: %d\n", layer, key_layer);
        if (key_layer == layer) {
            if (record->event.pressed) {
                // Reset state to make it work if we use another key to change layer
                switch (*state) {
                    case os_down_unused:
                        // Handle hold case
                        *state = os_down_used;
                        dprintf("MHL - Other key down, layer: %d, os_down_unused -> os_down_used\n", layer);
                        break;
                    case os_up_queued:
                        // Handle tap case
                        *state = os_up_queued_used;
                        dprintf("MHL - Other key down, layer: %d, os_up_queued -> os_up_queued_used\n", layer);
                        break;
                    case os_up_queued_used:
                        // Handle tap case
                        *state = os_up_unqueued;
                        dprintf("MHL - Other key down, layer: %d, os_up_queued_used -> os_up_unqueued\n", layer);
                        break;
                    default:
                        break;
                }
            } else {
                // Reset state to make it work if we use another key to change layer
                switch (*state) {
                    case os_down_unused:
                        // Handle hold case
                        *state = os_down_used;
                        dprintf("MHL - Other key up, layer: %d, os_down_unused -> os_down_used\n", layer);
                        break;
                    case os_up_queued:
                        // Force reset of layer state
                        *state = os_up_unqueued;
                        dprintf("MHL - Other key up, layer: %d, os_up_queued -> os_up_unqueued\n", layer);
                        break;
                    case os_up_queued_used:
                        // Force reset of layer state
                        *state = os_up_unqueued;
                        dprintf("MHL - Other key up, layer: %d, os_up_queued_used -> os_up_unqueued\n", layer);
                    default:
                        break;
                }
            }
        }
    }
}

void update_active_hold_layer(switcher_state* state, uint16_t layer, uint16_t trigger, uint16_t keycode, keyrecord_t* record) {
    if (keycode == trigger) {
        if (record->event.pressed) {
            // Trigger keydown
            layer_on(layer);
            *state = os_down_unused;
        } else {
            // Trigger keyup
            switch (*state) {
                case os_down_unused:
                    // If we didn't use the layer while trigger was held, queue it.
                    *state = os_up_queued;
                    break;
                case os_down_used:
                    // If we did use the layer while trigger was held, turn it off.
                    *state = os_up_unqueued;
                    layer_off(layer);
                    break;
                default:
                    break;
            }
        }
    } else {
        uint8_t key_layer = read_source_layers_cache(record->event.key);
        if (key_layer == layer) {
            if (record->event.pressed) {
                // Reset state to make it work if we use another key to change layer
                switch (*state) {
                    case os_down_unused:
                        // Handle hold case
                        *state = os_down_used;
                        break;
                    case os_up_queued:
                        // Handle tap case
                        *state = os_up_queued_used;
                        break;
                    default:
                        break;
                }
            } else {
                // Reset state to make it work if we use another key to change layer
                switch (*state) {
                    case os_up_queued:
                        // Force reset of layer state
                        *state = os_up_unqueued;
                        break;
                    default:
                        break;
                }
            }
        } else {
            // Handle special case where a upper layer is active while this one is also active
            // but with lower precedence
            // Ex: Move to NAV (upper layer) then hold NUM (lower layer) and pressing another key
            if (record->event.pressed) {
                switch (*state) {
                    case os_down_unused:
                        // Force deactivation
                        *state = os_down_used;
                        break;
                    default:
                        break;
                }
            }
        }
    }
}

bool update_move_mod_layer(tap_mod_state* state, uint16_t layer, uint16_t mod, uint16_t trigger, uint16_t keycode, keyrecord_t* record, uint16_t* internal_timer) {
    if (keycode == trigger) {
        if (record->event.pressed) {
            // Start timer to select between hold/tap later
            *internal_timer = timer_read();
            *state          = mm_held_unused;
            return false;
        } else {
            // Trigger keyup
            switch (*state) {
                case mm_held_used:
                    // Another key was tapped while holding this one
                    // Assume user want a hold
                    *state = mm_up;
                    unregister_code16(mod);
                    return false;
                case mm_held_unused:
                    // Assume tapped if quick enough
                    if (timer_elapsed(*internal_timer) < TAPPING_TERM) {
                        layer_move(layer);
                    }
                default:
                    break;
            }
            *state = mm_up;
            return false;
        }
    } else {
        if (record->event.pressed) {
            if (is_oneshot_cancel_key(keycode, record) && *state != mm_up) {
                // Cancel modifier
                *state = mm_up;
                unregister_code16(mod);
                return false;
            } else if (!is_oneshot_layer_ignored_press(keycode, record)) {
                switch (*state) {
                    case mm_held_unused:
                        // Register mod and let qmk handle the pressed key + mod
                        *state = mm_held_used;
                        register_code16(mod);
                        return true;
                    default:
                        break;
                }
            }
        }
    }
    return true;
}

bool update_tap_hold_layer(tap_mod_state* state, uint16_t layerTap, uint16_t layerHold, uint16_t trigger, uint16_t keycode, keyrecord_t* record, uint16_t* internal_timer) {
    if (keycode == trigger) {
        if (record->event.pressed) {
            // Start timer to select between hold/tap later
            *internal_timer = timer_read();
            *state          = mm_held_unused;
            return false;
        } else {
            // Trigger keyup
            switch (*state) {
                case mm_held_used:
                    // Another key was tapped while holding this one
                    // Assume user want a hold
                    *state = mm_up;
                    layer_off(layerHold);
                    return false;
                case mm_held_unused:
                    // Assume tapped if quick enough
                    if (timer_elapsed(*internal_timer) < TAPPING_TERM) {
                        layer_move(layerTap);
                    } else {
                        layer_move(layerHold);
                    }
                default:
                    break;
            }
            *state = mm_up;
            return false;
        }
    } else {
        if (record->event.pressed) {
            if (is_oneshot_cancel_key(keycode, record) && *state != mm_up) {
                // Cancel modifier
                *state = mm_up;
                layer_off(layerHold);
                return false;
            } else if (!is_oneshot_layer_ignored_press(keycode, record)) {
                switch (*state) {
                    case mm_held_unused:
                        // Register layerHold and let qmk handle the pressed key in that layer
                        *state = mm_held_used;
                        layer_on(layerHold);
                        return true;
                    default:
                        break;
                }
            }
        }
    }
    return true;
}

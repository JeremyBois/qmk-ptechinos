#include "switcher.h"

void update_oneshot(oneshot_state *state, uint16_t mod, uint16_t trigger, uint16_t keycode, keyrecord_t *record) {
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
            if (is_oneshot_cancel_key(keycode) && *state != os_up_unqueued) {
                // Cancel oneshot on designated cancel keydown.
                *state = os_up_unqueued;
                unregister_code(mod);
            }
        } else {
            if (!is_oneshot_ignored_key(keycode)) {
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

bool update_oneshot_layer(oneshot_state *state, uint16_t layer, uint16_t trigger, uint16_t keycode, keyrecord_t *record) {
    if (keycode == trigger) {
        if (record->event.pressed) {
            // Trigger keydown
            if (*state == os_up_unqueued) {
                layer_on(layer);
            }
            *state = os_down_unused;
            return false;
        } else {
            // Trigger keyup
            switch (*state) {
                case os_down_unused:
                    // If we didn't use the layer while trigger was held, queue it.
                    *state = os_up_queued;
                    return false;
                case os_down_used:
                    // If we did use the layer while trigger was held, turn it off.
                    *state = os_up_unqueued;
                    layer_off(layer);
                    return false;
                default:
                    break;
            }
        }
    } else {
        if (record->event.pressed) {
            if (is_oneshot_layer_cancel_key(keycode) && *state != os_up_unqueued) {
                // Cancel oneshot layer on designated cancel keydown.
                *state = os_up_unqueued;
                layer_off(layer);
                return false;
            }
            if (is_oneshot_ignored_key(keycode) && *state != os_up_unqueued) {
                return false;
            }
            uint8_t key_layer = read_source_layers_cache(record->event.key);
            if (key_layer == layer) {
                // On non-ignored keyup, consider the oneshot used.
                switch (*state) {
                    case os_down_unused:
                        *state = os_down_used;
                        return true;
                    case os_up_queued:
                        if (is_oneshot_mod_key(keycode)) {
                            *state = os_up_unqueued;
                            layer_off(layer);
                            return false;
                        } else {
                            *state = os_up_queued_used;
                            return true;
                        }
                    case os_up_queued_used:
                        *state = os_up_unqueued;
                        layer_off(layer);
                        return false;
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
                        return true;
                    case os_up_queued_used:
                        *state = os_up_unqueued;
                        layer_off(layer);
                        return true;
                    default:
                        break;
                }
            }
        }
    }
    return true;
}

bool update_move_hold_layer(oneshot_state *state, uint16_t layer, uint16_t trigger, uint16_t keycode, keyrecord_t *record) {
    if (keycode == trigger) {
        if (record->event.pressed) {
            // Trigger keydown
            layer_move(layer);
            *state = os_down_unused;
            return false;
        } else {
            // Trigger keyup
            switch (*state) {
                case os_down_unused:
                    // If we didn't use the layer while trigger was held, queue it.
                    *state = os_up_queued;
                    return false;
                case os_down_used:
                    // If we did use the layer while trigger was held, turn it off.
                    *state = os_up_unqueued;
                    layer_off(layer);
                    return false;
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
                        return true;
                    case os_up_queued:
                        // Handle tap case
                        *state = os_up_queued_used;
                        return true;
                    case os_up_queued_used:
                        // Handle tap case
                        *state = os_up_unqueued;
                        return false;
                    default:
                        break;
                }
            } else {
                // Reset state to make it work if we use another key to change layer
                switch (*state) {
                    case os_up_queued:
                        // Force reset of layer state
                        *state = os_up_unqueued;
                        return true;
                    case os_up_queued_used:
                        // Force reset of layer state
                        *state = os_up_unqueued;
                        return true;
                    default:
                        break;
                }
            }
        }
    }
    return true;
}

bool update_active_hold_layer(oneshot_state *state, uint16_t layer, uint16_t trigger, uint16_t keycode, keyrecord_t *record) {
    if (keycode == trigger) {
        if (record->event.pressed) {
            // Maybe better to use IS_LAYER_ON(layer) to be sure ??
            if (*state == os_up_queued || *state == os_up_queued_used) {
                // Deactivate if active
                layer_off(layer);
                *state = os_up_unqueued;
            } else {
                // Activate if inactive
                if (*state == os_up_unqueued) {
                    layer_on(layer);
                }
                *state = os_down_unused;
            }

            return false;
        } else {
            // Trigger keyup
            switch (*state) {
                case os_down_unused:
                    // If we didn't use the layer while trigger was held, queue it.
                    *state = os_up_queued;
                    return false;
                case os_down_used:
                    // If we did use the layer while trigger was held, turn it off.
                    *state = os_up_unqueued;
                    layer_off(layer);
                    return false;
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
                        return true;
                    case os_up_queued:
                        // Handle tap case
                        *state = os_up_queued_used;
                        return true;
                    default:
                        break;
                }
            } else {
                // Reset state to make it work if we use another key to change layer
                switch (*state) {
                    case os_up_queued:
                        // Force reset of layer state
                        *state = os_up_unqueued;
                        return true;
                    default:
                        break;
                }
            }
        }
    }
    return true;
}

bool update_move_mod_layer(tap_mod_state *state, uint16_t layer, uint16_t mod, uint16_t trigger, uint16_t keycode, keyrecord_t *record, uint16_t *internal_timer) {
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
                    unregister_code(mod);
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
            if (is_oneshot_cancel_key(keycode) && *state != mm_up) {
                // Cancel modifier
                *state = mm_up;
                unregister_code(mod);
                return false;
            } else if (!is_oneshot_ignored_key(keycode)) {
                switch (*state) {
                    case mm_held_unused:
                        // Register mod and let qmk handle the pressed key + mod
                        *state = mm_held_used;
                        register_code(mod);
                        return true;
                    default:
                        break;
                }
            }
        }
    }
    return true;
}

bool update_tap_hold_layer(tap_mod_state *state, uint16_t layerTap, uint16_t layerHold, uint16_t trigger, uint16_t keycode, keyrecord_t *record, uint16_t *internal_timer) {
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
            if (is_oneshot_cancel_key(keycode) && *state != mm_up) {
                // Cancel modifier
                *state = mm_up;
                layer_off(layerHold);
                return false;
            } else if (!is_oneshot_ignored_key(keycode)) {
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

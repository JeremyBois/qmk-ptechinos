#pragma once

#include QMK_KEYBOARD_H
#include "action.h"

//
// Based on works from callum-oakley and daliusd
// https://github.com/callum-oakley/qmk_firmware/tree/master/users/callum
// https://blog.ffff.lt/posts/callum-layers/
//

// Represents the five states a oneshot key can be in
typedef enum {
    os_up_unqueued,
    os_up_queued,
    os_up_queued_used,
    os_down_unused,
    os_down_used,
} switcher_state;

// Custom oneshot mod implementation that doesn't rely on timers. If a mod is
// used while it is held it will be unregistered on keyup as normal, otherwise
// it will be queued and only released after the next non-mod keyup.
void update_oneshot(switcher_state *state, uint16_t mod, uint16_t trigger, uint16_t keycode, keyrecord_t *record);

// Oneshot implementation for layers
bool update_oneshot_layer(switcher_state *state, uint16_t layer, uint16_t trigger, uint16_t keycode, keyrecord_t *record);

// Custom move / hold layer implementation that doesn't rely on timers. If the trigger is held down the layer is tui
// and another key is pressed then the layer is turn off when the the layer key is released (layer_off).
// If the trigger key is released before any other key then the layer stay active (layer_move).

// If the trigger is tapped then we move to the @layer layer (layer_move).
// If the trigger is held down then the @layer layer is activated (layer_move).
//    - If the trigger is released before any other key then @layer activation is persistent
//    - If the trigger is still held while another key is pressed then @layer remains active until the trigger key is released (layer_off)
bool update_move_hold_layer(switcher_state *state, uint16_t layer, uint16_t trigger, uint16_t keycode, keyrecord_t *record);

// Same as update_move_hold_layer but using layer_on not layer_move
bool update_active_hold_layer(switcher_state *state, uint16_t layer, uint16_t trigger, uint16_t keycode, keyrecord_t *record);

// To be implemented by the consumer.
// Layers one shot implementation needs to know which keys are used as oneshot mods
// true  --> Exit layer and update_oneshot_layer function returns false
// false --> update_oneshot_layer function returns true
bool is_oneshot_mod_key(uint16_t keycode);

// To be implemented by the consumer.Defines keys to cancel oneshot mods.
bool is_oneshot_cancel_key(uint16_t keycode);

// To be implemented by the consumer.Defines keys to cancel oneshot layers.
bool is_oneshot_layer_cancel_key(uint16_t keycode);

// To be implemented by the consumer.
// Defines keys to ignore when determining whether a oneshot mod has been used.
// Setting this to modifiers and layer change keys allows stacking multiple oneshot modifiers
// and carrying them between layers.
// True to ignore, False to handle
bool is_oneshot_ignored_key(uint16_t keycode);

// To be implemented by the consumer.
// Defines keys for which pressed event is ignore but the release event is handled
// Setting this to modifiers allows
//   - Modifier + one shot key --> modifier(one shot key) + leaving layer
//   - Mod tap + release       --> tap action of key + leaving layer
// True to ignore, False to handle
bool is_oneshot_layer_ignored_press(uint16_t keycode);

// Represents the three states a tap_mod key can be in
typedef enum {
    mm_held_unused,
    mm_held_used,
    mm_up,
} tap_mod_state;

// Custom switcher to move to another layer on tap and register a modifier on held
// If the trigger is tapped then we move to the @layer (layer_move)
// If the trigger is held down while another key is pressed then the modifier is register until the trigger is released
bool update_move_mod_layer(tap_mod_state *state, uint16_t layer, uint16_t mods, uint16_t trigger, uint16_t keycode, keyrecord_t *record, uint16_t *internal_timer);

// Custom double layer switcher based on tap / hold behavior.
// If the trigger is tapped then we move to the @layerTap layer (layer_move).
// If the trigger is held down then the @layerHold layer is activated and other layers remains active (layer_on)
//    - If the trigger is released before any other key then @layerHold activation is persistent (layer_move)
//    - If the trigger is still held while another key is pressed then @layerHold remains active (layer_on) until the trigger key is released (layer_off)
bool update_tap_hold_layer(tap_mod_state *state, uint16_t layerTap, uint16_t layerHold, uint16_t trigger, uint16_t keycode, keyrecord_t *record, uint16_t *internal_timer);

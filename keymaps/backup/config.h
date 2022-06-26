#pragma once

//
// Optimization
// https://thomasbaart.nl/2018/12/01/reducing-firmware-size-in-qmk/
//

/* The way how "handedness" is decided (which half is which),
see https://docs.qmk.fm/#/feature_split_keyboard?id=setting-handedness
for more options.
// */
#define MASTER_LEFT
// #define MASTER_RIGHT

// Encoder resolution on both sides
// https://github.com/qmk/qmk_firmware/blob/master/docs/feature_encoders.md


// How many taps before triggering the toggle
#define TAPPING_TOGGLE 2
// Delay between register / unregister for a keycode
#ifdef TAP_CODE_DELAY
#    undef TAP_CODE_DELAY
#endif
#define TAP_CODE_DELAY 10

// Control difference between a hold and a tap
#ifdef TAPPING_TERM
#    undef TAPPING_TERM
#endif
#define TAPPING_TERM 220 // Tapping duration in ms

// https://github.com/qmk/qmk_firmware/blob/master/docs/tap_hold.md#ignore-mod-tap-interrupt
// Remove special case for mod tap keys that strongly prefers the hold
#define IGNORE_MOD_TAP_INTERRUPT

// https://github.com/qmk/qmk_firmware/blob/master/docs/tap_hold.md#permissive-hold
// Allow a more permissive hold for mod tap (does not work with tap dance).
// #define PERMISSIVE_HOLD

// https://github.com/qmk/qmk_firmware/blob/master/docs/tap_hold.md#hold-on-other-key-press
// #define HOLD_ON_OTHER_KEY_PRESS

// One shot settings
#define ONESHOT_TAP_TOGGLE 10 // Sticky key activation (high to only support it in code)
#define ONESHOT_TIMEOUT 4000  // Sticky key duration

// Combo settings
#ifdef COMBO_ENABLE
#    undef COMBO_TERM
#    define COMBO_TERM 55 // Default combo timeout is 200ms.
#    define EXTRA_SHORT_COMBOS
#    define COMBO_MUST_TAP_PER_COMBO
// #    define COMBO_MUST_HOLD_PER_COMBO
#    define COMBO_TERM_PER_COMBO
// All combos are specified from the base layer, saves space
#    define COMBO_ONLY_FROM_LAYER 0
#endif

// Leader settings
#ifdef LEADER_ENABLE
#    define LEADER_NO_TIMEOUT
#    define LEADER_TIMEOUT 400 // Default leader timeout is 200ms.
#endif

// NKRO Settings
#ifdef NKRO_ENABLE
#    define FORCE_NKRO // Force NKRO if enabled.
#endif

// Limit to 8 layers to save space
#define LAYER_STATE_8BIT

// Mouse settings
// https://www.reddit.com/r/olkb/comments/72u8ou/qmk_mouse_keys_rock/
#ifdef MOUSEKEY_ENABLE
#    define MOUSEKEY_INTERVAL 16
#    define MOUSEKEY_DELAY 0
#    define MOUSEKEY_TIME_TO_MAX 60
#    define MOUSEKEY_MAX_SPEED 6
#    define MOUSEKEY_WHEEL_DELAY 0
#    define MOUSEKEY_WHEEL_MAX_SPEED 8
#    define MOUSEKEY_WHEEL_TIME_TO_MAX 40
#endif

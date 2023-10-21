#pragma once

// ┌─────────────────────────────────────────────────┐
// │ Handness                                        │
// └─────────────────────────────────────────────────┘
// BUG in data driven implementation
// Fixed by PR at https://github.com/qmk/qmk_firmware/pull/18254
// #define MASTER_LEFT
// #define MASTER_RIGHT
// Using EE_HANDS (see info.json)

// ┌─────────────────────────────────────────────────┐
// │ Combo                                           │
// └─────────────────────────────────────────────────┘
#ifdef COMBO_ENABLE
#    define EXTRA_SHORT_COMBOS
#    define COMBO_MUST_TAP_PER_COMBO
// If a combo triggers a modifier, only trigger when the combo is held
#    define COMBO_MUST_HOLD_MODS
// Bigger than default tap to avoid any risk of misfire
#    define COMBO_HOLD_TERM 220
#    define COMBO_TERM_PER_COMBO
// All combos are specified from the base layer
//  - saves space
//  - allow position specific combo and not key specific
#    define COMBO_ONLY_FROM_LAYER 0
#endif

// ┌─────────────────────────────────────────────────┐
// │ NKRO                                            │
// └─────────────────────────────────────────────────┘
#ifdef NKRO_ENABLE
#    define FORCE_NKRO // Force NKRO if enabled.
#endif

// ┌─────────────────────────────────────────────────┐
// │ Layers                                         │
// └─────────────────────────────────────────────────┘
#define LAYER_STATE_16BIT // Max number of layers = 16

// ┌─────────────────────────────────────────────────┐
// │ Mouse emulation                                 │
// └─────────────────────────────────────────────────┘
// https://www.reddit.com/r/olkb/comments/72u8ou/qmk_mouse_keys_rock/
#ifdef MOUSEKEY_ENABLE
#    define MOUSEKEY_WHEEL_MAX_SPEED 8
#    define MOUSEKEY_WHEEL_TIME_TO_MAX 80
// Enable quadratic curve :
//   - accurate small movements
//   - fast large motion
#    define MK_KINETIC_SPEED 1
#endif

#ifdef POINTING_DEVICE_ENABLE

// ┌─────────────────────────────────────────────────┐
// │ Pointing devices                                │
// └─────────────────────────────────────────────────┘
// https://github.com/qmk/qmk_firmware/blob/master/docs/feature_split_keyboard.md?id=data-sync-options
// https://github.com/qmk/qmk_firmware/blob/master/docs/feature_pointing_device.md#split-keyboard-configuration
// Pointing device on both sides
#    define SPLIT_POINTING_ENABLE
#    define POINTING_DEVICE_COMBINED
// Rotate sensor report (trackpad / left side)
#    define POINTING_DEVICE_ROTATION_90
// Invert the Y axis (trackball / right side)
#    define POINTING_DEVICE_INVERT_Y_RIGHT 1

// ┌─────────────────────────────────────────────────┐
// │ Auto mouse layer                                │
// └─────────────────────────────────────────────────┘
#    define POINTING_DEVICE_AUTO_MOUSE_ENABLE
#    if defined(POINTING_DEVICE_AUTO_MOUSE_ENABLE)
#        define AUTO_MOUSE_TIME 700            // Activation duration on mouse movement
#        define AUTO_MOUSE_DELAY TAPPING_TERM  // Lock out after a non mouse key
#        define AUTO_MOUSE_DEBOUNCE 40         // Time delay from last activation to next update
#        define AUTO_MOUSE_MOUSEKEY_ACTIVATION // Timer will also be reset by any mousekey press while mouse layer is on
#    endif

// ┌─────────────────────────────────────────────────┐
// │ Trackpad                                        │
// └─────────────────────────────────────────────────┘
// Common parameters can be founded in ../config.h

// Both relative and absolute does not support all features
#    define CIRQUE_PINNACLE_POSITION_MODE CIRQUE_PINNACLE_ABSOLUTE_MODE
// Circular scroll gesture
#    define POINTING_DEVICE_GESTURES_SCROLL_ENABLE
// Single tap support
#    define CIRQUE_PINNACLE_TAP_ENABLE 1
// Right tap support (relative only)
// #    define CIRQUE_PINNACLE_SECONDARY_TAP_ENABLE

// ┌─────────────────────────────────────────────────┐
// │ DRAG SCROLL                                     │
// └─────────────────────────────────────────────────┘
// Revert Y scrolling direction
#    define PTECHINOS_DRAGSCROLL_INVERT_Y 1
#endif

// ┌─────────────────────────────────────────────────┐
// │ VIA                                             │
// └─────────────────────────────────────────────────┘
#ifdef VIA_ENABLE
#    if defined(LAYER_STATE_8BIT)
#        define DYNAMIC_KEYMAP_LAYER_COUNT 8
#    elif defined(LAYER_STATE_16BIT)
#        define DYNAMIC_KEYMAP_LAYER_COUNT 16
#    elif defined(LAYER_STATE_32BIT)
#        define DYNAMIC_KEYMAP_LAYER_COUNT 32
#    else
#        define DYNAMIC_KEYMAP_LAYER_COUNT 16
#    endif
#endif

// ┌─────────────────────────────────────────────────┐
// │ UNICODE                                         │
// └─────────────────────────────────────────────────┘
#define UNICODE_SELECTED_MODES UNICODE_MODE_LINUX, UNICODE_MODE_WINCOMPOSE, UNICODE_MODE_MACOS
#define UNICODE_CYCLE_PERSIST false

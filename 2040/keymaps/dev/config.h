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
// │ Optimization                                    │
// └─────────────────────────────────────────────────┘
#define LAYER_STATE_8BIT

// ┌─────────────────────────────────────────────────┐
// │ Mouse emulation                                 │
// └─────────────────────────────────────────────────┘
// https://www.reddit.com/r/olkb/comments/72u8ou/qmk_mouse_keys_rock/
#ifdef MOUSEKEY_ENABLE
#    define MOUSEKEY_WHEEL_MAX_SPEED 8
#    define MOUSEKEY_WHEEL_TIME_TO_MAX 40
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
// │ Trackpad                                        │
// └─────────────────────────────────────────────────┘
// Common parameters can be founded in ../config.h

// Both relative and absolute does not support all features
#    define CIRQUE_PINNACLE_POSITION_MODE CIRQUE_PINNACLE_ABSOLUTE_MODE
// Circular scroll gesture
// #    define POINTING_DEVICE_GESTURES_SCROLL_ENABLE
// Single tap support
#    define CIRQUE_PINNACLE_TAP_ENABLE 1
// Right tap support (relative only)
// #    define CIRQUE_PINNACLE_SECONDARY_TAP_ENABLE

// ┌─────────────────────────────────────────────────┐
// │ DRAG SCROLL                                     │
// └─────────────────────────────────────────────────┘
// Revert Y scrolling direction
#    define PTECHINOS_DRAGSCROLL_INVERT_Y 1
// Revert X scrolling direction
// #    define PTECHINOS_DRAGSCROLL_INVERT_X 1

#endif

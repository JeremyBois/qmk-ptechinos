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
// │ Debug                                           │
// └─────────────────────────────────────────────────┘
// Last measure --> 1225 (Custom Auto Mouse Layer - 02/12/2023) > 1000 (USB polling)
// #define DEBUG_MATRIX_SCAN_RATE

// ┌─────────────────────────────────────────────────┐
// │ Hold tap                                        │
// └─────────────────────────────────────────────────┘
#define QUICK_TAP_TERM (TAPPING_TERM - 50)
#define PERMISSIVE_HOLD_PER_KEY
#define HOLD_ON_OTHER_KEY_PRESS_PER_KEY

// ┌─────────────────────────────────────────────────┐
// │ Combo                                           │
// └─────────────────────────────────────────────────┘
#ifdef COMBO_ENABLE
#    define EXTRA_SHORT_COMBOS
#    define COMBO_MUST_TAP_PER_COMBO
// If a combo triggers a modifier, only trigger when the combo is held
#    define COMBO_MUST_HOLD_MODS
// Bigger than default tapping term to avoid any risk of misfire
#    define COMBO_HOLD_TERM (TAPPING_TERM + 30)
#    define COMBO_TERM_PER_COMBO
// All combos are specified from the base layer
//  - saves space
//  - available on all layers at the same position
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
#    define MOUSEKEY_WHEEL_TIME_TO_MAX 64

// Quadratic acceleration (allow small and large movements)
#    ifdef MOUSEKEY_KINETIC
#        define MK_KINETIC_SPEED
#    endif

// Constant on hold (default + 3 modes) or on tap (3 modes)
#    ifdef MOUSEKEY_CONSTANT
#        define MK_3_SPEED
#        ifdef MOUSEKEY_CONSTANT_HOLD
#            define MK_MOMENTARY_ACCEL
#        endif
#    endif

// Constant on hold + Acceleration as default
#    ifdef MOUSEKEY_COMBINED
#        define MK_COMBINED
#    endif
#endif

#if defined(MOUSEKEY_CONSTANT) || defined(MOUSEKEY_COMBINED)
//       Overrides modes for mousing
#    define MK_C_OFFSET_0 4
#    define MK_C_INTERVAL_0 16
#    define MK_C_OFFSET_2 28
#    define MK_C_INTERVAL_2 16
#    ifdef MOUSEKEY_CONSTANT_HOLD
#        define MK_C_OFFSET_1 8
#        define MK_C_INTERVAL_1 16
#        define MK_C_OFFSET_UNMOD 15
#        define MK_C_INTERVAL_UNMOD 16
#    else
#        define MK_C_OFFSET_1 14
#        define MK_C_INTERVAL_1 16
#    endif
//       Overrides modes for scrolling
#    define MK_W_OFFSET_0 1
#    define MK_W_INTERVAL_0 100
#    define MK_W_OFFSET_2 1
#    define MK_W_INTERVAL_2 20
#    ifdef MOUSEKEY_CONSTANT_HOLD
#        define MK_W_OFFSET_1 1
#        define MK_W_INTERVAL_1 70
#        define MK_W_OFFSET_UNMOD 1
#        define MK_W_INTERVAL_UNMOD 40
#    else
#        define MK_W_OFFSET_1 1
#        define MK_W_INTERVAL_1 40
#    endif
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

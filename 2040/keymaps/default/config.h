#pragma once

// ┌─────────────────────────────────────────────────┐
// │ Handness                                        │
// └─────────────────────────────────────────────────┘
// BUG in data driven implementation
// Fixed by PR at https://github.com/qmk/qmk_firmware/pull/18254
#define MASTER_LEFT
// #define MASTER_RIGHT

// ┌─────────────────────────────────────────────────┐
// │ Combo                                           │
// └─────────────────────────────────────────────────┘
#ifdef COMBO_ENABLE
#    define EXTRA_SHORT_COMBOS
#    define COMBO_MUST_TAP_PER_COMBO
// If a combo triggers a modifier, only trigger when the combo is held
#    define COMBO_MUST_HOLD_MODS
#    define COMBO_HOLD_TERM 150
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

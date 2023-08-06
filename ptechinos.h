#pragma once

#ifndef POINTING_DEVICE_ENABLE
#define POINTING_DEVICE_ENABLE
#endif

#include "quantum_keycodes.h"
#if defined(KEYBOARD_ptechinos_2040)
#    include "2040.h"
#elif defined(KEYBOARD_ptechinos_promicro)
#    include "promicro.h"
#else
#    error "Unsuported hardware"
#endif

#include "quantum.h"

#ifdef POINTING_DEVICE_ENABLE
typedef enum pointer_side { PTECHINOS_RIGHT = 0, PTECHINOS_LEFT = 1 } pointer_side_t; // Value match boolean on QMK (left == true)

#    ifndef NO_PTECHINOS_KEYCODES
enum ptechinos_keycodes {
    POINTER_LEFT_MOUSING_DPI_UP = QK_KB_0,
    POINTER_LEFT_MOUSING_DPI_DOWN,
    POINTER_RIGHT_MOUSING_DPI_UP,
    POINTER_RIGHT_MOUSING_DPI_DOWN,
    POINTER_LEFT_MODE_TOOGLE,
    POINTER_RIGHT_MODE_TOOGLE,
};
#    endif // !NO_PTECHINOS_KEYCODES

//
// MOUSING
//

/** \brief Whether mousing is enabled. */
bool ptechinos_is_pointer_mousing_enabled(pointer_side_t side);

/**
 * \brief Enable mousing mode.
 */
void ptechinos_set_pointer_as_mousing(pointer_side_t side);

/** \brief Return the current DPI value for the pointer's default mode. */
uint16_t ptechinos_get_pointer_mousing_dpi(pointer_side_t side);

/**
 * \brief Update the pointer's default CPI to the next or previous step.
 *   - Update global configuration
 *   - Update device CPI
 *   - Update EEPROM
 */
void ptechinos_set_pointer_mousing_dpi(pointer_side_t side, bool forward);

//
// DRAG-SCROLL
//
/** \brief Whether drag-scroll is enabled. */
bool ptechinos_is_pointer_dragscroll_enabled(pointer_side_t side);

/**
 * \brief Enable drag-scroll mode.
 *
 * When drag-scroll mode is enabled, horizontal and vertical pointer movements
 * are translated into horizontal and vertical scroll movements.
 */
void ptechinos_set_pointer_as_dragscroll(pointer_side_t side);

//
// BOTH
//
void ptechinos_toogle_pointer_between_mousing_dragscroll(pointer_side_t side);

#endif // POINTING_DEVICE_ENABLE

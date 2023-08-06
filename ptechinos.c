#include "ptechinos.h"

#ifdef POINTING_DEVICE_ENABLE

// // // ┌─────────────────────────────────────────────────┐
// // // │ PWM3360 Trackball                               │
// // // └─────────────────────────────────────────────────┘
// // #    ifndef TRACKBALL_DPI_OPTIONS
// // #        define TRACKBALL_DPI_OPTIONS { 800, 1000, 1200, 1600 }
// // #        ifndef TRACKBALL_DPI_DEFAULT
// // #            define TRACKBALL_DPI_DEFAULT 1
// // #        endif
// // #    endif
// // #    ifndef TRACKBALL_DPI_DEFAULT
// // #        define TRACKBALL_DPI_DEFAULT 0
// // #    endif

//
// DOCUMENTATION / INSPIRATION
// https://github.com/qmk/qmk_firmware/blob/master/quantum/eeconfig.h
// https://github.com/qmk/qmk_firmware/blob/master/docs/feature_eeprom.md
// https://github.com/qmk/qmk_firmware/blob/master/docs/feature_pointing_device.md
// https://github.com/qmk/qmk_firmware/blob/master/docs/feature_split_keyboard.md
// https://github.com/qmk/qmk_firmware/blob/master/keyboards/bastardkb/dilemma/dilemma.c
// Ploopy mouse code
// QMK code - pointing_device, keyboard, split_util, eeconfig
// DOCUMENTATION / INSPIRATION

// TODO
// [x] Draft Mousing + Scrolling (Both, One side, master or not)
// [x] Complete implementation (compile and seems ok ^^)
// [ ] Add user keycode to test (without writing to EEPROM)
// [ ] Test EEPROM read / save
// [ ] User keymap overrides --> Add auto mouse layer support
// [ ] Use CPI in place of DPI to be consistent with QMK API
// [ ] Add a joystick mode (https://www.yorku.ca/mack/FuturePlay1.html) ??
// [ ] Add a sniping (low DPI) mode ??
// TODO

// WHY
// Cast DPI to uint16_t from uint8_t
// WHY

// UNSURE
// ?? Use an array of CPIs instead of a step size ??
// UNSURE

// Mousing (Avoid values below 100)
#    define PTECHINOS_MOUSING_DPI_MIN 400
#    ifndef PTECHINOS_MOUSING_DPI_MIN
#        define PTECHINOS_MOUSING_DPI_MIN 400
#    endif // PTECHINOS_MOUSING_DPI_MIN

#    ifndef PTECHINOS_MOUSING_DPI_CONFIG_STEP
#        define PTECHINOS_MOUSING_DPI_CONFIG_STEP 200
#    endif // PTECHINOS_MOUSING_DPI_CONFIG_STEP

// Scrolling (Avoid values below 100)
#    ifndef PTECHINOS_DRAGSCROLL_DPI
#        define PTECHINOS_DRAGSCROLL_DPI 100
#    endif // PTECHINOS_DRAGSCROLL_DPI

// Revert Y scrolling direction
#    ifndef PTECHINOS_DRAGSCROLL_INVERT_Y
#        define PTECHINOS_DRAGSCROLL_INVERT_Y 1
#    endif // PTECHINOS_DRAGSCROLL_INVERT_Y

// Revert X scrolling direction
#    ifndef PTECHINOS_DRAGSCROLL_INVERT_X
#        define PTECHINOS_DRAGSCROLL_INVERT_X 1
#    endif // PTECHINOS_DRAGSCROLL_INVERT_X

// Pointing data
typedef union {
    uint32_t raw;
    struct {
        // Persistent (stored in EEPROM)
        uint8_t mousing_left_dpi : 4;  // 4 bits --> 16 steps (0-15)
        uint8_t mousing_right_dpi : 4; // 4 bits --> 16 steps (0-15)
        // Not persistent (discard when reading from EEPROM)
        bool is_dragscroll_left_enabled : 1;
        bool is_dragscroll_right_enabled : 1;
    } __attribute__((packed));
} pointer_config_t;

static pointer_config_t g_ptechinos_pointer_config = {0};

/**
 * \brief Set the value of `config` from EEPROM.
 *
 * Note that `is_dragscroll_[left|right]_enabled` states
 * are purposefully ignored since we do not want to persist them to memory.
 */
static void ptechinos_read_config_from_eeprom(pointer_config_t* config) {
    config->raw                         = eeconfig_read_kb();
    config->is_dragscroll_left_enabled  = false;
    config->is_dragscroll_right_enabled = false;
}

/**
 * \brief Save the value of `config` to EEPROM.
 *
 * Note that all values are written verbatim.
 * This include `is_dragscroll_[left|right]_enabled` states.
 */
static void ptechinos_write_config_to_eeprom(pointer_config_t* config) {
    eeconfig_update_kb(config->raw);
}

// Helper to make it easier to set CPI
static void ptechinos_pointing_device_set_dpi_internal(bool left, uint16_t cpi) {
#    if defined(SPLIT_POINTING_ENABLE) && defined(POINTING_DEVICE_COMBINED)
    pointing_device_set_cpi_on_side(left, cpi);
#    else
    pointing_device_set_cpi(cpi);
#    endif
}

/**
 *\brief Set the appropriate CPI on the device based on the input config.
 */
static void ptechinos_pointing_device_set_cpi(pointer_config_t* config, pointer_side_t side) {
    switch (side) {
        case PTECHINOS_LEFT:
            if (config->is_dragscroll_left_enabled) {
                ptechinos_pointing_device_set_dpi_internal(true, PTECHINOS_DRAGSCROLL_DPI);
            } else {
                uint16_t dpi = ptechinos_get_pointer_mousing_dpi(side);
                ptechinos_pointing_device_set_dpi_internal(true, dpi);
            }
            break;
        case PTECHINOS_RIGHT:
            if (config->is_dragscroll_right_enabled) {
                ptechinos_pointing_device_set_dpi_internal(false, PTECHINOS_DRAGSCROLL_DPI);
            } else {
                uint16_t dpi = ptechinos_get_pointer_mousing_dpi(side);
                ptechinos_pointing_device_set_dpi_internal(false, dpi);
            }
            break;
    }
}

bool ptechinos_is_pointer_mousing_enabled(pointer_side_t side) {
    switch (side) {
        case PTECHINOS_LEFT:
            return !g_ptechinos_pointer_config.is_dragscroll_left_enabled;
        case PTECHINOS_RIGHT:
            return !g_ptechinos_pointer_config.is_dragscroll_right_enabled;
        default:
            return false;
    }
}

void ptechinos_set_pointer_as_mousing(pointer_side_t side) {
    switch (side) {
        case PTECHINOS_LEFT:
            g_ptechinos_pointer_config.is_dragscroll_left_enabled = false;
        case PTECHINOS_RIGHT:
            g_ptechinos_pointer_config.is_dragscroll_right_enabled = false;
    }
    // Update device
    ptechinos_pointing_device_set_cpi(&g_ptechinos_pointer_config, side);

    // Non persistent data --> Do nothing
}

uint16_t ptechinos_get_pointer_mousing_dpi(pointer_side_t side) {
    uint16_t dpi;
    switch (side) {
        case PTECHINOS_LEFT:
            dpi = (uint16_t)g_ptechinos_pointer_config.mousing_left_dpi;
            break;
        case PTECHINOS_RIGHT:
            dpi = (uint16_t)g_ptechinos_pointer_config.mousing_right_dpi;
            break;
        default:
            dpi = (uint16_t)0;
            break;
    }

    dpi = dpi * PTECHINOS_MOUSING_DPI_CONFIG_STEP + PTECHINOS_MOUSING_DPI_MIN;
    return dpi;
}

void ptechinos_set_pointer_mousing_dpi(pointer_side_t side, bool increase) {
    // Update config
    switch (side) {
        case PTECHINOS_LEFT:
            if (increase) {
                g_ptechinos_pointer_config.mousing_left_dpi += 1;
            } else if (g_ptechinos_pointer_config.mousing_left_dpi > 0u) {
                g_ptechinos_pointer_config.mousing_left_dpi -= 1;
            }
            break;
        case PTECHINOS_RIGHT:
            if (increase) {
                g_ptechinos_pointer_config.mousing_right_dpi += 1;
            } else if (g_ptechinos_pointer_config.mousing_right_dpi > 0u) {
                g_ptechinos_pointer_config.mousing_right_dpi -= 1;
            }
            break;
    }
    // Update device
    ptechinos_pointing_device_set_cpi(&g_ptechinos_pointer_config, side);

    // Persistent data --> update EEPROM
    ptechinos_write_config_to_eeprom(&g_ptechinos_pointer_config);
}

bool ptechinos_is_pointer_dragscroll_enabled(pointer_side_t side) {
    switch (side) {
        case PTECHINOS_LEFT:
            return g_ptechinos_pointer_config.is_dragscroll_left_enabled;
        case PTECHINOS_RIGHT:
            return g_ptechinos_pointer_config.is_dragscroll_right_enabled;
        default:
            return false;
    }
}

void ptechinos_set_pointer_as_dragscroll(pointer_side_t side) {
    switch (side) {
        case PTECHINOS_LEFT:
            g_ptechinos_pointer_config.is_dragscroll_left_enabled = true;
        case PTECHINOS_RIGHT:
            g_ptechinos_pointer_config.is_dragscroll_right_enabled = true;
    }
    // Update device
    ptechinos_pointing_device_set_cpi(&g_ptechinos_pointer_config, side);

    // Non persistent data --> Do nothing
}

void ptechinos_toogle_pointer_between_mousing_dragscroll(pointer_side_t side) {
    if (ptechinos_is_pointer_dragscroll_enabled(side)) {
        // Switch to mousing mode
        ptechinos_set_pointer_as_mousing(side);
    } else {
        // Switch to drag scroll mode
        ptechinos_set_pointer_as_dragscroll(side);
    }
}

static void ptechinos_pointing_device_task_drag_scroll(report_mouse_t* mouse_report) {
#    ifdef PTECHINOS_DRAGSCROLL_INVERT_X
    // Invert horizontal scroll direction
    mouse_report->h = -mouse_report->x;
#    else
    mouse_report->h     = mouse_report->x;
#    endif // PTECHINOS_DRAGSCROLL_INVERT_X
#    ifdef PTECHINOS_DRAGSCROLL_INVERT_Y
    // Invert vertical scroll direction
    mouse_report->v = -mouse_report->y;
#    else
    mouse_report->v     = mouse_report->y;
#    endif // PTECHINOS_DRAGSCROLL_INVERT_Y

    // Disable movement
    mouse_report->x = 0;
    mouse_report->y = 0;
}

#    if defined(SPLIT_POINTING_ENABLE)
#        if defined(POINTING_DEVICE_COMBINED)
report_mouse_t pointing_device_task_combined_kb(report_mouse_t left_report, report_mouse_t right_report) {
    // Don't poll the target side pointing device
    // Redundant with pointing_device_task in QMK base code
    // if (!is_keyboard_master()) {
    //   return pointing_device_combine_reports(left_report, right_report);
    // };

    if (g_ptechinos_pointer_config.is_dragscroll_left_enabled) {
        ptechinos_pointing_device_task_drag_scroll(&left_report);
    }
    if (g_ptechinos_pointer_config.is_dragscroll_right_enabled) {
        ptechinos_pointing_device_task_drag_scroll(&right_report);
    }
    return pointing_device_task_combined_user(left_report, right_report);
}
#        elif defined(POINTING_DEVICE_LEFT) || defined(POINTING_DEVICE_RIGHT)
report_mouse_t pointing_device_task_kb(report_mouse_t report) {
    // Don't poll the target side pointing device
    // Redundant with pointing_device_task in QMK base code
    // if (!is_keyboard_master()) {
    //   return report;
    // };

    if (is_keyboard_left()) {
        if (g_ptechinos_pointer_config.is_dragscroll_left_enabled) {
            ptechinos_pointing_device_task_drag_scroll(&report);
        }
    } else {
        if (g_ptechinos_pointer_config.is_dragscroll_right_enabled) {
            ptechinos_pointing_device_task_drag_scroll(&report);
        }

        return pointing_device_task_user(report);
    }
    return report;
#        else
#            error "You need to define the side(s) the pointing device is on. POINTING_DEVICE_COMBINED / POINTING_DEVICE_LEFT / POINTING_DEVICE_RIGHT"
#        endif
#    endif

void pointing_device_init_kb(void) {
    // Called before keyboard_post_init_kb in keyboard_init (keyboard.c)
#    if defined(SPLIT_POINTING_ENABLE)
#        if defined(POINTING_DEVICE_COMBINED)
    ptechinos_pointing_device_set_cpi(&g_ptechinos_pointer_config, PTECHINOS_LEFT);
    ptechinos_pointing_device_set_cpi(&g_ptechinos_pointer_config, PTECHINOS_RIGHT);
#        elif defined(POINTING_DEVICE_LEFT)
        ptechinos_pointing_device_set_cpi(&g_ptechinos_pointer_config, PTECHINOS_LEFT);
#        elif defined(POINTING_DEVICE_RIGHT)
    ptechinos_pointing_device_set_cpi(&g_ptechinos_pointer_config, PTECHINOS_RIGHT);
#        else
#            error "You need to define the side(s) the pointing device is on. POINTING_DEVICE_COMBINED / POINTING_DEVICE_LEFT / POINTING_DEVICE_RIGHT"
#        endif
#    else
    pointer_side_t side = is_keyboard_left() ? PTECHINOS_LEFT : PTECHINOS_RIGHT;
    ptechinos_pointing_device_set_cpi(&g_ptechinos_pointer_config, side);
#    endif

    pointing_device_init_user();
}

//
// COMMON (QMK)
//
void eeconfig_init_kb(void) {
    // EEPROM is getting reset!
    // To force an EEPROM reset, use the EE_CLR keycode or Bootmagic Lite functionallity
    g_ptechinos_pointer_config.raw               = 0;
    g_ptechinos_pointer_config.mousing_left_dpi  = 2;
    g_ptechinos_pointer_config.mousing_right_dpi = 2;
    ptechinos_write_config_to_eeprom(&g_ptechinos_pointer_config);

    // Reset all devices even if user only use one
    ptechinos_pointing_device_set_cpi(&g_ptechinos_pointer_config, PTECHINOS_LEFT);
    ptechinos_pointing_device_set_cpi(&g_ptechinos_pointer_config, PTECHINOS_RIGHT);

    // Let user do whatever he wants
    eeconfig_init_user();
}

void matrix_init_kb(void) {
    // Safe to read DPI setting from configuration since
    // matrix init comes before pointing device init
    ptechinos_read_config_from_eeprom(&g_ptechinos_pointer_config);

    matrix_init_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t* record) {
    if (!process_record_user(keycode, record)) {
        return false;
    }

    // Pointer specific code
    switch (keycode) {
        case POINTER_LEFT_MOUSING_DPI_UP:
            if (record->event.pressed) {
                if (ptechinos_is_pointer_mousing_enabled(PTECHINOS_LEFT)) {
                    // Only update DPI when user can actually see a change
                    ptechinos_set_pointer_mousing_dpi(PTECHINOS_LEFT, true);
                }
            }
            break;
        case POINTER_LEFT_MOUSING_DPI_DOWN:
            if (record->event.pressed) {
                if (ptechinos_is_pointer_mousing_enabled(PTECHINOS_LEFT)) {
                    // Only update DPI when user can actually see a change
                    ptechinos_set_pointer_mousing_dpi(PTECHINOS_LEFT, true);
                }
            }
            break;
        case POINTER_LEFT_MODE_TOOGLE:
            ptechinos_toogle_pointer_between_mousing_dragscroll(PTECHINOS_LEFT);
            break;
        case POINTER_RIGHT_MOUSING_DPI_UP:
            if (record->event.pressed) {
                if (ptechinos_is_pointer_mousing_enabled(PTECHINOS_RIGHT)) {
                    // Only update DPI when user can actually see a change
                    ptechinos_set_pointer_mousing_dpi(PTECHINOS_RIGHT, true);
                }
            }
            break;
        case POINTER_RIGHT_MOUSING_DPI_DOWN:
            if (record->event.pressed) {
                if (ptechinos_is_pointer_mousing_enabled(PTECHINOS_RIGHT)) {
                    // Only update DPI when user can actually see a change
                    ptechinos_set_pointer_mousing_dpi(PTECHINOS_RIGHT, true);
                }
            }
            break;
        case POINTER_RIGHT_MODE_TOOGLE:
            ptechinos_toogle_pointer_between_mousing_dragscroll(PTECHINOS_RIGHT);
            break;
    }

    return true;
}

#endif

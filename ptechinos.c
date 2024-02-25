#include "ptechinos.h"
#include <stdint.h>

#ifdef CONSOLE_ENABLE
#    include "print.h"
#endif // CONSOLE_ENABLE

#ifdef POINTING_DEVICE_ENABLE

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
// [x] Complete working implementation
// [x] Add user keycode to test
// [x] Test EEPROM read / save
// [x] Test COMBINED mode
// [ ] Test master only mode
// [ ] Test slave left mode
// [ ] Test slave right mode
// [x] Use CPI in place of DPI
// [ ] Add documentation
// [x] ?? User keymap overrides --> Add auto mouse layer support ??
// [ ] ?? Add a joystick mode (https://www.yorku.ca/mack/FuturePlay1.html) ??
// [ ] ?? Add a sniping (low CPI) mode ??
// [ ] ?? Add gestures (copy/paste/back/next) ??
// [ ] Handle modes using an enum instead of booleans
// TODO

// UNSURE
// ?? Use an array of CPIs instead of a step size ??
// #    ifndef TRACKBALL_CPI_OPTIONS
// #        define TRACKBALL_CPI_OPTIONS { 800, 1000, 1200, 1600 }
// #        ifndef TRACKBALL_CPI_DEFAULT
// #            define TRACKBALL_CPI_DEFAULT 1
// #        endif
// #    endif
// #    ifndef TRACKBALL_CPI_DEFAULT
// #        define TRACKBALL_CPI_DEFAULT 0
// #    endif
// UNSURE

// Persistence in EEPROM
#    ifndef PTECHINOS_EEPROM_READ_WRITE_DISABLED
#        define PTECHINOS_EEPROM_READ_WRITE
#    endif // PTECHINOS_EEPROM_READ_WRITE_DISABLED

// Mousing (Avoid values below 100)
#    ifndef PTECHINOS_MOUSING_CPI_MIN
#        define PTECHINOS_MOUSING_CPI_MIN 200
#    endif // PTECHINOS_MOUSING_CPI_MIN

#    ifndef PTECHINOS_MOUSING_CPI_CONFIG_STEP
#        define PTECHINOS_MOUSING_CPI_CONFIG_STEP 200
#    endif // PTECHINOS_MOUSING_CPI_CONFIG_STEP

// Scrolling (Avoid values below 100)
#    ifndef PTECHINOS_DRAGSCROLL_LEFT
#        define PTECHINOS_DRAGSCROLL_LEFT 100
#    endif // PTECHINOS_DRAGSCROLL_LEFT
#    ifndef PTECHINOS_DRAGSCROLL_RIGHT
#        define PTECHINOS_DRAGSCROLL_RIGHT 250
#    endif // PTECHINOS_DRAGSCROLL_RIGHT
#    ifndef PTECHINOS_SCROLL_DIVISOR_H
#        define PTECHINOS_SCROLL_DIVISOR_H 5.0
#    endif // PTECHINOS_SCROLL_DIVISOR_H
#    ifndef PTECHINOS_SCROLL_DIVISOR_V
#        define PTECHINOS_SCROLL_DIVISOR_V 5.0
#    endif // PTECHINOS_SCROLL_DIVISOR_V

// Pointing data
typedef union {
    uint32_t raw;
    struct {
        // Persistent (stored in EEPROM)
        uint8_t mousing_left_cpi : 4;  // 4 bits --> 16 steps (0-15)
        uint8_t mousing_right_cpi : 4; // 4 bits --> 16 steps (0-15)
        // Not persistent (discard when reading from EEPROM)
        bool is_dragscroll_left_enabled : 1;
        bool is_dragscroll_right_enabled : 1;
    } __attribute__((packed));
} pointer_config_t;

// Used to avoid unsigned int wrapping when CPI is updated
const uint8_t max_cpi_state = 15u;
const uint8_t min_cpi_state = 0u;

static pointer_config_t g_ptechinos_pointer_config = {0};

/**
 * \brief Outputs the Dilemma configuration to console.
 *
 * Prints the in-memory configuration structure to console, for debugging.
 * Includes:
 *   - raw value
 *   - drag-scroll: on/off
 *   - sniping: on/off
 *   - default CPI: internal table index/actual CPI
 *   - sniping CPI: internal table index/actual CPI
 */
static void ptechinos_print_config_to_console(const char* location, pointer_config_t* config) {
#    ifdef CONSOLE_ENABLE
    dprintf("[Ptechinos] %s\n"
            "CONFIG = {\n"
            "\traw = 0x%lX,\n"
            "\t{\n"
            "\t\tis_dragscroll_left_enabled=%u\n"
            "\t\tmousing_left_cpi=0x%X (%u)\n"
            "\t}\n"
            "\t{\n"
            "\t\tis_dragscroll_right_enabled=%u\n"
            "\t\tmousing_right_cpi=0x%X (%u)\n"
            "\t}\n"
            "}\n",
            location, config->raw, config->is_dragscroll_left_enabled, config->mousing_left_cpi, ptechinos_get_pointer_mousing_cpi(PTECHINOS_LEFT), config->is_dragscroll_right_enabled, config->mousing_right_cpi, ptechinos_get_pointer_mousing_cpi(PTECHINOS_RIGHT));
#    endif // CONSOLE_ENABLE
}

// static void ptechinos_print_mouse_report_to_console(const char* location, pointer_side_t side, report_mouse_t* report) {
// #    ifdef CONSOLE_ENABLE
//     dprintf("[Ptechinos] %s\n"
//             "REPORT (side=%d) ={\n"
//             "\tx=%d\n"
//             "\ty=%d\n"
//             "\tv=%d\n"
//             "\th=%d\n"
//             "}\n",
//             location, side, report->x, report->y, report->v, report->h);
// #    endif // CONSOLE_ENABLE
// }

/**
 * \brief Set the value of `config` from EEPROM.
 *
 * Note that `is_dragscroll_[left|right]_enabled` states
 * are purposefully ignored since we do not want to persist them to memory.
 */
static void ptechinos_read_config_from_eeprom(pointer_config_t* config) {
#    ifdef PTECHINOS_EEPROM_READ_WRITE
    config->raw = eeconfig_read_kb();
#    else
    config.raw = 0;
#    endif

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
#    ifdef PTECHINOS_EEPROM_READ_WRITE
    eeconfig_update_kb(config->raw);
#    else
    config.raw = 0;
#    endif
}

// Helper to make it easier to set CPI
static void ptechinos_pointing_device_set_cpi_internal(bool left, uint16_t cpi) {
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
    ptechinos_print_config_to_console("set_cpi", &g_ptechinos_pointer_config);
    switch (side) {
        case PTECHINOS_LEFT:
            if (config->is_dragscroll_left_enabled) {
                ptechinos_pointing_device_set_cpi_internal(true, PTECHINOS_DRAGSCROLL_LEFT);
            } else {
                uint16_t cpi = ptechinos_get_pointer_mousing_cpi(side);
                ptechinos_pointing_device_set_cpi_internal(true, cpi);
            }
            break;
        case PTECHINOS_RIGHT:
            if (config->is_dragscroll_right_enabled) {
                ptechinos_pointing_device_set_cpi_internal(false, PTECHINOS_DRAGSCROLL_RIGHT);
            } else {
                uint16_t cpi = ptechinos_get_pointer_mousing_cpi(side);
                ptechinos_pointing_device_set_cpi_internal(false, cpi);
            }
            break;
    }
}

bool ptechinos_is_pointer_mousing_enabled(pointer_side_t side) {
    bool isMousing = false;
    switch (side) {
        case PTECHINOS_LEFT:
            isMousing = !g_ptechinos_pointer_config.is_dragscroll_left_enabled;
            break;
        case PTECHINOS_RIGHT:
            isMousing = !g_ptechinos_pointer_config.is_dragscroll_right_enabled;
            break;
    }
    return isMousing;
}

void ptechinos_set_pointer_as_mousing(pointer_side_t side) {
    switch (side) {
        case PTECHINOS_LEFT:
            g_ptechinos_pointer_config.is_dragscroll_left_enabled = false;
            break;
        case PTECHINOS_RIGHT:
            g_ptechinos_pointer_config.is_dragscroll_right_enabled = false;
            break;
    }
    // Update device
    ptechinos_pointing_device_set_cpi(&g_ptechinos_pointer_config, side);

    // Non persistent data --> Do nothing
}

uint16_t ptechinos_get_pointer_mousing_cpi(pointer_side_t side) {
    uint16_t cpi;
    switch (side) {
        case PTECHINOS_LEFT:
            cpi = (uint16_t)g_ptechinos_pointer_config.mousing_left_cpi;
            break;
        case PTECHINOS_RIGHT:
            cpi = (uint16_t)g_ptechinos_pointer_config.mousing_right_cpi;
            break;
        default:
            cpi = (uint16_t)0;
            break;
    }

    cpi = cpi * PTECHINOS_MOUSING_CPI_CONFIG_STEP + PTECHINOS_MOUSING_CPI_MIN;
    return cpi;
}

void ptechinos_set_pointer_mousing_cpi(pointer_side_t side, bool increase) {
    // Update config
    switch (side) {
        case PTECHINOS_LEFT:
            if (increase) {
                if (g_ptechinos_pointer_config.mousing_left_cpi < max_cpi_state) {
                    g_ptechinos_pointer_config.mousing_left_cpi += 1u;
                }
            } else if (g_ptechinos_pointer_config.mousing_left_cpi > min_cpi_state) {
                g_ptechinos_pointer_config.mousing_left_cpi -= 1u;
            }
            break;
        case PTECHINOS_RIGHT:
            if (increase) {
                if (g_ptechinos_pointer_config.mousing_right_cpi < max_cpi_state) {
                    g_ptechinos_pointer_config.mousing_right_cpi += 1;
                }
            } else if (g_ptechinos_pointer_config.mousing_right_cpi > min_cpi_state) {
                g_ptechinos_pointer_config.mousing_right_cpi -= 1;
            }
            break;
    }
    // Update device
    ptechinos_pointing_device_set_cpi(&g_ptechinos_pointer_config, side);

    // Persistent data --> update EEPROM
    ptechinos_write_config_to_eeprom(&g_ptechinos_pointer_config);
}

bool ptechinos_is_pointer_dragscroll_enabled(pointer_side_t side) {
    bool isDragscroll = false;
    switch (side) {
        case PTECHINOS_LEFT:
            isDragscroll = g_ptechinos_pointer_config.is_dragscroll_left_enabled;
            break;
        case PTECHINOS_RIGHT:
            isDragscroll = g_ptechinos_pointer_config.is_dragscroll_right_enabled;
            break;
    }

    return isDragscroll;
}

void ptechinos_set_pointer_as_dragscroll(pointer_side_t side) {
    switch (side) {
        case PTECHINOS_LEFT:
            g_ptechinos_pointer_config.is_dragscroll_left_enabled = true;
            break;
        case PTECHINOS_RIGHT:
            g_ptechinos_pointer_config.is_dragscroll_right_enabled = true;
            break;
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

/**
 * @brief      Augment the pointing device behavior with advance drag scroll feature.
 *             Scrolling speed can be controlled using
 *               - PTECHINOS_SCROLL_DIVISOR_H (1.0 to disable raw result scaling)
 *               - PTECHINOS_SCROLL_DIVISOR_V (1.0 to disable raw result scaling)
 *             Borrowed from QMK Oddball keyboard
 *
 * @param      mouse_report  Left or Right mouse report
 */
static void ptechinos_pointing_device_task_drag_scroll(report_mouse_t* mouse_report) {
    // @WARNING Accumulators are shared between both sides
    static int16_t acc_h = 0;
    static int16_t acc_v = 0;
    // @WARNING Accumulators are shared between both sides

    // Update accumulators
    acc_h += mouse_report->x;
    acc_v += mouse_report->y;
    int8_t scaled_scroll_h = acc_h / PTECHINOS_SCROLL_DIVISOR_H;
    int8_t scaled_scroll_v = acc_v / PTECHINOS_SCROLL_DIVISOR_V;

    // Clear accumulators on assignment
    if (scaled_scroll_h != 0) {
#    ifdef PTECHINOS_DRAGSCROLL_INVERT_X
        mouse_report->h = -scaled_scroll_h;
#    else
        mouse_report->h = scaled_scroll_h;
#    endif // PTECHINOS_DRAGSCROLL_INVERT_X
        acc_h = 0;
    }
    if (scaled_scroll_v != 0) {
#    ifdef PTECHINOS_DRAGSCROLL_INVERT_Y
        mouse_report->v = -scaled_scroll_v;
#    else
        mouse_report->v = scaled_scroll_v;
#    endif // PTECHINOS_DRAGSCROLL_INVERT_Y
        acc_v = 0;
    }

    // Disable mousing
    mouse_report->x = 0;
    mouse_report->y = 0;
}

#    if defined(SPLIT_POINTING_ENABLE)
// With SPLIT_POINTING_ENABLE  pointing task is only called on the master side (the one with USB connected)
#        if defined(POINTING_DEVICE_COMBINED)
report_mouse_t pointing_device_task_combined_kb(report_mouse_t left_report, report_mouse_t right_report) {
    // ptechinos_print_mouse_report_to_console("task_drag_scroll (BEFORE)", PTECHINOS_LEFT, &left_report);
    // ptechinos_print_mouse_report_to_console("task_drag_scroll (BEFORE)", PTECHINOS_RIGHT, &right_report);
    if (g_ptechinos_pointer_config.is_dragscroll_left_enabled) {
        ptechinos_pointing_device_task_drag_scroll(&left_report);
    }
    if (g_ptechinos_pointer_config.is_dragscroll_right_enabled) {
        ptechinos_pointing_device_task_drag_scroll(&right_report);
    }
    // ptechinos_print_mouse_report_to_console("task_drag_scroll (AFTER)", PTECHINOS_LEFT, &left_report);
    // ptechinos_print_mouse_report_to_console("task_drag_scroll (AFTER)", PTECHINOS_RIGHT, &right_report);
    return pointing_device_task_combined_user(left_report, right_report);
}
#        elif defined(POINTING_DEVICE_LEFT)
report_mouse_t pointing_device_task_kb(report_mouse_t report) {
    if (g_ptechinos_pointer_config.is_dragscroll_left_enabled) {
        ptechinos_pointing_device_task_drag_scroll(&report);
    }
    return pointing_device_task_user(report);
}
#        elif defined(POINTING_DEVICE_RIGHT)
report_mouse_t pointing_device_task_kb(report_mouse_t report) {
    if (g_ptechinos_pointer_config.is_dragscroll_right_enabled) {
        ptechinos_pointing_device_task_drag_scroll(&report);
    }
    return pointing_device_task_user(report);
}
#        else
#            error "You need to define the side(s) the pointing device is on. POINTING_DEVICE_COMBINED / POINTING_DEVICE_LEFT / POINTING_DEVICE_RIGHT"
#        endif
#    else
report_mouse_t pointing_device_task_kb(report_mouse_t report) {
    if (!is_keyboard_master()) return report;

    if (is_keyboard_left()) {
        if (g_ptechinos_pointer_config.is_dragscroll_left_enabled) {
            ptechinos_pointing_device_task_drag_scroll(&report);
        }
    } else {
        if (g_ptechinos_pointer_config.is_dragscroll_right_enabled) {
            ptechinos_pointing_device_task_drag_scroll(&report);
        }
    }
    report = pointing_device_task_user(report);
    return report;
}
#    endif

void pointing_device_init_kb(void) {
    // Called before keyboard_post_init_kb in keyboard_init (see QMK keyboard.c)
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
    if (!is_keyboard_master()) return;

    pointer_side_t side = is_keyboard_left() ? PTECHINOS_LEFT : PTECHINOS_RIGHT;
    ptechinos_pointing_device_set_cpi(&g_ptechinos_pointer_config, side);
#    endif

    // Already called by pointing_device_init (see QMK pointing_device.c)
    // pointing_device_init_user();
}

//
// AUTO MOUSE (QMK)
//
#    if defined(POINTING_DEVICE_AUTO_MOUSE_ENABLE)
/**
 * @brief Keyboard level callback for adding keyrecords as mouse keys
 */
bool is_mouse_record_kb(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case PL_CPI_UP:
        case PL_CPI_DOWN:
        case PL_DS_TOOGLE:
        case PR_CPI_UP:
        case PR_CPI_DOWN:
        case PR_DS_TOOGLE:
            return true;
    }
    return is_mouse_record_user(keycode, record);
}
#    endif

//
// COMMON (QMK)
//
void eeconfig_init_kb(void) {
    // EEPROM is getting reset!
    // To force an EEPROM reset, use the EE_CLR keycode or Bootmagic Lite functionality
    g_ptechinos_pointer_config.raw               = 0;
    g_ptechinos_pointer_config.mousing_left_cpi  = 2;
    g_ptechinos_pointer_config.mousing_right_cpi = 2;
    ptechinos_write_config_to_eeprom(&g_ptechinos_pointer_config);

    // Reset all devices even if user only use one
    ptechinos_pointing_device_set_cpi(&g_ptechinos_pointer_config, PTECHINOS_LEFT);
    ptechinos_pointing_device_set_cpi(&g_ptechinos_pointer_config, PTECHINOS_RIGHT);

    // Let user do whatever he wants
    eeconfig_init_user();
}

void matrix_init_kb(void) {
    // Safe to read CPI setting from configuration since
    // matrix init comes before pointing device init
    ptechinos_read_config_from_eeprom(&g_ptechinos_pointer_config);
    ptechinos_print_config_to_console("matrix_init_kb", &g_ptechinos_pointer_config);

    matrix_init_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t* record) {
    if (!process_record_user(keycode, record)) {
        // ptechinos_print_config_to_console("process_record_user", &g_ptechinos_pointer_config);
        return false;
    }

    // Pointer specific code
    switch (keycode) {
        case PL_CPI_UP:
            if (record->event.pressed) {
                if (ptechinos_is_pointer_mousing_enabled(PTECHINOS_LEFT)) {
                    // Only update CPI when user can actually see a change
                    ptechinos_set_pointer_mousing_cpi(PTECHINOS_LEFT, true);
                }
            }
            break;
        case PL_CPI_DOWN:
            if (record->event.pressed) {
                if (ptechinos_is_pointer_mousing_enabled(PTECHINOS_LEFT)) {
                    // Only update CPI when user can actually see a change
                    ptechinos_set_pointer_mousing_cpi(PTECHINOS_LEFT, false);
                }
            }
            break;
        case PL_DS_TOOGLE:
            // Simulate dragscroll on hold (pressed / released)
            ptechinos_toogle_pointer_between_mousing_dragscroll(PTECHINOS_LEFT);
            // if (record->event.pressed) {
            //     // Toogle between drag and mouse mode
            //     ptechinos_toogle_pointer_between_mousing_dragscroll(PTECHINOS_LEFT);
            // }
            break;
        case PR_CPI_UP:
            if (record->event.pressed) {
                if (ptechinos_is_pointer_mousing_enabled(PTECHINOS_RIGHT)) {
                    // Only update CPI when user can actually see a change
                    ptechinos_set_pointer_mousing_cpi(PTECHINOS_RIGHT, true);
                }
            }
            break;
        case PR_CPI_DOWN:
            if (record->event.pressed) {
                if (ptechinos_is_pointer_mousing_enabled(PTECHINOS_RIGHT)) {
                    // Only update CPI when user can actually see a change
                    ptechinos_set_pointer_mousing_cpi(PTECHINOS_RIGHT, false);
                }
            }
            break;
        case PR_DS_TOOGLE:
            // Simulate dragscroll on hold (pressed / released)
            ptechinos_toogle_pointer_between_mousing_dragscroll(PTECHINOS_RIGHT);
            // if (record->event.pressed) {
            //     // Toogle between drag and mouse mode
            //     ptechinos_toogle_pointer_between_mousing_dragscroll(PTECHINOS_RIGHT);
            // }
            break;
    }
    // ptechinos_print_config_to_console("process_record_kb", &g_ptechinos_pointer_config);

    return true;
}

#endif

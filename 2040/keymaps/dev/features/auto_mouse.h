#pragma once

#include QMK_KEYBOARD_H

#include "action.h"
#include "report.h"

typedef struct {
    uint8_t  layer;     // Layer to activate
    uint16_t timeout;   // Layer activation timeout if unused
    uint8_t  key_delay; // Time delay after a key press / release
    uint8_t  debounce;  // Time delay from last activation to next update
    uint8_t  threshold; // Minimal movement to turn on the auto mouse layer
} auto_mouse_config_t;

typedef struct {
    uint16_t            active_timer;      // Keep track of the mouse layer activation time
    uint16_t            key_timer;         // Keep track of the last time a non mousekey was used
    uint16_t            mouse_key_tracker; // Keep track of pressed / hold keys on mouse layer
    bool                is_enabled;
    auto_mouse_config_t config;
} auto_mouse_data_t;

// Default value for the auto mouse layer configuration
#ifndef PTECHINOS_AUTO_MOUSE_LAYER
#    define PTECHINOS_AUTO_MOUSE_LAYER 0 // Layer to activate
#endif

#ifndef PTECHINOS_AUTO_MOUSE_TIMEOUT
#    define PTECHINOS_AUTO_MOUSE_TIMEOUT 700 // Layer activation timeout if unused
#endif

#ifndef PTECHINOS_AUTO_MOUSE_KEY_DELAY
#    define PTECHINOS_AUTO_MOUSE_KEY_DELAY (TAPPING_TERM + 20) // Time delay after a key press / release
#endif

#ifndef PTECHINOS_AUTO_MOUSE_DEBOUNCE
#    define PTECHINOS_AUTO_MOUSE_DEBOUNCE 40 // Time delay from last activation to next update
#endif

#ifndef PTECHINOS_AUTO_MOUSE_ACTIVATION_THRESHOLD
#    define PTECHINOS_AUTO_MOUSE_ACTIVATION_THRESHOLD 4 // Minimal movement to turn on the auto mouse layer
#endif

/**
 * @brief      Enable of disable the auto_mouse feature.
 *
 * @param[in]  is_enabled  Indicates if enabled
 */
void auto_mouse_set_enabled(bool is_enabled);

/**
 * @brief      Set auto mouse layer.
 *
 * @param[in]  mouse_layer  The mouse layer
 */
void auto_mouse_set_layer(uint8_t mouse_layer);

/**
 * @brief      Assign user defined configuration.
 *
 * @param[in]  user_config  The user configuration
 */
void auto_mouse_init(auto_mouse_config_t user_config);

/**
 * @brief      Turn the mouse layer on if feature is active.
 */
void auto_mouse_set_active(void);

/**
 * @brief      Event raised when layer is set active
 *
 * @param      context  The auto mouse context / configuration
 */
void auto_mouse_on_layer_active(auto_mouse_data_t* context);

/**
 * @brief      Turn the mouse layer off.
 */
void auto_mouse_set_inactive(void);

/**
 * @brief      Event raised when layer is set inactive
 *
 * @param      context  The auto mouse context / configuration
 */
void auto_mouse_on_layer_inactive(auto_mouse_data_t* context);

/**
 * @brief      Indicates if the auto mouse layer is on or off.
 *
 * @return     True if the auto mouse layer is on else false.
 */
bool auto_mouse_is_active(void);

/**
 * @brief      Update auto mouse layer state on key report. Must be called from
 *             process_record_kb or process_record_user
 *
 * @param[in]  keycode  The keycode
 * @param      record   The record
 */
void auto_mouse_on_process_record(uint16_t keycode, keyrecord_t* record);

/**
 * @brief      Update auto mouse layer state on mouse report Must be called from
 *             pointing_device_task_kb or pointing_device_task_user.
 *
 * @param[in]  mouse_report  The mouse report
 */
void auto_mouse_on_pointing_device_task(report_mouse_t mouse_report);

/**
 * @brief      Control if a key should or not turn off the auto mouse layer. Do some
 *             processing and also call <auto_mou _user> which is the preferred entry
 *             point for user configuration.
 *
 * @param[in]  keycode  The keycode
 * @param      record   The record
 *
 * @return     True if keycode should turn off the auto mouse layer else false.
 */
bool auto_mouse_should_exit(uint16_t keycode, keyrecord_t* record);

/**
 * @brief      User level control of which keys turns off the auto mouse layer
 *
 * @param[in]  keycode  The keycode
 * @param      record   The record
 *
 * @return     True if keycode should turn off the auto mouse layer else false.
 */
bool auto_mouse_should_exit_user(uint16_t keycode, keyrecord_t* record);

#include "keyboard.h"
#include "quantum.h"

#include "auto_mouse.h"

#ifdef CONSOLE_ENABLE
#    include "print.h"
#endif // CONSOLE_ENABLE

static auto_mouse_data_t auto_mouse_context = {.active_timer = (uint16_t)0,
                                               .key_timer    = (uint16_t)0,
                                               .is_enabled   = false,
                                               .config       = {
                                                         .layer     = (uint8_t)(PTECHINOS_AUTO_MOUSE_LAYER),
                                                         .timeout   = (uint16_t)(PTECHINOS_AUTO_MOUSE_TIMEOUT),
                                                         .key_delay = (uint16_t)(PTECHINOS_AUTO_MOUSE_KEY_DELAY),
                                                         .debounce  = (uint8_t)(PTECHINOS_AUTO_MOUSE_DEBOUNCE),
                                                         .threshold = (uint8_t)(PTECHINOS_AUTO_MOUSE_ACTIVATION_THRESHOLD),
                                               }};
// clang-format off
static void auto_mouse_debug(const char* location)
{
    #    ifdef CONSOLE_ENABLE
    dprintf("[Auto Mouse (%s)] \n"
            "  Status {\n"
            "\tis_enabled=%d\n"
            "\tis_active=%d \tis_layer_on=%d\n"
            "\tactive_timer=%u\n"
            "\tkey_timer=%u\n"
            "\t}\n"
            "  Config {\n"
            "\tlayer=%u\n"
            "\ttimeout=%u\n"
            "\tkey_delay=%u\n"
            "\tdebounce=%u\n"
            "\tthreshold=%u\n"
            "\t}\n",
            location,
            (int)auto_mouse_context.is_enabled,
            (int)auto_mouse_is_active(),
            (int)layer_state_is(auto_mouse_context.config.layer),
            (uint)auto_mouse_context.active_timer,
            (uint)auto_mouse_context.key_timer,
            (uint)auto_mouse_context.config.layer,
            (uint)auto_mouse_context.config.timeout,
            (uint)auto_mouse_context.config.key_delay,
            (uint)auto_mouse_context.config.debounce,
            (uint)auto_mouse_context.config.threshold
            );
#    endif // CONSOLE_ENABLE
}
// clang-format on

void auto_mouse_set_active(void) {
    if (!auto_mouse_context.is_enabled) {
        return;
    }
    auto_mouse_debug("set_active");

    auto_mouse_context.active_timer = timer_read();
    if (!layer_state_is(auto_mouse_context.config.layer)) {
        layer_on(auto_mouse_context.config.layer);
    }
}

void auto_mouse_set_inactive(void) {
    auto_mouse_debug("set_inactive");

    auto_mouse_context.active_timer = 0.0;
    if (layer_state_is(auto_mouse_context.config.layer)) {
        layer_off(auto_mouse_context.config.layer);
    }
}

bool auto_mouse_is_active(void) {
    return auto_mouse_context.is_enabled && layer_state_is(auto_mouse_context.config.layer);
}

void auto_mouse_set_enabled(bool is_enabled) {
    auto_mouse_context.is_enabled = is_enabled;
}

void auto_mouse_set_layer(uint8_t mouse_layer) {
    auto_mouse_context.config.layer = mouse_layer;
}

void auto_mouse_init(auto_mouse_config_t user_config) {
    auto_mouse_context.config = user_config;
}

void auto_mouse_on_process_record(uint16_t keycode, keyrecord_t* record) {
    // Do nothing when feature is disabled
    if (!auto_mouse_context.is_enabled) {
        return;
    }
    if (!auto_mouse_is_active()) {
        // Auto mouse layer is off
        if (IS_EVENT(record->event)) {
            auto_mouse_context.key_timer = timer_read();
            return;
        }
    }

    // @TODO Handle hold by using a key down counter
    // Auto mouse layer is on
    bool isExitKey = auto_mouse_should_exit(keycode, record);
    if (isExitKey) {
        auto_mouse_set_inactive();
        auto_mouse_context.key_timer = timer_read();
    } else {
        auto_mouse_context.active_timer = timer_read();
    }
}

__attribute__((weak)) bool auto_mouse_should_exit_user(uint16_t keycode, keyrecord_t* record) {
    return false;
}

__attribute__((weak)) bool auto_mouse_should_exit(uint16_t keycode, keyrecord_t* record) {
    bool should_exit = false;
    switch (keycode) {
        case QK_TOGGLE_LAYER ... QK_TOGGLE_LAYER_MAX:
            if (QK_TOGGLE_LAYER_GET_LAYER(keycode) != auto_mouse_context.config.layer) {
                should_exit = true;
            }
            break;
        case QK_TO ... QK_TO_MAX:
            if (QK_TO_GET_LAYER(keycode) != auto_mouse_context.config.layer) {
                if (record->event.pressed) {
                    should_exit = true;
                }
            }
            break;
        default:
            break;
    }

    return should_exit || auto_mouse_should_exit_user(keycode, record);
}

void auto_mouse_on_pointing_device_task(report_mouse_t mouse_report) {
    // Do nothing is feature is disabled
    if (!auto_mouse_context.is_enabled) {
        return;
    }

    // Avoid on / off using a small delay after activation
    if (timer_elapsed(auto_mouse_context.active_timer) <= auto_mouse_context.config.debounce) {
        return;
    }

    // Avoid spurious activation using a small delay on each non mouse key press
    if (timer_elapsed(auto_mouse_context.key_timer) <= auto_mouse_context.config.key_delay) {
        return;
    }

    // Preprocessing of mouse report data
    const uint8_t distance       = abs(mouse_report.x) + abs(mouse_report.y);
    const uint8_t scroll         = abs(mouse_report.h) + abs(mouse_report.v);
    const bool    button_pressed = mouse_report.buttons;

    if (!auto_mouse_is_active()) {
        // Avoid spurious activation using a threshold to discard false positive
        if (distance > auto_mouse_context.config.threshold || scroll > auto_mouse_context.config.threshold || button_pressed) {
            auto_mouse_set_active();
        }
    } else {
        if (distance > 0 || scroll > 0 || button_pressed) {
            auto_mouse_context.active_timer = timer_read();
        }

        // Check if layer should be deactivated
        if (timer_elapsed(auto_mouse_context.active_timer) > auto_mouse_context.config.timeout) {
            auto_mouse_set_inactive();
        }
    }
}
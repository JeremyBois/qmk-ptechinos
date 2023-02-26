#include "swapper.h"

bool update_swapper(bool *active, uint16_t cmdish, uint16_t tabish, uint16_t trigger, uint16_t keycode, keyrecord_t *record) {
    bool modTapHandled = false;
    bool oldState = *active;
    if (keycode == trigger) {
        switch (keycode) {
            // Handle custom keycode detection when using mod tap
            // https://docs.qmk.fm/#/mod_tap?id=intercepting-mod-taps
            case QK_MOD_TAP ... QK_MOD_TAP_MAX:
                if (record->tap.count) {
                    if (record->event.pressed) {
                        if (!*active) {
                            *active = true;
                            register_code(cmdish);
                        }
                        register_code(tabish);
                    } else {
                        unregister_code(tabish);
                        // Don't unregister cmdish until some other key is hit or released.
                    }
                    // Required to avoid weird bug on Windows that send random event like LaunchApp2
                    // on key pressed
                    modTapHandled = true;
                } else {
                    // On modifier held
                    unregister_code(cmdish);
                    *active = false;
                }
                break;
            default:
                if (record->event.pressed) {
                    if (!*active) {
                        *active = true;
                        register_code(cmdish);
                    }
                    register_code(tabish);
                } else {
                    unregister_code(tabish);
                    // Don't unregister cmdish until some other key is hit or released.
                }
                break;
        }
    } else if (*active) {
        unregister_code(cmdish);
        *active = false;
    }

    // True when key should be discarded
    //   - mod tap
    //   - cancel key pressed
    return (modTapHandled || (!*active && oldState));
}

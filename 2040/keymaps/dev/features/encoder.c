#ifdef ENCODER_ENABLE

#    include "quantum.h"
#    include "customCodes.h"

#    include "encoder.h"

// @NOTE Delay (>10) required on media keys to avoid computer to ignore / not receiving it

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        // Upper left encoder
        if (clockwise) {
            tap_code_delay(KC_VOLU, 20);
        } else {
            tap_code_delay(KC_VOLD, 20);
        }
    } else if (index == 1) {
        // Lower left encoder
        if (clockwise) {
            tap_code16_delay(C(A(KC_RIGHT)), 20);
        } else {
            tap_code16_delay(C(A(KC_LEFT)), 20);
        }
    } else if (index == 2) {
        // Upper right encoder
        if (clockwise) {
            tap_code16_delay(C(A(KC_RIGHT)), 20);
        } else {
            tap_code16_delay(C(A(KC_LEFT)), 20);
        }
    } else if (index == 3) {
        // Lower right encoder
        if (clockwise) {
            tap_code_delay(KC_VOLU, 20);
        } else {
            tap_code_delay(KC_VOLD, 20);
        }
    }

    return false;
}

#endif

#ifdef ENCODER_ENABLE

#    include "encoder.h"
#    include "customCodes.h"

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        // Upper left encoder
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 1) {
        // Lower left encoder
        if (clockwise) {
            tap_code16(C(A(KC_RIGHT)));
        } else {
            tap_code16(C(A(KC_LEFT)));
        }
    } else if (index == 2) {
        // Upper right encoder
        if (clockwise) {
            tap_code16(C(A(KC_RIGHT)));
        } else {
            tap_code16(C(A(KC_LEFT)));
        }
    } else if (index == 3) {
        // Lower right encoder
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }

    return true;
}

#endif

#ifdef ENCODER_ENABLE

#    include "encoder.h"
#    include "customCodes.h"

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        // Volume control
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 1) {
        // Scroll history
        if (clockwise) {
            tap_code16(C(A(KC_RIGHT)));
            // tap_code(KC_VOLU);
        } else {
            tap_code16(C(A(KC_LEFT)));
            // tap_code(KC_VOLD);
        }
    }
    return true;
}

#endif

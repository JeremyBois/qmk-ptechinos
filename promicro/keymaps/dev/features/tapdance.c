#include "tapdance.h"

#ifdef TAP_DANCE_ENABLE
// Keep track of modifiers state to handle accented character better
static uint8_t tap_dance_mod_state;


td_state_t complex_dance(qk_tap_dance_state_t *state) {
    // Keep global mode state
    tap_dance_mod_state = get_mods();

    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else
            return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (state->interrupted)
            return TD_DOUBLE_SINGLE_TAP;
        else if (state->pressed)
            return TD_DOUBLE_HOLD;
        else
            return TD_DOUBLE_TAP;
    }

    // Assumes no one is trying to type the same letter three times
    if (state->count == 3) {
        if (state->interrupted || !state->pressed)
            return TD_TRIPLE_TAP;
        else
            return TD_TRIPLE_HOLD;
    }

    return TD_UNKNOWN;
}
#endif

void tap_key_with_mods(uint16_t keycode, uint8_t mods) {
    uint8_t prev_mods = get_mods();

    clear_mods();
    clear_keyboard();
    add_key(keycode);
    if (mods) set_mods(mods);
    send_keyboard_report();
    del_key(keycode);
    clear_mods();
    send_keyboard_report();
    set_mods(prev_mods);
    send_keyboard_report();
};

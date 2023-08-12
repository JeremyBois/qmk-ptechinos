#include "utility.h"

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

void tap_undead_key(uint16_t code) {
    tap_code16(code);
    tap_code16(KC_SPACE);
}

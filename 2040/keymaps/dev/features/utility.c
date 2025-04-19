#include "action.h"
#include "action_util.h"
#include "modifiers.h"
#include "quantum.h"

#include "utility.h"

void tap_key_with_mods(uint16_t keycode, uint8_t mods) {
    uint8_t prev_mods = get_mods();

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

void tap_with_dead_key_with_mods(uint16_t dead_code, uint16_t key_code, uint8_t mods, bool shift) {
    tap_key_with_mods(dead_code, mods);
    if (shift)
        tap_code16(S(key_code));
    else
        tap_code16(key_code);
}

void tap_with_dead_key_no_mods(uint16_t dead_code, uint16_t key_code, bool shift) {
    tap_key_with_mods(dead_code, 0U);
    if (shift)
        tap_code16(S(key_code));
    else
        tap_code16(key_code);
}

void tap_with_dead_key(uint16_t dead_code, uint16_t key_code, bool shift) {
    tap_code16(dead_code);
    if (shift)
        tap_code16(S(key_code));
    else
        tap_code16(key_code);
}


bool is_weak_mod_active(uint8_t mod) {
    return (get_weak_mods() & mod) == mod;
}


bool is_mod_active(uint8_t mods, uint8_t mod) {
    return (mods & mod) == mod;
}

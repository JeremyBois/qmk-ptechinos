#pragma once

#include QMK_KEYBOARD_H

/**
 * @brief      Force a specific set of modifier when taping a key.
 *             Useful for example to get È when shift is enabled instead of Ẽ
 * @note       https://github.com/qmk/qmk_firmware/issues/1708#issuecomment-432442389
 *
 * @param[in]  keycode  The keycode
 * @param[in]  mods     The mods
 */
void tap_key_with_mods(uint16_t keycode, uint8_t mods);

/**
 * @brief      Force undead key on a single key press
 *
 * @param[in]  code  The code
 */
void tap_undead_key(uint16_t code);

/**
 * @brief      Combine a dead key with a normal one.
 *
 * @param[in]  dead_code  The dead key code
 * @param[in]  key_code   The normal key code
 * @param[in]  mods       Mods that must be added to the dead code
 * @param[in]  shift      True to shift the key code
 */
void tap_with_dead_key_with_mods(uint16_t dead_code, uint16_t key_code, uint8_t mods, bool shift);
void tap_with_dead_key_no_mods(uint16_t dead_code, uint16_t key_code, bool shift);
void tap_with_dead_key(uint16_t dead_code, uint16_t key_code, bool shift);


bool is_weak_mod_active(uint8_t mod);
bool is_mod_active(uint8_t mods, uint8_t mod);

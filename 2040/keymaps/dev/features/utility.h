#pragma once

#include QMK_KEYBOARD_H

/**
 * @brief      Force a specific set of modifier when taping a key.
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

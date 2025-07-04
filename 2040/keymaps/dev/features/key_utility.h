#pragma once

#include QMK_KEYBOARD_H
#include "action.h"

bool tap_dead_key_sequence(const keyrecord_t* record, uint16_t trigger, uint16_t dead, uint16_t key, uint8_t deadMask);

bool tap_key_sequence(const keyrecord_t* record, uint16_t trigger, const uint16_t* keys, uint8_t num_keys, uint8_t mods);

bool tap_two_key_sequence(const keyrecord_t* record, uint16_t trigger, uint16_t first, uint16_t second, uint8_t mods);

bool tap_three_key_sequence(const keyrecord_t* record, uint16_t trigger, uint16_t first, uint16_t second, uint16_t third, uint8_t mods);

bool tap_key_with_mods(const keyrecord_t* record, uint16_t trigger, uint16_t key, uint8_t mods);

// Backup modifier state
void sync_mods_state(void);

// Revert modifiers state
void reset_mods_state(void) ;

// Remove all modifiers
void clear_mods_state(void) ;

// Remove any modifier from the current state
// mods can be any packed modifier like MOD_MASK_SHIFT
void del_mods_state(uint8_t mods);

bool is_weak_mod_active(uint8_t mod);

bool is_oneshot_mod_active(uint8_t mods, uint8_t mod);

bool is_mod_active(uint8_t mods, uint8_t mod);

// Used to extract the basic tapping keycode from a dual-role key.
// Example: get_tap_key(MT(MOD_RSFT, KC_E)) == KC_E
uint8_t get_tap_key(uint16_t dual_role_key);

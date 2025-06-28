#pragma once

#include QMK_KEYBOARD_H
#include "action.h"

// CAPS_WORD_LOCK: A "smart" Caps Lock key that only capitalizes the next identifier you type
// and then toggles off Caps Lock automatically when you're done.

// ----
// Mainly extracted from precondition user code
// https://github.com/precondition/dactyl-manuform-keymap/blob/main/keymap.c
// ----


bool is_caps_word_lock_on(void);

void caps_word_lock_enable(void);

void caps_word_lock_disable(void);

void sync_caps_word_lock_on(void);

void process_caps_word_lock(uint16_t keycode, const keyrecord_t *record);

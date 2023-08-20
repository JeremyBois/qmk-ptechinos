#pragma once

#include QMK_KEYBOARD_H

// ----
// Mainly extracted from kapJI user code
// https://gist.github.com/NotGate/3e3d8ab81300a86522b2c2549f99b131
// ----

void process_repeat_key(uint16_t keycode, const keyrecord_t *record, uint16_t repeatKeycode);

uint16_t get_last_pressed_keycode(void);

#pragma once

#include "config_common.h"

/* Key matrix size */
#define MATRIX_ROWS 8 // Rows are doubled-up
#define MATRIX_COLS 5

/* Encoder support
 * Same pins / resolution on both sides
 * Encoders reference : EVQWGD001
 * https://github.com/qmk/qmk_firmware/blob/master/docs/feature_encoders.md
 */
#define ENCODER_DEFAULT_POS 0x3

/* VIA */
#define DYNAMIC_KEYMAP_LAYER_COUNT 7

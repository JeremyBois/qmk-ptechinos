#pragma once

#include "config_common.h"

/* USB Device descriptor parameters */
#define VENDOR_ID 0x7466  // JB
#define PRODUCT_ID 0x5053 // PS
#define DEVICE_VER 0x0005
#define MANUFACTURER JeremyBois
#define PRODUCT Ptechinos

/* Key matrix size */
#define MATRIX_ROWS 8 // Rows are doubled-up
#define MATRIX_COLS 5

/*
 * Keyboard Matrix Assignments
 * ROWS: AVR pins used for rows, top to bottom
 * COLS: AVR pins used for columns, left to right
 * DIODE_DIRECTION :
 *  COL2ROW = COL = Anode(+), ROW = Cathode(-, marked on diode)
 *  ROW2COL = ROW = Anode(+), COL = Cathode(-, marked on diode)
 */
#define MATRIX_ROW_PINS \
    { D7, E6, B4, B5 }
#define MATRIX_COL_PINS \
    { F7, B1, B3, B2, B6 }
#define DIODE_DIRECTION COL2ROW

/* Encoder support
 * Same pins / resolution on both sides
 * Encoders reference : EVQWGD001
 * https://github.com/qmk/qmk_firmware/blob/master/docs/feature_encoders.md
 */
#define ENCODERS_PAD_A \
    { F5 }
#define ENCODERS_PAD_B \
    { F4 }
#define ENCODERS_PAD_A_RIGHT \
    { F5 }
#define ENCODERS_PAD_B_RIGHT \
    { F4 }
#define ENCODER_RESOLUTIONS \
    { 4 }
#define ENCODER_RESOLUTIONS_RIGHT \
    { 4 }
#define ENCODER_DEFAULT_POS 0x3

/*
 * Split Keyboard specific options,
 * 'SPLIT_KEYBOARD = yes' should be your rules.mk
 */
#define USE_SERIAL
#define SOFT_SERIAL_PIN D2 // pin used for data communication between halves

/* General */
#define TAPPING_TERM 100
#define DEBOUNCE 2  // Default is 5 (lower is better)
#define TAP_CODE_DELAY 10

/* VIA */
#define DYNAMIC_KEYMAP_LAYER_COUNT 7

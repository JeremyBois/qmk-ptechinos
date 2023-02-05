#pragma once

#include "config_common.h"

// ┌─────────────────────────────────────────────────┐
// │ Split communication                             │
// └─────────────────────────────────────────────────┘
// PIO driver with USART Half-duplex
//   LEFT                      RIGHT
// +-------+  |           |  +-------+
// |       |  R           R  |       |
// |       |  |   SERIAL  |  |       |
// |    TX |-----------------| TX    |
// |       |       VDD       |       |
// |       |-----------------|       |
// |       |       GND       |       |
// |       |-----------------|       |
// +-------+                 +-------+
// https://github.com/qmk/qmk_firmware/blob/master/docs/serial_driver.md#the-pio-driver
// https://qmk.github.io/qmk_mkdocs/master/en/serial_driver/#usart-half-duplex
// Force the usage of PIO1 peripheral as TX (RP2040)
#define SERIAL_PIO_USE_PIO1

// ┌─────────────────────────────────────────────────┐
// │ Bootloader                                      │
// └─────────────────────────────────────────────────┘
// Allow to double tap the reset button to enter into bootloader mode (closest to single tap on AVR)
// https://github.com/qmk/qmk_firmware/blob/master/docs/platformdev_rp2040.md#pre-defined-rp2040-boards
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET // Default on Generic Pro Micro RP2040
// Timeout window in ms in which the double tap can occur.
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 500U
// Specify a optional status led by GPIO number which blinks when entering the bootloader
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP17 // Default on Generic Pro Micro RP2040
// Linux fstab configuration to be able to mount it easily
// LABEL=RPdI-RP2  /mnt/kb2040 vfat rw,relatime,noauto,fmask=0022,dmask=0022,utf8 0 2

// ┌─────────────────────────────────────────────────┐
// │ Encoder                                         │
// └─────────────────────────────────────────────────┘
// Encoders reference : EVQWGD001
// https://github.com/qmk/qmk_firmware/blob/master/docs/feature_encoders.md
#define ENCODER_DEFAULT_POS 0x3

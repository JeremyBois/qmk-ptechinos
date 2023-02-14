#pragma once

// https://github.com/qmk/qmk_firmware/blob/master/docs/i2c_driver.md#arm-configuration

// ┌─────────────────────────────────────────────────┐
// │ Serial half duplex                              │
// └─────────────────────────────────────────────────┘
// RP2040 driver

// ┌─────────────────────────────────────────────────┐
// │ Trackpad / OLED                                 │
// └─────────────────────────────────────────────────┘
// Define at the user level (rules.mk)
// #define HAL_USE_I2C TRUE

// ┌─────────────────────────────────────────────────┐
// │ Trackball                                       │
// └─────────────────────────────────────────────────┘
// Define at the user level (rules.mk)
// #define HAL_USE_SPI TRUE
#define SPI_USE_WAIT TRUE
#define SPI_SELECT_MODE SPI_SELECT_MODE_PAD

#include_next <halconf.h>

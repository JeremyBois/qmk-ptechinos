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
#include_next <halconf.h>

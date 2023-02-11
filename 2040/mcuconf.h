#pragma once

// https://github.com/qmk/qmk_firmware/blob/master/docs/i2c_driver.md#arm-configuration

#include_next <mcuconf.h>

// ┌─────────────────────────────────────────────────┐
// │ Serial half duplex                              │
// └─────────────────────────────────────────────────┘
// RP2040 driver

// ┌─────────────────────────────────────────────────┐
// │ Trackpad / OLED                                 │
// └─────────────────────────────────────────────────┘
// https://learn.adafruit.com/adafruit-kb2040/pinouts
// https://qmk.github.io/qmk_mkdocs/master/en/i2c_driver
// https://github.com/qmk/qmk_firmware/blob/master/docs/platformdev_rp2040.md#i2c-driver
#undef RP_I2C_USE_I2C1
#define RP_I2C_USE_I2C1 TRUE

#pragma once

// https://github.com/qmk/qmk_firmware/blob/master/docs/i2c_driver.md#arm-configuration

// ┌─────────────────────────────────────────────────┐
// │ Serial half duplex                              │
// └─────────────────────────────────────────────────┘
// RP2040 driver

// ┌─────────────────────────────────────────────────┐
// │ Trackpad                                        │
// └─────────────────────────────────────────────────┘
#if defined(POINTING_DEVICE_ENABLE) && (POINTING_DEVICE_DRIVER == cirque_pinnacle_i2c)
#    define HAL_USE_I2C TRUE
#endif

// ┌─────────────────────────────────────────────────┐
// │ Trackball                                       │
// └─────────────────────────────────────────────────┘
// Define at the user level (rules.mk)
#if defined(POINTING_DEVICE_ENABLE) && (POINTING_DEVICE_DRIVER == pmw3360)
#    undef HAL_USE_SPI
#    define HAL_USE_SPI TRUE
#    undef SPI_USE_WAIT
#    define SPI_USE_WAIT TRUE
#    undef SPI_SELECT_MODE
#    define SPI_SELECT_MODE SPI_SELECT_MODE_PAD
#endif

#include_next <halconf.h>

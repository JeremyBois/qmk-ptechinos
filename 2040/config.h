#pragma once

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

#ifdef POINTING_DEVICE_ENABLE
// ┌─────────────────────────────────────────────────┐
// │ Cirque Trackpad                                 │
// └─────────────────────────────────────────────────┘
// Driver / Wiring
// https://github.com/qmk/qmk_firmware/blob/master/docs/platformdev_rp2040.md#i2c-driver
// https://github.com/qmk/qmk_firmware/blob/master/docs/i2c_driver.md
#    define I2C1_SDA_PIN GP2 // Default on Generic Pro Micro RP2040
#    define I2C1_SCL_PIN GP3 // Default on Generic Pro Micro RP2040
#    define I2C1_CLOCK_SPEED 100000

// Common settings
// https://docs.qmk.fm/#/feature_pointing_device?id=common-settings
#    define CIRQUE_PINNACLE_DIAMETER_MM 35
#    define CIRQUE_PINNACLE_ATTENUATION EXTREG__TRACK_ADCCONFIG__ADC_ATTENUATE_4X
// I2C settings
#    define CIRQUE_PINNACLE_ADDR 0x2A
#    define CIRQUE_PINNACLE_TIMEOUT 20
// Limits the frequency that the sensor is polled for motion
#    define POINTING_DEVICE_TASK_THROTTLE_MS 10

// ┌─────────────────────────────────────────────────┐
// │ PWM3360 Trackball                               │
// └─────────────────────────────────────────────────┘
// https://github.com/qmk/qmk_firmware/blob/master/docs/platformdev_rp2040.md#spi-driver
#    define SPI_DRIVER SPID0
#    define SPI_SCK_PIN GP2
#    define SPI_MOSI_PIN GP3
#    define SPI_MISO_PIN GP4
#    define POINTING_DEVICE_CS_PIN GP5
// #    define ADNS9800_CS_PIN POINTING_DEVICE_CS_PIN  // default
// #    define PMW33XX_CS_PIN POINTING_DEVICE_CS_PIN  // default
#    define PMW33XX_CLOCK_SPEED 2000000
#    define PMW33XX_LIFTOFF_DISTANCE 0x02  // default
#    define PMW33XX_CPI 800
// #    define ROTATIONAL_TRANSFORM_ANGLE -90 // Horizontal
#    define ROTATIONAL_TRANSFORM_ANGLE 0   // Vertical
#endif

// ┌─────────────────────────────────────────────────┐
// │ CRC                                             │
// └─────────────────────────────────────────────────┘
// https://github.com/qmk/qmk_firmware/pull/12641
// Data validation in split transport code (trackball on slave side)
#define CRC8_USE_TABLE
#define CRC8_OPTIMIZE_SPEED

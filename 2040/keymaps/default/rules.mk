# Easy definition of combos
VPATH +=  keyboards/gboards/

# Sources
SRC += features/encoder.c
SRC += features/utility.c
SRC += features/swapper.c
SRC += features/switcher.c
SRC += features/leader.c
SRC += features/repeat.c

# Allow user to control which pointing device to use
ifeq ($(strip $(trackpad)), true)
    # ┌─────────────────────────────────────────────────┐
	# │ Cirque Trackpad                                 │
	# └─────────────────────────────────────────────────┘
	POINTING_DEVICE_ENABLE = yes
	POINTING_DEVICE_DRIVER = cirque_pinnacle_i2c
	OPT_DEFS += -DHAL_USE_I2C=TRUE
endif
ifeq ($(strip $(trackball)), true)
	# ┌─────────────────────────────────────────────────┐
	# │ PWM3360 Trackball                               │
	# └─────────────────────────────────────────────────┘
	POINTING_DEVICE_ENABLE = yes
	POINTING_DEVICE_DRIVER = pmw3360
	OPT_DEFS += -DHAL_USE_SPI=TRUE
endif


# Easy definition of combos
VPATH +=  keyboards/gboards/

# Sources
SRC += features/encoder.c
SRC += features/utility.c
SRC += features/swapper.c
SRC += features/switcher.c
SRC += features/repeat.c

# Allow user to control which pointing device to use
ifeq ($(strip $(trackpad)), true)
    # ┌─────────────────────────────────────────────────┐
	# │ Cirque Trackpad                                 │
	# └─────────────────────────────────────────────────┘
	POINTING_DEVICE_ENABLE = yes
	POINTING_DEVICE_DRIVER = cirque_pinnacle_i2c
endif
ifeq ($(strip $(trackball)), true)
	# ┌─────────────────────────────────────────────────┐
	# │ PWM3360 Trackball                               │
	# └─────────────────────────────────────────────────┘
	POINTING_DEVICE_ENABLE = yes
	POINTING_DEVICE_DRIVER = pmw3360
endif

# Unicode maps
UNICODEMAP_ENABLE = yes

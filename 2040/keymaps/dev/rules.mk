# Easy definition of combos
VPATH +=  keyboards/gboards/

#
# Pointing device options
#
ifeq ($(strip $(trackpad)), true)
    # ┌───────────────────────────────────────────────────────────────┐
	# │ Cirque Trackpad                                               │
	# └───────────────────────────────────────────────────────────────┘
	POINTING_DEVICE_ENABLE = yes
	POINTING_DEVICE_DRIVER = cirque_pinnacle_i2c
	OPT_DEFS += -DPTECHINOS_POINTING_DEVICE_ENABLE=yes
endif

ifeq ($(strip $(trackball)), true)
	# ┌───────────────────────────────────────────────────────────────┐
	# │ PWM3360 Trackball                                             │
	# └───────────────────────────────────────────────────────────────┘
	POINTING_DEVICE_ENABLE = yes
	POINTING_DEVICE_DRIVER = pmw3360
	OPT_DEFS += -DPTECHINOS_POINTING_DEVICE_ENABLE=yes
endif

ifeq ($(strip $(auto_mouse)), true)
	# ┌───────────────────────────────────────────────────────────────┐
	# │ Custom auto mouse                                             │
	# └───────────────────────────────────────────────────────────────┘
	OPT_DEFS += -DPTECHINOS_AUTO_MOUSE_ENABLE=yes
	SRC += features/auto_mouse.c
endif

# Unicode maps
UNICODEMAP_ENABLE = yes

# Repeat
REPEAT_KEY_ENABLE = yes

# Sources
SRC += features/encoder.c
SRC += features/utility.c
SRC += features/swapper.c
SRC += features/switcher.c
SRC += features/auto_mouse.c


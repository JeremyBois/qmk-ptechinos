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


#
# Mouse keys options
#
ifeq ($(strip $(kinetic)), true)
	# ┌───────────────────────────────────────────────────────────────┐
	# │ Enable mouse kinetic mode                                     │
	# └───────────────────────────────────────────────────────────────┘
	OPT_DEFS += -DMOUSEKEY_KINETIC=yes
endif

ifeq ($(strip $(constant_hold)), true)
	# ┌───────────────────────────────────────────────────────────────┐
	# │ Enable mouse constant (hold mode)                             │
	# └───────────────────────────────────────────────────────────────┘
	OPT_DEFS += -DMOUSEKEY_CONSTANT=yes
	OPT_DEFS += -DMOUSEKEY_CONSTANT_HOLD=yes
endif

ifeq ($(strip $(constant_tap)), true)
	# ┌───────────────────────────────────────────────────────────────┐
	# │ Enable mouse constant (tap mode)                              │
	# └───────────────────────────────────────────────────────────────┘
	OPT_DEFS += -DMOUSEKEY_CONSTANT=yes
	OPT_DEFS += -DMOUSEKEY_CONSTANT_TAP=yes
endif

ifeq ($(strip $(combined)), true)
	# ┌───────────────────────────────────────────────────────────────┐
	# │ Enable Combined mode --> Constant on hold or acceleration     │
	# └───────────────────────────────────────────────────────────────┘
	OPT_DEFS += -DMOUSEKEY_COMBINED=yes
endif


# Unicode maps
UNICODEMAP_ENABLE = yes

# # Repeat
# REPEAT_KEY_ENABLE = yes

# # Key overrides
# KEY_OVERRIDE_ENABLE = yes

# Sources
SRC += features/encoder.c
SRC += features/utility.c
SRC += features/swapper.c
SRC += features/switcher.c


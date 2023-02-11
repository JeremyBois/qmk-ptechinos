# Easy definition of combos
VPATH +=  keyboards/gboards/

# Sources
SRC += features/encoder.c
SRC += features/utility.c
SRC += features/swapper.c
SRC += features/switcher.c
SRC += features/leader.c
SRC += features/repeat.c

# ┌─────────────────────────────────────────────────┐
# │ Cirque Trackpad                                 │
# └─────────────────────────────────────────────────┘
POINTING_DEVICE_ENABLE = yes
POINTING_DEVICE_DRIVER = cirque_pinnacle_i2c
OPT_DEFS += -DHAL_USE_I2C=TRUE

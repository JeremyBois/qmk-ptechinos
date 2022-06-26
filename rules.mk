# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = caterina

SPLIT_KEYBOARD = yes			# Split keyboard
LTO_ENABLE = yes				# Save space by link time optimization

# Options
RGBLIGHT_ENABLE = no			# RGB lighting (+3826)
ENCODER_ENABLE = yes		    # Rotary encoders (+1112)
EXTRAKEY_ENABLE = yes			# Audio control and System control (+450)
MOUSEKEY_ENABLE = yes			# Mouse keys (+1482). Not required for trackball usage
COMBO_ENABLE = yes              # Allow to write combo

# Unused
BOOTMAGIC_ENABLE = no           # Software way to enter boot mode
OLED_ENABLE = no                # Must be disabled if OLEDs are not installed (+3608-4774 with pet)
CONSOLE_ENABLE = no             # Console for debug (+4686)
UNICODE_ENABLE = no             # Allow to send unicode characters
SPACE_CADET_ENABLE = no 		# Save space by not using space cadet left/right shift (+350)
NKRO_ENABLE = no				# 6KRO by default. NKRO works if enabled (+328)
TAP_DANCE_ENABLE = no           # Allow tap dance combinations
LEADER_ENABLE = no              # Combinaisons with a leader key
GRAVE_ESC_ENABLE = no

# Saves a bunch of memory
# EXTRAFLAGS += -flto
VERBOSE = no
DEBUG_MATRIX_SCAN_RATE  = no
DEBUG_MATRIX = no
MAGIC_ENABLE = no

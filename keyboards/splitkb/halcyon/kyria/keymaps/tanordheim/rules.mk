ENCODER_MAP_ENABLE := yes
KEY_OVERRIDE_ENABLE := yes

# Either half can be the USB master for the left display.
WPM_ENABLE := yes
SRC += bongo_tft.c

ifdef HLC_TFT_DISPLAY
VPATH += $(QMK_USERSPACE)/examples/display/graphics
SRC += $(QMK_USERSPACE)/examples/display/graphics/thintel15.qff.c
endif

# This adds module functionality to your keyboard (files found in users/halcyon_modules)
USER_NAME := halcyon_modules

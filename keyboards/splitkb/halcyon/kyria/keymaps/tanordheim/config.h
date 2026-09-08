#pragma once
#define TAPPING_TERM 200
#define QUICK_TAP_TERM 0
#define PERMISSIVE_HOLD

// Both module builds must use the same split transaction layout.
#define SPLIT_ACTIVITY_ENABLE
#define SPLIT_WPM_ENABLE

// Bongo owns panel/backlight sleep, including keys held beyond the idle timeout.
#define HLC_BACKLIGHT_TIMEOUT 0

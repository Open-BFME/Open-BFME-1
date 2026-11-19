#pragma once

// Shared existing BFME1 declaration values. Consumers prove their original native
// enum primitive, size, members and runtime independently; no new recovery is claimed.
enum FilterModes
{
    FM_FIRST = 0,
    FM_NULL_MODE = 0,
    FM_VIEW_BW_BLACK_AND_WHITE = 1,
    FM_VIEW_BW_RED_AND_WHITE = 2,
    FM_VIEW_BW_GREEN_AND_WHITE = 3,
    FM_VIEW_BW_BLUE_AND_WHITE = 4,
    FM_VIEW_CROSSFADE_CIRCLE = 4,
    FM_VIEW_BW_IN_AND_OUT = 5,
    FM_VIEW_BW_FADE_AND_RETURN = 6,
    FM_VIEW_MB_IN_AND_OUT_ALPHA = 7,
    FM_VIEW_MB_IN_AND_OUT_SATURATE = 8,
    FM_VIEW_MB_END_PAN_ALPHA = 13,
    FM_VIEW_MB_PAN_ALPHA = 16,
};

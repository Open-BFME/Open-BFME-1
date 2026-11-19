#pragma once

// Shared existing BFME1 declaration values. Consumers prove their original native
// enum primitive, size, members and runtime independently; no new recovery is claimed.
enum FilterTypes
{
    FT_NULL_FILTER = 0,
    FT_VIEW_BW_FILTER = 1,
    FT_VIEW_MOTION_BLUR_FILTER = 2,
    FT_VIEW_CROSSFADE = 3,
    FT_VIEW_DEFAULT = 4,
};

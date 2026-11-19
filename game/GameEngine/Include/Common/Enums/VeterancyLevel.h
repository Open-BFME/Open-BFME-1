#pragma once

// Shared existing BFME1 declaration values. Consumers prove their original native
// enum primitive, size, members and runtime independently; no new recovery is claimed.
enum VeterancyLevel
{
    VETERANCY_LEVEL_INVALID = -1,
    LEVEL_REGULAR = 0,
    VETERANCY_INVALID = 0,
    LEVEL_VETERAN = 1,
    LEVEL_ELITE = 2,
    LEVEL_HEROIC = 3,
};

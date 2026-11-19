#pragma once

// Shared existing BFME1 declaration values. Consumers prove their original native
// enum primitive, size, members and runtime independently; no new recovery is claimed.
enum WeaponChoiceCriteria
{
    PREFER_MOST_DAMAGE = 0,
    PREFER_LONGEST_RANGE = 1,
    PREFER_SPECIAL = 2,
};

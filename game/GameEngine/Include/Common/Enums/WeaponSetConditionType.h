#pragma once

// Shared existing BFME1 declaration values. Consumers prove their original native
// enum primitive, size, members and runtime independently; no new recovery is claimed.
enum WeaponSetConditionType
{
    WSF_INVALID = -1,
    WSF_NONE = 0,
    WSF_FIRING = 1,
    WSF_BETWEEN = 2,
    WSF_RELOADING = 3,
    WSF_UNUSED = 4,
    WSF_PREATTACK = 5,
    WSF_COUNT = 6,
};

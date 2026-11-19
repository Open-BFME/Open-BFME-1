#pragma once

// Shared existing BFME1 declaration values. Consumers prove their original native
// enum primitive, size, members and runtime independently; no new recovery is claimed.
enum GuardMode
{
    BFME_GUARD_MODE_NORMAL = 0,
    GUARDMODE_NORMAL = 0,
    GUARDMODE_GUARD_WITHOUT_PURSUIT = 1,
    GUARDMODE_GUARD_FLYING_UNITS_ONLY = 2,
};

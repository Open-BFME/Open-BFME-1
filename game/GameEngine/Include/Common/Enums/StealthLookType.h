#pragma once

// Shared existing BFME1 declaration values. Consumers prove their original native
// enum primitive, size, members and runtime independently; no new recovery is claimed.
enum StealthLookType
{
    STEALTHLOOK_NONE = 0,
    STEALTHLOOK_VISIBLE_FRIENDLY = 1,
    STEALTHLOOK_DISGUISED_ENEMY = 2,
    STEALTHLOOK_VISIBLE_DETECTED = 3,
    STEALTHLOOK_VISIBLE_FRIENDLY_DETECTED = 4,
    STEALTHLOOK_INVISIBLE = 5,
};

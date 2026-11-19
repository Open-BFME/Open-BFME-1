#pragma once

// Shared existing BFME1 declaration values. Consumers prove their original native
// enum primitive, size, members and runtime independently; no new recovery is claimed.
enum AllowPlayerRelationship
{
    ALLOW_SAME_PLAYER = 1,
    ALLOW_ALLIES = 2,
    ALLOW_ENEMIES = 4,
    ALLOW_NEUTRAL = 8,
};

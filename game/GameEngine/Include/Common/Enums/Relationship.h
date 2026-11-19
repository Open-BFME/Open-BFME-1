#pragma once

// Shared existing BFME1 declaration values. Consumers prove their original native
// enum primitive, size, members and runtime independently; no new recovery is claimed.
enum Relationship
{
    ENEMIES = 0,
    NEUTRAL = 1,
    ALLIES = 2,
};

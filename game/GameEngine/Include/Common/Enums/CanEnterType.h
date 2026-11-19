#pragma once

// Shared existing BFME1 declaration values. Consumers prove their original native
// enum primitive, size, members and runtime independently; no new recovery is claimed.
enum CanEnterType
{
    CHECK_CAPACITY = 0,
    DONT_CHECK_CAPACITY = 1,
    COMBATDROP_INTO = 2,
};

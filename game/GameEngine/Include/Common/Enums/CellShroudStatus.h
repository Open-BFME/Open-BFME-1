#pragma once

// Shared existing BFME1 declaration values. Consumers prove their original native
// enum primitive, size, members and runtime independently; no new recovery is claimed.
enum CellShroudStatus
{
    BFME5_CELLSHROUD_ZERO = 0,
    CELLSHROUD_CLEAR = 0,
    SHROUD_CLEAR = 0,
    CELLSHROUD_FOGGED = 1,
    CELLSHROUD_SHROUDED = 2,
    CELLSHROUD_COUNT = 3,
};

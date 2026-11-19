#pragma once

// Shared existing BFME1 declaration values. Consumers prove their original native
// enum primitive, size, members and runtime independently; no new recovery is claimed.
enum RepairStates
{
    REPAIRSTATE_NONE = 0,
    REPAIRSTATE_UNPACKING = 1,
    REPAIRSTATE_PACKING = 2,
    REPAIRSTATE_READY = 3,
    REPAIRSTATE_EXTENDING = 4,
    REPAIRSTATE_RETRACTING = 5,
    REPAIRSTATE_WELDING = 6,
};

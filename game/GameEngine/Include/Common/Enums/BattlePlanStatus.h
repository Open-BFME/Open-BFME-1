#pragma once

// Shared existing BFME1 declaration values. Consumers prove their original native
// enum primitive, size, members and runtime independently; no new recovery is claimed.
enum BattlePlanStatus
{
    BfmeBattlePlanStatusNone = 0,
    NONE = 0,
    PLANSTATUS_NONE = 0,
    BOMBARDMENT = 1,
    HOLDTHELINE = 2,
    SEARCHANDDESTROY = 3,
};

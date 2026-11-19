#pragma once

// Shared existing BFME1 declaration values. Consumers prove their original native
// enum primitive, size, members and runtime independently; no new recovery is claimed.
enum BridgeTowerType
{
    BRIDGE_TOWER_0 = 0,
    BRIDGE_TOWER_FIRST = 0,
    BRIDGE_TOWER_FROM_LEFT = 0,
    BRIDGE_TOWER_1 = 1,
    BRIDGE_TOWER_FROM_RIGHT = 1,
    BRIDGE_TOWER_2 = 2,
    BRIDGE_TOWER_TO_LEFT = 2,
    BRIDGE_TOWER_3 = 3,
    BRIDGE_TOWER_TO_RIGHT = 3,
    BRIDGE_MAX_TOWERS = 4,
};

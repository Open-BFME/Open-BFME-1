#pragma once

// Shared existing BFME1 declaration values. Consumers prove their original native
// enum primitive, size, members and runtime independently; no new recovery is claimed.
enum RCItemType
{
    ITEM_BUDDY = 0,
    ITEM_REQUEST = 1,
    ITEM_NONBUDDY = 2,
    ITEM_NONE = 3,
};

#pragma once

// Shared existing BFME1 declaration values. Consumers prove their original native
// enum primitive, size, members and runtime independently; no new recovery is claimed.
enum MaxHealthChangeType
{
    SAME_CURRENTHEALTH = 0,
    PRESERVE_RATIO = 1,
    ADD_CURRENT_HEALTH_TOO = 2,
    FULLY_HEAL = 3,
};

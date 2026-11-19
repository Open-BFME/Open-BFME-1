#pragma once

// Shared existing BFME1 declaration values. Consumers prove their original native
// enum primitive, size, members and runtime independently; no new recovery is claimed.
enum IterOrderType
{
    ITER_FASTEST = 0,
    ITER_SORTED_NEAR_TO_FAR = 1,
    ITER_SORTED_FAR_TO_NEAR = 2,
    ITER_SORTED_CHEAP_TO_EXPENSIVE = 3,
    ITER_SORTED_EXPENSIVE_TO_CHEAP = 4,
};

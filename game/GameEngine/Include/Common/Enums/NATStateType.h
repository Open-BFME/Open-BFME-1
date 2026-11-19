#pragma once

// Shared existing BFME1 declaration values. Consumers prove their original native
// enum primitive, size, members and runtime independently; no new recovery is claimed.
enum NATStateType
{
    NATSTATE_IDLE = 0,
    NATSTATE_DOCONNECTIONPATHS = 1,
    NATSTATE_WAITFORSTATS = 2,
    NATSTATE_DONE = 3,
    NATSTATE_FAILED = 4,
};

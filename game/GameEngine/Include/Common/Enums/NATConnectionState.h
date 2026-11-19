#pragma once

// Shared existing BFME1 declaration values. Consumers prove their original native
// enum primitive, size, members and runtime independently; no new recovery is claimed.
enum NATConnectionState
{
    NATCONNECTIONSTATE_IDLE = 0,
    NATCONNECTIONSTATE_NOSTATE = 0,
    NATCONNECTIONSTATE_WAITINGTOBEGIN = 1,
    NATCONNECTIONSTATE_WAITINGFORMANGLERRESPONSE = 2,
    NATCONNECTIONSTATE_WAITINGFORMANGLEDPORT = 3,
    NATCONNECTIONSTATE_WAITINGFORRESPONSE = 4,
    NATCONNECTIONSTATE_DONE = 5,
    NATCONNECTIONSTATE_FAILED = 6,
};

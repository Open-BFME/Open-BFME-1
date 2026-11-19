#pragma once

// Shared existing BFME1 declaration values. Consumers prove their original native
// enum primitive, size, members and runtime independently; no new recovery is claimed.
enum BfmeMessageType
{
    BFME_MSG_CLEAR_GAME_DATA = 29,
    BFME_MSG_NEW_GAME = 30,
};

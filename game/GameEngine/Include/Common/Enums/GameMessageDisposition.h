#pragma once

// Shared existing BFME1 declaration values. Consumers prove their original native
// enum primitive, size, members and runtime independently; no new recovery is claimed.
enum GameMessageDisposition
{
    KEEP_MESSAGE = 0,
    DESTROY_MESSAGE = 1,
};

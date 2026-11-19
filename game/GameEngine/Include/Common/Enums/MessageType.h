#pragma once

// Shared existing BFME1 declaration values. Consumers prove their original native
// enum primitive, size, members and runtime independently; no new recovery is claimed.
enum MessageType
{
    NormalMessage = 0,
    ActionMessage = 1,
    NoticeMessage = 2,
};

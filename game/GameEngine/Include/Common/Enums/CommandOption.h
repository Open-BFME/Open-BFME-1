#pragma once

// Shared existing BFME1 declaration values. Consumers prove their original native
// enum primitive, size, members and runtime independently; no new recovery is claimed.
enum CommandOption
{
    NEED_TARGET_ENEMY_OBJECT = 1,
    NEED_TARGET_NEUTRAL_OBJECT = 2,
    NEED_TARGET_ALLY_OBJECT = 4,
    COMMAND_OPTION_NEED_OBJECT_TARGET = 7,
    NEED_TARGET_POS = 32,
};

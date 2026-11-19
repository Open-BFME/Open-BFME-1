#pragma once

// Shared existing BFME1 declaration values. Consumers prove their original native
// enum primitive, size, members and runtime independently; no new recovery is claimed.
enum GameDifficulty
{
    DIFFICULTY_EASY = 0,
    DIFFICULTY_NORMAL = 1,
    DIFFICULTY_HARD = 2,
};

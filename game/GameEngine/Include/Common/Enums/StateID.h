#pragma once

// Shared existing BFME1 declaration values. Consumers prove their original native
// enum primitive, size, members and runtime independently; no new recovery is claimed.
enum StateID
{
    BFME_AI_MOVE_TO = 1,
    BFME_AI_FOLLOW_PATH = 6,
    BFME_AI_FOLLOW_EXIT_PRODUCTION_PATH = 7,
    AI_ATTACK_POSITION = 9,
    BFME_AI_GUARD = 16,
    BFME_AI_HUNT = 17,
    BFME_AI_GET_REPAIRED = 24,
    BFME_AI_STATE_1B = 27,
    BFME_AI_STATE_1C = 28,
    BFME_AI_STATE_1D = 29,
    BFME_AI_STATE_1E = 30,
    BFME_AI_FACE_OBJECT = 31,
    BFME_AI_ATTACK_MOVE_TO = 33,
    BFME_AI_STATE_25 = 37,
    BFME_AI_EXIT_INSTANTLY = 38,
    AI_IDLE_MOVE = 40,
    BFME_AI_FOLLOW_PATH_STATE_0x36 = 54,
    BFME_AI_STATE_37 = 55,
    BFME_AI_STATE_38 = 56,
    BFME_AI_FOLLOW_PATH_STATE_0x3D = 61,
    BFME_AI_GUARD_RETALIATE = 62,
    BFME_AI_STATE_3F = 63,
    INVALID_STATE_ID = 999999,
};

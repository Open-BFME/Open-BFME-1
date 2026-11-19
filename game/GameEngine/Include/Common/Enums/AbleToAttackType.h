#pragma once

// Shared existing BFME1 declaration values. Consumers prove their original native
// enum primitive, size, members and runtime independently; no new recovery is claimed.
enum AbleToAttackType
{
    ATTACK_NEW_TARGET = 0,
    ATTACK_TYPE_0 = 0,
    ATTACK_TYPE_DUMMY = 0,
    ATTACK_TYPE_UNRECONSTRUCTED = 0,
    ATTACK_NEW_TARGET_FORCED = 1,
    _ATTACK_FORCED = 1,
    ATTACK_TUNNEL_NETWORK_GUARD = 4,
    CONTEST_ATTACK_TYPE = 8,
};

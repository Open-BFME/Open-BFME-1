#pragma once

// Shared existing BFME1 declaration values. Consumers prove their original native
// enum primitive, size, members and runtime independently; no new recovery is claimed.
enum BodyDamageType
{
    BODY_DAMAGE_PRISTINE = 0,
    BODY_DAMAGE_TYPE_UNKNOWN = 0,
    BODY_OK = 0,
    BODY_PRISTINE = 0,
    BODY_DAMAGED = 1,
    BODY_REALLYDAMAGED = 2,
    BODY_RUBBLE = 3,
    BODYDAMAGETYPE_COUNT = 4,
};

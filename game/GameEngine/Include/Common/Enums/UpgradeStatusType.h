#pragma once

// Shared existing BFME1 declaration values. Consumers prove their original native
// enum primitive, size, members and runtime independently; no new recovery is claimed.
enum UpgradeStatusType
{
    UPGRADE_STATUS_INVALID = 0,
    UPGRADE_STATUS_IN_PRODUCTION = 1,
    UPGRADE_STATUS_COMPLETE = 2,
};

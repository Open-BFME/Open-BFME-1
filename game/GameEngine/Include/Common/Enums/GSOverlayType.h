#pragma once

// Shared existing BFME1 declaration values. Consumers prove their original native
// enum primitive, size, members and runtime independently; no new recovery is claimed.
enum GSOverlayType
{
    GSOVERLAY_PLAYERINFO = 0,
    GSOverlayType_Thunk = 0,
    GSOVERLAY_MAPSELECT = 1,
    GSOVERLAY_BUDDY = 2,
    GSOVERLAY_PAGE = 3,
    GSOVERLAY_GAMEOPTIONS = 4,
    GSOVERLAY_GAMEPASSWORD = 5,
    GSOVERLAY_LADDERSELECT = 6,
    GSOVERLAY_BFME_SEVEN = 7,
    GSOVERLAY_OPTIONS = 8,
    GSOVERLAY_MAX = 9,
};


#pragma once

// Existing BFME1 enum contract from inputs/reference/shims/gamelod/Common/GameLOD.h.
// Original provider contexts remain intact; this narrow header is for proven consumers.
enum StaticGameLODLevel
{
	STATIC_GAME_LOD_UNKNOWN=-1,
	STATIC_GAME_LOD_LOW,
	STATIC_GAME_LOD_MEDIUM,
	STATIC_GAME_LOD_HIGH,
	STATIC_GAME_LOD_CUSTOM,	//make sure this remains last!
	STATIC_GAME_LOD_COUNT
};

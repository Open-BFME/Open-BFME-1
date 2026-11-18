
#pragma once

// Existing BFME1 enum contract from inputs/reference/shims/gamestatepristinemapname/Common/GameState.h.
// Original provider contexts remain intact; this narrow header is for proven consumers.
enum SaveFileType
{
	SAVE_FILE_TYPE_NORMAL,		///< a regular save game at any arbitrary point in the game
	SAVE_FILE_TYPE_MISSION,		///< a save game in between missions (a mission save)

	SAVE_FILE_TYPE_NUM_TYPES
};

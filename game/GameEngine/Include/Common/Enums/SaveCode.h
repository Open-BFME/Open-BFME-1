
#pragma once

// Existing BFME1 enum contract from inputs/reference/shims/gamestatepristinemapname/Common/GameState.h.
// Original provider contexts remain intact; this narrow header is for proven consumers.
enum SaveCode
{
	SC_INVALID = -1,
	SC_OK,
	SC_NO_FILE_AVAILABLE,
	SC_FILE_NOT_FOUND,
	SC_UNABLE_TO_OPEN_FILE,
	SC_INVALID_XFER,
	SC_UNKNOWN_BLOCK,
	SC_INVALID_DATA,
	SC_ERROR,
};

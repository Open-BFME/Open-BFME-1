
#pragma once

// Existing BFME1 enum contract from inputs/reference/shims/gamestatepristinemapname/Common/GameState.h.
// Original provider contexts remain intact; this narrow header is for proven consumers.
enum SnapshotType {
	SNAPSHOT_SAVELOAD,
	SNAPSHOT_DEEPCRC_LOGICONLY,
	SNAPSHOT_DEEPCRC,
	SNAPSHOT_MAX
};

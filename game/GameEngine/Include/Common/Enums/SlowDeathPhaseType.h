
#pragma once

// Existing BFME1 enum contract from inputs/reference/shims/slowdeathmoduledatadtor/GameLogic/Module/SlowDeathBehavior.h.
// Original provider contexts remain intact; this narrow header is for proven consumers.
enum SlowDeathPhaseType
{
	SDPHASE_INITIAL = 0,
	SDPHASE_MIDPOINT,
	SDPHASE_FINAL,

	SD_PHASE_COUNT	// keep last
};

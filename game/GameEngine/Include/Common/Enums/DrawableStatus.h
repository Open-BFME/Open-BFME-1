
#pragma once

// Existing BFME1 enum contract from inputs/reference/shims/swayclientupdate/GameClient/Drawable.h.
// Original provider contexts remain intact; this narrow header is for proven consumers.
enum DrawableStatus
{
	DRAWABLE_STATUS_NONE = 0,
	DRAWABLE_STATUS_DRAWS_IN_MIRROR = 1,
	DRAWABLE_STATUS_SHADOWS = 2,
	DRAWABLE_STATUS_TINT_COLOR_LOCKED = 4,
	DRAWABLE_STATUS_NO_STATE_PARTICLES = 8,
	DRAWABLE_STATUS_NO_SAVE = 0x10
};

/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#pragma once

// Existing BFME1 enum contract from inputs/reference/shims/sweep/GameClient/Shadow.h.
// Original provider contexts remain intact; this narrow header is for proven consumers.
enum ShadowType
{
	SHADOW_NONE											=	0x00000000,
	SHADOW_DECAL										=	0x00000001,		//shadow decal applied via modulate blend
	SHADOW_VOLUME										=	0x00000002,
	SHADOW_PROJECTION								=	0x00000004,
	SHADOW_DYNAMIC_PROJECTION				= 0x00000008,		//extra setting for shadows which need dynamic updates
	SHADOW_DIRECTIONAL_PROJECTION		= 0x00000010,		//extra setting for shadow decals that rotate with sun direction
	SHADOW_ALPHA_DECAL							= 0x00000020,		//not really for shadows but for other decal uses. Alpha blended.
	SHADOW_ADDITIVE_DECAL						= 0x00000040		//not really for shadows but for other decal uses. Additive blended.
};

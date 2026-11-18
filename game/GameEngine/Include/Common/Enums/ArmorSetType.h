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

// Existing BFME1 enum contract from inputs/reference/shims/sweep/GameLogic/ArmorSet.h.
// Original provider contexts remain intact; this narrow header is for proven consumers.
enum ArmorSetType
{
	// The access and use of this enum has the bit shifting built in, so this is a 0,1,2,3,4,5 enum
	ARMORSET_VETERAN		= 0,
	ARMORSET_ELITE			= 1,
	ARMORSET_HERO				= 2,
	ARMORSET_PLAYER_UPGRADE = 3,
	ARMORSET_WEAK_VERSUS_BASEDEFENSES = 4,
	ARMORSET_ALTERNATE_FORMATION = 5,
	ARMORSET_MOUNTED,
	ARMORSET_PLAYER_UPGRADE_2,
	ARMORSET_PLAYER_UPGRADE_3,
	ARMORSET_UNBESIEGEABLE,
	ARMORSET_AS_TOWER,

	ARMORSET_COUNT			///< keep last, please
};

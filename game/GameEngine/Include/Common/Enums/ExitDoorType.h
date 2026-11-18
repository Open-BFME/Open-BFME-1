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

// Existing BFME1 enum contract from game/GameEngine/Include/GameLogic/Module/UpdateModule.h.
// Original provider contexts remain intact; this narrow header is for proven consumers.
enum ExitDoorType
{
	DOOR_1 = 0,
	DOOR_2 = 1,
	DOOR_3 = 2,
	DOOR_4 = 3,

	DOOR_COUNT_MAX = 4,

	DOOR_NONE_AVAILABLE = -1,	// need a door, but none currently available
	DOOR_NONE_NEEDED		= -2	// don't need a door reservation
};

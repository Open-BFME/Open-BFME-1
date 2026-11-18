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

// Existing BFME1 enum contract from game/GameEngine/Include/Common/Module.h.
// Original provider contexts remain intact; this narrow header is for proven consumers.
enum ModuleType
{
	MODULETYPE_BEHAVIOR = 0,

	//
	// drawable module types - you should *NOT* remove drawable module types, we write
	// modules into save game files in buckets of module types ... if you do remove one
	// here you will have to update the xfer code for a drawable.
	//
	// ALSO note that new drawable module types should go at the end of the existing drawable modules
	//
	MODULETYPE_DRAW = 1,
	MODULETYPE_CLIENT_UPDATE = 2,
	// put new drawable module types here

	NUM_MODULE_TYPES,  // keep this last!

	FIRST_DRAWABLE_MODULE_TYPE = MODULETYPE_DRAW,
	LAST_DRAWABLE_MODULE_TYPE = MODULETYPE_CLIENT_UPDATE,
	NUM_DRAWABLE_MODULE_TYPES = (LAST_DRAWABLE_MODULE_TYPE - FIRST_DRAWABLE_MODULE_TYPE + 1)

};

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

// Existing BFME1 enum contract from inputs/reference/shims/particlecount/GameClient/ParticleSys.h.
// Original provider contexts remain intact; this narrow header is for proven consumers.
enum ParticlePriorityType
{
	INVALID_PRIORITY = 0,
	PARTICLE_PRIORITY_LOWEST = 1,
//	FLUFF = PARTICLE_PRIORITY_LOWEST,		///< total and absolute fluff
//	DEBRIS,		///< debris related particles
//	NATURE,	///< neato effects we just might see in the world
//	WEAPON,		///< Weapons firing and flying in the air
//	DAMAGE,		///< taking damage/dying explosions
//	SPECIAL,	///< super special top priority like a superweapon

	WEAPON_EXPLOSION = PARTICLE_PRIORITY_LOWEST,
	SCORCHMARK,
	DUST_TRAIL,
	BUILDUP,
	DEBRIS_TRAIL,
	UNIT_DAMAGE_FX,
	DEATH_EXPLOSION,
	SEMI_CONSTANT,
	CONSTANT,
	WEAPON_TRAIL,
	AREA_EFFECT,
	CRITICAL,				///< super special top priority like a superweapon
	ALWAYS_RENDER,	///< used for logically important display (not just fluff), so must never be culled, regardless of particle cap, lod, etc
	// !!! *Noting* goes here ... special is the top priority !!!
	PARTICLE_PRIORITY_HIGHEST = ALWAYS_RENDER,
	NUM_PARTICLE_PRIORITIES  ///< Keep this last
};

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

// Existing BFME1 enum contract from inputs/reference/shims/radar/Common/Radar.h.
// Original provider contexts remain intact; this narrow header is for proven consumers.
enum RadarEventType
{
	RADAR_EVENT_INVALID = 0,
	RADAR_EVENT_CONSTRUCTION,
	RADAR_EVENT_UPGRADE,
	RADAR_EVENT_UNDER_ATTACK,
	RADAR_EVENT_INFORMATION,
	RADAR_EVENT_BEACON_PULSE,
	RADAR_EVENT_INFILTRATION, //for defection, hijacking, hacking, carbombing, and other sneaks
	RADAR_EVENT_BATTLE_PLAN,
	RADAR_EVENT_STEALTH_DISCOVERED,		// we discovered a stealth unit
	RADAR_EVENT_STEALTH_NEUTRALIZED,	// our stealth unit has been revealed
	RADAR_EVENT_FAKE,					//Internally creates a radar event, but doesn't notify the player (unit lost
														//for example, so we can use the spacebar to jump to the event).

	RADAR_EVENT_NUM_EVENTS  // keep this last

};

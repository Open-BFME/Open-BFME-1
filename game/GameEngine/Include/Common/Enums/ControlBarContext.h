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

// Existing BFME1 enum contract from inputs/reference/shims/sweep/GameClient/ControlBar.h.
// Original provider contexts remain intact; this narrow header is for proven consumers.
enum ControlBarContext
{
	CB_CONTEXT_NONE,									///< default view for center bar and portrait window
//	CB_CONTEXT_PURCHASE_SCIENCE,
	CB_CONTEXT_COMMAND,								///< set of commands (attack-move,stop,deploy etc)
	CB_CONTEXT_STRUCTURE_INVENTORY,		///< garrisonable building inventory interface
	CB_CONTEXT_BEACON,								///< beacon interface
	CB_CONTEXT_UNDER_CONSTRUCTION,		///< building under construction
	CB_CONTEXT_MULTI_SELECT,					///< for when we have multiple objects selected
	CB_CONTEXT_OBSERVER_INFO,					///< for when we want to populate the player info
	CB_CONTEXT_OBSERVER_LIST,					///< for when we want to update the observer list
	CB_CONTEXT_OCL_TIMER,							///< Countdown for OCL spewers

	NUM_CB_CONTEXTS
};

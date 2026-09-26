// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/networkutil /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
// stlport
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

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////


#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "GameNetwork/NetworkUtil.h"

// Only the one function BFME's own bytes pin is carried here. The rest of the
// reference's NetworkUtil.cpp cannot be included as-is: its bodies test
// NETCOMMANDTYPE_RUNAHEADMETRICS, NETCOMMANDTYPE_RUNAHEAD and
// NETCOMMANDTYPE_FRAMERESENDREQUEST, none of which exist in BFME, and its
// MAX_FRAMES_AHEAD / FRAME_DATA_LENGTH constants are runtime globals in BFME
// (FRAME_DATA_LENGTH lives at VA 0x012BA088) rather than the compile-time
// formulas the reference uses.

Int DoesCommandRequireACommandID(NetCommandType type) {
	// BFME's own order, read straight off the comparison chain at 0x00682D20.
	if ((type == NETCOMMANDTYPE_GAMECOMMAND) ||
			(type == NETCOMMANDTYPE_REQUEST_GAMESPY_STATS_AUTHKEY) ||
			(type == NETCOMMANDTYPE_GAMESPY_STATS_AUTHKEY) ||
			(type == NETCOMMANDTYPE_FRAMEINFO) ||
			(type == NETCOMMANDTYPE_PLAYERLEAVE) ||
			(type == NETCOMMANDTYPE_INFORMPLAYERLEAVEFRAME) ||
			(type == NETCOMMANDTYPE_REQUESTFRAMEDATA) ||
			(type == NETCOMMANDTYPE_REQUESTPLAYERLEAVE) ||
			(type == NETCOMMANDTYPE_DESTROYPLAYER) ||
			(type == NETCOMMANDTYPE_CHAT) ||
			(type == NETCOMMANDTYPE_DISCONNECTVOTE) ||
			(type == NETCOMMANDTYPE_LOADCOMPLETE) ||
			(type == NETCOMMANDTYPE_TIMEOUTSTART) ||
			(type == NETCOMMANDTYPE_WRAPPER) ||
			(type == NETCOMMANDTYPE_FILE) ||
			(type == NETCOMMANDTYPE_FILEANNOUNCE) ||
			(type == NETCOMMANDTYPE_FILEPROGRESS) ||
			(type == NETCOMMANDTYPE_DISCONNECTPLAYER) ||
			(type == NETCOMMANDTYPE_DISCONNECTFRAME) ||
			(type == NETCOMMANDTYPE_DISCONNECTSCREENOFF))
	{
		return TRUE;
	}

	return FALSE;
}

/**
 * Returns the next network command ID.
 */
UnsignedShort GenerateNextCommandID() {
	// Retail loads the counter, then increments it in place (a1 <slot>;
	// 66 ff 05 <slot>) -- a post-increment, where the reference pre-increments
	// and so never hands out the seed. The seed itself is 100, read straight out
	// of .data at the address both instructions reference.
	static UnsignedShort commandID = 100;
	return commandID++;
}


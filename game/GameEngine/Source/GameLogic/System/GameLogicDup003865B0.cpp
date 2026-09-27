// cl: /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/stringbaseascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/multiplayer /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WWLib
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
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

// The "always add in an observer player" block of GameLogic::startNewGame.
// BFME1 outlines it into its own __cdecl body at retail 0x003865B0 (655 bytes)
// and calls it from startNewGame; the Zero Hour twin keeps the same statements
// inline. The helper's observable name is not recovered -- it is file-scope, has
// no vtable slot, and its only xref is the one call in startNewGame -- so the
// body is parked under its address as ?dup_003865b0@@YAXXZ.

#include "PreRTS.h"	// This must go first in EVERY cpp file in the GameEngine

#include "Common/MultiplayerSettings.h"
#include "Common/PlayerTemplate.h"
#include "Common/WellKnownKeys.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/SidesList.h"

// The addSide call goes through the ILT thunk at 0x0001CA12 in retail
// (body 0x0019A780), and that body is not the one the ledger currently
// places ?addSide@SidesList@@QAEXPBVDict@@@Z at, so the call site names the
// address-only thunk rather than the SidesList member.
void j_0001ca12(void);

struct BfmeSidesListObserverShim
{
	void rva0001CA12(const Dict *d)
	{
		union { void (*entry)(); void (BfmeSidesListObserverShim::*method)(const Dict *); } fn;
		fn.entry = &j_0001ca12;
		(this->*fn.method)(d);
	}
};

// The ledger already owns the 331-byte body retail reaches at 0x0019BA40
// (through the 0x00045DC7 thunk) under the address-derived name
// ?append@Rva0019BE80TeamRec@@QAEHPBVDict@@@Z, and that is what this call
// site targets. The Zero Hour spelling of the same statement is
// TheSidesList->m_teamrec.addTeam(&d); retail's +0x258 receiver adjustment
// by 0x630 is the &m_teamrec subobject of SidesList, so the call is made
// through the owner the ledger already uses. The competing
// ?addTeam@TeamsInfoRec@@QAEXPBVDict@@@Z pin sits on 0x0000D828, which the
// image shows to be an AsciiString releaseBuffer thunk (0x0000D828 jumps to
// 0x0005EE90 -> 0x00C87940), and one symbol can only carry one address, so
// this site takes the body the ledger actually matched rather than a pin.
struct Rva0019BE80TeamRec
{
	int append(const Dict *d);
};



void dup_003865b0( void )
{
	// Always add in an observer Player
	Dict d;
	d.setAsciiString(TheKey_playerName, "ReplayObserver");
	d.setBool(TheKey_playerIsHuman, TRUE);
	{
		UnicodeString observerDisplayName(L"Observer");
		d.setUnicodeString(TheKey_playerDisplayName, observerDisplayName);
	}
	const PlayerTemplate* pt;
	pt = ThePlayerTemplateStore->findPlayerTemplate( TheNameKeyGenerator->nameToKey("FactionObserver") );
	if (pt)
	{
		d.setAsciiString(TheKey_playerFaction, KEYNAME(pt->getNameKey()));
	}
	d.setAsciiString(TheKey_playerAllies, AsciiString::TheEmptyString);
	d.setAsciiString(TheKey_playerEnemies, AsciiString::TheEmptyString);
	d.setInt(TheKey_playerColor, TheMultiplayerSettings->getColor(0)->getColor());
	d.setInt(TheKey_playerNightColor, TheMultiplayerSettings->getColor(0)->getNightColor());
	d.setInt(TheKey_multiplayerStartIndex, 0);
	d.setBool(TheKey_multiplayerIsLocal, FALSE);

	((BfmeSidesListObserverShim *)TheSidesList)->rva0001CA12(&d);
	d.clear();
	d.setAsciiString(TheKey_teamName, "teamReplayObserver");
	d.setAsciiString(TheKey_teamOwner, "ReplayObserver");
	d.setBool(TheKey_teamIsSingleton, true);
	// Retail 0x003865B0 +0x258 adjusts the receiver by 0x630, which is
	// &TheSidesList->m_teamrec, and calls the 0x00045DC7 thunk there.
	((Rva0019BE80TeamRec *)((char *)TheSidesList + 0x630))->append(&d);
	TheSidesList->validateSides();
}

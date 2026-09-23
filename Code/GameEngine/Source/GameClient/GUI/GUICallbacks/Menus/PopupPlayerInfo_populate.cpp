// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/stringbaseunicode /Ireference/shims/stringbaseascii /Ireference/shims/psplayerstats /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Benchmark /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /ICode/Libraries/Source/WWVegas/WWLib
// stlport

// Identity: PopulatePlayerInfoWindows 0x004DBE80, WOLWelcomeMenu callers
// and PopupPlayerInfo.wnd literal; the recovered native stats view is 0x1C4.
// Rva004D9DF0 is the actual called battle-honors helper, intentionally named
// by address. Its entry consumes ECX=honors, ESI=list, [entry ESP+4]=stats;
// optimizer-visible natural C++ reproduces that private contract.
// All four visible helpers are individually byte-verified (1394/434/352/100).
// Witnesses and probe history: build/unclaimed_map/astra_B/.
// Existing PopupPlayerInfo.cpp claims retain their original include environment.
#define Matrix4x4 Matrix4  // BFME renamed it
#define __PLACEMENT_VEC_NEW_INLINE  // always.h/GameMemory.h define array placement-new themselves
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

///////////////////////////////////////////////////////////////////////////////////////
// FILE: PopupPlayerInfo_populate.cpp
// Author: Chris Huybregts, November 2001
// Description: BFME player statistics and battle-honors population
///////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "GameSpy/peer/peer.h"

#include "Common/GameEngine.h"
#include "Common/GameSpyMiscPreferences.h"
#include "Common/CustomMatchPreferences.h"
#include "Common/GlobalData.h"
#include "Common/UserPreferences.h"
#include "Common/PlayerTemplate.h"

#include "GameClient/AnimateWindowManager.h"
#include "GameClient/Display.h"
#include "GameClient/WindowLayout.h"
#include "GameClient/Gadget.h"
#include "GameClient/GameText.h"
#include "GameClient/Shell.h"
#include "GameClient/KeyDefs.h"
#include "GameClient/GameWindowManager.h"
#include "GameClient/GadgetListBox.h"
#include "GameClient/GadgetTextEntry.h"
#include "GameClient/GadgetStaticText.h"
#include "GameClient/GadgetCheckBox.h"
#include "GameClient/MessageBox.h"
#include "GameClient/GameWindowTransitions.h"

#include "GameNetwork/FirewallHelper.h"
#include "GameNetwork/GameSpyOverlay.h"

#include "GameNetwork/GameSpy/BuddyDefs.h"
#define BuddyRequest Rva0050D030ReferenceBuddyRequest
#define GameSpyBuddyMessageQueueInterface Rva0050D030ReferenceBuddyMessageQueueInterface
#include "GameNetwork/GameSpy/BuddyThread.h"
#undef GameSpyBuddyMessageQueueInterface
#undef BuddyRequest
#include "GameNetwork/GameSpy/PeerDefs.h"
#define PeerRequest Rva0050D030ReferencePeerRequest
#define GameSpyPeerMessageQueueInterface Rva0050D030ReferencePeerMessageQueueInterface
#include "GameNetwork/GameSpy/PeerThread.h"
#undef GameSpyPeerMessageQueueInterface
#undef PeerRequest
#include "GameNetwork/GameSpy/PersistentStorageDefs.h"

#include "GameNetwork/GameSpy/PersistentStorageThread.h"
#include "GameNetwork/GameSpy/BuddyThread.h"
#include "GameNetwork/GameSpy/ThreadUtils.h"
#include "GameNetwork/GameSpy/MainMenuUtils.h"
#include "GameNetwork/WOLBrowser/WebBrowser.h"

#include "Common/BattleHonors.h"
#include "GameNetwork/RankPointValue.h"
#include "GameClient/GadgetProgressBar.h"


extern RankPoints *TheRankPointValues;
extern GameWindow* findWindow(GameWindow*,AsciiString,AsciiString);

static const char *rankNames[] = {
	"Private",
	"Corporal",
	"Sergeant",
	"Lieutenant",
	"Captain",
	"Major",
	"Colonel",
	"General",
	"Brigadier",
	"Commander",
};

static const char *asciiStringText(const AsciiString &text)
{
	void *data = *(void * const *)&text;
	return data ? (const char *)data + 8 : "";
}

static bool asciiStringIsEmpty(const AsciiString &text)
{
	void *data = *(void * const *)&text;
	return data == 0 || *(const unsigned short *)((const char *)data + 4) == 0;
}

static const Image *lookupRankImage(AsciiString side, Int rank)
{
	if (asciiStringIsEmpty(side))
		return TheMappedImageCollection->findImageByName("NewPlayer");

	if (rank < 0 || rank >= 10)
		return 0;

	if (side.compare("America") == 0)
		side = "_USA";
	else if (side.compare("China") == 0)
		side = "_China";
	else if (side.compare("GLA") == 0)
		side = "_GLA";
	else if (side.compare("Random") == 0)
		side = "Elite";

	AsciiString fullImageName;
	fullImageName.format("Rank_%s%s", rankNames[rank], asciiStringText(side));
	if (strcmp(asciiStringText(fullImageName), "Rank_PrivateElite") == 0)
		fullImageName = "Rank";
	return TheMappedImageCollection->findImageByName(fullImageName);
}



class Rva004DBE80Display
{
public:
	virtual void slot00(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot0C(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot14(void) = 0;
	virtual void slot18(void) = 0;
	virtual void slot1C(void) = 0;
	virtual void slot20(void) = 0;
	virtual void slot24(void) = 0;
	virtual void slot28(void) = 0;
	virtual UnsignedInt getWidth(void) = 0;
	virtual UnsignedInt getHeight(void) = 0;
};

class Rva004DBE80GameSpyInfo
{
public:
	virtual void slot00(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot0C(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot14(void) = 0;
	virtual void slot18(void) = 0;
	virtual void slot1C(void) = 0;
	virtual void slot20(void) = 0;
	virtual void joinBestGroupRoom(Bool refresh) = 0;
	virtual void slot28(void) = 0;
	virtual void slot2C(void) = 0;
	virtual void slot30(void) = 0;
	virtual void slot34(void) = 0;
	virtual void slot38(void) = 0;
	virtual void slot3C(void) = 0;
	virtual void slot40(void) = 0;
	virtual void slot44(void) = 0;
	virtual void slot48(void) = 0;
	virtual void slot4C(void) = 0;
	virtual void slot50(void) = 0;
	virtual void slot54(void) = 0;
	virtual void slot58(void) = 0;
	virtual void slot5C(void) = 0;
	virtual void slot60(void) = 0;
	virtual void slot64(void) = 0;
	virtual AsciiString getLocalName(void) = 0;
	virtual void slot6C(void) = 0;
	virtual Int getLocalProfileID(void) = 0;
	virtual void slot74(void) = 0;
	virtual void slot78(void) = 0;
	virtual void slot7C(void) = 0;
	virtual void slot80(void) = 0;
	virtual void slot84(void) = 0;
	virtual void slot88(void) = 0;
	virtual void slot8C(void) = 0;
	virtual PSPlayerStats getCachedLocalPlayerStats(void) = 0;
	virtual void slot94(void) = 0;
	virtual void slot98(void) = 0;
	virtual void slot9C(void) = 0;
	virtual void slotA0(void) = 0;
	virtual void slotA4(void) = 0;
	virtual void slotA8(void) = 0;
	virtual void slotAC(void) = 0;
	virtual void slotB0(void) = 0;
	virtual void slotB4(void) = 0;
	virtual void slotB8(void) = 0;
	virtual void slotBC(void) = 0;
	virtual void slotC0(void) = 0;
	virtual void slotC4(void) = 0;
	virtual void slotC8(void) = 0;
	virtual void slotCC(void) = 0;
	virtual void slotD0(void) = 0;
	virtual void slotD4(void) = 0;
	virtual void slotD8(void) = 0;
	virtual void slotDC(void) = 0;
	virtual void slotE0(void) = 0;
	virtual void slotE4(void) = 0;
	virtual void slotE8(void) = 0;
	virtual void slotEC(void) = 0;
	virtual void slotF0(void) = 0;
	virtual void slotF4(void) = 0;
	virtual void slotF8(void) = 0;
	virtual void slotFC(void) = 0;
	virtual void slot100(void) = 0;
	virtual void slot104(void) = 0;
	virtual void slot108(void) = 0;
	virtual void slot10C(void) = 0;
	virtual void slot110(void) = 0;
	virtual void slot114(void) = 0;
	virtual void slot118(void) = 0;
	virtual void slot11C(void) = 0;
	virtual void slot120(void) = 0;
	virtual void slot124(void) = 0;
	virtual void slot128(void) = 0;
	virtual void slot12C(void) = 0;
	virtual void slot130(void) = 0;
	virtual void slot134(void) = 0;
	virtual void slot138(void) = 0;
	virtual void slot13C(void) = 0;
	virtual void slot140(void) = 0;
	virtual void slot144(void) = 0;
	virtual void slot148(void) = 0;
	virtual void slot14C(void) = 0;
	virtual void slot150(void) = 0;
	virtual void slot154(void) = 0;
	virtual void slot158(void) = 0;
	virtual void slot15C(void) = 0;
	virtual Bool didPlayerPreorder(Int) = 0;
	virtual void slot164(void) = 0;
	virtual void slot168(void) = 0;
	virtual void slot16C(void) = 0;
	virtual Int getAdditionalDisconnects(void) = 0;
	virtual void clearAdditionalDisconnects(void) = 0;
};

extern Int __fastcall readAdditionalDisconnectsFromUserFile(Int);

extern Int lookAtPlayerID;
extern std::string lookAtPlayerName;
extern GameWindow *parentWOLWelcome;

Int GetAdditionalDisconnectsFromUserFile(Int playerID)
{
	Int retval = readAdditionalDisconnectsFromUserFile(playerID);

	if (playerID == 0) {
		return 0;
	}
	if (((Rva004DBE80GameSpyInfo*)TheGameSpyInfo)->getAdditionalDisconnects() > 0 && !retval)
	{
		DEBUG_LOG(("Clearing additional disconnects\n"));
		((Rva004DBE80GameSpyInfo*)TheGameSpyInfo)->clearAdditionalDisconnects();
	}

	if (((Rva004DBE80GameSpyInfo*)TheGameSpyInfo)->getAdditionalDisconnects() != -1)
	{
		return ((Rva004DBE80GameSpyInfo*)TheGameSpyInfo)->getAdditionalDisconnects();
	}

	return retval;
}

Int CalculateRank(const PSPlayerStats&);
static Int rowsToSkip=0;

void ResetBattleHonorInsertion(void)
{
	rowsToSkip = 0;
}

void InsertBattleHonor(GameWindow *list, const Image *image, Bool enabled, Int itemData, Int& row, Int& column, UnicodeString text = UnicodeString::TheEmptyString, Int extra = 0)
{
	Int width = 50 * ( ((Rva004DBE80Display*)TheDisplay)->getWidth() / 800.0f );
	Int height = 51 * ( ((Rva004DBE80Display*)TheDisplay)->getHeight() / 600.0f );

	static Int enabledColor = 0xFFFFFFFF;
	static Int disabledColor = GameMakeColor( 80, 80, 80, 255 );
	Int color;
	if ( enabled )
		color = enabledColor;
	else
	{
		Int updated = itemData;
		color = disabledColor;
		updated |= BATTLE_HONOR_NOT_GAINED;
		itemData = updated;
	}

	GadgetListBoxAddEntryImage( list, image, row, column, height, width, true, color );
	GadgetListBoxSetItemData( list, (void *)itemData, row, column );

	if ( ++column >= GadgetListBoxGetNumColumns( list ) )
	{
		column = 0;
		row = row + 1 + rowsToSkip;
		Int dec = rowsToSkip - 1;
		Int zero = 0;
		rowsToSkip = *( dec > 0 ? &dec : &zero );
	}
}

struct Rva004DBE80Stats
{
	Int id;                             // +0x000
	PerGeneralMap wins;                 // +0x004
	PerGeneralMap losses;               // +0x010
	PerGeneralMap currentWinStreaks;    // +0x01c
	PerGeneralMap currentLossStreaks;   // +0x028
	PerGeneralMap worstLossStreaks;     // +0x034
	PerGeneralMap bestWinStreaks;       // +0x040
	PerGeneralMap games;                // +0x04c
	PerGeneralMap duration;             // +0x058
	PerGeneralMap unitsKilled;          // +0x064
	PerGeneralMap unitsLost;            // +0x070
	PerGeneralMap unitsBuilt;           // +0x07c
	PerGeneralMap buildingsKilled;      // +0x088
	PerGeneralMap buildingsLost;        // +0x094
	PerGeneralMap buildingsBuilt;       // +0x0a0
	PerGeneralMap earnings;             // +0x0ac
	PerGeneralMap discons;              // +0x0b8
	PerGeneralMap desyncs;              // +0x0c4
	PerGeneralMap surrenders;           // +0x0d0
	PerGeneralMap gamesOf2p;            // +0x0dc
	PerGeneralMap gamesOf3p;            // +0x0e8
	PerGeneralMap gamesOf4p;            // +0x0f4
	PerGeneralMap gamesOf5p;            // +0x100
	PerGeneralMap gamesOf6p;            // +0x10c
	PerGeneralMap gamesOf7p;            // +0x118
	PerGeneralMap gamesOf8p;            // +0x124
	PerGeneralMap customGames;          // +0x130
	PerGeneralMap QMGames;              // +0x13c
	Int locale;                         // +0x148
	std::string dateCreated;            // +0x14c
	Int gamesAsRandom;                  // +0x158
	std::string options;                // +0x15c
	std::string systemSpec;             // +0x168
	Real lastFPS;                       // +0x174
	Int lastSide;                       // +0x178
	Int gamesInRowWithLastSide;         // +0x17c
	Int challengeMedals;                // +0x180
	Int battleHonors;                   // +0x184
	Int winsInARow;                     // +0x188
	Int maxWinsInARow;                  // +0x18c
	Int lossesInARow;                   // +0x190
	Int maxLossesInARow;                // +0x194
	Int gamesOn1_1_Ladder;              // +0x198
	Int gamesOn2_2_Ladder;              // +0x19c
	Int disconsInARow;                  // +0x1a0
	Int maxDisconsInARow;               // +0x1a4
	Int desyncsInARow;                  // +0x1a8
	Int maxDesyncsInARow;               // +0x1ac
	Int best1v1LadderRank;              // +0x1b0
	Int best2v2LadderRank;              // +0x1b4
	std::string lastLadderPlayed;       // +0x1b8
};

void BattleHonorTooltip(GameWindow*,WinInstanceData*,UnsignedInt);

// The existing InsertBattleHonor ledger signature retains ZH's unused extra
// parameter. Retail 004DA164 supplies seven stack arguments (ADD ESP,1Ch),
// and the byte-exact 352-byte callee never reads the dropped eighth argument.
// Use that witnessed call type while retaining the existing symbol binding
// and the actual callee definition so alias analysis sees its reference writes.
typedef void (__cdecl *Rva004D9800Call)(GameWindow*,const Image*,Bool,Int,Int&,Int&,UnicodeString);
#define InsertBattleHonor reinterpret_cast<Rva004D9800Call>(InsertBattleHonor)

static void Rva004D9DF0(const PSPlayerStats& stats, Int battleHonors, Int gamesInRow, Int lastGen, Int challenge, GameWindow *list)
{
	if( !list )
		return;

	list->winSetTooltipFunc(BattleHonorTooltip);
	GadgetListBoxReset( list );
    const Rva004DBE80Stats& statsView=*(const Rva004DBE80Stats*)&stats;
	Int column = 0;
	Int row = 0;

	Bool isFairPlayer = FALSE;
	Int numGames = 0;
	Int numDiscons = 0;
	PerGeneralMap::const_iterator it;
	for(it = statsView.games.begin(); it != statsView.games.end(); ++it)
	{
		numGames += it->second;
	}
	for(it = statsView.discons.begin(); it != statsView.discons.end(); ++it)
	{
		numDiscons += it->second;
	}
	for(it = statsView.desyncs.begin(); it != statsView.desyncs.end(); ++it)
	{
		numDiscons += it->second;
	}
	if (numGames >= 10 && numDiscons * 10 < numGames)
	{
		isFairPlayer = TRUE;
	}

	ResetBattleHonorInsertion();
	GadgetListBoxAddEntryImage(list, NULL, 0, 0, 10, 10, TRUE, GameMakeColor(255,255,255,255));
	row = 1;

	InsertBattleHonor(list, TheMappedImageCollection->findImageByName("FairPlay"), isFairPlayer,
		BATTLE_HONOR_FAIR_PLAY, row, column, UnicodeString::TheEmptyString);

	InsertBattleHonor(list, TheMappedImageCollection->findImageByName("HonorAirWing"), BitTest(battleHonors, BATTLE_HONOR_AIR_WING),
		BATTLE_HONOR_AIR_WING, row, column, UnicodeString::TheEmptyString);
	InsertBattleHonor(list, TheMappedImageCollection->findImageByName("HonorBattleTank"), BitTest(battleHonors, BATTLE_HONOR_BATTLE_TANK),
		BATTLE_HONOR_BATTLE_TANK, row, column, UnicodeString::TheEmptyString);
	InsertBattleHonor(list, TheMappedImageCollection->findImageByName("Apocalypse"), BitTest(battleHonors, BATTLE_HONOR_APOCALYPSE),
		BATTLE_HONOR_APOCALYPSE, row, column, UnicodeString::TheEmptyString);

	if (BitTest(battleHonors, BATTLE_HONOR_BLITZ5))
	{
		InsertBattleHonor(list, TheMappedImageCollection->findImageByName("HonorBlitz5"), TRUE,
			BATTLE_HONOR_BLITZ5, row, column, UnicodeString::TheEmptyString);
	}
	else if (BitTest(battleHonors, BATTLE_HONOR_BLITZ10))
	{
		InsertBattleHonor(list, TheMappedImageCollection->findImageByName("HonorBlitz10"), TRUE,
			BATTLE_HONOR_BLITZ10, row, column, UnicodeString::TheEmptyString);
	}
	else
	{
		InsertBattleHonor(list, TheMappedImageCollection->findImageByName("HonorBlitz10"), FALSE,
			BATTLE_HONOR_BLITZ10, row, column, UnicodeString::TheEmptyString);
	}

	// create a spacer for row 2 and start the images on row 3
	GadgetListBoxAddEntryImage(list, NULL, 2, 0, 10, 10, TRUE, GameMakeColor(255,255,255,255));
	row = 3;

	// TEST FOR STREAK HONOR
	UnicodeString uStr;
	uStr.format(UnicodeString(L"%10d"), statsView.maxWinsInARow);
	if (battleHonors & 0x10)
	{
		InsertBattleHonor(list, TheMappedImageCollection->findImageByName("HonorStreak_G"), TRUE,
			0x10, row, column, uStr);
	}
	else if (battleHonors & 8)
	{
		InsertBattleHonor(list, TheMappedImageCollection->findImageByName("HonorStreak_S"), TRUE,
			8, row, column, uStr);
	}
	else if (battleHonors & 2)
	{
		InsertBattleHonor(list, TheMappedImageCollection->findImageByName("HonorStreak_B"), TRUE,
			2, row, column, uStr);
	}
	else
	{
		InsertBattleHonor(list, TheMappedImageCollection->findImageByName("HonorStreak_B"), FALSE,
			2, row, column, UnicodeString::TheEmptyString);
	}

	if (((Rva004DBE80GameSpyInfo*)TheGameSpyInfo)->didPlayerPreorder(statsView.id))
	{
		InsertBattleHonor(list, TheMappedImageCollection->findImageByName("OfficersClub"), TRUE,
			BATTLE_HONOR_OFFICERSCLUB, row, column, UnicodeString::TheEmptyString);
	}
}

#undef InsertBattleHonor

template<class T> inline const T& rvaMax(const T& a,const T& b) { return a>b?a:b; }
template<> inline const wchar_t *StringBase<wchar_t>::str() const {return m_data ? &m_data->data[0] : L"";}

void PopulatePlayerInfoWindows( AsciiString parentWindowName )
{
    Int lookupID = ((Rva004DBE80GameSpyInfo *)TheGameSpyInfo)->getLocalProfileID();
	if(parentWindowName.compare("PopupPlayerInfo.wnd") == 0)
	{
		lookupID = lookAtPlayerID;
		if (lookAtPlayerID <= 0 || !parentWOLWelcome)
			return;
	}

	PSPlayerStats stats = TheGameSpyPSMessageQueue->findPlayerStatsByID(lookupID);
    Rva004DBE80Stats &statsView = *(Rva004DBE80Stats*)&stats;

	Bool weHaveStats = (statsView.id != 0);

	// if we don't have the stats from the server, see if we have cached stats
    if( !weHaveStats && lookupID == ((Rva004DBE80GameSpyInfo *)TheGameSpyInfo)->getLocalProfileID() )
	{
		stats = ((Rva004DBE80GameSpyInfo *)TheGameSpyInfo)->getCachedLocalPlayerStats();

		weHaveStats = TRUE;
	}

	Int currentRank = 0;
	Int rankPoints = CalculateRank(stats);
	Int i = 0;
	while( rankPoints >= TheRankPointValues->m_ranks[i + 1])
		++i;
	currentRank = i;

	PerGeneralMap::iterator it;
	Int numWins = 0;
	Int numLosses = 0;
	Int numDiscons = 0;
	Int numGames = 0;
	for(it =statsView.wins.begin(); it != statsView.wins.end(); ++it)
	{
		numWins += it->second;
	}
	for(it =statsView.losses.begin(); it != statsView.losses.end(); ++it)
	{
		numLosses += it->second;
	}
	for(it =statsView.discons.begin(); it != statsView.discons.end(); ++it)
	{
		numDiscons += it->second;
	}
	for(it =statsView.desyncs.begin(); it != statsView.desyncs.end(); ++it)
	{
		numDiscons += it->second;
	}

	numDiscons += GetAdditionalDisconnectsFromUserFile(lookupID);

	numGames = numWins + numLosses + numDiscons;

	GameWindow *win = NULL;
	UnicodeString uStr;
	win = findWindow(NULL, parentWindowName, "StaticTextPlayerStatisticsLabel");
	if(win)
	{
		AsciiString localeID = "WOL:Locale00";
		if (statsView.locale >= LOC_MIN && statsView.locale <= LOC_MAX)
			localeID.format("WOL:Locale%2.2d", statsView.locale);
		uStr.format(TheGameText->fetch("GUI:PlayerStatistics"), lookAtPlayerName.c_str(), TheGameText->fetch(localeID).str());
		GadgetStaticTextSetText(win, uStr);
	}
	win = findWindow(NULL, parentWindowName, "StaticTextGamesPlayedValue");
	if(win)
	{
		uStr.format(UnicodeString(L"%d"), numGames);
		GadgetStaticTextSetText(win, uStr);
	}
	win = findWindow(NULL, parentWindowName, "StaticTextWinsValue");
	if(win)
	{
		uStr.format(UnicodeString(L"%d"), numWins);
		GadgetStaticTextSetText(win, uStr);
	}
	win = findWindow(NULL, parentWindowName, "StaticTextLossesValue");
	if(win)
	{
		uStr.format(UnicodeString(L"%d"), numLosses);
		GadgetStaticTextSetText(win, uStr);
	}
	win = findWindow(NULL, parentWindowName, "StaticTextDisconnectsValue");
	if(win)
	{
		uStr.format(UnicodeString(L"%d"), numDiscons);
		GadgetStaticTextSetText(win, uStr);
	}

	win = findWindow(NULL, parentWindowName, "StaticTextBestStreakValue");
	if (win)
	{
		uStr.format(UnicodeString(L"%d"), statsView.maxWinsInARow);
		GadgetStaticTextSetText(win, uStr);
	}

	win = findWindow(NULL, parentWindowName, "StaticTextStreak");
	if (win)
	{
		if (statsView.lossesInARow > 0)
		{
			GadgetStaticTextSetText(win, TheGameText->fetch("GUI:CurrentLossStreak"));
		}
		else
		{
			GadgetStaticTextSetText(win, TheGameText->fetch("GUI:CurrentWinStreak"));
		}
	}
	win = findWindow(NULL, parentWindowName, "StaticTextStreakValue");
	if(win)
	{
		Int streak = rvaMax(statsView.lossesInARow, statsView.winsInARow);
		uStr.format(UnicodeString(L"%d"), streak);
		GadgetStaticTextSetText(win, uStr);
	}

    AsciiString favoriteSide = "Random";
    win = findWindow(NULL, parentWindowName, "StaticTextFavoriteSideValue");
    {
        Int mostGames = 0;
        Int favorite = 0;
        for (it=statsView.games.begin(); it!=statsView.games.end(); ++it)
        {
            if (it->second >= mostGames) {mostGames=it->second; favorite=it->first;}
        }
        if (mostGames == 0)
            GadgetStaticTextSetText(win, TheGameText->fetch("GUI:None"));
        else if (statsView.gamesAsRandom >= mostGames)
            GadgetStaticTextSetText(win, TheGameText->fetch("GUI:Random"));
        else
        {
            const PlayerTemplate *pt=ThePlayerTemplateStore->getNthPlayerTemplate(favorite);
            if (pt)
            {
                AsciiString side;
                const AsciiString &nativeSide=*(const AsciiString*)((const char*)pt+8);
                side.format("SIDE:%s",nativeSide.str());
                GadgetStaticTextSetText(win,TheGameText->fetch(side));
                favoriteSide=nativeSide;
            }
        }
    }

	win = findWindow(NULL, parentWindowName, "StaticTextTotalKillsValue");
	if(win)
	{
		Int numGames = 0;
		for(it =statsView.unitsKilled.begin(); it != statsView.unitsKilled.end(); ++it)
		{
			numGames += it->second;
		}
		uStr.format(UnicodeString(L"%d"), numGames);
		GadgetStaticTextSetText(win, uStr);
	}
	win = findWindow(NULL, parentWindowName, "StaticTextTotalDeathsValue");
	if(win)
	{
		Int numGames = 0;
		for(it =statsView.unitsLost.begin(); it != statsView.unitsLost.end(); ++it)
		{
			numGames += it->second;
		}
		uStr.format(UnicodeString(L"%d"), numGames);
		GadgetStaticTextSetText(win, uStr);
	}
	win = findWindow(NULL, parentWindowName, "StaticTextTotalBuiltValue");
	if(win)
	{
		Int numGames = 0;
		for(it =statsView.unitsBuilt.begin(); it != statsView.unitsBuilt.end(); ++it)
		{
			numGames += it->second;
		}
		uStr.format(UnicodeString(L"%d"), numGames);
		GadgetStaticTextSetText(win, uStr);
	}
	win = findWindow(NULL, parentWindowName, "StaticTextBuildingsKilledValue");
	if(win)
	{
		Int numGames = 0;
		for(it =statsView.buildingsKilled.begin(); it != statsView.buildingsKilled.end(); ++it)
		{
			numGames += it->second;
		}
		uStr.format(UnicodeString(L"%d"), numGames);
		GadgetStaticTextSetText(win, uStr);
	}
	win = findWindow(NULL, parentWindowName, "StaticTextBuildingsLostValue");
	if(win)
	{
		Int numGames = 0;
		for(it =statsView.buildingsLost.begin(); it != statsView.buildingsLost.end(); ++it)
		{
			numGames += it->second;
		}
		uStr.format(UnicodeString(L"%d"), numGames);
		GadgetStaticTextSetText(win, uStr);
	}
	win = findWindow(NULL, parentWindowName, "StaticTextBuildingsBuiltValue");
	if(win)
	{
		Int numGames = 0;
		for(it =statsView.buildingsBuilt.begin(); it != statsView.buildingsBuilt.end(); ++it)
		{
			numGames += it->second;
		}
		uStr.format(UnicodeString(L"%d"), numGames);
		GadgetStaticTextSetText(win, uStr);
	}

	win = findWindow(NULL, parentWindowName, "StaticTextWinPercentValue");
	if(win)
	{
		uStr.format(TheGameText->fetch("GUI:WinPercent"), (Int)(numWins/(Real)numGames*100.0f));
		GadgetStaticTextSetText(win, uStr);
	}

	win = findWindow(NULL, parentWindowName, "ProgressBarRank");
	if(win && TheRankPointValues)
	{
		if( currentRank == MAX_RANKS - 1)
		{
			// we've reached the max rank
			win->winHide(TRUE);
		}
		else
		{
			GadgetProgressBarSetProgress(win, 100 * INT_TO_REAL(rankPoints - TheRankPointValues->m_ranks[currentRank])/( TheRankPointValues->m_ranks[currentRank + 1] - TheRankPointValues->m_ranks[currentRank]));
		}
	}

    win = findWindow(NULL,parentWindowName,"WinRank");
    if (win && TheRankPointValues)
    {
        if (rankPoints == 0) win->winSetEnabledImage(0,lookupRankImage(AsciiString::TheEmptyString,0));
        else win->winSetEnabledImage(0,lookupRankImage(favoriteSide,currentRank));
    }
    win = findWindow(NULL,parentWindowName,"StaticTextRank");
    if (win)
    {
        AsciiString rank;
        rank.format("GUI:GSRank%d",currentRank);
        GadgetStaticTextSetText(win,TheGameText->fetch(rank));
    }

	win = findWindow(NULL, parentWindowName, "StaticTextInProgress");
	if (win)
	{
		if (weHaveStats)
		{
			win->winHide(TRUE);
		}
		else
		{
			win->winHide(FALSE);
			GadgetStaticTextSetText(win, TheGameText->fetch("GUI:FetchingPlayerInfo"));
		}
	}

	win = findWindow(NULL, parentWindowName, "ListboxInfo");
	if(win)
	{
		Rva004D9DF0(stats, statsView.battleHonors,statsView.gamesInRowWithLastSide,statsView.lastSide,statsView.challengeMedals, win);
	}
}

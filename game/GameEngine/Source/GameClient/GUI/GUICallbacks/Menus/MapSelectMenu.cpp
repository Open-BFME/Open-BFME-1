// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/stringbaseunicode /Iinputs/reference/shims/stringbaseascii /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Igame/Libraries/Source/WWVegas/WWLib
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
#define __PLACEMENT_VEC_NEW_INLINE  // always.h/GameMemory.h define array placement-new themselves
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

// FILE: MapSelectMenu.cpp ////////////////////////////////////////////////////////////////////////
// Author: Colin Day, October 2001
// Description: MapSelect menu window callbacks
///////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/GameEngine.h"
#include "Common/MessageStream.h"
#include "Common/RandomValue.h"
#include "Common/UserPreferences.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/ScriptEngine.h"
#include "GameClient/AnimateWindowManager.h"
#include "GameClient/CampaignManager.h"
#include "GameClient/WindowLayout.h"
#include "GameClient/Gadget.h"
#include "GameClient/Shell.h"
#include "GameClient/GameWindowManager.h"
#include "GameClient/GadgetListBox.h"
#include "GameClient/GadgetComboBox.h"
#include "GameClient/GadgetRadioButton.h"
#include "GameClient/MapUtil.h"
#include "GameClient/Mouse.h"

// PUBLIC FUNCTIONS ///////////////////////////////////////////////////////////////////////////////
static NameKeyType radioButtonSystemMapsID = NAMEKEY_INVALID;
static NameKeyType radioButtonUserMapsID = NAMEKEY_INVALID;
static GameWindow *mapList = NULL;

static Bool showSoloMaps = true;
static Bool isShuttingDown = false;
static Bool startGame = false;
static Bool buttonPushed = false;
static GameDifficulty s_AIDiff = DIFFICULTY_NORMAL;


class BFMERetailScriptEngineView
{
public:
	unsigned char m_unreconstructed_00000[0x17620];
	GameDifficulty m_globalDifficulty;

	GameDifficulty getGlobalDifficulty() const { return m_globalDifficulty; }
};

// Zero Hour's setupGameStart(AsciiString) is not reconstructed here: retail's
// copy is the out-of-line body at 0x004D1080 (ledger name bfmeCommitYH) that
// MapSelectMenuSystem's OK branch calls; see the declaration above that body.

static void doGameStart( void )
{
	startGame = false;

	if (TheGameLogic->isInGame())
		TheGameLogic->clearGameData();
	//TheScriptEngine->setGlobalDifficulty(s_AIDiff); // CANNOT DO THIS! REPLAYS WILL BREAK!!!
	// send a message to the logic for a new game
	GameMessage *msg = TheMessageStream->appendMessage( GameMessage::MSG_NEW_GAME );
	msg->appendIntegerArgument(GAME_SINGLE_PLAYER);
	msg->appendIntegerArgument(s_AIDiff);
	msg->appendIntegerArgument(0);

	/// @todo: when Campaign & skirmish are separated, make campaign have fixed seed and skirmish random.
	InitRandom(0);
	/*
	if (TheGlobalData->m_fixedSeed >= 0)
		InitGameLogicRandom(TheGlobalData->m_fixedSeed);
	else
		InitGameLogicRandom(GameClientRandomValue(0, INT_MAX - 1));
	*/

	isShuttingDown = true;
}


//-------------------------------------------------------------------------------------------------
// Open-BFME5: BFME made WindowLayout::hide VIRTUAL, at vtable slot 0x10. The
// Zero Hour WindowLayout.h in this tree declares it an ordinary member, so we
// emit a direct call to the right function instead of a dispatch. Correcting
// the declaration would touch every TU that includes WindowLayout.h and force
// the full repo gate, so it is spelled TU-locally: a shim whose fifth virtual
// lands on that slot, and a cast at each call site. Slots 0-3 stay anonymous
// because nothing here needs them. Same shim as NetworkDirectConnect.cpp.
//-------------------------------------------------------------------------------------------------
class BfmeVirtualHideLayout
{
public:
	virtual void slot0() = 0;
	virtual void slot4() = 0;
	virtual void slot8() = 0;
	virtual void slotC() = 0;
	virtual void hide( Bool immediate ) = 0;
};

//-------------------------------------------------------------------------------------------------
/** This is called when a shutdown is complete for this menu */
//-------------------------------------------------------------------------------------------------
// Retail 0x004D1000 (22 B): this menu static over isShuttingDown
// (VA 0x012F3E6C); layout arrives in EAX beside MapSelectMenuUpdate and
// MapSelectMenuShutdown (mov ecx,[TheShell] / push 0 / push eax / clear
// flag / call Shell::shutdownComplete via ILT 0x2F1D). Update/Shutdown
// inline the same sequence; no direct callers, refs=2 abs-ref.
// ?shutdownCompleteMapSelectMenu@@YAXPAVWindowLayout@@@Z
static void shutdownCompleteMapSelectMenu( WindowLayout *layout )
{

	isShuttingDown = false;

	// Open-BFME5: BFME dropped Zero Hour's `layout->hide( TRUE )` here. Retail
	// inlines this helper wholesale into MapSelectMenuUpdate at 0x004D1BD0 and
	// the inlined copy is `mov eax,[esp+4]` / `mov ecx,[TheShell]` / `push 0` /
	// `push eax` / clear the flag / call -- no vtable load, no hide, and no room
	// for one in the 79-byte extent. NetworkDirectConnect.cpp still has the hide
	// and reaches it through vtable slot 0x10, so this is a per-menu change and
	// not a change to WindowLayout.

	// our shutdown is complete
	TheShell->shutdownComplete( layout );

}  // end if

// Retail 0x004D1120 (ILT 0x00019727), called from MapSelectMenuInit. Zero Hour
// names this helper SetDifficultyRadioButton in both MapSelectMenu.cpp and
// DifficultySelect.cpp (static there); the ledger gives that mangled name to
// DifficultySelect's copy at 0x004C6E70, so this copy carries the menu suffix,
// as shutdownCompleteMapSelectMenu does.
// ?SetDifficultyRadioButtonMapSelectMenu@@YAXXZ
void SetDifficultyRadioButtonMapSelectMenu( void )
{
	AsciiString parentName( "MapSelectMenu.wnd:MapSelectMenuParent" );
	NameKeyType parentID = TheNameKeyGenerator->nameToKey( parentName.str() );
	GameWindow *parent = TheWindowManager->winGetWindowFromId( NULL, parentID );

	if (!TheScriptEngine)
	{
		s_AIDiff = DIFFICULTY_EASY;
	}
	else
	{
		switch (((BFMERetailScriptEngineView *)TheScriptEngine)->getGlobalDifficulty())
		{
			case DIFFICULTY_EASY:
			{
				NameKeyType radioButtonEasyAIID = TheNameKeyGenerator->nameToKey(
					AsciiString( "MapSelectMenu.wnd:RadioButtonEasyAI" ).str() );
				GameWindow *radioButtonEasyAI = TheWindowManager->winGetWindowFromId( parent, radioButtonEasyAIID );			
				GadgetRadioSetSelection(radioButtonEasyAI, FALSE);
				s_AIDiff = DIFFICULTY_EASY;
				break;
			}
			case DIFFICULTY_NORMAL:
			{
				NameKeyType radioButtonMediumAIID = TheNameKeyGenerator->nameToKey(
					AsciiString( "MapSelectMenu.wnd:RadioButtonMediumAI" ).str() );
				GameWindow *radioButtonMediumAI = TheWindowManager->winGetWindowFromId( parent, radioButtonMediumAIID );
				GadgetRadioSetSelection(radioButtonMediumAI, FALSE);
				s_AIDiff = DIFFICULTY_NORMAL;
				break;
			}
			case DIFFICULTY_HARD:
			{
				NameKeyType radioButtonHardAIID = TheNameKeyGenerator->nameToKey(
					AsciiString( "MapSelectMenu.wnd:RadioButtonHardAI" ).str() );
				GameWindow *radioButtonHardAI = TheWindowManager->winGetWindowFromId( parent, radioButtonHardAIID );			
				GadgetRadioSetSelection(radioButtonHardAI, FALSE);
				s_AIDiff = DIFFICULTY_HARD;
				break;
			}

		default:
			{
				DEBUG_CRASH(("unrecognized difficulty level in the script engine"));
			}
			
		}
	} // if (TheScriptEngine)
}

// BFME's populateMapListbox call site: see the note above MapSelectMenuSystem.
void __cdecl bfmePopulateMapListFlags( void *listbox, char useSystemMaps, char isMultiplayer, void *mapToSelect );

// BFME clears GameWindow+0x1F4 on the menu parent right after focusing it (the
// same store as ReplayMenuInit, SaveLoadMenuInit and WOLStatusMenu). Only the
// offset is recoverable, so the field keeps its address.
class BfmeMenuParentView
{
public:
	char m_pad[ 0x1F4 ];
	void *m_fieldAt1F4;
};

//-------------------------------------------------------------------------------------------------
/** Initialize the MapSelect menu */
//-------------------------------------------------------------------------------------------------
// Retail 0x004D1370, named by the FunctionLexicon row at VA 0x012A99A4 whose
// literal 0x01086CC0 "MapSelectMenuInit" pairs with ILT 0x0000274D. BFME adds
// the HeadlessCount combo box ("---" then 1..7), selects its first entry, and
// clears the parent's +0x1F4 field.
void MapSelectMenuInit( WindowLayout *layout, void *userData )
{
	showSoloMaps = true;
	buttonPushed = false;
	isShuttingDown = false;
	startGame = false;
	TheShell->showShellMap(TRUE);
	// show menu
	// Open-BFME5: BFME made WindowLayout::hide virtual -- retail reaches it here
	// through vtable slot 0x10 (`mov eax,[ecx]` / `call [eax+0x10]`) where the
	// Zero Hour header declares it an ordinary member. Same drift and same
	// TU-local shim as NetworkDirectConnect.cpp; see BfmeVirtualHideLayout above.
	((BfmeVirtualHideLayout *)layout)->hide( FALSE );

	OptionPreferences pref;
	Bool usesSystemMapDir = pref.usesSystemMapDir();

	// get the listbox window
	AsciiString listString( "MapSelectMenu.wnd:ListboxMap" );
	NameKeyType mapListID = TheNameKeyGenerator->nameToKey( listString.str() );
	mapList = TheWindowManager->winGetWindowFromId( NULL, mapListID );
	if( mapList )
	{
		if (TheMapCache)
			TheMapCache->updateCache();
		bfmePopulateMapListFlags( mapList, usesSystemMapDir, !showSoloMaps, (void *)&AsciiString::TheEmptyString );
	}

	GameWindow *headlessCount = TheWindowManager->winGetWindowFromId( NULL,
		TheNameKeyGenerator->nameToKey( "MapSelectMenu.wnd:HeadlessCount" ) );
	GadgetComboBoxAddEntry( headlessCount, UnicodeString( L"---" ), -1 );
	for( Int i = 1; i < 8; ++i )
	{
		UnicodeString countText;
		countText.format( UnicodeString( L"%i" ), i );
		GadgetComboBoxAddEntry( headlessCount, countText, -1 );
	}
	GadgetComboBoxSetSelectedPos( headlessCount, 0 );

	// set keyboard focus to main parent
	AsciiString parentName( "MapSelectMenu.wnd:MapSelectMenuParent" );
	NameKeyType parentID = TheNameKeyGenerator->nameToKey( parentName.str() );
	GameWindow *parent = TheWindowManager->winGetWindowFromId( NULL, parentID );
	TheWindowManager->winSetFocus( parent );
	if( parent )
		((BfmeMenuParentView *)parent)->m_fieldAt1F4 = NULL;

	NameKeyType buttonBackID = TheNameKeyGenerator->nameToKey( AsciiString("MapSelectMenu.wnd:ButtonBack").str() );
	GameWindow *buttonBack = TheWindowManager->winGetWindowFromId( NULL, buttonBackID );
	
	NameKeyType buttonOKID = TheNameKeyGenerator->nameToKey( AsciiString("MapSelectMenu.wnd:ButtonOK").str() );
	GameWindow *buttonOK = TheWindowManager->winGetWindowFromId( NULL, buttonOKID );


	TheShell->registerWithAnimateManager(buttonBack, WIN_ANIMATION_SLIDE_RIGHT, TRUE,0);
	TheShell->registerWithAnimateManager(buttonOK, WIN_ANIMATION_SLIDE_LEFT, TRUE, 0);

	SetDifficultyRadioButtonMapSelectMenu();

	radioButtonSystemMapsID = TheNameKeyGenerator->nameToKey( "MapSelectMenu.wnd:RadioButtonSystemMaps" );
	radioButtonUserMapsID = TheNameKeyGenerator->nameToKey( "MapSelectMenu.wnd:RadioButtonUserMaps" );
	GameWindow *radioButtonSystemMaps = TheWindowManager->winGetWindowFromId( parent, radioButtonSystemMapsID );
	GameWindow *radioButtonUserMaps = TheWindowManager->winGetWindowFromId( parent, radioButtonUserMapsID );
	if (usesSystemMapDir)
		GadgetRadioSetSelection( radioButtonSystemMaps, FALSE );
	else
		GadgetRadioSetSelection( radioButtonUserMaps, FALSE );
}  // end MapSelectMenuInit

//-------------------------------------------------------------------------------------------------
/** MapSelect menu shutdown method */
//-------------------------------------------------------------------------------------------------
void MapSelectMenuShutdown( WindowLayout *layout, void *userData )
{
	if (!startGame)
		isShuttingDown = true;

	// if we are shutting down for an immediate pop, skip the animations
	Bool popImmediate = *(Bool *)userData;
	if( popImmediate )
	{

		shutdownCompleteMapSelectMenu( layout );
		return;

	}  //end if

	if (!startGame)
		TheShell->reverseAnimatewindow();

}  // end MapSelectMenuShutdown

//-------------------------------------------------------------------------------------------------
/** MapSelect menu update method */
//-------------------------------------------------------------------------------------------------
void MapSelectMenuUpdate( WindowLayout *layout, void *userData )
{

	if (startGame && TheShell->isAnimFinished())
		doGameStart();

	// We'll only be successful if we've requested to 
	if(isShuttingDown && TheShell->isAnimFinished())
		shutdownCompleteMapSelectMenu(layout);


}  // end MapSelectMenuUpdate

//-------------------------------------------------------------------------------------------------
/** Map select menu input callback */
//-------------------------------------------------------------------------------------------------
WindowMsgHandledType MapSelectMenuInput( GameWindow *window, UnsignedInt msg,
																				 WindowMsgData mData1, WindowMsgData mData2 )
{

	switch( msg ) 
	{

		// --------------------------------------------------------------------------------------------
		case GWM_CHAR:
		{
			UnsignedByte key = mData1;
			UnsignedByte state = mData2;
			if (buttonPushed)
				break;

			switch( key )
			{

				// ----------------------------------------------------------------------------------------
				case KEY_ESC:
				{
					
					//
					// send a simulated selected event to the parent window of the
					// back/exit button
					//
					if( BitTest( state, KEY_STATE_UP ) )
					{
						AsciiString buttonName( "MapSelectMenu.wnd:ButtonBack" );
						NameKeyType buttonID = TheNameKeyGenerator->nameToKey( buttonName );
						GameWindow *button = TheWindowManager->winGetWindowFromId( window, buttonID );

						TheWindowManager->winSendSystemMsg( window, GBM_SELECTED, 
																								(WindowMsgData)button, buttonID );

					}  // end if

					// don't let key fall through anywhere else
					return MSG_HANDLED;

				}  // end escape

			}  // end switch( key )

		}  // end char

	}  // end switch( msg )

	return MSG_IGNORED;

}  // end MapSelectMenuInput

//-------------------------------------------------------------------------------------------------
/** MapSelect menu window system callback */
//-------------------------------------------------------------------------------------------------
// Retail 0x004D1C40, named by the FunctionLexicon row at 0x00EA94DC
// (MapSelectMenuSystem) whose ILT 0x0002EB81 jumps here.
//
// BFME's populateMapListbox call site is the cdecl four-argument helper at
// 0x00457090 (reached through ILT 0x00029CEE); its last argument is the
// address of AsciiString::TheEmptyString, i.e. taken by reference.
void __cdecl bfmePopulateMapListFlags( void *listbox, char useSystemMaps, char isMultiplayer, void *mapToSelect );

// Retail 0x004D1080 (Zero Hour's setupGameStart shape plus a BFME refresh)
// takes the chosen map name by value. Retail builds that argument in place with
// the out-of-line AsciiString(const char *) copy at 0x0005EE70 (ILT 0x00012C42)
// and the callee releases it through the StringBase<char> dtor 0x00887940, so
// the parameter is the real AsciiString; the landed row spells the same type
// as its alias AsciiStringYH, hence the second pinned spelling.
extern void __cdecl bfmeCommitYH( AsciiString label );

// Retail 0x012F3E70: filled from the HeadlessCount combo box selection.
extern void *g_bfmePtrAAV;

WindowMsgHandledType MapSelectMenuSystem( GameWindow *window, UnsignedInt msg,
																				  WindowMsgData mData1, WindowMsgData mData2 )
{
	static NameKeyType buttonBack = NAMEKEY_INVALID;
	static NameKeyType buttonOK = NAMEKEY_INVALID;
	static NameKeyType listboxMap = NAMEKEY_INVALID;
	static NameKeyType radioButtonEasyAI = NAMEKEY_INVALID;
	static NameKeyType radioButtonMediumAI = NAMEKEY_INVALID;
	static NameKeyType radioButtonHardAI = NAMEKEY_INVALID;
	switch( msg )
	{

		// --------------------------------------------------------------------------------------------
		case GWM_CREATE:
		{

			// get ids for our children controls
			buttonBack = TheNameKeyGenerator->nameToKey( AsciiString("MapSelectMenu.wnd:ButtonBack") );
			buttonOK = TheNameKeyGenerator->nameToKey( AsciiString("MapSelectMenu.wnd:ButtonOK") );
			listboxMap = TheNameKeyGenerator->nameToKey( AsciiString("MapSelectMenu.wnd:ListboxMap") );
			radioButtonEasyAI = TheNameKeyGenerator->nameToKey( AsciiString("MapSelectMenu.wnd:RadioButtonEasyAI") );
			radioButtonMediumAI = TheNameKeyGenerator->nameToKey( AsciiString("MapSelectMenu.wnd:RadioButtonMediumAI") );
			radioButtonHardAI = TheNameKeyGenerator->nameToKey( AsciiString("MapSelectMenu.wnd:RadioButtonHardAI") );
			break;

		}  // end create

		//---------------------------------------------------------------------------------------------
		case GWM_DESTROY:
		{

			break;

		}  // end case

		// --------------------------------------------------------------------------------------------
		case GWM_INPUT_FOCUS:
		{

			// if we're givin the opportunity to take the keyboard focus we must say we want it
			if( mData1 == TRUE )
				*(Bool *)mData2 = TRUE;

			return MSG_HANDLED;

		}  // end input

		//---------------------------------------------------------------------------------------------
		case GBM_SELECTED:
		{
			if (buttonPushed)
				break;

			GameWindow *control = (GameWindow *)mData1;
			Int controlID = control->winGetWindowId();

			static NameKeyType singlePlayerID = NAMEKEY("MapSelectMenu.wnd:ButtonSinglePlayer");
			static NameKeyType multiplayerID = NAMEKEY("MapSelectMenu.wnd:ButtonMultiplayer");
			if ( controlID == singlePlayerID )
			{
				showSoloMaps = true;
				OptionPreferences pref;
				bfmePopulateMapListFlags( mapList, pref.usesSystemMapDir(), !showSoloMaps, (void *)&AsciiString::TheEmptyString );
			}
			else if ( controlID == multiplayerID )
			{
				showSoloMaps = false;
				OptionPreferences pref;
				bfmePopulateMapListFlags( mapList, pref.usesSystemMapDir(), !showSoloMaps, (void *)&AsciiString::TheEmptyString );
			}
			else if ( controlID == radioButtonSystemMapsID )
			{
				if (TheMapCache)
					TheMapCache->updateCache();
				bfmePopulateMapListFlags( mapList, TRUE, !showSoloMaps, (void *)&AsciiString::TheEmptyString );
				OptionPreferences pref;
				pref["UseSystemMapDir"] = "yes";
				pref.write();
			}
			else if ( controlID == radioButtonUserMapsID )
			{
				if (TheMapCache)
					TheMapCache->updateCache();
				bfmePopulateMapListFlags( mapList, FALSE, !showSoloMaps, (void *)&AsciiString::TheEmptyString );
				OptionPreferences pref;
				pref["UseSystemMapDir"] = "no";
				pref.write();
			}
			else if( controlID == buttonBack )
			{

				// go back one screen
				TheShell->pop();
				buttonPushed = true;

			}  // end if
			else if( controlID == buttonOK )
			{

				Int selected;
				UnicodeString map;
				GameWindow *mapWindow = TheWindowManager->winGetWindowFromId( NULL, listboxMap );

				// get the selected index
				GadgetListBoxGetSelected( mapWindow, &selected );

				if( selected != -1 )
				{
					buttonPushed = true;
					// reset the campaign manager to empty
					if( TheCampaignManager )
					  TheCampaignManager->setCampaign( AsciiString( "" ) );
					// get text of the map to load
					const char *mapFname = (const char *)GadgetListBoxGetItemData( mapWindow, selected );
					DEBUG_ASSERTCRASH(mapFname, ("No map item data"));
					if (mapFname)
					{
						GameWindow *headlessCount = TheWindowManager->winGetWindowFromId( NULL,
							NAMEKEY("MapSelectMenu.wnd:HeadlessCount") );
						GadgetComboBoxGetSelectedPos( headlessCount, (Int *)&g_bfmePtrAAV );
						bfmeCommitYH( mapFname );
					}
				}  // end if

			}  // end else if
			else if( controlID == radioButtonEasyAI)
			{
				s_AIDiff = DIFFICULTY_EASY;
			}
			else if( controlID == radioButtonMediumAI)
			{
				s_AIDiff = DIFFICULTY_NORMAL;
			}
			else if( controlID == radioButtonHardAI)
			{
				s_AIDiff = DIFFICULTY_HARD;
			}
			break;

		}  // end selected
		// BFME's list box double-click message is 0x4015 (GBM_SELECTED + 0xD).
		case 0x4015:
			{
				if (buttonPushed)
					break;

				GameWindow *control = (GameWindow *)mData1;
				Int controlID = control->winGetWindowId();
				if( controlID == listboxMap )
				{
					int rowSelected = mData2;

					if (rowSelected >= 0)
					{
						//buttonPushed = true;
						GadgetListBoxSetSelected( control, rowSelected );
						NameKeyType buttonOKID = TheNameKeyGenerator->nameToKey( AsciiString("MapSelectMenu.wnd:ButtonOK") );
						GameWindow *buttonOK = TheWindowManager->winGetWindowFromId( NULL, buttonOKID );

						TheWindowManager->winSendSystemMsg( window, GBM_SELECTED,
																								(WindowMsgData)buttonOK, buttonOKID );
					}
				}
				break;
			}
		default:
			return MSG_IGNORED;

	}  // end switch

	return MSG_HANDLED;

}  // end MapSelectMenuSystem

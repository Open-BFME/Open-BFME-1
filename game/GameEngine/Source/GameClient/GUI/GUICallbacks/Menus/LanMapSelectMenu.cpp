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

// FILE: LanMapSelectMenu.cpp ////////////////////////////////////////////////////////////////////////
// Author: Colin Day, October 2001
// Description: MapSelect menu window callbacks
///////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/GameEngine.h"
#include "Common/NameKeyGenerator.h"
#include "Common/MessageStream.h"
#include "Common/UserPreferences.h"
#include "GameClient/WindowLayout.h"
#include "GameClient/Gadget.h"
#include "GameClient/Shell.h"
#include "GameClient/GameWindowManager.h"
#include "GameClient/GadgetListBox.h"
#include "GameClient/GadgetRadioButton.h"
#include "GameNetwork/LANAPICallbacks.h"
#include "GameClient/MapUtil.h"
#include "GameNetwork/GUIUtil.h"

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

// PRIVATE DATA ///////////////////////////////////////////////////////////////////////////////////
static NameKeyType buttonBack = NAMEKEY_INVALID;
static NameKeyType buttonOK = NAMEKEY_INVALID;
static NameKeyType listboxMap = NAMEKEY_INVALID;
static NameKeyType winMapPreviewID = NAMEKEY_INVALID;
static GameWindow *parent = NULL;
static GameWindow *mapList = NULL;
static GameWindow *winMapPreview = NULL;
static NameKeyType radioButtonSystemMapsID = NAMEKEY_INVALID;
static NameKeyType radioButtonUserMapsID = NAMEKEY_INVALID;

static GameWindow *buttonMapStartPosition[MAX_SLOTS] = {NULL,NULL,NULL,NULL,
																								NULL,NULL,NULL,NULL };
static NameKeyType buttonMapStartPositionID[MAX_SLOTS] = { NAMEKEY_INVALID,NAMEKEY_INVALID,
																									NAMEKEY_INVALID,NAMEKEY_INVALID,
																										NAMEKEY_INVALID,NAMEKEY_INVALID,
																										NAMEKEY_INVALID,NAMEKEY_INVALID };


// PUBLIC FUNCTIONS ///////////////////////////////////////////////////////////////////////////////
void positionStartSpots( AsciiString mapName, GameWindow *buttonMapStartPositions[], GameWindow *mapWindow, Bool onLoadScreen);
static const char *layoutFilename = "LanGameOptionsMenu.wnd";
static const char *parentName = "LanGameOptionsMenuParent";
static const char *gadgetsToHide[] =
{
	"MapWindow",
	//"StaticTextTitle",
	"StaticTextTeam",
	"StaticTextFaction",
	"StaticTextColor",
	"TextEntryMapDisplay",
	"ButtonSelectMap",
	"ButtonStart",
	"StaticTextMapPreview",

	NULL // keep this last
};
static const char *perPlayerGadgetsToHide[] =
{
	"ComboBoxTeam",
	"ComboBoxColor",
	"ComboBoxPlayerTemplate",
	NULL // keep this last
};

static void showLANGameOptionsUnderlyingGUIElements( Bool show )
{
	ShowUnderlyingGUIElements( show, layoutFilename, parentName, gadgetsToHide, perPlayerGadgetsToHide );
	GameWindow *win	= TheWindowManager->winGetWindowFromId( NULL, TheNameKeyGenerator->nameToKey("LanGameOptionsMenu.wnd:ButtonBack") );
	if(win)
		win->winEnable( show );

}

static void NullifyControls()
{
	mapList = NULL;
	winMapPreview = NULL;
	parent = NULL;
	for (Int i=0; i<MAX_SLOTS; ++i)
	{
		buttonMapStartPosition[i] = NULL;
	}
}

//-------------------------------------------------------------------------------------------------
/** Initialize the MapSelect menu */
//-------------------------------------------------------------------------------------------------
void LanMapSelectMenuInit( WindowLayout *layout, void *userData )
{
	showLANGameOptionsUnderlyingGUIElements(FALSE);

	// set keyboard focus to main parent
	AsciiString parentName( "LanMapSelectMenu.wnd:LanMapSelectMenuParent" );
	NameKeyType parentID = TheNameKeyGenerator->nameToKey( parentName );
	parent = TheWindowManager->winGetWindowFromId( NULL, parentID );

	TheWindowManager->winSetFocus( parent );

	LANPreferences pref;
	Bool usesSystemMapDir = pref.usesSystemMapDir();

	const MapMetaData *mmd = TheMapCache->findMap(TheLAN->GetMyGame()->getMap());
	if (mmd)
	{
		usesSystemMapDir = mmd->m_isOfficial;
	}


	buttonBack = TheNameKeyGenerator->nameToKey( AsciiString("LanMapSelectMenu.wnd:ButtonBack") );
	buttonOK = TheNameKeyGenerator->nameToKey( AsciiString("LanMapSelectMenu.wnd:ButtonOK") );
	listboxMap = TheNameKeyGenerator->nameToKey( AsciiString("LanMapSelectMenu.wnd:ListboxMap") );
	winMapPreviewID = TheNameKeyGenerator->nameToKey( AsciiString("LanMapSelectMenu.wnd:WinMapPreview") );

	radioButtonSystemMapsID = TheNameKeyGenerator->nameToKey( "LanMapSelectMenu.wnd:RadioButtonSystemMaps" );
	radioButtonUserMapsID = TheNameKeyGenerator->nameToKey( "LanMapSelectMenu.wnd:RadioButtonUserMaps" );
	GameWindow *radioButtonSystemMaps = TheWindowManager->winGetWindowFromId( parent, radioButtonSystemMapsID );
	GameWindow *radioButtonUserMaps = TheWindowManager->winGetWindowFromId( parent, radioButtonUserMapsID );
	winMapPreview = TheWindowManager->winGetWindowFromId(parent, winMapPreviewID);
	if (usesSystemMapDir)
		GadgetRadioSetSelection( radioButtonSystemMaps, FALSE );
	else
		GadgetRadioSetSelection( radioButtonUserMaps, FALSE );

	AsciiString tmpString;
	for (Int i = 0; i < MAX_SLOTS; i++)
	{
		tmpString.format("LanMapSelectMenu.wnd:ButtonMapStartPosition%d", i);
		buttonMapStartPositionID[i] = TheNameKeyGenerator->nameToKey( tmpString );
		buttonMapStartPosition[i] = TheWindowManager->winGetWindowFromId( winMapPreview, buttonMapStartPositionID[i] );
		DEBUG_ASSERTCRASH(buttonMapStartPosition[i], ("Could not find the ButtonMapStartPosition[%d]",i ));
		buttonMapStartPosition[i]->winHide(TRUE);
		buttonMapStartPosition[i]->winEnable(FALSE);
	}

	// get the listbox window
	AsciiString listString( "LanMapSelectMenu.wnd:ListboxMap" );
	NameKeyType mapListID = TheNameKeyGenerator->nameToKey( listString );
	mapList = TheWindowManager->winGetWindowFromId( parent, mapListID );
	if( mapList )
	{
		if (TheMapCache)
			TheMapCache->updateCache();
		populateMapListbox( mapList, usesSystemMapDir, TRUE, TheLAN->GetMyGame()->getMap() );
	}
}  // end LanMapSelectMenuInit

//-------------------------------------------------------------------------------------------------
/** MapSelect menu shutdown method */
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// Open-BFME5: BFME made WindowLayout::hide VIRTUAL. Retail reaches it through
// vtable slot 0x10 -- `mov eax,[esi]' then `call dword ptr [eax+0x10]' -- where
// the Zero Hour WindowLayout.h in this tree declares it an ordinary member and
// we emit a direct call. Correcting the declaration would touch every TU that
// includes WindowLayout.h and force the full repo gate, so it is spelled
// TU-locally, the same way NetworkDirectConnect.cpp already does it: a shim
// whose fifth virtual lands on that slot, and a cast at the one call site.
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

void LanMapSelectMenuShutdown( WindowLayout *layout, void *userData )
{

	// hide menu
	((BfmeVirtualHideLayout *)layout)->hide( TRUE );

	NullifyControls();
	
	// our shutdown is complete
	TheShell->shutdownComplete( layout );
}  // end LanMapSelectMenuShutdown

//-------------------------------------------------------------------------------------------------
/** MapSelect menu update method */
//-------------------------------------------------------------------------------------------------
void LanMapSelectMenuUpdate( WindowLayout *layout, void *userData )
{

}  // end LanMapSelectMenuUpdate

//-------------------------------------------------------------------------------------------------
/** Map select menu input callback */
//-------------------------------------------------------------------------------------------------
WindowMsgHandledType LanMapSelectMenuInput( GameWindow *window, UnsignedInt msg,
																				 WindowMsgData mData1, WindowMsgData mData2 )
{

	switch( msg ) 
	{

		// --------------------------------------------------------------------------------------------
		case GWM_CHAR:
		{
			UnsignedByte key = mData1;
			UnsignedByte state = mData2;

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
						AsciiString buttonName( "LanMapSelectMenu.wnd:ButtonBack" );
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

}  // end LanMapSelectMenuInput

//-------------------------------------------------------------------------------------------------
/** MapSelect menu window system callback */
//-------------------------------------------------------------------------------------------------
class BfmeLanMapAPI
{
public:
    virtual void slot00() = 0;
    virtual void slot04() = 0;
    virtual void slot08() = 0;
    virtual void slot0C() = 0;
    virtual void slot10() = 0;
    virtual void slot14() = 0;
    virtual void slot18() = 0;
    virtual void slot1C() = 0;
    virtual void slot20() = 0;
    virtual void slot24() = 0;
    virtual void slot28() = 0;
    virtual void slot2C() = 0;
    virtual void slot30() = 0;
    virtual void slot34() = 0;
    virtual void slot38() = 0;
    virtual void slot3C() = 0;
    virtual void slot40() = 0;
    virtual void slot44() = 0;
    virtual void slot48() = 0;
    virtual void slot4C() = 0;
    virtual void slot50() = 0;
    virtual void slot54() = 0;
    virtual void slot58() = 0;
    virtual void slot5C() = 0;
    virtual void slot60() = 0;
    virtual void slot64() = 0;
    virtual void slot68() = 0;
    virtual void slot6C() = 0;
    virtual void slot70() = 0;
    virtual void slot74() = 0;
    virtual void slot78() = 0;
    virtual void slot7C() = 0;
    virtual void slot80() = 0;
    virtual void slot84() = 0;
    virtual void slot88() = 0;
    virtual void slot8C() = 0;
    virtual void slot90() = 0;
    virtual void slot94() = 0;
    virtual void slot98() = 0;
    virtual void slot9C() = 0;
    virtual void slotA0() = 0;
    virtual void slotA4() = 0;
    virtual void slotA8() = 0;
    virtual void slotAC() = 0;
    virtual void slotB0() = 0;
    virtual void slotB4() = 0;
    virtual void slotB8() = 0;
    virtual void slotBC() = 0;
    virtual LANGameInfo *GetMyGame() = 0;
};

void resetLanSession(int mode);
void j_00029cee();
typedef Int (__cdecl *BfmePopulateRefFn)(GameWindow *, Bool, Bool, const AsciiString &);
class BfmeVirtualLayoutTeardown { public: virtual void slot00() = 0; virtual void deletingDestructor(unsigned int) = 0; virtual void slot08() = 0; virtual void slot0C() = 0; virtual void slot10() = 0; virtual void slot14() = 0; virtual void slot18() = 0; virtual void slot1C() = 0; virtual void destroyWindows() = 0; };
class BfmeLanMapGameInfo { public: virtual void slot00() = 0; virtual void slot04() = 0; virtual void slot08() = 0; virtual void slot0C() = 0; virtual void slot10() = 0; virtual void slot14() = 0; virtual void slot18() = 0; virtual void resetStartSpots() = 0; virtual void adjustSlotsForMap() = 0; };
// ?LanMapSelectMenuSystem@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z
WindowMsgHandledType LanMapSelectMenuSystem( GameWindow *window, UnsignedInt msg, 
																				  WindowMsgData mData1, WindowMsgData mData2 )
{
	GameWindow *mapWindow = NULL;
	if (listboxMap != NULL)
	{
		mapWindow = TheWindowManager->winGetWindowFromId( parent, listboxMap );
	}

	switch( msg ) 
	{

		// --------------------------------------------------------------------------------------------
		case GWM_CREATE:
		{
			
			break;

		}  // end create

		//---------------------------------------------------------------------------------------------
		case GWM_DESTROY:
		{
			NullifyControls();

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
		case 0x4015:
			{
				GameWindow *control = (GameWindow *)mData1;
				Int controlID = control->winGetWindowId();
				if( controlID == listboxMap ) 
				{
					int rowSelected = mData2;
				
					if (rowSelected >= 0)
					{
						GadgetListBoxSetSelected( control, rowSelected );
						GameWindow *button = TheWindowManager->winGetWindowFromId( window, buttonOK );

						TheWindowManager->winSendSystemMsg( window, GBM_SELECTED, 
																								(WindowMsgData)button, buttonOK );
					}
				}
				break;
			}
		//---------------------------------------------------------------------------------------------
		case GBM_SELECTED:
		{
			GameWindow *control = (GameWindow *)mData1;
			Int controlID = control->winGetWindowId();

			if ( controlID == radioButtonSystemMapsID )
			{
				if (TheMapCache)
					TheMapCache->updateCache();
				((BfmePopulateRefFn)&j_00029cee)( mapList, TRUE, TRUE, ((BfmeLanMapAPI *)TheLAN)->GetMyGame()->getMap() );
				LANPreferences pref;
				pref["UseSystemMapDir"] = "yes";
				pref.write();
			}
			else if ( controlID == radioButtonUserMapsID )
			{
				if (TheMapCache)
					TheMapCache->updateCache();
				((BfmePopulateRefFn)&j_00029cee)( mapList, FALSE, TRUE, ((BfmeLanMapAPI *)TheLAN)->GetMyGame()->getMap() );
				LANPreferences pref;
				pref["UseSystemMapDir"] = "no";
				pref.write();
			}
			else if ( controlID == buttonBack )
			{
				
				((BfmeVirtualLayoutTeardown *)mapSelectLayout)->destroyWindows();
				if (mapSelectLayout) ((BfmeVirtualLayoutTeardown *)mapSelectLayout)->deletingDestructor(1);
				mapSelectLayout = NULL;
				// set the controls to NULL since they've been destroyed.
				NullifyControls();
				showLANGameOptionsUnderlyingGUIElements(TRUE);
				resetLanSession( MAP_BACK );
			}  // end if
			else if ( controlID == buttonOK )
			{
				Int selected = -1;
				UnicodeString map;

				// get the selected index
				if (mapWindow != NULL)
				{
					GadgetListBoxGetSelected( mapWindow, &selected );
				}

				if( selected != -1 )
				{
					// get text of the map to load
					map = GadgetListBoxGetText( mapWindow, selected, 0 );

					// set the map name in the global data map name
					AsciiString asciiMap;
					const char *mapFname = (const char *)GadgetListBoxGetItemData( mapWindow, selected );
					DEBUG_ASSERTCRASH(mapFname, ("No map item data"));
					if (mapFname)
						asciiMap = mapFname;
					else
						asciiMap.translate( map );
					((BfmeLanMapAPI *)TheLAN)->GetMyGame()->setMap( asciiMap );
					asciiMap.toLower();
					MapCache *mapCache = TheMapCache;
                    std::map<AsciiString, MapMetaData>::iterator it = mapCache->find(asciiMap);
					if (it != mapCache->end())
					{
						((BfmeLanMapAPI *)TheLAN)->GetMyGame()->getSlot(0)->setMapAvailability(true);
						((BfmeLanMapAPI *)TheLAN)->GetMyGame()->setMapCRC( it->second.m_CRC );
						((BfmeLanMapAPI *)TheLAN)->GetMyGame()->setMapSize( it->second.m_filesize );

						((BfmeLanMapGameInfo *)((BfmeLanMapAPI *)TheLAN)->GetMyGame())->resetStartSpots();
						((BfmeLanMapGameInfo *)((BfmeLanMapAPI *)TheLAN)->GetMyGame())->adjustSlotsForMap(); // BGC- adjust the slots for the new map.
					}

					
					((BfmeVirtualLayoutTeardown *)mapSelectLayout)->destroyWindows();
					if (mapSelectLayout) ((BfmeVirtualLayoutTeardown *)mapSelectLayout)->deletingDestructor(1);
					mapSelectLayout = NULL;

					// set the controls to NULL since they've been destroyed.
					NullifyControls();

					showLANGameOptionsUnderlyingGUIElements(TRUE);
					resetLanSession(SEND_GAME_OPTS);

				}  // end if
			}  // end else if

			break;

		}  // end selected

		case 0x4014:
			{
				
				GameWindow *control = (GameWindow *)mData1;
				Int controlID = control->winGetWindowId();
				if( controlID == listboxMap ) 
				{
					int rowSelected = mData2;
					if( rowSelected < 0 )
					{
						positionStartSpots( AsciiString::TheEmptyString, buttonMapStartPosition, winMapPreview, FALSE);
//						winMapPreview->winClearStatus(WIN_STATUS_IMAGE);
						break;
					}
					winMapPreview->winSetStatus(WIN_STATUS_IMAGE);
					UnicodeString map;
					// get text of the map to load
					map = GadgetListBoxGetText( mapWindow, rowSelected, 0 );

					// set the map name in the global data map name
					AsciiString asciiMap;
					const char *mapFname = (const char *)GadgetListBoxGetItemData( mapWindow, rowSelected );
					DEBUG_ASSERTCRASH(mapFname, ("No map item data"));
					if (mapFname)
						asciiMap = mapFname;
					else
						asciiMap.translate( map );
					asciiMap.toLower();
					Image *image = getMapPreviewImage(asciiMap);
					winMapPreview->winSetUserData((void *)TheMapCache->findMap(asciiMap));
					if(image)
					{
						winMapPreview->winSetEnabledImage(0, image);
					}
					else
					{
						winMapPreview->winClearStatus(WIN_STATUS_IMAGE);
					}
					positionStartSpots( asciiMap, buttonMapStartPosition, winMapPreview, FALSE);
				}
				break;
			}

		default:
			return MSG_IGNORED;

	}  // end switch

	return MSG_HANDLED;

}  // end LanMapSelectMenuSystem

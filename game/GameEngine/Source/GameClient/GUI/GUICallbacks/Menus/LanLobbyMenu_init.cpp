// LanLobbyMenuInit: recovered from the banked Zero Hour body.
// Exact native body 0x004CF440, 2243 bytes; witnesses in build/unclaimed_map/astra_N/.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/stringbaseascii /Iinputs/reference/shims/stringbaseunicode /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Igame/Libraries/Source/WWVegas/WWLib
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

///////////////////////////////////////////////////////////////////////////////////////
// FILE: LanLobbyMenu_init.cpp
// Author: Chris Huybregts, October 2001
// Description: Lan Lobby Menu
///////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

extern "C" __declspec(dllimport) char *getenv( const char *name );

#include "Lib/BaseType.h"
#include "string_base.h"
#include "Common/CRC.h"
#include "Common/GameEngine.h"
#include "Common/GlobalData.h"
#include "Common/MultiplayerSettings.h"
#include "Common/NameKeyGenerator.h"
#include "Common/Player.h"
#include "Common/PlayerTemplate.h"
#include "Common/QuotedPrintable.h"
#include "Common/UserPreferences.h"
#include "GameClient/AnimateWindowManager.h"
#include "GameClient/GameText.h"
#include "GameClient/MapUtil.h"
#include "GameClient/Mouse.h"
#include "GameClient/WindowLayout.h"
#include "GameClient/Gadget.h"
#include "GameClient/Shell.h"
#include "GameClient/ShellHooks.h"
#include "GameClient/KeyDefs.h"
#include "GameClient/GameInfoWindow.h"
#include "GameClient/GameWindowManager.h"
#include "GameClient/GadgetListBox.h"
#include "GameClient/GadgetTextEntry.h"
#include "GameClient/MessageBox.h"
#include "GameClient/GameWindowTransitions.h"
#include "GameLogic/GameLogic.h"

#include "GameNetwork/IPEnumeration.h"
extern Bool LANisShuttingDown;
extern Bool LANbuttonPushed;
extern Bool LANSocketErrorDetected;
extern char * LANnextScreen;

static Int	initialGadgetDelay = 2;
static Bool justEntered = FALSE;



// window ids ------------------------------------------------------------------------------
static NameKeyType parentLanLobbyID = NAMEKEY_INVALID;
static NameKeyType buttonBackID = NAMEKEY_INVALID;
static NameKeyType buttonClearID = NAMEKEY_INVALID;
static NameKeyType buttonHostID = NAMEKEY_INVALID;
static NameKeyType buttonJoinID = NAMEKEY_INVALID;
static NameKeyType buttonDirectConnectID = NAMEKEY_INVALID;
static NameKeyType buttonEmoteID = NAMEKEY_INVALID;
static NameKeyType staticToolTipID = NAMEKEY_INVALID;
static NameKeyType textEntryPlayerNameID = NAMEKEY_INVALID;
static NameKeyType textEntryChatID = NAMEKEY_INVALID;
static NameKeyType listboxPlayersID = NAMEKEY_INVALID;
static NameKeyType staticTextGameInfoID = NAMEKEY_INVALID;


// Window Pointers ------------------------------------------------------------------------
static GameWindow *parentLanLobby = NULL;
static GameWindow *buttonBack = NULL;
static GameWindow *buttonClear = NULL;
static GameWindow *buttonHost = NULL;
static GameWindow *buttonJoin = NULL;
static GameWindow *buttonDirectConnect = NULL;
static GameWindow *buttonEmote = NULL;
static GameWindow *staticToolTip = NULL;
static GameWindow *textEntryPlayerName = NULL;
static GameWindow *textEntryChat = NULL;
static GameWindow *staticTextGameInfo = NULL;

//external declarations of the Gadgets the callbacks can use
extern NameKeyType listboxChatWindowID;
static GameWindow *listboxChatWindow = NULL;
static GameWindow *listboxPlayers = NULL;
extern NameKeyType listboxGamesID;
static GameWindow *listboxGames = NULL;

// hack to disable framerate limiter in LAN games
//static Bool shellmapOn;
static Bool useFpsLimit;
static UnicodeString defaultName;


static Bool Rva012F3D51;

extern void playerTooltip(GameWindow *, WinInstanceData *, UnsignedInt);
// Retail 0x004CFA24..0x004CFA29 and 0x004CFC76..0x004CFC83.
// The reference WindowLayout declares these virtual methods as nonvirtual.
class Rva004CF440WindowLayout {
public:
 virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0c();
 virtual void hide(Bool); virtual void bringForward();
};
class LANGameInfo;
// TU-local native view: allocation 0x68 at 0x004CFA36; field stores at
// 0x004CFA84/0x004CFA92/0x004CFAA1. The ZH LANAPI view is shorter and
// lacks six BFME virtual slots. Unidentified slots retain numeric names.
class LANAPI {
public:
 LANAPI();
 virtual ~LANAPI();
 virtual void init();
 virtual void slot02();
 virtual void slot03();
 virtual void reset();
 virtual void slot05();
 virtual void slot06();
 virtual void slot07();
 virtual void slot08();
 virtual void slot09();
 virtual void RequestLocations();
 virtual void slot0b();
 virtual void slot0c();
 virtual void slot0d();
 virtual void slot0e();
 virtual void slot0f();
 virtual void slot10();
 virtual void slot11();
 virtual void slot12();
 virtual void slot13();
 virtual void slot14();
 virtual void slot15();
 virtual void slot16();
 virtual void slot17();
 virtual void RequestSetName(UnicodeString);
 virtual void slot19();
 virtual void slot1a();
 virtual void slot1b();
 virtual void slot1c();
 virtual void slot1d();
 virtual void slot1e();
 virtual void slot1f();
 virtual void slot20();
 virtual void slot21();
 virtual void slot22();
 virtual void slot23();
 virtual void slot24();
 virtual void slot25();
 virtual void slot26();
 virtual void slot27();
 virtual void slot28();
 virtual void slot29();
 virtual void slot2a();
 virtual void slot2b();
 virtual void slot2c();
 virtual Bool SetLocalIP(UnsignedInt);
 virtual void slot2e();
 virtual void slot2f();
 virtual LANGameInfo *GetMyGame();
 virtual void slot31();
 virtual void checkMOTD();
 unsigned char opaque04[0x58];
 GameWindow *field5c, *field60, *field64;
};
extern LANAPI *TheLAN;

static unsigned short Rva004CF440Length(const UnicodeString &text) {
 const void *buffer=*(void *const *)&text;
 return buffer ? *(const unsigned short *)((const char *)buffer+4) : 0;
}
void LanLobbyMenuInit( WindowLayout *layout, void *userData )
{
    if (TheLAN && TheLAN->GetMyGame() && *(const Bool *)((const char *)TheLAN->GetMyGame() + 0xD))
    {
        TheShell->popImmediate();
        delete TheLAN;
        TheLAN = NULL;
        return;
    }
	LANnextScreen = NULL;
	LANbuttonPushed = false;
	LANisShuttingDown = false;

	// get the ids for our controls
	parentLanLobbyID = TheNameKeyGenerator->nameToKey( AsciiString( "LanLobbyMenu.wnd:LanLobbyMenuParent" ) );
	buttonBackID = TheNameKeyGenerator->nameToKey( AsciiString( "LanLobbyMenu.wnd:ButtonBack" ) );
	buttonClearID = TheNameKeyGenerator->nameToKey( AsciiString( "LanLobbyMenu.wnd:ButtonClear" ) );
	buttonHostID = TheNameKeyGenerator->nameToKey( AsciiString( "LanLobbyMenu.wnd:ButtonHost" ) );
	buttonJoinID = TheNameKeyGenerator->nameToKey( AsciiString( "LanLobbyMenu.wnd:ButtonJoin" ) );
	buttonDirectConnectID = TheNameKeyGenerator->nameToKey( AsciiString( "LanLobbyMenu.wnd:ButtonDirectConnect" ) );
	buttonEmoteID = TheNameKeyGenerator->nameToKey( AsciiString( "LanLobbyMenu.wnd:ButtonEmote" ) );
	staticToolTipID = TheNameKeyGenerator->nameToKey( AsciiString( "LanLobbyMenu.wnd:StaticToolTip" ) );
	textEntryPlayerNameID = TheNameKeyGenerator->nameToKey( AsciiString( "LanLobbyMenu.wnd:TextEntryPlayerName" ) );
	textEntryChatID = TheNameKeyGenerator->nameToKey( AsciiString( "LanLobbyMenu.wnd:TextEntryChat" ) );
	listboxPlayersID = TheNameKeyGenerator->nameToKey( AsciiString( "LanLobbyMenu.wnd:ListboxPlayers" ) );
	listboxChatWindowID = TheNameKeyGenerator->nameToKey( AsciiString( "LanLobbyMenu.wnd:ListboxChatWindowLanLobby" ) );
	listboxGamesID = TheNameKeyGenerator->nameToKey( AsciiString( "LanLobbyMenu.wnd:ListboxGames" ) );
	staticTextGameInfoID = TheNameKeyGenerator->nameToKey( AsciiString( "LanLobbyMenu.wnd:StaticTextGameInfo" ) );


	// Get pointers to the window buttons
	parentLanLobby = TheWindowManager->winGetWindowFromId( NULL, parentLanLobbyID );
	buttonBack = TheWindowManager->winGetWindowFromId( NULL,  buttonBackID);
	buttonClear = TheWindowManager->winGetWindowFromId( NULL,  buttonClearID);
	buttonHost = TheWindowManager->winGetWindowFromId( NULL, buttonHostID );
	buttonJoin = TheWindowManager->winGetWindowFromId( NULL, buttonJoinID );
	buttonDirectConnect = TheWindowManager->winGetWindowFromId( NULL, buttonDirectConnectID );
	buttonEmote = TheWindowManager->winGetWindowFromId( NULL,buttonEmoteID  );
	staticToolTip = TheWindowManager->winGetWindowFromId( NULL, staticToolTipID );
	textEntryPlayerName = TheWindowManager->winGetWindowFromId( NULL, textEntryPlayerNameID );
	textEntryChat = TheWindowManager->winGetWindowFromId( NULL, textEntryChatID );
	listboxPlayers = TheWindowManager->winGetWindowFromId( NULL, listboxPlayersID );
	listboxChatWindow = TheWindowManager->winGetWindowFromId( NULL, listboxChatWindowID );
	listboxGames = TheWindowManager->winGetWindowFromId( NULL, listboxGamesID );
	staticTextGameInfo = TheWindowManager->winGetWindowFromId( NULL, staticTextGameInfoID );
	listboxPlayers->winSetTooltipFunc(playerTooltip);

	// Show Menu
	((Rva004CF440WindowLayout *)layout)->hide( FALSE );

	// Init LAN API Singleton
	if (!TheLAN)
	{
		TheLAN = NEW LANAPI();	/// @todo clh delete TheLAN and 
		useFpsLimit = *(const Bool *)((const char *)TheGlobalData + 0x1e);
	}
	else
	{

		TheLAN->reset();
	}

    TheLAN->field5c = listboxChatWindow;
    TheLAN->field60 = listboxPlayers;
    TheLAN->field64 = listboxGames;

	// Choose an IP address, then initialize the LAN singleton
	UnsignedInt IP = *(const UnsignedInt *)((const char *)TheGlobalData + 0xb10);
	IPEnumeration IPs;

	if (!IP)
	{
		EnumeratedIP *IPlist = IPs.getAddresses();
		/*
		while (IPlist && IPlist->getNext())
		{
			IPlist = IPlist->getNext();
		}
		*/
		DEBUG_ASSERTCRASH(IPlist, ("No IP addresses found!"));
		if (!IPlist)
		{
			/// @todo: display error and exit lan lobby if no IPs are found
		}

		//UnicodeString str;
		//str.format(L"Local IP chosen: %hs", IPlist->getIPstring().str());
		//GadgetListBoxAddEntryText(listboxChatWindow, str, chatSystemColor, -1, 0);
		IP = *(const UnsignedInt *)((const char *)IPlist + 4);
	}
	else
	{
		/*
		UnicodeString str;
		str.format(L"Default local IP: %d.%d.%d.%d",
			(IP >> 24),
			(IP >> 16) & 0xFF,
			(IP >> 8) & 0xFF,
			IP & 0xFF);
		GadgetListBoxAddEntryText(listboxChatWindow, str, chatSystemColor, -1, 0);
		*/
	}

	// TheLAN->init() sets us to be in a LAN menu screen automatically.
	const char *headless = getenv("_EA_RTS_HEADLESS");
	TheLAN->init();
	if (headless) IP = 0x7f000001;
	if (TheLAN->SetLocalIP(IP) == FALSE) {
		LANSocketErrorDetected = TRUE;
	}

	//Initialize the gadgets on the window
	//UnicodeString	txtInput;
	//txtInput.translate(IPs.getMachineName());
	LANPreferences prefs;
	if (headless) defaultName.format(UnicodeString(L"auto_client%i"), atoi(headless));
	else defaultName = prefs.getUserName();
	while (Rva004CF440Length(defaultName) > 12)
		defaultName.removeLastChar();
	GadgetTextEntrySetText( textEntryPlayerName, defaultName);
	// Clear the text entry line
	GadgetTextEntrySetText(textEntryChat, UnicodeString::TheEmptyString);

	GadgetListBoxReset(listboxPlayers);
	GadgetListBoxReset(listboxGames);

	while (Rva004CF440Length(defaultName) > 12)
		defaultName.removeLastChar();
	TheLAN->RequestSetName(defaultName);
	TheLAN->RequestLocations();

	/*
	UnicodeString unicodeChat;

	unicodeChat = L"Local IP list:";
	GadgetListBoxAddEntryText(listboxChatWindow, unicodeChat, chatSystemColor, -1, 0);

	IPlist = IPs.getAddresses();
	while (IPlist)
	{
		unicodeChat.translate(IPlist->getIPstring());
		GadgetListBoxAddEntryText(listboxChatWindow, unicodeChat, chatSystemColor, -1, 0);
		IPlist = IPlist->getNext();
	}
	*/

	// Set Keyboard to Main Parent
	//TheWindowManager->winSetFocus( parentLanLobby );
	TheWindowManager->winSetFocus( textEntryChat );
	CreateLANGameInfoWindow(staticTextGameInfo);

	//TheShell->showShellMap(FALSE);
	//shellmapOn = FALSE;
	// coming out of a game, re-load the shell map
	TheShell->showShellMap(TRUE);
		
	// check for MOTD
	TheLAN->checkMOTD();
	((Rva004CF440WindowLayout *)layout)->hide(FALSE);
	((Rva004CF440WindowLayout *)layout)->bringForward();

	justEntered = TRUE;
	Rva012F3D51 = TRUE;
	initialGadgetDelay = 2;
	GameWindow *win = TheWindowManager->winGetWindowFromId(NULL, TheNameKeyGenerator->nameToKey("LanLobbyMenu.wnd:GadgetParent"));
	if(win)
		win->winHide(TRUE);

	
	// animate controls
	//TheShell->registerWithAnimateManager(parentLanLobby, WIN_ANIMATION_SLIDE_TOP, TRUE);
//	TheShell->registerWithAnimateManager(buttonHost, WIN_ANIMATION_SLIDE_LEFT, TRUE, 600);
//	TheShell->registerWithAnimateManager(buttonJoin, WIN_ANIMATION_SLIDE_LEFT, TRUE, 400);
//	TheShell->registerWithAnimateManager(buttonDirectConnect, WIN_ANIMATION_SLIDE_LEFT, TRUE, 200);
//	//TheShell->registerWithAnimateManager(buttonOptions, WIN_ANIMATION_SLIDE_LEFT, TRUE, 1);
//	TheShell->registerWithAnimateManager(buttonBack, WIN_ANIMATION_SLIDE_RIGHT, TRUE, 1);

} // GameLobbyMenuInit

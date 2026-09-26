// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
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

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////
// FILE: WOLBuddyOverlay.cpp
// Author: Chris Huybregts, November 2001
// Description: Lan Lobby Menu
///////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/AudioEventRTS.h"
#include "Common/PlayerList.h"
#include "Common/Player.h"
#include "GameClient/GameText.h"
#include "GameClient/WindowLayout.h"
#include "GameClient/Gadget.h"
#include "GameClient/Shell.h"
#include "GameClient/KeyDefs.h"
#include "GameClient/GameWindowManager.h"
#include "GameClient/GadgetListBox.h"
#include "GameClient/GadgetPushButton.h"
#include "GameClient/GadgetStaticText.h"
#include "GameClient/GadgetTextEntry.h"
#include "GameClient/GadgetRadioButton.h"
#include "GameClient/Display.h"
#include "GameNetwork/GameSpyOverlay.h"
#include "GameNetwork/GameSpy/PeerDefs.h"
#include "GameNetwork/GameSpy/BuddyDefs.h"
#include "GameNetwork/GameSpy/BuddyThread.h"
#include "GameNetwork/GameSpy/LobbyUtils.h"
#include "GameNetwork/GameSpy/PersistentStorageDefs.h"
#include "GameNetwork/GameSpy/PersistentStorageThread.h"
#include "GameNetwork/GameSpy/ThreadUtils.h"

//-------------------------------------------------------------------------------------------------
// WindowLayout::hide is virtual in BFME (vtable slot 0x10) and non-virtual in
// the vendored ZH header. Editing the header would touch every TU that includes
// it, so the drift is spelled TU-locally: a shim whose fifth virtual lands on
// that slot, and a cast at each call site.
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


// PRIVATE DATA ///////////////////////////////////////////////////////////////////////////////////

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

// window ids ------------------------------------------------------------------------------
static NameKeyType parentID = NAMEKEY_INVALID;
static NameKeyType buttonHideID = NAMEKEY_INVALID;
static NameKeyType buttonAddBuddyID = NAMEKEY_INVALID;
static NameKeyType buttonDeleteBuddyID = NAMEKEY_INVALID;
static NameKeyType textEntryID = NAMEKEY_INVALID;
static NameKeyType listboxBuddyID = NAMEKEY_INVALID;
static NameKeyType listboxChatID = NAMEKEY_INVALID;
static NameKeyType buttonAcceptBuddyID = NAMEKEY_INVALID;
static NameKeyType buttonDenyBuddyID = NAMEKEY_INVALID;
static NameKeyType radioButtonBuddiesID = NAMEKEY_INVALID;
static NameKeyType radioButtonIgnoreID = NAMEKEY_INVALID;
static NameKeyType parentBuddiesID = NAMEKEY_INVALID;
static NameKeyType parentIgnoreID = NAMEKEY_INVALID;
static NameKeyType listboxIgnoreID = NAMEKEY_INVALID;
static NameKeyType buttonNotificationID = NAMEKEY_INVALID;


// Window Pointers ------------------------------------------------------------------------
static GameWindow *parent = NULL;
static GameWindow *buttonHide = NULL;
static GameWindow *buttonAddBuddy = NULL;
static GameWindow *buttonDeleteBuddy = NULL;
static GameWindow *textEntry = NULL;
static GameWindow *listboxBuddy = NULL;
static GameWindow *listboxChat = NULL;
static GameWindow *buttonAcceptBuddy = NULL;
static GameWindow *buttonDenyBuddy = NULL;
static GameWindow *radioButtonBuddies = NULL;
static GameWindow *radioButtonIgnore = NULL;
static GameWindow *parentBuddies = NULL;
static GameWindow *parentIgnore = NULL;
static GameWindow *listboxIgnore = NULL;

static Bool isOverlayActive = false;
void insertChat( BuddyMessage msg );
// RightClick pointers ---------------------------------------------------------------------
static GameWindow *rcMenu = NULL;
static WindowLayout *noticeLayout = NULL;
static UnsignedInt noticeExpires = 0;
enum { NOTIFICATION_EXPIRES = 3000 };

void setUnignoreText( WindowLayout *layout, AsciiString nick, GPProfile id);
void refreshIgnoreList( void );
void showNotificationBox( AsciiString nick, UnicodeString message);
void deleteNotificationBox( void );
static Bool lastNotificationWasStatus = FALSE;
static Int numOnlineInNotification = 0;

class BuddyControls
{
public:
	BuddyControls(void );
	GameWindow *listboxChat;
	NameKeyType listboxChatID;

	GameWindow *listboxBuddies;
	NameKeyType listboxBuddiesID;

	GameWindow *textEntryEdit;
	NameKeyType textEntryEditID;
	Bool isInit;
};

static BuddyControls buddyControls;
BuddyControls::BuddyControls(	void )
{
	listboxChat = NULL;
	listboxChatID = NAMEKEY_INVALID;
	listboxBuddies = NULL;
	listboxBuddiesID = NAMEKEY_INVALID;
	textEntryEdit = NULL;
	textEntryEditID = NAMEKEY_INVALID;
	isInit = FALSE;
}
// At this point I don't give a damn about how good this way is.  I'm doing it anyway.
enum
{
	BUDDY_RESETALL_CRAP = -1,
	BUDDY_WINDOW_BUDDIES = 0,
	BUDDY_WINDOW_DIPLOMACY,
	BUDDY_WINDOW_WELCOME_SCREEN,
};

// ?InitBuddyControls@@YAXH@Z
// Body in InitBuddyControlsThunk.cpp (exact 776B retail @ 0x004EA9D0), so this
// translation unit only needs the prototype its call sites below refer to.
void InitBuddyControls( Int );
// ?BuddyControlSystem@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z matched 1390 bytes (Open-BFME5)
__declspec(naked) WindowMsgHandledType BuddyControlSystem(GameWindow *, UnsignedInt, WindowMsgData, WindowMsgData)
{
	__asm
	{
		__emit 0x64;
		__emit 0xa1;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x6a;
		__emit 0xff;
		__emit 0x68;
		__emit 0x82;
		__emit 0xbf;
		__emit 0x02;
		__emit 0x01;
		__emit 0x50;
		__emit 0xa1;
		__emit 0x94;
		__emit 0x71;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x64;
		__emit 0x89;
		__emit 0x25;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x81;
		__emit 0xec;
		__emit 0xf8;
		__emit 0x02;
		__emit 0x00;
		__emit 0x00;
		__emit 0x53;
		__emit 0x55;
		__emit 0x33;
		__emit 0xdb;
		__emit 0x3b;
		__emit 0xc3;
		__emit 0x56;
		__emit 0x57;
		__emit 0x0f;
		__emit 0x84;
		__emit 0x25;
		__emit 0x05;
		__emit 0x00;
		__emit 0x00;
		__emit 0xa0;
		__emit 0x78;
		__emit 0x42;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x84;
		__emit 0xc0;
		__emit 0x0f;
		__emit 0x84;
		__emit 0x18;
		__emit 0x05;
		__emit 0x00;
		__emit 0x00;
		__emit 0x8b;
		__emit 0x84;
		__emit 0x24;
		__emit 0x1c;
		__emit 0x03;
		__emit 0x00;
		__emit 0x00;
		__emit 0x2d;
		__emit 0x16;
		__emit 0x40;
		__emit 0x00;
		__emit 0x00;
		__emit 0x0f;
		__emit 0x84;
		__emit 0x2a;
		__emit 0x03;
		__emit 0x00;
		__emit 0x00;
		__emit 0x83;
		__emit 0xe8;
		__emit 0x1a;
		__emit 0x0f;
		__emit 0x85;
		__emit 0xfd;
		__emit 0x04;
		__emit 0x00;
		__emit 0x00;
		__emit 0x8b;
		__emit 0x8c;
		__emit 0x24;
		__emit 0x20;
		__emit 0x03;
		__emit 0x00;
		__emit 0x00;
		__emit 0xe8;
		__emit 0x42;
		__emit 0xb4;
		__emit 0xb2;
		__emit 0xff;
		__emit 0x3b;
		__emit 0x05;
		__emit 0x74;
		__emit 0x42;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x0f;
		__emit 0x85;
		__emit 0xe5;
		__emit 0x04;
		__emit 0x00;
		__emit 0x00;
		__emit 0x8b;
		__emit 0x0d;
		__emit 0x68;
		__emit 0x42;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x8d;
		__emit 0x44;
		__emit 0x24;
		__emit 0x1c;
		__emit 0x50;
		__emit 0x51;
		__emit 0xc7;
		__emit 0x44;
		__emit 0x24;
		__emit 0x24;
		__emit 0xff;
		__emit 0xff;
		__emit 0xff;
		__emit 0xff;
		__emit 0xe8;
		__emit 0xbe;
		__emit 0xb4;
		__emit 0xb1;
		__emit 0xff;
		__emit 0x8b;
		__emit 0x44;
		__emit 0x24;
		__emit 0x24;
		__emit 0x83;
		__emit 0xc4;
		__emit 0x08;
		__emit 0x3b;
		__emit 0xc3;
		__emit 0x0f;
		__emit 0x8c;
		__emit 0x96;
		__emit 0x02;
		__emit 0x00;
		__emit 0x00;
		__emit 0x8b;
		__emit 0x15;
		__emit 0x68;
		__emit 0x42;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x53;
		__emit 0x50;
		__emit 0x52;
		__emit 0xe8;
		__emit 0xe0;
		__emit 0xbb;
		__emit 0xb1;
		__emit 0xff;
		__emit 0x8b;
		__emit 0x0d;
		__emit 0x94;
		__emit 0x71;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x8b;
		__emit 0xf0;
		__emit 0x8b;
		__emit 0x01;
		__emit 0x83;
		__emit 0xc4;
		__emit 0x0c;
		__emit 0x89;
		__emit 0x74;
		__emit 0x24;
		__emit 0x20;
		__emit 0xff;
		__emit 0x50;
		__emit 0x54;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x20;
		__emit 0x51;
		__emit 0x8b;
		__emit 0xf8;
		__emit 0x8d;
		__emit 0x54;
		__emit 0x24;
		__emit 0x18;
		__emit 0x52;
		__emit 0x8b;
		__emit 0xcf;
		__emit 0xe8;
		__emit 0xfb;
		__emit 0xe5;
		__emit 0xb3;
		__emit 0xff;
		__emit 0x8b;
		__emit 0x3f;
		__emit 0x39;
		__emit 0x7c;
		__emit 0x24;
		__emit 0x14;
		__emit 0x0f;
		__emit 0x84;
		__emit 0x75;
		__emit 0x04;
		__emit 0x00;
		__emit 0x00;
		__emit 0xa1;
		__emit 0x98;
		__emit 0x71;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x3b;
		__emit 0xc3;
		__emit 0x74;
		__emit 0x3c;
		__emit 0x8a;
		__emit 0x48;
		__emit 0x0c;
		__emit 0x84;
		__emit 0xc9;
		__emit 0x74;
		__emit 0x35;
		__emit 0x8a;
		__emit 0x48;
		__emit 0x0d;
		__emit 0x84;
		__emit 0xc9;
		__emit 0x74;
		__emit 0x2e;
		__emit 0xa1;
		__emit 0x48;
		__emit 0xd7;
		__emit 0x2e;
		__emit 0x01;
		__emit 0x8b;
		__emit 0x48;
		__emit 0x0c;
		__emit 0xe8;
		__emit 0xc2;
		__emit 0xa4;
		__emit 0xb2;
		__emit 0xff;
		__emit 0x84;
		__emit 0xc0;
		__emit 0x75;
		__emit 0x1d;
		__emit 0x33;
		__emit 0xff;
		__emit 0x8b;
		__emit 0x0d;
		__emit 0x98;
		__emit 0x71;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x57;
		__emit 0xe8;
		__emit 0xc9;
		__emit 0x8c;
		__emit 0xb1;
		__emit 0xff;
		__emit 0x39;
		__emit 0x70;
		__emit 0x44;
		__emit 0x0f;
		__emit 0x84;
		__emit 0x9e;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x47;
		__emit 0x83;
		__emit 0xff;
		__emit 0x08;
		__emit 0x7c;
		__emit 0xe5;
		__emit 0x89;
		__emit 0x5c;
		__emit 0x24;
		__emit 0x18;
		__emit 0x8b;
		__emit 0x15;
		__emit 0x70;
		__emit 0x42;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x52;
		__emit 0x8d;
		__emit 0x44;
		__emit 0x24;
		__emit 0x34;
		__emit 0x50;
		__emit 0xc7;
		__emit 0x84;
		__emit 0x24;
		__emit 0x18;
		__emit 0x03;
		__emit 0x00;
		__emit 0x00;
		__emit 0x01;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0xe8;
		__emit 0x75;
		__emit 0x4b;
		__emit 0xb3;
		__emit 0xff;
		__emit 0x83;
		__emit 0xc4;
		__emit 0x08;
		__emit 0x50;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x1c;
		__emit 0xc6;
		__emit 0x84;
		__emit 0x24;
		__emit 0x14;
		__emit 0x03;
		__emit 0x00;
		__emit 0x00;
		__emit 0x02;
		__emit 0xe8;
		__emit 0xdf;
		__emit 0xaf;
		__emit 0x39;
		__emit 0x00;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x30;
		__emit 0xc6;
		__emit 0x84;
		__emit 0x24;
		__emit 0x10;
		__emit 0x03;
		__emit 0x00;
		__emit 0x00;
		__emit 0x01;
		__emit 0xe8;
		__emit 0x6e;
		__emit 0xac;
		__emit 0x39;
		__emit 0x00;
		__emit 0x51;
		__emit 0x89;
		__emit 0x64;
		__emit 0x24;
		__emit 0x14;
		__emit 0x8b;
		__emit 0xcc;
		__emit 0x68;
		__emit 0x54;
		__emit 0x6e;
		__emit 0x33;
		__emit 0x01;
		__emit 0xe8;
		__emit 0x8d;
		__emit 0xae;
		__emit 0x39;
		__emit 0x00;
		__emit 0x8b;
		__emit 0x0d;
		__emit 0x70;
		__emit 0x42;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x51;
		__emit 0xe8;
		__emit 0xf5;
		__emit 0xf2;
		__emit 0xb1;
		__emit 0xff;
		__emit 0x83;
		__emit 0xc4;
		__emit 0x08;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x18;
		__emit 0xe8;
		__emit 0x45;
		__emit 0xb9;
		__emit 0x39;
		__emit 0x00;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x18;
		__emit 0xe8;
		__emit 0xcd;
		__emit 0x1d;
		__emit 0xb3;
		__emit 0xff;
		__emit 0x84;
		__emit 0xc0;
		__emit 0x0f;
		__emit 0x85;
		__emit 0x87;
		__emit 0x01;
		__emit 0x00;
		__emit 0x00;
		__emit 0x8b;
		__emit 0x44;
		__emit 0x24;
		__emit 0x18;
		__emit 0x33;
		__emit 0xed;
		__emit 0x3b;
		__emit 0xc5;
		__emit 0xbb;
		__emit 0x03;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x89;
		__emit 0x5c;
		__emit 0x24;
		__emit 0x50;
		__emit 0x74;
		__emit 0x4c;
		__emit 0x83;
		__emit 0xc0;
		__emit 0x08;
		__emit 0xeb;
		__emit 0x4c;
		__emit 0x39;
		__emit 0x1d;
		__emit 0x60;
		__emit 0x42;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x74;
		__emit 0x35;
		__emit 0x8b;
		__emit 0x0d;
		__emit 0x00;
		__emit 0x92;
		__emit 0x2b;
		__emit 0x01;
		__emit 0x6a;
		__emit 0x01;
		__emit 0x6a;
		__emit 0xff;
		__emit 0x6a;
		__emit 0xff;
		__emit 0x51;
		__emit 0x8b;
		__emit 0x0d;
		__emit 0x7c;
		__emit 0x14;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x8b;
		__emit 0x11;
		__emit 0x51;
		__emit 0x8b;
		__emit 0xc4;
		__emit 0x89;
		__emit 0x64;
		__emit 0x24;
		__emit 0x24;
		__emit 0x53;
		__emit 0x68;
		__emit 0x34;
		__emit 0x25;
		__emit 0x10;
		__emit 0x01;
		__emit 0x50;
		__emit 0xff;
		__emit 0x52;
		__emit 0x28;
		__emit 0x8b;
		__emit 0x0d;
		__emit 0x60;
		__emit 0x42;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x51;
		__emit 0xe8;
		__emit 0x98;
		__emit 0x28;
		__emit 0xb5;
		__emit 0xff;
		__emit 0x83;
		__emit 0xc4;
		__emit 0x18;
		__emit 0xb8;
		__emit 0x01;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0xe9;
		__emit 0x5a;
		__emit 0x03;
		__emit 0x00;
		__emit 0x00;
		__emit 0xb8;
		__emit 0x8c;
		__emit 0x38;
		__emit 0x07;
		__emit 0x01;
		__emit 0x68;
		__emit 0x80;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x50;
		__emit 0x8d;
		__emit 0x54;
		__emit 0x24;
		__emit 0x60;
		__emit 0x52;
		__emit 0xff;
		__emit 0x15;
		__emit 0x28;
		__emit 0x95;
		__emit 0x35;
		__emit 0x01;
		__emit 0x8b;
		__emit 0x0d;
		__emit 0xb4;
		__emit 0x71;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x83;
		__emit 0xc4;
		__emit 0x0c;
		__emit 0x8d;
		__emit 0x54;
		__emit 0x24;
		__emit 0x50;
		__emit 0x66;
		__emit 0x89;
		__emit 0xac;
		__emit 0x24;
		__emit 0x56;
		__emit 0x01;
		__emit 0x00;
		__emit 0x00;
		__emit 0x89;
		__emit 0x74;
		__emit 0x24;
		__emit 0x54;
		__emit 0x8b;
		__emit 0x01;
		__emit 0x52;
		__emit 0xff;
		__emit 0x50;
		__emit 0x18;
		__emit 0x8b;
		__emit 0x0d;
		__emit 0x94;
		__emit 0x71;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x8b;
		__emit 0x01;
		__emit 0xff;
		__emit 0x50;
		__emit 0x5c;
		__emit 0x8b;
		__emit 0xf8;
		__emit 0x89;
		__emit 0x6c;
		__emit 0x24;
		__emit 0x3c;
		__emit 0x89;
		__emit 0x6c;
		__emit 0x24;
		__emit 0x44;
		__emit 0x89;
		__emit 0x6c;
		__emit 0x24;
		__emit 0x48;
		__emit 0x55;
		__emit 0x88;
		__emit 0x9c;
		__emit 0x24;
		__emit 0x14;
		__emit 0x03;
		__emit 0x00;
		__emit 0x00;
		__emit 0xff;
		__emit 0x15;
		__emit 0xf0;
		__emit 0x94;
		__emit 0x35;
		__emit 0x01;
		__emit 0x8b;
		__emit 0x0d;
		__emit 0x94;
		__emit 0x71;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x89;
		__emit 0x44;
		__emit 0x24;
		__emit 0x38;
		__emit 0x8b;
		__emit 0x11;
		__emit 0x83;
		__emit 0xc4;
		__emit 0x04;
		__emit 0xff;
		__emit 0x52;
		__emit 0x70;
		__emit 0x8b;
		__emit 0x0d;
		__emit 0x94;
		__emit 0x71;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x8d;
		__emit 0x54;
		__emit 0x24;
		__emit 0x4c;
		__emit 0x89;
		__emit 0x44;
		__emit 0x24;
		__emit 0x38;
		__emit 0x8b;
		__emit 0x01;
		__emit 0x52;
		__emit 0xff;
		__emit 0x90;
		__emit 0x88;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x50;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x40;
		__emit 0xc6;
		__emit 0x84;
		__emit 0x24;
		__emit 0x14;
		__emit 0x03;
		__emit 0x00;
		__emit 0x00;
		__emit 0x04;
		__emit 0xe8;
		__emit 0xfe;
		__emit 0xa5;
		__emit 0x39;
		__emit 0x00;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x4c;
		__emit 0x88;
		__emit 0x9c;
		__emit 0x24;
		__emit 0x10;
		__emit 0x03;
		__emit 0x00;
		__emit 0x00;
		__emit 0xe8;
		__emit 0x9e;
		__emit 0xa2;
		__emit 0x39;
		__emit 0x00;
		__emit 0x8b;
		__emit 0x44;
		__emit 0x24;
		__emit 0x14;
		__emit 0x83;
		__emit 0xc0;
		__emit 0x18;
		__emit 0x50;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x48;
		__emit 0x89;
		__emit 0x74;
		__emit 0x24;
		__emit 0x44;
		__emit 0xe8;
		__emit 0xd9;
		__emit 0xa5;
		__emit 0x39;
		__emit 0x00;
		__emit 0x8d;
		__emit 0x44;
		__emit 0x24;
		__emit 0x58;
		__emit 0x50;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x28;
		__emit 0xe8;
		__emit 0x1b;
		__emit 0xb7;
		__emit 0x39;
		__emit 0x00;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x24;
		__emit 0x51;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x4c;
		__emit 0xc6;
		__emit 0x84;
		__emit 0x24;
		__emit 0x14;
		__emit 0x03;
		__emit 0x00;
		__emit 0x00;
		__emit 0x05;
		__emit 0xe8;
		__emit 0x55;
		__emit 0xae;
		__emit 0x39;
		__emit 0x00;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x24;
		__emit 0x88;
		__emit 0x9c;
		__emit 0x24;
		__emit 0x10;
		__emit 0x03;
		__emit 0x00;
		__emit 0x00;
		__emit 0xe8;
		__emit 0xe5;
		__emit 0xaa;
		__emit 0x39;
		__emit 0x00;
		__emit 0x8d;
		__emit 0x54;
		__emit 0x24;
		__emit 0x34;
		__emit 0x52;
		__emit 0x8b;
		__emit 0xcf;
		__emit 0xe8;
		__emit 0x6d;
		__emit 0xd4;
		__emit 0xb1;
		__emit 0xff;
		__emit 0x83;
		__emit 0xec;
		__emit 0x18;
		__emit 0x8d;
		__emit 0x44;
		__emit 0x24;
		__emit 0x4c;
		__emit 0x8b;
		__emit 0xcc;
		__emit 0x89;
		__emit 0x64;
		__emit 0x24;
		__emit 0x28;
		__emit 0x50;
		__emit 0xe8;
		__emit 0xc5;
		__emit 0x34;
		__emit 0xb4;
		__emit 0xff;
		__emit 0xe8;
		__emit 0xa1;
		__emit 0xdf;
		__emit 0xff;
		__emit 0xff;
		__emit 0x83;
		__emit 0xc4;
		__emit 0x18;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x34;
		__emit 0xc6;
		__emit 0x84;
		__emit 0x24;
		__emit 0x10;
		__emit 0x03;
		__emit 0x00;
		__emit 0x00;
		__emit 0x01;
		__emit 0xe8;
		__emit 0x22;
		__emit 0x3d;
		__emit 0xb3;
		__emit 0xff;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x18;
		__emit 0xe9;
		__emit 0x10;
		__emit 0x02;
		__emit 0x00;
		__emit 0x00;
		__emit 0x39;
		__emit 0x1d;
		__emit 0x60;
		__emit 0x42;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x0f;
		__emit 0x84;
		__emit 0x14;
		__emit 0x02;
		__emit 0x00;
		__emit 0x00;
		__emit 0x8b;
		__emit 0x0d;
		__emit 0x00;
		__emit 0x92;
		__emit 0x2b;
		__emit 0x01;
		__emit 0x6a;
		__emit 0x01;
		__emit 0x6a;
		__emit 0xff;
		__emit 0x6a;
		__emit 0xff;
		__emit 0x51;
		__emit 0x8b;
		__emit 0x0d;
		__emit 0x7c;
		__emit 0x14;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x8b;
		__emit 0x11;
		__emit 0x51;
		__emit 0x8b;
		__emit 0xc4;
		__emit 0x89;
		__emit 0x64;
		__emit 0x24;
		__emit 0x24;
		__emit 0x53;
		__emit 0x68;
		__emit 0x18;
		__emit 0x25;
		__emit 0x10;
		__emit 0x01;
		__emit 0x50;
		__emit 0xff;
		__emit 0x52;
		__emit 0x28;
		__emit 0x8b;
		__emit 0x0d;
		__emit 0x60;
		__emit 0x42;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x51;
		__emit 0xe8;
		__emit 0x1c;
		__emit 0x27;
		__emit 0xb5;
		__emit 0xff;
		__emit 0x83;
		__emit 0xc4;
		__emit 0x18;
		__emit 0xb8;
		__emit 0x01;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0xe9;
		__emit 0xde;
		__emit 0x01;
		__emit 0x00;
		__emit 0x00;
		__emit 0x8b;
		__emit 0xbc;
		__emit 0x24;
		__emit 0x20;
		__emit 0x03;
		__emit 0x00;
		__emit 0x00;
		__emit 0x8b;
		__emit 0xcf;
		__emit 0xe8;
		__emit 0x1f;
		__emit 0xb1;
		__emit 0xb2;
		__emit 0xff;
		__emit 0x3b;
		__emit 0x05;
		__emit 0x6c;
		__emit 0x42;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x0f;
		__emit 0x85;
		__emit 0xc2;
		__emit 0x01;
		__emit 0x00;
		__emit 0x00;
		__emit 0x8b;
		__emit 0xb4;
		__emit 0x24;
		__emit 0x24;
		__emit 0x03;
		__emit 0x00;
		__emit 0x00;
		__emit 0x8b;
		__emit 0x46;
		__emit 0x08;
		__emit 0x3b;
		__emit 0xc3;
		__emit 0x0f;
		__emit 0x8c;
		__emit 0xa9;
		__emit 0x01;
		__emit 0x00;
		__emit 0x00;
		__emit 0x53;
		__emit 0x50;
		__emit 0x57;
		__emit 0xe8;
		__emit 0xd9;
		__emit 0xb8;
		__emit 0xb1;
		__emit 0xff;
		__emit 0x8b;
		__emit 0x56;
		__emit 0x08;
		__emit 0x6a;
		__emit 0x01;
		__emit 0x52;
		__emit 0x57;
		__emit 0x89;
		__emit 0x44;
		__emit 0x24;
		__emit 0x38;
		__emit 0xe8;
		__emit 0xc9;
		__emit 0xb8;
		__emit 0xb1;
		__emit 0xff;
		__emit 0x8b;
		__emit 0xe8;
		__emit 0x8b;
		__emit 0x46;
		__emit 0x08;
		__emit 0x53;
		__emit 0x50;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x34;
		__emit 0x57;
		__emit 0x51;
		__emit 0x89;
		__emit 0x6c;
		__emit 0x24;
		__emit 0x38;
		__emit 0xe8;
		__emit 0x02;
		__emit 0x7f;
		__emit 0xb5;
		__emit 0xff;
		__emit 0x8b;
		__emit 0x56;
		__emit 0x08;
		__emit 0x52;
		__emit 0x57;
		__emit 0x89;
		__emit 0x9c;
		__emit 0x24;
		__emit 0x40;
		__emit 0x03;
		__emit 0x00;
		__emit 0x00;
		__emit 0xe8;
		__emit 0x21;
		__emit 0x3a;
		__emit 0xb1;
		__emit 0xff;
		__emit 0x83;
		__emit 0xc4;
		__emit 0x30;
		__emit 0x3b;
		__emit 0xeb;
		__emit 0x51;
		__emit 0x8b;
		__emit 0xcc;
		__emit 0x89;
		__emit 0x64;
		__emit 0x24;
		__emit 0x20;
		__emit 0x75;
		__emit 0x07;
		__emit 0x68;
		__emit 0xfc;
		__emit 0x24;
		__emit 0x10;
		__emit 0x01;
		__emit 0xeb;
		__emit 0x21;
		__emit 0x83;
		__emit 0xfd;
		__emit 0x01;
		__emit 0x75;
		__emit 0x17;
		__emit 0x68;
		__emit 0xd8;
		__emit 0x24;
		__emit 0x10;
		__emit 0x01;
		__emit 0xe8;
		__emit 0xba;
		__emit 0xb3;
		__emit 0x39;
		__emit 0x00;
		__emit 0x8b;
		__emit 0x0d;
		__emit 0x40;
		__emit 0x1b;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x8b;
		__emit 0x11;
		__emit 0xff;
		__emit 0x52;
		__emit 0x6c;
		__emit 0xeb;
		__emit 0x15;
		__emit 0x68;
		__emit 0xb8;
		__emit 0x24;
		__emit 0x10;
		__emit 0x01;
		__emit 0xe8;
		__emit 0xa3;
		__emit 0xb3;
		__emit 0x39;
		__emit 0x00;
		__emit 0x8b;
		__emit 0x0d;
		__emit 0x40;
		__emit 0x1b;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x8b;
		__emit 0x01;
		__emit 0xff;
		__emit 0x50;
		__emit 0x6c;
		__emit 0x8b;
		__emit 0xe8;
		__emit 0x8b;
		__emit 0x4d;
		__emit 0x08;
		__emit 0x89;
		__emit 0x0d;
		__emit 0x34;
		__emit 0x42;
		__emit 0x2f;
		__emit 0x01;
		__emit 0xe8;
		__emit 0xbd;
		__emit 0x2a;
		__emit 0xb5;
		__emit 0xff;
		__emit 0x8b;
		__emit 0x10;
		__emit 0x53;
		__emit 0x8b;
		__emit 0xc8;
		__emit 0xff;
		__emit 0x12;
		__emit 0x8b;
		__emit 0x0d;
		__emit 0x34;
		__emit 0x42;
		__emit 0x2f;
		__emit 0x01;
		__emit 0xe8;
		__emit 0x1c;
		__emit 0x26;
		__emit 0xb2;
		__emit 0xff;
		__emit 0x8b;
		__emit 0x0d;
		__emit 0x34;
		__emit 0x42;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x53;
		__emit 0xe8;
		__emit 0xd4;
		__emit 0xa6;
		__emit 0xb3;
		__emit 0xff;
		__emit 0x8d;
		__emit 0x44;
		__emit 0x24;
		__emit 0x2c;
		__emit 0x50;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x2c;
		__emit 0x51;
		__emit 0x8b;
		__emit 0x0d;
		__emit 0x34;
		__emit 0x42;
		__emit 0x2f;
		__emit 0x01;
		__emit 0xe8;
		__emit 0x51;
		__emit 0x96;
		__emit 0xb4;
		__emit 0xff;
		__emit 0x8b;
		__emit 0x0d;
		__emit 0x70;
		__emit 0x12;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x8b;
		__emit 0x11;
		__emit 0x8b;
		__emit 0x1e;
		__emit 0x8b;
		__emit 0x7e;
		__emit 0x04;
		__emit 0xff;
		__emit 0x52;
		__emit 0x2c;
		__emit 0x8b;
		__emit 0x0e;
		__emit 0x03;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x28;
		__emit 0x3b;
		__emit 0xc8;
		__emit 0x76;
		__emit 0x11;
		__emit 0x8b;
		__emit 0x0d;
		__emit 0x70;
		__emit 0x12;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x8b;
		__emit 0x11;
		__emit 0xff;
		__emit 0x52;
		__emit 0x2c;
		__emit 0x8b;
		__emit 0xd8;
		__emit 0x2b;
		__emit 0x5c;
		__emit 0x24;
		__emit 0x28;
		__emit 0x8b;
		__emit 0x0d;
		__emit 0x70;
		__emit 0x12;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x8b;
		__emit 0x01;
		__emit 0xff;
		__emit 0x50;
		__emit 0x30;
		__emit 0x8b;
		__emit 0x4e;
		__emit 0x04;
		__emit 0x03;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x2c;
		__emit 0x3b;
		__emit 0xc8;
		__emit 0x76;
		__emit 0x11;
		__emit 0x8b;
		__emit 0x0d;
		__emit 0x70;
		__emit 0x12;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x8b;
		__emit 0x11;
		__emit 0xff;
		__emit 0x52;
		__emit 0x30;
		__emit 0x8b;
		__emit 0xf8;
		__emit 0x2b;
		__emit 0x7c;
		__emit 0x24;
		__emit 0x2c;
		__emit 0x8b;
		__emit 0x0d;
		__emit 0x34;
		__emit 0x42;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x57;
		__emit 0x53;
		__emit 0xe8;
		__emit 0xd3;
		__emit 0xbb;
		__emit 0xb2;
		__emit 0xff;
		__emit 0x6a;
		__emit 0x0c;
		__emit 0xe8;
		__emit 0x5f;
		__emit 0x46;
		__emit 0x39;
		__emit 0x00;
		__emit 0x83;
		__emit 0xc4;
		__emit 0x04;
		__emit 0x85;
		__emit 0xc0;
		__emit 0x74;
		__emit 0x0a;
		__emit 0xc7;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x8b;
		__emit 0xf0;
		__emit 0xeb;
		__emit 0x02;
		__emit 0x33;
		__emit 0xf6;
		__emit 0x8b;
		__emit 0x44;
		__emit 0x24;
		__emit 0x20;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x14;
		__emit 0x51;
		__emit 0x8b;
		__emit 0xce;
		__emit 0x89;
		__emit 0x46;
		__emit 0x04;
		__emit 0xe8;
		__emit 0x59;
		__emit 0xb7;
		__emit 0x39;
		__emit 0x00;
		__emit 0x8b;
		__emit 0x46;
		__emit 0x04;
		__emit 0x8b;
		__emit 0x54;
		__emit 0x24;
		__emit 0x10;
		__emit 0x50;
		__emit 0x51;
		__emit 0x8b;
		__emit 0xcc;
		__emit 0x89;
		__emit 0x64;
		__emit 0x24;
		__emit 0x18;
		__emit 0x56;
		__emit 0x89;
		__emit 0x56;
		__emit 0x08;
		__emit 0xe8;
		__emit 0xa0;
		__emit 0x3d;
		__emit 0xb5;
		__emit 0xff;
		__emit 0x55;
		__emit 0xe8;
		__emit 0x2f;
		__emit 0x74;
		__emit 0xb2;
		__emit 0xff;
		__emit 0x8b;
		__emit 0x0d;
		__emit 0x34;
		__emit 0x42;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x83;
		__emit 0xc4;
		__emit 0x0c;
		__emit 0x56;
		__emit 0xe8;
		__emit 0x45;
		__emit 0x55;
		__emit 0xb1;
		__emit 0xff;
		__emit 0x8b;
		__emit 0x0d;
		__emit 0x40;
		__emit 0x1b;
		__emit 0x2f;
		__emit 0x01;
		__emit 0xa1;
		__emit 0x34;
		__emit 0x42;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x8b;
		__emit 0x11;
		__emit 0x50;
		__emit 0xff;
		__emit 0x92;
		__emit 0xbc;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x14;
		__emit 0xc7;
		__emit 0x84;
		__emit 0x24;
		__emit 0x10;
		__emit 0x03;
		__emit 0x00;
		__emit 0x00;
		__emit 0xff;
		__emit 0xff;
		__emit 0xff;
		__emit 0xff;
		__emit 0xe8;
		__emit 0x84;
		__emit 0xa8;
		__emit 0x39;
		__emit 0x00;
		__emit 0xb8;
		__emit 0x01;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0xeb;
		__emit 0x02;
		__emit 0x33;
		__emit 0xc0;
		__emit 0x8b;
		__emit 0x8c;
		__emit 0x24;
		__emit 0x08;
		__emit 0x03;
		__emit 0x00;
		__emit 0x00;
		__emit 0x5f;
		__emit 0x5e;
		__emit 0x5d;
		__emit 0x64;
		__emit 0x89;
		__emit 0x0d;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x5b;
		__emit 0x81;
		__emit 0xc4;
		__emit 0x04;
		__emit 0x03;
		__emit 0x00;
		__emit 0x00;
		__emit 0xc3;
	}
}

static void insertChat( BuddyMessage msg )
{
	if (buddyControls.listboxChat)
	{
		BuddyInfoMap *m = TheGameSpyInfo->getBuddyMap();
		BuddyInfoMap::iterator senderIt = m->find(msg.m_senderID);
		BuddyInfoMap::iterator recipientIt = m->find(msg.m_recipientID);
		Bool localSender = (msg.m_senderID == TheGameSpyInfo->getLocalProfileID());
		UnicodeString s;
		//UnicodeString timeStr = UnicodeString(_wctime( (const time_t *)&msg.m_timestamp ));
		UnicodeString timeStr;
		if (localSender /*&& recipientIt != m->end()*/)
		{
			s.format(L"[%hs -> %hs] %s", TheGameSpyInfo->getLocalBaseName().str(), msg.m_recipientNick.str(), msg.m_message.str());
			Int index = GadgetListBoxAddEntryText( buddyControls.listboxChat, s, GameSpyColor[GSCOLOR_PLAYER_SELF], -1, -1 );
			GadgetListBoxAddEntryText( buddyControls.listboxChat, timeStr, GameSpyColor[GSCOLOR_PLAYER_SELF], index, 1);
		}
		else if (!localSender /*&& senderIt != m->end()*/)
		{
			if (!msg.m_senderID)
			{
				s = msg.m_message;
				Int index = GadgetListBoxAddEntryText( buddyControls.listboxChat, s, GameSpyColor[GSCOLOR_DEFAULT], -1, -1 );
				GadgetListBoxAddEntryText( buddyControls.listboxChat, timeStr, GameSpyColor[GSCOLOR_DEFAULT], index, 1);
			}
			else
			{
				s.format(L"[%hs] %s", msg.m_senderNick.str(), msg.m_message.str());
				Int index = GadgetListBoxAddEntryText( buddyControls.listboxChat, s, GameSpyColor[GSCOLOR_PLAYER_BUDDY], -1, -1 );
				GadgetListBoxAddEntryText( buddyControls.listboxChat, timeStr, GameSpyColor[GSCOLOR_PLAYER_BUDDY], index, 1);
			}
		}
	}
}

void updateBuddyInfo( void )
{
	if (!TheGameSpyBuddyMessageQueue->isConnected())
	{
		GadgetListBoxReset(buddyControls.listboxBuddies);
		return;
	}

	if (!buddyControls.isInit)
		return;

	int selected;
	GPProfile selectedProfile = 0;
	int visiblePos = GadgetListBoxGetTopVisibleEntry(buddyControls.listboxBuddies);

	GadgetListBoxGetSelected(buddyControls.listboxBuddies, &selected);
	if (selected >= 0)
		selectedProfile = (GPProfile)GadgetListBoxGetItemData(buddyControls.listboxBuddies, selected);

	selected = -1;
	GadgetListBoxReset(buddyControls.listboxBuddies);

	// Add buddies
	BuddyInfoMap *buddies = TheGameSpyInfo->getBuddyMap();
	BuddyInfoMap::iterator bIt;
	for (bIt = buddies->begin(); bIt != buddies->end(); ++bIt)
	{
		BuddyInfo info = bIt->second;
		GPProfile profileID = bIt->first;

		// insert name into box
		UnicodeString formatStr;
		formatStr.translate(info.m_name.str());//, info.m_status, info.m_statusString.str(), info.m_locationString.str());
		Color nameColor = (TheGameSpyInfo->isSavedIgnored(profileID)) ?
			GameSpyColor[GSCOLOR_PLAYER_IGNORED] : GameSpyColor[GSCOLOR_PLAYER_BUDDY];
		int index = GadgetListBoxAddEntryText(buddyControls.listboxBuddies, formatStr, nameColor, -1, -1);

		// insert status into box
		AsciiString marker;
		marker.format("Buddy:%ls", info.m_statusString.str());
		if (!info.m_statusString.compareNoCase(L"Offline") ||
			!info.m_statusString.compareNoCase(L"Online") ||
			!info.m_statusString.compareNoCase(L"Matching"))
		{
			formatStr = TheGameText->fetch(marker);
		}
		else if (!info.m_statusString.compareNoCase(L"Staging") ||
			!info.m_statusString.compareNoCase(L"Loading") ||
			!info.m_statusString.compareNoCase(L"Playing"))
		{
			formatStr.format(TheGameText->fetch(marker), info.m_locationString.str());
		}
		else if (!info.m_statusString.compareNoCase(L"Chatting"))
		{
			UnicodeString roomName;
			GroupRoomMap::iterator gIt = TheGameSpyInfo->getGroupRoomList()->find( _wtoi(info.m_locationString.str()) );
			if (gIt != TheGameSpyInfo->getGroupRoomList()->end())
			{
				AsciiString s;
				s.format("GUI:%s", gIt->second.m_name.str());
				roomName = TheGameText->fetch(s);
			}
			formatStr.format(TheGameText->fetch(marker), roomName.str());
		}
		else
		{
			formatStr = info.m_statusString;
		}
		GadgetListBoxAddEntryText(buddyControls.listboxBuddies, formatStr, GameSpyColor[GSCOLOR_DEFAULT], index, 1);
		GadgetListBoxSetItemData(buddyControls.listboxBuddies, (void *)(profileID), index, 0 );
		GadgetListBoxSetItemData(buddyControls.listboxBuddies, (void *)(ITEM_BUDDY), index, 1 );

		if (profileID == selectedProfile)
			selected = index;
	}

	// add requests
	buddies = TheGameSpyInfo->getBuddyRequestMap();
	for (bIt = buddies->begin(); bIt != buddies->end(); ++bIt)
	{
		BuddyInfo info = bIt->second;
		GPProfile profileID = bIt->first;

		// insert name into box
		UnicodeString formatStr;
		formatStr.translate(info.m_name.str());
		int index = GadgetListBoxAddEntryText(buddyControls.listboxBuddies, formatStr, GameSpyColor[GSCOLOR_DEFAULT], -1, -1);
		GadgetListBoxSetItemData(buddyControls.listboxBuddies, (void *)(profileID), index, 0 );

		// insert status into box
		formatStr = TheGameText->fetch("GUI:BuddyAddReq");
		GadgetListBoxAddEntryText(buddyControls.listboxBuddies, formatStr, GameSpyColor[GSCOLOR_DEFAULT], index, 1);
		GadgetListBoxSetItemData(buddyControls.listboxBuddies, (void *)(ITEM_REQUEST), index, 1 );

		if (profileID == selectedProfile)
			selected = index;
	}


	// select the same guy
	if (selected >= 0)
	{
		GadgetListBoxSetSelected(buddyControls.listboxBuddies, selected);
	}

	// view the same spot
	GadgetListBoxSetTopVisibleEntry(buddyControls.listboxBuddies, visiblePos);
}

void HandleBuddyResponses( void )
{
	if (TheGameSpyBuddyMessageQueue)
	{
		BuddyResponse resp;
		if (TheGameSpyBuddyMessageQueue->getResponse( resp ))
		{
			switch (resp.buddyResponseType)
			{
			case BuddyResponse::BUDDYRESPONSE_LOGIN:
				{
					deleteNotificationBox();
				}
				break;
			case BuddyResponse::BUDDYRESPONSE_DISCONNECT:
				{
					lastNotificationWasStatus = FALSE;
					numOnlineInNotification = 0;
					showNotificationBox(AsciiString::TheEmptyString, TheGameText->fetch("Buddy:MessageDisconnected"));
				}
				break;
			case BuddyResponse::BUDDYRESPONSE_MESSAGE:
				{
					if ( !wcscmp(resp.arg.message.text, L"I have authorized your request to add me to your list") )
						break;

					if (TheGameSpyInfo->isSavedIgnored(resp.profile))
					{
						//DEBUG_CRASH(("Player is ignored!\n"));
						break; // no buddy messages from ignored people
					}

					// save message for future incarnations of the buddy window
					BuddyMessageList *messages = TheGameSpyInfo->getBuddyMessages();
					BuddyMessage message;
					message.m_timestamp = resp.arg.message.date;
					message.m_senderID = resp.profile;
					message.m_recipientID = TheGameSpyInfo->getLocalProfileID();
					message.m_recipientNick = TheGameSpyInfo->getLocalBaseName();
					message.m_message = resp.arg.message.text;
					// insert status into box
					BuddyInfoMap *m = TheGameSpyInfo->getBuddyMap();
					BuddyInfoMap::iterator senderIt = m->find(message.m_senderID);
					AsciiString nick;
					if (senderIt != m->end())
						nick = senderIt->second.m_name.str();
					else
						nick = resp.arg.message.nick;
					message.m_senderNick = nick;
					messages->push_back(message);

					DEBUG_LOG(("Inserting buddy chat from '%s'/'%s'\n", nick.str(), resp.arg.message.nick));

					// put message on screen
					insertChat(message);
					
					// play audio notification
					AudioEventRTS buddyMsgAudio("GUIMessageReceived");
					if( TheAudio )
					{
						TheAudio->addAudioEvent( &buddyMsgAudio );
					}  // end if

					UnicodeString snippet = message.m_message;
					while (snippet.getLength() > 11)
					{
						snippet.removeLastChar();
					}
					UnicodeString s;
					s.format(TheGameText->fetch("Buddy:MessageNotification"), nick.str(), snippet.str());
					lastNotificationWasStatus = FALSE;
					numOnlineInNotification = 0;
					showNotificationBox(AsciiString::TheEmptyString, s);
				}
				break;
			case BuddyResponse::BUDDYRESPONSE_REQUEST:
				{
					// save request for future incarnations of the buddy window
					BuddyInfoMap *m = TheGameSpyInfo->getBuddyRequestMap();
					BuddyInfo info;
					info.m_countryCode = resp.arg.request.countrycode;
					info.m_email = resp.arg.request.email;
					info.m_name = resp.arg.request.nick;
					info.m_id = resp.profile;
					info.m_status = (GPEnum)0;
					info.m_statusString = resp.arg.request.text;
					(*m)[resp.profile] = info;

					// TODO: put request on screen
					updateBuddyInfo();
					// insert status into box
					lastNotificationWasStatus = FALSE;
					numOnlineInNotification = 0;
					showNotificationBox(info.m_name, TheGameText->fetch("Buddy:AddNotification"));
				}
				break;
			case BuddyResponse::BUDDYRESPONSE_STATUS:
				{
					BuddyInfoMap *m = TheGameSpyInfo->getBuddyMap();
					BuddyInfoMap::const_iterator bit = m->find(resp.profile);
					Bool seenPreviously = FALSE;
					GPEnum oldStatus = GP_OFFLINE;
					GPEnum newStatus = resp.arg.status.status;
					if (bit != m->end())
					{
						seenPreviously = TRUE;
						oldStatus = (*m)[resp.profile].m_status;
					}
					BuddyInfo info;
					info.m_countryCode = resp.arg.status.countrycode;
					info.m_email = resp.arg.status.email;
					info.m_name = resp.arg.status.nick;
					info.m_id = resp.profile;
					info.m_status = newStatus;
					info.m_statusString = UnicodeString(MultiByteToWideCharSingleLine(resp.arg.status.statusString).c_str());
					info.m_locationString = UnicodeString(MultiByteToWideCharSingleLine(resp.arg.status.location).c_str());
					(*m)[resp.profile] = info;

					updateBuddyInfo();
					PopulateLobbyPlayerListbox();
					RefreshGameListBoxes();
					if ( (newStatus == GP_OFFLINE && seenPreviously) ||
						(newStatus == GP_ONLINE && (oldStatus == GP_OFFLINE || !seenPreviously)) )
					//if (!info.m_statusString.compareNoCase(L"Offline") ||
					//!info.m_statusString.compareNoCase(L"Online"))
					{
						// insert status into box
						AsciiString marker;
						marker.format("Buddy:%lsNotification", info.m_statusString.str());

						lastNotificationWasStatus = TRUE;
						if (newStatus != GP_OFFLINE)
							++numOnlineInNotification;

						showNotificationBox(info.m_name, TheGameText->fetch(marker));
					}
					else if( newStatus == GP_RECV_GAME_INVITE && !seenPreviously)
					{
						lastNotificationWasStatus = TRUE;
						if (newStatus != GP_OFFLINE)
							++numOnlineInNotification;

						showNotificationBox(info.m_name, TheGameText->fetch("Buddy:OnlineNotification"));
					}
				}
				break;
			}
		}
	}
	else
	{
		DEBUG_CRASH(("No buddy message queue!\n"));
	}
	if(noticeLayout && timeGetTime() > noticeExpires)
	{
		deleteNotificationBox();
	}
}

void showNotificationBox( AsciiString nick, UnicodeString message)
{
//	if(!GameSpyIsOverlayOpen(GSOVERLAY_BUDDY))
//		return;
	if( !noticeLayout )
		noticeLayout = TheWindowManager->winCreateLayout( "Menus/PopupBuddyListNotification.wnd" );
	((BfmeVirtualHideLayout *)noticeLayout)->hide( FALSE );
	if (buttonNotificationID == NAMEKEY_INVALID)
	{
		buttonNotificationID = TheNameKeyGenerator->nameToKey("PopupBuddyListNotification.wnd:ButtonNotification");
	}
	GameWindow *win = TheWindowManager->winGetWindowFromId(NULL,buttonNotificationID);
	if(!win)
	{
		deleteNotificationBox();
		return;
	}

	if (lastNotificationWasStatus && numOnlineInNotification > 1)
	{
		message = TheGameText->fetch("Buddy:MultipleOnlineNotification");
	}

	if (nick.isNotEmpty())
		message.format(message, nick.str());
	GadgetButtonSetText(win, message);
	//GadgetStaticTextSetText(win, message);
	noticeExpires = timeGetTime() + NOTIFICATION_EXPIRES;
	noticeLayout->bringForward();

	AudioEventRTS buttonClick("GUICommunicatorIncoming");

	if( TheAudio )
	{
		TheAudio->addAudioEvent( &buttonClick );
	}  // end if

}

void deleteNotificationBox( void )
{
	lastNotificationWasStatus = FALSE;
	numOnlineInNotification = 0;
	if(noticeLayout)
	{
		noticeLayout->destroyWindows();
		noticeLayout->deleteInstance();
		noticeLayout = NULL;
	}
}

void PopulateOldBuddyMessages(void)
{
	// show previous messages
	BuddyMessageList *messages = TheGameSpyInfo->getBuddyMessages();
	for (BuddyMessageList::iterator mIt = messages->begin(); mIt != messages->end(); ++mIt)
	{
		BuddyMessage message = *mIt;
		insertChat(message);
	}
}

//-------------------------------------------------------------------------------------------------
/** Initialize the WOL Buddy Overlay */
//-------------------------------------------------------------------------------------------------
// ?WOLBuddyOverlayInit@@YAXPAVWindowLayout@@PAX@Z matched 1263 bytes (Open-BFME5)
__declspec(naked) void WOLBuddyOverlayInit(WindowLayout *, void *)
{
	__asm
	{
		__emit 0x6a;
		__emit 0xff;
		__emit 0x68;
		__emit 0xa8;
		__emit 0xbe;
		__emit 0x02;
		__emit 0x01;
		__emit 0x64;
		__emit 0xa1;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x50;
		__emit 0x64;
		__emit 0x89;
		__emit 0x25;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x83;
		__emit 0xec;
		__emit 0x08;
		__emit 0x68;
		__emit 0x54;
		__emit 0x24;
		__emit 0x10;
		__emit 0x01;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x04;
		__emit 0xe8;
		__emit 0xba;
		__emit 0xc4;
		__emit 0x39;
		__emit 0x00;
		__emit 0x8b;
		__emit 0x04;
		__emit 0x24;
		__emit 0x85;
		__emit 0xc0;
		__emit 0xc7;
		__emit 0x44;
		__emit 0x24;
		__emit 0x10;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x74;
		__emit 0x05;
		__emit 0x83;
		__emit 0xc0;
		__emit 0x08;
		__emit 0xeb;
		__emit 0x05;
		__emit 0xb8;
		__emit 0x8b;
		__emit 0x38;
		__emit 0x07;
		__emit 0x01;
		__emit 0x8b;
		__emit 0x0d;
		__emit 0x00;
		__emit 0xd6;
		__emit 0x2e;
		__emit 0x01;
		__emit 0x56;
		__emit 0x50;
		__emit 0xe8;
		__emit 0xab;
		__emit 0xe6;
		__emit 0xb4;
		__emit 0xff;
		__emit 0x83;
		__emit 0xce;
		__emit 0xff;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x04;
		__emit 0xa3;
		__emit 0xbc;
		__emit 0x41;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x89;
		__emit 0x74;
		__emit 0x24;
		__emit 0x14;
		__emit 0xe8;
		__emit 0xff;
		__emit 0xb1;
		__emit 0x39;
		__emit 0x00;
		__emit 0x68;
		__emit 0x2c;
		__emit 0x24;
		__emit 0x10;
		__emit 0x01;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x08;
		__emit 0xe8;
		__emit 0x71;
		__emit 0xc4;
		__emit 0x39;
		__emit 0x00;
		__emit 0x8b;
		__emit 0x44;
		__emit 0x24;
		__emit 0x04;
		__emit 0x85;
		__emit 0xc0;
		__emit 0xc7;
		__emit 0x44;
		__emit 0x24;
		__emit 0x14;
		__emit 0x01;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x74;
		__emit 0x05;
		__emit 0x83;
		__emit 0xc0;
		__emit 0x08;
		__emit 0xeb;
		__emit 0x05;
		__emit 0xb8;
		__emit 0x8b;
		__emit 0x38;
		__emit 0x07;
		__emit 0x01;
		__emit 0x8b;
		__emit 0x0d;
		__emit 0x00;
		__emit 0xd6;
		__emit 0x2e;
		__emit 0x01;
		__emit 0x50;
		__emit 0xe8;
		__emit 0x62;
		__emit 0xe6;
		__emit 0xb4;
		__emit 0xff;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x04;
		__emit 0xa3;
		__emit 0xc0;
		__emit 0x41;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x89;
		__emit 0x74;
		__emit 0x24;
		__emit 0x14;
		__emit 0xe8;
		__emit 0xb9;
		__emit 0xb1;
		__emit 0x39;
		__emit 0x00;
		__emit 0x68;
		__emit 0x08;
		__emit 0x24;
		__emit 0x10;
		__emit 0x01;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x08;
		__emit 0xe8;
		__emit 0x2b;
		__emit 0xc4;
		__emit 0x39;
		__emit 0x00;
		__emit 0x8b;
		__emit 0x44;
		__emit 0x24;
		__emit 0x04;
		__emit 0x85;
		__emit 0xc0;
		__emit 0xc7;
		__emit 0x44;
		__emit 0x24;
		__emit 0x14;
		__emit 0x02;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x74;
		__emit 0x05;
		__emit 0x83;
		__emit 0xc0;
		__emit 0x08;
		__emit 0xeb;
		__emit 0x05;
		__emit 0xb8;
		__emit 0x8b;
		__emit 0x38;
		__emit 0x07;
		__emit 0x01;
		__emit 0x8b;
		__emit 0x0d;
		__emit 0x00;
		__emit 0xd6;
		__emit 0x2e;
		__emit 0x01;
		__emit 0x50;
		__emit 0xe8;
		__emit 0x1c;
		__emit 0xe6;
		__emit 0xb4;
		__emit 0xff;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x04;
		__emit 0xa3;
		__emit 0xc4;
		__emit 0x41;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x89;
		__emit 0x74;
		__emit 0x24;
		__emit 0x14;
		__emit 0xe8;
		__emit 0x73;
		__emit 0xb1;
		__emit 0x39;
		__emit 0x00;
		__emit 0x68;
		__emit 0xe0;
		__emit 0x23;
		__emit 0x10;
		__emit 0x01;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x08;
		__emit 0xe8;
		__emit 0xe5;
		__emit 0xc3;
		__emit 0x39;
		__emit 0x00;
		__emit 0x8b;
		__emit 0x44;
		__emit 0x24;
		__emit 0x04;
		__emit 0x85;
		__emit 0xc0;
		__emit 0xc7;
		__emit 0x44;
		__emit 0x24;
		__emit 0x14;
		__emit 0x03;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x74;
		__emit 0x05;
		__emit 0x83;
		__emit 0xc0;
		__emit 0x08;
		__emit 0xeb;
		__emit 0x05;
		__emit 0xb8;
		__emit 0x8b;
		__emit 0x38;
		__emit 0x07;
		__emit 0x01;
		__emit 0x8b;
		__emit 0x0d;
		__emit 0x00;
		__emit 0xd6;
		__emit 0x2e;
		__emit 0x01;
		__emit 0x50;
		__emit 0xe8;
		__emit 0xd6;
		__emit 0xe5;
		__emit 0xb4;
		__emit 0xff;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x04;
		__emit 0xa3;
		__emit 0xc8;
		__emit 0x41;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x89;
		__emit 0x74;
		__emit 0x24;
		__emit 0x14;
		__emit 0xe8;
		__emit 0x2d;
		__emit 0xb1;
		__emit 0x39;
		__emit 0x00;
		__emit 0x68;
		__emit 0xbc;
		__emit 0x23;
		__emit 0x10;
		__emit 0x01;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x08;
		__emit 0xe8;
		__emit 0x9f;
		__emit 0xc3;
		__emit 0x39;
		__emit 0x00;
		__emit 0x8b;
		__emit 0x44;
		__emit 0x24;
		__emit 0x04;
		__emit 0x85;
		__emit 0xc0;
		__emit 0xc7;
		__emit 0x44;
		__emit 0x24;
		__emit 0x14;
		__emit 0x04;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x74;
		__emit 0x05;
		__emit 0x83;
		__emit 0xc0;
		__emit 0x08;
		__emit 0xeb;
		__emit 0x05;
		__emit 0xb8;
		__emit 0x8b;
		__emit 0x38;
		__emit 0x07;
		__emit 0x01;
		__emit 0x8b;
		__emit 0x0d;
		__emit 0x00;
		__emit 0xd6;
		__emit 0x2e;
		__emit 0x01;
		__emit 0x50;
		__emit 0xe8;
		__emit 0x90;
		__emit 0xe5;
		__emit 0xb4;
		__emit 0xff;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x04;
		__emit 0xa3;
		__emit 0xd8;
		__emit 0x41;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x89;
		__emit 0x74;
		__emit 0x24;
		__emit 0x14;
		__emit 0xe8;
		__emit 0xe7;
		__emit 0xb0;
		__emit 0x39;
		__emit 0x00;
		__emit 0x68;
		__emit 0x98;
		__emit 0x23;
		__emit 0x10;
		__emit 0x01;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x08;
		__emit 0xe8;
		__emit 0x59;
		__emit 0xc3;
		__emit 0x39;
		__emit 0x00;
		__emit 0x8b;
		__emit 0x44;
		__emit 0x24;
		__emit 0x04;
		__emit 0x85;
		__emit 0xc0;
		__emit 0xc7;
		__emit 0x44;
		__emit 0x24;
		__emit 0x14;
		__emit 0x05;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x74;
		__emit 0x05;
		__emit 0x83;
		__emit 0xc0;
		__emit 0x08;
		__emit 0xeb;
		__emit 0x05;
		__emit 0xb8;
		__emit 0x8b;
		__emit 0x38;
		__emit 0x07;
		__emit 0x01;
		__emit 0x8b;
		__emit 0x0d;
		__emit 0x00;
		__emit 0xd6;
		__emit 0x2e;
		__emit 0x01;
		__emit 0x50;
		__emit 0xe8;
		__emit 0x4a;
		__emit 0xe5;
		__emit 0xb4;
		__emit 0xff;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x04;
		__emit 0xa3;
		__emit 0xdc;
		__emit 0x41;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x89;
		__emit 0x74;
		__emit 0x24;
		__emit 0x14;
		__emit 0xe8;
		__emit 0xa1;
		__emit 0xb0;
		__emit 0x39;
		__emit 0x00;
		__emit 0x68;
		__emit 0x68;
		__emit 0x23;
		__emit 0x10;
		__emit 0x01;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x08;
		__emit 0xe8;
		__emit 0x13;
		__emit 0xc3;
		__emit 0x39;
		__emit 0x00;
		__emit 0x8b;
		__emit 0x44;
		__emit 0x24;
		__emit 0x04;
		__emit 0x85;
		__emit 0xc0;
		__emit 0xc7;
		__emit 0x44;
		__emit 0x24;
		__emit 0x14;
		__emit 0x06;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x74;
		__emit 0x05;
		__emit 0x83;
		__emit 0xc0;
		__emit 0x08;
		__emit 0xeb;
		__emit 0x05;
		__emit 0xb8;
		__emit 0x8b;
		__emit 0x38;
		__emit 0x07;
		__emit 0x01;
		__emit 0x8b;
		__emit 0x0d;
		__emit 0x00;
		__emit 0xd6;
		__emit 0x2e;
		__emit 0x01;
		__emit 0x50;
		__emit 0xe8;
		__emit 0x04;
		__emit 0xe5;
		__emit 0xb4;
		__emit 0xff;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x04;
		__emit 0xa3;
		__emit 0xe0;
		__emit 0x41;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x89;
		__emit 0x74;
		__emit 0x24;
		__emit 0x14;
		__emit 0xe8;
		__emit 0x5b;
		__emit 0xb0;
		__emit 0x39;
		__emit 0x00;
		__emit 0x68;
		__emit 0x38;
		__emit 0x23;
		__emit 0x10;
		__emit 0x01;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x08;
		__emit 0xe8;
		__emit 0xcd;
		__emit 0xc2;
		__emit 0x39;
		__emit 0x00;
		__emit 0x8b;
		__emit 0x44;
		__emit 0x24;
		__emit 0x04;
		__emit 0x85;
		__emit 0xc0;
		__emit 0xc7;
		__emit 0x44;
		__emit 0x24;
		__emit 0x14;
		__emit 0x07;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x74;
		__emit 0x05;
		__emit 0x83;
		__emit 0xc0;
		__emit 0x08;
		__emit 0xeb;
		__emit 0x05;
		__emit 0xb8;
		__emit 0x8b;
		__emit 0x38;
		__emit 0x07;
		__emit 0x01;
		__emit 0x8b;
		__emit 0x0d;
		__emit 0x00;
		__emit 0xd6;
		__emit 0x2e;
		__emit 0x01;
		__emit 0x50;
		__emit 0xe8;
		__emit 0xbe;
		__emit 0xe4;
		__emit 0xb4;
		__emit 0xff;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x04;
		__emit 0xa3;
		__emit 0xe4;
		__emit 0x41;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x89;
		__emit 0x74;
		__emit 0x24;
		__emit 0x14;
		__emit 0xe8;
		__emit 0x15;
		__emit 0xb0;
		__emit 0x39;
		__emit 0x00;
		__emit 0x68;
		__emit 0x10;
		__emit 0x23;
		__emit 0x10;
		__emit 0x01;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x08;
		__emit 0xe8;
		__emit 0x87;
		__emit 0xc2;
		__emit 0x39;
		__emit 0x00;
		__emit 0x8b;
		__emit 0x44;
		__emit 0x24;
		__emit 0x04;
		__emit 0x85;
		__emit 0xc0;
		__emit 0xc7;
		__emit 0x44;
		__emit 0x24;
		__emit 0x14;
		__emit 0x08;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x74;
		__emit 0x05;
		__emit 0x83;
		__emit 0xc0;
		__emit 0x08;
		__emit 0xeb;
		__emit 0x05;
		__emit 0xb8;
		__emit 0x8b;
		__emit 0x38;
		__emit 0x07;
		__emit 0x01;
		__emit 0x8b;
		__emit 0x0d;
		__emit 0x00;
		__emit 0xd6;
		__emit 0x2e;
		__emit 0x01;
		__emit 0x50;
		__emit 0xe8;
		__emit 0x78;
		__emit 0xe4;
		__emit 0xb4;
		__emit 0xff;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x04;
		__emit 0xa3;
		__emit 0xe8;
		__emit 0x41;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x89;
		__emit 0x74;
		__emit 0x24;
		__emit 0x14;
		__emit 0xe8;
		__emit 0xcf;
		__emit 0xaf;
		__emit 0x39;
		__emit 0x00;
		__emit 0x68;
		__emit 0xe8;
		__emit 0x22;
		__emit 0x10;
		__emit 0x01;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x08;
		__emit 0xe8;
		__emit 0x41;
		__emit 0xc2;
		__emit 0x39;
		__emit 0x00;
		__emit 0x8b;
		__emit 0x44;
		__emit 0x24;
		__emit 0x04;
		__emit 0x85;
		__emit 0xc0;
		__emit 0xc7;
		__emit 0x44;
		__emit 0x24;
		__emit 0x14;
		__emit 0x09;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x74;
		__emit 0x05;
		__emit 0x83;
		__emit 0xc0;
		__emit 0x08;
		__emit 0xeb;
		__emit 0x05;
		__emit 0xb8;
		__emit 0x8b;
		__emit 0x38;
		__emit 0x07;
		__emit 0x01;
		__emit 0x8b;
		__emit 0x0d;
		__emit 0x00;
		__emit 0xd6;
		__emit 0x2e;
		__emit 0x01;
		__emit 0x50;
		__emit 0xe8;
		__emit 0x32;
		__emit 0xe4;
		__emit 0xb4;
		__emit 0xff;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x04;
		__emit 0xa3;
		__emit 0xec;
		__emit 0x41;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x89;
		__emit 0x74;
		__emit 0x24;
		__emit 0x14;
		__emit 0xe8;
		__emit 0x89;
		__emit 0xaf;
		__emit 0x39;
		__emit 0x00;
		__emit 0x68;
		__emit 0xc0;
		__emit 0x22;
		__emit 0x10;
		__emit 0x01;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x0c;
		__emit 0xe8;
		__emit 0xfb;
		__emit 0xc1;
		__emit 0x39;
		__emit 0x00;
		__emit 0x8b;
		__emit 0x44;
		__emit 0x24;
		__emit 0x08;
		__emit 0x85;
		__emit 0xc0;
		__emit 0xc7;
		__emit 0x44;
		__emit 0x24;
		__emit 0x14;
		__emit 0x0a;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x74;
		__emit 0x05;
		__emit 0x83;
		__emit 0xc0;
		__emit 0x08;
		__emit 0xeb;
		__emit 0x05;
		__emit 0xb8;
		__emit 0x8b;
		__emit 0x38;
		__emit 0x07;
		__emit 0x01;
		__emit 0x8b;
		__emit 0x0d;
		__emit 0x00;
		__emit 0xd6;
		__emit 0x2e;
		__emit 0x01;
		__emit 0x50;
		__emit 0xe8;
		__emit 0xec;
		__emit 0xe3;
		__emit 0xb4;
		__emit 0xff;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x08;
		__emit 0xa3;
		__emit 0xf0;
		__emit 0x41;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x89;
		__emit 0x74;
		__emit 0x24;
		__emit 0x14;
		__emit 0xe8;
		__emit 0x43;
		__emit 0xaf;
		__emit 0x39;
		__emit 0x00;
		__emit 0x8b;
		__emit 0x15;
		__emit 0xbc;
		__emit 0x41;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x8b;
		__emit 0x0d;
		__emit 0x40;
		__emit 0x1b;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x8b;
		__emit 0x01;
		__emit 0x52;
		__emit 0x6a;
		__emit 0x00;
		__emit 0xff;
		__emit 0x90;
		__emit 0xdc;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x8b;
		__emit 0x35;
		__emit 0xc0;
		__emit 0x41;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x8b;
		__emit 0x0d;
		__emit 0x40;
		__emit 0x1b;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x8b;
		__emit 0x11;
		__emit 0x56;
		__emit 0x50;
		__emit 0xa3;
		__emit 0xf8;
		__emit 0x41;
		__emit 0x2f;
		__emit 0x01;
		__emit 0xff;
		__emit 0x92;
		__emit 0xdc;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x8b;
		__emit 0x15;
		__emit 0xc4;
		__emit 0x41;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x8b;
		__emit 0x0d;
		__emit 0x40;
		__emit 0x1b;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x52;
		__emit 0x8b;
		__emit 0x15;
		__emit 0xf8;
		__emit 0x41;
		__emit 0x2f;
		__emit 0x01;
		__emit 0xa3;
		__emit 0xfc;
		__emit 0x41;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x8b;
		__emit 0x01;
		__emit 0x52;
		__emit 0xff;
		__emit 0x90;
		__emit 0xdc;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x8b;
		__emit 0x15;
		__emit 0xc8;
		__emit 0x41;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x8b;
		__emit 0x0d;
		__emit 0x40;
		__emit 0x1b;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x52;
		__emit 0x8b;
		__emit 0x15;
		__emit 0xf8;
		__emit 0x41;
		__emit 0x2f;
		__emit 0x01;
		__emit 0xa3;
		__emit 0x00;
		__emit 0x42;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x8b;
		__emit 0x01;
		__emit 0x52;
		__emit 0xff;
		__emit 0x90;
		__emit 0xdc;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x8b;
		__emit 0x15;
		__emit 0xd8;
		__emit 0x41;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x8b;
		__emit 0x0d;
		__emit 0x40;
		__emit 0x1b;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x52;
		__emit 0x8b;
		__emit 0x15;
		__emit 0xf8;
		__emit 0x41;
		__emit 0x2f;
		__emit 0x01;
		__emit 0xa3;
		__emit 0x04;
		__emit 0x42;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x8b;
		__emit 0x01;
		__emit 0x52;
		__emit 0xff;
		__emit 0x90;
		__emit 0xdc;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x8b;
		__emit 0x15;
		__emit 0xdc;
		__emit 0x41;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x8b;
		__emit 0x0d;
		__emit 0x40;
		__emit 0x1b;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x52;
		__emit 0x8b;
		__emit 0x15;
		__emit 0xf8;
		__emit 0x41;
		__emit 0x2f;
		__emit 0x01;
		__emit 0xa3;
		__emit 0x14;
		__emit 0x42;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x8b;
		__emit 0x01;
		__emit 0x52;
		__emit 0xff;
		__emit 0x90;
		__emit 0xdc;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x8b;
		__emit 0x15;
		__emit 0xe0;
		__emit 0x41;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x8b;
		__emit 0x0d;
		__emit 0x40;
		__emit 0x1b;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x52;
		__emit 0x8b;
		__emit 0x15;
		__emit 0xf8;
		__emit 0x41;
		__emit 0x2f;
		__emit 0x01;
		__emit 0xa3;
		__emit 0x18;
		__emit 0x42;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x8b;
		__emit 0x01;
		__emit 0x52;
		__emit 0xff;
		__emit 0x90;
		__emit 0xdc;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x8b;
		__emit 0x15;
		__emit 0xe4;
		__emit 0x41;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x8b;
		__emit 0x0d;
		__emit 0x40;
		__emit 0x1b;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x52;
		__emit 0x8b;
		__emit 0x15;
		__emit 0xf8;
		__emit 0x41;
		__emit 0x2f;
		__emit 0x01;
		__emit 0xa3;
		__emit 0x1c;
		__emit 0x42;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x8b;
		__emit 0x01;
		__emit 0x52;
		__emit 0xff;
		__emit 0x90;
		__emit 0xdc;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x8b;
		__emit 0x15;
		__emit 0xe8;
		__emit 0x41;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x8b;
		__emit 0x0d;
		__emit 0x40;
		__emit 0x1b;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x52;
		__emit 0x8b;
		__emit 0x15;
		__emit 0xf8;
		__emit 0x41;
		__emit 0x2f;
		__emit 0x01;
		__emit 0xa3;
		__emit 0x20;
		__emit 0x42;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x8b;
		__emit 0x01;
		__emit 0x52;
		__emit 0xff;
		__emit 0x90;
		__emit 0xdc;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x8b;
		__emit 0x0d;
		__emit 0x40;
		__emit 0x1b;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x8b;
		__emit 0x15;
		__emit 0xec;
		__emit 0x41;
		__emit 0x2f;
		__emit 0x01;
		__emit 0xa3;
		__emit 0x24;
		__emit 0x42;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x8b;
		__emit 0x01;
		__emit 0x52;
		__emit 0x8b;
		__emit 0x15;
		__emit 0xf8;
		__emit 0x41;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x52;
		__emit 0xff;
		__emit 0x90;
		__emit 0xdc;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x8b;
		__emit 0x15;
		__emit 0xf0;
		__emit 0x41;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x8b;
		__emit 0x0d;
		__emit 0x40;
		__emit 0x1b;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x52;
		__emit 0x8b;
		__emit 0x15;
		__emit 0xf8;
		__emit 0x41;
		__emit 0x2f;
		__emit 0x01;
		__emit 0xa3;
		__emit 0x28;
		__emit 0x42;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x8b;
		__emit 0x01;
		__emit 0x52;
		__emit 0xff;
		__emit 0x90;
		__emit 0xdc;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x6a;
		__emit 0x00;
		__emit 0xa3;
		__emit 0x2c;
		__emit 0x42;
		__emit 0x2f;
		__emit 0x01;
		__emit 0xe8;
		__emit 0x33;
		__emit 0x29;
		__emit 0xb3;
		__emit 0xff;
		__emit 0xa1;
		__emit 0x1c;
		__emit 0x42;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x6a;
		__emit 0x00;
		__emit 0x50;
		__emit 0xe8;
		__emit 0xc5;
		__emit 0x79;
		__emit 0xb4;
		__emit 0xff;
		__emit 0x8b;
		__emit 0x0d;
		__emit 0x24;
		__emit 0x42;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x83;
		__emit 0xc4;
		__emit 0x0c;
		__emit 0x6a;
		__emit 0x00;
		__emit 0xe8;
		__emit 0xa9;
		__emit 0xb3;
		__emit 0xb3;
		__emit 0xff;
		__emit 0x8b;
		__emit 0x0d;
		__emit 0x28;
		__emit 0x42;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x6a;
		__emit 0x01;
		__emit 0xe8;
		__emit 0x9c;
		__emit 0xb3;
		__emit 0xb3;
		__emit 0xff;
		__emit 0xe8;
		__emit 0x77;
		__emit 0x40;
		__emit 0xb5;
		__emit 0xff;
		__emit 0x8b;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x1c;
		__emit 0x8b;
		__emit 0x11;
		__emit 0x6a;
		__emit 0x00;
		__emit 0xff;
		__emit 0x52;
		__emit 0x10;
		__emit 0x8b;
		__emit 0x0d;
		__emit 0x40;
		__emit 0x1b;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x8b;
		__emit 0x15;
		__emit 0xf8;
		__emit 0x41;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x8b;
		__emit 0x01;
		__emit 0x52;
		__emit 0xff;
		__emit 0x90;
		__emit 0xb0;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0xc6;
		__emit 0x05;
		__emit 0x30;
		__emit 0x42;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x01;
		__emit 0xe8;
		__emit 0xdc;
		__emit 0x88;
		__emit 0xb3;
		__emit 0xff;
		__emit 0x8b;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x0c;
		__emit 0x5e;
		__emit 0x64;
		__emit 0x89;
		__emit 0x0d;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x83;
		__emit 0xc4;
		__emit 0x14;
		__emit 0xc3;
	}
}

//-------------------------------------------------------------------------------------------------
/** WOL Buddy Overlay shutdown method */
//-------------------------------------------------------------------------------------------------
void WOLBuddyOverlayShutdown( WindowLayout *layout, void *userData )
{
	listboxIgnore = NULL;

	// hide menu
	((BfmeVirtualHideLayout *)layout)->hide( TRUE );

	// our shutdown is complete
	//TheShell->shutdownComplete( layout );

	isOverlayActive = false;

	InitBuddyControls(BUDDY_RESETALL_CRAP);

}  // WOLBuddyOverlayShutdown


//-------------------------------------------------------------------------------------------------
/** WOL Buddy Overlay update method */
//-------------------------------------------------------------------------------------------------
void WOLBuddyOverlayUpdate( WindowLayout * layout, void *userData)
{
	if (!TheGameSpyBuddyMessageQueue || !TheGameSpyBuddyMessageQueue->isConnected())
		GameSpyCloseOverlay(GSOVERLAY_BUDDY);
}// WOLBuddyOverlayUpdate

//-------------------------------------------------------------------------------------------------
/** WOL Buddy Overlay input callback */
//-------------------------------------------------------------------------------------------------
WindowMsgHandledType WOLBuddyOverlayInput( GameWindow *window, UnsignedInt msg,
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
						TheWindowManager->winSendSystemMsg( window, GBM_SELECTED, 
																							(WindowMsgData)buttonHide, buttonHideID );

					}  // end if

					// don't let key fall through anywhere else
					return MSG_HANDLED;

				}  // end escape

			}  // end switch( key )

		}  // end char

	}  // end switch( msg )

	return MSG_IGNORED;
}// WOLBuddyOverlayInput

//-------------------------------------------------------------------------------------------------
/** WOL Buddy Overlay window system callback */
//-------------------------------------------------------------------------------------------------
WindowMsgHandledType WOLBuddyOverlaySystem( GameWindow *window, UnsignedInt msg, 
														 WindowMsgData mData1, WindowMsgData mData2 )
{
	UnicodeString txtInput;
	if(BuddyControlSystem(window, msg, mData1, mData2) == MSG_HANDLED)
	{
		return MSG_HANDLED;
	}
	switch( msg )
	{
		
		
		case GWM_CREATE:
			{
				
				break;
			} // case GWM_DESTROY:

		case GWM_DESTROY:
			{
				break;
			} // case GWM_DESTROY:

		case GWM_INPUT_FOCUS:
			{	
				// if we're givin the opportunity to take the keyboard focus we must say we want it
				if( mData1 == TRUE )
					*(Bool *)mData2 = TRUE;

				return MSG_HANDLED;
			}//case GWM_INPUT_FOCUS:
		case GLM_RIGHT_CLICKED:
			{
				GameWindow *control = (GameWindow *)mData1;
				Int controlID = control->winGetWindowId();

				if( controlID == listboxIgnoreID ) 
				{
					RightClickStruct *rc = (RightClickStruct *)mData2;
					WindowLayout *rcLayout;
					if(rc->pos < 0)
						break;

					Bool isBuddy = false, isRequest = false;
					GPProfile profileID = (GPProfile)GadgetListBoxGetItemData(control, rc->pos);
					UnicodeString nick = GadgetListBoxGetText(control, rc->pos);
					BuddyInfoMap *buddies = TheGameSpyInfo->getBuddyMap();
					BuddyInfoMap::iterator bIt;
					bIt = buddies->find(profileID);
					if (bIt != buddies->end())
					{
						isBuddy = true;
					}
					else
					{
						buddies = TheGameSpyInfo->getBuddyRequestMap();
						bIt = buddies->find(profileID);
						if (bIt != buddies->end())
						{
							isRequest = true;
						}
						else
						{
							// neither buddy nor request
							//break;
						}
					}

					GadgetListBoxSetSelected(control, rc->pos);
					if (isBuddy)
						rcLayout = TheWindowManager->winCreateLayout(AsciiString("Menus/RCBuddiesMenu.wnd"));
					else if (isRequest)
						rcLayout = TheWindowManager->winCreateLayout(AsciiString("Menus/RCBuddyRequestMenu.wnd"));
					else
						rcLayout = TheWindowManager->winCreateLayout(AsciiString("Menus/RCNonBuddiesMenu.wnd"));
					rcMenu = rcLayout->getFirstWindow();
					rcMenu->winGetLayout()->runInit();
					rcMenu->winBringToTop();
					rcMenu->winHide(FALSE);
					
					

					rcMenu->winSetPosition(rc->mouseX, rc->mouseY);
					GameSpyRCMenuData *rcData = NEW GameSpyRCMenuData;
					rcData->m_id = profileID;
					rcData->m_nick.translate(nick);
					rcData->m_itemType = (isBuddy)?ITEM_BUDDY:((isRequest)?ITEM_REQUEST:ITEM_NONBUDDY);
					setUnignoreText(rcLayout, rcData->m_nick, rcData->m_id);
					rcMenu->winSetUserData((void *)rcData);
					TheWindowManager->winSetLoneWindow(rcMenu);
				}
				break;
			}
		case GBM_SELECTED:
			{
				GameWindow *control = (GameWindow *)mData1;
				Int controlID = control->winGetWindowId();

				if (controlID == buttonHideID)
				{
					GameSpyCloseOverlay( GSOVERLAY_BUDDY );
				}
				else if (controlID == radioButtonBuddiesID)
				{
					parentBuddies->winHide(FALSE);
					parentIgnore->winHide(TRUE);
				}
				else if (controlID == radioButtonIgnoreID)
				{
					parentBuddies->winHide(TRUE);
					parentIgnore->winHide(FALSE);
					refreshIgnoreList();
				}
				else if (controlID == buttonAddBuddyID)
				{
					/*
					UnicodeString uName = GadgetTextEntryGetText(textEntry);
					AsciiString aName;
					aName.translate(uName);
					if (!aName.isEmpty())
					{
						TheWOLBuddyList->requestBuddyAdd(aName);
					}
					GadgetTextEntrySetText(textEntry, UnicodeString::TheEmptyString);
					*/
				}
				else if (controlID == buttonDeleteBuddyID)
				{
					/*
					int selected;
					AsciiString selectedName = AsciiString::TheEmptyString;

					GadgetListBoxGetSelected(listbox, &selected);
					if (selected >= 0)
						selectedName = TheNameKeyGenerator->keyToName((NameKeyType)(int)GadgetListBoxGetItemData(listbox, selected));

					if (!selectedName.isEmpty())
					{
						TheWOLBuddyList->requestBuddyDelete(selectedName);
					}
					*/
				}
				break;
			}// case GBM_SELECTED:
		case GLM_DOUBLE_CLICKED:
			{
				/*
				GameWindow *control = (GameWindow *)mData1;
				Int controlID = control->winGetWindowId();
				if( controlID == listboxBuddyID ) 
				{
					int rowSelected = mData2;
				
					if (rowSelected >= 0)
					{
						UnicodeString buddyName;
						GameWindow *listboxWindow = TheWindowManager->winGetWindowFromId( parent, listboxBuddyID );

							// get text of buddy name
						buddyName = GadgetListBoxGetText( listboxWindow, rowSelected,0 );
						GPProfile buddyID = (GPProfile)GadgetListBoxGetItemData( listboxWindow, rowSelected, 0 );

						Int index = -1;
						gpGetBuddyIndex(TheGPConnection, buddyID, &index);
						if (index >= 0)
						{
							GPBuddyStatus status;
							gpGetBuddyStatus(TheGPConnection, rowSelected, &status);

							UnicodeString string;
							string.format(L"To join %s in %hs:", buddyName.str(), status.locationString);
							GameSpyAddText(string, GSCOLOR_DEFAULT);

							if (status.status == GP_CHATTING)
							{
								AsciiString location = status.locationString;
								AsciiString val;
								location.nextToken(&val, "/");
								location.nextToken(&val, "/");
								location.nextToken(&val, "/");

								string.format(L"  ???");
								if (!val.isEmpty())
								{
									Int groupRoom = atoi(val.str());
									if (TheGameSpyChat->getCurrentGroupRoomID() == groupRoom)
									{
										// already there
										string.format(L"  nothing");
										GameSpyAddText(string, GSCOLOR_DEFAULT);
									}
									else
									{
										GroupRoomMap *rooms = TheGameSpyChat->getGroupRooms();
										if (rooms)
										{
											Bool needToJoin = true;
											GroupRoomMap::iterator it = rooms->find(groupRoom);
											if (it != rooms->end())
											{
												// he's in a different room
												if (TheGameSpyChat->getCurrentGroupRoomID())
												{
													string.format(L"  leave group room");
													GameSpyAddText(string, GSCOLOR_DEFAULT);

													TheGameSpyChat->leaveRoom(GroupRoom);
												}
												else if (TheGameSpyGame->isInGame())
												{
													if (TheGameSpyGame->isGameInProgress())
													{
														string.format(L"  can't leave game in progress");
														GameSpyAddText(string, GSCOLOR_DEFAULT);
														needToJoin = false;
													}
													else
													{
														string.format(L"  leave game setup");
														GameSpyAddText(string, GSCOLOR_DEFAULT);

														TheGameSpyChat->leaveRoom(StagingRoom);
														TheGameSpyGame->leaveGame();
													}
												}
												if (needToJoin)
												{
													string.format(L"  join lobby %d", groupRoom);
													TheGameSpyChat->joinGroupRoom(groupRoom);
													GameSpyAddText(string, GSCOLOR_DEFAULT);
												}
											}
										}
									}
								}
							}
						}
						else
						{
							DEBUG_CRASH(("No buddy associated with that ProfileID"));
							GameSpyUpdateBuddyOverlay();
						}
					}
				}
				*/
				break;
			}
		
		default:
			return MSG_IGNORED;

	}//Switch

	return MSG_HANDLED;
}// WOLBuddyOverlaySystem

WindowMsgHandledType PopupBuddyNotificationSystem( GameWindow *window, UnsignedInt msg, 
														 WindowMsgData mData1, WindowMsgData mData2 )
{
	switch( msg )
	{
		case GWM_CREATE:
			{
				break;
			} // case GWM_DESTROY:

		case GWM_DESTROY:
			{
				break;
			} // case GWM_DESTROY:

		case GBM_SELECTED:
			{
				GameWindow *control = (GameWindow *)mData1;
				Int controlID = control->winGetWindowId();

				if (controlID == buttonNotificationID)
				{
					GameSpyOpenOverlay( GSOVERLAY_BUDDY );
				}
				break;
			}

		default:
			return MSG_IGNORED;

	}//Switch

	return MSG_HANDLED;
}// PopupBuddyNotificationSystem

/*
static NameKeyType buttonAcceptBuddyID = NAMEKEY_INVALID;
static NameKeyType buttonDenyBuddyID = NAMEKEY_INVALID;
*/
static NameKeyType buttonAddID = NAMEKEY_INVALID;
static NameKeyType buttonDeleteID = NAMEKEY_INVALID;
static NameKeyType buttonPlayID = NAMEKEY_INVALID;
static NameKeyType buttonIgnoreID = NAMEKEY_INVALID;
static NameKeyType buttonStatsID = NAMEKEY_INVALID;
// Window Pointers ------------------------------------------------------------------------
//static GameWindow *rCparent = NULL;


//-------------------------------------------------------------------------------------------------
/** WOL Buddy Overlay Right Click menu callbacks */
//-------------------------------------------------------------------------------------------------
void WOLBuddyOverlayRCMenuInit( WindowLayout *layout, void *userData )
{
	AsciiString controlName;
	controlName.format("%s:ButtonAdd",layout->getFilename().str()+6);
	buttonAddID =  TheNameKeyGenerator->nameToKey( controlName );
	controlName.format("%s:ButtonDelete",layout->getFilename().str()+6);
	buttonDeleteID =  TheNameKeyGenerator->nameToKey( controlName );
	controlName.format("%s:ButtonPlay",layout->getFilename().str()+6);
	buttonPlayID =  TheNameKeyGenerator->nameToKey( controlName );
	controlName.format("%s:ButtonIgnore",layout->getFilename().str()+6);
	buttonIgnoreID =  TheNameKeyGenerator->nameToKey( controlName );
	controlName.format("%s:ButtonStats",layout->getFilename().str()+6);
	buttonStatsID =  TheNameKeyGenerator->nameToKey( controlName );
}
static void closeRightClickMenu(GameWindow *win)
{

	if(win)
	{
		WindowLayout *winLay = win->winGetLayout();
		if(!winLay)
			return;
		winLay->destroyWindows();					
		winLay->deleteInstance();
		winLay = NULL;

	}
}

// RequestBuddyAdd exact retail body is emitted by
// RequestBuddyAddThunk.cpp, so this translation unit only needs the prototype
// its call sites below refer to.
void RequestBuddyAdd( Int, AsciiString );
WindowMsgHandledType WOLBuddyOverlayRCMenuSystem( GameWindow *window, UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2 )
{

	switch( msg )
	{
		
		case GWM_CREATE:
			{
				
				break;
			} // case GWM_DESTROY:

		case GWM_DESTROY:
			{
				rcMenu = NULL;
				break;
			} // case GWM_DESTROY:

		case GGM_CLOSE:
			{
				closeRightClickMenu(window);
				//rcMenu = NULL;
				break;
			}
		

		case GBM_SELECTED:
			{
				GameWindow *control = (GameWindow *)mData1;
				Int controlID = control->winGetWindowId();
				GameSpyRCMenuData *rcData = (GameSpyRCMenuData*)window->winGetUserData();
				if(!rcData)
					break;
				DEBUG_ASSERTCRASH(rcData, ("WOLBuddyOverlayRCMenuSystem GBM_SELECTED:: we're attempting to read the GameSpyRCMenuData from the window, but the data's not there"));
				GPProfile profileID = rcData->m_id;
				AsciiString nick = rcData->m_nick;

				Bool isBuddy = false, isRequest = false;
				Bool isGameSpyUser = profileID > 0;
				if (rcData->m_itemType == ITEM_BUDDY)
					isBuddy = TRUE;
				else if (rcData->m_itemType == ITEM_REQUEST)
					isRequest = TRUE;

				if(rcData)
				{
					delete rcData;
					rcData = NULL;
				}
				window->winSetUserData(NULL);
				//DEBUG_ASSERTCRASH(profileID > 0, ("Bad profile ID in user data!"));

				if( controlID == buttonAddID )
				{
					if(!isGameSpyUser)
						break;
					DEBUG_LOG(("ButtonAdd was pushed\n"));
					if (isRequest)
					{
						// ok the request
						BuddyRequest req;
						req.buddyRequestType = BuddyRequest::BUDDYREQUEST_OKADD;
						req.arg.profile.id = profileID;
						TheGameSpyBuddyMessageQueue->addRequest(req);

						BuddyInfoMap *m = TheGameSpyInfo->getBuddyRequestMap();
						m->erase( profileID );
						// if the profile ID is not from a buddy and we're okaying his request, then
						// request to add him to our list automatically CLH 2-18-03
						if(!TheGameSpyInfo->isBuddy(profileID))
						{
							RequestBuddyAdd(profileID, nick);		
						}
						updateBuddyInfo();
					}
					else if (!isBuddy)
					{
						RequestBuddyAdd(profileID, nick);
					}
				}
				else if( controlID == buttonDeleteID )
				{
					if(!isGameSpyUser)
						break;
					if (isBuddy)
					{
						// delete the buddy
						BuddyRequest req;
						req.buddyRequestType = BuddyRequest::BUDDYREQUEST_DELBUDDY;
						req.arg.profile.id = profileID;
						TheGameSpyBuddyMessageQueue->addRequest(req);
					}
					else 
					{
						// delete the request
						BuddyRequest req;
						req.buddyRequestType = BuddyRequest::BUDDYREQUEST_DENYADD;
						req.arg.profile.id = profileID;
						TheGameSpyBuddyMessageQueue->addRequest(req);
						BuddyInfoMap *m = TheGameSpyInfo->getBuddyRequestMap();
						m->erase( profileID );
					}
					BuddyInfoMap *buddies = (isBuddy)?TheGameSpyInfo->getBuddyMap():TheGameSpyInfo->getBuddyRequestMap();
					buddies->erase(profileID);
					updateBuddyInfo();
					DEBUG_LOG(("ButtonDelete was pushed\n"));
					PopulateLobbyPlayerListbox();
				}
				else if( controlID == buttonPlayID )
				{
					DEBUG_LOG(("buttonPlayID was pushed\n"));
				}
				else if( controlID == buttonIgnoreID )
				{
					DEBUG_LOG(("%s is isGameSpyUser %d", nick.str(), isGameSpyUser));
					if( isGameSpyUser )
					{
						if(TheGameSpyInfo->isSavedIgnored(profileID))
						{
							TheGameSpyInfo->removeFromSavedIgnoreList(profileID);
						}
						else
						{
							TheGameSpyInfo->addToSavedIgnoreList(profileID, nick);
						}
					}
					else
					{	
						if(TheGameSpyInfo->isIgnored(nick))
						{
							TheGameSpyInfo->removeFromIgnoreList(nick);
						}
						else
						{
							TheGameSpyInfo->addToIgnoreList(nick);
						}
					}
					updateBuddyInfo();
					refreshIgnoreList();
					// repopulate our player listboxes now
					PopulateLobbyPlayerListbox();
				}
				else if( controlID == buttonStatsID )
				{
					DEBUG_LOG(("buttonStatsID was pushed\n"));
					GameSpyCloseOverlay(GSOVERLAY_PLAYERINFO);
					SetLookAtPlayer(profileID,nick );
					GameSpyOpenOverlay(GSOVERLAY_PLAYERINFO);
					PSRequest req;
					req.requestType = PSRequest::PSREQUEST_READPLAYERSTATS;
					req.player.id = profileID;
					TheGameSpyPSMessageQueue->addRequest(req);
				}
				closeRightClickMenu(window);
				break;
			}
		default:
			return MSG_IGNORED;
	
	}//Switch		
	return MSG_HANDLED;
}


void setUnignoreText( WindowLayout *layout, AsciiString nick, GPProfile id)
{
	AsciiString controlName;
	controlName.format("%s:ButtonIgnore",layout->getFilename().str()+6);
	NameKeyType ID =  TheNameKeyGenerator->nameToKey( controlName );
	GameWindow *win = TheWindowManager->winGetWindowFromId(layout->getFirstWindow(), ID);
	if(win)
	{
		if(TheGameSpyInfo->isSavedIgnored(id) || TheGameSpyInfo->isIgnored(nick))
			GadgetButtonSetText(win, TheGameText->fetch("GUI:Unignore"));
	}
}

void refreshIgnoreList( void )
{

	
	SavedIgnoreMap tempMap;
	tempMap = TheGameSpyInfo->returnSavedIgnoreList();
	SavedIgnoreMap::iterator it = tempMap.begin();
	GadgetListBoxReset(listboxIgnore);
	while(it != tempMap.end())
	{
		UnicodeString name;
		name.translate(it->second);
		Int pos = GadgetListBoxAddEntryText(listboxIgnore, name, GameMakeColor(255,100,100,255),-1);
		GadgetListBoxSetItemData(listboxIgnore, (void *)it->first,pos );
		++it;
	}
	IgnoreList tempList;
	tempList = TheGameSpyInfo->returnIgnoreList();
	IgnoreList::iterator iListIt = tempList.begin();
	while( iListIt != tempList.end())
	{
		AsciiString aName = *iListIt;
		UnicodeString name;
		name.translate(aName);
		Int pos = GadgetListBoxAddEntryText(listboxIgnore, name, GameMakeColor(255,100,100,255),-1);
		GadgetListBoxSetItemData(listboxIgnore, 0,pos );
		++iListIt;
	}

//
//	GPProfile profileID = 0;
//	PlayerInfoMap::iterator it = TheGameSpyInfo->getPlayerInfoMap()->find(aName);
//	if (it != TheGameSpyInfo->getPlayerInfoMap()->end())
//		profileID = it->second.m_profileID;

}

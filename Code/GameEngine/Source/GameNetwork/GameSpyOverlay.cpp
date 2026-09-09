// cl: /DNDEBUG /DWIN32 /D_WINDOWS /DIN_ADDR=in_addr /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
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

// FILE: wolscreens.cpp //////////////////////////////////////////////////////
// Westwood Online screen setup/teardown
// Author: Matthew D. Campbell, November 2001

// This TU supplies the retail-sized AudioEventRTS declaration below.  Several
// GUI headers include the Zero Hour AudioEventRTS header transitively, so keep
// that smaller declaration out without changing the shared headers.
#define _H_AUDIOEVENTRTS_

class AsciiString;
enum ObjectID;
enum DrawableID;
class AudioEventRTS
{
public:
	AudioEventRTS();
	AudioEventRTS( const AsciiString &eventName );
	AudioEventRTS( const AsciiString &eventName, ObjectID extra );
	AudioEventRTS( const AsciiString &eventName, DrawableID extra );
	~AudioEventRTS();
	AudioEventRTS( const AudioEventRTS &other );
	AudioEventRTS &operator=( const AudioEventRTS &other );

private:
	unsigned char m_data[0x70];
};

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "GameClient/GadgetListBox.h"
#include "GameClient/GameText.h"
#include "GameClient/MessageBox.h"
#include "GameClient/ShellHooks.h"
//#include "GameNetwork/GameSpy.h"
//#include "GameNetwork/GameSpyGP.h"

#include "GameNetwork/GameSpyOverlay.h"
//#include "GameNetwork/GameSpy/PeerDefs.h"
#include "GameNetwork/GameSpy/BuddyThread.h"

class BFMERetailAsciiString;

template <typename T> class StringBase
{
friend class BFMERetailAsciiString;

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

	friend class UnicodeString;
	void *m_data;
};

inline UnicodeString::UnicodeString( const UnicodeString &other )
{
	((StringBase<wchar_t> *)this)->StringBase<wchar_t>::StringBase(
		*(const StringBase<wchar_t> *)&other);
}

void deleteNotificationBox( void );
void b_00042a50( void );
static void raiseOverlays( void );

// BFME WindowLayout vtable order (see Code/.../window_layout.h):
// slot0 runInit, slot1 dtor, slot2 runUpdate (+0x08), slot3 runShutdown (+0x0c),
// slot4 hide (+0x10), slot5 bringForward (+0x14), slot8 destroyWindows (+0x20).
// Retail raiseOverlays/RaiseGSMessageBox and CloseAll use this slot map.
class BFMEOverlayLayoutCloseView
{
public:
	virtual void runInit( void *userData ) {}
	virtual ~BFMEOverlayLayoutCloseView() {}
	virtual void runUpdate( void *userData ) {}
	virtual void runShutdown( void *userData ) {}
	virtual void hide( int hide ) {}
	virtual void bringForward( void ) {}
	virtual void addWindow( void *window ) {}
	virtual void removeWindow( void *window ) {}
	virtual void destroyWindows( void ) {}
};

class BFMERetailAsciiString : private StringBase<char>
{
public:
	BFMERetailAsciiString( const char *text ) : StringBase<char>( text ) {}
	BFMERetailAsciiString( const BFMERetailAsciiString &other )
		: StringBase<char>( other ) {}
	~BFMERetailAsciiString() {}
};

class AudioManager;
extern AudioManager *TheAudio;

class BFMEOverlayAudioManagerView
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual void slot3c() = 0;
	virtual void slot40() = 0;
	virtual void addAudioEvent( AudioEventRTS *event ) = 0;
};

// GameWindowManager::winCreateLayout is the retail virtual at +0x6c.  The
// parameter is a BFME AsciiString by value, so a local view is needed to keep
// the temporary's construction ABI without changing the shared header.
class BFMEOverlayWindowManagerView
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual void slot3c() = 0;
	virtual void slot40() = 0;
	virtual void slot44() = 0;
	virtual void slot48() = 0;
	virtual void slot4c() = 0;
	virtual void slot50() = 0;
	virtual void slot54() = 0;
	virtual void slot58() = 0;
	virtual void slot5c() = 0;
	virtual void slot60() = 0;
	virtual void slot64() = 0;
	virtual void slot68() = 0;
	virtual WindowLayout *winCreateLayout( BFMERetailAsciiString filename ) = 0;
};

// Message boxes -------------------------------------
static GameWinMsgBoxFunc okFunc = NULL;
static GameWinMsgBoxFunc cancelFunc = NULL;
static volatile Bool reOpenPlayerInfoFlag = FALSE;
/**
	* messageBoxOK is called when a message box is destroyed
	* by way of an OK button, so we can clear our pointers to it.
	*/
static void messageBoxOK( void )
{
	if (okFunc)
	{
		okFunc();
		okFunc = NULL;
	}
}

/**
	* messageBoxCancel is called when a message box is destroyed
	* by way of a Cancel button, so we can clear our pointers to it.
	*/
static void messageBoxCancel( void )
{
	if (cancelFunc)
	{
		cancelFunc();
		cancelFunc = NULL;
	}
}

/**
	* clearGSMessageBoxes removes the current message box if
	* one is present.  This is usually done when putting up a
	* second messageBox.
	*/
void ClearGSMessageBoxes( void )
{
	if (okFunc)
	{
		okFunc = NULL;
	}

	if (cancelFunc)
	{
		cancelFunc = NULL;
	}
}

/**
	* GSMessageBoxOk puts up an OK dialog box and saves the
	* pointers to it and its callbacks.
	*/
void GSMessageBoxOk(UnicodeString title, UnicodeString message, GameWinMsgBoxFunc newOkFunc)
{
	if (reOpenPlayerInfoFlag)
	{
		b_00042a50();
		reOpenPlayerInfoFlag = FALSE;
	}
	if (okFunc)
		okFunc = NULL;
	if (cancelFunc)
		cancelFunc = NULL;
	MessageBoxOk(title, message, messageBoxOK);
	reOpenPlayerInfoFlag = TRUE;
	okFunc = newOkFunc;
}

/**
	* GSMessageBoxOkCancel puts up an OK/Cancel dialog box and saves the
	* pointers to it and its callbacks.
	*/
void GSMessageBoxOkCancel(UnicodeString title, UnicodeString message, GameWinMsgBoxFunc newOkFunc, GameWinMsgBoxFunc newCancelFunc)
{
	if (reOpenPlayerInfoFlag)
	{
		b_00042a50();
		reOpenPlayerInfoFlag = FALSE;
	}
	if (okFunc)
		okFunc = NULL;
	if (cancelFunc)
		cancelFunc = NULL;
	MessageBoxOkCancel(title, message, messageBoxOK, messageBoxCancel);
	okFunc = newOkFunc;
	cancelFunc = newCancelFunc;
	reOpenPlayerInfoFlag = TRUE;
}

/**
	* GSMessageBoxYesNo puts up a Yes/No dialog box and saves the
	* pointers to it and its callbacks.
	*/
void GSMessageBoxYesNo(UnicodeString title, UnicodeString message, GameWinMsgBoxFunc newYesFunc, GameWinMsgBoxFunc newNoFunc)
{
	if (reOpenPlayerInfoFlag)
	{
		b_00042a50();
		reOpenPlayerInfoFlag = FALSE;
	}
	if (okFunc)
		okFunc = NULL;
	if (cancelFunc)
		cancelFunc = NULL;
	MessageBoxYesNo(title, message, messageBoxOK, messageBoxCancel);
	reOpenPlayerInfoFlag = TRUE;
	okFunc = newYesFunc;
	cancelFunc = newNoFunc;
}

/**
	* If the screen transitions underneath the dialog box, we
	* need to raise it to keep it visible.
	*
	* Retail (0x627C50, 32B): only the overlay bringForward loop. The ZH
	* messageBoxWindow->winBringToTop() tail is absent from the standalone body.
	*/
void RaiseGSMessageBox( void )
{
	raiseOverlays();
}

// Overlay screens -------------------------------------

/**
	* gsOverlays holds a list of the .wnd files used in GS overlays.
	* The entries *MUST* be in the same order as the GSOverlayType enum.
	*/
static const char * gsOverlays[GSOVERLAY_MAX] =
{
	"Menus/PopupPlayerInfo.wnd",	// Player info (right-click)
	"Menus/WOLMapSelectMenu.wnd",	// Map select
	"Menus/WOLBuddyOverlay.wnd",	// Buddy list
	"Menus/WOLPageOverlay.wnd",		// Find/page
	"Menus/PopupHostGame.wnd",		// Hosting options (game name, password, etc)
	"Menus/PopupJoinGame.wnd",		// Joining options (password, etc)
	"Menus/PopupLadderSelect.wnd",// LadderSelect
	"Menus/PopupLocaleSelect.wnd",// Prompt for user's locale
	"Menus/OptionsMenu.wnd",			// popup options
};

static WindowLayout *overlayLayouts[GSOVERLAY_MAX] =
{
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
};

static void buddyTryReconnect( void )
{
	BuddyRequest req;
	req.buddyRequestType = BuddyRequest::BUDDYREQUEST_RELOGIN;
	TheGameSpyBuddyMessageQueue->addRequest( req );
}

void GameSpyOpenOverlay( GSOverlayType overlay )
{
	if (overlay == GSOVERLAY_BUDDY)
	{
		if (!TheGameSpyBuddyMessageQueue->isConnected())
		{
			// not connected - is it because we were disconnected?
			if (TheGameSpyBuddyMessageQueue->getLocalProfileID())
			{
				// used to be connected
				GSMessageBoxYesNo(TheGameText->fetch("GUI:GPErrorTitle"), TheGameText->fetch("GUI:GPDisconnected"), buddyTryReconnect, NULL);
			}
			else
			{
				// no profile
				GSMessageBoxOk(TheGameText->fetch("GUI:GPErrorTitle"), TheGameText->fetch("GUI:GPNoProfile"), NULL);
			}
			return;
		}
		AudioEventRTS buttonClick(
			*(AsciiString *)&BFMERetailAsciiString("GUICommunicatorOpen"),
			(ObjectID)2);

		if( TheAudio )
		{
			((BFMEOverlayAudioManagerView *)TheAudio)->addAudioEvent(
				&buttonClick);
		}  // end if
	}
	if (overlayLayouts[overlay])
	{
		((BFMEOverlayLayoutCloseView *)overlayLayouts[overlay])->hide(
			FALSE );
		((BFMEOverlayLayoutCloseView *)overlayLayouts[overlay])->bringForward();
	}
	else
	{
		overlayLayouts[overlay] =
			((BFMEOverlayWindowManagerView *)TheWindowManager)->winCreateLayout(
				BFMERetailAsciiString( gsOverlays[overlay] ));
		if (overlayLayouts[overlay]->getFirstWindow())
			*(int *)((char *)overlayLayouts[overlay]->getFirstWindow() +
				0x1f4) = 0;
		((BFMEOverlayLayoutCloseView *)overlayLayouts[overlay])->runInit(
			0 );
		((BFMEOverlayLayoutCloseView *)overlayLayouts[overlay])->hide(
			FALSE );
		((BFMEOverlayLayoutCloseView *)overlayLayouts[overlay])->bringForward();
	}
}

void GameSpyCloseOverlay( GSOverlayType overlay )
{
	switch(overlay)
	{
		case GSOVERLAY_PLAYERINFO:
			DEBUG_LOG(("Closing overlay GSOVERLAY_PLAYERINFO\n"));
			break;
		case GSOVERLAY_MAPSELECT:
			DEBUG_LOG(("Closing overlay GSOVERLAY_MAPSELECT\n"));
			break;
		case GSOVERLAY_BUDDY:
			DEBUG_LOG(("Closing overlay GSOVERLAY_BUDDY\n"));
			break;
		case GSOVERLAY_PAGE:
			DEBUG_LOG(("Closing overlay GSOVERLAY_PAGE\n"));
			break;
		case GSOVERLAY_GAMEOPTIONS:
			DEBUG_LOG(("Closing overlay GSOVERLAY_GAMEOPTIONS\n"));
			break;
		case GSOVERLAY_GAMEPASSWORD:
			DEBUG_LOG(("Closing overlay GSOVERLAY_GAMEPASSWORD\n"));
			break;
		case GSOVERLAY_LADDERSELECT:
			DEBUG_LOG(("Closing overlay GSOVERLAY_LADDERSELECT\n"));
			break;
		case GSOVERLAY_OPTIONS:
			DEBUG_LOG(("Closing overlay GSOVERLAY_OPTIONS\n"));
			if( overlayLayouts[overlay] )
			{
				SignalUIInteraction(SHELL_SCRIPT_HOOK_OPTIONS_CLOSED);
			}
			break;
	}
	if( overlayLayouts[overlay] )
	{
		overlayLayouts[overlay]->runShutdown();
		overlayLayouts[overlay]->destroyWindows();
		overlayLayouts[overlay]->deleteInstance();
		overlayLayouts[overlay] = NULL;
	}
}

Bool GameSpyIsOverlayOpen( GSOverlayType overlay )
{
	return (overlayLayouts[overlay] != NULL);
}

void GameSpyToggleOverlay( GSOverlayType overlay )
{
	if (GameSpyIsOverlayOpen(overlay))
		GameSpyCloseOverlay(overlay);
	else
		GameSpyOpenOverlay(overlay);
}

void raiseOverlays( void )
{
	// Double-load of overlayLayouts[i] yields retail mov eax,[esi]/mov ecx,eax
	// thiscall shape (single local would load straight into ecx, 30B miss).
	for (int i=0; i<GSOVERLAY_MAX; ++i)
	{
		if (overlayLayouts[i])
			((BFMEOverlayLayoutCloseView *)overlayLayouts[i])->bringForward();
	}
}

void GameSpyCloseAllOverlays( void )
{
	for (int i=0; i<GSOVERLAY_MAX; ++i)
	{
		GSOverlayType overlay = (GSOverlayType)i;
		// Release OPTIONS special-case only (DEBUG_LOG cases compile out under NDEBUG).
		if (overlay == GSOVERLAY_OPTIONS)
		{
			if (overlayLayouts[overlay])
			{
				SignalUIInteraction(SHELL_SCRIPT_HOOK_OPTIONS_CLOSED);
			}
		}
		BFMEOverlayLayoutCloseView *layout =
			(BFMEOverlayLayoutCloseView *)overlayLayouts[overlay];
		if (layout)
		{
			layout->runShutdown( NULL );
			layout = (BFMEOverlayLayoutCloseView *)overlayLayouts[overlay];
			layout->destroyWindows();
			layout = (BFMEOverlayLayoutCloseView *)overlayLayouts[overlay];
			if (layout)
			{
				// scalar-deleting dtor at vtable slot 1 (push 1; call [eax+4])
				delete layout;
			}
			overlayLayouts[overlay] = NULL;
		}
	}

	// if we're shutting down the rest, chances are we don't want this popping up.
	deleteNotificationBox();
}

void GameSpyUpdateOverlays( void )
{
	// Same double-load as raiseOverlays: retail is
	// mov eax,[esi] / test eax,eax / jz / mov ecx,eax / mov eax,[ecx] / push 0 / call [eax+8].
	// A single local loads straight into ecx and misses the 34-byte body at 0x00627C10.
	for (int i=0; i<GSOVERLAY_MAX; ++i)
	{
		if (overlayLayouts[i])
			((BFMEOverlayLayoutCloseView *)overlayLayouts[i])->runUpdate( NULL );
	}
}

void ReOpenPlayerInfo( void )
{
	reOpenPlayerInfoFlag = TRUE;
}
void CheckReOpenPlayerInfo(void )
{
	if(!reOpenPlayerInfoFlag)
		return;

	GameSpyOpenOverlay(GSOVERLAY_PLAYERINFO);
	reOpenPlayerInfoFlag = FALSE;
		
}

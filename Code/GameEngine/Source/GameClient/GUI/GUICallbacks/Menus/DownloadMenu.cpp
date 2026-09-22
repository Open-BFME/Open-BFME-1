// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWLib
// getErrorString retail4C7970 is recovered in NetworkStringGetterIdentities.cpp from this OnError caller.
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it

#include <string.h>
#define ASCIISTRING_H
#include "string_base.h"

class AsciiString : private StringBase<char>
{
public:
	static AsciiString TheEmptyString;
	AsciiString() : StringBase<char>() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}

	const char *str() const
	{
		return m_data ? m_data->data : "";
	}

	const char *reverseFind(char character) const
	{
		const char *start = m_data ? m_data->data : "";
		const char *cursor = start + (m_data ? m_data->length : 0);
		while (cursor != start)
		{
			--cursor;
			if (*cursor == character)
				return cursor;
		}
		return 0;
	}

	__forceinline void set(const char *text)
	{
		((StringBase<char> *)this)->set(text, text ? strlen(text) : 0);
	}

	int compareNoCase(const AsciiString &other) const;

	void __cdecl format(AsciiString format, ...);
};

inline bool operator==(const AsciiString &left, const AsciiString &right)
{
	return left.compareNoCase(right) == 0;
}
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

// FILE: DownloadMenu.cpp /////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
//                                                                          
//                       Electronic Arts Pacific.                          
//                                                                          
//                       Confidential Information                           
//                Copyright (C) 2002 - All Rights Reserved                  
//                                                                          
//-----------------------------------------------------------------------------
//
// Project:   RTS3
//
// File name: DownloadMenu.cpp
//
// Created:   Matthew D. Campbell, July 2002
//
// Desc:      the Patch Download window control
//
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/GameEngine.h"
#include "Common/NameKeyGenerator.h"
#include "GameClient/GUICallbacks.h"
#include "GameClient/GameWindowManager.h"
#include "GameClient/GadgetStaticText.h"
#include "GameClient/GadgetProgressBar.h"
#include "GameClient/GameText.h"
#include "GameClient/MessageBox.h"

#include "GameLogic/GameLogic.h"

#include "GameNetwork/DownloadManager.h"
#include "GameNetwork/GameSpy/MainMenuUtils.h"

// Retail's UnicodeString derives from StringBase<unsigned short> and holds
// nothing of its own, so its copy ctor is a forwarder retail inlines at every
// by-value-return and member-copy site: the bytes encode the base body at
// 0x00888400 (??0?$StringBase@G@@AAE@ABV0@@Z) directly. The vendored
// UnicodeString.h leaves the copy ctor declared and undefined, so without this
// cl emits an out-of-line call to ??0UnicodeString@@QAE@ABV0@@Z instead.
inline UnicodeString::UnicodeString(const UnicodeString &stringSrc)
{
	((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(
		*(const StringBase<unsigned short> *)&stringSrc);
}

// Retail StringBase<char> temp ABI for DownloadMenuInput @ 0x4C8360:
// ctor 0x888BC0, buffer data at +8, dtor via releaseBuffer 0x887940 (same as DifficultySelect).
class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString( const char *string );
	~BFMERetailAsciiString() { releaseBuffer(); }

	const char *str() const
	{
		static const char nullCharacter = 0;
		return m_data ? m_data + 8 : &nullCharacter;
	}

private:
	void releaseBuffer();
	char *m_data;
};

// PRIVATE DATA ///////////////////////////////////////////////////////////////////////////////////
static NameKeyType buttonCancelID = NAMEKEY_INVALID;
static NameKeyType staticTextSizeID = NAMEKEY_INVALID;
static NameKeyType staticTextTimeID = NAMEKEY_INVALID;
static NameKeyType staticTextFileID = NAMEKEY_INVALID;
static NameKeyType staticTextStatusID = NAMEKEY_INVALID;
static NameKeyType progressBarMunkeeID = NAMEKEY_INVALID;

static GameWindow * staticTextSize = NULL;
static GameWindow * staticTextTime = NULL;
static GameWindow * staticTextFile = NULL;
static GameWindow * staticTextStatus = NULL;
static GameWindow * progressBarMunkee = NULL;

static GameWindow *parent = NULL;

// BFME made WindowLayout's methods virtual (vtable read at 0x10f7514: runInit,
// dtor, runUpdate, runShutdown @+0x0c, hide, bringForward, addWindow,
// removeWindow, destroyWindows @+0x20); the swept ZH header is non-virtual, so
// closeDownloadWindow casts to this view to emit retail's virtual-call shape.
// deleteInstance stays a plain inline: `delete this` through the virtual dtor
// produces retail's `push 1; call [eax+4]` deleting-dtor call.
class BFMEDownloadMenuLayoutView
{
public:
	virtual void runInit( void *userData );
	virtual ~BFMEDownloadMenuLayoutView( );
	virtual void runUpdate( void *userData );
	virtual void runShutdown( void *userData );
	virtual void hide( int hide );
	virtual void bringForward( void );
	virtual void addWindow( GameWindow *window );
	virtual void removeWindow( GameWindow *window );
	virtual void destroyWindows( void );
	void deleteInstance( void ) { delete this; }
};

static void closeDownloadWindow( void )
{
	DEBUG_ASSERTCRASH(parent, ("No Parent"));
	if (!parent)
		return;

  BFMEDownloadMenuLayoutView *menuLayout = (BFMEDownloadMenuLayoutView *)parent->winGetLayout();
	menuLayout->runShutdown( NULL );
  menuLayout->destroyWindows();
	menuLayout->deleteInstance();
	menuLayout = NULL;

	GameWindow *mainWin = TheWindowManager->winGetWindowFromId( NULL, NAMEKEY("MainMenu.wnd:MainMenuParent") );
	if (mainWin)
		TheWindowManager->winSetFocus( mainWin );
}

static void errorCallback( void )
{
	HandleCanceledDownload();
	closeDownloadWindow();
}

static void successQuitCallback( void )
{
	TheGameEngine->setQuitting( TRUE );
	closeDownloadWindow();

	// Clean up game data.  No crashy-crash for you!
	if (TheGameLogic->isInGame())
		TheMessageStream->appendMessage( GameMessage::MSG_CLEAR_GAME_DATA );
}

static void successNoQuitCallback( void )
{
	HandleCanceledDownload();
	closeDownloadWindow();
}

class DownloadManagerMunkee : public DownloadManager
{
public:
	DownloadManagerMunkee() {m_shouldQuitOnSuccess = true; m_shouldQuitOnSuccess = false;}
	virtual HRESULT OnError( Int error );
	virtual HRESULT OnEnd();
	virtual HRESULT OnProgressUpdate( Int bytesread, Int totalsize, Int timetaken, Int timeleft );
	virtual HRESULT OnStatusUpdate( Int status );
	virtual HRESULT downloadFile( AsciiString server, AsciiString username, AsciiString password, AsciiString file, AsciiString localfile, AsciiString regkey, Bool tryResume );

private:
	Bool m_shouldQuitOnSuccess;
};

// ?downloadFile@DownloadManagerMunkee@@UAEJVAsciiString@@00000_N@Z
HRESULT DownloadManagerMunkee::downloadFile( AsciiString server, AsciiString username, AsciiString password, AsciiString file, AsciiString localfile, AsciiString regkey, Bool tryResume )
{
	if (strstr(localfile.str(), "patches\\") != NULL)
	{
		m_shouldQuitOnSuccess = true;
	}

	if (staticTextFile)
	{
		AsciiString bob = file;
		const char *tmp = bob.reverseFind('/');
		if (tmp)
			bob.set(tmp + 1);
		tmp = bob.reverseFind('\\');
		if (tmp)
			bob.set(tmp + 1);

		UnicodeString fileString;
		fileString.translate(bob);
		GadgetStaticTextSetText(staticTextFile, fileString);
	}

	password.format("-%s", password.str());
	return DownloadManager::downloadFile( server, username, password, file, localfile, regkey, tryResume );
}
HRESULT DownloadManagerMunkee::OnError( Int error )
{
	HRESULT ret = DownloadManager::OnError( error );

	MessageBoxOk(TheGameText->fetch("GUI:DownloadErrorTitle"), getErrorString(), errorCallback);
	return ret;
}
HRESULT DownloadManagerMunkee::OnEnd()
{
	HRESULT ret = DownloadManager::OnEnd();

	if (isFileQueuedForDownload())
	{
		return downloadNextQueuedFile();
	}
	if (m_shouldQuitOnSuccess)
		MessageBoxOk(TheGameText->fetch("GUI:DownloadSuccessTitle"), TheGameText->fetch("GUI:DownloadSuccessMustQuit"), successQuitCallback);
	else
		MessageBoxOk(TheGameText->fetch("GUI:DownloadSuccessTitle"), TheGameText->fetch("GUI:DownloadSuccess"), successNoQuitCallback);
	return ret;
}

static time_t lastUpdate = 0;
static Int timeLeft = 0;

class DownloadManagerProgressView
{
public:
	HRESULT OnProgressUpdate(Int bytesread, Int totalsize, Int timetaken, Int timeleft);
};

class DownloadUnicodeStringSetView
{
public:
	void set(const DownloadUnicodeStringSetView &other);
};

// byte-exact reconstruction: Code/GameEngine/Source/Common/DownloadManagerMunkee_OnProgressUpdateMethodThunk.cpp
HRESULT DownloadManagerMunkee::OnProgressUpdate( Int bytesread, Int totalsize, Int timetaken, Int timeleft )
{
	HRESULT ret = reinterpret_cast<DownloadManagerProgressView *>(this)->OnProgressUpdate(
		bytesread, totalsize, timetaken, timeleft );

	if (progressBarMunkee)
	{
		Int percent = bytesread * 100 / totalsize;
		GadgetProgressBarSetProgress( progressBarMunkee, percent );
	}

	if (staticTextSize)
	{
		UnicodeString sizeString;
		sizeString.format(TheGameText->fetch("GUI:DownloadBytesRatio"), bytesread, totalsize);
		GadgetStaticTextSetText(staticTextSize, sizeString);
	}
	timeLeft = timeleft;
	if (staticTextTime && GadgetStaticTextGetText(staticTextTime).isEmpty()) // only update immediately the first time
	{
		lastUpdate = time(NULL);
		UnicodeString timeString;
		if (timeleft)
		{
			DEBUG_ASSERTCRASH(timeleft > 0, ("Time left is negative!"));
			timeleft = max(1, timeleft);
			Int takenHour, takenMin, takenSec;
			takenHour = timeleft / 60 / 60;
			takenMin = timeleft / 60;
			takenSec = timeleft % 60;
			timeString.format(TheGameText->fetch("GUI:DownloadTimeLeft"), takenHour, takenMin, takenSec);
		}
		else
		{
			reinterpret_cast<DownloadUnicodeStringSetView *>(&timeString)->set(
				reinterpret_cast<const DownloadUnicodeStringSetView &>(
					TheGameText->fetch("GUI:DownloadUnknownTime")));
		}
		GadgetStaticTextSetText(staticTextTime, timeString);
	}
	return ret;
}

HRESULT DownloadManagerMunkee::OnStatusUpdate( Int status )
{
	HRESULT ret = DownloadManager::OnStatusUpdate( status );

	if (staticTextStatus)
	{
		GadgetStaticTextSetText(staticTextStatus, getStatusString());
	}
	return ret;
}

// PUBLIC FUNCTIONS ///////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------
/** Initialize the menu */
//-------------------------------------------------------------------------------------------------
void DownloadMenuInit( WindowLayout *layout, void *userData )
{

	//set keyboard focus to main parent and set modal
	NameKeyType parentID = TheNameKeyGenerator->nameToKey("DownloadMenu.wnd:ParentDownload");
	parent = TheWindowManager->winGetWindowFromId( NULL, parentID );

  // get ids for our children controls
	buttonCancelID = TheNameKeyGenerator->nameToKey( "DownloadMenu.wnd:ButtonCancel" );
	staticTextSizeID = TheNameKeyGenerator->nameToKey( "DownloadMenu.wnd:StaticTextSize" );
	staticTextTimeID = TheNameKeyGenerator->nameToKey( "DownloadMenu.wnd:StaticTextTime" );
	staticTextFileID = TheNameKeyGenerator->nameToKey( "DownloadMenu.wnd:StaticTextFile" );
	staticTextStatusID = TheNameKeyGenerator->nameToKey( "DownloadMenu.wnd:StaticTextStatus" );
	progressBarMunkeeID = TheNameKeyGenerator->nameToKey( "DownloadMenu.wnd:ProgressBarMunkee" );

	staticTextSize = TheWindowManager->winGetWindowFromId( parent, staticTextSizeID );
	staticTextTime = TheWindowManager->winGetWindowFromId( parent, staticTextTimeID );
	staticTextFile = TheWindowManager->winGetWindowFromId( parent, staticTextFileID );
	staticTextStatus = TheWindowManager->winGetWindowFromId( parent, staticTextStatusID );
	progressBarMunkee = TheWindowManager->winGetWindowFromId( parent, progressBarMunkeeID );

	DEBUG_ASSERTCRASH(!TheDownloadManager, ("Download manager already exists"));
	if (TheDownloadManager)
	{
		delete TheDownloadManager;
	}
	TheDownloadManager = NEW DownloadManagerMunkee;

}  // end DownloadMenuInit

//-------------------------------------------------------------------------------------------------
/** menu shutdown method */
//-------------------------------------------------------------------------------------------------
void DownloadMenuShutdown( WindowLayout *layout, void *userData )
{
	DEBUG_ASSERTCRASH(TheDownloadManager, ("No download manager"));
	if (TheDownloadManager)
	{
		delete TheDownloadManager;
		TheDownloadManager = NULL;
	}

	staticTextSize = NULL;
	staticTextTime = NULL;
	staticTextFile = NULL;
	staticTextStatus = NULL;
	progressBarMunkee = NULL;
	parent = NULL;

}  // end DownloadMenuShutdown

//-------------------------------------------------------------------------------------------------
/** menu update method */
//-------------------------------------------------------------------------------------------------
void DownloadMenuUpdate( WindowLayout *layout, void *userData )
{
	if (staticTextTime && !GadgetStaticTextGetText(staticTextTime).isEmpty())
	{
		time_t now = time(NULL);
		if (now <= lastUpdate)
			return;

		lastUpdate = now;

		UnicodeString timeString;
		if (timeLeft)
		{
			DEBUG_ASSERTCRASH(timeLeft > 0, ("Time left is negative!"));
			if (timeLeft < 1)
				timeLeft = 1;
			Int takenHour, takenMin, takenSec;
			takenHour = timeLeft / 60 / 60;
			takenMin = timeLeft / 60;
			takenSec = timeLeft % 60;
			timeString.format(TheGameText->fetch("GUI:DownloadTimeLeft"), takenHour, takenMin, takenSec);
		}
		else
		{
			reinterpret_cast<DownloadUnicodeStringSetView *>(&timeString)->set(
				reinterpret_cast<const DownloadUnicodeStringSetView &>(
					TheGameText->fetch("GUI:DownloadUnknownTime")));
		}
		GadgetStaticTextSetText(staticTextTime, timeString);
	}

}  // end DownloadMenuUpdate 

//-------------------------------------------------------------------------------------------------
/** menu input callback */
//-------------------------------------------------------------------------------------------------
WindowMsgHandledType DownloadMenuInput( GameWindow *window, UnsignedInt msg,
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
						BFMERetailAsciiString buttonName( "DownloadMenu.wnd:ButtonCancel" );
						NameKeyType buttonID = TheNameKeyGenerator->nameToKey( buttonName.str() );
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

}  // end DownloadMenuInput

//-------------------------------------------------------------------------------------------------
// BFME does not call HandleCanceledDownload from the cancel button. It clears one
// byte at +0x259 of the singleton at 0x012F49B4 and goes straight to
// closeDownloadWindow. Nothing else in the image names that singleton, so it and
// the member are named for what the call site proves - an offset and a store of
// zero - and no layout is invented around them.
//-------------------------------------------------------------------------------------------------
class BfmeDownloadState
{
public:
	char m_pad[0x259];
	Bool m_flagAt259;
};

extern BfmeDownloadState *TheBfmeDownloadState;


//-------------------------------------------------------------------------------------------------
/** menu window system callback */
//-------------------------------------------------------------------------------------------------
WindowMsgHandledType DownloadMenuSystem( GameWindow *window, UnsignedInt msg, 
																		 WindowMsgData mData1, WindowMsgData mData2 )
{

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

			break;

		}  // end case

    //----------------------------------------------------------------------------------------------
    case GWM_INPUT_FOCUS:
		{

			// if we're givin the opportunity to take the keyboard focus we must say we want it
			if( mData1 == TRUE )
				*(Bool *)mData2 = TRUE;

			break;

		}  // end input
    //---------------------------------------------------------------------------------------------
		case GBM_SELECTED:
		{
			GameWindow *control = (GameWindow *)mData1;
			Int controlID = control->winGetWindowId();
      
			if( controlID == buttonCancelID )
			{
				if( TheBfmeDownloadState )
					TheBfmeDownloadState->m_flagAt259 = FALSE;
				closeDownloadWindow();
			}  // end if
	
			break;

		}  // end selected

		default:
			return MSG_IGNORED;

	}  // end switch

	return MSG_HANDLED;

} // end DownloadMenuSystem

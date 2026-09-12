// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
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

// FILE: PopupJoinGame.cpp /////////////////////////////////////////////////
//-----------------------------------------------------------------------------
//                                                                          
//                       Electronic Arts Pacific.                          
//                                                                          
//                       Confidential Information                           
//                Copyright (C) 2002 - All Rights Reserved                  
//                                                                          
//-----------------------------------------------------------------------------
//
//	created:	Jul 2002
//
//	Filename: 	PopupJoinGame.cpp
//
//	author:		Matthew D. Campbell
//	
//	purpose:	Contains the Callbacks for the Join Game Popup
//
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
// SYSTEM INCLUDES ////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// USER INCLUDES //////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
#ifndef BFME_POPUP_STRINGBASE_H
#define BFME_POPUP_STRINGBASE_H
template <typename T> struct PopupStringData
{
    int m_refCount;
    int m_length;
    T m_text[1];
};
template <> struct PopupStringData<unsigned short>
{
    unsigned short m_refCount;
    unsigned short m_length;
    unsigned short m_text[1];
};
template <typename T> class StringBase
{
    friend class AsciiString;
    friend class UnicodeString;
public:
    bool isEmpty() const;
    bool isNotEmpty() const;
    bool isNone() const;
    bool isNotNone() const;
    int getLength() const;
    const T *str() const;
    int compareNoCase(const StringBase<T> &other) const;
    void set(const StringBase<T> &other);
    void trim();
protected:
    T *m_text_for_popup() const;
private:
    StringBase() : m_data(0) {}
    StringBase(const T *text);
    StringBase(const StringBase<T> &other);
    ~StringBase();
    void releaseBuffer();
    PopupStringData<T> *m_data;
};
#endif

#ifndef ASCIISTRING_H
#define ASCIISTRING_H
class UnicodeString;
class AsciiString : private StringBase<char>
{
public:
    static AsciiString TheEmptyString;
    AsciiString() : StringBase<char>() {}
    AsciiString(char c);
    AsciiString(const char *text) : StringBase<char>(text) {}
    AsciiString(const AsciiString &other) : StringBase<char>(other) {}
    ~AsciiString() { ((StringBase<char> *)this)->releaseBuffer(); }
    const char *str() const { return m_data ? m_data->m_text : ""; }
    int getLength() const;
    bool isEmpty() const;
    bool isNotEmpty() const;
    bool isNone() const;
    bool isNotNone() const;
    int compareNoCase(const AsciiString &other) const;
    void translate(const UnicodeString &other);
    void set(const AsciiString &other);
    void trim();
    const char *getBufferForRead(int len);
};
inline bool operator==(const AsciiString &a, const AsciiString &b) { return a.compareNoCase(b) == 0; }
inline bool operator!=(const AsciiString &a, const AsciiString &b) { return !(a == b); }
inline bool operator<(const AsciiString &a, const AsciiString &b) { return a.compareNoCase(b) < 0; }
#endif

#ifndef UNICODESTRING_H
#define UNICODESTRING_H
class AsciiString;
class UnicodeString : private StringBase<unsigned short>
{
public:
    static UnicodeString TheEmptyString;
    UnicodeString() : StringBase<unsigned short>() {}
    UnicodeString(unsigned short c);
    explicit UnicodeString(const unsigned short *text) : StringBase<unsigned short>(text) {}
    UnicodeString(const UnicodeString &other) : StringBase<unsigned short>(other) {}
    ~UnicodeString() { ((StringBase<unsigned short> *)this)->releaseBuffer(); }
    int getLength() const;
    bool isEmpty() const { return m_data == 0 || m_data->m_text[0] == 0; }
    bool isNotEmpty() const { return !isEmpty(); }
    int compareNoCase(const UnicodeString &other) const;
    const unsigned short *str() const { return m_data ? m_data->m_text : (const unsigned short *)L""; }
    void set(const UnicodeString &other) { ((StringBase<unsigned short> *)this)->set(*(const StringBase<unsigned short> *)&other); }
    void trim();
    void clear();
    void translate(const AsciiString &other);
};
inline bool operator==(const UnicodeString &a, const UnicodeString &b) { return a.compareNoCase(b) == 0; }
inline bool operator!=(const UnicodeString &a, const UnicodeString &b) { return !(a == b); }
inline bool operator<(const UnicodeString &a, const UnicodeString &b) { return a.compareNoCase(b) < 0; }
#endif


#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/GlobalData.h"
#include "Common/NameKeyGenerator.h"
#include "GameClient/WindowLayout.h"
#include "GameClient/Gadget.h"
#include "GameClient/KeyDefs.h"
#include "GameClient/GadgetTextEntry.h"
#include "GameClient/GadgetStaticText.h"
#include "GameNetwork/GameSpy/Peerdefs.h"
#include "GameNetwork/GameSpy/PeerThread.h"
#include "GameNetwork/GameSpyOverlay.h"


//-----------------------------------------------------------------------------
// DEFINES ////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------

namespace PopupJoinGameState
{
NameKeyType parentPopupID = NAMEKEY_INVALID;
NameKeyType textEntryGamePasswordID = NAMEKEY_INVALID;
NameKeyType buttonCancelID = NAMEKEY_INVALID;

GameWindow *parentPopup = NULL;
GameWindow *textEntryGamePassword = NULL;

}
using PopupJoinGameState::parentPopupID;
using PopupJoinGameState::textEntryGamePasswordID;
using PopupJoinGameState::buttonCancelID;
using PopupJoinGameState::parentPopup;
using PopupJoinGameState::textEntryGamePassword;

void joinGame( AsciiString password );

//-----------------------------------------------------------------------------
// PUBLIC FUNCTIONS ///////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
/** Initialize the PopupHostGameInit menu */
//-------------------------------------------------------------------------------------------------
// Byte-verified initialization is in PopupJoinGameInit.cpp; state is shared above.


//-------------------------------------------------------------------------------------------------
/** PopupHostGameInput callback */
//-------------------------------------------------------------------------------------------------
WindowMsgHandledType PopupJoinGameInput( GameWindow *window, UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2 )
{
	switch( msg ) 
	{

		// --------------------------------------------------------------------------------------------
		case GWM_CHAR:
		{
			UnsignedByte key = mData1;
			UnsignedByte state = mData2;
//			if (buttonPushed)
//				break;

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
						GameSpyCloseOverlay(GSOVERLAY_GAMEPASSWORD);
						SetLobbyAttemptHostJoin( FALSE );
						parentPopup = NULL;
					}  // end if

					// don't let key fall through anywhere else
					return MSG_HANDLED;

				}  // end escape

			}  // end switch( key )

		}  // end char

	}  // end switch( msg )

	return MSG_IGNORED;

}

//-------------------------------------------------------------------------------------------------
/** PopupHostGameSystem callback */
//-------------------------------------------------------------------------------------------------
WindowMsgHandledType PopupJoinGameSystem( GameWindow *window, UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2 )
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

		//---------------------------------------------------------------------------------------------
		case GBM_SELECTED:
		{
			GameWindow *control = (GameWindow *)mData1;
			Int controlID = control->winGetWindowId();
			if (controlID == buttonCancelID)
			{
				GameSpyCloseOverlay(GSOVERLAY_GAMEPASSWORD);
				SetLobbyAttemptHostJoin( FALSE );
				parentPopup = NULL;
			}
			break;
		}

    //----------------------------------------------------------------------------------------------
    case GWM_INPUT_FOCUS:
		{

			// if we're givin the opportunity to take the keyboard focus we must say we want it
			if( mData1 == TRUE )
				*(Bool *)mData2 = TRUE;

			break;

		}  // end input
    //---------------------------------------------------------------------------------------------
		case GEM_EDIT_DONE:
		{
			GameWindow *control = (GameWindow *)mData1;
			Int controlID = control->winGetWindowId();
     
      if( controlID == textEntryGamePasswordID )
			{
				// read the user's input and clear the entry box
				UnicodeString txtInput;
				txtInput.set(GadgetTextEntryGetText( textEntryGamePassword ));
				GadgetTextEntrySetText(textEntryGamePassword, UnicodeString::TheEmptyString);
				txtInput.trim();
				if (!txtInput.isEmpty())
				{
					AsciiString munkee;
					munkee.translate(txtInput);
					joinGame(munkee);
				}
			}
			break;
		}
		default:
			return MSG_IGNORED;

	}  // end switch

	return MSG_HANDLED;

}


//-----------------------------------------------------------------------------
// PRIVATE FUNCTIONS //////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------

// The byte-verified request producer is in PopupJoinGameJoin.cpp.


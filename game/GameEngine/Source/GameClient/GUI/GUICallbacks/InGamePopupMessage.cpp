// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/displaystring /Iinputs/reference/shims/displaystringmanager /Iinputs/reference/shims/stringbaseunicode /Iinputs/reference/shims/stringbaseascii /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Igame/Libraries/Source/WWVegas/WWLib
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

// FILE: InGamePopupMessage.cpp /////////////////////////////////////////////////
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
//	Filename: 	InGamePopupMessage.cpp
//
//	author:		Chris Huybregts
//	
//	purpose:	Init, input, and system for the in game message popup
//
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
// SYSTEM INCLUDES ////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// USER INCLUDES //////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/GlobalData.h"
#include "Common/NameKeyGenerator.h"
#include "Common/Version.h"
#include "Common/MessageStream.h"
#include "GameClient/WindowLayout.h"
#include "GameClient/Gadget.h"
#include "GameClient/GadgetStaticText.h"
#include "GameClient/KeyDefs.h"
#include "GameClient/GameWindowManager.h"
#include "GameClient/InGameUI.h"
#include "GameClient/DisplayStringManager.h"

//-----------------------------------------------------------------------------
// DEFINES ////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------

static NameKeyType parentID = NAMEKEY_INVALID;
static NameKeyType staticTextMessageID = NAMEKEY_INVALID;
static NameKeyType buttonOkID = NAMEKEY_INVALID;


static GameWindow *parent = NULL;
static GameWindow *staticTextMessage = NULL;
static GameWindow *buttonOk = NULL;


static Bool pause = FALSE;

// DisplayString::getSize is vtable slot 0x3C in BFME; the displaystring shim
// puts it at 0x30. One call site, so it is spelled here rather than in the
// shim, which other files depend on as it stands.
class BfmeVirtualDisplayString
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
	virtual void getSize( Int *width, Int *height ) = 0;
};

// InGameUI::getPopupMessageData is an inline over m_popupMessageData, and BFME
// holds that member at +0x12A8 where the vendored header puts it at +0x1D14.
// Read at the retail offset rather than moving the header, which nearly every
// GameClient source includes.
static PopupMessageData *bfmePopupMessageData( InGameUI *ui )
{
	return *(PopupMessageData **)((char *)ui + 0x12A8);
}
//-----------------------------------------------------------------------------
// PUBLIC FUNCTIONS ///////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
/** Initialize the InGamePopupMessageInit menu */
//-------------------------------------------------------------------------------------------------
void InGamePopupMessageInit( WindowLayout *layout, void *userData )
{


	parentID = TheNameKeyGenerator->nameToKey(AsciiString("InGamePopupMessage.wnd:InGamePopupMessageParent"));
	parent = TheWindowManager->winGetWindowFromId(NULL, parentID);

	staticTextMessageID = TheNameKeyGenerator->nameToKey(AsciiString("InGamePopupMessage.wnd:StaticTextMessage"));
	staticTextMessage = TheWindowManager->winGetWindowFromId(parent, staticTextMessageID);
	buttonOkID = TheNameKeyGenerator->nameToKey(AsciiString("InGamePopupMessage.wnd:ButtonOk"));
	buttonOk = TheWindowManager->winGetWindowFromId(parent, buttonOkID);
	
	PopupMessageData *pMData = bfmePopupMessageData( TheInGameUI );
	
	if(!pMData)
	{
		DEBUG_ASSERTCRASH(pMData, ("We're in InGamePopupMessage without a pointer to pMData\n") );
		///< @todo: add a call to the close this bitch method when I implement it CLH
		return;
	}
	
	DisplayString *tempString = TheDisplayStringManager->newDisplayString();
	tempString->setText(pMData->message);
	tempString->setFont(staticTextMessage->winGetFont());
	tempString->setWordWrap(pMData->width - 14);
	Int width, height;
	((BfmeVirtualDisplayString *)tempString)->getSize(&width, &height);
	TheDisplayStringManager->freeDisplayString(tempString);
	
	GadgetStaticTextSetText(staticTextMessage, pMData->message);
	// set the positions/sizes
	Int widthOk, heightOk;
	buttonOk->winGetSize(&widthOk, &heightOk);
	parent->winSetPosition( pMData->x, pMData->y);
	parent->winSetSize( pMData->width, height + 7 + 2 + 2 + heightOk + 2 );
	staticTextMessage->winSetPosition(  2,  2);
	staticTextMessage->winSetSize( pMData->width - 4, height + 7);
	buttonOk->winSetPosition(pMData->width - widthOk - 2, height + 7 + 2 + 2);
	staticTextMessage->winSetEnabledTextColors(pMData->textColor, 0);
	pause = pMData->pause;
	if(pMData->pause)
		TheWindowManager->winSetModal( parent );
	
	TheWindowManager->winSetFocus( parent );

	parent->winHide(FALSE);
	parent->winBringToTop();
}

//-------------------------------------------------------------------------------------------------
/** InGamePopupMessageInput callback */
//-------------------------------------------------------------------------------------------------
WindowMsgHandledType InGamePopupMessageInput( GameWindow *window, UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2 )
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
					case KEY_ENTER:
					case KEY_ESC:
					{
						
						//
						// send a simulated selected event to the parent window of the
						// back/exit button
						//
						if( BitTest( state, KEY_STATE_UP ) )
						{
							TheWindowManager->winSendSystemMsg( window, GBM_SELECTED, 
																								(WindowMsgData)buttonOk, buttonOkID );
	
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
/** InGamePopupMessageSystem callback */
//-------------------------------------------------------------------------------------------------
WindowMsgHandledType InGamePopupMessageSystem( GameWindow *window, UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2 )
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
     
      if( controlID == buttonOkID )
			{
				if(!pause)
				{
					// Two BFME drifts on one line, both spelled here rather than in
					// the shared headers. MSG_CLEAR_INGAME_POPUP_MESSAGE is 0x442,
					// not the vendored enum's 0x440 -- BFME added two messages
					// ahead of it. And appendMessage is vtable slot 13, [vtbl+0x34],
					// where the vendored MessageStream puts it at slot 10.
					struct AppendThunk { void Call(int); };
					typedef void (AppendThunk::*AppendFn)(int);
					void **vtbl = *reinterpret_cast<void ***>(TheMessageStream);
					union { void *asVoid; AppendFn asMember; } fnCast;
					fnCast.asVoid = vtbl[13];
					(reinterpret_cast<AppendThunk *>(TheMessageStream)->*fnCast.asMember)(0x442);
				}
				else
					TheInGameUI->clearPopupMessageData();
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

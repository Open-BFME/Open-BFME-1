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

///////////////////////////////////////////////////////////////////////////////////////
// FILE: WOLLoginMenu.cpp
// Author: Chris Huybregts, November 2001
// Description: Lan Lobby Menu
///////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/GameEngine.h"
#include "GameClient/WindowLayout.h"
#include "GameClient/Gadget.h"
#include "GameClient/Shell.h"
#include "GameClient/KeyDefs.h"
#include "GameClient/GameWindowManager.h"
#include "GameClient/GadgetListBox.h"
#include "GameClient/GadgetTextEntry.h"

//-------------------------------------------------------------------------------------------------
// WindowLayout::hide is virtual in BFME (vtable slot 0x10) and non-virtual in
// the vendored ZH header. Editing the header would touch every TU that includes
// it, so the drift is spelled TU-locally: a shim whose fifth virtual lands on
// that slot, and a cast at each call site.
//-------------------------------------------------------------------------------------------------
// BFME closes WOLStatusMenuInit by clearing one GameWindow field the vendored
// header does not describe: retail reads parentWOLStatus back and, when it is
// non-null, stores zero at +0x1F4. Only the offset is recoverable from the
// call site, so the field is named for it rather than guessed at.
class BfmeGameWindowFields
{
public:
	char m_pad[0x1F4];
	void *m_fieldAt1F4;
};

class BfmeVirtualHideLayout
{
public:
	virtual void slot0() = 0;
	virtual void slot4() = 0;
	virtual void slot8() = 0;
	virtual void slotC() = 0;
	virtual void hide( Bool immediate ) = 0;
};

//#include "GameNetwork/WOL.h"
//#include "GameNetwork/WOLmenus.h"



// PRIVATE DATA ///////////////////////////////////////////////////////////////////////////////////
// window ids ------------------------------------------------------------------------------
static NameKeyType parentWOLStatusID = NAMEKEY_INVALID;
static NameKeyType buttonDisconnectID = NAMEKEY_INVALID;

// Window Pointers ------------------------------------------------------------------------
static GameWindow *parentWOLStatus = NULL;
static GameWindow *buttonDisconnect = NULL;
GameWindow *progressTextWindow = NULL;

//-------------------------------------------------------------------------------------------------
/** Initialize the WOL Status Menu */
//-------------------------------------------------------------------------------------------------
void WOLStatusMenuInit( WindowLayout *layout, void *userData )
{
	parentWOLStatusID = TheNameKeyGenerator->nameToKey( AsciiString( "WOLStatusMenu.wnd:WOLStatusMenuParent" ) );
	buttonDisconnectID = TheNameKeyGenerator->nameToKey( AsciiString( "WOLStatusMenu.wnd:ButtonDisconnect" ) );
	parentWOLStatus = TheWindowManager->winGetWindowFromId( NULL, parentWOLStatusID );
	buttonDisconnect = TheWindowManager->winGetWindowFromId( NULL,  buttonDisconnectID);

	progressTextWindow = TheWindowManager->winGetWindowFromId( NULL,
		TheNameKeyGenerator->nameToKey( AsciiString( "WOLStatusMenu.wnd:ListboxStatus" ) ) );
	
	// Show Menu
	((BfmeVirtualHideLayout *)layout)->hide( FALSE );

	// Set Keyboard to Main Parent
	TheWindowManager->winSetFocus( parentWOLStatus );

	if( parentWOLStatus )
		((BfmeGameWindowFields *)parentWOLStatus)->m_fieldAt1F4 = NULL;

	//progressLayout = TheShell->top();

	//WOL::raiseWOLMessageBox();
} // WOLStatusMenuInit

//-------------------------------------------------------------------------------------------------
/** WOL Status Menu shutdown method */
//-------------------------------------------------------------------------------------------------
void WOLStatusMenuShutdown( WindowLayout *layout, void *userData )
{

	// hide menu
	((BfmeVirtualHideLayout *)layout)->hide( TRUE );

	// our shutdown is complete
	TheShell->shutdownComplete( layout );

	//progressLayout = NULL;

	//WOL::raiseWOLMessageBox();
}  // WOLStatusMenuShutdown


//-------------------------------------------------------------------------------------------------
/** WOL Status Menu update method */
//-------------------------------------------------------------------------------------------------
void WOLStatusMenuUpdate( WindowLayout * layout, void *userData)
{
	//if (WOL::TheWOL)
		//WOL::TheWOL->update();
}// WOLStatusMenuUpdate

//-------------------------------------------------------------------------------------------------
/** WOL Status Menu input callback */
//-------------------------------------------------------------------------------------------------
WindowMsgHandledType WOLStatusMenuInput( GameWindow *window, UnsignedInt msg,
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
																							(WindowMsgData)buttonDisconnect, buttonDisconnectID );

					}  // end if

					// don't let key fall through anywhere else
					return MSG_HANDLED;

				}  // end escape

			}  // end switch( key )

		}  // end char

	}  // end switch( msg )

	return MSG_IGNORED;
}// WOLStatusMenuInput

//-------------------------------------------------------------------------------------------------
/** WOL Status Menu window system callback */
//-------------------------------------------------------------------------------------------------
WindowMsgHandledType WOLStatusMenuSystem( GameWindow *window, UnsignedInt msg, 
														 WindowMsgData mData1, WindowMsgData mData2 )
{
	UnicodeString txtInput;

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

		case GBM_SELECTED:
			{
				/*
				GameWindow *control = (GameWindow *)mData1;
				Int controlID = control->winGetWindowId();

				if ( controlID == buttonDisconnectID )
				{
					//TheShell->pop();
					if (WOL::TheWOL->setState( WOL::WOLAPI_FATAL_ERROR ))
					{
						WOL::TheWOL->addCommand( WOL::WOLCOMMAND_RESET );  // don't display an error, log out, or anything
					}

				} //if ( controlID == buttonDisconnect )
				*/
				break;
			}// case GBM_SELECTED:
	
		case GEM_EDIT_DONE:
			{
				break;
			}
		default:
			return MSG_IGNORED;

	}//Switch

	return MSG_HANDLED;
}// WOLStatusMenuSystem

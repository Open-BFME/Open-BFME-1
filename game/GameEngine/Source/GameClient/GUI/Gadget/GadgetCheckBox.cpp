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

// FILE: CheckBox.cpp /////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
//                                                                          
//                       Westwood Studios Pacific.                          
//                                                                          
//                       Confidential Information                           
//                Copyright (C) 2001 - All Rights Reserved                  
//                                                                          
//-----------------------------------------------------------------------------
//
// Project:   RTS3
//
// File name: CheckBox.cpp
//
// Created:   Colin Day, June 2001
//
// Desc:      Checkbox GUI control
//
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////

// SYSTEM INCLUDES ////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

// USER INCLUDES //////////////////////////////////////////////////////////////
#include "Common/Language.h"
#include "GameClient/Gadget.h"
#include "GameClient/GameWindowManager.h"
#include "GameClient/Keyboard.h"

// DEFINES ////////////////////////////////////////////////////////////////////

// PRIVATE TYPES //////////////////////////////////////////////////////////////

// PRIVATE DATA ///////////////////////////////////////////////////////////////

// PUBLIC DATA ////////////////////////////////////////////////////////////////

// PRIVATE PROTOTYPES /////////////////////////////////////////////////////////

// PRIVATE FUNCTIONS //////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS ///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//-------------------------------------------------------------------------------------------------
// Two BFME drifts the checkbox input callback needs. winNextTab and winPrevTab
// are vtable slots 0x94 and 0x98 of GameWindowManager, and the tab direction
// comes from a shift flag: retail reads bit 0x10 of the byte at +8 of the
// keyboard singleton at 0x012F4C50. Only the offset and the bit are
// recoverable from the call site, so the reader is named for them.
//-------------------------------------------------------------------------------------------------
class BfmeVirtualTabWindowManager
{
public:
	virtual void slot000() = 0;
	virtual void slot004() = 0;
	virtual void slot008() = 0;
	virtual void slot00C() = 0;
	virtual void slot010() = 0;
	virtual void slot014() = 0;
	virtual void slot018() = 0;
	virtual void slot01C() = 0;
	virtual void slot020() = 0;
	virtual void slot024() = 0;
	virtual void slot028() = 0;
	virtual void slot02C() = 0;
	virtual void slot030() = 0;
	virtual void slot034() = 0;
	virtual void slot038() = 0;
	virtual void slot03C() = 0;
	virtual void slot040() = 0;
	virtual void slot044() = 0;
	virtual void slot048() = 0;
	virtual void slot04C() = 0;
	virtual void slot050() = 0;
	virtual void slot054() = 0;
	virtual void slot058() = 0;
	virtual void slot05C() = 0;
	virtual void slot060() = 0;
	virtual void slot064() = 0;
	virtual void slot068() = 0;
	virtual void slot06C() = 0;
	virtual void slot070() = 0;
	virtual void slot074() = 0;
	virtual void slot078() = 0;
	virtual void slot07C() = 0;
	virtual void slot080() = 0;
	virtual void slot084() = 0;
	virtual void slot088() = 0;
	virtual void slot08C() = 0;
	virtual void slot090() = 0;
	virtual void winNextTab( GameWindow *window ) = 0;   // slot 0x94
	virtual void winPrevTab( GameWindow *window ) = 0;   // slot 0x98
};

class BfmeKeyboardModifiers
{
public:
	char m_pad[8];
	unsigned char m_flagsAt8;
};

extern BfmeKeyboardModifiers *TheBfmeKeyboardModifiers;

static Bool bfmeShiftHeld( void )
{
	return BitTest( TheBfmeKeyboardModifiers->m_flagsAt8, 0x10 );
}


// GadgetCheckBoxInput ========================================================
/** Handle input for check box */
//=============================================================================
WindowMsgHandledType GadgetCheckBoxInput( GameWindow *window, UnsignedInt msg,
													WindowMsgData mData1, WindowMsgData mData2 )
{
	WinInstanceData *instData = window->winGetInstanceData();

	switch( msg ) 
	{

		// ------------------------------------------------------------------------
		case GWM_MOUSE_ENTERING:
		{

			if( BitTest( instData->getStyle(), GWS_MOUSE_TRACK ) ) 
			{

				BitSet( instData->m_state, WIN_STATE_HILITED );
				TheWindowManager->winSendSystemMsg( window->winGetOwner(), 
																						GBM_MOUSE_ENTERING,
																						(WindowMsgData)window, 
																						mData1 );
				//TheWindowManager->winSetFocus( window );

			}  // end if
			break;

		}  // end mouse entering

		// ------------------------------------------------------------------------
		case GWM_MOUSE_LEAVING:
		{

			if( BitTest( instData->getStyle(), GWS_MOUSE_TRACK ) ) 
			{

				BitClear( instData->m_state, WIN_STATE_HILITED );
				TheWindowManager->winSendSystemMsg( window->winGetOwner(), 
																						GBM_MOUSE_LEAVING,
																						(WindowMsgData)window, 
																						mData1 );
			}  // end if
			break;

		}  // end mouse leaving

		// ------------------------------------------------------------------------
		case GWM_LEFT_DRAG:
		{

			TheWindowManager->winSendSystemMsg( window->winGetOwner(), GGM_LEFT_DRAG,
																					(WindowMsgData)window, mData1 );
			break;

		}  // end left drag

		// ------------------------------------------------------------------------
		case GWM_LEFT_DOWN:
		{

			break;

		}  // end left down

		// ------------------------------------------------------------------------
		case GWM_LEFT_UP:
		{

			if( BitTest( instData->getState(), WIN_STATE_HILITED ) == FALSE )
			{
				// this up click was not meant for this button
				return MSG_IGNORED;
			}

			// Toggle the check state
			instData->m_state ^= WIN_STATE_SELECTED;

			TheWindowManager->winSendSystemMsg( window->winGetOwner(), GBM_SELECTED,
																					(WindowMsgData)window, mData1 );


			break;

		}  // end left up and left click

		// ------------------------------------------------------------------------
		case GWM_RIGHT_DOWN:
		{

			break;
		}  // end right down

		//-------------------------------------------------------------------------
		case GWM_RIGHT_UP:
		{
			// Need to be specially marked to care about right mouse events
			if( BitTest( instData->getState(), WIN_STATE_SELECTED ) )
			{
				TheWindowManager->winSendSystemMsg( instData->getOwner(), GBM_SELECTED_RIGHT,
																						(WindowMsgData)window, mData1 );

				BitClear( instData->m_state, WIN_STATE_SELECTED );
			}
			else
			{
				// this up click was not meant for this button
				return MSG_IGNORED;
			}
			break;
		}  // end right up or right click

		// ------------------------------------------------------------------------
		case GWM_CHAR:
		{

			switch( mData1 ) 
			{

				// --------------------------------------------------------------------
				case KEY_ENTER:
				case KEY_SPACE:
				{

					if( BitTest( mData2, KEY_STATE_DOWN ) )
					{
						// Toggle the check state
						instData->m_state ^= WIN_STATE_SELECTED;

						TheWindowManager->winSendSystemMsg( window->winGetOwner(), 
																								GBM_SELECTED,
																								(WindowMsgData)window, 
																								0 );
					}  //end if
					break;

				}  // end enter/space

				// --------------------------------------------------------------------
				// BFME keeps only TAB here - no DOWN/RIGHT and no UP/LEFT case at all -
				// and picks the direction from the shift modifier instead. Three cases
				// is why retail compares 0x0F, 0x1C and 0x39 in a chain where the Zero
				// Hour set compiles to a jump table.
				case KEY_TAB:
				{

					if( BitTest( mData2, KEY_STATE_DOWN ) )
					{
						if( bfmeShiftHeld() )
							((BfmeVirtualTabWindowManager *)TheWindowManager)->winPrevTab(window);
						else
							((BfmeVirtualTabWindowManager *)TheWindowManager)->winNextTab(window);
					}
					break;

				}  // end tab

				// --------------------------------------------------------------------
				default:
				{

					return MSG_IGNORED;

				}  // end default

			}  // end switch

			break;

		}  // end char msg

		// ------------------------------------------------------------------------
		default:
		{

			return MSG_IGNORED;

		}  // end default

	}  // end switch( msg )

	return MSG_HANDLED;

}  // end GadgetCheckBoxInput

// GadgetCheckBoxSystem =======================================================
/** Handle system messages for check box */
//=============================================================================
WindowMsgHandledType GadgetCheckBoxSystem( GameWindow *window, UnsignedInt msg,
													 WindowMsgData mData1, WindowMsgData mData2 )
{
	WinInstanceData *instData = window->winGetInstanceData();

	switch( msg ) 
	{
		// ------------------------------------------------------------------------	
		case GGM_SET_LABEL:
		{
			// BFME dispatches this base operation directly; virtual dispatch changes the retail call shape.
			window->GameWindow::winSetText( *(UnicodeString*)mData1 );
			break;
		}

		// ------------------------------------------------------------------------
		case GWM_CREATE:
			break;

		// ------------------------------------------------------------------------
		case GWM_DESTROY:
			break;

		// ------------------------------------------------------------------------
		case GWM_INPUT_FOCUS:

			if( mData1 == FALSE )
				BitClear( instData->m_state, WIN_STATE_HILITED );
			else
				BitSet( instData->m_state, WIN_STATE_HILITED );
			TheWindowManager->winSendSystemMsg( window->winGetOwner(), 
																					GGM_FOCUS_CHANGE,
																					mData1, 
																					window->winGetWindowId() );
			if( mData1 == FALSE )
				*(Bool*)mData2 = FALSE;
			else
				*(Bool*)mData2 = TRUE;
			
			break;

		default: 
			return MSG_IGNORED;

	}  // end switch msg

	return MSG_HANDLED;

}  // end GadgetCheckBoxSystem

// GadgetCheckBoxSetText ======================================================
/** Set the text for the control */
//=============================================================================
void GadgetCheckBoxSetText( GameWindow *g, UnicodeString text )
{

	// sanity
	if( g == NULL )
		return;

	TheWindowManager->winSendSystemMsg( g, GGM_SET_LABEL, (WindowMsgData)&text, 0 );

}  // end GadgetCheckBoxSetText

// GadgetCheckBoxSetChecked ============================================
//=============================================================================
/** Set the check state for the check box */
//=============================================================================
void GadgetCheckBoxSetChecked( GameWindow *g, Bool isChecked)
{
	WinInstanceData *instData = g->winGetInstanceData();
	if (isChecked)
	{
		BitSet(instData->m_state,  WIN_STATE_SELECTED);
	}
	else
	{
		BitClear(instData->m_state,  WIN_STATE_SELECTED);
	}

	TheWindowManager->winSendSystemMsg( g->winGetOwner(), GBM_SELECTED,
																					(WindowMsgData)g, 0 );

}

// GadgetCheckBoxToggle ============================================
//=============================================================================
/** Toggle the check state for the check box */
//=============================================================================
void GadgetCheckBoxToggle( GameWindow *g)
{
	WinInstanceData *instData = g->winGetInstanceData();
	Bool isChecked = BitTest(instData->m_state, WIN_STATE_SELECTED);
	if (isChecked)
	{
		BitClear(instData->m_state,  WIN_STATE_SELECTED);
	}
	else
	{
		BitSet(instData->m_state,  WIN_STATE_SELECTED);
	}

	TheWindowManager->winSendSystemMsg( g->winGetOwner(), GBM_SELECTED,
																					(WindowMsgData)g, 0 );

}

// GadgetCheckBoxIsChecked ======================================================
/** Check the check state */
//=============================================================================
Bool GadgetCheckBoxIsChecked( GameWindow *g )
{
	WinInstanceData *instData = g->winGetInstanceData();
	return (BitTest(instData->m_state, WIN_STATE_SELECTED));
}

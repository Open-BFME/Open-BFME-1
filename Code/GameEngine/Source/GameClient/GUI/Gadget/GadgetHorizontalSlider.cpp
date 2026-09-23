// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
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

// FILE: HorizontalSlider.cpp /////////////////////////////////////////////////
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
// File name: HorizontalSlider.cpp
//
// Created:   Colin Day, June 2001
//
// Desc:      Horizontal GUI slider
//
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////

// SYSTEM INCLUDES ////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

// USER INCLUDES //////////////////////////////////////////////////////////////
#include "Common/Language.h"
#include "GameClient/Keyboard.h"
#include "Gameclient/GameWindowManager.h"
#include "GameClient/Gadget.h"
#include "GameClient/GadgetSlider.h"

// DEFINES ////////////////////////////////////////////////////////////////////

// PRIVATE TYPES //////////////////////////////////////////////////////////////

// PRIVATE DATA ///////////////////////////////////////////////////////////////

// PUBLIC DATA ////////////////////////////////////////////////////////////////

// PRIVATE PROTOTYPES /////////////////////////////////////////////////////////

// PRIVATE FUNCTIONS //////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS ///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

// Identity: retail callback table RVA 0x00EA9750 pairs literal VA 0x010871B0
// "GadgetHorizontalSliderInput" with ILT RVA 0x00032943 -> 0x004B4FF0.
// GadgetHorizontalSliderInput ================================================
/** Handle input for horizontal slider */
//=============================================================================
WindowMsgHandledType GadgetHorizontalSliderInput( GameWindow *window, UnsignedInt msg,
																	WindowMsgData mData1, WindowMsgData mData2 )
{
	SliderData *s = (SliderData *)window->winGetUserData();
	WinInstanceData *instData = window->winGetInstanceData();
	ICoord2D size, childSize, childCenter;
	window->winGetSize( &size.x, &size.y );
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
																						0 );
				//TheWindowManager->winSetFocus( window );

			}  // end if
			
			if(window->winGetChild() && BitTest(window->winGetChild()->winGetStyle(),GWS_PUSH_BUTTON) )
			{
				WinInstanceData *instDataChild = window->winGetChild()->winGetInstanceData();
				BitSet(instDataChild->m_state, WIN_STATE_HILITED);
			}

			break;

		}  //  end mouse entering

		// ------------------------------------------------------------------------
		case GWM_MOUSE_LEAVING:
		{

			if( BitTest( instData->getStyle(), GWS_MOUSE_TRACK )) 
			{

				BitClear( instData->m_state, WIN_STATE_HILITED );
				TheWindowManager->winSendSystemMsg( window->winGetOwner(), 
																						GBM_MOUSE_LEAVING,
																						(WindowMsgData)window, 
																						0 );
			}  // end if
			if(window->winGetChild() && BitTest(window->winGetChild()->winGetStyle(),GWS_PUSH_BUTTON) )
			{
				WinInstanceData *instDataChild = window->winGetChild()->winGetInstanceData();
				BitClear(instDataChild->m_state, WIN_STATE_HILITED);
			}

			break;

		}  // end mouse leaving

		// ------------------------------------------------------------------------	
		case GWM_LEFT_DRAG:

			if( BitTest( instData->getStyle(), GWS_MOUSE_TRACK ) )
				TheWindowManager->winSendSystemMsg( window->winGetOwner(), 
																						GGM_LEFT_DRAG,
																						(WindowMsgData)window, 
																						mData1 );
			break;

		// ------------------------------------------------------------------------
		case GWM_LEFT_DOWN:
			break;

		// ------------------------------------------------------------------------
		case GWM_LEFT_UP:
		{
			Int x, y;
			Int mousex = mData1 & 0xFFFF;
//			Int mousey = mData1 >> 16;
			
			GameWindow *child = window->winGetChild();
			Int pageClickSize, clickPos;

			window->winGetScreenPosition( &x, &y );
	
			child->winGetSize( &childSize.x, &childSize.y );
			child->winGetPosition( &childCenter.x, &childCenter.y );
			childCenter.x += childSize.x / 2;
			childCenter.y += childSize.y / 2;

			//
			// when you click on the slider, but not the button, we will jump
			// the slider position up/down by this much
			//
			pageClickSize = size.x / 5;

			clickPos = mousex - x;
			if( clickPos >= childCenter.x )
			{

				clickPos = childCenter.x + pageClickSize;
				if( clickPos > mousex - x )
					clickPos = mousex - x;

			}  // end if
			else
			{

				clickPos = childCenter.x - pageClickSize;
				if( clickPos < mousex - x )
					clickPos = mousex - x;

			}  // end else

			// keep it all valid to the window
			Int clampOrigin = x - childSize.x / 2;
			if( clickPos > clampOrigin + size.x )
				clickPos = clampOrigin + size.y;
			if( clickPos < childSize.x / 2 )
				clickPos = childSize.x / 2;

			child->winSetPosition( clickPos - childSize.x / 2, 0);
			TheWindowManager->winSendSystemMsg( window, GGM_LEFT_DRAG, 0, mData1 );
			// BFME notifies the owner after a click on the track (retail 0x004B525E).
			TheWindowManager->winSendSystemMsg(window->winGetOwner(), 0x4010, (WindowMsgData)window, 0);
			break;

		}  // end left up, left click

		// ------------------------------------------------------------------------
		case GWM_CHAR:
		{

			switch( mData1 )
			{

				// --------------------------------------------------------------------
				case KEY_RIGHT:
					if( BitTest( mData2, KEY_STATE_DOWN ) )
					{

						if( s->position > s->minVal + 1 ) 
						{
							GameWindow *child = window->winGetChild();

							s->position -= 2;
							TheWindowManager->winSendSystemMsg( window->winGetOwner(),
																									(GadgetGameMessage)0x400C,
																									(WindowMsgData)window, 
																									s->position );

							// Translate to window coords
							child->winSetPosition( (Int)((s->position - s->minVal) * s->numTicks), 0 );

						}  // end if

					}  // if key down

					break;

				// --------------------------------------------------------------------
				case KEY_LEFT:

					if( BitTest( mData2, KEY_STATE_DOWN ) )
					{

						if( s->position < s->maxVal - 1 ) 
						{
							GameWindow *child = window->winGetChild();

							s->position += 2;
							TheWindowManager->winSendSystemMsg( window->winGetOwner(), 
																									(GadgetGameMessage)0x400C,
																									(WindowMsgData)window, 
																									s->position );

							// Translate to window coords
							child->winSetPosition( (Int)((s->position - s->minVal) * s->numTicks),0 );

						}

					}  // end if key down

					break;

				// --------------------------------------------------------------------
				case KEY_TAB:

					if( BitTest( mData2, KEY_STATE_DOWN ) )
					{
						if (TheKeyboard->getModifierFlags() & KEY_STATE_LSHIFT)
							TheWindowManager->winPrevTab(window);
						else
							TheWindowManager->winNextTab(window);
					}
					break;

				// --------------------------------------------------------------------
				default:
					return MSG_IGNORED;

			}  // end switch( mData1 )

			break;

		}  // end char

		// ------------------------------------------------------------------------
		default:
			return MSG_IGNORED;

	}

	return MSG_HANDLED;

}  // end GadgetHorizontalSliderInput


// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
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
// BFME's ICoord2D has a user-declared empty inline constructor (its
// out-of-line copy is ??0ICoord2D@@QAE@XZ at 0x00083360); the Zero Hour
// headers expose a plain aggregate, which packs the slider's coordinate
// locals on different stack slots.  Hide that one and declare BFME's below.
#define ICoord2D ZeroHourPlainICoord2D
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

// USER INCLUDES //////////////////////////////////////////////////////////////
#include "Common/Language.h"
#include "GameClient/Keyboard.h"
#include "Gameclient/GameWindowManager.h"
#include "GameClient/Gadget.h"
#include "GameClient/GadgetSlider.h"
#undef ICoord2D

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
namespace
{
	struct ICoord2D
	{
		Int x, y;
		ICoord2D() {}
	};
}

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


// Identity: retail FunctionLexicon row VA 0x012A947C pairs literal VA
// 0x01087800 "GadgetHorizontalSliderSystem" with ILT VA 0x00437367 ->
// 0x004B5530.  BFME clamps the drag against the full track edges using half
// the thumb width, parks the thumb at the right edge by track minus thumb
// size, and adds the 0x4010 owner notification on selection.
// GadgetHorizontalSliderSystem ===============================================
/** Handle system messages for horizontal slider */
//=============================================================================
WindowMsgHandledType GadgetHorizontalSliderSystem( GameWindow *window, UnsignedInt msg,
																		WindowMsgData mData1, WindowMsgData mData2 )
{
	SliderData *s = (SliderData *)window->winGetUserData();
	WinInstanceData *instData = window->winGetInstanceData();
	ICoord2D size, childSize, childCenter, childRelativePos;

	window->winGetSize( &size.x, &size.y );

	switch( msg )
	{
		// ------------------------------------------------------------------------
		case GBM_SELECTED:
			TheWindowManager->winSendSystemMsg( window->winGetOwner(), 
																					(GadgetGameMessage)0x4010,
																					(WindowMsgData)window, 
																					0 );
			break;

		// ------------------------------------------------------------------------
		case GGM_LEFT_DRAG:
		{
			Int mousex = mData2 & 0xFFFF;
//			Int mousey = mData2 >> 16;
			Int x, y, delta;
			GameWindow *child = window->winGetChild();

			window->winGetScreenPosition( &x, &y );

			child->winGetSize( &childSize.x, &childSize.y );
			child->winGetScreenPosition( &childCenter.x, &childCenter.y );
			child->winGetPosition( &childRelativePos.x, &childRelativePos.y );
			childCenter.x += childSize.x / 2;
			childCenter.y += childSize.y / 2;

			//
			// ignore drag attempts when the mouse is right or left of slider totally
			// and put the dragging thumb back at the slider pos
			//
			if( mousex > x + size.x )
			{

				TheWindowManager->winSendSystemMsg( window, (GadgetGameMessage)0x400D,
																						s->maxVal, 0 );
				// tell owner i moved
				TheWindowManager->winSendSystemMsg( window->winGetOwner(), 
																						(GadgetGameMessage)0x400C,
																						(WindowMsgData)window, 
																						s->maxVal );
				break;

			}  // end if
			else if( mousex < x )
			{

				TheWindowManager->winSendSystemMsg( window, (GadgetGameMessage)0x400D,
																						s->minVal, 0 );
				// tell owner i moved
				TheWindowManager->winSendSystemMsg( window->winGetOwner(), 
																						(GadgetGameMessage)0x400C,
																						(WindowMsgData)window, 
																						s->minVal );
				break;

			}  // end else if

			if( childCenter.x < x + childSize.x / 2 )
			{
				child->winSetPosition( 0, 0 );
				s->position = s->minVal;
			}
			else if( childCenter.x >= x + size.x - childSize.x / 2 )
			{
				Int rightPos = size.x - childSize.x;
				child->winSetPosition( rightPos, 0 );
				s->position = s->maxVal;
			}
			else
			{
				delta = childCenter.x - childSize.x / 2 - x;

				// Calc slider position
				s->position = (Int)(delta / s->numTicks) + s->minVal;

				if( s->position > s->maxVal )
					s->position = s->maxVal;
				if( s->position < s->minVal )
					s->position = s->minVal;
			}

			// tell owner i moved
			TheWindowManager->winSendSystemMsg( window->winGetOwner(), 
																					(GadgetGameMessage)0x400C,
																					(WindowMsgData)window, 
																					s->position );
			break;

		}  // end left drag

		// ------------------------------------------------------------------------
		case (GadgetGameMessage)0x400D:
		{
			Int newPos = (Int)mData1;
			GameWindow *child = window->winGetChild();

			if( newPos < s->minVal || newPos > s->maxVal )
				break;

			s->position = newPos;

			// Translate to window coords
			newPos = (Int)((newPos - s->minVal) * s->numTicks);

			child->winSetPosition( newPos, 0 );
			break;

		}  // end set slider

		// ------------------------------------------------------------------------
		case (GadgetGameMessage)0x400E:
		{
			ICoord2D size;
			GameWindow *child = window->winGetChild();

			window->winGetSize( &size.x, &size.y );

			s->minVal = (Int)mData1;
			s->maxVal = (Int)mData2;
			s->numTicks = (Real)(size.x - HORIZONTAL_SLIDER_THUMB_WIDTH)
										/ (Real)(s->maxVal - s->minVal);
			s->position = s->minVal;

			child->winSetPosition( 0, 0 );
			break;

		}  // end set min max

		// ------------------------------------------------------------------------
		case GWM_CREATE:
			break;

		// ------------------------------------------------------------------------
		case GWM_DESTROY:
			delete ( (SliderData *)window->winGetUserData() );
			break;

		// ------------------------------------------------------------------------
		case GWM_INPUT_FOCUS:
		{

			if( mData1 == FALSE )
				BitClear( instData->m_state, WIN_STATE_HILITED );
			else
				BitSet( instData->m_state, WIN_STATE_HILITED );

			TheWindowManager->winSendSystemMsg( window->winGetOwner(), GGM_FOCUS_CHANGE,
																					mData1, window->winGetWindowId() );
			*(Bool *)mData2 = TRUE;
			break;

		}  // end input focus

		// ------------------------------------------------------------------------
		case GGM_RESIZED:
		{
			Int height = (Int)mData2;

			s->numTicks = (Real)((Int)mData1 - HORIZONTAL_SLIDER_THUMB_WIDTH)
										/ (Real)(s->maxVal - s->minVal);

			GameWindow *thumb = window->winGetChild();
			if( thumb )
				thumb->winSetSize( HORIZONTAL_SLIDER_THUMB_WIDTH, height );
			break;

		}  // end resized

		// ------------------------------------------------------------------------
		default:
			return MSG_IGNORED;

	}  // end switch( msg )

	return MSG_HANDLED;

}  // end GadgetHorizontalSliderSystem

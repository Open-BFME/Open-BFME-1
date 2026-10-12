// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/gamewindow /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
#define __PLACEMENT_VEC_NEW_INLINE  // always.h/GameMemory.h define array placement-new themselves
// stlport
// ?W3DGadgetTextEntryDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z
//
// Retail 0x00798F30 (495 bytes through RET +0x1EE, then INT3) is the text
// entry gadget's draw callback. It cancels the pending-unichar flag, reads
// the window's screen position and size, selects the composite/text/back
// colours for the disabled, hilited and enabled states, draws the back
// border and the filled back, measures the entry text through the
// DisplayString vtable and draws the edit text through the file-static
// seven-word helper at 0x007986C0.
//
// Identity: ilt_oracle confirms this decorated name at 0x00798F30 exactly
// (p_false=3.91e-04); the address-derived spelling is contradicted.
//
// Shape: the four ICoord2D locals carry an empty default constructor through
// an address-qualified local template derived from ICoord2D. Construction
// alone leaves one LEA SIB byte (end.x at +0x14B); constructing every
// coordinate removes it, the same lever banked for 0x00793260
// (targets/game/reverse/identity_evidence/00793260-empty-coordinate.md).
// The template adds no field, store, destructor or escaping object and keeps
// ICoord2D itself in use.

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

// FILE: W3DGadgetTextEntryDraw.cpp //////////////////////////////////////////
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
// File name: W3DGadgetTextEntryDraw.cpp
//
// Created:   Colin Day, June 2001
//
// Desc:      W3D implementation for the text entry gadget
//
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////

// SYSTEM INCLUDES ////////////////////////////////////////////////////////////
#include <stdlib.h>

// USER INCLUDES //////////////////////////////////////////////////////////////
#include "GameClient/GameWindowGlobal.h"
#include "GameClient/GadgetTextEntry.h"
#include "GameClient/IMEManager.h"
#include "W3DDevice/GameClient/W3DGadget.h"
#include "W3DDevice/GameClient/W3DDisplay.h"

// A local, address-qualified construction-only view of ICoord2D: no field,
// store, destructor or escaping object, and ICoord2D itself stays in use.
template <class Coord>
struct DefaultConstructed00798f30 : Coord
{
    DefaultConstructed00798f30() {}
};

extern void Rva007986C0(GameWindow*, Color, Color, Color, Color, Int, Int);
void W3DGadgetTextEntryDraw( GameWindow *window, WinInstanceData *instData )
{
	EntryData *e = (EntryData *)window->winGetUserData();
	DefaultConstructed00798f30<ICoord2D> origin, size, start, end;
	Color backBorder, backColor, textColor, textBorder, 
			compositeColor, compositeBorder;

	// cancel unichar flag
	*((unsigned char*)e + 0x15) = 0;

	// get size and position of window
	window->winGetScreenPosition( &origin.x, &origin.y );
	window->winGetSize( &size.x, &size.y );

	// get the right colors
	if( BitTest( window->winGetStatus(), WIN_STATUS_ENABLED ) == FALSE )
	{

		compositeColor	= window->winGetDisabledTextColor();
		compositeBorder	= window->winGetDisabledTextBorderColor();
		textColor		= window->winGetDisabledTextColor();
		textBorder	= window->winGetDisabledTextBorderColor();
		backColor		= GadgetTextEntryGetDisabledColor( window );
		backBorder	= GadgetTextEntryGetDisabledBorderColor( window );

	}  // end if, disabled
	else if( BitTest( instData->getState(), WIN_STATE_HILITED ) )
	{

		compositeColor	= window->winGetIMECompositeTextColor();
		compositeBorder	= window->winGetIMECompositeBorderColor();
		textColor		= window->winGetHiliteTextColor();
		textBorder	= window->winGetHiliteTextBorderColor();
		backColor		= GadgetTextEntryGetHiliteColor( window );
		backBorder	= GadgetTextEntryGetHiliteBorderColor( window );

	}  // end else if, hilited
	else
	{

		compositeColor	= window->winGetIMECompositeTextColor();
		compositeBorder	= window->winGetIMECompositeBorderColor();
		textColor		= window->winGetEnabledTextColor();
		textBorder	= window->winGetEnabledTextBorderColor();
		backColor		= GadgetTextEntryGetEnabledColor( window );
		backBorder	= GadgetTextEntryGetEnabledBorderColor( window );

	}  // end else, just enabled

	// draw the back border
	if( backBorder != WIN_COLOR_UNDEFINED )
	{

		start.x = origin.x;
		start.y = origin.y;
		end.x = start.x + size.x;
		end.y = start.y + size.y;
		TheWindowManager->winOpenRect( backBorder, WIN_DRAW_LINE_WIDTH,
																	 start.x, start.y, end.x, end.y );

	}  // end if

	// draw the filled back
	if( backColor != WIN_COLOR_UNDEFINED )
	{

		start.x = origin.x + 1;
		start.y = origin.y + 1;
		end.x = start.x + size.x - 2;
		end.y = start.y + size.y - 2;
		TheWindowManager->winFillRect( backColor, WIN_DRAW_LINE_WIDTH,
																	 start.x, start.y, end.x, end.y );

	}  // end if

	// draw the text
	Int textWidth, fontHeight;
	union { void *address; void (DisplayString::*method)(Int*, Int*); } slot;
	slot.address = (*(void***)e->text)[15];
	(e->text->*slot.method)(&textWidth, &fontHeight);
	Int startOffset = 5;
	volatile Int width;

	width = size.x - (2 * startOffset);
	start.x = origin.x + startOffset;  // offset a little bit into the entry
	if( BitTest( window->winGetStatus(), WIN_STATUS_ONE_LINE ) )
		start.y = size.y / 2 - (fontHeight + 1) / 2;
	else
		start.y = origin.y + startOffset;  // offset a little bit into the entry

	// draw the edit text
	Rva007986C0( window, textColor, textBorder, compositeColor, compositeBorder,
										 start.x, start.y );

}  // end W3DGadgetTextEntryDraw



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

// FILE: W3DCheckBox.cpp //////////////////////////////////////////////////////
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
// File name: W3DCheckBox.cpp
//
// Created:   Colin Day, June 2001
//
// Desc:      W3D methods needed to implement the checkbox UI control
//
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////

// SYSTEM INCLUDES ////////////////////////////////////////////////////////////
#include <stdlib.h>

#include "../../../../../../../inputs/reference/shims/w3ddisplaystring/GameClient/DisplayString.h"

// USER INCLUDES //////////////////////////////////////////////////////////////
#include "GameClient/GadgetCheckBox.h"
#include "GameClient/GameWindowGlobal.h"
#include "GameClient/GameWindowManager.h"
#include "W3DDevice/GameClient/W3DGadget.h"
#include "W3DDevice/GameClient/W3DDisplay.h"

// DEFINES ////////////////////////////////////////////////////////////////////

// PRIVATE TYPES //////////////////////////////////////////////////////////////

// ??0CtorCoord@@QAE@XZ absent-from-retail
struct CtorCoord : ICoord2D { CtorCoord() {} };

namespace Rva0078FDE0 {
class DisplayString
{
public:
	virtual void unused00();
	virtual void unused01();
	virtual void unused02();
	virtual Int getTextLength();
	virtual void unused04();
	virtual void unused05();
	virtual void setFont(GameFont *font);
	virtual GameFont *getFont();
	virtual void setWordWrap(Int wordWrap);
	virtual void setWordWrapCentered(unsigned char centered);
	virtual void setTextColor(Color color, Color dropColor);
	virtual void unused11();
	virtual void unused12();
	virtual void unused13();
	virtual void draw(Int x, Int y, Color color, Color dropColor);
	virtual void getSize(Int *width, Int *height);
	virtual void unused16();
	virtual void unused17();
	virtual void unused18();
	virtual void setUseHotkey(unsigned char use, Color color);
	virtual void setClipRegion(void *region);
};
}

// BFME 1 keeps the draw-data arrays 4 bytes later than the shared GameWindow header, hence the window + 4 below.

// PRIVATE DATA ///////////////////////////////////////////////////////////////

// PUBLIC DATA ////////////////////////////////////////////////////////////////

// PRIVATE PROTOTYPES /////////////////////////////////////////////////////////

// The five checkbox image getters are `inline` in GadgetCheckBox.h, so MSVC
// emits a body for one only where it is odr-used. W3DGadgetCheckBoxImageDraw
// reads the fields directly (retail loads the colour slot, four bytes past the
// image), which since 1949cbad6 left five retail bodies claimed from this file
// with no definition in the object at all. Naming them keeps them emitted
// without touching a byte of the draw path.
// External linkage on purpose: a file-static table nothing reads is discarded
// before it can pull the getters in, and then the object still has no bodies.
typedef const Image *(*CheckBoxImageGetter)( GameWindow * );
extern const CheckBoxImageGetter theW3DCheckBoxImageGetters[];
const CheckBoxImageGetter theW3DCheckBoxImageGetters[] =
{
	&GadgetCheckBoxGetEnabledCheckedBoxImage,
	&GadgetCheckBoxGetDisabledUncheckedBoxImage,
	&GadgetCheckBoxGetDisabledCheckedBoxImage,
	&GadgetCheckBoxGetHiliteUncheckedBoxImage,
	&GadgetCheckBoxGetHiliteCheckedBoxImage,
};


// drawCheckBoxText ===========================================================
/** Draw the text for a checkbox */
//=============================================================================
static void drawCheckBoxText( GameWindow *window, WinInstanceData *instData )
{
	CtorCoord origin, size, textPos;
	Int width, height;
	Color textColor, dropColor;
	DisplayString *text = instData->getTextDisplayString();

	// sanity
	if( text == NULL || ((Rva0078FDE0::DisplayString *)text)->getTextLength() == 0 )
		return;

	// get window position and size
	window->winGetScreenPosition( &origin.x, &origin.y );
	window->winGetSize( &size.x, &size.y );

	// get the right text color
	if( BitTest( window->winGetStatus(), WIN_STATUS_ENABLED ) == FALSE )
	{
		textColor = window->winGetDisabledTextColor();
		dropColor = window->winGetDisabledTextBorderColor();
	}  // end if, disabled
	else if( BitTest( instData->getState(), WIN_STATE_HILITED ) )
	{
		textColor = window->winGetHiliteTextColor();
		dropColor = window->winGetHiliteTextBorderColor();
	}  // end else if, hilited
	else
	{
		textColor = window->winGetEnabledTextColor();
		dropColor = window->winGetEnabledTextBorderColor();
	}  // end enabled only

	// set our font to that of our parent if not the same
	if( ((Rva0078FDE0::DisplayString *)text)->getFont() != window->winGetFont() )
		((Rva0078FDE0::DisplayString *)text)->setFont( window->winGetFont() );

	// get text size
	((Rva0078FDE0::DisplayString *)text)->getSize( &width, &height );

	// where to draw
	textPos.x = origin.x + size.y;//(size.x / 2) - (width / 2);
	textPos.y = origin.y + (size.y / 2) - (height / 2);

	// draw it
	((Rva0078FDE0::DisplayString *)text)->setTextColor(textColor, dropColor);
	((Rva0078FDE0::DisplayString *)text)->draw(textPos.x, textPos.y, 1, 1);

}  // end drawCheckBoxText

// PRIVATE FUNCTIONS //////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS ///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// W3DGadgetCheckBoxDraw ======================================================
/** Draw colored check box using standard graphics */
//=============================================================================
// ?W3DGadgetCheckBoxDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z
// Open BFME 2 donor: Code/GameEngineDevice/Source/W3DDevice/GameClient/GUI/Gadget/W3DCheckBox.cpp.
void W3DGadgetCheckBoxDraw( GameWindow *window, WinInstanceData *instData )
{
	Int checkOffsetFromLeft;
	Color backColor,
				backBorder,
				boxColor,
				boxBorder;
	CtorCoord origin, size, start, end;

	// get window position and size
	window->winGetScreenPosition( &origin.x, &origin.y );
	window->winGetSize( &size.x, &size.y );

	// compute start of check offset
	checkOffsetFromLeft = size.x / 16;

	//
	// get the colors we should be using to draw, see GadgetCheckBox.h
	// draw appropriate state, see GadgetCheckBox.h for info
	//
	if( BitTest( window->winGetStatus(), WIN_STATUS_ENABLED ) == FALSE )
	{

		// disabled background
		backColor			= GadgetCheckBoxGetDisabledColor( (GameWindow *)((char *)window + 4) );
		backBorder		= GadgetCheckBoxGetDisabledBorderColor( (GameWindow *)((char *)window + 4) );

		// check box
		if( BitTest( instData->getState(), WIN_STATE_SELECTED ) )
		{
				boxColor		= GadgetCheckBoxGetDisabledCheckedBoxColor( (GameWindow *)((char *)window + 4) );
				boxBorder		= GadgetCheckBoxGetDisabledCheckedBoxBorderColor( (GameWindow *)((char *)window + 4) );
		}
		else
		{
				boxColor		= GadgetCheckBoxGetDisabledUncheckedBoxColor( (GameWindow *)((char *)window + 4) );
				boxBorder		= GadgetCheckBoxGetDisabledUncheckedBoxBorderColor( (GameWindow *)((char *)window + 4) );
		}

	}  // end if
	else if( BitTest( instData->getState(), WIN_STATE_HILITED ) )
	{

		// hilited background 
		backColor			= GadgetCheckBoxGetHiliteColor( (GameWindow *)((char *)window + 4) );
		backBorder		= GadgetCheckBoxGetHiliteBorderColor( (GameWindow *)((char *)window + 4) );

		// check box
		if( BitTest( instData->getState(), WIN_STATE_SELECTED ) )
		{
			boxColor		= GadgetCheckBoxGetHiliteCheckedBoxColor( (GameWindow *)((char *)window + 4) );
			boxBorder		= GadgetCheckBoxGetHiliteCheckedBoxBorderColor( (GameWindow *)((char *)window + 4) );
		}
		else
		{
			boxColor		= GadgetCheckBoxGetHiliteUncheckedBoxColor( (GameWindow *)((char *)window + 4) );
			boxBorder		= GadgetCheckBoxGetHiliteUncheckedBoxBorderColor( (GameWindow *)((char *)window + 4) );
		}

	}  // end else if
	else
	{

		// enabled background 
		backColor			= GadgetCheckBoxGetEnabledColor( (GameWindow *)((char *)window + 4) );
		backBorder		= GadgetCheckBoxGetEnabledBorderColor( (GameWindow *)((char *)window + 4) );

		// check box
		if( BitTest( instData->getState(), WIN_STATE_SELECTED ) )
		{
			boxColor		= GadgetCheckBoxGetEnabledCheckedBoxColor( (GameWindow *)((char *)window + 4) );
			boxBorder		= GadgetCheckBoxGetEnabledCheckedBoxBorderColor( (GameWindow *)((char *)window + 4) );
		}
		else
		{
			boxColor		= GadgetCheckBoxGetEnabledUncheckedBoxColor( (GameWindow *)((char *)window + 4) );
			boxBorder		= GadgetCheckBoxGetEnabledUncheckedBoxBorderColor( (GameWindow *)((char *)window + 4) );
		}

	}  // end else

	// draw background border
	start.x = origin.x;
	start.y = origin.y;
	end.x = start.x + size.x;
	end.y = start.y + size.y;
	TheWindowManager->winOpenRect( backBorder, WIN_DRAW_LINE_WIDTH, 
																 start.x, start.y, end.x, end.y );

	// draw the background
	start.x++;
	start.y++;
	end.x--;
	end.y--;
	TheWindowManager->winFillRect( backColor, WIN_DRAW_LINE_WIDTH, 
																 start.x, start.y, end.x, end.y );

	// draw box border
	start.x = origin.x + checkOffsetFromLeft;
	start.y = origin.y + (size.y / 3);
	end.x = start.x + (size.y / 3);
	end.y = start.y + (size.y / 3);
	TheWindowManager->winOpenRect( boxBorder, WIN_DRAW_LINE_WIDTH, 
																 start.x, start.y, end.x, end.y );

	// draw "x" for button
	if( boxColor != WIN_COLOR_UNDEFINED )
	{

		TheWindowManager->winDrawLine( boxColor, WIN_DRAW_LINE_WIDTH, 
																	 start.x, start.y, end.x, end.y );
		TheWindowManager->winDrawLine( boxColor, WIN_DRAW_LINE_WIDTH, 
																	 start.x, end.y, end.x, start.y );

	}  // end if

	// draw the button text
	if( instData->getTextLength() )
		drawCheckBoxText( window, instData );

}  // end W3DGadgetCheckBoxDraw

// W3DGadgetCheckBoxImageDraw =================================================
/** Draw check box with user supplied images */
//=============================================================================
// Open BFME 2 donor: Code/GameEngineDevice/Source/W3DDevice/GameClient/GUI/Gadget/W3DCheckBox.cpp.
void W3DGadgetCheckBoxImageDraw( GameWindow *window, WinInstanceData *instData )
{
	Int checkOffsetFromLeft;
	const Image  *boxImage = NULL;//*backgroundImage = NULL,
	CtorCoord origin, start, end, size;

	// get window position and size
	window->winGetScreenPosition( &origin.x, &origin.y );
	window->winGetSize( &size.x, &size.y );

	// compute screen coords
	start.x = origin.x + instData->m_imageOffset.x;
	start.y = origin.y + instData->m_imageOffset.y;
	end.x = start.x + size.x;
	end.y = start.y + size.y;

	// compute start of check offset
	checkOffsetFromLeft =  0;

	//
	// get the colors we should be using to draw, see GadgetCheckBoxButton.h
	// draw appropriate state, see GadgetCheckBoxButton.h for info
	//
	if( BitTest( window->winGetStatus(), WIN_STATUS_ENABLED ) == FALSE )
	{

		// disabled background
//		backgroundImage	= GadgetCheckBoxGetDisabledImage( window );

		// check box
		if( BitTest( instData->getState(), WIN_STATE_SELECTED ) )
				boxImage		= *(const Image **)((char *)window + 0xCC);
		else
				boxImage		= *(const Image **)((char *)window + 0xC0);

	}  // end if
	else if( BitTest( instData->getState(), WIN_STATE_HILITED ) )
	{

		// hilited background 
//		backgroundImage	= GadgetCheckBoxGetHiliteImage( window );

		// check box
		if( BitTest( instData->getState(), WIN_STATE_SELECTED ) )
			boxImage		= *(const Image **)((char *)window + 0x138);
		else
			boxImage		= *(const Image **)((char *)window + 0x12C);

	}  // end else if
	else
	{

		// enabled background 
//		backgroundImage	= GadgetCheckBoxGetEnabledImage( window );

		// check box
		if( BitTest( instData->getState(), WIN_STATE_SELECTED ) )
			boxImage		= *(const Image **)((char *)window + 0x60);
		else
			boxImage		= *(const Image **)((char *)window + 0x54);

	}  // end else

	// draw background image
//	if( backgroundImage )
//		TheWindowManager->winDrawImage( backgroundImage, start.x, start.y, 
//																		end.x, end.y );

	// draw the box image
	if( boxImage )
	{

		start.x = origin.x + instData->m_imageOffset.x + checkOffsetFromLeft;
		start.y = origin.y +  3;
		end.x = (size.y - 6) + start.x;
		end.y = start.y + (size.y - 6);
		TheWindowManager->winDrawImage( boxImage, start.x, start.y, 
																	  end.x, end.y );

	}  // end if
		
	// draw the text
	if( instData->getTextLength() )
		drawCheckBoxText( window, instData );

}  // end W3DGadgetCheckBoxImageDraw

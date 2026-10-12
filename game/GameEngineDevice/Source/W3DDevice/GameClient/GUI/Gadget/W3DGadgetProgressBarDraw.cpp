// ?W3DGadgetProgressBarDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z
//
// Retail 0x00793260 (553 bytes) is the progress bar gadget's draw callback:
// it reads the window's user data as the 0..100 progress, takes the screen
// position and size, picks the back/bar colours for the disabled, hilited and
// enabled states, strokes the back border and fills the back, then strokes and
// fills the progress rect plus its two light edges.
//
// Identity: ilt_oracle confirms this decorated name at 0x00793260.
//
// Shape: the four ICoord2D locals carry an empty default constructor through an
// address-qualified local template derived from ICoord2D, the lever banked for
// this body in targets/game/reverse/identity_evidence/00793260-empty-coordinate.md.
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

// FILE: W3DProgressBar.cpp ///////////////////////////////////////////////////
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
// File name: W3DProgressBar.cpp
//
// Created:   Colin Day, June 2001
//
// Desc:      W3D implementation for the progress bar GUI control
//
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////

// SYSTEM INCLUDES ////////////////////////////////////////////////////////////
#include <stdlib.h>

// USER INCLUDES //////////////////////////////////////////////////////////////
#include "GameClient/GameWindowGlobal.h"
#include "GameClient/GameWindowManager.h"
#include "GameClient/GadgetProgressBar.h"
#include "W3DDevice/GameClient/W3DGadget.h"
#include "W3DDevice/GameClient/W3DDisplay.h"

// DEFINES ////////////////////////////////////////////////////////////////////

// PRIVATE TYPES //////////////////////////////////////////////////////////////

// PRIVATE DATA ///////////////////////////////////////////////////////////////

// PUBLIC DATA ////////////////////////////////////////////////////////////////

// PRIVATE PROTOTYPES /////////////////////////////////////////////////////////

// PRIVATE FUNCTIONS //////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS ///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// W3DGadgetProgressBarDraw ===================================================
/** Draw colored Progress Bar using standard graphics */
//=============================================================================
template <class Coord>
struct DefaultConstructed00793260 : Coord
{
    DefaultConstructed00793260() {}
};

void W3DGadgetProgressBarDraw(GameWindow *window, WinInstanceData *instData)
{
	DefaultConstructed00793260<ICoord2D> origin, size, start, end;
	Color backColor, backBorder, barColor, barBorder;
	Int progress = (Int)window->winGetUserData();

	window->winGetScreenPosition(&origin.x, &origin.y);
	window->winGetSize(&size.x, &size.y);

	if (BitTest(window->winGetStatus(), WIN_STATUS_ENABLED) == FALSE)
	{
		backColor = GadgetProgressBarGetDisabledColor((GameWindow *)((char *)window + 4));
		backBorder = GadgetProgressBarGetDisabledBorderColor((GameWindow *)((char *)window + 4));
		barColor = GadgetProgressBarGetDisabledBarColor((GameWindow *)((char *)window + 4));
		barBorder = GadgetProgressBarGetDisabledBarBorderColor((GameWindow *)((char *)window + 4));
	}
	else if (BitTest(instData->getState(), WIN_STATE_HILITED))
	{
		backColor = GadgetProgressBarGetHiliteColor((GameWindow *)((char *)window + 4));
		backBorder = GadgetProgressBarGetHiliteBorderColor((GameWindow *)((char *)window + 4));
		barColor = GadgetProgressBarGetHiliteBarColor((GameWindow *)((char *)window + 4));
		barBorder = GadgetProgressBarGetHiliteBarBorderColor((GameWindow *)((char *)window + 4));
	}
	else
	{
		backColor = GadgetProgressBarGetEnabledColor((GameWindow *)((char *)window + 4));
		backBorder = GadgetProgressBarGetEnabledBorderColor((GameWindow *)((char *)window + 4));
		barColor = GadgetProgressBarGetEnabledBarColor((GameWindow *)((char *)window + 4));
		barBorder = GadgetProgressBarGetEnabledBarBorderColor((GameWindow *)((char *)window + 4));
	}

	if (backBorder != WIN_COLOR_UNDEFINED)
	{
		start.x = origin.x;
		start.y = origin.y;
		end.x = start.x + size.x;
		end.y = start.y + size.y;
		TheWindowManager->winOpenRect(backBorder, WIN_DRAW_LINE_WIDTH,
																				 start.x, start.y, end.x, end.y);
	}

	if (backColor != WIN_COLOR_UNDEFINED)
	{
		start.x = origin.x + 1;
		start.y = origin.y + 1;
		end.x = start.x + size.x - 2;
		end.y = start.y + size.y - 2;
		TheWindowManager->winFillRect(backColor, WIN_DRAW_LINE_WIDTH,
																				 start.x, start.y, end.x, end.y);
	}

	if (progress)
	{
		if (barBorder != WIN_COLOR_UNDEFINED)
		{
			start.x = origin.x;
			start.y = origin.y;
			end.x = start.x + (size.x * progress) / 100;
			end.y = start.y + size.y;
			if (end.x - start.x > 1)
			{
				TheWindowManager->winOpenRect(barBorder, WIN_DRAW_LINE_WIDTH,
																				 start.x, start.y, end.x, end.y);
			}
		}

		if (barColor != WIN_COLOR_UNDEFINED)
		{
			start.x = origin.x + 1;
			start.y = origin.y + 1;
			end.x = start.x + (size.x * progress) / 100 - 2;
			end.y = start.y + size.y - 2;
			if (end.x - start.x > 1)
			{
				TheWindowManager->winFillRect(barColor, WIN_DRAW_LINE_WIDTH,
																				 start.x, start.y, end.x, end.y);
				TheWindowManager->winDrawLine(GameMakeColor(255, 255, 255, 255),
					WIN_DRAW_LINE_WIDTH, start.x, start.y, end.x, start.y);
				TheWindowManager->winDrawLine(GameMakeColor(200, 200, 200, 255),
					WIN_DRAW_LINE_WIDTH, start.x, start.y, start.x, end.y);
			}
		}
	}
}  // end W3DGadgetProgressBarDraw


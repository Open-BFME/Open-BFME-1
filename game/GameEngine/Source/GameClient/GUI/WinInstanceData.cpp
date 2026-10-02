// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
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

// FILE: WinInstanceData.cpp //////////////////////////////////////////////////
//-----------------------------------------------------------------------------
//                                                                          
//                       Westwood Studios Pacific.                          
//                                                                          
//                       Confidential Information                           
//                Copyright (C) 2001 - All Rights Reserved                  
//                                                                          
//-----------------------------------------------------------------------------
//
// Project:    RTS3
//
// File name:  WinInstanceData.cpp
//
// Created:    Colin Day, July 2001
//
// Desc:       Game window instance data
//
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////

// SYSTEM INCLUDES ////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

// USER INCLUDES //////////////////////////////////////////////////////////////
#include "GameClient/WinInstanceData.h"
#include "GameClient/GameWindow.h"
#include "GameClient/DisplayStringManager.h"
#include "Common/Debug.h"

// DEFINES ////////////////////////////////////////////////////////////////////

// PRIVATE TYPES //////////////////////////////////////////////////////////////

// PRIVATE DATA ///////////////////////////////////////////////////////////////

// PUBLIC DATA ////////////////////////////////////////////////////////////////

// PRIVATE PROTOTYPES /////////////////////////////////////////////////////////

// PRIVATE FUNCTIONS //////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS ///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// WinInstanceData::WinInstanceData ===========================================
//=============================================================================
WinInstanceData::WinInstanceData( void )
{

	// we don't allocate strings unless we need them
	m_text = NULL;
	m_tooltip = NULL;
	m_videoBuffer = NULL;
	init();

}  // end WinInstanceData

// WinInstanceData::~WinInstanceData ==========================================
//=============================================================================
// ??1WinInstanceData@@UAE@XZ present-unmatched
WinInstanceData::~WinInstanceData( void )
{

	if( m_text )
		TheDisplayStringManager->freeDisplayString( m_text );

	if( m_tooltip )
		TheDisplayStringManager->freeDisplayString( m_tooltip );

	m_videoBuffer = NULL; //Video Buffer needs to be clean up by the control that is in charge of the video.

}  // end ~WinInstanceData

// WinInstanceData::init ======================================================
/** Set initial values for instance data if desired */
//=============================================================================
// Retail implementation: WinInstanceDataDisplayStrings.cpp.

// WinInstanceData::setTooltipText ============================================
//=============================================================================
// Retail implementation: WinInstanceDataDisplayStrings.cpp.

// WinInstanceData:setText ====================================================
/** Set the text for this window instance data */
//=============================================================================
// byte-exact reconstruction: game/GameEngine/Source/GameClient/GUI/WinInstanceDataDisplayStrings.cpp
// ?setText@WinInstanceData@@QAEXVUnicodeString@@@Z present-unmatched
void WinInstanceData::setText( UnicodeString text )
{

	// allocate a text instance if needed
	if( m_text == NULL )
		m_text = TheDisplayStringManager->newDisplayString();
	DEBUG_ASSERTCRASH( m_text, ("no text") );

	// set the text
	m_text->setText( text );

}  // end set text

// WinInstanceData:setText ====================================================
/** Set the text for this window instance data */
//=============================================================================
void WinInstanceData::setVideoBuffer( VideoBuffer * videoBuffer )
{
	m_videoBuffer = videoBuffer;
}
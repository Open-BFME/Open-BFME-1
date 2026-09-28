// ?drawText006F5170@W3DDisplayString@@IAEXHHHH@Z
// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/w3ddisplaystring /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
// Keep the reference string buffer at BFME's witnessed +8 offset.
// StringBase's length field is handled separately where needed.
#define _INTERNAL
#define DISABLE_ALLOW_DEBUG_UTILS
#define DISABLE_MEMORYPOOL_DEBUG_CUSTOM_NEW
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

// FILE: W3DDisplayString.cpp /////////////////////////////////////////////////
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
// File name:  W3DDisplayString.cpp
//
// Created:    Colin Day, July 2001
//
// Desc:       Display string W3D implementation, display strings hold
//						 double byte characters and all the data we need to render
//						 those strings to the screen.
//
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////

// SYSTEM INCLUDES ////////////////////////////////////////////////////////////
#include <stdlib.h>

// USER INCLUDES //////////////////////////////////////////////////////////////
#include "GameClient/GameClient.h"
#include "W3DDevice/GameClient/W3DDisplayString.h"
#include "GameClient/HotKey.h"
#include "GameClient/GameFont.h"
#include "GameClient/GlobalLanguage.h"

// DEFINES ////////////////////////////////////////////////////////////////////
#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

class Render2DSentenceHHHH
{
public:
	void Draw_Sentence( UnsignedInt c0, UnsignedInt c1, UnsignedInt c2, UnsignedInt c3 );
};

// W3DDisplayString::drawText006F5170 ==========================================
/** Render the built sentence(s) at x,y with the drop shadow offset by
	* xDrop,yDrop.  color/dropColor (and the shadow's own colors) are already
	* stored in members by the caller before this runs; this only rebuilds
	* the sentence if needed and redraws the quads if position or a dirty
	* flag changed. */
//=============================================================================
// retail 0x006F5170; address-derived name, exact public overload unproven
void W3DDisplayString::drawText006F5170( Int x, Int y, Int xDrop, Int yDrop )
{
	Bool needNewPolys = FALSE;

	if( getTextLength() == 0 )
		return;

	if( !checkForChangedTextData( &needNewPolys ) )
		return;

	if( needNewPolys ||
			x != m_textPos.x ||
			y != m_textPos.y ||
			m_bfmeFlag1EC ||
			m_bfmeFlag20C )
	{

		m_textPos.x = x;
		m_textPos.y = y;

		m_textRenderer.Reset_Polys();

		if( xDrop || yDrop )
		{
			Int sx = m_textPos.x + xDrop;
			Int sy = m_textPos.y + yDrop;
			m_textRenderer.Set_Location( Vector2( sx, sy ) );
			((Render2DSentenceHHHH *)&m_textRenderer)->Draw_Sentence( m_bfmeResetFields[2], m_bfmeResetFields[3], m_bfmeResetFields[4], m_bfmeResetFields[5] );
		}

		m_textRenderer.Set_Location( Vector2( m_textPos.x, m_textPos.y ) );
		((Render2DSentenceHHHH *)&m_textRenderer)->Draw_Sentence( m_currTextColor, m_currDropColor, m_bfmeResetFields[0], m_bfmeResetFields[1] );

		if(m_useHotKey)
		{
			m_textRendererHotKey.Reset_Polys();
			m_textRendererHotKey.Set_Location( Vector2( m_textPos.x + m_hotKeyPos.x , m_textPos.y + m_hotKeyPos.y) );
			((Render2DSentenceHHHH *)&m_textRendererHotKey)->Draw_Sentence( m_hotKeyColor, m_hotKeyColor, m_hotKeyColor, m_hotKeyColor );
			m_textRendererHotKey.Render();
		}

		m_bfmeFlag20C = FALSE;

	}  // end if

	m_textRenderer.Render();

	if( TheGameClient )
		usingResources( TheGameClient->getFrame() );

}  // end drawText006F5170

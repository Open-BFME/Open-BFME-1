// ?checkForChangedTextData@W3DDisplayString@@IAE_NPA_N@Z
// cl: /Iinputs/reference/shims/asciistring_outofline /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/w3ddisplaystring /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
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
#include "../../../../Libraries/Source/WWVegas/WWLib/string_base.h"
template <typename T> inline bool StringBase<T>::isEmpty() const { return m_data == 0 || m_data->length == 0; }

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

// The existing canonical callee at 0x00942BC0 is Gen_00942BC0::process.
// Its three arguments and ret12 match Build_Sentence; reuse it without a second identity.
class Gen_00942BC0 { public: void process(void *, void *, void *); };

// Retail 0x006F4F50: checkForChangedTextData(Bool*); ret 4.
// BFME StringBase length at header+4 determines emptiness, not the first character.
Bool W3DDisplayString::checkForChangedTextData( Bool *needNewPolys )
{

	// sanity
	if( getTextLength() == 0 )
		return FALSE;

	// if our font or text has changed we need to build a new sentence
	if( m_fontChanged || m_textChanged )
	{
		if(m_useHotKey)
		{
			m_textRenderer.Set_Hot_Key_Parse(TRUE);
			reinterpret_cast<Gen_00942BC0 *>(&m_textRenderer)->process( const_cast<WideChar *>(getText().str()), &m_hotKeyPos.x, &m_hotKeyPos.y );
			m_hotkey.translate(TheHotKeyManager->searchHotKey(getText()));
			if(!reinterpret_cast<const StringBase<wchar_t> *>(&m_hotkey)->isEmpty())
				reinterpret_cast<Gen_00942BC0 *>(&m_textRendererHotKey)->process(const_cast<WideChar *>(m_hotkey.str()), NULL, NULL);
			else
			{
				m_useHotKey = FALSE;
				m_textRendererHotKey.Reset();
			}
		}
		else
			reinterpret_cast<Gen_00942BC0 *>(&m_textRenderer)->process( const_cast<WideChar *>(getText().str()), NULL, NULL );
		m_fontChanged = FALSE;
		m_textChanged = FALSE;
		*needNewPolys = TRUE;

	}  // end if

	return TRUE;

}  // end checkForChangedTextData

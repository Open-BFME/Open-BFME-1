// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
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

// FILE: Win32DIKeyboardCtor.cpp //////////////////////////////////////////////
//
// DirectInputKeyboard::DirectInputKeyboard. Declared here rather than through
// Win32DIKeyboard.h for the same reason as Win32DIKeyboardOpen.cpp: BFME's
// Keyboard base is wider than ZH's, putting m_pDirectInput at +0xe1c and
// m_pKeyboardDevice at +0xe20. This body needs one more base member than that
// file does -- m_modifiers, an UnsignedShort at +0x8, which retail touches as
// the byte at +0x9 because KEY_STATE_CAPSLOCK (0x0200) lives in its high half.
//
///////////////////////////////////////////////////////////////////////////////

#include <windows.h>

enum { KEY_STATE_CAPSLOCK = 0x0200 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Keyboard.h
class Keyboard
{
public:

	Keyboard( void );
	virtual ~Keyboard( void );

protected:

	// vptr @0x0
	char m_bfmeKeyboardHead[ 0x8 - 0x4 ];
	unsigned short m_modifiers;								// @0x8
	char m_bfmeKeyboardTail[ 0xe1c - 0xa ];

};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/Win32Device/GameClient/Win32DIKeyboard.h
class DirectInputKeyboard : public Keyboard
{
public:

	DirectInputKeyboard( void );
	virtual ~DirectInputKeyboard( void );

protected:

	void *m_pDirectInput;											// @0xe1c
	void *m_pKeyboardDevice;									// @0xe20

};

//-----------------------------------------------------------------------------
DirectInputKeyboard::DirectInputKeyboard( void )
{

	m_pDirectInput = 0;
	m_pKeyboardDevice = 0;


	if( GetKeyState( VK_CAPITAL ) & 0x01 )
	{
		m_modifiers |= KEY_STATE_CAPSLOCK;
	}
	else
	{
		m_modifiers &= ~KEY_STATE_CAPSLOCK;
	}

}  // end DirectInputKeyboard

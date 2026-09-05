// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
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

// FILE: Win32DIKeyboardDtor.cpp //////////////////////////////////////////////
//
// DirectInputKeyboard::~DirectInputKeyboard. Twin of Win32DIMouse.cpp's
// ~DirectInputMouse (same shape: release two DirectInput pointers then chain
// to the base dtor), rebuilt with the layout Win32DIKeyboardCtor.cpp and
// Win32DIKeyboardOpen.cpp already established: BFME's Keyboard base runs to
// +0xe1c, putting m_pDirectInput at +0xe1c and m_pKeyboardDevice at +0xe20.
// Keyboard's own dtor (~Keyboard) is still an unconverted dump at 0x0002208E;
// it is declared but never defined here so the call resolves through the
// reverse/symbols.csv pin added for this body's exact mangled name.
//
///////////////////////////////////////////////////////////////////////////////

#define DIRECTINPUT_VERSION 0x800
#include <windows.h>
#include <dinput.h>

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

	virtual ~DirectInputKeyboard( void );

protected:

	void closeKeyboard( void );

	LPDIRECTINPUT8 m_pDirectInput;							// @0xe1c
	LPDIRECTINPUTDEVICE8 m_pKeyboardDevice;		// @0xe20

};

//-----------------------------------------------------------------------------
void DirectInputKeyboard::closeKeyboard( void )
{

	if( m_pKeyboardDevice )
	{

		m_pKeyboardDevice->Unacquire();
		m_pKeyboardDevice->Release();
		m_pKeyboardDevice = NULL;

	}  // end if

	if( m_pDirectInput )
	{

		m_pDirectInput->Release();
		m_pDirectInput = NULL;

	}  // end if

}  // end closeKeyboard

//-----------------------------------------------------------------------------
DirectInputKeyboard::~DirectInputKeyboard( void )
{

	closeKeyboard();

}  // end ~DirectInputKeyboard

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

// FILE: Win32DIKeyboardOpen.cpp //////////////////////////////////////////////
//
// DirectInputKeyboard::openKeyboard. Declared here rather than through
// Win32DIKeyboard.h: BFME's Keyboard base is wider than ZH's, putting
// m_pDirectInput at +0xe1c and m_pKeyboardDevice at +0xe20, and the padding
// below is the only part of the layout this body needs.
//
///////////////////////////////////////////////////////////////////////////////

#define DIRECTINPUT_VERSION 0x800
#include <windows.h>
#include <dinput.h>

extern HINSTANCE ApplicationHInstance;
extern HWND ApplicationHWnd;

// dinput.h declares DirectInput8Create __declspec(dllimport), which makes the
// compiler call the import slot directly in six bytes. Retail calls the
// five-byte import stub at 0x009f9af0, so route through an undecorated
// declaration of the same entry point.
extern "C" HRESULT WINAPI bfmeDirectInput8Create( HINSTANCE, DWORD, REFIID, void **, IUnknown * );

enum { KEYBOARD_BUFFER_SIZE = 256 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/Win32Device/GameClient/Win32DIKeyboard.h
class DirectInputKeyboard
{
protected:
	char m_bfmeKeyboardBase[0xe1c];
	LPDIRECTINPUT8 m_pDirectInput;						// @0xe1c
	LPDIRECTINPUTDEVICE8 m_pKeyboardDevice;		// @0xe20

	void openKeyboard( void );
	void closeKeyboard( void );
};

void DirectInputKeyboard::closeKeyboard( void )
{
	if( m_pKeyboardDevice )
	{
		m_pKeyboardDevice->Unacquire();
		m_pKeyboardDevice->Release();
		m_pKeyboardDevice = NULL;
	}

	if( m_pDirectInput )
	{
		m_pDirectInput->Release();
		m_pDirectInput = NULL;
	}
}

void DirectInputKeyboard::openKeyboard( void )
{
  HRESULT hr;

	// create our interface to direct input
	hr = bfmeDirectInput8Create( ApplicationHInstance,
													 DIRECTINPUT_VERSION,
													 IID_IDirectInput8,
													 (void **)&m_pDirectInput,
													 NULL );
	if( FAILED( hr ) )
	{
		closeKeyboard();
		return;

	}  // end if

	// obtain an interface to the system keyboard device
	hr = m_pDirectInput->CreateDevice( GUID_SysKeyboard,
																		 &m_pKeyboardDevice,
																		 NULL );
	if( FAILED( hr ) )
	{
		closeKeyboard();
		return;

	}  // end if

	// set the data format for the keyboard
	hr = m_pKeyboardDevice->SetDataFormat( &c_dfDIKeyboard );
	if( FAILED( hr ) )
	{
		closeKeyboard();
		return;

	}  // end if

	// set the cooperative level for the keyboard, must be non-exclusive for
	// NT support
	hr = m_pKeyboardDevice->SetCooperativeLevel( ApplicationHWnd,
																							 DISCL_FOREGROUND |
																							 DISCL_NONEXCLUSIVE );
	if( FAILED( hr ) )
	{
		closeKeyboard();
		return;

	}  // end if

  // set the keyboard buffer size
	DIPROPDWORD prop;
	prop.diph.dwSize = sizeof( DIPROPDWORD );
	prop.diph.dwHeaderSize = sizeof( DIPROPHEADER );
	prop.diph.dwObj = 0;
	prop.diph.dwHow = DIPH_DEVICE;
	prop.dwData = KEYBOARD_BUFFER_SIZE;
	hr = m_pKeyboardDevice->SetProperty( DIPROP_BUFFERSIZE, &prop.diph );
	if( FAILED( hr ) )
	{
		closeKeyboard();
		return;

	}  // end if

	// acquire the keyboard
	hr = m_pKeyboardDevice->Acquire();

}  // end openKeyboard

// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
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

// FILE: Win32DIKeyboard.cpp
// DirectInput keyboard lifecycle and event input share one BFME layout.
// The ZH Win32DIKeyboard source establishes class ownership; BFME's matched
// constructor/open/getKey bodies place the device pointers at +0xe1c/+0xe20.
// name_oracle/layout_witness independently confirms both member names.
// Keyboard::m_modifiers is the unsigned short at +0x8 used by the caps-lock test.

#define DIRECTINPUT_VERSION 0x800
#include <windows.h>
#include <dinput.h>

#undef DIERR_NOTACQUIRED
#define DIERR_NOTACQUIRED 0x8007000CL

enum { KEY_STATE_CAPSLOCK = 0x0200, KEYBOARD_BUFFER_SIZE = 256 };
enum
{
	KEY_NONE = 0,
	KEY_LOST = 0xff,
    KEY_STATE_UP = 1,
    KEY_STATE_DOWN = 2,
};

struct KeyboardIO
{
	enum StatusType
	{
		STATUS_UNUSED = 0,
		STATUS_USED = 1,
	};

	unsigned char key;
	unsigned char status;
	unsigned short state;
	unsigned int sequence;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Keyboard.h
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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/Win32Device/GameClient/Win32DIKeyboard.h
class DirectInputKeyboard : public Keyboard
{
public:
    DirectInputKeyboard( void );
    virtual ~DirectInputKeyboard( void );
protected:
    void openKeyboard( void );
    void closeKeyboard( void );
    virtual void getKey( KeyboardIO *key );
    LPDIRECTINPUT8 m_pDirectInput;          // @0xe1c
    LPDIRECTINPUTDEVICE8 m_pKeyboardDevice; // @0xe20
};

extern HINSTANCE ApplicationHInstance;
extern HWND ApplicationHWnd;

// dinput.h declares DirectInput8Create __declspec(dllimport), which makes the
// compiler call the import slot directly in six bytes. Retail calls the
// five-byte import stub at 0x009f9af0, so route through an undecorated
// declaration of the same entry point.
extern "C" HRESULT WINAPI bfmeDirectInput8Create( HINSTANCE, DWORD, REFIID, void **, IUnknown * );

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

DirectInputKeyboard::~DirectInputKeyboard( void )
{

	closeKeyboard();

}  // end ~DirectInputKeyboard

void DirectInputKeyboard::getKey( KeyboardIO *key )
{
	DIDEVICEOBJECTDATA kbdat;
	DWORD num = 0;
	HRESULT hr;

	key->sequence = 0;
	key->key = KEY_NONE;

	if( m_pKeyboardDevice )
	{
		num = 1;
		hr = m_pKeyboardDevice->Acquire();
		if( hr == DI_OK || hr == S_FALSE )
			hr = m_pKeyboardDevice->GetDeviceData( sizeof( DIDEVICEOBJECTDATA ),
				&kbdat, &num, 0 );
		switch( hr )
		{
		case DI_OK:
			break;

		case DIERR_INPUTLOST:
		case DIERR_NOTACQUIRED:
			hr = m_pKeyboardDevice->Acquire();
			switch( hr )
			{
			case DIERR_INVALIDPARAM:
			case DIERR_NOTINITIALIZED:
			case DIERR_OTHERAPPHASPRIO:
				break;

			case DI_OK:
			case S_FALSE:
				key->key = KEY_LOST;
				break;
			}
			return;

		default:
			return;
		}

		if( num == 0 )
			return;

		key->key = (unsigned char)(kbdat.dwOfs & 0xff);
		key->sequence = kbdat.dwSequence;
		key->state = (( kbdat.dwData & 0x80 ) ? KEY_STATE_DOWN : KEY_STATE_UP);
		key->status = KeyboardIO::STATUS_UNUSED;
	}
}

// cl: /DNDEBUG /MD /EHsc
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
//
// BFME recovery for retail RVA 0x005A3460 (688 bytes including switch tables).
//
// This is the real Keyboard modifier/character translation body, not the
// generated d_005a3460 placeholder.  The named caller at 0x005A3EF0 is
// Rva005A3EF0Keyboard::processKeyEvents; it calls this body through ILT
// 0x00025374 for modifier events.  The address-qualified spelling below is
// retained because the BFME split-method name is not proven.
//
// Boundary evidence: executable code occupies 497 bytes through 0x005A3650.
// Three alignment bytes precede eight DWORD jump targets at 0x005A3654
// and 156 byte indices at 0x005A3674 for keys 0x1D..0xB8. The complete
// 688-byte range ends at 0x005A3710, where INT3 padding begins. Its fields
// are the same BFME Keyboard fields already established by the matched ctor,
// processKeyEvents, and check-repeat bodies: modifiers +0x08, shift2 key
// +0x0A, key-status records +0x18 (8-byte stride), and key names +0x818
// (6-byte stride).  The caps-state virtual call is at the observed BFME
// Keyboard vtable slot +0x24.

typedef unsigned char  BfmeKeyboardByte;
typedef unsigned short BfmeKeyboardWord;
typedef unsigned int   BfmeKeyboardDword;
typedef bool           BfmeKeyboardBool;

extern "C" __declspec(dllimport) int __cdecl iswalpha(
	BfmeKeyboardWord value );

enum
{

	BfmeKeyCaps       = 0x3A,
	BfmeKeyLeftCtrl   = 0x1D,
	BfmeKeyRightCtrl  = 0x9D,
	BfmeKeyLeftShift  = 0x2A,
	BfmeKeyRightShift = 0x36,
	BfmeKeyLeftAlt    = 0x38,
	BfmeKeyRightAlt   = 0xB8,

	BfmeKeyDown       = 0x0002,
	BfmeCapsLock      = 0x0200,
	BfmeShift2        = 0x0400,
	BfmeLeftShift     = 0x0010,
	BfmeRightShift    = 0x0020,
	BfmeLeftCtrl      = 0x0004,
	BfmeRightCtrl     = 0x0008,
	BfmeLeftAlt       = 0x0040,
	BfmeRightAlt      = 0x0080
};

struct BfmeKeyboardStatusRecord
{
	BfmeKeyboardByte  key;
	BfmeKeyboardByte  status;
	BfmeKeyboardWord  state;
	BfmeKeyboardDword sequence;
};

struct BfmeKeyboardKeyName
{
	BfmeKeyboardWord standard;
	BfmeKeyboardWord shifted;
	BfmeKeyboardWord shifted2;
};

// The vtable view is deliberately local.  BFME's Keyboard vtable has the
// inherited subsystem slots plus the observed BFME input slots; the
// caps-state entry used by this body is slot 9 (+0x24).  Four bytes after the
// vptr are the inherited subsystem name, so the derived data begins at +8.
class BfmeKeyboardVtableView
{
public:
	virtual void slot00( void ) = 0;
	virtual void slot01( void ) = 0;
	virtual void slot02( void ) = 0;
	virtual void slot03( void ) = 0;
	virtual void slot04( void ) = 0;
	virtual void slot05( void ) = 0;
	virtual void slot06( void ) = 0;
	virtual void slot07( void ) = 0;
	virtual void slot08( void ) = 0;
	virtual BfmeKeyboardBool getCapsState( void ) = 0;

	BfmeKeyboardByte m_subsystemName[ 4 ];
};

class Rva005A3EF0Keyboard : public BfmeKeyboardVtableView
{
public:
	BfmeKeyboardWord Rva005A3460TranslateKey( BfmeKeyboardWord keyCode );

	BfmeKeyboardWord m_modifiers; // +0x08
	BfmeKeyboardByte m_shift2Key; // +0x0A
	BfmeKeyboardByte m_pad0B;     // +0x0B
	BfmeKeyboardDword m_eventVector[ 3 ]; // +0x0C..+0x17
	BfmeKeyboardStatusRecord m_keyStatus[ 256 ]; // +0x18..+0x817
	BfmeKeyboardKeyName m_keyNames[ 256 ]; // +0x818..+0xE17
	BfmeKeyboardDword m_inputFrame; // +0xE18

	inline BfmeKeyboardByte getKeyStatusData( BfmeKeyboardByte key ) const
	{
		return m_keyStatus[ key ].status;
	}

	inline BfmeKeyboardBool getKeyStateBit( BfmeKeyboardByte key,
		BfmeKeyboardDword bit ) const
	{
		return (m_keyStatus[ key ].state & bit) ? 1 : 0;
	}

	inline void setKeyStatusData( BfmeKeyboardByte key,
		BfmeKeyboardByte value )
	{
		m_keyStatus[ key ].status = value;
	}

	inline BfmeKeyboardBool isShift( void ) const
	{
		if( m_modifiers & BfmeLeftShift ||
			m_modifiers & BfmeRightShift ||
			m_modifiers & BfmeShift2 )
			return true;
		return false;
	}
};

// @?Rva005A3460TranslateKey@Rva005A3EF0Keyboard@@QAEGG@Z 0x005A3460
BfmeKeyboardWord Rva005A3EF0Keyboard::Rva005A3460TranslateKey(
	BfmeKeyboardWord keyCode )
{
	if( keyCode > 0x00FF )
		return keyCode;

	BfmeKeyboardByte ubKeyCode = (BfmeKeyboardByte)keyCode;
	switch( ubKeyCode )
	{
		case BfmeKeyCaps:
			if( getKeyStatusData( BfmeKeyCaps ) == 0 )
			{
				if( getKeyStateBit( BfmeKeyCaps, BfmeKeyDown ) )
				{
					if( m_modifiers & BfmeCapsLock )
						m_modifiers &= (BfmeKeyboardWord)~BfmeCapsLock;
					else
						m_modifiers |= BfmeCapsLock;
				}

				setKeyStatusData( BfmeKeyCaps, 1 );
			}
			return 0;

		case BfmeKeyLeftShift:
			if( getKeyStateBit( BfmeKeyLeftShift, BfmeKeyDown ) )
				m_modifiers |= BfmeLeftShift;
			else
				m_modifiers &= (BfmeKeyboardWord)~BfmeLeftShift;
			return 0;

		case BfmeKeyRightShift:
			if( getKeyStateBit( BfmeKeyRightShift, BfmeKeyDown ) )
				m_modifiers |= BfmeRightShift;
			else
				m_modifiers &= (BfmeKeyboardWord)~BfmeRightShift;
			return 0;

		case BfmeKeyLeftCtrl:
			if( getKeyStateBit( BfmeKeyLeftCtrl, BfmeKeyDown ) )
				m_modifiers |= BfmeLeftCtrl;
			else
				m_modifiers &= (BfmeKeyboardWord)~BfmeLeftCtrl;
			return 0;

		case BfmeKeyRightCtrl:
			if( getKeyStateBit( BfmeKeyRightCtrl, BfmeKeyDown ) )
				m_modifiers |= BfmeRightCtrl;
			else
				m_modifiers &= (BfmeKeyboardWord)~BfmeRightCtrl;
			return 0;

		case BfmeKeyLeftAlt:
			if( getKeyStateBit( BfmeKeyLeftAlt, BfmeKeyDown ) )
				m_modifiers |= BfmeLeftAlt;
			else
				m_modifiers &= (BfmeKeyboardWord)~BfmeLeftAlt;
			return 0;

		case BfmeKeyRightAlt:
			if( getKeyStateBit( BfmeKeyRightAlt, BfmeKeyDown ) )
				m_modifiers |= BfmeRightAlt;
			else
				m_modifiers &= (BfmeKeyboardWord)~BfmeRightAlt;
			return 0;

		default:
			if( ubKeyCode == m_shift2Key )
			{
				if( getKeyStateBit( m_shift2Key, BfmeKeyDown ) )
					m_modifiers |= BfmeShift2;
				else
					m_modifiers &= (BfmeKeyboardWord)~BfmeShift2;
				return 0;
			}

			if( m_modifiers & BfmeShift2 )
				return m_keyNames[ ubKeyCode ].shifted2;

			if( isShift() || getCapsState() &&
				iswalpha( m_keyNames[ ubKeyCode ].standard ) )
				return m_keyNames[ ubKeyCode ].shifted;

			return m_keyNames[ ubKeyCode ].standard;
	}
}

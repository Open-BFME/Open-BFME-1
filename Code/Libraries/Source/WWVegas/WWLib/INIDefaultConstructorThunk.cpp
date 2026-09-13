// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ob1 /Ireference/shims/ini_inline /Ireference/shims/ini /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
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
//	(c) 2001-2003 Electronic Arts Inc.																//
////////////////////////////////////////////////////////////////////////////////

// Real C++ body recovered from the canonical donor:
// Code/GameEngine/Source/Common/INI/ini_parsers.cpp
// BFME's retail layout is proven by the constructor bytes: the read counters
// are at +8/+C, ENDSCRIPT occupies +0x428, m_endOfFile is +0x42C, and the
// BfmeThingTK subobject begins at +0x834. These are TU-local layout shims so
// the shared INI header remains untouched.
#include <new>
#include "Common/AsciiString.h"

class BfmeThingTK
{
public:
	BfmeThingTK *bfmeInitTK();

private:
	void *m_bfmeVft;
	void *m_bfmeOne;
	void *m_bfmeTwo;
	void *m_bfmeThree;
	void *m_bfmeFour;
};

class INI
{
public:
	INI();

private:
	void *m_file;
	AsciiString m_filename;
	unsigned m_readBufferNext;
	unsigned m_readBufferUsed;
	char m_buffer[1028];
	const char *m_seps;
	const char *m_sepsPercent;
	const char *m_sepsColon;
	const char *m_sepsQuote;
	const char *m_blockEndToken;
	const char *m_endScriptToken;
	unsigned char m_endOfFile;
	char m_curBlockStart[1028];
	BfmeThingTK m_thing;
};

// ??0INI@@QAE@XZ
INI::INI() : m_file(NULL), m_filename("None")
{
    m_readBufferNext = 0;
    m_readBufferUsed = 0;
	m_seps = " \n\r\t=";
	m_sepsPercent = " \n\r\t=%%";
	m_sepsColon = " \n\r\t=:";
	m_sepsQuote = "\"\n=";
	m_blockEndToken = "END";
	m_endScriptToken = "ENDSCRIPT";
	m_endOfFile = 0;
	m_thing.bfmeInitTK();
	m_buffer[0] = 0;
    m_curBlockStart[0] = 0;
}

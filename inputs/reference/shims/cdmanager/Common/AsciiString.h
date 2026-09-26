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

// FILE: AsciiString.h
//-----------------------------------------------------------------------------
//
// BFME shadow shim (TU-scoped; only CDManager.cpp uses this -I path).
//
// Same StringBase<char>-backed design as reference/shims/namekeygenerator/:
// inline operator=(const char*) so CDManager::newDrive's setPath assignment
// compiles to the retail shape (inline strlen, then call
// StringBase<char>::set(const char*,int) @ 0x00887D20 on drive+0x1C).

#pragma once

#ifndef ASCIISTRING_H
#define ASCIISTRING_H

#include <string.h>

#include "../../../../game/Libraries/Source/WWVegas/WWLib/string_base.h"

class UnicodeString;

class AsciiString
{
public:
	AsciiString() { m_text = 0; }

	AsciiString(const AsciiString& that)
	{
		((StringBase<char>*)this)->StringBase<char>::StringBase(*(const StringBase<char>*)&that);
	}

	// SubsystemInterfaceList::initSubsystem default arg AsciiString name="".
	AsciiString(const char* s)
	{
		((StringBase<char>*)this)->StringBase<char>::StringBase(s);
	}

	~AsciiString()
	{
		((StringBase<char>*)this)->releaseBuffer();
	}

	AsciiString& operator=(const char* s)
	{
		((StringBase<char>*)this)->set(s, s ? (int)strlen(s) : 0);
		return *this;
	}

	AsciiString& operator=(const AsciiString& that)
	{
		((StringBase<char>*)this)->set(*(const StringBase<char>*)&that);
		return *this;
	}

	void clear()
	{
		((StringBase<char>*)this)->clear();
	}

	int compareNoCase(const AsciiString& that) const
	{
		return ((const StringBase<char>*)this)->compareNoCase(*(const StringBase<char>*)&that);
	}

	const char* str() const { return m_text ? (const char*)(m_text + 8) : ""; }

	static AsciiString TheEmptyString;

private:
	char* m_text;
};

inline bool operator==(const AsciiString& a, const AsciiString& b)
{
	return strcmp(a.str(), b.str()) == 0;
}

#endif // ASCIISTRING_H

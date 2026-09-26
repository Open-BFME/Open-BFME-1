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

// BFME shadow shim (TU-scoped; only Common/NameKeyGenerator.cpp uses this -I path).
//
// This supersedes the earlier debugptr/AsciiStringData-header model.
// keyToName/nameToKey(const char*)'s retail bodies were disassembled directly
// (build.read_target_bytes @0x8FD30/0x8FFC0) and PROVEN to call straight out
// to WWLib's already-matched StringBase<char> members:
//   - keyToName's `return bucket->m_nameString;` / `return TheEmptyString;`
//     both compile to `push &src; mov ecx,&dest; call 0x887b60` -- i.e. a
//     direct, out-of-line call to ?0?$StringBase@D@@AAE@ABV0@@Z (already
//     matched byte-exact, naked-asm guarded copy ctor, in
//     Code/Libraries/Source/WWVegas/WWLib/string_base.cpp).
//   - nameToKey(const char*)'s `b->m_nameString = nameString;` compiles the
//     strlen inline then calls 0x887d20 == ?set@?$StringBase@D@@QAEXPBDH@Z
//     (already matched, same file) directly with the explicit length -- NOT
//     a 1-arg AsciiString::set(const char*).
// This is exactly the same StringBase<char>-backed design already landed for
// the REAL (non-shimmed) AsciiString at
// Code/Libraries/Source/WWVegas/WWLib/ascii_string.h/.cpp (see its "Delegate
// so a caller inlines a `call StringBase<char>::method`" comment) -- that
// file's own ctor/operator= are defined OUT-OF-LINE, though, so cross-TU
// calls to them land on THEIR OWN matched addresses, not on StringBase's.
// Here the copy ctor / operator=(const char*) are instead defined INLINE
// (in-header), so the compiler inlines this thin wrapper AT NameKeyGenerator
// .cpp's call sites and emits the direct StringBase<char> call retail has --
// matching the disassembly above.
//
// AsciiString's data member is a single pointer (matches the already-proven
// "chars @ m_data+8" header size: StringBase<char>::Header is
// {int ref_count; ushort length; ushort capacity; T data[]} = 8 bytes), so
// Bucket's layout (vtbl@0, m_nextInSocket@4, m_key@8, m_nameString@0xc,
// sizeof 0x10) is UNCHANGED from the prior shim.

#pragma once

#ifndef ASCIISTRING_H
#define ASCIISTRING_H

#include <string.h>

// The real WWLib template this TU's AsciiString delegates to (already
// byte-matched via Code/Libraries/Source/WWVegas/WWLib/string_base.cpp).
// `friend class AsciiString;` inside it binds to whichever class named
// AsciiString this TU goes on to define below (standard not-yet-defined-
// friend idiom) -- so our reinterpret_cast + explicit-ctor-call pattern
// below gets access to StringBase<char>'s private ctors/dtor/releaseBuffer.
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

	// Only needed so reference/shims/sweep/Common/SubsystemInterface.h's
	// `AsciiString name=""` default argument (SubsystemInterfaceList::
	// initSubsystem, pulled in transitively but never called from this TU)
	// type-checks; not a call shape byte-verified against any retail body.
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

	// Dead code in this TU (never called from NameKeyGenerator.cpp) -- exists
	// only so SubsystemInterface::setName() and STLTypedefs.h's
	// rts::hash<AsciiString>/equal_to<AsciiString>/less_than_nocase<AsciiString>
	// full specializations (eagerly compiled, not lazily instantiated, since
	// they're non-template) type-check.
	AsciiString& operator=(const AsciiString& that)
	{
		((StringBase<char>*)this)->set(*(const StringBase<char>*)&that);
		return *this;
	}

	int compareNoCase(const AsciiString& that) const
	{
		return ((const StringBase<char>*)this)->compareNoCase(*(const StringBase<char>*)&that);
	}

	// NOT delegated to StringBase<char>::str() (unlike the real
	// Code/Libraries/Source/WWVegas/WWLib/ascii_string.h): that method has no
	// standalone body anywhere in retail (zero matched rows for
	// ?str@?$StringBase@D@@) -- it is always fully inlined at its call sites,
	// which this TU-scoped delegation (calling an out-of-line, unseen .cpp
	// definition) can't reproduce. nameToKey(const char*)'s
	// `b->m_nameString.str()` disassembles to exactly this inline shape
	// (`mov eax,[bucket+0xc]; test eax,eax; lea esi,[eax+8]; jne ...; mov
	// esi,<empty-string literal>` -- no call at all), so inline the same
	// ternary here directly instead of forwarding.
	const char* str() const { return m_text ? (const char*)(m_text + 8) : ""; }

	static AsciiString TheEmptyString;

private:
	char* m_text;
};

// Dead code in this TU -- see the compareNoCase comment above.
inline bool operator==(const AsciiString& a, const AsciiString& b)
{
	return strcmp(a.str(), b.str()) == 0;
}

#endif // ASCIISTRING_H

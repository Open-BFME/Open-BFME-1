// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/shims/namekeygenerator /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
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

// FILE: NameKeyGeneratorNameToLowercaseKey.cpp
// Own TU for NameKeyGenerator::nameToLowercaseKey(const char*)@0x9EDD70 (187B).
// Kept separate from Common/NameKeyGenerator.cpp because that file carries a
// pre-existing nonmatching row (parseStringAsNameKeyType, a different BFME
// function) that blocks whole-file byte verification, and this reconstruction
// byte-matches independently here.
//
// BFME retail compiled this method against a stale header (a real in-image
// inconsistency): its Bucket has NO vtable ({m_nextInSocket@0, m_key@4,
// m_nameString@8}, 12 bytes) and m_sockets starts at this+4 with m_nextID at
// this+0x2bf40 -- whereas the matched siblings (init/reset/nameToKey/
// freeSockets) use the vptr'd Bucket with m_sockets at this+8 and m_nextID at
// this+0x2bf44. Retail's early `if (!nameString) return NAMEKEY_INVALID;` is
// also proven by the absence of the `s ? strlen(s) : 0` test in the
// nameString store below. Model the stale layout locally so the shared shim
// (used by the matched siblings) stays untouched.

#include "PreRTS.h"

// calcHashForLowercaseString lives in Common/NameKeyGenerator.cpp (matched
// standalone body @0x8F3C0); declared here rather than shared so this TU
// emits the same out-of-line call retail makes (through its ILT thunk).
UnsignedInt calcHashForLowercaseString(const char* p);

//------------------------------------------------------------------------------------------------- 
NameKeyType NameKeyGenerator::nameToLowercaseKey(const char* nameString)
{
	struct LegacyBucket
	{
		LegacyBucket() : m_nextInSocket(NULL), m_key(NAMEKEY_INVALID) { }
		LegacyBucket *m_nextInSocket;
		NameKeyType m_key;
		AsciiString m_nameString;
	};
	LegacyBucket **const sockets = reinterpret_cast<LegacyBucket **>(reinterpret_cast<char *>(this) + 4);
	UnsignedInt *const nextID = reinterpret_cast<UnsignedInt *>(reinterpret_cast<char *>(this) + 0x2bf40);

	if (nameString == NULL)
		return NAMEKEY_INVALID;

	UnsignedInt hash = calcHashForLowercaseString(nameString) % SOCKET_COUNT;

	// hmm, do we have it already?
	for (LegacyBucket *b = sockets[hash]; b; b = b->m_nextInSocket)
	{
		if (_strcmpi(nameString, b->m_nameString.str()) == 0)
			return b->m_key; 
	}

	// nope, guess not. let's allocate it.
	LegacyBucket *b = new LegacyBucket;
	b->m_key = (NameKeyType)(*nextID)++;
	b->m_nameString = nameString;
	b->m_nextInSocket = sockets[hash];
	sockets[hash] = b;

	return b->m_key;

}  // end nameToLowercaseKey

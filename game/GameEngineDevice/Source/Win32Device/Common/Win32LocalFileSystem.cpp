// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/win32localfilesystem_wide /Iinputs/reference/shims/asciistring_thin /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
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

///////// Win32LocalFileSystem.cpp /////////////////////////
// Bryan Cleveland, August 2002
////////////////////////////////////////////////////////////

// BFME's retail AsciiStringData has an extra 4-byte field (debug ptr) before the
// string buffer, so force the _INTERNAL layout without enabling debug side effects.
#define _INTERNAL
#define DISABLE_ALLOW_DEBUG_UTILS
#define DISABLE_MEMORYPOOL_DEBUG_CUSTOM_NEW

#include <windows.h>
#include "Common/AsciiString.h"
#include "Common/GameMemory.h"
#include "Common/PerfTimer.h"
#include "Win32Device/Common/Win32LocalFileSystem.h"
#include "Win32Device/Common/Win32LocalFile.h"
#include <io.h>

// ??0Win32LocalFileSystem@@QAE@XZ present-unmatched
Win32LocalFileSystem::Win32LocalFileSystem() : LocalFileSystem() 
{
}

Win32LocalFileSystem::~Win32LocalFileSystem() {
}


// BFME's string keeps its length as a 16-bit field at buffer+4 and its
// characters at buffer+8, and the one-argument set/concat/find are inline
// wrappers over the two-argument StringBase forms rather than the expansions
// down to ensureUniqueBufferOfSize the reference header does. Declaring
// StringBase here rather than inventing a name makes these calls mangle to the
// bodies the ledger already claims.
static inline Int bfmeLength( const AsciiString &s )
{
	const char *d = *(const char * const *)&s;
	return d ? *(const unsigned short *)(d + 4) : 0;
}

static inline const char *bfmeStr( const AsciiString &s )
{
	const char *d = *(const char * const *)&s;
	return d ? d + 8 : "";
}

template <class T> class StringBase
{
public:
	void set( const T *s, int len );
	void concat( const T *s, int len );
};

static inline void bfmeSet( AsciiString &s, const char *v )
{
	((StringBase<char> *)&s)->set( v, v ? (int)strlen( v ) : 0 );
}

static inline void bfmeConcat( AsciiString &s, const AsciiString &v )
{
	((StringBase<char> *)&s)->concat( bfmeStr( v ), bfmeLength( v ) );
}

static inline void bfmeConcat( AsciiString &s, char c )
{
	((StringBase<char> *)&s)->concat( &c, 1 );
}

static void (AsciiString::* const bfmeKeepAsciiConcat)(const AsciiString &) =
	&AsciiString::concat;

static inline const char *bfmeFind( const AsciiString &s, char c )
{
	const char *p = bfmeStr( s );
	const char *end = p + bfmeLength( s );
	for (; p != end; ++p) {
		if (*p == c) {
			return p;
		}
	}
	return NULL;
}

// ?update@Win32LocalFileSystem@@UAEXXZ present-unmatched
void Win32LocalFileSystem::update() 
{
}

void Win32LocalFileSystem::init() 
{
}

// ?reset@Win32LocalFileSystem@@UAEXXZ present-unmatched
// Deliberately not claimed, unlike init above. Slots 8 and 9 of vtable
// 0x01143B98 are both one-byte bare rets at 0x009CDDB0 and 0x009CDD90, and they
// are reset and update in some order -- but nothing says which. init was
// claimable because a call site pins it: the FileSystem setup at 0x009C8820
// calls TheLocalFileSystem through [eax+4], slot 1. There is no equivalent for
// these two, and a bare ret matches every empty function in the image, so
// picking one would be a coin flip dressed up as a match. Find a caller first.
void Win32LocalFileSystem::reset() 
{
}

//DECLARE_PERF_TIMER(Win32LocalFileSystem_doesFileExist)
Bool Win32LocalFileSystem::doesFileExist(const Char *filename) const
{
	//USE_PERF_TIMER(Win32LocalFileSystem_doesFileExist)
	if (_access(filename, 0) == 0) {
		return TRUE;
	}
	return FALSE;
}

// ?getFileInfo@Win32LocalFileSystem@@UBE_NABVAsciiString@@PAUFileInfo@@@Z
Bool Win32LocalFileSystem::getFileInfo(const AsciiString& filename, FileInfo *fileInfo) const 
{
	WIN32_FIND_DATA findData;
	HANDLE findHandle = NULL;
	findHandle = FindFirstFile(filename.str(), &findData);

	if (findHandle == INVALID_HANDLE_VALUE) {
		return FALSE;
	}

	fileInfo->timestampHigh = findData.ftLastWriteTime.dwHighDateTime;
	fileInfo->timestampLow = findData.ftLastWriteTime.dwLowDateTime;
	fileInfo->sizeHigh = findData.nFileSizeHigh;
	fileInfo->sizeLow = findData.nFileSizeLow;

	FindClose(findHandle);

	return TRUE;
}

// BFME's string buffer header is {int refCount; unsigned short length; unsigned
// short capacity;}, so the length is a 16-bit field at +4 and the characters
// start at +8. Retail reads both directly -- movzx ecx,[eax+4] once, compared
// twice, then add eax,8 for the pointer. The Zero Hour AsciiString this TU
// includes has the older four-byte header, so its getLength() inlines a strlen
// and its str() adds 4; both are wrong here. Reading the fields is what retail
// does. The whole TU cannot simply switch to the BFME string shim: this file
// also owns ?concat@AsciiString@@QAEXABV1@@Z, which is a real out-of-line body
// here and collapses to a 5-byte thunk under the shim.
// ?createDirectory@Win32LocalFileSystem@@UAE_NVAsciiString@@@Z
Bool Win32LocalFileSystem::createDirectory(AsciiString directory)
{
	if ((bfmeLength(directory) > 0) && (bfmeLength(directory) < _MAX_DIR)) {
		return (CreateDirectory(bfmeStr(directory), NULL) != 0);
	}
	return FALSE;
}

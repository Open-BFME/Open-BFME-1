// cl: /DNDEBUG /MD /EHsc /Ireference/shims/win32localfilesystem_wide /Ireference/shims/asciistring_thin /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
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

static inline void bfmeConcat( AsciiString &s, const char *v )
{
	((StringBase<char> *)&s)->concat( v, v ? (int)strlen( v ) : 0 );
}

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

//DECLARE_PERF_TIMER(Win32LocalFileSystem_openFile)
// This is Zero Hour's openFile, and in BFME it is NOT the two-argument form.
// BFME widened openFile to four parameters and left a 22-byte forwarder at the
// two-argument slot; that forwarder is matched in
// Win32LocalFileSystem_openFile.cpp, and the body below belongs to the wide
// form at slot 3, retail 0x009CDF50, 571 bytes. The THIRD parameter is a seek
// offset applied on success -- see docs/filesystem_family.md for the frame
// arithmetic that pins it, and Win32BIGFile::openFile, which is matched and
// uses its third as an offset too.
//
// STATE: compiles to 571 bytes against retail's 571, NOT claimed. Every call
// target, every constant, every stack offset, every vtable slot and every
// control-flow edge agrees. What is left is the assignment of two callee-saved
// registers, plus one instruction pair that retail schedules the other way
// round:
//
//   retail   this -> edi,  the zero constant -> ebp
//   here     this -> ebp,  the zero constant -> edi
//
// The two swapped, nothing else. Both are used exactly as often on both sides
// -- twelve references to the zero, three to this -- so the usual density
// tie-break does not explain it. It costs 271 of 571 bytes rather than four,
// because ebp-relative addressing needs a displacement byte: retail's
// `mov eax,[edi]` is two bytes and this file's `mov eax,[ebp]` is three, and
// that one byte shifts every instruction after it.
//
// Ruled out, each measured rather than assumed:
//   * /G7 -- looked like a fix (271 -> 9) but the 9 was a DIFFERENT function in
//     this TU. Measured against openFile it is 495, and it breaks doesFileExist,
//     which matches today. Retail is not /G7 in any case: it emits `inc eax`
//     where /G7 emits `add eax,1`.
//   * /G6, /G5, /Ob1, /Ot, /Gs, /GF- -- no change at all (271).
//   * /Oy- -- worse (504), and it keeps ebp as a frame pointer, which retail
//     plainly does not do.
//
// The scheduling difference, for the record: at 0x009CE065 retail stores the
// by-value AsciiString temporary's address for the unwinder and then loads the
// receiver, `mov [esp+0x28],esp` / `mov ecx,esp`; this file emits the same two
// instructions the other way round.
// ?openFile@Win32LocalFileSystem@@UAEPAVFile@@PBDHHH@Z present-unmatched
File * Win32LocalFileSystem::openFile(const Char *filename, Int access, Int seekTo, Int a4)
{
	//USE_PERF_TIMER(Win32LocalFileSystem_openFile)
	// Retail checks the name BEFORE allocating -- the inline strlen and its
	// jnz come first in the disassembly, with the operator new call after.
	if (strlen(filename) <= 0) {
		return NULL;
	}

	Win32LocalFile *file = newInstance( Win32LocalFile );	

	if (access & File::WRITE) {
		// if opening the file for writing, we need to make sure the directory is there
		// before we try to create the file.
		AsciiString string;
		bfmeSet(string, filename);
		AsciiString token;
		AsciiString dirName;
		string.nextToken(&token, "\\/");
		dirName = token;
		while ((bfmeFind(token, '.') == NULL) || (bfmeFind(string, '.') != NULL)) {
			createDirectory(dirName);
			string.nextToken(&token, "\\/");
			bfmeConcat(dirName, '\\');
			bfmeConcat(dirName, token);
		}
	}

	if (file->open(filename, access) == FALSE) {
		file->close();
		// Retail frees this with a plain delete -- push 1, call [eax], the scalar
		// deleting destructor at slot 0 -- not with the pool's deleteInstance,
		// which would read the pool out of the vtable first and then call it.
		delete file;
		file = NULL;
	} else {
		file->deleteOnClose();
		// BFME only: hand the file back already positioned, which is what
		// reading a member out of a BIG archive needs. seek is File slot 5 and
		// mode 1 is CURRENT.
		if (seekTo != 0) {
			file->seek(seekTo, File::CURRENT);
		}
	}

// this will also need to play nice with the STREAMING type that I added, if we ever enable this

// srj sez: this speeds up INI loading, but makes BIG files unusable. 
// don't enable it without further tweaking.
//
// unless you like running really slowly.
//	if (!(access&File::WRITE)) {
//		// Return a ramfile.
//		RAMFile *ramFile = newInstance( RAMFile );
//		if (ramFile->open(file)) {
//			file->close(); // is deleteonclose, so should delete.
//			ramFile->deleteOnClose();
//			return ramFile;
//		}	else {
//			ramFile->close();
//			ramFile->deleteInstance();
//		}
//	}

	return file;
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

// ?getFileListInDirectory@Win32LocalFileSystem@@UBEXABVAsciiString@@00AAV?$set@VAsciiString@@U?$less_than_nocase@VAsciiString@@@rts@@V?$allocator@VAsciiString@@@_STL@@@_STL@@_N@Z present-unmatched
void Win32LocalFileSystem::getFileListInDirectory(const AsciiString& currentDirectory, const AsciiString& originalDirectory, const AsciiString& searchName, FilenameList & filenameList, Bool searchSubdirectories) const
{
	HANDLE fileHandle = NULL;
	WIN32_FIND_DATA findData;

	char search[_MAX_PATH];
	AsciiString asciisearch;
	asciisearch = originalDirectory;
	bfmeConcat(asciisearch, currentDirectory);
	bfmeConcat(asciisearch, searchName);
	strcpy(search, bfmeStr(asciisearch));

	Bool done = FALSE;

	fileHandle = FindFirstFile(search, &findData);
	done = (fileHandle == INVALID_HANDLE_VALUE);

	while (!done)	{
		if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
				(strcmp(findData.cFileName, ".") && strcmp(findData.cFileName, ".."))) {
			// if we haven't already, add this filename to the list.
				// a stl set should only allow one copy of each filename
				AsciiString newFilename;
				newFilename = originalDirectory;
				bfmeConcat(newFilename, currentDirectory);
				bfmeConcat(newFilename, findData.cFileName);
				if (filenameList.find(newFilename) == filenameList.end()) {
					filenameList.insert(newFilename);
				}
		}

		done = (FindNextFile(fileHandle, &findData) == 0);
	}
	FindClose(fileHandle);

	if (searchSubdirectories) {
		AsciiString subdirsearch;
		subdirsearch = originalDirectory;
		bfmeConcat(subdirsearch, currentDirectory);
		bfmeConcat(subdirsearch, "*.");
		fileHandle = FindFirstFile(bfmeStr(subdirsearch), &findData);
		done = fileHandle == INVALID_HANDLE_VALUE;

		while (!done) {
			if ((findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
					(strcmp(findData.cFileName, ".") && strcmp(findData.cFileName, ".."))) {

					AsciiString tempsearchstr;
					bfmeConcat(tempsearchstr, currentDirectory);
					bfmeConcat(tempsearchstr, findData.cFileName);
					bfmeConcat(tempsearchstr, '\\');
					
					// recursively add files in subdirectories if required.
					getFileListInDirectory(tempsearchstr, originalDirectory, searchName, filenameList, searchSubdirectories);
			}

			done = (FindNextFile(fileHandle, &findData) == 0);
		}

		FindClose(fileHandle);
	}

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

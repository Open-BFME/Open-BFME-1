// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
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

////// Win32BIGFile.cpp /////////////////////////
// Bryan Cleveland, August 2002
/////////////////////////////////////////////////////

#include "Common/LocalFile.h"
#include "Common/LocalFileSystem.h"
// BFME de-pooled this glue: retail's per-class `operator delete(void*, MagicEnum)`
// is one 12-byte body (0x007EFFF0) that calls the CRT free IMPORT THUNK -- a
// `call rel32` into `jmp [__imp__free]` -- where ::operator delete (0x00881EB0)
// is a different function. <stdlib.h> declares free __declspec(dllimport) under
// /MD, which compiles to the `ff 15` indirect form instead, so the C-linkage
// redeclaration below is what names `_free` for the linker's thunk; it is
// namespaced so every other free() call in this TU keeps the indirect form
// retail also uses. Same TU-scoped override Team.cpp already carries.
namespace BfmePoolGlue { extern "C" void __cdecl free(void *); }
#undef MEMORY_POOL_GLUE_WITHOUT_GCMP
#define MEMORY_POOL_GLUE_WITHOUT_GCMP(ARGCLASS) \
protected: \
	virtual ~ARGCLASS(); \
public: \
	enum ARGCLASS##MagicEnum { ARGCLASS##_GLUE_NOT_IMPLEMENTED = 0 }; \
public: \
	inline void *operator new(size_t s, ARGCLASS##MagicEnum e DECLARE_LITERALSTRING_ARG2) \
	{ return MP_GLUE_ALLOCATE(ARGCLASS); } \
public: \
	inline void operator delete(void *p, ARGCLASS##MagicEnum e DECLARE_LITERALSTRING_ARG2) \
	{ BfmePoolGlue::free(p); } \
protected: \
	inline void *operator new(size_t s) { return ::operator new(s); } \
	inline void operator delete(void *p) { ::operator delete(p); } \
private: \
	virtual MemoryPool *getObjectMemoryPool() { return ARGCLASS::getClassMemoryPool(); } \
public:

#include "Common/RAMFile.h"
#include "Common/StreamingArchiveFile.h"
#include "Common/GameMemory.h"
#include "Common/PerfTimer.h"
#include "Win32Device/Common/Win32BIGFile.h"

//============================================================================
// Win32BIGFile::Win32BIGFile
//============================================================================

Win32BIGFile::Win32BIGFile()
{

}

//============================================================================
// Win32BIGFile::~Win32BIGFile lives in the sibling Win32BIGFileLifecycle.cpp. Its
// source body is empty, but the compiler-generated part destroys m_name and
// m_path, and retail reaches StringBase<char>::releaseBuffer by a call where
// this file's Zero Hour Common/AsciiString.h inlines it -- the same divergence
// that moved getName and getPath out. See that file's header comment.
//============================================================================
// Win32BIGFile::openFile
//============================================================================

// The signature Zero Hour declares is BFME's two-argument openFile, and that one
// is matched from Win32BIGFileOpen.cpp -- it is a bare forward, not this. What
// stands here is Zero Hour's body, kept only so this translation unit still
// compiles the way its eight matched rows were proven under. BFME's real body
// moved into the four-argument overload and is matched from
// Win32BIGFileOpenArchived.cpp; read that one, not this.
// byte-exact reconstruction: game/GameEngineDevice/Source/Win32Device/Common/Win32BIGFileOpen.cpp
// ?openFile@Win32BIGFile@@UAEPAVFile@@PBDH@Z present-unmatched
File* Win32BIGFile::openFile( const Char *filename, Int access )
{
	const ArchivedFileInfo *fileInfo = getArchivedFileInfo(AsciiString(filename));

	if (fileInfo == NULL) {
		return NULL;
	}

	RAMFile *ramFile = NULL;
	
	if (BitTest(access, File::STREAMING)) 
		ramFile = newInstance( StreamingArchiveFile );
	else 
		ramFile = newInstance( RAMFile );

	ramFile->deleteOnClose();
	if (ramFile->openFromArchive(m_file, fileInfo->m_filename, fileInfo->m_offset, fileInfo->m_size) == FALSE) {
		ramFile->close();
		ramFile = NULL;
		return NULL;
	}

	if ((access & File::WRITE) == 0) {
		// requesting read only access. Just return the RAM file.
		return ramFile;
	}

	// whoever is opening this file wants write access, so copy the file to the local disk
	// and return that file pointer.

	File *localFile = TheLocalFileSystem->openFile(filename, access);
	if (localFile != NULL) {
		ramFile->copyDataToFile(localFile);
	}

	ramFile->close();
	ramFile = NULL;

	return localFile;
}

//============================================================================
// Win32BIGFile::closeAllFiles
//============================================================================

void Win32BIGFile::closeAllFiles( void )
{

}

//============================================================================
// Win32BIGFile::getName and Win32BIGFile::getPath live in the sibling
// Win32BIGFileLifecycle.cpp. Both are one `return m_name;`, but retail reaches
// StringBase<char>'s copy constructor by a call where this file's Zero Hour
// Common/AsciiString.h inlines the refcount bump, so they only match against a
// delegating AsciiString -- which the rest of this file's matched rows do not
// want. See that file's header comment.
//============================================================================
// Win32BIGFile::setSearchPriority
//============================================================================

void Win32BIGFile::setSearchPriority( Int new_priority )
{

}

//============================================================================
// Win32BIGFile::close
//============================================================================

void Win32BIGFile::close( void )
{

}

//============================================================================
// Win32BIGFile::getFileInfo lives in the sibling Win32BIGFileGetInfo.cpp. It
// needs the same delegating AsciiString the destructor and the name accessors
// do -- it builds a temporary from the archive's own filename -- and BFME
// appends a compressed-size decode that Zero Hour's body has no trace of.
//============================================================================

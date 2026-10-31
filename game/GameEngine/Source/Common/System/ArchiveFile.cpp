// cl: /DNDEBUG /DBFME_STLP_NODE_ALLOC /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/win32localfilesystem_wide /Iinputs/reference/shims/zhcanonascii /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
#define __PLACEMENT_VEC_NEW_INLINE  // always.h/GameMemory.h define array placement-new themselves
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
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

/////////ArchiveFile.cpp ///////////////////////
// Bryan Cleveland, August 2002
////////////////////////////////////////////////

// BFME's MemoryPoolObject contributes ONE vtable slot, not two -- see
// inputs/reference/shims/win32localfilesystem_wide/Common/GameMemory.h. That directory
// name is wrong for a fact this general -- the header belongs somewhere neutral,
// and moving it is a inputs/reference/shims/ change, which forces the full gate. Master
// cannot pass one right now: three in-flight sources carry zero matched rows.
// Move it when that clears. Pulled in BEFORE PreRTS.h
// on purpose: PreRTS.h lives in inputs/reference/shims/sweep and includes
// "Common/GameMemory.h", which MSVC resolves against the including file's own
// directory first, so sweep's copy would win no matter where bfme_mempool sits
// on the include path. Getting there first lets the _GAME_MEMORY_H_ guard skip
// it. Without this, File::close is slot 3 and every call through it is wrong.
#include "Common/GameMemory.h"
#include "PreRTS.h"

#include "Common/ArchiveFile.h"
#include "Common/ArchiveFileSystem.h"
#include "Common/File.h"
#include "Common/PerfTimer.h"

ArchiveFile::ArchiveFile() : m_file(NULL)
{
	m_rootDirectory.clear();
}

// checks to see if str matches searchString.  Search string is done in the
// using * and ? as wildcards. * is used to denote any number of characters,
// and ? is used to denote a single wildcard character.
static Bool SearchStringMatches(AsciiString str, AsciiString searchString) 
{
	if (str.getLength() == 0) {
		if (searchString.getLength() == 0) {
			return TRUE;
		}
		return FALSE;
	}
	if (searchString.getLength() == 0) {
		return FALSE;
	}

	const char *c1 = str.str();
	const char *c2 = searchString.str();

	while ((*c1 == *c2) || (*c2 == '?') || (*c2 == '*')) {
		if ((*c1 == *c2) || (*c2 == '?')) {
			++c1;
			++c2;
		} else if (*c2 == '*') {
			++c2;
			if (*c2 == 0) {
				return TRUE;
			}
			while (*c1 != 0) {
				if (SearchStringMatches(AsciiString(c1), AsciiString(c2))) {
					return TRUE;
				}
				++c1;
			}
		}
		if (*c1 == 0) {
			if (*c2 == 0) {
				return TRUE;
			}
			return FALSE;
		}
		if (*c2 == 0) {
			return FALSE;
		}
	}
	return FALSE;
}

ArchiveFile::~ArchiveFile() 
{
	if (m_file != NULL) {
		m_file->close();
		m_file = NULL;
	}
}

// ?addFile@ArchiveFile@@ present-unmatched
void ArchiveFile::addFile(const AsciiString& path, const ArchivedFileInfo *fileInfo) 
{
	AsciiString temp;
	temp = path;
	temp.toLower();
	AsciiString token;
	AsciiString debugpath;

	DetailedArchivedDirectoryInfo *dirInfo = &m_rootDirectory;

	temp.nextToken(&token, "\\/");

	while (token.getLength() > 0) {
		if (dirInfo->m_directories.find(token) == dirInfo->m_directories.end()) 
		{
			dirInfo->m_directories[token].clear();
			dirInfo->m_directories[token].m_directoryName = token;
		}

		debugpath.concat(token);
		debugpath.concat('\\');
		dirInfo = &(dirInfo->m_directories[token]);
		temp.nextToken(&token, "\\/");
	}

	dirInfo->m_files[fileInfo->m_filename] = *fileInfo;
	//path.concat(fileInfo->m_filename);
}

// ?getFileListInDirectory@ArchiveFile@@QBEXABVAsciiString@@00AAV?$set@VAsciiString@@U?$less_than_nocase@VAsciiString@@@rts@@V?$allocator@VAsciiString@@@_STL@@@_STL@@_N@Z: retail body is in game/GameEngine/Source/Common/System/ArchiveFileGetFileList.cpp

// ?getFileListInDirectory@ArchiveFile@@QBEXPBVDetailedArchivedDirectoryInfo@@ABVAsciiString@@1AAV?$set@VAsciiString@@U?$less_than_nocase@VAsciiString@@@rts@@V?$allocator@VAsciiString@@@_STL@@@_STL@@_N@Z: retail body is in game/GameEngine/Source/Common/System/ArchiveFileGetFileList.cpp

void ArchiveFile::attachFile(File *file) 
{
	if (m_file != NULL) {
		m_file->close();
		m_file = NULL;
	}
	m_file = file;
}

// ?getArchivedFileInfo@ArchiveFile@@IBEPBUArchivedFileInfo@@ABVAsciiString@@@Z: retail body is in game/GameEngine/Source/Common/System/ArchiveFileGetArchivedFileInfo.cpp

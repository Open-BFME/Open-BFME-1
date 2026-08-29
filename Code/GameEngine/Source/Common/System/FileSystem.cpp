// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
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

//----------------------------------------------------------------------------
//                                                                          
//                       Westwood Studios Pacific.                          
//                                                                          
//                       Confidential Information                           
//                Copyright(C) 2001 - All Rights Reserved                  
//                                                                          
//----------------------------------------------------------------------------
//
// Project:   WSYS Library
//
// Module:    IO
//
// File name: IO_FileSystem.cpp
//
// Created:   4/23/01
//
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
//         Includes                                                      
//----------------------------------------------------------------------------

#include "PreRTS.h"
#include "Common/File.h"
#include "Common/FileSystem.h"

#include "Common/ArchiveFileSystem.h"
#include "Common/CDManager.h"
#include "Common/GameAudio.h"
#include "Common/LocalFileSystem.h"
#include "Common/PerfTimer.h"


DECLARE_PERF_TIMER(FileSystem)

//----------------------------------------------------------------------------
//         Externals                                                     
//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
//         Defines                                                         
//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
//         Private Types                                                     
//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
//         Private Data                                                     
//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
//         Public Data                                                      
//----------------------------------------------------------------------------

//===============================
// TheFileSystem 
//===============================
/**
  *	This is the FileSystem's singleton class. All file access 
	* should be through TheFileSystem, unless code needs to use an explicit
	* File or FileSystem derivative.
	*
	* Using TheFileSystem->open and File exclusively for file access, particularly
	* in library or modular code, allows applications to transparently implement 
	* file access as they see fit. This is particularly important for code that
	* needs to be shared between applications, such as games and tools.
	*/
//===============================

FileSystem	*TheFileSystem = NULL;

//----------------------------------------------------------------------------
//         Private Prototypes                                               
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
//         Private Functions                                               
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
//         Public Functions                                                
//----------------------------------------------------------------------------


//============================================================================
// FileSystem::FileSystem
//============================================================================

// byte-exact reconstruction: Code/GameEngine/Source/Common/System/FileSystemCtor.cpp
// ??0FileSystem@@ present-unmatched
FileSystem::FileSystem()
{

}

//============================================================================
// FileSystem::~FileSystem
//============================================================================

// ??1FileSystem@@ present-unmatched
FileSystem::~FileSystem()
{

}

//============================================================================
// FileSystem::init
//============================================================================

// ?init@FileSystem@@ present-unmatched
void		FileSystem::init( void )
{
	TheLocalFileSystem->init();
	TheArchiveFileSystem->init();
}

//============================================================================
// FileSystem::update
//============================================================================

// ?update@FileSystem@@ present-unmatched
void		FileSystem::update( void )
{
	USE_PERF_TIMER(FileSystem)
	TheLocalFileSystem->update();
	TheArchiveFileSystem->update();
}

//============================================================================
// FileSystem::reset
//============================================================================

// ?reset@FileSystem@@ present-unmatched
void		FileSystem::reset( void )
{
	USE_PERF_TIMER(FileSystem)
	TheLocalFileSystem->reset();
	TheArchiveFileSystem->reset();
}

//============================================================================
// FileSystem::open
//============================================================================

// byte-exact reconstruction: Code/GameEngine/Source/Common/System/FileSystem_openFile.cpp
// ?openFile@FileSystem@@ present-unmatched
File*		FileSystem::openFile( const Char *filename, Int access ) 
{
	USE_PERF_TIMER(FileSystem)
	File *file = NULL;

	if ( TheLocalFileSystem != NULL )
	{
		file = TheLocalFileSystem->openFile( filename, access );
	}

	if ( (TheArchiveFileSystem != NULL) && (file == NULL) )
	{
		file = TheArchiveFileSystem->openFile( filename );
	}

	return file;
}

//============================================================================
// FileSystem::doesFileExist — matched body in FileSystem_doesFileExist.cpp
// Keep a map touch so the pair/construct helpers claimed on this TU still emit.
//============================================================================
static void fileSystemExistCacheTouch(std::map<unsigned, bool> &cache, unsigned key, bool value)
{
	cache[key] = value;
}
// Force instantiation of the pair helpers claimed on this TU (were part of ZH doesFileExist).
static void (*s_fileSystemExistCacheTouch)(std::map<unsigned, bool> &, unsigned, bool) = fileSystemExistCacheTouch;

//============================================================================
// FileSystem::getFileListInDirectory
//============================================================================
// ?getFileListInDirectory@FileSystem@@ present-unmatched
void FileSystem::getFileListInDirectory(const AsciiString& directory, const AsciiString& searchName, FilenameList &filenameList, Bool searchSubdirectories) const
{
	USE_PERF_TIMER(FileSystem)
	TheLocalFileSystem->getFileListInDirectory(AsciiString(""), directory, searchName, filenameList, searchSubdirectories);
	TheArchiveFileSystem->getFileListInDirectory(AsciiString(""), directory, searchName, filenameList, searchSubdirectories);
}

//============================================================================
// FileSystem::getFileInfo
//============================================================================
// ?getFileInfo@FileSystem@@ present-unmatched
Bool FileSystem::getFileInfo(const AsciiString& filename, FileInfo *fileInfo) const
{
	USE_PERF_TIMER(FileSystem)
	if (fileInfo == NULL) {
		return FALSE;
	}
	memset(fileInfo, 0, sizeof(fileInfo));
	
	if (TheLocalFileSystem->getFileInfo(filename, fileInfo)) {
		return TRUE;
	}

	if (TheArchiveFileSystem->getFileInfo(filename, fileInfo)) {
		return TRUE;
	}

	return FALSE;
}

//============================================================================
// FileSystem::createDirectory
//============================================================================
// byte-exact reconstruction: Code/GameEngine/Source/Common/System/FileSystem_createDirectory.cpp
// ?createDirectory@FileSystem@@ present-unmatched
Bool FileSystem::createDirectory(AsciiString directory) 
{
	USE_PERF_TIMER(FileSystem)
	if (TheLocalFileSystem != NULL) {
		return TheLocalFileSystem->createDirectory(directory);
	}
	return FALSE;
}

//============================================================================
// FileSystem::areMusicFilesOnCD
//============================================================================
// ?areMusicFilesOnCD@FileSystem@@ present-unmatched
Bool FileSystem::areMusicFilesOnCD()
{
	if (!TheCDManager) {
		DEBUG_LOG(("FileSystem::areMusicFilesOnCD() - No CD Manager; returning false\n"));
		return FALSE;
	}

	AsciiString cdRoot;
	Int dc = TheCDManager->driveCount();
	for (Int i = 0; i < dc; ++i) {
		DEBUG_LOG(("FileSystem::areMusicFilesOnCD() - checking drive %d\n", i));
		CDDriveInterface *cdi = TheCDManager->getDrive(i);
		if (!cdi) {
			continue;
		}

		cdRoot = cdi->getPath();
		if (!cdRoot.endsWith("\\"))
			cdRoot.concat("\\");
		cdRoot.concat("genseczh.big");
		DEBUG_LOG(("FileSystem::areMusicFilesOnCD() - checking for %s\n", cdRoot.str()));
		File *musicBig = TheLocalFileSystem->openFile(cdRoot.str());
		if (musicBig)
		{
			DEBUG_LOG(("FileSystem::areMusicFilesOnCD() - found it!\n"));
			musicBig->close();
			return TRUE;
		}
	}
	return FALSE;
}
//============================================================================
// FileSystem::loadMusicFilesFromCD
//============================================================================
// ?loadMusicFilesFromCD@FileSystem@@ present-unmatched
void FileSystem::loadMusicFilesFromCD()
{
	if (!TheCDManager) {
		return;
	}

	AsciiString cdRoot;
	Int dc = TheCDManager->driveCount();
	for (Int i = 0; i < dc; ++i) {
		CDDriveInterface *cdi = TheCDManager->getDrive(i);
		if (!cdi) {
			continue;
		}

		cdRoot = cdi->getPath();
		if (TheArchiveFileSystem->loadBigFilesFromDirectory(cdRoot, MUSIC_BIG)) {
			break;
		}
	}
}

//============================================================================
// FileSystem::unloadMusicFilesFromCD
//============================================================================
// ?unloadMusicFilesFromCD@FileSystem@@ present-unmatched
void FileSystem::unloadMusicFilesFromCD()
{
	if (!(TheAudio && TheAudio->isMusicPlayingFromCD())) {
		return;
	}

	TheArchiveFileSystem->closeArchiveFile( MUSIC_BIG );
}

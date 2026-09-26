// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
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

//----------------------------------------------------------------------------
//                                                                          
//                       Westwood Studios Pacific.                          
//                                                                          
//                       Confidential Information                           
//                Copyright (C) 2001 - All Rights Reserved                  
//                                                                          
//----------------------------------------------------------------------------
//
// Project:   Generals
//
// Module:    Game Engine Device Win32 Common
//
// File name: Win32CDManager.cpp
//
// Created:   11/26/01 TR
//
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
//         Includes                                                      
//----------------------------------------------------------------------------

#include "windows.h"
#include <string.h>

#include "Common/GameMemory.h"
#include "Common/FileSystem.h"

#include "Win32DEvice/Common/Win32CDManager.h"

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



//----------------------------------------------------------------------------
//         Private Prototypes                                               
//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
//         Private Functions                                               
//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
//         Public Functions                                                
//----------------------------------------------------------------------------


// BFME's CD-drive refresh body uses the retail string-layout aliases rather
// than the shorter ZH declarations.  Keep these calls TU-local so the
// official CD-manager header and its already matched siblings remain intact.
class RetailLayoutString
{
public:
	void set( const char *text, int length );
};

class BFMERetailAsciiString
{
public:
	void releaseBuffer( void );
};

#define BFME_AUDIO_SLOT(n) virtual void slot##n( void ) = 0;

struct Rva005A00B0AudioClient
{
public:
	BFME_AUDIO_SLOT(0)  BFME_AUDIO_SLOT(1)  BFME_AUDIO_SLOT(2)  BFME_AUDIO_SLOT(3)
	BFME_AUDIO_SLOT(4)  BFME_AUDIO_SLOT(5)  BFME_AUDIO_SLOT(6)  BFME_AUDIO_SLOT(7)
	BFME_AUDIO_SLOT(8)  BFME_AUDIO_SLOT(9)
	virtual void clearMusicFromCD( int value ) = 0;
	BFME_AUDIO_SLOT(11) BFME_AUDIO_SLOT(12) BFME_AUDIO_SLOT(13) BFME_AUDIO_SLOT(14)
	BFME_AUDIO_SLOT(15) BFME_AUDIO_SLOT(16) BFME_AUDIO_SLOT(17) BFME_AUDIO_SLOT(18)
	BFME_AUDIO_SLOT(19) BFME_AUDIO_SLOT(20) BFME_AUDIO_SLOT(21) BFME_AUDIO_SLOT(22)
	BFME_AUDIO_SLOT(23) BFME_AUDIO_SLOT(24) BFME_AUDIO_SLOT(25) BFME_AUDIO_SLOT(26)
	BFME_AUDIO_SLOT(27) BFME_AUDIO_SLOT(28) BFME_AUDIO_SLOT(29) BFME_AUDIO_SLOT(30)
	BFME_AUDIO_SLOT(31) BFME_AUDIO_SLOT(32) BFME_AUDIO_SLOT(33) BFME_AUDIO_SLOT(34)
	BFME_AUDIO_SLOT(35) BFME_AUDIO_SLOT(36) BFME_AUDIO_SLOT(37) BFME_AUDIO_SLOT(38)
	BFME_AUDIO_SLOT(39) BFME_AUDIO_SLOT(40) BFME_AUDIO_SLOT(41) BFME_AUDIO_SLOT(42)
	BFME_AUDIO_SLOT(43) BFME_AUDIO_SLOT(44) BFME_AUDIO_SLOT(45) BFME_AUDIO_SLOT(46)
	BFME_AUDIO_SLOT(47) BFME_AUDIO_SLOT(48) BFME_AUDIO_SLOT(49) BFME_AUDIO_SLOT(50)
	BFME_AUDIO_SLOT(51) BFME_AUDIO_SLOT(52) BFME_AUDIO_SLOT(53) BFME_AUDIO_SLOT(54)
	BFME_AUDIO_SLOT(55) BFME_AUDIO_SLOT(56) BFME_AUDIO_SLOT(57) BFME_AUDIO_SLOT(58)
	BFME_AUDIO_SLOT(59) BFME_AUDIO_SLOT(60) BFME_AUDIO_SLOT(61) BFME_AUDIO_SLOT(62)
	BFME_AUDIO_SLOT(63) BFME_AUDIO_SLOT(64) BFME_AUDIO_SLOT(65) BFME_AUDIO_SLOT(66)
	BFME_AUDIO_SLOT(67) BFME_AUDIO_SLOT(68) BFME_AUDIO_SLOT(69) BFME_AUDIO_SLOT(70)
	BFME_AUDIO_SLOT(71) BFME_AUDIO_SLOT(72) BFME_AUDIO_SLOT(73) BFME_AUDIO_SLOT(74)
	BFME_AUDIO_SLOT(75) BFME_AUDIO_SLOT(76) BFME_AUDIO_SLOT(77) BFME_AUDIO_SLOT(78)
	virtual bool isMusicPlayingFromCD( void ) const = 0;
};

#undef BFME_AUDIO_SLOT

extern Rva005A00B0AudioClient *TheAudioClientUpdate;

class ArchiveFileSystem
{
public:
	virtual void slot00( void ) = 0;
	virtual void slot01( void ) = 0;
	virtual void slot02( void ) = 0;
	virtual void closeArchiveFile( const char *filename ) = 0;
};

extern ArchiveFileSystem *TheArchiveFileSystem;

#define BFME_DRIVE_PATH_EMPTY ((const char *)0x0107388B)
#define BFME_FILE_SYSTEM_STATE (*(void **)0x0134CB48)
#define BFME_MUSIC_BIG ((const char *)0x0111BFB0)

CDManagerInterface* CreateCDManager( void )
{
	return NEW Win32CDManager;
}

//============================================================================
// Win32CDDrive::Win32CDDrive
//============================================================================

// ??0Win32CDDrive@@QAE@XZ present-unmatched
Win32CDDrive::Win32CDDrive()
{

}

//============================================================================
// Win32CDDrive::~Win32CDDrive
//============================================================================

// ??1Win32CDDrive@@UAE@XZ present-unmatched
Win32CDDrive::~Win32CDDrive()
{

}

//============================================================================
// Win32CDDrive::refreshInfo
//============================================================================

void Win32CDDrive::refreshInfo( void )
{
	Bool mayRequireUpdate = (m_disk != CD::NO_DISK);
	Char volName[1024];
	const char *drivePath = *(const char **)((char *)this + 0x1c);
	if (drivePath)
		drivePath += 8;
	else
		drivePath = BFME_DRIVE_PATH_EMPTY;

	if ( GetVolumeInformation( drivePath, volName, sizeof(volName) -1, NULL, NULL, NULL, NULL, 0 ))
	{
		((RetailLayoutString *)((char *)this + 0x18))->set(volName, strlen(volName));
		m_disk = CD::UNKNOWN_DISK;
	}
	else
	{
		((BFMERetailAsciiString *)((char *)this + 0x18))->releaseBuffer();
		m_disk = CD::NO_DISK;

		if (mayRequireUpdate && BFME_FILE_SYSTEM_STATE != 0 &&
			TheAudioClientUpdate != 0 &&
			TheAudioClientUpdate->isMusicPlayingFromCD())
		{
			TheAudioClientUpdate->clearMusicFromCD(1);
			TheArchiveFileSystem->closeArchiveFile(BFME_MUSIC_BIG);
		}
	}

	// This is an override, not an extension of CDDrive
}

#undef BFME_DRIVE_PATH_EMPTY
#undef BFME_FILE_SYSTEM_STATE
#undef BFME_MUSIC_BIG

//============================================================================
// Win32CDManager::Win32CDManager
//============================================================================

// ??0Win32CDManager@@QAE@XZ present-unmatched
Win32CDManager::Win32CDManager()
{

}

//============================================================================
// Win32CDManager::~Win32CDManager
//============================================================================

// ??1Win32CDManager@@UAE@XZ present-unmatched
Win32CDManager::~Win32CDManager()
{

}

//============================================================================
// Win32CDManager::init
//============================================================================

// ?init@Win32CDManager@@UAEXXZ present-unmatched
void Win32CDManager::init( void )
{
// byte-exact reconstruction: game/GameEngine/Source/Common/System/CDManager.cpp
// ?init@CDManager@@ present-unmatched
	CDManager::init();	// init base classes

	destroyAllDrives();

	// detect CD Drives
	for ( Char driveLetter = 'a'; driveLetter <= 'z'; driveLetter++ )
	{
		AsciiString drivePath;
		drivePath.format( "%c:\\", driveLetter );

		if ( GetDriveType( drivePath.str() ) == DRIVE_CDROM )
		{
			newDrive( drivePath.str() );
		}
	}

	refreshDrives();
}

//============================================================================
// Win32CDManager::update
//============================================================================

// ?update@Win32CDManager@@UAEXXZ present-unmatched
void Win32CDManager::update( void )
{
	CDManager::update();


}

//============================================================================
// Win32CDManager::reset
//============================================================================

// ?reset@Win32CDManager@@UAEXXZ present-unmatched
void Win32CDManager::reset( void )
{
	CDManager::reset();

}

//============================================================================
// Win32CDManager::createDrive
//============================================================================

CDDriveInterface* Win32CDManager::createDrive( void )
{
	return NEW Win32CDDrive;
}


//============================================================================
// Win32CDManager::refreshDrives
//============================================================================

// ?refreshDrives@Win32CDManager@@UAEXXZ present-unmatched
void Win32CDManager::refreshDrives( void )
{
	CDManager::refreshDrives();
}


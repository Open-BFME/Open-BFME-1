// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
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
// Project:   RTS
//
// Module:    IO
//
// File name: StreamingArchiveFile.cpp
//
// Created:   12/06/02
//
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
//         Includes                                                      
//----------------------------------------------------------------------------

#include "PreRTS.h"

#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <string.h>
#include <sys/stat.h>

#include "Common/AsciiString.h"
#include "Common/FileSystem.h"
#include "Common/StreamingArchiveFile.h"
#include "Common/PerfTimer.h"
									

//----------------------------------------------------------------------------
//         Externals                                                     
//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
//         Defines                                                         
//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
//         Private Types                                                     
//----------------------------------------------------------------------------

class BfmeStreamingArchiveFileVtable
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual Bool openFile(File *file);
};

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

//=================================================================
// StreamingArchiveFile::StreamingArchiveFile
//=================================================================

StreamingArchiveFile::StreamingArchiveFile()
: m_file(NULL), 
	m_startingPos(0), 
	m_size(0), 
	m_curPos(0)
{

}


//----------------------------------------------------------------------------
//         Public Functions                                                
//----------------------------------------------------------------------------


//=================================================================
// StreamingArchiveFile::~StreamingArchiveFile	
//=================================================================

StreamingArchiveFile::~StreamingArchiveFile()
{
	File::close();
}

//=================================================================
// StreamingArchiveFile::open	
//=================================================================
/**
  *	This function opens a file using the standard C open() call. Access flags
	* are mapped to the appropriate open flags. Returns true if file was opened
	* successfully.
	*/
//=================================================================

//DECLARE_PERF_TIMER(StreamingArchiveFile)
Bool StreamingArchiveFile::open( const Char *filename, Int access )
{
	//USE_PERF_TIMER(StreamingArchiveFile)
	File *file = TheFileSystem->openFile( filename, access );

	if ( file == NULL )
	{
		return FALSE;
	}	

	// BFME adds File::lock/unlock, moving RAMFile::open(File *) to vtable slot 17.
	return (((BfmeStreamingArchiveFileVtable *)this)->openFile(file) != NULL);
}

//============================================================================
// StreamingArchiveFile::open
//============================================================================

Bool StreamingArchiveFile::open( File *file )
{
	return TRUE;
}

//============================================================================
// StreamingArchiveFile::openFromArchive
//============================================================================
// ?openFromArchive@StreamingArchiveFile@@ present-unmatched
Bool StreamingArchiveFile::openFromArchive(File *archiveFile, const AsciiString& filename, Int offset, Int size) 
{
	//USE_PERF_TIMER(StreamingArchiveFile)
	if (archiveFile == NULL) {
		return FALSE;
	}

	if (File::open(filename.str(), File::READ | File::BINARY | File::STREAMING) == FALSE) {
		return FALSE;
	}

	m_file = archiveFile;
	m_startingPos = offset;
	m_size = size;
	m_curPos = 0;

	if (m_file->seek(offset, File::START) != offset) {
		return FALSE;
	}
	
	if (m_file->seek(size) != m_startingPos + size) {
		return FALSE;
	}

	// We know this will succeed.
	m_file->seek(offset, File::START);

	m_nameStr = filename;

	return TRUE;
}

//=================================================================
// StreamingArchiveFile::close 	
//=================================================================
/**
	* Closes the current file if it is open.
// ?close@StreamingArchiveFile@@ present-unmatched
  * Must call StreamingArchiveFile::close() for each successful StreamingArchiveFile::open() call.
	*/
//=================================================================

// ?close@StreamingArchiveFile@@ present-unmatched
void StreamingArchiveFile::close( void )
{
	File::close();
}

//=================================================================
// StreamingArchiveFile::read 
//=================================================================
// if buffer is null, just advance the current position by 'bytes'
// byte-exact reconstruction: game/GameEngine/Source/Common/StreamingArchiveFileRead.cpp
// ?read@StreamingArchiveFile@@ present-unmatched
Int StreamingArchiveFile::read( void *buffer, Int bytes )
{
	if (!m_file) {
		return 0;
	}

	// There shouldn't be a way that this can fail, because we've already verified that the file 
	// contains at least this many bits.
	m_file->seek(m_startingPos + m_curPos, File::START);

	if (bytes + m_curPos > m_size) 
		bytes = m_size - m_curPos;

	Int bytesRead = m_file->read(buffer, bytes);

	m_curPos += bytesRead;

	return bytesRead;
}

//=================================================================
// StreamingArchiveFile::write 
//=================================================================

// ?write@StreamingArchiveFile@@ present-unmatched
Int StreamingArchiveFile::write( const void *buffer, Int bytes )
{
	DEBUG_CRASH(("Cannot write to streaming files.\n"));
	return -1;
}

//=================================================================
// StreamingArchiveFile::seek 
//=================================================================

// ?seek@StreamingArchiveFile@@ present-unmatched
Int StreamingArchiveFile::seek( Int pos, seekMode mode)
{
	Int newPos;

	switch( mode )
	{
		case START:
			newPos = pos;
			break;
		case CURRENT:
			newPos = m_curPos + pos;
			break;
		case END:
			DEBUG_ASSERTCRASH(pos <= 0, ("StreamingArchiveFile::seek - position should be <= 0 for a seek starting from the end."));
			newPos = m_size + pos;
			break;
		default:
			// bad seek mode
			return -1;
	}

	if ( newPos < 0 )
	{
		newPos = 0;
	}
	else if ( newPos > m_size )
	{
		newPos = m_size;
	}

	m_curPos = newPos;

	return m_curPos;

}

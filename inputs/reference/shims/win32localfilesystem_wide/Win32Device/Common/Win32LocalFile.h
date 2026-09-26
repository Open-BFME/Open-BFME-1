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

///// Win32LocalFile.h ///////////////////////////
// Bryan Cleveland, August 2002
//////////////////////////////////////////////////

#pragma once

#ifndef __WIN32LOCALFILE_H
#define __WIN32LOCALFILE_H

#include "Common/LocalFile.h"

class Win32LocalFile : public LocalFile
{
	MEMORY_POOL_GLUE_WITH_USERLOOKUP_CREATE(Win32LocalFile, "Win32LocalFile")

	// SHIM: the pool glue leaves the destructor and operator delete protected,
	// but retail's Win32LocalFileSystem::openFile frees the file with a plain
	// delete -- push 1, call [eax] -- so in BFME they are reachable from there.
	friend class Win32LocalFileSystem;

public:
	Win32LocalFile();
	//virtual ~Win32LocalFile();

protected:
	// SHIM: four bytes BFME's File has and the reference's does not. BFME added
	// a mutex handle at File+0x10 -- lock and unlock are vtable slots 15 and 16,
	// and File.cpp in this tree models it -- so File is 20 bytes rather than 16
	// and Win32LocalFile is 24 rather than 20. That size is visible: retail
	// pushes 0x18 to the allocator in Win32LocalFileSystem::openFile, not 0x14.
	int m_bfmeMutexPadding;
};

#endif // __WIN32LOCALFILE_H
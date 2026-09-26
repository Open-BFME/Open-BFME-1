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

///// Win32LocalFileSystem.h //////////////////////////////////
// Bryan Cleveland, August 2002
///////////////////////////////////////////////////////////////

#pragma once

#ifndef __WIN32LOCALFILESYSTEM_H
#define __WIN32LOCALFILESYSTEM_H
#include "Common/LocalFileSystem.h"

class Win32LocalFileSystem : public LocalFileSystem
{
public:
	Win32LocalFileSystem();
	virtual ~Win32LocalFileSystem();

	virtual void init();

	// SHIM: BFME widened openFile to four parameters. The narrow form is vtable
	// slot 2, a 22-byte forwarder passing the extra pair as zero (matched in
	// Win32LocalFileSystem_openFile.cpp); the wide form is slot 3, retail
	// 0x009CDF50. The fourth parameter is a seek offset applied on success --
	// see docs/filesystem_family.md. Declared widest-first because MSVC lays out
	// same-name virtual overloads in reverse declaration order.
	virtual File * openFile(const Char *filename, Int access, Int seekTo, Int a4);
	virtual File * openFile(const Char *filename, Int access = 0);	///< open the given file.
	virtual Bool doesFileExist(const Char *filename) const;								///< does the given file exist?

	virtual void getFileListInDirectory(const AsciiString& currentDirectory, const AsciiString& originalDirectory, const AsciiString& searchName, FilenameList &filenameList, Bool searchSubdirectories) const; ///< search the given directory for files matching the searchName (egs. *.ini, *.rep).  Possibly search subdirectories.
	virtual Bool getFileInfo(const AsciiString& filename, FileInfo *fileInfo) const;

	virtual Bool createDirectory(AsciiString directory);
	// SHIM: reset and update are slots 8 and 9 in BFME, not 2 and 3. The
	// reference order puts them before openFile, which shifts createDirectory
	// from slot 7 to slot 10 and makes every vtable call through it wrong.
	virtual void reset();
	virtual void update();

protected:
};

#endif // __WIN32LOCALFILESYSTEM_H
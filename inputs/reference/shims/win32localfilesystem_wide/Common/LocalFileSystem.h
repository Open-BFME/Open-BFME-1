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

/////// LocalFileSystem.h ////////////////////////////////
// Bryan Cleveland, August 2002
//////////////////////////////////////////////////////////

#pragma once

#ifndef __LOCALFILESYSTEM_H
#define __LOCALFILESYSTEM_H

#include "Common/SubsystemInterface.h"
#include "Common/FileSystem.h" // for typedefs, etc.

class File;

// SHIM: not a SubsystemInterface in BFME.
//
// SubsystemInterface contributes six slots, which would put createDirectory at
// slot 11; retail reaches it at [eax+0x1c], slot 7. Standalone, with the order
// below, it lands exactly there. This matches ArchiveFileSystem, which is also
// not a SubsystemInterface in BFME -- slot 2 of its vtable is _purecall where
// all 147 real subsystem vtables carry loadIniFilesFromLegend.
class LocalFileSystem
{
public:
	virtual ~LocalFileSystem() {}

	virtual void init() = 0;

	// SHIM: BFME's slot order, which is not the reference's. The slots are fixed
	// by the call sites: FileSystem's setup at 0x009C8820 reaches init through
	// [eax+4] (slot 1), and Win32LocalFileSystem::openFile reaches
	// createDirectory through [eax+0x1c] (slot 7). reset and update are the two
	// bare rets at the end, not slots 2 and 3.
	//
	// openFile is widened to four parameters across the whole file-system family
	// -- the fourth is a seek offset -- with the narrow form kept as a 22-byte
	// forwarder passing 0, 0. The wide form is declared first because MSVC lays
	// out same-name virtual overloads in reverse declaration order, so this
	// yields narrow at slot 2 and wide at slot 3. See docs/filesystem_family.md.
	virtual File * openFile(const Char *filename, Int access, Int seekTo, Int a4) = 0;
	virtual File * openFile(const Char *filename, Int access = 0) = 0;
	virtual Bool doesFileExist(const Char *filename) const = 0;
	virtual void getFileListInDirectory(const AsciiString& currentDirectory, const AsciiString& originalDirectory, const AsciiString& searchName, FilenameList &filenameList, Bool searchSubdirectories) const = 0; ///< search the given directory for files matching the searchName (egs. *.ini, *.rep).  Possibly search subdirectories.
	virtual Bool getFileInfo(const AsciiString& filename, FileInfo *fileInfo) const = 0; ///< see FileSystem.h
	virtual Bool createDirectory(AsciiString directory) = 0; ///< see FileSystem.h
	virtual void reset() = 0;
	virtual void update() = 0;

protected:
};

extern LocalFileSystem *TheLocalFileSystem;

#endif // __LOCALFILESYSTEM_H
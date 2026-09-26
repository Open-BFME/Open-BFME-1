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
// Project:    Generals
//
// Module:     Game Engine Common
//
// File name:  Common/CDManager.h
//
// Created:    11/26/01 TR
//
//----------------------------------------------------------------------------

// BFME shadow shim (TU-scoped; only CDManager.cpp uses this -I path).
//
// Retail CDManager / Win32CDManager vtables place createDrive at slot 14
// (vtbl+0x38). ZH's SubsystemInterface (dtor/init/postProcessLoad/reset/
// update/draw) + CDManagerInterface methods would put createDrive at slot 11
// (vtbl+0x2c). Three BFME-only pure virtuals sit between draw and driveCount
// (retail slots 6-8: false-return / ret / ret 4 stubs). Inserting them here
// shifts newDrive to slot 11 and createDrive to slot 14 so newDrive's virtual
// createDrive call matches retail. Layout of m_drives (@+0x08 after vptr +
// SubsystemInterface::m_name) is unchanged.

#pragma once

#ifndef _COMMON_CDMANAGER_H_
#define _COMMON_CDMANAGER_H_


//----------------------------------------------------------------------------
//           Includes
//----------------------------------------------------------------------------

#include "Common/List.h"
#include "Common/SubSystemInterface.h"
#include "Common/AsciiString.h"


//----------------------------------------------------------------------------
//           Forward References
//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
//           Type Defines
//----------------------------------------------------------------------------

namespace CD
{
	enum Disk
	{
		UNKNOWN_DISK = -3,
		NO_DISK = -2,
		ANY_DISK = -1,
		DISK_1 = 0,
		NUM_DISKS
	};
};

//===============================
// CDDriveInterface
//===============================
/**
  *	Interface to a CD ROM drive
	*/
//===============================

class CDDriveInterface
{
	public:

		virtual ~CDDriveInterface() {};

		virtual void refreshInfo( void ) = 0;					///< Update drive with least

		virtual AsciiString getDiskName( void ) = 0;	///< Returns the drive path for this drive
		virtual AsciiString getPath( void ) = 0;			///< Returns the drive path for this drive
		virtual CD::Disk getDisk( void ) = 0;					///< Returns ID of current disk in this drive

};

//===============================
// CDDrive
//===============================

class CDDrive : public CDDriveInterface
{
	friend class CDManager;
	public:

		CDDrive();
		virtual ~CDDrive();

		// CDDriveInterface operations
		virtual AsciiString getPath( void );			///< Returns the drive path for this drive
		virtual AsciiString getDiskName( void );	///< Returns the drive path for this drive
		virtual CD::Disk getDisk( void );					///< Returns ID of current disk in this drive
		virtual void refreshInfo( void );					///< Update drive with least

		// CDDrive operations
		void setPath( const Char *path );					///< Set the drive's path

	protected:

		LListNode				m_node;										///< Link list node
		AsciiString			m_diskName;								///< disk's volume name
		AsciiString			m_drivePath;							///< drive's device path
		CD::Disk				m_disk;										///< ID of disk in drive
};


//===============================
// CDManagerInterface
//===============================

class CDManagerInterface : public SubsystemInterface
{
	public:

		virtual ~CDManagerInterface(){};

		// BFME: three extra pure virtuals after SubsystemInterface::draw
		// (retail vtable slots 6-8). Order is load-bearing for createDrive@+0x38.
		virtual void bfmeCDManagerSlot6( void ) = 0;
		virtual void bfmeCDManagerSlot7( void ) = 0;
		virtual void bfmeCDManagerSlot8( void ) = 0;

		virtual Int								driveCount( void ) = 0;						///< Number of CD drives detected
		virtual CDDriveInterface* getDrive( Int index ) = 0;				///< Return the specified drive
		virtual CDDriveInterface* newDrive( const Char *path ) = 0;	///< add new drive of specified path
		virtual void							refreshDrives( void ) = 0;				///< Refresh drive info
		virtual void							destroyAllDrives( void ) = 0;			///< Like it says, destroy all drives

	protected:

		virtual CDDriveInterface* createDrive( void ) = 0;
};

//===============================
// CDManager
//===============================

class CDManager : public CDManagerInterface
{
	public:

		CDManager();
		virtual ~CDManager();

		// sub system operations
		virtual void init( void );
		virtual void update( void );
		virtual void reset( void );

		// BFME slot stubs (retail: xor al,al;ret 4 / ret / ret 4). Empty bodies
		// keep CDManager concrete enough for this TU; slot offsets only matter.
		virtual void bfmeCDManagerSlot6( void ) {}
		virtual void bfmeCDManagerSlot7( void ) {}
		virtual void bfmeCDManagerSlot8( void ) {}

		//
		virtual Int								driveCount( void );						///< Number of CD drives detected
		virtual CDDriveInterface*	getDrive( Int index );				///< Return the specified drive
		virtual CDDriveInterface* newDrive( const Char *path );	///< add new drive of specified path
		virtual void							refreshDrives( void );				///< Refresh drive info
		virtual void							destroyAllDrives( void );			///< Like it says, destroy all drives



	protected:

	LList			m_drives;					///< List of drives detected on this machine
};

//----------------------------------------------------------------------------
//           Inlining
//----------------------------------------------------------------------------

extern CDManagerInterface *TheCDManager;
CDManagerInterface* CreateCDManager( void );

#endif // _COMMON_CDMANAGER_H_

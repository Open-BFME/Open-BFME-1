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

// FILE: DisplayStringManager.h ///////////////////////////////////////////////////////////////////
// Created:    Colin Day, July 2001
// Desc:       Access for creating game managed display strings
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef __DISPLAYSTRINGMANAGER_H_
#define __DISPLAYSTRINGMANAGER_H_

#include "Common/SubsystemInterface.h"
#include "GameClient/DisplayString.h"

//-------------------------------------------------------------------------------------------------
/** Factory for managing and creating display strings */
//-------------------------------------------------------------------------------------------------
class DisplayStringManager : public SubsystemInterface
{

public:

	DisplayStringManager( void );
	virtual ~DisplayStringManager( void );

	// BFME: the same three stub virtuals that occupy slots 6-8 across this
	// family (see sweep's GameWindowManager.h) are present here too, which is
	// why CreditsLine::~CreditsLine @0x40C230 reaches freeDisplayString
	// through vtable +0x28 while this header puts it at +0x1C. Names and
	// signatures are still unknown; the slots only need to exist.
	virtual Bool bfme_dsm_6( void * ) { return FALSE; }
	virtual void bfme_dsm_7( void ) { }
	virtual void bfme_dsm_8( void * ) { }

	virtual void init( void ) {}			///< initialize the factory
	virtual void reset( void ) {}			///< reset system
	virtual void update( void ) {};		///< update anything we need to in our strings

	virtual DisplayString *newDisplayString( void ) = 0;  ///< allocate new display string
	virtual void freeDisplayString( DisplayString *string ) = 0;  ///< free string

	virtual DisplayString *getGroupNumeralString( Int numeral ) = 0;
	virtual DisplayString *getFormationLetterString( void ) = 0;
protected:

	void link( DisplayString *string );  ///< link display string to list
	void unLink( DisplayString *string );  ///< unlink display string from list

	DisplayString *m_stringList;  ///< list of all display strings
	DisplayString *m_currentCheckpoint; ///< current checkpoint of strings to be freed
};

// EXTERNALS //////////////////////////////////////////////////////////////////////////////////////
extern DisplayStringManager *TheDisplayStringManager;  ///< singleton extern

#endif // __DISPLAYSTRINGMANAGER_H_


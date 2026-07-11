// GameText.h -- BFME shadow shim. Verbatim ZH GeneralsMD header except:
//  * three BFME-only stub virtuals at slots 6-8 of GameTextInterface (same
//    family stubs as GameWindowManager/InGameUI; retail call sites encode
//    fetch(AsciiString) at vtable+0x28 = slot 10, e.g. in
//    DownloadManagerMunkee::OnError, not +0x1c as the ZH layout gives).
//    The stubs are NOT in the SubsystemInterface base because the Display
//    branch doesn't have them (see Common/SubsystemInterface.h).
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
// Project:    RTS 3
//
// File name:  GameClient/GameText.h
//
// Created:    11/07/01
//
//----------------------------------------------------------------------------

#pragma once

#ifndef __GAMECLIENT_GAMETEXT_H_
#define __GAMECLIENT_GAMETEXT_H_


//----------------------------------------------------------------------------
//           Includes                                                      
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
//           Forward References
//----------------------------------------------------------------------------

class AsciiString;
class UnicodeString;

//----------------------------------------------------------------------------
//           Type Defines
//----------------------------------------------------------------------------
typedef std::vector<AsciiString> AsciiStringVec;

//===============================
// GameTextInterface 
//===============================
/** Game text interface object for localised text.
	*/
//===============================

class GameTextInterface : public SubsystemInterface
{

	public:

		virtual ~GameTextInterface() {};

		// BFME: three stub virtuals occupy slots 6-8 (shared family stubs;
		// see GameWindowManager.h). Names/signatures pending RE; the slots
		// must exist here so fetch() lands at its retail vtable slots 9/10.
		virtual Bool bfme_gt_6( void * ) { return FALSE; }
		virtual void bfme_gt_7( void ) { }
		virtual void bfme_gt_8( void * ) { }

		virtual UnicodeString fetch( const Char *label, Bool *exists = NULL ) = 0;		///< Returns the associated labeled unicode text
		virtual UnicodeString fetch( AsciiString label, Bool *exists = NULL ) = 0;		///< Returns the associated labeled unicode text
		// This function is not performance tuned.. Its really only for Worldbuilder. jkmcd
		virtual AsciiStringVec& getStringsWithLabelPrefix(AsciiString label) = 0;

		virtual void					initMapStringFile( const AsciiString& filename ) = 0;
};


extern GameTextInterface *TheGameText;
extern GameTextInterface* CreateGameTextInterface( void );

//----------------------------------------------------------------------------
//           Inlining                                                       
//----------------------------------------------------------------------------


#endif // __GAMECLIENT_GAMETEXT_H_

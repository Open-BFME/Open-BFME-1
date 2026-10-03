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

// FILE: DieModule.cpp ////////////////////////////////////////////////////////////////////////////
// Author:
// Desc:   
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#define DEFINE_OBJECT_STATUS_NAMES
#include "Common/Xfer.h"
#include "GameClient/Drawable.h"
#include "GameLogic/ExperienceTracker.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/Module/DieModule.h"
#include "GameLogic/Object.h"


#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif



//-------------------------------------------------------------------------------------------------
// ??0DieMuxData@@ present-unmatched
DieMuxData::DieMuxData() :
	m_deathTypes(DEATH_TYPE_FLAGS_ALL),
	m_veterancyLevels(VETERANCY_LEVEL_FLAGS_ALL)
{
}

//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: game/GameEngine/Source/GameLogic/Module/DieMuxDataGetFieldParseThunk.cpp
// ?getFieldParse@DieMuxData@@ present-unmatched
const FieldParse* DieMuxData::getFieldParse() 
{
	static const FieldParse dataFieldParse[] = 
	{
		{ "DeathTypes",				INI::parseDeathTypeFlags,						NULL, offsetof( DieMuxData, m_deathTypes ) },
		{ "VeterancyLevels",	INI::parseVeterancyLevelFlags,			NULL, offsetof( DieMuxData, m_veterancyLevels ) },
		{ "ExemptStatus",			ObjectStatusMaskType::parseFromINI,	NULL,	offsetof( DieMuxData, m_exemptStatus ) },
		{ "RequiredStatus",		ObjectStatusMaskType::parseFromINI, NULL,	offsetof( DieMuxData, m_requiredStatus ) },
		{ 0, 0, 0, 0 }
	};
  return dataFieldParse;
}

// 0x001FB090 and 0x00255120: two unreferenced retail copies of the same
// one-bit flag test, (flags & (1 << (n - 1))) != 0.  Both are reached only
// through ILT jumps (0x000372BD, 0x0001E37B) that nothing calls; the Zero Hour
// helpers getDeathTypeFlag/getVeterancyLevelFlag have these bytes but retail
// shows no caller that would say which name belongs to which address.
// IDENTITY IS NOT RECOVERED.  Names are derived from the addresses.
bool __cdecl rva001FB090BitFlag( unsigned int flags, int n )
{
	return ( flags & ( 1 << ( n - 1 ) ) ) != 0;
}

bool __cdecl rva00255120BitFlag( unsigned int flags, int n )
{
	return ( flags & ( 1 << ( n - 1 ) ) ) != 0;
}

// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// ?crc@DieModule@@ present-unmatched
void DieModule::crc( Xfer *xfer )
{

	// extend base class
	BehaviorModule::crc( xfer );

}  // end crc

// ------------------------------------------------------------------------------------------------
/** Xfer Method */
// ------------------------------------------------------------------------------------------------
// ?xfer@DieModule@@ present-unmatched
void DieModule::xfer( Xfer *xfer )
{

	// version
	XferVersion currentVersion = 1;
	XferVersion version = currentVersion;
	xfer->xferVersion( &version, currentVersion );

	// call base class
	BehaviorModule::xfer( xfer );

}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
// ?loadPostProcess@DieModule@@ present-unmatched
void DieModule::loadPostProcess( void )
{

	// call base class
	BehaviorModule::loadPostProcess();

}  // end loadPostProcess

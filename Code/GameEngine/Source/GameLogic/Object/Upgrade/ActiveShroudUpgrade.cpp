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

// FILE: ActiveShroudUpgrade.cpp ///////////////////////////////////////////////////////////////////////////
// Author: Graham Smallwood, July 2002
// Desc:	 An upgrade that modifies the object's ShroudRange.
///////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/Xfer.h"
#include "GameLogic/Module/ActiveShroudUpgrade.h"
#include "GameLogic/Object.h"

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ??0ActiveShroudUpgradeModuleData@@ present-unmatched
ActiveShroudUpgradeModuleData::ActiveShroudUpgradeModuleData( void )
{

	m_newShroudRange = 0.0f;

}  // end SpecialPowerModuleData

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
/* static */ void ActiveShroudUpgradeModuleData::buildFieldParse(MultiIniFieldParse& p)
{
	UpgradeModuleData::buildFieldParse( p );

	static const FieldParse dataFieldParse[] = 
	{
		{ "NewShroudRange", INI::parseReal, NULL, offsetof( ActiveShroudUpgradeModuleData, m_newShroudRange ) },
		{ 0, 0, 0, 0 }
	};
	p.add(dataFieldParse);

}  // end buildFieldParse

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: Code/GameEngine/Source/GameLogic/Object/Upgrade/ActiveShroudUpgradeConstructor.cpp
// ??0ActiveShroudUpgrade@@ present-unmatched
// Fourth member of the Upgrade family that stops on the same two bytes, and the
// sibling note in MaxHealthUpgrade.cpp, StatusBitsUpgrade.cpp and
// ModelConditionUpgrade.cpp applies here unchanged: the base COUNT is right and
// two base OFFSETS are wrong. Retail stores four vftables at +0x00, +0x0C,
// +0x10 and +0x18; this tree stores four at +0x00, +0x04, +0x10 and +0x14.
//
// Read as sub-object spans that is NOT a uniform shift, which is why no single
// define fixes it: the first sub-object spans 0x0C in BFME against 0x04 here,
// the second spans 0x04 against 0x0C, and the third 0x08 against 0x04. Eight
// bytes move OUT of the second base and INTO the first, and the third gains
// four -- the shape of a different base order or of members that changed base,
// not of one class growing. BFME_MODULE_NO_MPO makes it worse: it deletes one
// of the four vftables the count already agrees on.
ActiveShroudUpgrade::ActiveShroudUpgrade( Thing *thing, const ModuleData* moduleData ) : 
							UpgradeModule( thing, moduleData )
{

}  // end ActiveShroudUpgrade

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ??1ActiveShroudUpgrade@@ present-unmatched
ActiveShroudUpgrade::~ActiveShroudUpgrade( void )
{

}  // end ~ActiveShroudUpgrade

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ?upgradeImplementation@ActiveShroudUpgrade@@ present-unmatched
void ActiveShroudUpgrade::upgradeImplementation( void )
{
	// Set my object's ability to actively shroud.
	if( getActiveShroudUpgradeModuleData() )
	{
		getObject()->setShroudRange( getActiveShroudUpgradeModuleData()->m_newShroudRange );
		getObject()->handlePartitionCellMaintenance();// To shroud where I am without waiting.
	}
}  // end upgradeImplementation

// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// ?crc@ActiveShroudUpgrade@@ present-unmatched
void ActiveShroudUpgrade::crc( Xfer *xfer )
{

	// extend base class
	UpgradeModule::crc( xfer );

}  // end crc

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
// ?xfer@ActiveShroudUpgrade@@ present-unmatched
void ActiveShroudUpgrade::xfer( Xfer *xfer )
{

	// version
	XferVersion currentVersion = 1;
	XferVersion version = currentVersion;
	xfer->xferVersion( &version, currentVersion );

	// extend base class
	UpgradeModule::xfer( xfer );

}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
// ?loadPostProcess@ActiveShroudUpgrade@@ present-unmatched
void ActiveShroudUpgrade::loadPostProcess( void )
{

	// extend base class
	UpgradeModule::loadPostProcess();

}  // end loadPostProcess

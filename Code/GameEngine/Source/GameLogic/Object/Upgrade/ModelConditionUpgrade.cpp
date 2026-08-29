// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
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

// FILE: ModelConditionUpgrade.cpp /////////////////////////////////////////////////////////////////////////////
// Author: Graham Smallwood, July 2003
// Desc:	 UpgradeModule that sets a modelcondition flag
///////////////////////////////////////////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "GameLogic/Module/ModelConditionUpgrade.h"

#include "Common/ModelState.h"
#include "GameLogic/Object.h"

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// byte-exact reconstruction: Code/GameEngine/Source/GameLogic/AI/ModelConditionUpgradeModuleDataCtorThunk.cpp
// ??0ModelConditionUpgradeModuleData@@QAE@XZ present-unmatched
ModelConditionUpgradeModuleData::ModelConditionUpgradeModuleData()
{
	m_conditionFlag = MODELCONDITION_INVALID;
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// byte-exact reconstruction: Code/GameEngine/Source/GameLogic/Object/Upgrade/MaxHealthUpgrade.cpp
// ?buildFieldParse@ModelConditionUpgradeModuleData@@ present-unmatched
void ModelConditionUpgradeModuleData::buildFieldParse(MultiIniFieldParse& p) 
{
  UpgradeModuleData::buildFieldParse(p);

	static const FieldParse dataFieldParse[] = 
	{
		{ "ConditionFlag",	ModelConditionFlags::parseSingleBitFromINI,	NULL, offsetof( ModelConditionUpgradeModuleData, m_conditionFlag ) },
		{ 0, 0, 0, 0 }
	};
  p.add(dataFieldParse);
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// The base COUNT is right and two base OFFSETS are wrong. Retail stores four
// vtables, at +0x00, +0x0C, +0x10 and +0x18; this tree stores four, at +0x00,
// +0x04, +0x10 and +0x14. So the sub-object at +0x00 spans 0x0C bytes in BFME
// and 0x04 here -- eight bytes of data the vendored BehaviorModule does not
// declare -- and bases two and four both slide by that eight. Nothing is
// missing and nothing is reordered.
//
// BFME_MODULE_NO_MPO is not the fix and is actively misleading here: it makes
// base two land correctly at +0x0C while DELETING base four, so a screen run
// with the define on shows three stores against retail's four and reads as a
// missing base class. It is not; that is the define's own removal. Screen this
// family WITHOUT the define.
//
// The same eight-byte shift accounts for MaxHealthUpgrade, StatusBitsUpgrade,
// ModelConditionUpgrade and ActiveShroudUpgrade, so it is the class and not the
// four bodies. Unblocking it is a header change.
// byte-exact reconstruction: Code/GameEngine/Source/GameLogic/Object/Upgrade/ModelConditionUpgradeConstructor.cpp
// ??0ModelConditionUpgrade@@QAE@PAVThing@@PBVModuleData@@@Z present-unmatched
ModelConditionUpgrade::ModelConditionUpgrade( Thing *thing, const ModuleData* moduleData ) : UpgradeModule( thing, moduleData )
{
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ??1ModelConditionUpgrade@@MAE@XZ present-unmatched
ModelConditionUpgrade::~ModelConditionUpgrade( void )
{
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ?upgradeImplementation@ModelConditionUpgrade@@MAEXXZ present-unmatched
void ModelConditionUpgrade::upgradeImplementation( )
{
	const ModelConditionUpgradeModuleData *data = getModelConditionUpgradeModuleData();

	Object *me = getObject();	

	if( data->m_conditionFlag != MODELCONDITION_INVALID )
		me->setModelConditionState(data->m_conditionFlag);
}

// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// ?crc@ModelConditionUpgrade@@MAEXPAVXfer@@@Z present-unmatched
void ModelConditionUpgrade::crc( Xfer *xfer )
{

	// extend base class
	UpgradeModule::crc( xfer );

}  // end crc

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
// ?xfer@ModelConditionUpgrade@@MAEXPAVXfer@@@Z present-unmatched
void ModelConditionUpgrade::xfer( Xfer *xfer )
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
// ?loadPostProcess@ModelConditionUpgrade@@MAEXXZ present-unmatched
void ModelConditionUpgrade::loadPostProcess( void )
{

	// extend base class
	UpgradeModule::loadPostProcess();

}  // end loadPostProcess

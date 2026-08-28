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

// FILE: GrantUpgradeCreate.cpp ////////////////////////////////////////////////////////////////////////
// Author: Kris Morness, April 2002
// Desc:   GrantUpgrade create module
///////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#define DEFINE_OBJECT_STATUS_NAMES
#include "Common/Player.h"
#include "Common/Upgrade.h"
#include "Common/Xfer.h"
#include "GameLogic/Module/GrantUpgradeCreate.h"
#include "GameLogic/Object.h"

// BFME tests ExemptStatus / object status with Generals-style ObjectStatusBits
// masks (UNDER_CONSTRUCTION = 1<<2), not ZH BitFlags indices.
enum
{
	BFME_OBJECT_STATUS_UNDER_CONSTRUCTION = (1 << 2)
};

// Retail onCreate materializes 12 bytes from Object::m_status @ +0x90 even though
// the live BitFlags field is 8 bytes (over-read of the next field).
struct GrantUpgradeStatusBits12
{
	UnsignedInt d0;
	UnsignedInt d1;
	UnsignedInt d2;
};

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// byte-exact reconstruction: Code/GameEngine/Source/GameLogic/Object/Create/GrantUpgradeCreateModuleDataCtor.cpp
// ??0GrantUpgradeCreateModuleData@@QAE@XZ present-unmatched
GrantUpgradeCreateModuleData::GrantUpgradeCreateModuleData()
{
	m_upgradeName = "";
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ?buildFieldParse@GrantUpgradeCreateModuleData@@ present-unmatched
void GrantUpgradeCreateModuleData::buildFieldParse(MultiIniFieldParse& p)
{
  CreateModuleData::buildFieldParse(p);

	static const FieldParse dataFieldParse[] = 
	{
		{ "UpgradeToGrant",	INI::parseAsciiString,							NULL, offsetof( GrantUpgradeCreateModuleData, m_upgradeName ) },
		{ "ExemptStatus",		ObjectStatusMaskType::parseFromINI, NULL, offsetof( GrantUpgradeCreateModuleData, m_exemptStatus ) },
		{ 0, 0, 0, 0 }
	};

  p.add(dataFieldParse);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: Code/GameEngine/Source/GameLogic/Object/Create/GrantUpgradeCreateConstructor.cpp
// ??0GrantUpgradeCreate@@QAE@PAVThing@@PBVModuleData@@@Z present-unmatched
GrantUpgradeCreate::GrantUpgradeCreate( Thing *thing, const ModuleData* moduleData ) : CreateModule( thing, moduleData )
{
}  // end GrantUpgradeCreate

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ??1GrantUpgradeCreate@@MAE@XZ present-unmatched
GrantUpgradeCreate::~GrantUpgradeCreate( void )
{

}  // end ~GrantUpgradeCreate

//-------------------------------------------------------------------------------------------------
/** The create callback. */
//-------------------------------------------------------------------------------------------------
// ?onCreate@GrantUpgradeCreate@@UAEXXZ
void GrantUpgradeCreate::onCreate( void )
{
	// Evaluate object status first so MSVC 7.1 matches the retail load order.
	// Retail tests Generals-style mask 0x4 (UNDER_CONSTRUCTION), not ZH BitFlags index 3.
	// m_exemptStatus is ObjectStatusMaskType in the ZH header; BFME stores/tests it as a
	// Generals bitmask in the first dword (test byte [moduleData+0xc], 4).
	GrantUpgradeStatusBits12 currentStatus =
		*reinterpret_cast<const GrantUpgradeStatusBits12 *>(
			reinterpret_cast<const char *>( getObject() ) + 0x90 );
	UnsignedInt exemptStatus =
		*reinterpret_cast<const UnsignedInt *>(
			&getGrantUpgradeCreateModuleData()->m_exemptStatus );
	if( BitTest( exemptStatus, BFME_OBJECT_STATUS_UNDER_CONSTRUCTION ) == TRUE )
	{
		if( BitTest( currentStatus.d0, BFME_OBJECT_STATUS_UNDER_CONSTRUCTION ) == FALSE )
		{
			const UpgradeTemplate *upgradeTemplate = TheUpgradeCenter->findUpgrade( getGrantUpgradeCreateModuleData()->m_upgradeName );
			if( !upgradeTemplate )
			{
				DEBUG_ASSERTCRASH( 0, ("GrantUpdateCreate for %s can't find upgrade template %s.", getObject()->getName(), getGrantUpgradeCreateModuleData()->m_upgradeName ) );
				return;
			}

			if( upgradeTemplate->getUpgradeType() == UPGRADE_TYPE_PLAYER )
			{
				// get the player
				Player *player = getObject()->getControllingPlayer();
				player->addUpgrade( upgradeTemplate, UPGRADE_STATUS_COMPLETE );
			}
			else
			{
				getObject()->giveUpgrade( upgradeTemplate );
			}
		}
	}

}  // end onCreate

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
void GrantUpgradeCreate::onBuildComplete( void )
{
	if( ! shouldDoOnBuildComplete() )
		return;

// byte-exact reconstruction: Code/GameEngine/Source/GameLogic/Object/Create/CreateModule.cpp
// ?onBuildComplete@CreateModule@@UAEXXZ present-unmatched
	CreateModule::onBuildComplete(); // extend

	const UpgradeTemplate *upgradeTemplate = TheUpgradeCenter->findUpgrade( getGrantUpgradeCreateModuleData()->m_upgradeName );
	if( !upgradeTemplate )
	{
		DEBUG_ASSERTCRASH( 0, ("GrantUpdateCreate for %s can't find upgrade template %s.", getObject()->getName(), getGrantUpgradeCreateModuleData()->m_upgradeName ) );
		return;
	}

	if( upgradeTemplate->getUpgradeType() == UPGRADE_TYPE_PLAYER )
	{
		// get the player
		Player *player = getObject()->getControllingPlayer();
		player->addUpgrade( upgradeTemplate, UPGRADE_STATUS_COMPLETE );
	}
	else
	{
		getObject()->giveUpgrade( upgradeTemplate );
	}
}  // end onBuildComplete

// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// ?crc@GrantUpgradeCreate@@MAEXPAVXfer@@@Z present-unmatched
void GrantUpgradeCreate::crc( Xfer *xfer )
{

	// extend base class
	CreateModule::crc( xfer );

}  // end crc

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
// ?xfer@GrantUpgradeCreate@@MAEXPAVXfer@@@Z present-unmatched
void GrantUpgradeCreate::xfer( Xfer *xfer )
{

	// version
	XferVersion currentVersion = 1;
	XferVersion version = currentVersion;
	xfer->xferVersion( &version, currentVersion );

	// extend base class
	CreateModule::xfer( xfer );

}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
// ?loadPostProcess@GrantUpgradeCreate@@MAEXXZ present-unmatched
void GrantUpgradeCreate::loadPostProcess( void )
{

	// extend base class
	CreateModule::loadPostProcess();

}  // end loadPostProcess

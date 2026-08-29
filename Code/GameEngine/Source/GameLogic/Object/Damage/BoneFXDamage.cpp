// cl: /DNDEBUG /DWIN32 /D_WINDOWS /DBFME_MODULE_NO_MPO /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
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

// FILE: BoneFXDamage.cpp ///////////////////////////////////////////////////////////////////
// Author: Bryan Cleveland, March 2002
// Desc:   Damage module that goes with BoneFX update
///////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/Xfer.h"
#include "GameClient/Drawable.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/Object.h"
#include "GameLogic/Module/BoneFXDamage.h"
#include "GameLogic/Module/BoneFXUpdate.h"

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// The module hierarchy needs BFME_MODULE_NO_MPO on this file's own cl line:
// retail's Module has no MemoryPoolObject base, so BehaviorModule spans 0x0C
// and this constructor's second vtable store lands at +0x0C, where the wider
// layout puts a fourth vptr at +0x04 and +0x14 and shifts everything.
BoneFXDamage::BoneFXDamage( Thing *thing, const ModuleData* moduleData ) 
																		  : DamageModule( thing, moduleData )
{
}  // end BoneFXDamage

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ??1BoneFXDamage@@MAE@XZ present-unmatched
BoneFXDamage::~BoneFXDamage( void )
{

}  // end ~BoneFXDamage

//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: Code/GameEngine/Source/GameLogic/Object/Damage/BoneFXDamage_onObjectCreated_Thunk.cpp
// ?onObjectCreated@BoneFXDamage@@ present-unmatched
void BoneFXDamage::onObjectCreated()
{
	static NameKeyType key_BoneFXUpdate = NAMEKEY("BoneFXUpdate");
	BoneFXUpdate* bfxu = (BoneFXUpdate*)getObject()->findUpdateModule(key_BoneFXUpdate);
	if (bfxu == NULL)
	{
		DEBUG_ASSERTCRASH(bfxu != NULL, ("BoneFXDamage requires BoneFXUpdate"));
		throw INI_INVALID_DATA;
	}
}

//-------------------------------------------------------------------------------------------------
/** Switching damage states */
//-------------------------------------------------------------------------------------------------
void BoneFXDamage::onBodyDamageStateChange( const DamageInfo *damageInfo, 
																						BodyDamageType oldState, 
																						BodyDamageType newState )
{
	static NameKeyType key_BoneFXUpdate = NAMEKEY("BoneFXUpdate");
	BoneFXUpdate* bfxu = (BoneFXUpdate*)getObject()->findUpdateModule(key_BoneFXUpdate);
	if (bfxu)
		bfxu->changeBodyDamageState(oldState, newState);

}  // end onBodyDamageStateChange

// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// ?crc@BoneFXDamage@@MAEXPAVXfer@@@Z present-unmatched
void BoneFXDamage::crc( Xfer *xfer )
{

	// extend base class
	DamageModule::crc( xfer );

}  // end crc

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
// ?xfer@BoneFXDamage@@MAEXPAVXfer@@@Z present-unmatched
void BoneFXDamage::xfer( Xfer *xfer )
{

	// version
	XferVersion currentVersion = 1;
	XferVersion version = currentVersion;
	xfer->xferVersion( &version, currentVersion );

	// extend base class
	DamageModule::xfer( xfer );

}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
// ?loadPostProcess@BoneFXDamage@@MAEXXZ present-unmatched
void BoneFXDamage::loadPostProcess( void )
{

	// extend base class
	DamageModule::loadPostProcess();

}  // end loadPostProcess

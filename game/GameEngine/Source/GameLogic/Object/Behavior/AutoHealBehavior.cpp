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

// FILE: AutoHealBehavior.cpp ///////////////////////////////////////////////////////////////////////
// Author:
// Desc:  
///////////////////////////////////////////////////////////////////////////////////////////////////


// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine
#include "Common/Thing.h"
#include "Common/ThingTemplate.h"
#include "Common/INI.h"
#include "Common/Player.h"
#include "Common/Xfer.h"
#include "GameClient/ParticleSys.h"
#include "GameClient/Anim2D.h"
#include "GameClient/InGameUI.h"
#include "GameLogic/Module/AutoHealBehavior.h"
#include "GameLogic/Module/BodyModule.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/Object.h"
#include "GameLogic/PartitionManager.h"

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
struct AutoHealPlayerScanHelper
{
	KindOfMaskType m_kindOfToTest;
	KindOfMaskType m_forbiddenKindOf;
	Object *m_theHealer;
	ObjectPointerList *m_objectList;	
	Bool m_skipSelfForHealing;
};

static void checkForAutoHeal( Object *testObj, void *userData )
{
	AutoHealPlayerScanHelper *helper = (AutoHealPlayerScanHelper*)userData;
	ObjectPointerList *listToAddTo = helper->m_objectList;

	if( testObj->isEffectivelyDead() )
		return;

	if( testObj->getControllingPlayer() != helper->m_theHealer->getControllingPlayer() )
		return;

	if( testObj->isOffMap() )
		return;

	if( helper->m_skipSelfForHealing && testObj == helper->m_theHealer )
		return;

	if( !testObj->isAnyKindOf(helper->m_kindOfToTest) )
		return;

	if( testObj->isAnyKindOf( helper->m_forbiddenKindOf ) )
		return;

	if( testObj->getBodyModule()->getHealth() >= testObj->getBodyModule()->getMaxHealth() )
		return;

	listToAddTo->push_back(testObj);
}

// BFME's module-data layout places the onDamage fields at different offsets
// from the vendored Zero Hour declaration, and stores the radius gate as a
// word tested for zero by the retail body.
struct BfmeAutoHealDamageData
{
	UnsignedByte m_padding[0x7c];
	UnsignedInt m_startHealingDelay;
	UnsignedInt m_radius;
};

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ??1AutoHealBehavior@@ present-unmatched
AutoHealBehavior::~AutoHealBehavior( void )
{

	if( m_radiusParticleSystemID != INVALID_PARTICLE_SYSTEM_ID )
		TheParticleSystemManager->destroyParticleSystemByID( m_radiusParticleSystemID );

}

//-------------------------------------------------------------------------------------------------
// ?stopHealing@AutoHealBehavior@@ present-unmatched
void AutoHealBehavior::stopHealing()
{
	m_stopped = true;
	m_soonestHealFrame = FOREVER;
	setWakeFrame(getObject(), UPDATE_SLEEP_FOREVER);
}

//-------------------------------------------------------------------------------------------------
// ?undoUpgrade@AutoHealBehavior@@ present-unmatched
void AutoHealBehavior::undoUpgrade()
{
	m_soonestHealFrame = 0;
	setUpgradeExecuted( FALSE );
}

//-------------------------------------------------------------------------------------------------
/** Damage has been dealt, this is an opportunity to reach to that damage */
//-------------------------------------------------------------------------------------------------
void AutoHealBehavior::onDamage( DamageInfo *damageInfo )
{
	// BFME's AutoHealBehavior base layout differs from the vendored Zero Hour
	// declaration in this interface-adjusted method.  Use the retail offsets
	// explicitly so the generated body keeps the original field accesses.
	if (*(const Bool *)((const char *)this + 0x30))
		return;

	const BfmeAutoHealDamageData *d =
		*(const BfmeAutoHealDamageData *const *)((const char *)this + 0x04);
	if (isUpgradeActive() && d->m_radius == 0)
	{
		// if this is nonzero, getting damaged resets our healing process. so go to
		// sleep for this long.
		if (d->m_startHealingDelay > 0)
		{
			setWakeFrame(*(Object *const *)((const char *)this + 0x08), UPDATE_SLEEP(d->m_startHealingDelay));
		}
		else if( TheGameLogic->getFrame() > *(const Int *)((const char *)this + 0x2c) )
		{
			// We can only force an immediate wake if we are ready to heal.  Otherwise we will
			// heal on a timer AND at every damage input.
			setWakeFrame(*(Object *const *)((const char *)this + 0x08), UPDATE_SLEEP_NONE);
		}
	}
}

//-------------------------------------------------------------------------------------------------
/** The update callback. */
//-------------------------------------------------------------------------------------------------
 
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ?pulseHealObject@AutoHealBehavior@@ present-unmatched
void AutoHealBehavior::pulseHealObject( Object *obj )
{
	if (m_stopped)
		return;

	const AutoHealBehaviorModuleData *data = getAutoHealBehaviorModuleData();

	
	if ( data->m_radius == 0.0f )
		obj->attemptHealing(data->m_healingAmount, getObject());
	else
		obj->attemptHealingFromSoleBenefactor( data->m_healingAmount, getObject(), data->m_healingDelay );


	if( data->m_unitHealPulseParticleSystemTmpl )
	{
		ParticleSystem *system = TheParticleSystemManager->createParticleSystem( data->m_unitHealPulseParticleSystemTmpl );
		if( system )
		{
			system->setPosition( obj->getPosition() );
		}
	}
	
	m_soonestHealFrame = TheGameLogic->getFrame() + data->m_healingDelay;// In case onDamage tries to wake us up early
}

// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// ?crc@AutoHealBehavior@@ present-unmatched
void AutoHealBehavior::crc( Xfer *xfer )
{

	// extend base class
	UpdateModule::crc( xfer );

	// extend base class
	UpgradeMux::upgradeMuxCRC( xfer );

}  // end crc

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
// ?xfer@AutoHealBehavior@@ present-unmatched
void AutoHealBehavior::xfer( Xfer *xfer )
{

	// version
	XferVersion currentVersion = 1;
	XferVersion version = currentVersion;
	xfer->xferVersion( &version, currentVersion );

	// extend base class
	UpdateModule::xfer( xfer );

	// extend base class
	UpgradeMux::upgradeMuxXfer( xfer );

	// particle system id
	xfer->xferUser( &m_radiusParticleSystemID, sizeof( ParticleSystemID ) );

	// Timer safety
	xfer->xferUnsignedInt( &m_soonestHealFrame );

	// stopped
	xfer->xferBool( &m_stopped );

}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
// ?loadPostProcess@AutoHealBehavior@@ present-unmatched
void AutoHealBehavior::loadPostProcess( void )
{

	// extend base class
	UpdateModule::loadPostProcess();

	// extend base class
	UpgradeMux::upgradeMuxLoadPostProcess();

}  // end loadPostProcess

// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/shims/aicommandoutofline /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
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

// FILE: SpawnBehavior.cpp ////////////////////////////////////////////////////////////////////////
// Author: Graham Smallwood, January 2002
// Desc:   Update will create and monitor a group of spawned units and replace as needed
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/GameState.h"
#include "Common/ThingFactory.h"
#include "Common/ThingTemplate.h"
#include "Common/Player.h"
#include "Common/Xfer.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/Object.h"
#include "GameLogic/PartitionManager.h"
#include "GameLogic/Module/AIUpdate.h"
#include "GameLogic/Module/SpawnBehavior.h"
#include "GameLogic/Module/BodyModule.h"
#include "GameClient/Drawable.h" //selection logic
#include "GameClient/InGameUI.h" // selection logic
#include "GameLogic/ExperienceTracker.h" //veterancy logic
#include "GameLogic/Module/StealthUpdate.h"


#define NONE_SPAWNED_YET (0xffffffff)


#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif



#define SPAWN_DELAY_MIN_FRAMES (16) // about as rapidly as you'd expect people to successively exit through the same door
//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: game/GameEngine/Source/GameLogic/Object/Behavior/SpawnBehaviorCtorThunk.cpp
// ??0SpawnBehavior@@ present-unmatched
SpawnBehavior::SpawnBehavior( Thing *thing, const ModuleData* moduleData ) 
						 : UpdateModule( thing, moduleData )
{
	const SpawnBehaviorModuleData* md = getSpawnBehaviorModuleData();

	// GEE, THIS IS NEW...
	// NOW, WE CAN HAVE A LIST OF TEMPLATE NAMES
	m_templateNameIterator = md->m_spawnTemplateNameData.begin();
	m_spawnTemplate = TheThingFactory->findTemplate( *m_templateNameIterator );
	//each time m_spawn template is used, it will increment m_templateNameIterator,
	//thus scanning through the ordered list of template names
	//looping back to the beginning

	m_framesToWait = 0;
	//Added By Sadullah Nader
	//Initialization(s) inserted
	m_firstBatchCount = 0;
	//
	if( md->m_isOneShotData )
		m_oneShotCountdown = md->m_spawnNumberData;
	else
		m_oneShotCountdown = -1;

	m_active = TRUE;

	m_replacementTimes.clear();
	// The initializing of the initial bursters is handled in the first update @todo invent an object::postConstructionProcess() some day
	m_initialBurstCountdown = md->m_initialBurst;
	m_initialBurstTimesInited = FALSE;


	
	m_aggregateHealth = md->m_aggregateHealth;

	m_spawnCount = NONE_SPAWNED_YET;
	m_active = TRUE;
	m_selfTaskingSpawnCount = 0;
} 

// ------------------------------------------------------------------------------------------------
// ?onDie@SpawnBehavior@@ present-unmatched
void SpawnBehavior::onDie( const DamageInfo *damageInfo )
{
	const SpawnBehaviorModuleData *modData = getSpawnBehaviorModuleData();

	///@todo isDieApplicable should be called outside of the onDie call
	if( modData->m_dieMuxData.isDieApplicable( getObject(), damageInfo ) == FALSE )
		return;

	for( objectIDListIterator iter = m_spawnIDs.begin();
				iter != m_spawnIDs.end();
				iter++
					)
	{
		Object *currentSpawn = TheGameLogic->findObjectByID( (*iter) );
		if( currentSpawn )
		{
			// Go through all my spawns and see if they have a SlavedUpdate I can tell I was killed to
			for (BehaviorModule** update = currentSpawn->getBehaviorModules(); *update; ++update)
			{
				SlavedUpdateInterface* sdu = (*update)->getSlavedUpdateInterface();
				if (sdu != NULL)
				{
					sdu->onSlaverDie( damageInfo );
					break;
				}
			}

			// our spawner has died, we must invalidate the ID now in the spawned object
			currentSpawn->setProducer( NULL );

		}
	}

	// kill anything that we have spawned if our module data directs us to do so
	if( modData->m_spawnedRequireSpawner )
	{
		Object *obj;

		for( objectIDListIterator it = m_spawnIDs.begin(); it != m_spawnIDs.end(); /*emtpy*/ )
		{

			// get object
			obj = TheGameLogic->findObjectByID( *it );

			// increment iterator incase the id list is alterd because what we're about to do
			++it;

			// kill it if not already dead
			if( obj && obj->isEffectivelyDead() == FALSE )
				obj->kill();

		}  // end for, it

	}  // end if

}

// Retail SpawnBehavior::update (0x0020C750) is implemented in SpawnBehaviorUpdate.cpp.

// ------------------------------------------------------------------------------------------------
// ?maySpawnSelfTaskAI@SpawnBehavior@@ present-unmatched
Bool SpawnBehavior::maySpawnSelfTaskAI( Real maxSelfTaskersRatio )
{
	if ( m_spawnCount == 0)
		return FALSE;
	if ( maxSelfTaskersRatio == 0)
		return FALSE;

	
	//if my last attack command was from player or script, I need to forbid my spawn from disobeying that command
	//otherwise (since my attack state was autoacquired my ny own ai), let them deviate by the ratio specified.
	Object* obj = getObject();
	if ( ! obj )
		return FALSE;
	AIUpdateInterface *ai = obj->getAI();
	if ( ! ai )
		return FALSE;
	
	CommandSourceType lastAttackCommandSource = ai->getLastCommandSource();
	

	if ( lastAttackCommandSource != CMD_FROM_AI )
		return FALSE;
	

	Real curSelfTaskersRatio = (Real)m_selfTaskingSpawnCount / (Real)m_spawnCount;

	return ( curSelfTaskersRatio < maxSelfTaskersRatio );
}

// Retail SpawnBehavior::getClosestSlave (0x0020B4C0) is implemented in SpawnBehavior_getClosestSlave.cpp.

// ------------------------------------------------------------------------------------------------
// ?orderSlavesToAttackTarget@SpawnBehavior@@ present-unmatched
void SpawnBehavior::orderSlavesToAttackTarget( Object *target, Int maxShotsToFire, CommandSourceType cmdSource )
{
	for( objectIDListIterator it = m_spawnIDs.begin(); it != m_spawnIDs.end(); ++it )
	{
		Object *obj = TheGameLogic->findObjectByID( *it );
		if( obj )
		{
			AIUpdateInterface *ai = obj->getAI();
			if( ai )
			{
				ai->aiForceAttackObject( target, maxShotsToFire, cmdSource );
			}
		}
	}
}

// ------------------------------------------------------------------------------------------------
// ?orderSlavesToAttackPosition@SpawnBehavior@@ present-unmatched
void SpawnBehavior::orderSlavesToAttackPosition( const Coord3D *pos, Int maxShotsToFire, CommandSourceType cmdSource )
{
	for( objectIDListIterator it = m_spawnIDs.begin(); it != m_spawnIDs.end(); ++it )
	{
		Object *obj = TheGameLogic->findObjectByID( *it );
		if( obj )
		{
			AIUpdateInterface *ai = obj->getAI();
			if( ai )
			{
				ai->aiAttackPosition( pos, maxShotsToFire, cmdSource );
			}
		}
	}
}

// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
// ?orderSlavesDisabledUntil@SpawnBehavior@@ present-unmatched
void SpawnBehavior::orderSlavesDisabledUntil( DisabledType type, UnsignedInt frame )
{
	for( objectIDListIterator it = m_spawnIDs.begin(); it != m_spawnIDs.end(); ++it )
	{
		Object *obj = TheGameLogic->findObjectByID( *it );
		if( obj )
		{
			AIUpdateInterface *ai = obj->getAI();
			if( ai )
			{
				ai->aiIdle( CMD_FROM_AI );
			}
			obj->setDisabledUntil( type, frame );
		}
	}
}

// ------------------------------------------------------------------------------------------------
// ?orderSlavesToClearDisabled@SpawnBehavior@@ present-unmatched
void SpawnBehavior::orderSlavesToClearDisabled( DisabledType type )
{
	for( objectIDListIterator it = m_spawnIDs.begin(); it != m_spawnIDs.end(); ++it )
	{
		Object *obj = TheGameLogic->findObjectByID( *it );
		if( obj )
		{
			obj->clearDisabled( type );
		}
	}
}

// Retail SpawnBehavior::getCanAnySlavesAttackSpecificTarget (0x0020B5B0) is implemented in SpawnBehavior_getCanAnySlavesAttackSpecificTarget.cpp.

// Retail SpawnBehavior::getCanAnySlavesUseWeaponAgainstTarget (0x0020B6B0) is implemented in SpawnBehavior_getCanAnySlavesUseWeaponAgainstTarget.cpp.

// ------------------------------------------------------------------------------------------------
// ?giveSlavesStealthUpgrade@SpawnBehavior@@ present-unmatched
void SpawnBehavior::giveSlavesStealthUpgrade( Bool grantStealth )
{
	for( objectIDListIterator it = m_spawnIDs.begin(); it != m_spawnIDs.end(); ++it )
	{
		Object *obj = TheGameLogic->findObjectByID( *it );
		if( obj )
		{
			obj->setStatus( MAKE_OBJECT_STATUS_MASK( OBJECT_STATUS_CAN_STEALTH ), grantStealth );
		}
	}
}

// Retail SpawnBehavior::canAnySlavesAttack (0x0020B7C0) is implemented in SpawnBehavior_canAnySlavesAttack.cpp.


// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
class OrphanData
{

public:

	OrphanData( void );

	const ThingTemplate *m_matchTemplate;
	Object *m_source;
	Object *m_closest;
	Real m_closestDistSq;

};

#define BIG_DISTANCE 99999999.9f
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
OrphanData::OrphanData( void )
{

	m_matchTemplate = NULL;
	m_source = NULL;
	m_closest = NULL;
	m_closestDistSq = BIG_DISTANCE;

}

// ------------------------------------------------------------------------------------------------
static void findClosestOrphan( Object *obj, void *userData )
{
	OrphanData *orphanData = (OrphanData *)userData;

	// if template doesn't match do nothing
	if( obj->getTemplate()->isEquivalentTo( orphanData->m_matchTemplate ) == FALSE )
		return;

	// this object must be orphaned
	if( obj->getProducerID() != INVALID_ID )
		return;

	// is this the closest one so far
	Real distSq = ThePartitionManager->getDistanceSquared( orphanData->m_source, obj, FROM_CENTER_2D );
	if( distSq < orphanData->m_closestDistSq )
	{
	
		orphanData->m_closest = obj;
		orphanData->m_closestDistSq = distSq;

	}  // end if
			
}  // findClosestOrphan

// ------------------------------------------------------------------------------------------------
// ?reclaimOrphanSpawn@SpawnBehavior@@ present-unmatched
Object *SpawnBehavior::reclaimOrphanSpawn( void )
{
	Player *player = getObject()->getControllingPlayer();
	const SpawnBehaviorModuleData *md = getSpawnBehaviorModuleData();

	//
	// iterate all the objects my controlling player has and look for any orphaned things
	// that we would normally spawn, if found we'll just make it our own
	//
	// EVEN MORE NEW AND DIFFERENT
	// This block scans the list for matchTemplates 
	//

	OrphanData orphanData;
	AsciiString prevName = "";
	for (std::vector<AsciiString>::const_iterator tempName = md->m_spawnTemplateNameData.begin();
			tempName != md->m_spawnTemplateNameData.end(); 
			++tempName)
	{
		if (prevName.compare(*tempName)) // the list may have redundancy, this will skip some of it
			continue;
		orphanData.m_matchTemplate = TheThingFactory->findTemplate( *tempName );;
		orphanData.m_source = getObject();
		orphanData.m_closest = NULL;
		orphanData.m_closestDistSq = BIG_DISTANCE;
		player->iterateObjects( findClosestOrphan, &orphanData );
		prevName = *tempName;
	}

	return orphanData.m_closest;
}

// Retail SpawnBehavior::createSpawn (0x0020C3B0) is implemented in SpawnBehaviorCreateSpawn.cpp.

// Retail SpawnBehavior::onSpawnDeath (0x0020C050) is implemented in SpawnBehavior_onSpawnDeath.cpp.

//-------------------------------------------------------------------------------------------------
// ?stopSpawning@SpawnBehavior@@ present-unmatched
void SpawnBehavior::stopSpawning()
{
	m_active = FALSE;
}

//-------------------------------------------------------------------------------------------------
// ?startSpawning@SpawnBehavior@@ present-unmatched
void SpawnBehavior::startSpawning()
{
	m_active = TRUE;
}

// Retail SpawnBehavior::onDamage (0x0020BA00) is implemented in SpawnBehavior_onDamage.cpp.

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ?shouldTryToSpawn@SpawnBehavior@@ present-unmatched
Bool SpawnBehavior::shouldTryToSpawn()
{
	const SpawnBehaviorModuleData *modData = getSpawnBehaviorModuleData();

	// Not if we are turned off
	if( !m_active )
		return FALSE;
	if( getObject()->getStatusBits().test( OBJECT_STATUS_RECONSTRUCTING ) && modData->m_isOneShotData )
	{
		// If we are a Hole rebuild, not only should we not, but we should never ask again.
		stopSpawning();
		return FALSE;
	}
	// Not if we are under construction or being sold
	if( getObject()->testStatus(OBJECT_STATUS_UNDER_CONSTRUCTION) || getObject()->testStatus(OBJECT_STATUS_SOLD) )
		return FALSE;
	// Not if we are civilian controlled
	if( getObject()->isNeutralControlled() )
		return FALSE;

	return TRUE;
}

//********************************************************************
//* This function allows various object states to be either inherited
//* from the spawner to the spawn, or vice versa
//* Selection is distributed across all spawn and spawner at once
//* Health for the spawner is calc'd by aggregating the sum of all
//*   spawn health, and dividing by optimal health of full population
//*   (that is, the max spawn, SpawnBehaviorModuleData::m_spawnNumberData)
//*   at full health.
//* Veterancy is sucked out of any unit that has any and put into the 
//* Spawner, scaled by 1/SpawnBehaviorModuleData::m_spawnNumberData;
//* The HealthBoxPosition (maybe to include moodicon, vet icon) is calc'd
//* as an average position of all the spawn.
//********************************************************************

// Retail SpawnBehavior::computeAggregateStates (0x0020BAE0) is implemented in SpawnBehaviorComputeAggregateStates.cpp.

//-------------------------------------------------------------------------------------------------
// ?areAllSlavesStealthed@SpawnBehavior@@ present-unmatched
Bool SpawnBehavior::areAllSlavesStealthed() const
{
	Object *currentSpawn;

	for( std::list<ObjectID>::const_iterator iter = m_spawnIDs.begin(); iter != m_spawnIDs.end(); iter++)
	{
		currentSpawn = TheGameLogic->findObjectByID( (*iter) );
		if( currentSpawn )
		{
      const StealthUpdate *stealthUpdate = currentSpawn->getStealth();
			if( !stealthUpdate || !stealthUpdate->allowedToStealth( currentSpawn ) )
			{
				return FALSE;
			}
		}
	}

	return TRUE; //0 or more spawns are ALL stealthed... I suppose if you have NO spawns, then they are considered stealthed ;)
}

//-------------------------------------------------------------------------------------------------
// ?revealSlaves@SpawnBehavior@@ present-unmatched
void SpawnBehavior::revealSlaves()
{
	Object *currentSpawn;

	for( objectIDListIterator iter = m_spawnIDs.begin(); iter != m_spawnIDs.end(); iter++)
	{
		currentSpawn = TheGameLogic->findObjectByID( (*iter) );
		if( currentSpawn )
		{
			StealthUpdate *stealthUpdate = currentSpawn->getStealth();
			if( stealthUpdate )
			{
				stealthUpdate->markAsDetected();
			}
		}
	}
}


// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// ?crc@SpawnBehavior@@ present-unmatched
void SpawnBehavior::crc( Xfer *xfer )
{

	// extend base class
	BehaviorModule::crc( xfer );

}  // end crc

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version 
	* 2: Added m_initialBurstTimesInited to the save. jba. 
*/
// ------------------------------------------------------------------------------------------------
// ?xfer@SpawnBehavior@@ present-unmatched
void SpawnBehavior::xfer( Xfer *xfer )
{
	AsciiString name;

	// version
	XferVersion currentVersion = 2;
	XferVersion version = currentVersion;
	xfer->xferVersion( &version, currentVersion );

	// extend base class
	BehaviorModule::xfer( xfer );

	
	if (version >= 2) {
		xfer->xferBool(&m_initialBurstTimesInited);
	}

	// spawn template
	name = m_spawnTemplate ? m_spawnTemplate->getName() : AsciiString::TheEmptyString;
	xfer->xferAsciiString( &name );
	if( xfer->getXferMode() == XFER_LOAD )
	{

		m_spawnTemplate = NULL;
		if( name.isEmpty() == FALSE )
		{
		
			m_spawnTemplate = TheThingFactory->findTemplate( name );
			if( m_spawnTemplate == NULL )
			{

				DEBUG_CRASH(( "SpawnBehavior::xfer - Unable to find template '%s'\n", name.str() ));
				throw SC_INVALID_DATA;

			}  // end if

		}  // end if

	}  // end if

	// one shot countdown
	xfer->xferInt( &m_oneShotCountdown );

	// frames to wait
	xfer->xferInt( &m_framesToWait );

	// first batch count
	xfer->xferInt( &m_firstBatchCount );

	// replacement times
	if( xfer->getXferMode() == XFER_LOAD )
		m_replacementTimes.clear();
	xfer->xferSTLIntList( &m_replacementTimes );

	// spawn ids
	xfer->xferSTLObjectIDList( &m_spawnIDs );

	// active
	xfer->xferBool( &m_active );

	// aggregate health
	xfer->xferBool( &m_aggregateHealth );

	// spawn count
	xfer->xferInt( &m_spawnCount );

	// self tasking spawn count
	xfer->xferUnsignedInt( &m_selfTaskingSpawnCount );

}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
// ?loadPostProcess@SpawnBehavior@@ present-unmatched
void SpawnBehavior::loadPostProcess( void )
{

	// extend base class
	BehaviorModule::loadPostProcess();

}  // end loadPostProcess

// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
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

// FILE: ActionManager.cpp ////////////////////////////////////////////////////////////////////////
// Author: Colin Day
// Desc:   TheActionManager is a convenient place for us to wrap up all sorts of logical 
//				 queries about what objects can do in the world and to other objects.  The purpose
//				 of having a central place for this logic assists us in making these logical kind
//				 of queries in the user interface and allows us to use the same code to validate
//				 commands as they come in over the network interface in order to do the 
//				 real action.
///////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/ActionManager.h"
#include "Common/GlobalData.h"
#include "Common/Player.h"
#include "Common/PlayerList.h"
#include "Common/SpecialPower.h"
#include "Common/Team.h"
#include "Common/ThingTemplate.h"

#include "GameClient/Drawable.h"
#include "GameClient/InGameUI.h"

#include "GameLogic/Object.h"
#include "GameLogic/PartitionManager.h"
#include "GameLogic/Module/BodyModule.h"
#include "GameLogic/Module/ContainModule.h"
#include "GameLogic/Module/CollideModule.h"
#include "GameLogic/Module/DozerAIUpdate.h"
#include "GameLogic/Module/RailroadGuideAIUpdate.h"
#include "GameLogic/Module/RailedTransportDockUpdate.h"
#include "GameLogic/Module/SpawnBehavior.h"
#include "GameLogic/Module/SupplyTruckAIUpdate.h"
#include "GameLogic/Module/SupplyCenterDockUpdate.h"
#include "GameLogic/Module/SupplyWarehouseDockUpdate.h"
#include "GameLogic/Module/SpecialPowerModule.h"
#include "GameLogic/Module/SpecialAbilityUpdate.h"
#include "GameLogic/Weapon.h"

#include "GameLogic/ExperienceTracker.h"//LORENZEN

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

// GLOBAL /////////////////////////////////////////////////////////////////////////////////////////
ActionManager *TheActionManager = NULL;

// LOCAL //////////////////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
static Bool appearsToContainFriendlies(const Object* obj, const Object* otherObject)
{
	// check if the object is a container containing stealth units tricking
	// the player into thinking it isn't actually an enemy.
	const ContainModuleInterface *otherContain = otherObject->getContain();
	if( otherContain )
	{
		const Player *otherPlayer = otherContain->getApparentControllingPlayer(obj->getControllingPlayer());
//	if( otherPlayer && otherPlayer->getRelationship( obj->getTeam() ) != ENEMIES )
// the above test is wrong; we want to know how WE consider THEM, not how THEY consider US
		if (otherPlayer && obj->getTeam()->getRelationship(otherPlayer->getDefaultTeam()) != ENEMIES)
		{
			return TRUE;
		}
	}
	return FALSE;
}

// BFME's out-of-line status helpers predate the ZH inline wrappers in the supplied headers.
class BFMEActionObject
{
public:
	Bool testStatus(Int status) const;
};

class BFMEActionThing
{
public:
	Bool isKindOf(Int kind) const;
};

class BFMEObjectStealthQuery
{
public:
	Bool isStealthedAndUndetected(const Object *viewer) const;
};

class BFMECaptureContainModule
{
public:
	virtual void slot_000() = 0;
	virtual void slot_004() = 0;
	virtual Bool isGarrisonable() const = 0;
	virtual void slot_00c() = 0;
	virtual void slot_010() = 0;
	virtual void slot_014() = 0;
	virtual void slot_018() = 0;
	virtual void slot_01c() = 0;
	virtual void slot_020() = 0;
	virtual void slot_024() = 0;
	virtual void slot_028() = 0;
	virtual void slot_02c() = 0;
	virtual void slot_030() = 0;
	virtual void slot_034() = 0;
	virtual void slot_038() = 0;
	virtual void slot_03c() = 0;
	virtual void slot_040() = 0;
	virtual void slot_044() = 0;
	virtual void slot_048() = 0;
	virtual void slot_04c() = 0;
	virtual void slot_050() = 0;
	virtual void slot_054() = 0;
	virtual void slot_058() = 0;
	virtual void slot_05c() = 0;
	virtual void slot_060() = 0;
	virtual void slot_064() = 0;
	virtual void slot_068() = 0;
	virtual void slot_06c() = 0;
	virtual void slot_070() = 0;
	virtual void slot_074() = 0;
	virtual void slot_078() = 0;
	virtual void slot_07c() = 0;
	virtual void slot_080() = 0;
	virtual void slot_084() = 0;
	virtual void slot_088() = 0;
	virtual void slot_08c() = 0;
	virtual void slot_090() = 0;
	virtual void slot_094() = 0;
	virtual void slot_098() = 0;
	virtual void slot_09c() = 0;
	virtual void slot_0a0() = 0;
	virtual void slot_0a4() = 0;
	virtual void slot_0a8() = 0;
	virtual void slot_0ac() = 0;
	virtual void slot_0b0() = 0;
	virtual void slot_0b4() = 0;
	virtual void slot_0b8() = 0;
	virtual void slot_0bc() = 0;
	virtual void slot_0c0() = 0;
	virtual void slot_0c4() = 0;
	virtual void slot_0c8() = 0;
	virtual void slot_0cc() = 0;
	virtual void slot_0d0() = 0;
	virtual void slot_0d4() = 0;
	virtual void slot_0d8() = 0;
	virtual void slot_0dc() = 0;
	virtual void slot_0e0() = 0;
	virtual void slot_0e4() = 0;
	virtual void slot_0e8() = 0;
	virtual void slot_0ec() = 0;
	virtual void slot_0f0() = 0;
	virtual void slot_0f4() = 0;
	virtual void slot_0f8() = 0;
	virtual void slot_0fc() = 0;
	virtual Int getContainCount(Int arg) const = 0;
	virtual void slot_104() = 0;
	virtual void slot_108() = 0;
	virtual void slot_10c() = 0;
	virtual Int getStealthUnitsContained() const = 0;
};

class BFMEActionBehaviorModule
{
public:
	virtual void slot0() = 0;
	virtual CollideModuleInterface *getCollide() = 0;
};

class BFMECarBombCollideModuleInterface
{
public:
	virtual void slot0() = 0;
	virtual Bool wouldLikeToCollideWith(const Object *other) const = 0;
	virtual void slot2() = 0;
	virtual Bool isCarBombCrateCollide() const = 0;
};

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
static Bool isObjectShroudedForAction(const Object *source, const Object *target, CommandSourceType commandSource)
{
	if (target)
	{
		// BFME reserves this signed ObjectID range for non-world objects, which cannot be shrouded targets.
		Int targetID = *reinterpret_cast<const Int *>(reinterpret_cast<const char *>(target) + 0x74);
		if (targetID >= 0x05f5e0fc && targetID <= 0x05f5e0ff)
			return FALSE;
	}

	if (source && target && source->getControllingPlayer())
	{
		if (*reinterpret_cast<const Int *>(reinterpret_cast<const char *>(source->getControllingPlayer()) + 0x2c) == PLAYER_HUMAN &&
				commandSource != CMD_FROM_SCRIPT &&
				target->getShroudedStatus(source->getControllingPlayer()->getPlayerIndex()) >= OBJECTSHROUD_FOGGED)
		{
			return TRUE;
		}
	}

	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ??0ActionManager@@QAE@XZ present-unmatched
ActionManager::ActionManager( void )
{

}  // end ActionManager

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ??1ActionManager@@UAE@XZ present-unmatched
ActionManager::~ActionManager( void )
{

}  // end ~ActionManager

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ?canGetRepairedAt@ActionManager@@QAE_NPBVObject@@0W4CommandSourceType@@@Z present-unmatched
Bool ActionManager::canGetRepairedAt( const Object *obj, const Object *repairDest, CommandSourceType commandSource ) 
{

	// sanity
	if( obj == NULL || repairDest == NULL )
		return FALSE;

	Relationship r = obj->getRelationship(repairDest);

	// only available by our allies
	if( r != ALLIES )
		return FALSE;

	// dead objects cannot be repaired
	if( obj->isEffectivelyDead() )
		return FALSE;
	
	// If I can't move, I can't get repaired
	if( !obj->isMobile() )
		return FALSE;

	// nothing can be done with things that are under construction
	if( obj->getStatusBits().test( OBJECT_STATUS_UNDER_CONSTRUCTION ) ||
			repairDest->getStatusBits().test( OBJECT_STATUS_UNDER_CONSTRUCTION ) )
		return FALSE;

	// Can't get repaired at something being sold
	if( repairDest->testStatus(OBJECT_STATUS_SOLD) )
		return FALSE;
	
	// only vehicles can go get repaired at something
	if( obj->isKindOf( KINDOF_VEHICLE ) == FALSE )
		return FALSE;

	// vehicles can only be repaired at something that is designated as a repair pad
	if (obj->isKindOf( KINDOF_AIRCRAFT ))
	{
		// aircraft require an airfield.
		if( !obj->isAboveTerrain() ||
					repairDest->isKindOf( KINDOF_FS_AIRFIELD ) == FALSE )
			return FALSE;
	}
	else
	{
		if( repairDest->isKindOf( KINDOF_REPAIR_PAD ) == FALSE )
			return FALSE;
	}

	// if I am at full health, I can't get repair there
	BodyModuleInterface *body = obj->getBodyModule();
	if( body->getHealth() == body->getMaxHealth() )
		return FALSE;

	// if the target is in the shroud, we can't do anything
	if (isObjectShroudedForAction(obj, repairDest, commandSource))
		return FALSE;

	// all is well, we can be repaired here
	return TRUE;

}  // end canGetRepairedAt

// ------------------------------------------------------------------------------------------------
/** Can object 'obj' dock with object 'dockDest' for any reason */
// ------------------------------------------------------------------------------------------------
// ?canDockAt@ActionManager@@ present-unmatched
Bool ActionManager::canDockAt( const Object *obj, const Object *dockDest, CommandSourceType commandSource )
{

	// look for a dock interface
	DockUpdateInterface *di = NULL;
	for (BehaviorModule **u = dockDest->getBehaviorModules(); *u; ++u)
	{
		if ((di = (*u)->getDockUpdateInterface()) != NULL)
			break;
	}
	if( di == NULL )
		return FALSE;  // no dock update interface, can't possibly dock

/*
	// can't dock if the dock is closed
	if( di->isDockOpen() == FALSE )
		return FALSE;
*/

	// transferring supplies is a valid docking action
	if( canTransferSuppliesAt( obj, dockDest ) == TRUE )
		return TRUE;

	// units and infantry can dock with a railed transport
	static const NameKeyType key = NAMEKEY( "RailedTransportDockUpdate" );
	RailedTransportDockUpdate *fdu = (RailedTransportDockUpdate *)dockDest->findUpdateModule( key );
	if( fdu )
	{

		if( obj->isKindOf( KINDOF_VEHICLE ) || obj->isKindOf( KINDOF_INFANTRY ) )
			return TRUE;

	}  // end if

	// cannot dock
	return FALSE;

}  // end canDockAt

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
Bool ActionManager::canGetHealedAt( const Object *obj, const Object *healDest, CommandSourceType commandSource ) 
{

	// sanity
	if( obj == NULL || healDest == NULL )
		return FALSE;

	Relationship r = obj->getRelationship(healDest);

	// only available by our allies
	if( r != ALLIES )
		return FALSE;

	// dead objects cannot be healed
	// These fields moved in ZH; use the verified BFME Object layout used by the retail checks.
	if (*reinterpret_cast<const UnsignedByte *>(reinterpret_cast<const char *>(healDest) + 0x344) & 1)
		return FALSE;

	// nothing can be done with things that are under construction
	if (*reinterpret_cast<const UnsignedByte *>(reinterpret_cast<const char *>(obj) + 0x90) & 4)
		return FALSE;
	if (reinterpret_cast<const BFMEActionObject *>(healDest)->testStatus(2))
		return FALSE;

	// Can't get healed at something being sold
	if (reinterpret_cast<const BFMEActionObject *>(healDest)->testStatus(0x13))
		return FALSE;
	
	// only infantry can go get "healed" somewhere (vehicles get "repaired")
	if (reinterpret_cast<const BFMEActionThing *>(obj)->isKindOf(8) == FALSE)
		return FALSE;

	// infantry can only be healed at something that is designated as a heal pad
	if (reinterpret_cast<const BFMEActionThing *>(healDest)->isKindOf(0x20) == FALSE)
		return FALSE;

	// if the target is in the shroud, we can't do anything
	if (isObjectShroudedForAction(obj, healDest, commandSource))
		return FALSE;
	
	class BFMEHealBody
	{
	public:
		virtual void slot0() = 0;
		virtual void slot1() = 0;
		virtual void slot2() = 0;
		virtual void slot3() = 0;
		virtual Real getHealth() const = 0;
		virtual void slot5() = 0;
		virtual Real getMaxHealth() const = 0;
	};
	BFMEHealBody *body = *reinterpret_cast<BFMEHealBody * const *>(reinterpret_cast<const char *>(obj) + 0x200);
	if( body && body->getHealth() == body->getMaxHealth() )
	{
		//No point in healing if you have full health!
		return FALSE;
	}

	// all is well, we can be healed here
	return TRUE;

}  // end canGetHealedAt

// ------------------------------------------------------------------------------------------------
/** Can 'obj' resume the construction of 'objectBeingConstructed' */
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ?canEnterObject@ActionManager@@QAE_NPBVObject@@0W4CommandSourceType@@W4CanEnterType@@@Z present-unmatched
Bool ActionManager::canEnterObject( const Object *obj, const Object *objectToEnter, CommandSourceType commandSource, CanEnterType mode )
{

	// sanity
	if( obj == NULL || objectToEnter == NULL )
		return FALSE;
	
	if( obj == objectToEnter )
	{
		//You can't contain yourself (crash fix for pow truck reselection)
		return FALSE;
	}

	// can't enter dead things
	if( objectToEnter->isEffectivelyDead() )
		return FALSE;

	// if the target is in the shroud, we can't do anything
	if (isObjectShroudedForAction(obj, objectToEnter, commandSource))
		return FALSE;

	// nothing can be done with things that are under construction
	if( obj->getStatusBits().test( OBJECT_STATUS_UNDER_CONSTRUCTION ) ||
			objectToEnter->getStatusBits().test( OBJECT_STATUS_UNDER_CONSTRUCTION ) )
	{
		return FALSE;
	}
	
	// Can't enter something being sold
	if( objectToEnter->testStatus(OBJECT_STATUS_SOLD) )
		return FALSE;
	if ( obj->isKindOf( KINDOF_IGNORED_IN_GUI )  //As in, Angry Mob Members, Cargo Planes
		|| obj->isKindOf( KINDOF_MOB_NEXUS )   
		|| objectToEnter->isKindOf( KINDOF_IGNORED_IN_GUI ) )  // As in Cargo Planes
	{																					
																						
		return FALSE;
	}


  if (objectToEnter->isDisabledByType( DISABLED_SUBDUED ))
    return FALSE; // a microwave tank has soldered the doors shut


	if( obj->isKindOf( KINDOF_STRUCTURE ) || obj->isKindOf( KINDOF_IMMOBILE ) )
	{
		//Structures or immobiles can't garrison
		return FALSE;
	}

	// Special case for unmanned vehicles. Any infantry unit can take over any unmanned vehicle!
	if( obj->isKindOf( KINDOF_INFANTRY ) && objectToEnter->isDisabledByType( DISABLED_UNMANNED ) )
	{
		if( !obj->isKindOf( KINDOF_REJECT_UNMANNED ) )
		{
			//But only if it's allowed to.
			return TRUE;
		}
	}

	// Special case for aircraft.
	if( obj->isKindOf( KINDOF_AIRCRAFT ) && objectToEnter->isKindOf( KINDOF_FS_AIRFIELD ) )
	{
		if( obj->getStatusBits().test( OBJECT_STATUS_DECK_HEIGHT_OFFSET ) && obj->getCarrierDeckHeight() >= obj->getPosition()->z )
		{
			return FALSE;
		}

		if (!obj->isAboveTerrain())
			return FALSE;
		
		if( obj->getControllingPlayer() == objectToEnter->getControllingPlayer() )
		{
			//Kris -- added code to prevent aircraft from landing in any airstrips other than their own!

			/// @todo srj -- this is horrible, but expedient.
			for (BehaviorModule** i = objectToEnter->getBehaviorModules(); *i; ++i)
			{
				ParkingPlaceBehaviorInterface* pp = (*i)->getParkingPlaceBehaviorInterface();
				if (pp == NULL)
					continue;

				if (pp->hasReservedSpace(obj->getID()))
					return TRUE;
						
				if (pp->shouldReserveDoorWhenQueued(obj->getTemplate()) && pp->hasAvailableSpaceFor(obj->getTemplate()))
					return TRUE;
			}
		}
		return FALSE;
	}

	// first, see if we'd like to collide with 'other'
	for (BehaviorModule** m = obj->getBehaviorModules(); *m; ++m)
	{
		CollideModuleInterface* collide = (*m)->getCollide();
		if (!collide)
			continue;

		if( collide->wouldLikeToCollideWith( objectToEnter ) )
		{
			//I thought this was a little confusing that it would return TRUE here before
			//getting to any of the other checks. The key is that it usually doesn't return
			//TRUE because most things aren't trying to collide with objects. This is different
			//for terrorist converting carbombs, and pilots entering vehicles. In these cases,
			//the vehicles don't have transport capacities, therefore returning true here 
			//foregoes that checking later on.
			return TRUE;
		}
	}
	
#ifdef ALLOW_SURRENDER
	if( objectToEnter->isKindOf( KINDOF_PRISON ) )
	{
		//We can't manually enter a prison!
		return FALSE;
	}
#endif

#ifdef ALLOW_SURRENDER
	if( objectToEnter->isKindOf( KINDOF_POW_TRUCK ) )
	{
		//We can't manually enter POWTruck, either!
		return FALSE;
	}
#endif

	// make sure our objectToEnter has a contain module.
	ContainModuleInterface *contain = objectToEnter->getContain();
	if( !contain )
	{
		return FALSE;
	}

	if( contain->isHealContain() )
	{
		BodyModuleInterface *body = obj->getBodyModule();
		if( body->getHealth() == body->getMaxHealth() )
		{
			//This container is only used for the purposes of healing and we cannot 
			//enter it with full health. This is not a normal container.
			return FALSE;
		}
	}

	if (mode == COMBATDROP_INTO)
	{
		// we don't care about valid container-ness, but we DO care about faction structures...
		// we aren't allowed to combat drop into them
		if (objectToEnter->isFactionStructure())
			return FALSE;
	}
	else
	{
		Bool checkCapacity = (mode == CHECK_CAPACITY);
		Int containCount = contain->getContainCount();
		Int stealthContainCount = contain->getStealthUnitsContained();
		Int nonStealthContainCount = containCount - stealthContainCount;

		// not ours... must do special checks.
		if (objectToEnter->getControllingPlayer() != obj->getControllingPlayer())
		{
			// not empty... can't do it.
			if (nonStealthContainCount > 0)
				return FALSE;

			// faction structure... can't do it.
			if (objectToEnter->isFactionStructure())
				return FALSE;
			
			// it's stealth-garrisoned... ignore check-cap and fall thru to
			// normal isValid test.
			if (stealthContainCount > 0 && nonStealthContainCount == 0)
				checkCapacity = FALSE;
		}

		// if our transport slot count is zero, we can't be transported. so punt.
		/// @todo srj -- seems like we should check always (not just for checkCap), but scared to change now -- check later
		if( checkCapacity && obj->getTransportSlotCount() == 0 )
		{
			return FALSE;		
		}

		// finally: make sure that objectToEnter is a valid container for obj
		if( contain->isValidContainerFor( obj, checkCapacity ) == FALSE )
		{
			return FALSE;
		}
	}

	return TRUE;

}


// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
Bool ActionManager::canConvertObjectToCarBomb( const Object *obj, const Object *objectToConvert, CommandSourceType commandSource ) 
{

	// sanity
	if( obj == NULL || objectToConvert == NULL )
	{
		return FALSE;
	}

	if (*reinterpret_cast<const UnsignedByte *>(reinterpret_cast<const char *>(objectToConvert) + 0x344) & 1)
	{
		return FALSE;
	}

	// if the target is in the shroud, we can't do anything
	if (isObjectShroudedForAction(obj, objectToConvert, commandSource))
		return FALSE;

	// first, see if we'd like to collide with 'other'
	BehaviorModule **m = *reinterpret_cast<BehaviorModule ***>(reinterpret_cast<char *>(const_cast<Object *>(obj)) + 0x1f0);
	for (; *m; ++m)
	{
		BFMEActionBehaviorModule *module = reinterpret_cast<BFMEActionBehaviorModule *>(reinterpret_cast<char *>(*m) + 0x0c);
		BFMECarBombCollideModuleInterface *collide = reinterpret_cast<BFMECarBombCollideModuleInterface *>(module->getCollide());
		if (!collide)
			continue;

		if( collide->wouldLikeToCollideWith( objectToConvert ) && collide->isCarBombCrateCollide() )
		{
			return TRUE;
		}
	}
	return FALSE;
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
Bool ActionManager::canHijackVehicle( const Object *obj, const Object *objectToHijack, CommandSourceType commandSource ) //LORENZEN
{
	if (obj == NULL || objectToHijack == NULL)
		return FALSE;
	if (*reinterpret_cast<const UnsignedByte *>(reinterpret_cast<const char *>(objectToHijack) + 0x344) & 1)
		return FALSE;
	if (isObjectShroudedForAction(obj, objectToHijack, commandSource))
		return FALSE;
	if (obj->getRelationship(objectToHijack) != ENEMIES)
		return FALSE;
	if (reinterpret_cast<const BFMEActionThing *>(objectToHijack)->isKindOf(12))
		return FALSE;

	BehaviorModule **m = *reinterpret_cast<BehaviorModule ***>(reinterpret_cast<char *>(const_cast<Object *>(obj)) + 0x1f0);
	for (; *m; ++m)
	{
		BFMEActionBehaviorModule *module = reinterpret_cast<BFMEActionBehaviorModule *>(reinterpret_cast<char *>(*m) + 0x0c);
		CollideModuleInterface *collide = module->getCollide();
		if (!collide)
			continue;
		if (collide->wouldLikeToCollideWith(objectToHijack) && collide->isHijackedVehicleCrateCollide())
			return TRUE;
	}
	return FALSE;
}

// ------------------------------------------------------------------------------------------------
// ?canSabotageBuilding@ActionManager@@QAE_NPBVObject@@0W4CommandSourceType@@@Z present-unmatched
Bool ActionManager::canSabotageBuilding( const Object *obj, const Object *objectToSabotage, CommandSourceType commandSource )
{
	// sanity
	if( obj == NULL || objectToSabotage == NULL )
	{
		return FALSE;
	}

	//Make sure it's alive.
	if( objectToSabotage->isEffectivelyDead() )
	{
		return FALSE;
	}

	// if the target is in the shroud, we can't do anything
	if (isObjectShroudedForAction(obj, objectToSabotage, commandSource))
	{
		return FALSE;
	}

	Relationship r = obj->getRelationship(objectToSabotage);
	//Only sabotage enemy objects
	if( r != ENEMIES )
	{
		return FALSE;
	}

	// last, see if we'd like to collide with 'objectToSabotage' 
	for (BehaviorModule** m = obj->getBehaviorModules(); *m; ++m)
	{
		CollideModuleInterface* collide = (*m)->getCollide();
		if (!collide)
			continue;

		if( collide->wouldLikeToCollideWith( objectToSabotage ) && collide->isSabotageBuildingCrateCollide() )
		{
			return TRUE;
		}
	}

	return FALSE;
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ?canMakeObjectDefector@ActionManager@@QAE_NPBVObject@@0W4CommandSourceType@@@Z present-unmatched
Bool ActionManager::canMakeObjectDefector( const Object *obj, const Object *objectToMakeDefector, CommandSourceType commandSource ) //LORENZEN
{
	// sanity
	if( obj == NULL || objectToMakeDefector == NULL )
	{
		return FALSE;
	}

	Relationship r = obj->getRelationship(objectToMakeDefector);

	//Only make defectors of enemy objects
	if( r != ENEMIES )
	{
		return FALSE;
	}

	//Make sure it's alive.
	if( objectToMakeDefector->isEffectivelyDead() )
	{
		return FALSE;
	}

	// if the target is in the shroud, we can't do anything
	if (isObjectShroudedForAction(obj, objectToMakeDefector, commandSource))
	{
		return FALSE;
	}


	return TRUE;
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

Bool ActionManager::canCaptureBuilding( const Object *obj, const Object *objectToCapture, CommandSourceType commandSource )
{

	// sanity
	if( obj == NULL || objectToCapture == NULL )
		return FALSE;

	//Make sure our object has the capability of performing this special ability.

	Bool isOwnerBlackLotus = obj->hasSpecialPower((SpecialPowerType)0x1a);

	if( !obj->hasSpecialPower((SpecialPowerType)0x1d) && !isOwnerBlackLotus)
	{
		return false;
	}

	if( objectToCapture->isKindOf((KindOfType)0x50) )
	{
		return false;
	}

//  This is the althernate way to one-at-a-time BlackLotus' specials; we'll keep it commented her until Dustin decides, or until 12/10/02
//	if ( isOwnerBlackLotus )
//	{
//		SpecialPowerModuleInterface *disableSPI = obj->findSpecialPowerModuleInterface( SPECIAL_BLACKLOTUS_DISABLE_VEHICLE_HACK );
//		if ( disableSPI && disableSPI->isBusy() )
//			return FALSE;
//		SpecialPowerModuleInterface *cashSPI = obj->findSpecialPowerModuleInterface( SPECIAL_BLACKLOTUS_STEAL_CASH_HACK );
//		if ( cashSPI && cashSPI->isBusy() )
//			return FALSE;
//	}


	SpecialPowerModuleInterface *spInterface = obj->findSpecialPowerModuleInterface((SpecialPowerType)0x1d);
	if (!spInterface)
		spInterface = obj->findSpecialPowerModuleInterface((SpecialPowerType)0x1a);
	if (!spInterface)
		return false;

	if( spInterface->getPercentReady() < 1.0f )
	{
		// Special not ready or non-existent.
		return false;
	}

	// can't capture things that are under construction, or sold.
	if (*reinterpret_cast<const UnsignedByte *>(reinterpret_cast<const char *>(objectToCapture) + 0x344) & 1)
		return FALSE;

	// Make sure we are targeting a building!
	if( !objectToCapture->isKindOf((KindOfType)7) )
	{
		return FALSE;
	}

	if (reinterpret_cast<const BFMEActionObject *>(objectToCapture)->testStatus(2) ||
			reinterpret_cast<const BFMEActionObject *>(objectToCapture)->testStatus(0x13))
	{
		return FALSE;
	}

	// if the target is in the shroud, we can't do anything
	if (isObjectShroudedForAction(obj, objectToCapture, commandSource))
		return FALSE;

	Relationship r = obj->getRelationship(objectToCapture);

	// ensure that it's capturable, and not allied
	// exception: we can always capture enemy bldgs, regardless of kindof
	if (!(r == ENEMIES || (objectToCapture->isKindOf((KindOfType)0x31) && r != ALLIES)))
		return false;

	//If the enemy unit is stealthed and not detected, then we can't capture it!
	if (reinterpret_cast<const BFMEObjectStealthQuery *>(objectToCapture)->isStealthedAndUndetected(reinterpret_cast<const Object *>(obj->getControllingPlayer())))
	{
		return FALSE;
	}

	// if it's garrisoned already, we cannot capture it.
	// (unless it's just stealth-garrisoned.)
	BFMECaptureContainModule *contain = *reinterpret_cast<BFMECaptureContainModule * const *>(reinterpret_cast<const char *>(objectToCapture) + 0x1fc);
	if (contain != NULL && contain->isGarrisonable())
	{
		Int containCount = contain->getContainCount(0);
		Int stealthContainCount = contain->getStealthUnitsContained();
		Int nonStealthContainCount = containCount - stealthContainCount;
		if (nonStealthContainCount > 0)
			return FALSE;
	}

	// Also check if the object is a container containing stealth units, tricking
	// the player into thinking it isn't actually an enemy.
	if (appearsToContainFriendlies(obj, objectToCapture))
		return FALSE;
	return TRUE;
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ?canDisableVehicleViaHacking@ActionManager@@QAE_NPBVObject@@0W4CommandSourceType@@_N@Z present-unmatched
Bool ActionManager::canDisableVehicleViaHacking( const Object *obj, const Object *objectToHack, CommandSourceType commandSource, Bool checkSourceRequirements)
{
	// sanity
	if( obj == NULL || objectToHack == NULL )
		return FALSE;

	if (checkSourceRequirements)
	{
		//Make sure our object has the capability of performing this special ability.
		if( !obj->hasSpecialPower( SPECIAL_BLACKLOTUS_DISABLE_VEHICLE_HACK ) )
		{
			return false;
		}
	}

//  This is the althernate way to one-at-a-time BlackLotus' specials; we'll keep it commented her until Dustin decides, or until 12/10/02
//	SpecialPowerModuleInterface *captureSPI = obj->findSpecialPowerModuleInterface( SPECIAL_BLACKLOTUS_CAPTURE_BUILDING );
//	if ( captureSPI && captureSPI->isBusy() )
//		return FALSE;
//	SpecialPowerModuleInterface *cashSPI = obj->findSpecialPowerModuleInterface( SPECIAL_BLACKLOTUS_STEAL_CASH_HACK );
//	if ( cashSPI && cashSPI->isBusy() )
//		return FALSE;

	
	SpecialPowerModuleInterface *spInterface = obj->findSpecialPowerModuleInterface( SPECIAL_BLACKLOTUS_DISABLE_VEHICLE_HACK );
	if (checkSourceRequirements)
	{
		if( !spInterface || spInterface->getPercentReady() < 1.0f )
		{
			//Special not ready or non-existent.
			return FALSE;
		}
	}

	if( objectToHack->isEffectivelyDead() )
	{
		return FALSE;
	}

	if( objectToHack->isKindOf( KINDOF_AIRCRAFT ) || objectToHack->isAirborneTarget() )
	{
		return false;
	}

	// if the target is in the shroud, we can't do anything
	if (isObjectShroudedForAction(obj, objectToHack, commandSource))
		return FALSE;

	Relationship r = obj->getRelationship(objectToHack);

	// Make sure object is an enemy
	if( r == ENEMIES )
	{

		//Make sure we are targeting a building!
		if( !objectToHack->isKindOf( KINDOF_VEHICLE ) )
		{
			return FALSE;
		}

		//If the enemy unit is stealthed and not detected, then we can't attack it!
	if( objectToHack->testStatus( OBJECT_STATUS_STEALTHED ) && 
			!objectToHack->testStatus( OBJECT_STATUS_DETECTED ) &&
			!objectToHack->testStatus( OBJECT_STATUS_DISGUISED ) )
		{
			return FALSE;
		}

		//Also check if the object is a container containing stealth units tricking
		//the player into thinking it isn't actually an enemy.
		if (appearsToContainFriendlies(obj, objectToHack))
			return FALSE;

		return TRUE;
	}
	return FALSE;
}

#ifdef ALLOW_SURRENDER
// ------------------------------------------------------------------------------------------------
/** Can 'obj' pick up the prisoner 'prisoner' */
// ------------------------------------------------------------------------------------------------
// ?canPickUpPrisoner@ActionManager@@ present-unmatched
Bool ActionManager::canPickUpPrisoner( const Object *obj, const Object *prisoner, CommandSourceType commandSource )
{

	// sanity
	if( obj == NULL || prisoner == NULL )
		return FALSE;

	// only pow trucks can pick up anything
	if( obj->isKindOf( KINDOF_POW_TRUCK ) == FALSE )
		return FALSE;

	// only infantry can be picked up
	if( prisoner->isKindOf( KINDOF_INFANTRY ) == FALSE )
		return FALSE;

	// prisoner cannot be contained inside anything
	if( prisoner->getContainedBy() )
		return FALSE;

	// prisoner must be in a surrendered state
	const AIUpdateInterface *ai = prisoner->getAI();
	if( ai == NULL || ai->isSurrendered() == FALSE )
		return FALSE;

	// prisoner must have been put in a surrendered state by our own player
	// (or be surrendered to "everyone")
	Int idx = ai->getSurrenderedPlayerIndex();
	Player* surrenderedToPlayer = (idx >= 0) ? ThePlayerList->getNthPlayer(idx) : NULL;
	if (surrenderedToPlayer != NULL && surrenderedToPlayer != obj->getControllingPlayer())
		return FALSE;

	// we must be enemies
	if( obj->getRelationship( prisoner ) != ENEMIES )
		return FALSE;

	return TRUE;

}  // end canPickUpPrisoner
#endif

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ?canStealCashViaHacking@ActionManager@@QAE_NPBVObject@@0W4CommandSourceType@@@Z present-unmatched
Bool ActionManager::canStealCashViaHacking( const Object *obj, const Object *objectToHack, CommandSourceType commandSource )
{
	// sanity
	if( obj == NULL || objectToHack == NULL )
		return FALSE;

	//Make sure our object has the capability of performing this special ability.
	if( !obj->hasSpecialPower( SPECIAL_BLACKLOTUS_STEAL_CASH_HACK ) )
	{
		return false;
	}

//  This is the althernate way to one-at-a-time BlackLotus' specials; we'll keep it commented her until Dustin decides, or until 12/10/02
//	SpecialPowerModuleInterface *captureSPI = obj->findSpecialPowerModuleInterface( SPECIAL_BLACKLOTUS_CAPTURE_BUILDING );
//	if ( captureSPI && captureSPI->isBusy() )
//		return FALSE;
//	SpecialPowerModuleInterface *disableSPI = obj->findSpecialPowerModuleInterface( SPECIAL_BLACKLOTUS_DISABLE_VEHICLE_HACK );
//	if ( disableSPI && disableSPI->isBusy() )
//		return FALSE;


	SpecialPowerModuleInterface *spInterface = obj->findSpecialPowerModuleInterface( SPECIAL_BLACKLOTUS_STEAL_CASH_HACK );
	if( !spInterface || spInterface->getPercentReady() < 1.0f )
	{
		//Special not ready or non-existent.
		return false;
	}

	if( objectToHack->isEffectivelyDead() )
	{
		return FALSE;
	}

	if( objectToHack->getStatusBits().test( OBJECT_STATUS_UNDER_CONSTRUCTION ) )
	{
		return FALSE;
	}

	// if the target is in the shroud, we can't do anything
	if (isObjectShroudedForAction(obj, objectToHack, commandSource))
		return FALSE;

	Relationship r = obj->getRelationship(objectToHack);

	// Make sure object is an enemy
	if( r == ENEMIES )
	{

		//Make sure we are targeting something that contains cash!
		if( !objectToHack->isKindOf( KINDOF_CASH_GENERATOR ) )
		{
			return FALSE;
		}
		
		//Make sure object isn't under construction!
		if( objectToHack->getStatusBits().test( OBJECT_STATUS_UNDER_CONSTRUCTION ) )
		{
			return FALSE;
		}
		
		//Make sure the building is considered hackable (temp: using capturable)
		if( !objectToHack->isKindOf( KINDOF_CAPTURABLE ) || objectToHack->isKindOf( KINDOF_REBUILD_HOLE ) )
		{
			return FALSE;
		}

		//If the enemy unit is stealthed and not detected, then we can't attack it!
	if( objectToHack->testStatus( OBJECT_STATUS_STEALTHED ) && 
			!objectToHack->testStatus( OBJECT_STATUS_DETECTED ) &&
			!objectToHack->testStatus( OBJECT_STATUS_DISGUISED ) )
		{
			return FALSE;
		}

		//Also check if the object is a container containing stealth units tricking
		//the player into thinking it isn't actually an enemy.
		if (appearsToContainFriendlies(obj, objectToHack))
			return FALSE;

		return TRUE;
	}
	return FALSE;
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ?canDisableBuildingViaHacking@ActionManager@@QAE_NPBVObject@@0W4CommandSourceType@@@Z present-unmatched
Bool ActionManager::canDisableBuildingViaHacking( const Object *obj, const Object *objectToHack, CommandSourceType commandSource )
{
	// sanity
	if( obj == NULL || objectToHack == NULL )
		return FALSE;

	//Make sure our object has the capability of performing this special ability.
	if( !obj->hasSpecialPower( SPECIAL_HACKER_DISABLE_BUILDING ) )
	{
		return FALSE;
	}
	
	SpecialPowerModuleInterface *spInterface = obj->findSpecialPowerModuleInterface( SPECIAL_HACKER_DISABLE_BUILDING );
	if( !spInterface || spInterface->getPercentReady() < 1.0f )
	{
		//Special not ready or non-existent.
		return FALSE;
	}

	if( objectToHack->isEffectivelyDead() )
	{
		return FALSE;
	}

	// if the target is in the shroud, we can't do anything
	if (isObjectShroudedForAction(obj, objectToHack, commandSource))
		return FALSE;

	Relationship r = obj->getRelationship(objectToHack);

	// Make sure object is an enemy
	if( r != ENEMIES )
		return FALSE;

	//Make sure we are targeting a building!
	if( !objectToHack->isKindOf( KINDOF_STRUCTURE ) )
	{
		return FALSE;
	}

	//Make sure the building is considered hackable (temp: using capturable)
	// An exception is any TechFactionBuilding that is not explicitly immune to capture
	if( ( !objectToHack->isKindOf( KINDOF_CAPTURABLE ) || objectToHack->isKindOf( KINDOF_REBUILD_HOLE ) ) &&
		! (objectToHack->isKindOf(KINDOF_FS_TECHNOLOGY) && ! objectToHack->isKindOf(KINDOF_IMMUNE_TO_CAPTURE)) )
	{
		return FALSE;
	}

	
	if ( objectToHack->isKindOf( KINDOF_REBUILD_HOLE ) || objectToHack->testStatus( OBJECT_STATUS_UNDER_CONSTRUCTION ))
		return FALSE;


	//If the enemy unit is stealthed and not detected, then we can't attack it!
	if( objectToHack->testStatus( OBJECT_STATUS_STEALTHED ) && 
			!objectToHack->testStatus( OBJECT_STATUS_DETECTED ) &&
			!objectToHack->testStatus( OBJECT_STATUS_DISGUISED ) )
	{
		return FALSE;
	}

	//Also check if the object is a container containing stealth units tricking
	//the player into thinking it isn't actually an enemy.
	if (appearsToContainFriendlies(obj, objectToHack))
		return FALSE;

	return TRUE;
}

// ------------------------------------------------------------------------------------------------
// ?canBribeUnit@ActionManager@@QAE_NPBVObject@@0W4CommandSourceType@@@Z
Bool ActionManager::canBribeUnit( const Object *obj, const Object *objectToBribe, CommandSourceType commandSource )
{
	return FALSE;
}

// ------------------------------------------------------------------------------------------------
// ?canCutBuildingPower@ActionManager@@QAE_NPBVObject@@0W4CommandSourceType@@@Z present-unmatched
Bool ActionManager::canCutBuildingPower( const Object *obj, const Object *building, CommandSourceType commandSource )
{
	return FALSE;
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ?canSnipeVehicle@ActionManager@@QAE_NPBVObject@@0W4CommandSourceType@@@Z present-unmatched
Bool ActionManager::canSnipeVehicle( const Object *obj, const Object *objectToSnipe, CommandSourceType commandSource )
{
	//Sanity check
	if( obj == NULL || objectToSnipe == NULL )
	{
		return FALSE;
	}

	//Make sure it's alive.
	if( objectToSnipe->isEffectivelyDead() )
	{
		return FALSE;
	}

	// if the target is in the shroud, we can't do anything
	if (isObjectShroudedForAction(obj, objectToSnipe, commandSource))
		return FALSE;

	Relationship r = obj->getRelationship(objectToSnipe);

	if( r == ENEMIES )
	{
		//Make sure target is a vehicle.
		if( !objectToSnipe->isKindOf( KINDOF_VEHICLE ) )
		{
			return FALSE;
		}
		
		//Can't be a drone type.
		if( objectToSnipe->isKindOf( KINDOF_DRONE ) )
		{
			return FALSE;
		}

		//Make sure object is not flying
		if( objectToSnipe->isAirborneTarget() )
		{
			return FALSE;
		}

		//Make sure the vehicle is manned!
		if( objectToSnipe->isDisabledByType( DISABLED_UNMANNED ) )
		{
			return FALSE;
		}

		return TRUE;
	}
	
	return FALSE;
}




//-------------------------------------------------------------------------------------------------
inline Bool isPointOnMap( const Coord3D  *testPos ) 
{
	Region3D mapRegion;
	TheTerrainLogic->getExtent( &mapRegion );
	return mapRegion.isInRegionNoZ( testPos );

}


// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
__declspec(naked) Bool ActionManager::canDoSpecialPowerAtLocation( const Object *obj, const Coord3D *loc, CommandSourceType commandSource, const SpecialPowerTemplate *spTemplate, const Object *objectInWay, UnsignedInt commandOptions, Bool checkSourceRequirements )
{
	__asm {
	__emit 0x64;
	__emit 0xa1;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x6a;
	__emit 0xff;
	__emit 0x68;
	__emit 0x07;
	__emit 0x95;
	__emit 0xff;
	__emit 0x00;
	__emit 0x50;
	__emit 0x64;
	__emit 0x89;
	__emit 0x25;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x81;
	__emit 0xec;
	__emit 0x54;
	__emit 0x02;
	__emit 0x00;
	__emit 0x00;
	__emit 0x55;
	__emit 0x56;
	__emit 0x8b;
	__emit 0xb4;
	__emit 0x24;
	__emit 0x78;
	__emit 0x02;
	__emit 0x00;
	__emit 0x00;
	__emit 0x33;
	__emit 0xed;
	__emit 0x3b;
	__emit 0xf5;
	__emit 0x75;
	__emit 0x07;
	__emit 0x32;
	__emit 0xc0;
	__emit 0xe9;
	__emit 0xde;
	__emit 0x03;
	__emit 0x00;
	__emit 0x00;
	__emit 0x53;
	__emit 0x8a;
	__emit 0x9c;
	__emit 0x24;
	__emit 0x88;
	__emit 0x02;
	__emit 0x00;
	__emit 0x00;
	__emit 0x84;
	__emit 0xdb;
	__emit 0x57;
	__emit 0x8b;
	__emit 0xbc;
	__emit 0x24;
	__emit 0x74;
	__emit 0x02;
	__emit 0x00;
	__emit 0x00;
	__emit 0x74;
	__emit 0x2a;
	__emit 0x8b;
	__emit 0x46;
	__emit 0x04;
	__emit 0x3b;
	__emit 0xc5;
	__emit 0x74;
	__emit 0x0e;
	__emit 0x8b;
	__emit 0x48;
	__emit 0x04;
	__emit 0x3b;
	__emit 0xcd;
	__emit 0x74;
	__emit 0x09;
	__emit 0xe8;
	__emit 0xd9;
	__emit 0x22;
	__emit 0xf8;
	__emit 0xff;
	__emit 0xeb;
	__emit 0x02;
	__emit 0x8b;
	__emit 0xc6;
	__emit 0x8b;
	__emit 0x40;
	__emit 0x14;
	__emit 0x50;
	__emit 0x8b;
	__emit 0xcf;
	__emit 0xe8;
	__emit 0x3a;
	__emit 0x75;
	__emit 0xf4;
	__emit 0xff;
	__emit 0x84;
	__emit 0xc0;
	__emit 0x0f;
	__emit 0x84;
	__emit 0x9c;
	__emit 0x03;
	__emit 0x00;
	__emit 0x00;
	__emit 0x3b;
	__emit 0xfd;
	__emit 0x74;
	__emit 0x4f;
	__emit 0x8b;
	__emit 0x8f;
	__emit 0x04;
	__emit 0x02;
	__emit 0x00;
	__emit 0x00;
	__emit 0x3b;
	__emit 0xcd;
	__emit 0x74;
	__emit 0x45;
	__emit 0xe8;
	__emit 0x7c;
	__emit 0xaa;
	__emit 0xf3;
	__emit 0xff;
	__emit 0x84;
	__emit 0xc0;
	__emit 0x74;
	__emit 0x3c;
	__emit 0x8b;
	__emit 0x47;
	__emit 0x38;
	__emit 0xd9;
	__emit 0x47;
	__emit 0x40;
	__emit 0xd8;
	__emit 0x05;
	__emit 0xbc;
	__emit 0x3b;
	__emit 0x08;
	__emit 0x01;
	__emit 0x8b;
	__emit 0x4f;
	__emit 0x3c;
	__emit 0x89;
	__emit 0x44;
	__emit 0x24;
	__emit 0x1c;
	__emit 0xa1;
	__emit 0x14;
	__emit 0xf2;
	__emit 0x2e;
	__emit 0x01;
	__emit 0x3b;
	__emit 0xc5;
	__emit 0xd9;
	__emit 0x5c;
	__emit 0x24;
	__emit 0x24;
	__emit 0x89;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x20;
	__emit 0x74;
	__emit 0x18;
	__emit 0x8b;
	__emit 0x40;
	__emit 0x0c;
	__emit 0x8d;
	__emit 0x54;
	__emit 0x24;
	__emit 0x1c;
	__emit 0x52;
	__emit 0x8b;
	__emit 0xc8;
	__emit 0xe8;
	__emit 0x72;
	__emit 0x3f;
	__emit 0xf5;
	__emit 0xff;
	__emit 0x83;
	__emit 0xf8;
	__emit 0x11;
	__emit 0x0f;
	__emit 0x8d;
	__emit 0x49;
	__emit 0x03;
	__emit 0x00;
	__emit 0x00;
	__emit 0xf6;
	__emit 0x05;
	__emit 0x1c;
	__emit 0xd7;
	__emit 0x2e;
	__emit 0x01;
	__emit 0x01;
	__emit 0x75;
	__emit 0x2e;
	__emit 0x83;
	__emit 0x0d;
	__emit 0x1c;
	__emit 0xd7;
	__emit 0x2e;
	__emit 0x01;
	__emit 0x01;
	__emit 0x8b;
	__emit 0x0d;
	__emit 0x00;
	__emit 0xd6;
	__emit 0x2e;
	__emit 0x01;
	__emit 0x68;
	__emit 0x50;
	__emit 0x3c;
	__emit 0x08;
	__emit 0x01;
	__emit 0x89;
	__emit 0xac;
	__emit 0x24;
	__emit 0x70;
	__emit 0x02;
	__emit 0x00;
	__emit 0x00;
	__emit 0xe8;
	__emit 0xbe;
	__emit 0x43;
	__emit 0xf7;
	__emit 0xff;
	__emit 0xa3;
	__emit 0x18;
	__emit 0xd7;
	__emit 0x2e;
	__emit 0x01;
	__emit 0xc7;
	__emit 0x84;
	__emit 0x24;
	__emit 0x6c;
	__emit 0x02;
	__emit 0x00;
	__emit 0x00;
	__emit 0xff;
	__emit 0xff;
	__emit 0xff;
	__emit 0xff;
	__emit 0x56;
	__emit 0x8b;
	__emit 0xcf;
	__emit 0xe8;
	__emit 0x8e;
	__emit 0x97;
	__emit 0xf7;
	__emit 0xff;
	__emit 0x8b;
	__emit 0xf8;
	__emit 0x3b;
	__emit 0xfd;
	__emit 0x0f;
	__emit 0x84;
	__emit 0x00;
	__emit 0x03;
	__emit 0x00;
	__emit 0x00;
	__emit 0x84;
	__emit 0xdb;
	__emit 0x74;
	__emit 0x28;
	__emit 0x8b;
	__emit 0x07;
	__emit 0x8b;
	__emit 0xcf;
	__emit 0xff;
	__emit 0x50;
	__emit 0x08;
	__emit 0xd8;
	__emit 0x1d;
	__emit 0x34;
	__emit 0x53;
	__emit 0x07;
	__emit 0x01;
	__emit 0xdf;
	__emit 0xe0;
	__emit 0xf6;
	__emit 0xc4;
	__emit 0x05;
	__emit 0x0f;
	__emit 0x8b;
	__emit 0xe4;
	__emit 0x02;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x17;
	__emit 0x55;
	__emit 0x8b;
	__emit 0xcf;
	__emit 0xff;
	__emit 0x52;
	__emit 0x58;
	__emit 0x84;
	__emit 0xc0;
	__emit 0x0f;
	__emit 0x84;
	__emit 0xd4;
	__emit 0x02;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x46;
	__emit 0x04;
	__emit 0x3b;
	__emit 0xc5;
	__emit 0x74;
	__emit 0x0e;
	__emit 0x8b;
	__emit 0x48;
	__emit 0x04;
	__emit 0x3b;
	__emit 0xcd;
	__emit 0x74;
	__emit 0x09;
	__emit 0xe8;
	__emit 0xe7;
	__emit 0x21;
	__emit 0xf8;
	__emit 0xff;
	__emit 0xeb;
	__emit 0x02;
	__emit 0x8b;
	__emit 0xc6;
	__emit 0x8b;
	__emit 0x40;
	__emit 0x14;
	__emit 0x8b;
	__emit 0xb4;
	__emit 0x24;
	__emit 0x78;
	__emit 0x02;
	__emit 0x00;
	__emit 0x00;
	__emit 0x83;
	__emit 0xe8;
	__emit 0x02;
	__emit 0x83;
	__emit 0xf8;
	__emit 0x70;
	__emit 0x77;
	__emit 0x44;
	__emit 0x0f;
	__emit 0xb6;
	__emit 0x80;
	__emit 0x50;
	__emit 0x75;
	__emit 0x4c;
	__emit 0x00;
	__emit 0xff;
	__emit 0x24;
	__emit 0x85;
	__emit 0x48;
	__emit 0x75;
	__emit 0x4c;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x46;
	__emit 0x04;
	__emit 0x8b;
	__emit 0x0d;
	__emit 0xcc;
	__emit 0xf4;
	__emit 0x2e;
	__emit 0x01;
	__emit 0x8b;
	__emit 0x11;
	__emit 0x55;
	__emit 0x55;
	__emit 0x50;
	__emit 0x8b;
	__emit 0x06;
	__emit 0x50;
	__emit 0xff;
	__emit 0x52;
	__emit 0x4c;
	__emit 0x84;
	__emit 0xc0;
	__emit 0x0f;
	__emit 0x85;
	__emit 0x81;
	__emit 0x02;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x46;
	__emit 0x04;
	__emit 0x8b;
	__emit 0x0d;
	__emit 0xcc;
	__emit 0xf4;
	__emit 0x2e;
	__emit 0x01;
	__emit 0x8b;
	__emit 0x11;
	__emit 0x50;
	__emit 0x8b;
	__emit 0x06;
	__emit 0x50;
	__emit 0xff;
	__emit 0x52;
	__emit 0x50;
	__emit 0x84;
	__emit 0xc0;
	__emit 0x0f;
	__emit 0x85;
	__emit 0x67;
	__emit 0x02;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x8c;
	__emit 0x24;
	__emit 0x80;
	__emit 0x02;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x41;
	__emit 0x04;
	__emit 0x3b;
	__emit 0xc5;
	__emit 0x74;
	__emit 0x0e;
	__emit 0x8b;
	__emit 0x48;
	__emit 0x04;
	__emit 0x3b;
	__emit 0xcd;
	__emit 0x74;
	__emit 0x09;
	__emit 0xe8;
	__emit 0x73;
	__emit 0x21;
	__emit 0xf8;
	__emit 0xff;
	__emit 0xeb;
	__emit 0x02;
	__emit 0x8b;
	__emit 0xc1;
	__emit 0x8b;
	__emit 0x40;
	__emit 0x14;
	__emit 0x83;
	__emit 0xe8;
	__emit 0x42;
	__emit 0x83;
	__emit 0xf8;
	__emit 0x30;
	__emit 0x0f;
	__emit 0x87;
	__emit 0xa5;
	__emit 0x03;
	__emit 0x00;
	__emit 0x00;
	__emit 0x0f;
	__emit 0xb6;
	__emit 0x88;
	__emit 0xd4;
	__emit 0x75;
	__emit 0x4c;
	__emit 0x00;
	__emit 0xff;
	__emit 0x24;
	__emit 0x8d;
	__emit 0xc4;
	__emit 0x75;
	__emit 0x4c;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x8c;
	__emit 0x24;
	__emit 0x80;
	__emit 0x02;
	__emit 0x00;
	__emit 0x00;
	__emit 0xe8;
	__emit 0xe6;
	__emit 0xbb;
	__emit 0xf4;
	__emit 0xff;
	__emit 0xd9;
	__emit 0x5c;
	__emit 0x24;
	__emit 0x14;
	__emit 0x89;
	__emit 0x6c;
	__emit 0x24;
	__emit 0x38;
	__emit 0xc7;
	__emit 0x44;
	__emit 0x24;
	__emit 0x34;
	__emit 0x80;
	__emit 0x3b;
	__emit 0x08;
	__emit 0x01;
	__emit 0x68;
	__emit 0x87;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x6a;
	__emit 0x2f;
	__emit 0x6a;
	__emit 0x1e;
	__emit 0x6a;
	__emit 0x58;
	__emit 0x55;
	__emit 0x8d;
	__emit 0x8c;
	__emit 0x24;
	__emit 0x18;
	__emit 0x01;
	__emit 0x00;
	__emit 0x00;
	__emit 0xc7;
	__emit 0x84;
	__emit 0x24;
	__emit 0x80;
	__emit 0x02;
	__emit 0x00;
	__emit 0x00;
	__emit 0x01;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0xe8;
	__emit 0x0f;
	__emit 0xa7;
	__emit 0xf3;
	__emit 0xff;
	__emit 0x50;
	__emit 0x68;
	__emit 0xb8;
	__emit 0xd8;
	__emit 0x2e;
	__emit 0x01;
	__emit 0x8d;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x5c;
	__emit 0xe8;
	__emit 0xa0;
	__emit 0x17;
	__emit 0xf7;
	__emit 0xff;
	__emit 0x55;
	__emit 0x8d;
	__emit 0x54;
	__emit 0x24;
	__emit 0x58;
	__emit 0x52;
	__emit 0x8d;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x3c;
	__emit 0xc6;
	__emit 0x84;
	__emit 0x24;
	__emit 0x74;
	__emit 0x02;
	__emit 0x00;
	__emit 0x00;
	__emit 0x02;
	__emit 0xe8;
	__emit 0x6c;
	__emit 0xbf;
	__emit 0x92;
	__emit 0x00;
	__emit 0x50;
	__emit 0x8b;
	__emit 0x44;
	__emit 0x24;
	__emit 0x1c;
	__emit 0x6a;
	__emit 0x01;
	__emit 0x50;
	__emit 0x56;
	__emit 0x8d;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x24;
	__emit 0x51;
	__emit 0x8b;
	__emit 0x0d;
	__emit 0xb8;
	__emit 0xd5;
	__emit 0x2e;
	__emit 0x01;
	__emit 0xe8;
	__emit 0xd3;
	__emit 0xbd;
	__emit 0x92;
	__emit 0x00;
	__emit 0xc6;
	__emit 0x84;
	__emit 0x24;
	__emit 0x6c;
	__emit 0x02;
	__emit 0x00;
	__emit 0x00;
	__emit 0x03;
	__emit 0x8b;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x10;
	__emit 0x8b;
	__emit 0x41;
	__emit 0x04;
	__emit 0x8b;
	__emit 0x51;
	__emit 0x0c;
	__emit 0x3b;
	__emit 0xd0;
	__emit 0x74;
	__emit 0x67;
	__emit 0x8b;
	__emit 0xc2;
	__emit 0x8b;
	__emit 0x38;
	__emit 0x83;
	__emit 0xc0;
	__emit 0x08;
	__emit 0x3b;
	__emit 0xfd;
	__emit 0x89;
	__emit 0x41;
	__emit 0x0c;
	__emit 0x74;
	__emit 0x59;
	__emit 0x6a;
	__emit 0x07;
	__emit 0x6a;
	__emit 0x02;
	__emit 0x55;
	__emit 0x8d;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x48;
	__emit 0xe8;
	__emit 0xce;
	__emit 0xad;
	__emit 0xf3;
	__emit 0xff;
	__emit 0x8d;
	__emit 0x54;
	__emit 0x24;
	__emit 0x3c;
	__emit 0x52;
	__emit 0x8b;
	__emit 0xcf;
	__emit 0xe8;
	__emit 0x3f;
	__emit 0xb9;
	__emit 0xf7;
	__emit 0xff;
	__emit 0x84;
	__emit 0xc0;
	__emit 0x74;
	__emit 0x11;
	__emit 0x6a;
	__emit 0x77;
	__emit 0x8b;
	__emit 0xcf;
	__emit 0xe8;
	__emit 0x47;
	__emit 0xb9;
	__emit 0xf6;
	__emit 0xff;
	__emit 0x84;
	__emit 0xc0;
	__emit 0x0f;
	__emit 0x84;
	__emit 0x4a;
	__emit 0x01;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x7f;
	__emit 0x04;
	__emit 0x3b;
	__emit 0xfd;
	__emit 0x75;
	__emit 0x04;
	__emit 0x33;
	__emit 0xc0;
	__emit 0xeb;
	__emit 0x10;
	__emit 0x8b;
	__emit 0x4f;
	__emit 0x04;
	__emit 0x3b;
	__emit 0xcd;
	__emit 0x74;
	__emit 0x07;
	__emit 0xe8;
	__emit 0xc4;
	__emit 0xb6;
	__emit 0xf3;
	__emit 0xff;
	__emit 0xeb;
	__emit 0x02;
	__emit 0x8b;
	__emit 0xc7;
	__emit 0x8a;
	__emit 0x88;
	__emit 0xb0;
	__emit 0x04;
	__emit 0x00;
	__emit 0x00;
	__emit 0x84;
	__emit 0xc9;
	__emit 0x74;
	__emit 0x90;
	__emit 0xe9;
	__emit 0x20;
	__emit 0x01;
	__emit 0x00;
	__emit 0x00;
	__emit 0x68;
	__emit 0xb8;
	__emit 0xd8;
	__emit 0x2e;
	__emit 0x01;
	__emit 0x6a;
	__emit 0x77;
	__emit 0x55;
	__emit 0x8d;
	__emit 0x8c;
	__emit 0x24;
	__emit 0xc8;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0xe8;
	__emit 0xf1;
	__emit 0x20;
	__emit 0xf4;
	__emit 0xff;
	__emit 0x50;
	__emit 0x8d;
	__emit 0x8c;
	__emit 0x24;
	__emit 0x54;
	__emit 0x01;
	__emit 0x00;
	__emit 0x00;
	__emit 0xe8;
	__emit 0xd2;
	__emit 0x16;
	__emit 0xf7;
	__emit 0xff;
	__emit 0x8b;
	__emit 0x0d;
	__emit 0xb8;
	__emit 0xd5;
	__emit 0x2e;
	__emit 0x01;
	__emit 0x55;
	__emit 0x50;
	__emit 0x55;
	__emit 0x68;
	__emit 0x00;
	__emit 0xc0;
	__emit 0x0f;
	__emit 0x44;
	__emit 0x56;
	__emit 0x8d;
	__emit 0x44;
	__emit 0x24;
	__emit 0x2c;
	__emit 0xb3;
	__emit 0x04;
	__emit 0x50;
	__emit 0x88;
	__emit 0x9c;
	__emit 0x24;
	__emit 0x84;
	__emit 0x02;
	__emit 0x00;
	__emit 0x00;
	__emit 0xe8;
	__emit 0x13;
	__emit 0xbd;
	__emit 0x92;
	__emit 0x00;
	__emit 0x50;
	__emit 0x8d;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x14;
	__emit 0xc6;
	__emit 0x84;
	__emit 0x24;
	__emit 0x70;
	__emit 0x02;
	__emit 0x00;
	__emit 0x00;
	__emit 0x05;
	__emit 0xe8;
	__emit 0x0d;
	__emit 0xa4;
	__emit 0xf5;
	__emit 0xff;
	__emit 0x8d;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x18;
	__emit 0x88;
	__emit 0x9c;
	__emit 0x24;
	__emit 0x6c;
	__emit 0x02;
	__emit 0x00;
	__emit 0x00;
	__emit 0xe8;
	__emit 0x02;
	__emit 0x58;
	__emit 0xf6;
	__emit 0xff;
	__emit 0xc6;
	__emit 0x84;
	__emit 0x24;
	__emit 0x6c;
	__emit 0x02;
	__emit 0x00;
	__emit 0x00;
	__emit 0x03;
	__emit 0xc7;
	__emit 0x84;
	__emit 0x24;
	__emit 0x4c;
	__emit 0x01;
	__emit 0x00;
	__emit 0x00;
	__emit 0x5c;
	__emit 0x3b;
	__emit 0x08;
	__emit 0x01;
	__emit 0x8b;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x10;
	__emit 0x8b;
	__emit 0x41;
	__emit 0x04;
	__emit 0x8b;
	__emit 0x51;
	__emit 0x0c;
	__emit 0x3b;
	__emit 0xd0;
	__emit 0x0f;
	__emit 0x84;
	__emit 0xc4;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0xc2;
	__emit 0x8b;
	__emit 0x38;
	__emit 0x83;
	__emit 0xc0;
	__emit 0x08;
	__emit 0x3b;
	__emit 0xfd;
	__emit 0x89;
	__emit 0x41;
	__emit 0x0c;
	__emit 0x0f;
	__emit 0x84;
	__emit 0xb2;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x0d;
	__emit 0x18;
	__emit 0xd7;
	__emit 0x2e;
	__emit 0x01;
	__emit 0x51;
	__emit 0x8b;
	__emit 0xcf;
	__emit 0xe8;
	__emit 0x6f;
	__emit 0x41;
	__emit 0xf6;
	__emit 0xff;
	__emit 0x3b;
	__emit 0xc5;
	__emit 0x74;
	__emit 0xca;
	__emit 0x39;
	__emit 0xa8;
	__emit 0x9c;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x74;
	__emit 0xc2;
	__emit 0x8b;
	__emit 0xc8;
	__emit 0xe8;
	__emit 0xfa;
	__emit 0x81;
	__emit 0xf4;
	__emit 0xff;
	__emit 0xd9;
	__emit 0x5c;
	__emit 0x24;
	__emit 0x14;
	__emit 0xd9;
	__emit 0x47;
	__emit 0x38;
	__emit 0x8b;
	__emit 0x46;
	__emit 0x04;
	__emit 0xd9;
	__emit 0x47;
	__emit 0x3c;
	__emit 0x8b;
	__emit 0x4e;
	__emit 0x08;
	__emit 0xd9;
	__emit 0x06;
	__emit 0x8b;
	__emit 0x57;
	__emit 0x40;
	__emit 0xd8;
	__emit 0xe2;
	__emit 0x89;
	__emit 0x44;
	__emit 0x24;
	__emit 0x20;
	__emit 0x89;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x24;
	__emit 0x89;
	__emit 0x54;
	__emit 0x24;
	__emit 0x44;
	__emit 0xd9;
	__emit 0x5c;
	__emit 0x24;
	__emit 0x1c;
	__emit 0x8d;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x1c;
	__emit 0xd9;
	__emit 0x44;
	__emit 0x24;
	__emit 0x20;
	__emit 0xd8;
	__emit 0xe1;
	__emit 0xd9;
	__emit 0x5c;
	__emit 0x24;
	__emit 0x20;
	__emit 0xdd;
	__emit 0xd8;
	__emit 0xdd;
	__emit 0xd8;
	__emit 0xd9;
	__emit 0x44;
	__emit 0x24;
	__emit 0x24;
	__emit 0xd8;
	__emit 0x64;
	__emit 0x24;
	__emit 0x44;
	__emit 0xd9;
	__emit 0x5c;
	__emit 0x24;
	__emit 0x24;
	__emit 0xe8;
	__emit 0xfe;
	__emit 0x90;
	__emit 0xf6;
	__emit 0xff;
	__emit 0xd9;
	__emit 0x44;
	__emit 0x24;
	__emit 0x14;
	__emit 0xd8;
	__emit 0x05;
	__emit 0x4c;
	__emit 0x3c;
	__emit 0x08;
	__emit 0x01;
	__emit 0xd8;
	__emit 0xd9;
	__emit 0xdf;
	__emit 0xe0;
	__emit 0xdd;
	__emit 0xd8;
	__emit 0xf6;
	__emit 0xc4;
	__emit 0x41;
	__emit 0x0f;
	__emit 0x85;
	__emit 0x58;
	__emit 0xff;
	__emit 0xff;
	__emit 0xff;
	__emit 0xc6;
	__emit 0x84;
	__emit 0x24;
	__emit 0x6c;
	__emit 0x02;
	__emit 0x00;
	__emit 0x00;
	__emit 0x02;
	__emit 0x8d;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x10;
	__emit 0xe8;
	__emit 0x36;
	__emit 0x57;
	__emit 0xf6;
	__emit 0xff;
	__emit 0x32;
	__emit 0xc0;
	__emit 0x5f;
	__emit 0x5b;
	__emit 0x8b;
	__emit 0x8c;
	__emit 0x24;
	__emit 0x5c;
	__emit 0x02;
	__emit 0x00;
	__emit 0x00;
	__emit 0x5e;
	__emit 0x5d;
	__emit 0x64;
	__emit 0x89;
	__emit 0x0d;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x81;
	__emit 0xc4;
	__emit 0x60;
	__emit 0x02;
	__emit 0x00;
	__emit 0x00;
	__emit 0xc2;
	__emit 0x1c;
	__emit 0x00;
	__emit 0x8d;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x10;
	__emit 0xc6;
	__emit 0x84;
	__emit 0x24;
	__emit 0x6c;
	__emit 0x02;
	__emit 0x00;
	__emit 0x00;
	__emit 0x02;
	__emit 0xe8;
	__emit 0x08;
	__emit 0x57;
	__emit 0xf6;
	__emit 0xff;
	__emit 0xe9;
	__emit 0x2d;
	__emit 0x01;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x17;
	__emit 0x56;
	__emit 0x8b;
	__emit 0xcf;
	__emit 0xff;
	__emit 0x52;
	__emit 0x58;
	__emit 0x84;
	__emit 0xc0;
	__emit 0x74;
	__emit 0xc1;
	__emit 0x68;
	__emit 0xb8;
	__emit 0xd8;
	__emit 0x2e;
	__emit 0x01;
	__emit 0x6a;
	__emit 0x07;
	__emit 0x55;
	__emit 0x8d;
	__emit 0x8c;
	__emit 0x24;
	__emit 0x98;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0xe8;
	__emit 0x81;
	__emit 0x1f;
	__emit 0xf4;
	__emit 0xff;
	__emit 0x50;
	__emit 0x8d;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x5c;
	__emit 0xe8;
	__emit 0x65;
	__emit 0x15;
	__emit 0xf7;
	__emit 0xff;
	__emit 0x8b;
	__emit 0x0d;
	__emit 0xb8;
	__emit 0xd5;
	__emit 0x2e;
	__emit 0x01;
	__emit 0x8d;
	__emit 0x44;
	__emit 0x24;
	__emit 0x54;
	__emit 0x50;
	__emit 0x55;
	__emit 0x68;
	__emit 0x00;
	__emit 0x00;
	__emit 0x80;
	__emit 0x3f;
	__emit 0x56;
	__emit 0xc7;
	__emit 0x84;
	__emit 0x24;
	__emit 0x7c;
	__emit 0x02;
	__emit 0x00;
	__emit 0x00;
	__emit 0x06;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0xe8;
	__emit 0xe6;
	__emit 0xb8;
	__emit 0x92;
	__emit 0x00;
	__emit 0x85;
	__emit 0xc0;
	__emit 0x0f;
	__emit 0x85;
	__emit 0x79;
	__emit 0xff;
	__emit 0xff;
	__emit 0xff;
	__emit 0x8b;
	__emit 0x0d;
	__emit 0xcc;
	__emit 0xf4;
	__emit 0x2e;
	__emit 0x01;
	__emit 0x56;
	__emit 0x55;
	__emit 0xe8;
	__emit 0xa6;
	__emit 0x58;
	__emit 0xf5;
	__emit 0xff;
	__emit 0x83;
	__emit 0xf8;
	__emit 0x01;
	__emit 0x0f;
	__emit 0x85;
	__emit 0x63;
	__emit 0xff;
	__emit 0xff;
	__emit 0xff;
	__emit 0x8b;
	__emit 0xbc;
	__emit 0x24;
	__emit 0x74;
	__emit 0x02;
	__emit 0x00;
	__emit 0x00;
	__emit 0xe9;
	__emit 0x91;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x68;
	__emit 0xb8;
	__emit 0xd8;
	__emit 0x2e;
	__emit 0x01;
	__emit 0x6a;
	__emit 0x07;
	__emit 0x55;
	__emit 0x8d;
	__emit 0x8c;
	__emit 0x24;
	__emit 0xe0;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0xe8;
	__emit 0x17;
	__emit 0x1f;
	__emit 0xf4;
	__emit 0xff;
	__emit 0x50;
	__emit 0x8d;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x5c;
	__emit 0xe8;
	__emit 0xfb;
	__emit 0x14;
	__emit 0xf7;
	__emit 0xff;
	__emit 0x8d;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x54;
	__emit 0x51;
	__emit 0x8b;
	__emit 0x0d;
	__emit 0xb8;
	__emit 0xd5;
	__emit 0x2e;
	__emit 0x01;
	__emit 0x55;
	__emit 0x68;
	__emit 0x00;
	__emit 0x00;
	__emit 0x80;
	__emit 0x3f;
	__emit 0x56;
	__emit 0xc7;
	__emit 0x84;
	__emit 0x24;
	__emit 0x7c;
	__emit 0x02;
	__emit 0x00;
	__emit 0x00;
	__emit 0x07;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0xe8;
	__emit 0x7c;
	__emit 0xb8;
	__emit 0x92;
	__emit 0x00;
	__emit 0x85;
	__emit 0xc0;
	__emit 0x0f;
	__emit 0x85;
	__emit 0x0f;
	__emit 0xff;
	__emit 0xff;
	__emit 0xff;
	__emit 0x8b;
	__emit 0xbc;
	__emit 0x24;
	__emit 0x74;
	__emit 0x02;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x15;
	__emit 0x14;
	__emit 0xf2;
	__emit 0x2e;
	__emit 0x01;
	__emit 0x8b;
	__emit 0x4a;
	__emit 0x0c;
	__emit 0x55;
	__emit 0x56;
	__emit 0x8d;
	__emit 0x47;
	__emit 0x38;
	__emit 0x50;
	__emit 0x57;
	__emit 0xe8;
	__emit 0xdf;
	__emit 0x34;
	__emit 0xf8;
	__emit 0xff;
	__emit 0x84;
	__emit 0xc0;
	__emit 0x0f;
	__emit 0x84;
	__emit 0xeb;
	__emit 0xfe;
	__emit 0xff;
	__emit 0xff;
	__emit 0x8b;
	__emit 0x0d;
	__emit 0xcc;
	__emit 0xf4;
	__emit 0x2e;
	__emit 0x01;
	__emit 0x56;
	__emit 0x55;
	__emit 0xe8;
	__emit 0x18;
	__emit 0x58;
	__emit 0xf5;
	__emit 0xff;
	__emit 0x8b;
	__emit 0x0d;
	__emit 0x14;
	__emit 0xf2;
	__emit 0x2e;
	__emit 0x01;
	__emit 0x8b;
	__emit 0x49;
	__emit 0x0c;
	__emit 0x50;
	__emit 0x56;
	__emit 0xe8;
	__emit 0x5b;
	__emit 0x72;
	__emit 0xf6;
	__emit 0xff;
	__emit 0x84;
	__emit 0xc0;
	__emit 0x0f;
	__emit 0x85;
	__emit 0xc6;
	__emit 0xfe;
	__emit 0xff;
	__emit 0xff;
	__emit 0x8b;
	__emit 0xcf;
	__emit 0xe8;
	__emit 0xb0;
	__emit 0xe9;
	__emit 0xf7;
	__emit 0xff;
	__emit 0x3b;
	__emit 0xc5;
	__emit 0x74;
	__emit 0x1b;
	__emit 0x8b;
	__emit 0xc8;
	__emit 0x57;
	__emit 0xe8;
	__emit 0x23;
	__emit 0xc2;
	__emit 0xf5;
	__emit 0xff;
	__emit 0xd9;
	__emit 0x05;
	__emit 0x50;
	__emit 0x53;
	__emit 0x07;
	__emit 0x01;
	__emit 0xda;
	__emit 0xe9;
	__emit 0xdf;
	__emit 0xe0;
	__emit 0xf6;
	__emit 0xc4;
	__emit 0x44;
	__emit 0x0f;
	__emit 0x8b;
	__emit 0xa0;
	__emit 0xfe;
	__emit 0xff;
	__emit 0xff;
	__emit 0xc7;
	__emit 0x84;
	__emit 0x24;
	__emit 0x6c;
	__emit 0x02;
	__emit 0x00;
	__emit 0x00;
	__emit 0xff;
	__emit 0xff;
	__emit 0xff;
	__emit 0xff;
	__emit 0x8b;
	__emit 0x8c;
	__emit 0x24;
	__emit 0x80;
	__emit 0x02;
	__emit 0x00;
	__emit 0x00;
	__emit 0xe8;
	__emit 0x8c;
	__emit 0x9b;
	__emit 0xf7;
	__emit 0xff;
	__emit 0x48;
	__emit 0x83;
	__emit 0xf8;
	__emit 0x72;
	__emit 0x0f;
	__emit 0x87;
	__emit 0x7f;
	__emit 0xfe;
	__emit 0xff;
	__emit 0xff;
	__emit 0x0f;
	__emit 0xb6;
	__emit 0x90;
	__emit 0x34;
	__emit 0x76;
	__emit 0x4c;
	__emit 0x00;
	__emit 0xff;
	__emit 0x24;
	__emit 0x95;
	__emit 0x08;
	__emit 0x76;
	__emit 0x4c;
	__emit 0x00;
	__emit 0x68;
	__emit 0xb8;
	__emit 0xd8;
	__emit 0x2e;
	__emit 0x01;
	__emit 0x68;
	__emit 0xa5;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x55;
	__emit 0x8d;
	__emit 0x8c;
	__emit 0x24;
	__emit 0x40;
	__emit 0x01;
	__emit 0x00;
	__emit 0x00;
	__emit 0xe8;
	__emit 0x2e;
	__emit 0x1e;
	__emit 0xf4;
	__emit 0xff;
	__emit 0x50;
	__emit 0x8d;
	__emit 0x8c;
	__emit 0x24;
	__emit 0xfc;
	__emit 0x01;
	__emit 0x00;
	__emit 0x00;
	__emit 0xe8;
	__emit 0x0f;
	__emit 0x14;
	__emit 0xf7;
	__emit 0xff;
	__emit 0xc7;
	__emit 0x84;
	__emit 0x24;
	__emit 0x6c;
	__emit 0x02;
	__emit 0x00;
	__emit 0x00;
	__emit 0x08;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x89;
	__emit 0x6c;
	__emit 0x24;
	__emit 0x38;
	__emit 0xc7;
	__emit 0x44;
	__emit 0x24;
	__emit 0x34;
	__emit 0x80;
	__emit 0x3b;
	__emit 0x08;
	__emit 0x01;
	__emit 0x50;
	__emit 0x8d;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x38;
	__emit 0xc6;
	__emit 0x84;
	__emit 0x24;
	__emit 0x70;
	__emit 0x02;
	__emit 0x00;
	__emit 0x00;
	__emit 0x09;
	__emit 0xe8;
	__emit 0xc9;
	__emit 0xbb;
	__emit 0x92;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x0d;
	__emit 0xb8;
	__emit 0xd5;
	__emit 0x2e;
	__emit 0x01;
	__emit 0x50;
	__emit 0x55;
	__emit 0x68;
	__emit 0x00;
	__emit 0x00;
	__emit 0x48;
	__emit 0x43;
	__emit 0x56;
	__emit 0xe8;
	__emit 0x76;
	__emit 0xb7;
	__emit 0x92;
	__emit 0x00;
	__emit 0x3b;
	__emit 0xc5;
	__emit 0xb9;
	__emit 0x5c;
	__emit 0x3b;
	__emit 0x08;
	__emit 0x01;
	__emit 0x89;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x34;
	__emit 0xc7;
	__emit 0x84;
	__emit 0x24;
	__emit 0x6c;
	__emit 0x02;
	__emit 0x00;
	__emit 0x00;
	__emit 0xff;
	__emit 0xff;
	__emit 0xff;
	__emit 0xff;
	__emit 0x89;
	__emit 0x8c;
	__emit 0x24;
	__emit 0xf4;
	__emit 0x01;
	__emit 0x00;
	__emit 0x00;
	__emit 0x0f;
	__emit 0x84;
	__emit 0xee;
	__emit 0xfd;
	__emit 0xff;
	__emit 0xff;
	__emit 0x8b;
	__emit 0x8c;
	__emit 0x24;
	__emit 0x74;
	__emit 0x02;
	__emit 0x00;
	__emit 0x00;
	__emit 0xe8;
	__emit 0xcb;
	__emit 0x98;
	__emit 0xf5;
	__emit 0xff;
	__emit 0x8b;
	__emit 0x40;
	__emit 0x24;
	__emit 0x8b;
	__emit 0x0d;
	__emit 0xbc;
	__emit 0xd5;
	__emit 0x2e;
	__emit 0x01;
	__emit 0x56;
	__emit 0x50;
	__emit 0xe8;
	__emit 0xc7;
	__emit 0x04;
	__emit 0x83;
	__emit 0x00;
	__emit 0xf7;
	__emit 0xd8;
	__emit 0x1b;
	__emit 0xc0;
	__emit 0x40;
	__emit 0xe9;
	__emit 0xca;
	__emit 0xfd;
	__emit 0xff;
	__emit 0xff;
	__emit 0xd9;
	__emit 0x06;
	__emit 0x8b;
	__emit 0x46;
	__emit 0x04;
	__emit 0xd9;
	__emit 0x05;
	__emit 0x4c;
	__emit 0x3c;
	__emit 0x08;
	__emit 0x01;
	__emit 0x89;
	__emit 0x44;
	__emit 0x24;
	__emit 0x20;
	__emit 0xd8;
	__emit 0xe9;
	__emit 0xe8;
	__emit 0xaf;
	__emit 0xfe;
	__emit 0x92;
	__emit 0x00;
	__emit 0xd8;
	__emit 0x05;
	__emit 0x4c;
	__emit 0x3c;
	__emit 0x08;
	__emit 0x01;
	__emit 0x8b;
	__emit 0xd8;
	__emit 0x89;
	__emit 0x5c;
	__emit 0x24;
	__emit 0x2c;
	__emit 0xe8;
	__emit 0x9e;
	__emit 0xfe;
	__emit 0x92;
	__emit 0x00;
	__emit 0xd9;
	__emit 0x44;
	__emit 0x24;
	__emit 0x20;
	__emit 0xd8;
	__emit 0x05;
	__emit 0x4c;
	__emit 0x3c;
	__emit 0x08;
	__emit 0x01;
	__emit 0x89;
	__emit 0x44;
	__emit 0x24;
	__emit 0x18;
	__emit 0xe8;
	__emit 0x8b;
	__emit 0xfe;
	__emit 0x92;
	__emit 0x00;
	__emit 0xd9;
	__emit 0x44;
	__emit 0x24;
	__emit 0x20;
	__emit 0xd8;
	__emit 0x25;
	__emit 0x4c;
	__emit 0x3c;
	__emit 0x08;
	__emit 0x01;
	__emit 0x8b;
	__emit 0xf8;
	__emit 0x89;
	__emit 0x7c;
	__emit 0x24;
	__emit 0x30;
	__emit 0xe8;
	__emit 0x76;
	__emit 0xfe;
	__emit 0x92;
	__emit 0x00;
	__emit 0x3b;
	__emit 0xc7;
	__emit 0x89;
	__emit 0x44;
	__emit 0x24;
	__emit 0x10;
	__emit 0x0f;
	__emit 0x8f;
	__emit 0xff;
	__emit 0x04;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0xff;
	__emit 0x3b;
	__emit 0x5c;
	__emit 0x24;
	__emit 0x18;
	__emit 0x89;
	__emit 0x5c;
	__emit 0x24;
	__emit 0x28;
	__emit 0x0f;
	__emit 0x8f;
	__emit 0x7c;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0xdb;
	__emit 0x44;
	__emit 0x24;
	__emit 0x10;
	__emit 0xd9;
	__emit 0x5c;
	__emit 0x24;
	__emit 0x14;
	__emit 0x8b;
	__emit 0x6c;
	__emit 0x24;
	__emit 0x14;
	__emit 0x8d;
	__emit 0x9b;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0xdb;
	__emit 0x44;
	__emit 0x24;
	__emit 0x28;
	__emit 0x8b;
	__emit 0x0d;
	__emit 0xcc;
	__emit 0xf4;
	__emit 0x2e;
	__emit 0x01;
	__emit 0x8b;
	__emit 0x11;
	__emit 0x55;
	__emit 0xd9;
	__emit 0x5c;
	__emit 0x24;
	__emit 0x18;
	__emit 0x8b;
	__emit 0x7c;
	__emit 0x24;
	__emit 0x18;
	__emit 0x57;
	__emit 0xff;
	__emit 0x52;
	__emit 0x54;
	__emit 0x84;
	__emit 0xc0;
	__emit 0x0f;
	__emit 0x85;
	__emit 0x2a;
	__emit 0xfd;
	__emit 0xff;
	__emit 0xff;
	__emit 0x8b;
	__emit 0x0d;
	__emit 0xcc;
	__emit 0xf4;
	__emit 0x2e;
	__emit 0x01;
	__emit 0x8b;
	__emit 0x01;
	__emit 0x55;
	__emit 0x57;
	__emit 0xff;
	__emit 0x50;
	__emit 0x50;
	__emit 0x84;
	__emit 0xc0;
	__emit 0x0f;
	__emit 0x85;
	__emit 0x15;
	__emit 0xfd;
	__emit 0xff;
	__emit 0xff;
	__emit 0x8b;
	__emit 0x0d;
	__emit 0xcc;
	__emit 0xf4;
	__emit 0x2e;
	__emit 0x01;
	__emit 0x8b;
	__emit 0x11;
	__emit 0x6a;
	__emit 0x00;
	__emit 0x6a;
	__emit 0x00;
	__emit 0x55;
	__emit 0x57;
	__emit 0xff;
	__emit 0x52;
	__emit 0x4c;
	__emit 0x84;
	__emit 0xc0;
	__emit 0x0f;
	__emit 0x85;
	__emit 0xfc;
	__emit 0xfc;
	__emit 0xff;
	__emit 0xff;
	__emit 0x8b;
	__emit 0x44;
	__emit 0x24;
	__emit 0x18;
	__emit 0x83;
	__emit 0xc3;
	__emit 0x0f;
	__emit 0x3b;
	__emit 0xd8;
	__emit 0x89;
	__emit 0x5c;
	__emit 0x24;
	__emit 0x28;
	__emit 0x7e;
	__emit 0xa2;
	__emit 0x8b;
	__emit 0x44;
	__emit 0x24;
	__emit 0x10;
	__emit 0x8b;
	__emit 0x7c;
	__emit 0x24;
	__emit 0x30;
	__emit 0x8b;
	__emit 0x5c;
	__emit 0x24;
	__emit 0x2c;
	__emit 0x83;
	__emit 0xc0;
	__emit 0x0f;
	__emit 0x3b;
	__emit 0xc7;
	__emit 0x89;
	__emit 0x44;
	__emit 0x24;
	__emit 0x10;
	__emit 0x0f;
	__emit 0x8e;
	__emit 0x67;
	__emit 0xff;
	__emit 0xff;
	__emit 0xff;
	__emit 0xe9;
	__emit 0x5f;
	__emit 0x04;
	__emit 0x00;
	__emit 0x00;
	__emit 0x68;
	__emit 0xb8;
	__emit 0xd8;
	__emit 0x2e;
	__emit 0x01;
	__emit 0x6a;
	__emit 0x77;
	__emit 0x55;
	__emit 0x8d;
	__emit 0x8c;
	__emit 0x24;
	__emit 0x28;
	__emit 0x01;
	__emit 0x00;
	__emit 0x00;
	__emit 0xe8;
	__emit 0x8d;
	__emit 0x1c;
	__emit 0xf4;
	__emit 0xff;
	__emit 0x50;
	__emit 0x8d;
	__emit 0x8c;
	__emit 0x24;
	__emit 0x8c;
	__emit 0x01;
	__emit 0x00;
	__emit 0x00;
	__emit 0xe8;
	__emit 0x6e;
	__emit 0x12;
	__emit 0xf7;
	__emit 0xff;
	__emit 0x8b;
	__emit 0x0d;
	__emit 0xb8;
	__emit 0xd5;
	__emit 0x2e;
	__emit 0x01;
	__emit 0x55;
	__emit 0x50;
	__emit 0x55;
	__emit 0x68;
	__emit 0x00;
	__emit 0xc0;
	__emit 0x28;
	__emit 0x44;
	__emit 0x56;
	__emit 0x8d;
	__emit 0x44;
	__emit 0x24;
	__emit 0x24;
	__emit 0x50;
	__emit 0xc7;
	__emit 0x84;
	__emit 0x24;
	__emit 0x84;
	__emit 0x02;
	__emit 0x00;
	__emit 0x00;
	__emit 0x0a;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0xe8;
	__emit 0xad;
	__emit 0xb8;
	__emit 0x92;
	__emit 0x00;
	__emit 0x8d;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x10;
	__emit 0xc6;
	__emit 0x84;
	__emit 0x24;
	__emit 0x6c;
	__emit 0x02;
	__emit 0x00;
	__emit 0x00;
	__emit 0x0c;
	__emit 0xc7;
	__emit 0x84;
	__emit 0x24;
	__emit 0x84;
	__emit 0x01;
	__emit 0x00;
	__emit 0x00;
	__emit 0x5c;
	__emit 0x3b;
	__emit 0x08;
	__emit 0x01;
	__emit 0xe8;
	__emit 0x19;
	__emit 0x04;
	__emit 0xf7;
	__emit 0xff;
	__emit 0x8b;
	__emit 0xf8;
	__emit 0x3b;
	__emit 0xfd;
	__emit 0x0f;
	__emit 0x84;
	__emit 0x9e;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8d;
	__emit 0xa4;
	__emit 0x24;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x0d;
	__emit 0x18;
	__emit 0xd7;
	__emit 0x2e;
	__emit 0x01;
	__emit 0x51;
	__emit 0x8b;
	__emit 0xcf;
	__emit 0xe8;
	__emit 0x35;
	__emit 0x3d;
	__emit 0xf6;
	__emit 0xff;
	__emit 0x3b;
	__emit 0xc5;
	__emit 0x74;
	__emit 0x72;
	__emit 0x39;
	__emit 0xa8;
	__emit 0x9c;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x74;
	__emit 0x6a;
	__emit 0x8b;
	__emit 0xc8;
	__emit 0xe8;
	__emit 0xc0;
	__emit 0x7d;
	__emit 0xf4;
	__emit 0xff;
	__emit 0xd9;
	__emit 0x5c;
	__emit 0x24;
	__emit 0x2c;
	__emit 0xd9;
	__emit 0x47;
	__emit 0x38;
	__emit 0x8b;
	__emit 0x46;
	__emit 0x04;
	__emit 0xd9;
	__emit 0x47;
	__emit 0x3c;
	__emit 0x8b;
	__emit 0x4e;
	__emit 0x08;
	__emit 0xd9;
	__emit 0x06;
	__emit 0x8b;
	__emit 0x57;
	__emit 0x40;
	__emit 0xd8;
	__emit 0xe2;
	__emit 0x89;
	__emit 0x44;
	__emit 0x24;
	__emit 0x20;
	__emit 0x89;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x24;
	__emit 0x89;
	__emit 0x54;
	__emit 0x24;
	__emit 0x44;
	__emit 0xd9;
	__emit 0x5c;
	__emit 0x24;
	__emit 0x1c;
	__emit 0x8d;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x1c;
	__emit 0xd9;
	__emit 0x44;
	__emit 0x24;
	__emit 0x20;
	__emit 0xd8;
	__emit 0xe1;
	__emit 0xd9;
	__emit 0x5c;
	__emit 0x24;
	__emit 0x20;
	__emit 0xdd;
	__emit 0xd8;
	__emit 0xdd;
	__emit 0xd8;
	__emit 0xd9;
	__emit 0x44;
	__emit 0x24;
	__emit 0x24;
	__emit 0xd8;
	__emit 0x64;
	__emit 0x24;
	__emit 0x44;
	__emit 0xd9;
	__emit 0x5c;
	__emit 0x24;
	__emit 0x24;
	__emit 0xe8;
	__emit 0xc4;
	__emit 0x8c;
	__emit 0xf6;
	__emit 0xff;
	__emit 0xd9;
	__emit 0x44;
	__emit 0x24;
	__emit 0x2c;
	__emit 0xd8;
	__emit 0x05;
	__emit 0x48;
	__emit 0x3c;
	__emit 0x08;
	__emit 0x01;
	__emit 0xd8;
	__emit 0xd9;
	__emit 0xdf;
	__emit 0xe0;
	__emit 0xdd;
	__emit 0xd8;
	__emit 0xf6;
	__emit 0xc4;
	__emit 0x41;
	__emit 0x0f;
	__emit 0x84;
	__emit 0xf3;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8d;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x10;
	__emit 0xe8;
	__emit 0x7b;
	__emit 0x03;
	__emit 0xf7;
	__emit 0xff;
	__emit 0x8b;
	__emit 0xf8;
	__emit 0x3b;
	__emit 0xfd;
	__emit 0x0f;
	__emit 0x85;
	__emit 0x69;
	__emit 0xff;
	__emit 0xff;
	__emit 0xff;
	__emit 0xd9;
	__emit 0x06;
	__emit 0x8b;
	__emit 0x56;
	__emit 0x04;
	__emit 0xd9;
	__emit 0x05;
	__emit 0x48;
	__emit 0x3c;
	__emit 0x08;
	__emit 0x01;
	__emit 0x89;
	__emit 0x54;
	__emit 0x24;
	__emit 0x20;
	__emit 0xd8;
	__emit 0xe9;
	__emit 0xe8;
	__emit 0xab;
	__emit 0xfc;
	__emit 0x92;
	__emit 0x00;
	__emit 0xd8;
	__emit 0x05;
	__emit 0x48;
	__emit 0x3c;
	__emit 0x08;
	__emit 0x01;
	__emit 0x89;
	__emit 0x44;
	__emit 0x24;
	__emit 0x28;
	__emit 0xe8;
	__emit 0x9c;
	__emit 0xfc;
	__emit 0x92;
	__emit 0x00;
	__emit 0xd9;
	__emit 0x44;
	__emit 0x24;
	__emit 0x20;
	__emit 0xd8;
	__emit 0x25;
	__emit 0x48;
	__emit 0x3c;
	__emit 0x08;
	__emit 0x01;
	__emit 0x8b;
	__emit 0xe8;
	__emit 0xe8;
	__emit 0x8b;
	__emit 0xfc;
	__emit 0x92;
	__emit 0x00;
	__emit 0xd9;
	__emit 0x44;
	__emit 0x24;
	__emit 0x20;
	__emit 0xd8;
	__emit 0x05;
	__emit 0x48;
	__emit 0x3c;
	__emit 0x08;
	__emit 0x01;
	__emit 0x8b;
	__emit 0xf8;
	__emit 0xe8;
	__emit 0x7a;
	__emit 0xfc;
	__emit 0x92;
	__emit 0x00;
	__emit 0x3b;
	__emit 0xf8;
	__emit 0x8b;
	__emit 0xdf;
	__emit 0x89;
	__emit 0x44;
	__emit 0x24;
	__emit 0x30;
	__emit 0x89;
	__emit 0x5c;
	__emit 0x24;
	__emit 0x14;
	__emit 0x7f;
	__emit 0x4e;
	__emit 0x8b;
	__emit 0x7c;
	__emit 0x24;
	__emit 0x28;
	__emit 0x3b;
	__emit 0xfd;
	__emit 0x89;
	__emit 0x7c;
	__emit 0x24;
	__emit 0x18;
	__emit 0x7f;
	__emit 0x33;
	__emit 0xdb;
	__emit 0x44;
	__emit 0x24;
	__emit 0x14;
	__emit 0xd9;
	__emit 0x5c;
	__emit 0x24;
	__emit 0x2c;
	__emit 0x8b;
	__emit 0x54;
	__emit 0x24;
	__emit 0x2c;
	__emit 0xdb;
	__emit 0x44;
	__emit 0x24;
	__emit 0x18;
	__emit 0x8b;
	__emit 0x0d;
	__emit 0xcc;
	__emit 0xf4;
	__emit 0x2e;
	__emit 0x01;
	__emit 0x8b;
	__emit 0x01;
	__emit 0x52;
	__emit 0x51;
	__emit 0xd9;
	__emit 0x1c;
	__emit 0x24;
	__emit 0xff;
	__emit 0x50;
	__emit 0x54;
	__emit 0x84;
	__emit 0xc0;
	__emit 0x75;
	__emit 0x5b;
	__emit 0x83;
	__emit 0xc7;
	__emit 0x23;
	__emit 0x3b;
	__emit 0xfd;
	__emit 0x89;
	__emit 0x7c;
	__emit 0x24;
	__emit 0x18;
	__emit 0x7e;
	__emit 0xd9;
	__emit 0x8b;
	__emit 0x7c;
	__emit 0x24;
	__emit 0x28;
	__emit 0x8b;
	__emit 0x44;
	__emit 0x24;
	__emit 0x30;
	__emit 0x83;
	__emit 0xc3;
	__emit 0x23;
	__emit 0x3b;
	__emit 0xd8;
	__emit 0x89;
	__emit 0x5c;
	__emit 0x24;
	__emit 0x14;
	__emit 0x7e;
	__emit 0xb6;
	__emit 0x8b;
	__emit 0x8c;
	__emit 0x24;
	__emit 0x74;
	__emit 0x02;
	__emit 0x00;
	__emit 0x00;
	__emit 0xe8;
	__emit 0xfe;
	__emit 0x95;
	__emit 0xf5;
	__emit 0xff;
	__emit 0x8b;
	__emit 0x40;
	__emit 0x24;
	__emit 0x8b;
	__emit 0x0d;
	__emit 0xbc;
	__emit 0xd5;
	__emit 0x2e;
	__emit 0x01;
	__emit 0x56;
	__emit 0x50;
	__emit 0xe8;
	__emit 0xfa;
	__emit 0x01;
	__emit 0x83;
	__emit 0x00;
	__emit 0x83;
	__emit 0xf8;
	__emit 0x02;
	__emit 0x8d;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x10;
	__emit 0x0f;
	__emit 0x95;
	__emit 0xc3;
	__emit 0xc7;
	__emit 0x84;
	__emit 0x24;
	__emit 0x6c;
	__emit 0x02;
	__emit 0x00;
	__emit 0x00;
	__emit 0xff;
	__emit 0xff;
	__emit 0xff;
	__emit 0xff;
	__emit 0xe8;
	__emit 0x21;
	__emit 0x52;
	__emit 0xf6;
	__emit 0xff;
	__emit 0x8a;
	__emit 0xc3;
	__emit 0xe9;
	__emit 0xe6;
	__emit 0xfa;
	__emit 0xff;
	__emit 0xff;
	__emit 0xc7;
	__emit 0x84;
	__emit 0x24;
	__emit 0x6c;
	__emit 0x02;
	__emit 0x00;
	__emit 0x00;
	__emit 0xff;
	__emit 0xff;
	__emit 0xff;
	__emit 0xff;
	__emit 0xe9;
	__emit 0xcb;
	__emit 0xfa;
	__emit 0xff;
	__emit 0xff;
	__emit 0x68;
	__emit 0xb8;
	__emit 0xd8;
	__emit 0x2e;
	__emit 0x01;
	__emit 0x6a;
	__emit 0x3b;
	__emit 0x55;
	__emit 0x8d;
	__emit 0x8c;
	__emit 0x24;
	__emit 0xf8;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0xe8;
	__emit 0x94;
	__emit 0x1a;
	__emit 0xf4;
	__emit 0xff;
	__emit 0x50;
	__emit 0x8d;
	__emit 0x8c;
	__emit 0x24;
	__emit 0xc4;
	__emit 0x01;
	__emit 0x00;
	__emit 0x00;
	__emit 0xe8;
	__emit 0x75;
	__emit 0x10;
	__emit 0xf7;
	__emit 0xff;
	__emit 0x8b;
	__emit 0x0d;
	__emit 0xb8;
	__emit 0xd5;
	__emit 0x2e;
	__emit 0x01;
	__emit 0x50;
	__emit 0x55;
	__emit 0x68;
	__emit 0x00;
	__emit 0x00;
	__emit 0x48;
	__emit 0x43;
	__emit 0x56;
	__emit 0xc7;
	__emit 0x84;
	__emit 0x24;
	__emit 0x7c;
	__emit 0x02;
	__emit 0x00;
	__emit 0x00;
	__emit 0x0d;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0xe8;
	__emit 0xfa;
	__emit 0xb3;
	__emit 0x92;
	__emit 0x00;
	__emit 0x3b;
	__emit 0xc5;
	__emit 0xc7;
	__emit 0x84;
	__emit 0x24;
	__emit 0x6c;
	__emit 0x02;
	__emit 0x00;
	__emit 0x00;
	__emit 0xff;
	__emit 0xff;
	__emit 0xff;
	__emit 0xff;
	__emit 0xc7;
	__emit 0x84;
	__emit 0x24;
	__emit 0xbc;
	__emit 0x01;
	__emit 0x00;
	__emit 0x00;
	__emit 0x5c;
	__emit 0x3b;
	__emit 0x08;
	__emit 0x01;
	__emit 0x0f;
	__emit 0x85;
	__emit 0x77;
	__emit 0xfa;
	__emit 0xff;
	__emit 0xff;
	__emit 0xd9;
	__emit 0x06;
	__emit 0x8b;
	__emit 0x46;
	__emit 0x04;
	__emit 0xd9;
	__emit 0x05;
	__emit 0x44;
	__emit 0x3c;
	__emit 0x08;
	__emit 0x01;
	__emit 0x89;
	__emit 0x44;
	__emit 0x24;
	__emit 0x20;
	__emit 0xd8;
	__emit 0xe9;
	__emit 0xe8;
	__emit 0x5e;
	__emit 0xfb;
	__emit 0x92;
	__emit 0x00;
	__emit 0xd8;
	__emit 0x05;
	__emit 0x44;
	__emit 0x3c;
	__emit 0x08;
	__emit 0x01;
	__emit 0x89;
	__emit 0x44;
	__emit 0x24;
	__emit 0x18;
	__emit 0xe8;
	__emit 0x4f;
	__emit 0xfb;
	__emit 0x92;
	__emit 0x00;
	__emit 0xd9;
	__emit 0x44;
	__emit 0x24;
	__emit 0x20;
	__emit 0xd8;
	__emit 0x05;
	__emit 0x44;
	__emit 0x3c;
	__emit 0x08;
	__emit 0x01;
	__emit 0x8b;
	__emit 0xe8;
	__emit 0xe8;
	__emit 0x3e;
	__emit 0xfb;
	__emit 0x92;
	__emit 0x00;
	__emit 0xd9;
	__emit 0x44;
	__emit 0x24;
	__emit 0x20;
	__emit 0xd8;
	__emit 0x25;
	__emit 0x44;
	__emit 0x3c;
	__emit 0x08;
	__emit 0x01;
	__emit 0x8b;
	__emit 0xf8;
	__emit 0x89;
	__emit 0x7c;
	__emit 0x24;
	__emit 0x30;
	__emit 0xe8;
	__emit 0x29;
	__emit 0xfb;
	__emit 0x92;
	__emit 0x00;
	__emit 0x8b;
	__emit 0xd8;
	__emit 0x3b;
	__emit 0xdf;
	__emit 0x89;
	__emit 0x5c;
	__emit 0x24;
	__emit 0x28;
	__emit 0x0f;
	__emit 0x8f;
	__emit 0xb0;
	__emit 0x01;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x7c;
	__emit 0x24;
	__emit 0x18;
	__emit 0x3b;
	__emit 0xfd;
	__emit 0x89;
	__emit 0x7c;
	__emit 0x24;
	__emit 0x14;
	__emit 0x7f;
	__emit 0x37;
	__emit 0xdb;
	__emit 0x44;
	__emit 0x24;
	__emit 0x28;
	__emit 0xd9;
	__emit 0x5c;
	__emit 0x24;
	__emit 0x2c;
	__emit 0x8b;
	__emit 0x44;
	__emit 0x24;
	__emit 0x2c;
	__emit 0xdb;
	__emit 0x44;
	__emit 0x24;
	__emit 0x14;
	__emit 0x8b;
	__emit 0x0d;
	__emit 0xcc;
	__emit 0xf4;
	__emit 0x2e;
	__emit 0x01;
	__emit 0x8b;
	__emit 0x11;
	__emit 0x50;
	__emit 0x51;
	__emit 0xd9;
	__emit 0x1c;
	__emit 0x24;
	__emit 0xff;
	__emit 0x52;
	__emit 0x54;
	__emit 0x84;
	__emit 0xc0;
	__emit 0x0f;
	__emit 0x85;
	__emit 0xea;
	__emit 0xf9;
	__emit 0xff;
	__emit 0xff;
	__emit 0x83;
	__emit 0xc7;
	__emit 0x28;
	__emit 0x3b;
	__emit 0xfd;
	__emit 0x89;
	__emit 0x7c;
	__emit 0x24;
	__emit 0x14;
	__emit 0x7e;
	__emit 0xd5;
	__emit 0x8b;
	__emit 0x7c;
	__emit 0x24;
	__emit 0x18;
	__emit 0x8b;
	__emit 0x44;
	__emit 0x24;
	__emit 0x30;
	__emit 0x83;
	__emit 0xc3;
	__emit 0x28;
	__emit 0x3b;
	__emit 0xd8;
	__emit 0x89;
	__emit 0x5c;
	__emit 0x24;
	__emit 0x28;
	__emit 0x7e;
	__emit 0xb2;
	__emit 0xe9;
	__emit 0x59;
	__emit 0x01;
	__emit 0x00;
	__emit 0x00;
	__emit 0x8b;
	__emit 0x84;
	__emit 0x24;
	__emit 0x74;
	__emit 0x02;
	__emit 0x00;
	__emit 0x00;
	__emit 0x3b;
	__emit 0xc5;
	__emit 0x74;
	__emit 0x41;
	__emit 0xd9;
	__emit 0x40;
	__emit 0x38;
	__emit 0x8b;
	__emit 0x48;
	__emit 0x40;
	__emit 0xd9;
	__emit 0x40;
	__emit 0x3c;
	__emit 0x89;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x24;
	__emit 0xd9;
	__emit 0xc9;
	__emit 0x8d;
	__emit 0x4c;
	__emit 0x24;
	__emit 0x1c;
	__emit 0xd8;
	__emit 0x26;
	__emit 0xd9;
	__emit 0x5c;
	__emit 0x24;
	__emit 0x1c;
	__emit 0xd8;
	__emit 0x66;
	__emit 0x04;
	__emit 0xd9;
	__emit 0x5c;
	__emit 0x24;
	__emit 0x20;
	__emit 0xd9;
	__emit 0x44;
	__emit 0x24;
	__emit 0x24;
	__emit 0xd8;
	__emit 0x66;
	__emit 0x08;
	__emit 0xd9;
	__emit 0x5c;
	__emit 0x24;
	__emit 0x24;
	__emit 0xe8;
	__emit 0xb5;
	__emit 0xc0;
	__emit 0xf7;
	__emit 0xff;
	__emit 0xd8;
	__emit 0x1d;
	__emit 0x44;
	__emit 0x3c;
	__emit 0x08;
	__emit 0x01;
	__emit 0xdf;
	__emit 0xe0;
	__emit 0xf6;
	__emit 0xc4;
	__emit 0x41;
	__emit 0x0f;
	__emit 0x84;
	__emit 0x7b;
	__emit 0xf9;
	__emit 0xff;
	__emit 0xff;
	__emit 0xd9;
	__emit 0x06;
	__emit 0x8b;
	__emit 0x56;
	__emit 0x04;
	__emit 0xd9;
	__emit 0x05;
	__emit 0x40;
	__emit 0x3c;
	__emit 0x08;
	__emit 0x01;
	__emit 0x89;
	__emit 0x54;
	__emit 0x24;
	__emit 0x20;
	__emit 0xd8;
	__emit 0xe9;
	__emit 0xe8;
	__emit 0x62;
	__emit 0xfa;
	__emit 0x92;
	__emit 0x00;
	__emit 0xd8;
	__emit 0x05;
	__emit 0x40;
	__emit 0x3c;
	__emit 0x08;
	__emit 0x01;
	__emit 0x89;
	__emit 0x44;
	__emit 0x24;
	__emit 0x18;
	__emit 0xe8;
	__emit 0x53;
	__emit 0xfa;
	__emit 0x92;
	__emit 0x00;
	__emit 0xd9;
	__emit 0x44;
	__emit 0x24;
	__emit 0x20;
	__emit 0xd8;
	__emit 0x25;
	__emit 0x40;
	__emit 0x3c;
	__emit 0x08;
	__emit 0x01;
	__emit 0x8b;
	__emit 0xe8;
	__emit 0xe8;
	__emit 0x42;
	__emit 0xfa;
	__emit 0x92;
	__emit 0x00;
	__emit 0xd9;
	__emit 0x44;
	__emit 0x24;
	__emit 0x20;
	__emit 0xd8;
	__emit 0x05;
	__emit 0x40;
	__emit 0x3c;
	__emit 0x08;
	__emit 0x01;
	__emit 0x8b;
	__emit 0xf8;
	__emit 0xe8;
	__emit 0x31;
	__emit 0xfa;
	__emit 0x92;
	__emit 0x00;
	__emit 0x3b;
	__emit 0xf8;
	__emit 0x8b;
	__emit 0xdf;
	__emit 0x89;
	__emit 0x44;
	__emit 0x24;
	__emit 0x30;
	__emit 0x89;
	__emit 0x5c;
	__emit 0x24;
	__emit 0x28;
	__emit 0x7f;
	__emit 0x59;
	__emit 0x8b;
	__emit 0x7c;
	__emit 0x24;
	__emit 0x18;
	__emit 0x8d;
	__emit 0xa4;
	__emit 0x24;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0x3b;
	__emit 0xfd;
	__emit 0x89;
	__emit 0x7c;
	__emit 0x24;
	__emit 0x14;
	__emit 0x7f;
	__emit 0x37;
	__emit 0xdb;
	__emit 0x44;
	__emit 0x24;
	__emit 0x28;
	__emit 0xd9;
	__emit 0x5c;
	__emit 0x24;
	__emit 0x2c;
	__emit 0x8b;
	__emit 0x54;
	__emit 0x24;
	__emit 0x2c;
	__emit 0xdb;
	__emit 0x44;
	__emit 0x24;
	__emit 0x14;
	__emit 0x8b;
	__emit 0x0d;
	__emit 0xcc;
	__emit 0xf4;
	__emit 0x2e;
	__emit 0x01;
	__emit 0x8b;
	__emit 0x01;
	__emit 0x52;
	__emit 0x51;
	__emit 0xd9;
	__emit 0x1c;
	__emit 0x24;
	__emit 0xff;
	__emit 0x50;
	__emit 0x54;
	__emit 0x84;
	__emit 0xc0;
	__emit 0x0f;
	__emit 0x85;
	__emit 0xeb;
	__emit 0xf8;
	__emit 0xff;
	__emit 0xff;
	__emit 0x83;
	__emit 0xc7;
	__emit 0x19;
	__emit 0x3b;
	__emit 0xfd;
	__emit 0x89;
	__emit 0x7c;
	__emit 0x24;
	__emit 0x14;
	__emit 0x7e;
	__emit 0xd5;
	__emit 0x8b;
	__emit 0x7c;
	__emit 0x24;
	__emit 0x18;
	__emit 0x8b;
	__emit 0x44;
	__emit 0x24;
	__emit 0x30;
	__emit 0x83;
	__emit 0xc3;
	__emit 0x19;
	__emit 0x3b;
	__emit 0xd8;
	__emit 0x89;
	__emit 0x5c;
	__emit 0x24;
	__emit 0x28;
	__emit 0x7e;
	__emit 0xb2;
	__emit 0x68;
	__emit 0xb8;
	__emit 0xd8;
	__emit 0x2e;
	__emit 0x01;
	__emit 0x6a;
	__emit 0x3b;
	__emit 0x6a;
	__emit 0x00;
	__emit 0x8d;
	__emit 0x8c;
	__emit 0x24;
	__emit 0xb0;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0xe8;
	__emit 0x8c;
	__emit 0x18;
	__emit 0xf4;
	__emit 0xff;
	__emit 0x50;
	__emit 0x8d;
	__emit 0x8c;
	__emit 0x24;
	__emit 0x34;
	__emit 0x02;
	__emit 0x00;
	__emit 0x00;
	__emit 0xe8;
	__emit 0x6d;
	__emit 0x0e;
	__emit 0xf7;
	__emit 0xff;
	__emit 0x8b;
	__emit 0x0d;
	__emit 0xb8;
	__emit 0xd5;
	__emit 0x2e;
	__emit 0x01;
	__emit 0x50;
	__emit 0x6a;
	__emit 0x00;
	__emit 0x68;
	__emit 0x00;
	__emit 0x00;
	__emit 0xfa;
	__emit 0x42;
	__emit 0x56;
	__emit 0xc7;
	__emit 0x84;
	__emit 0x24;
	__emit 0x7c;
	__emit 0x02;
	__emit 0x00;
	__emit 0x00;
	__emit 0x0e;
	__emit 0x00;
	__emit 0x00;
	__emit 0x00;
	__emit 0xe8;
	__emit 0xf1;
	__emit 0xb1;
	__emit 0x92;
	__emit 0x00;
	__emit 0x85;
	__emit 0xc0;
	__emit 0xc7;
	__emit 0x84;
	__emit 0x24;
	__emit 0x6c;
	__emit 0x02;
	__emit 0x00;
	__emit 0x00;
	__emit 0xff;
	__emit 0xff;
	__emit 0xff;
	__emit 0xff;
	__emit 0xc7;
	__emit 0x84;
	__emit 0x24;
	__emit 0x2c;
	__emit 0x02;
	__emit 0x00;
	__emit 0x00;
	__emit 0x5c;
	__emit 0x3b;
	__emit 0x08;
	__emit 0x01;
	__emit 0x0f;
	__emit 0x85;
	__emit 0x6e;
	__emit 0xf8;
	__emit 0xff;
	__emit 0xff;
	__emit 0x8b;
	__emit 0x8c;
	__emit 0x24;
	__emit 0x74;
	__emit 0x02;
	__emit 0x00;
	__emit 0x00;
	__emit 0xe8;
	__emit 0x4b;
	__emit 0x93;
	__emit 0xf5;
	__emit 0xff;
	__emit 0x8b;
	__emit 0x40;
	__emit 0x24;
	__emit 0x8b;
	__emit 0x0d;
	__emit 0xbc;
	__emit 0xd5;
	__emit 0x2e;
	__emit 0x01;
	__emit 0x56;
	__emit 0x50;
	__emit 0xe8;
	__emit 0x47;
	__emit 0xff;
	__emit 0x82;
	__emit 0x00;
	__emit 0xf7;
	__emit 0xd8;
	__emit 0x1a;
	__emit 0xc0;
	__emit 0xfe;
	__emit 0xc0;
	__emit 0xe9;
	__emit 0x49;
	__emit 0xf8;
	__emit 0xff;
	__emit 0xff;
	__emit 0xb0;
	__emit 0x01;
	__emit 0xe9;
	__emit 0x42;
	__emit 0xf8;
	__emit 0xff;
	__emit 0xff;
	__emit 0x8b;
	__emit 0x8c;
	__emit 0x24;
	__emit 0x74;
	__emit 0x02;
	__emit 0x00;
	__emit 0x00;
	__emit 0xe8;
	__emit 0x1d;
	__emit 0x93;
	__emit 0xf5;
	__emit 0xff;
	__emit 0x8b;
	__emit 0x40;
	__emit 0x24;
	__emit 0x8b;
	__emit 0x0d;
	__emit 0xbc;
	__emit 0xd5;
	__emit 0x2e;
	__emit 0x01;
	__emit 0x56;
	__emit 0x50;
	__emit 0xe8;
	__emit 0x19;
	__emit 0xff;
	__emit 0x82;
	__emit 0x00;
	__emit 0x33;
	__emit 0xc9;
	__emit 0x83;
	__emit 0xf8;
	__emit 0x02;
	__emit 0x0f;
	__emit 0x95;
	__emit 0xc1;
	__emit 0x8a;
	__emit 0xc1;
	__emit 0xe9;
	__emit 0x17;
	__emit 0xf8;
	__emit 0xff;
	__emit 0xff;
	__emit 0x8b;
	__emit 0x0d;
	__emit 0xcc;
	__emit 0xf4;
	__emit 0x2e;
	__emit 0x01;
	__emit 0x6a;
	__emit 0x01;
	__emit 0x6a;
	__emit 0x01;
	__emit 0x68;
	__emit 0x00;
	__emit 0x00;
	__emit 0xa0;
	__emit 0x40;
	__emit 0x56;
	__emit 0xe8;
	__emit 0x70;
	__emit 0xb1;
	__emit 0xf5;
	__emit 0xff;
	__emit 0xf7;
	__emit 0xd8;
	__emit 0x1b;
	__emit 0xc0;
	__emit 0xf7;
	__emit 0xd8;
	__emit 0xe9;
	__emit 0xf7;
	__emit 0xf7;
	__emit 0xff;
	__emit 0xff;
	}
#if 0
	if (checkSourceRequirements)
	{
		//First check, if our object can do this special power.
		if( !obj->hasSpecialPower( spTemplate->getSpecialPowerType() ) )
		{
			return false;
		}
	}

	SpecialPowerModuleInterface *mod = obj->getSpecialPowerModule( spTemplate );
	if( mod )
	{
		if (checkSourceRequirements)
		{
			if( mod->getPercentReady() < 1.0f )
			{
				//Not fully ready
				return false;
			}
		}
    
		// First check terrain type, if it is cared about.  Don't return a true, since there are more checks.
		switch( spTemplate->getSpecialPowerType() )
		{
			case SPECIAL_PARADROP_AMERICA:
			case INFA_SPECIAL_PARADROP_AMERICA:
			case SPECIAL_CRATE_DROP:
			case SPECIAL_TANK_PARADROP:
			{
				if( TheTerrainLogic->isUnderwater( loc->x, loc->y ) )
					return FALSE;
			}
		}

		// Last check is shroudedness, if it is cared about
		switch( spTemplate->getSpecialPowerType() )
		{
			case SPECIAL_DAISY_CUTTER:
			case AIRF_SPECIAL_DAISY_CUTTER:
			case SPECIAL_PARADROP_AMERICA:
			case SPECIAL_TANK_PARADROP:
			case INFA_SPECIAL_PARADROP_AMERICA:
			case SPECIAL_CARPET_BOMB:
			case SPECIAL_CHINA_CARPET_BOMB:
			case SPECIAL_LEAFLET_DROP:
			case EARLY_SPECIAL_LEAFLET_DROP:
			case EARLY_SPECIAL_CHINA_CARPET_BOMB:
			case AIRF_SPECIAL_CARPET_BOMB:
			case SUPR_SPECIAL_CRUISE_MISSILE:
			case SPECIAL_CLUSTER_MINES:
			case NUKE_SPECIAL_CLUSTER_MINES:
			case SPECIAL_EMP_PULSE:
			case SPECIAL_CRATE_DROP:
			case SPECIAL_NAPALM_STRIKE:
			case SPECIAL_BLACK_MARKET_NUKE:
			case SPECIAL_ANTHRAX_BOMB:
			case SPECIAL_TERROR_CELL:
			case SPECIAL_AMBUSH:
			case SPECIAL_NEUTRON_MISSILE:
			case NUKE_SPECIAL_NEUTRON_MISSILE:
			case SUPW_SPECIAL_NEUTRON_MISSILE:
			case SPECIAL_SCUD_STORM:
#ifdef ALLOW_DEMORALIZE
			case SPECIAL_DEMORALIZE:
#endif
			case SPECIAL_A10_THUNDERBOLT_STRIKE:
			case AIRF_SPECIAL_A10_THUNDERBOLT_STRIKE:
			case SPECIAL_SPECTRE_GUNSHIP:
			case AIRF_SPECIAL_SPECTRE_GUNSHIP:
			case SPECIAL_REPAIR_VEHICLES:
			case EARLY_SPECIAL_REPAIR_VEHICLES:
      case SPECIAL_GPS_SCRAMBLER:  
			case SLTH_SPECIAL_GPS_SCRAMBLER:
			case SPECIAL_ARTILLERY_BARRAGE:
			case SPECIAL_FRENZY:
			case EARLY_SPECIAL_FRENZY:
			case SPECIAL_PARTICLE_UPLINK_CANNON:
			case SUPW_SPECIAL_PARTICLE_UPLINK_CANNON:
			case LAZR_SPECIAL_PARTICLE_UPLINK_CANNON:
			case SPECIAL_CLEANUP_AREA:
			case SPECIAL_SNEAK_ATTACK:
			case SPECIAL_BATTLESHIP_BOMBARDMENT:
				//Don't allow "damaging" special powers in shrouded areas, but Fogged are okay.
				return ThePartitionManager->getShroudStatusForPlayer( obj->getControllingPlayer()->getPlayerIndex(), loc ) != CELLSHROUD_SHROUDED;

			case SPECIAL_SPY_SATELLITE:
			case SPECIAL_RADAR_VAN_SCAN:
			case SPECIAL_SPY_DRONE:
			case SPECIAL_HELIX_NAPALM_BOMB:

        //These specials can be used anywhere!
        return isPointOnMap( loc );
      case SPECIAL_LAUNCH_BAIKONUR_ROCKET:
			  return TRUE;

			//These special powers require object targets!
			case SPECIAL_MISSILE_DEFENDER_LASER_GUIDED_MISSILES:
			case SPECIAL_HACKER_DISABLE_BUILDING:
			case SPECIAL_TANKHUNTER_TNT_ATTACK:
			case SPECIAL_BOOBY_TRAP:
			case SPECIAL_CASH_HACK:
			case SPECIAL_DEFECTOR:
			case SPECIAL_BLACKLOTUS_CAPTURE_BUILDING:
			case SPECIAL_BLACKLOTUS_DISABLE_VEHICLE_HACK:
			case SPECIAL_BLACKLOTUS_STEAL_CASH_HACK:
			case SPECIAL_INFANTRY_CAPTURE_BUILDING:
			case SPECIAL_DETONATE_DIRTY_NUKE:
			case SPECIAL_DISGUISE_AS_VEHICLE:
			case SPECIAL_REMOTE_CHARGES:
			case SPECIAL_TIMED_CHARGES:
			case SPECIAL_CASH_BOUNTY:
			case SPECIAL_CHANGE_BATTLE_PLANS:
				return false;
		}
	}
	return false;
#endif
}

//------------------------------------------------------------------------------------------------
struct ActionManager_BFME_Object_WeaponSetField
{
	unsigned char pad[0x264];
	WeaponSet weaponSet;
};

//------------------------------------------------------------------------------------------------
Bool ActionManager::canFireWeaponAtLocation( const Object *obj, const Coord3D *loc, CommandSourceType commandSource, const WeaponSlotType slot, const Object *objectInWay )
{
	//Sanity check
	if( obj == NULL || loc == NULL )
	{
		return false;
	}

	//Make sure we have the right weapon.
	// Through the BFME field offset, the same way canFireWeapon does: retail
	// reaches the weapon set at Object+0x264 directly rather than through a
	// getter.
	Weapon *weapon = reinterpret_cast<const ActionManager_BFME_Object_WeaponSetField *>(obj)->weaponSet.getWeaponInWeaponSlot( slot );
	if( !weapon )
	{
		return false;
	}

	return true;
}

//------------------------------------------------------------------------------------------------
// ?canFireWeaponAtObject@ActionManager@@QAE_NPBVObject@@0W4CommandSourceType@@W4WeaponSlotType@@@Z present-unmatched
Bool ActionManager::canFireWeaponAtObject( const Object *obj, const Object *target, CommandSourceType commandSource, const WeaponSlotType slot )
{
	//Sanity check
	if( obj == NULL || target == NULL )
	{
		return FALSE;
	}

	//Make sure we have the right weapon.
	Weapon *weapon = obj->getWeaponInWeaponSlot( slot );
	if( !weapon )
	{
		return FALSE;
	}

	Bool sniper = FALSE;
	if( weapon->getDamageType() == DAMAGE_KILLPILOT )
	{
		if( !canSnipeVehicle( obj, target, commandSource ) )
		{
			return FALSE;
		}
		sniper = TRUE;
	}

	CanAttackResult result;
	if( sniper )
		result = obj->getAbleToAttackSpecificObject( ATTACK_NEW_TARGET, target, commandSource, slot );
	else
		result = obj->getAbleToAttackSpecificObject( ATTACK_NEW_TARGET, target, commandSource );
	
	if( result == ATTACKRESULT_POSSIBLE || result == ATTACKRESULT_POSSIBLE_AFTER_MOVING )
	{
		return weapon->estimateWeaponDamage( obj, target ) != 0.0f;
	}
	return FALSE;
}


// ?canFireWeapon@ActionManager@@QAE_NPBVObject@@W4WeaponSlotType@@W4CommandSourceType@@@Z
Bool ActionManager::canFireWeapon( const Object *obj, const WeaponSlotType slot, CommandSourceType commandSource )
{
	//Sanity check
	if( obj == NULL )
	{
		return false;
	}

	//Make sure we have the right weapon.
	Weapon *weapon = reinterpret_cast<const ActionManager_BFME_Object_WeaponSetField *>(obj)->weaponSet.getWeaponInWeaponSlot( slot );
	if( !weapon )
	{
		return false;
	}

	return true;
	
}

// The shroud subsystem is a SEPARATE global from the partition manager in BFME:
// the engine-init tag block at 0x0038A1F0 stores 0x012ED5BC and then pushes the
// tag "TheShroudManager", while ThePartitionManager is constructed just before
// it at 0x012ED5B8.  The shroud read below reaches the former; every other
// ThePartitionManager use in this file is a real partition call and is correct.
extern PartitionManager *TheShroudManager;				///< retail 0x012ED5BC

//------------------------------------------------------------------------------------------------
Bool ActionManager::canOverrideSpecialPowerDestination( const Object *obj, const Coord3D *loc, SpecialPowerType spType, CommandSourceType commandSource )
{
	SpecialPowerUpdateInterface* spuInterface = obj->findSpecialPowerWithOverridableDestinationActive( spType );
	if( spuInterface )
	{
		//But so long as it's not in the black areas of the map.
		return TheShroudManager->getShroudStatusForPlayer( obj->getControllingPlayer()->getPlayerIndex(), loc ) != CELLSHROUD_SHROUDED;
	}
	return false;
}

// 0x0090F2E0: unreferenced retail body, mov eax,[ecx+eax*4+0x14] indexed by one
// stack argument.  The Zero Hour WeaponTemplateSet::getNthCommandSourceMask has
// these bytes but no caller or vtable proves the name.
// IDENTITY IS NOT RECOVERED.  The name is derived from the address.
class Rva0090F2E0IndexedMasks
{
public:
	unsigned int get( int index ) const;

	char         m_lead[ 0x14 ];
	unsigned int m_masks[ 1 ];
};

unsigned int Rva0090F2E0IndexedMasks::get( int index ) const
{
	return m_masks[ index ];
}

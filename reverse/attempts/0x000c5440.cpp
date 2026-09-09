// attempt stash for ?canEnterObject@BFMEActionManager@@QAE_NPBVObject@@0W4CommandSourceType@@W4CanEnterType@@PA_N@Z at 0x000C5440
// partial score=0.35 date=2026-09-09
// BFME added a 5th out-parameter to ActionManager::canEnterObject; the class itself
// carries no state the body touches, so a minimal standalone type reproduces the ABI.
// ?canEnterObject@BFMEActionManager@@QAE_NPBVObject@@0W4CommandSourceType@@W4CanEnterType@@PA_N@Z present-unmatched (0x000C5440)
class BFMEActionManager
{
public:
	Bool canEnterObject( const Object *obj, const Object *objectToEnter, CommandSourceType commandSource, CanEnterType mode, Bool *pFlag );
};

Bool BFMEActionManager::canEnterObject( const Object *obj, const Object *objectToEnter, CommandSourceType commandSource, CanEnterType mode, Bool *pFlag )
{
	Bool dummyFlag;
	if( pFlag == NULL )
		pFlag = &dummyFlag;
	*pFlag = FALSE;

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
	if ( obj->isKindOf( KINDOF_IGNORED_IN_GUI )
		|| obj->isKindOf( KINDOF_MOB_NEXUS )
		|| objectToEnter->isKindOf( KINDOF_IGNORED_IN_GUI ) )
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
			return TRUE;
		}
	}

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
			return FALSE;
		}
	}

	if (mode == COMBATDROP_INTO)
	{
		if (objectToEnter->isFactionStructure())
			return FALSE;
	}
	else
	{
		Bool checkCapacity = (mode == CHECK_CAPACITY);
		Int containCount = contain->getContainCount();
		Int stealthContainCount = contain->getStealthUnitsContained();

		if (objectToEnter->getControllingPlayer() != obj->getControllingPlayer())
		{
			if (containCount - stealthContainCount > 0)
				return FALSE;

			if (objectToEnter->isFactionStructure())
				return FALSE;

			*pFlag = TRUE;

			if (stealthContainCount > 0 && containCount - stealthContainCount == 0)
				checkCapacity = FALSE;
		}

		if( checkCapacity && obj->getTransportSlotCount() == 0 )
		{
			return FALSE;
		}

		if( contain->isValidContainerFor( obj, checkCapacity ) == FALSE )
		{
			return FALSE;
		}
	}

	return TRUE;
}



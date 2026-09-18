// ?computeAttackPath@AIUpdateInterface@@AAE_NPAVPathfindServicesInterface@@PBVObject@@PBUCoord3D@@@Z
// partial score=0.19 date=2026-09-17
// ?computeAttackPath@AIUpdateInterface@@AAE_NPAVPathfindServicesInterface@@PBVObject@@PBUCoord3D@@@Z
// Extracted from Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate.cpp.
// This is the best semantic candidate; its complete TU remains the source of
// the compile experiment and the layout declarations used by the body.
Bool AIUpdateInterface::computeAttackPath( PathfindServicesInterface *pathServices, const Object *victim, const Coord3D* victimPos )
{
	//CRCDEBUG_LOG(("AIUpdateInterface::computeAttackPath() for object %d\n", getObject()->getID()));
	// See if it has been too soon.
	if (m_pathTimestamp >= TheGameLogic->getFrame()-2) 
	{
		// jba intense debug
		//CRCDEBUG_LOG(("Info - RePathing very quickly %d, %d.\n", m_pathTimestamp, TheGameLogic->getFrame()));
		if (m_path && m_isBlockedAndStuck) 
		{
			setIgnoreCollisionTime(2*LOGICFRAMES_PER_SECOND);
			m_blockedFrames = 0;
			m_isBlocked = FALSE;
			m_isBlockedAndStuck = FALSE;
			return TRUE;
		}
	}
	Bool landBound = FALSE;
	// Note - if a truck happens to pop into the air and gets a move to command, it still
	// needs to pathfind.  So only skip pathfinding for airborne things that can fly... jba.
	if (!(m_locomotorSet.getValidSurfaces() & LOCOMOTORSURFACE_AIR))
	{
		landBound = TRUE;
	}

	Object* source = getObject();
	if (!victim && !victimPos) 
	{
		return FALSE;
	}

	PathfindLayerEnum victimLayer = LAYER_GROUND;
	if (victim) {
		victimLayer = victim->getLayer();
	}

	Weapon *weapon = source->getCurrentWeapon();
	if (!weapon)
	{
		DEBUG_CRASH(("no weapon in AIUpdateInterface::computeAttackPath"));
		return FALSE;
	}

	if (victim != NULL)
	{
		if (weapon->isWithinAttackRange(source, victim))
		{
			Bool viewBlocked = FALSE;
			if (isDoingGroundMovement() && !victim->isSignificantlyAboveTerrain()) 
			{
				viewBlocked = TheAI->pathfinder()->isAttackViewBlockedByObstacle(source, *source->getPosition(), victim, *victim->getPosition());
			}
			if (!viewBlocked) 
			{
				destroyPath();
				return TRUE;
			}
		}
	}
	else if (victimPos != NULL)
	{
		if (weapon->isWithinAttackRange(source, victimPos))
		{
			Bool viewBlocked = FALSE;
			if (isDoingGroundMovement()) 
			{
				viewBlocked = TheAI->pathfinder()->isAttackViewBlockedByObstacle(source, *source->getPosition(), NULL, *victimPos);
			}
			if (!viewBlocked) {
				destroyPath();
				return TRUE;
			}
		}
	}

	// Contact weapon
	if (weapon->isContactWeapon()) 
	{
		Coord3D tmp = *victimPos;
		destroyPath();
		if (this->getCurLocomotor()) 
		{
			getCurLocomotor()->setNoSlowDownAsApproachingDest(TRUE);
		}
		Bool ok = computePath(pathServices, &tmp);
		if (m_path==NULL) return false;
		Real dx, dy;
		dx = victimPos->x - m_path->getLastNode()->getPosition()->x;
		dy = victimPos->y - m_path->getLastNode()->getPosition()->y;
		if (sqr(dx)+sqr(dy) < sqr(PATHFIND_CELL_SIZE_F*3)) {
			if (m_path) 
			{
				m_path->updateLastNode(victimPos);
			}
		}
		dx = source->getPosition()->x - m_path->getLastNode()->getPosition()->x;
		dy = source->getPosition()->y - m_path->getLastNode()->getPosition()->y;
		if (sqr(dx)+sqr(dy) < sqr(PATHFIND_CELL_SIZE_F)) {
			destroyPath();
			return false;
		}
		return ok;
	}

	Coord3D localVictimPos;
	if (victim != NULL)
	{
		if (victim->isKindOf(KINDOF_BRIDGE)) 
		{
			TBridgeAttackInfo info;
			TheTerrainLogic->getBridgeAttackPoints(victim, &info);
			Real distSqr1 = ThePartitionManager->getDistanceSquared( source, &info.attackPoint1, FROM_BOUNDINGSPHERE_3D );
			Real distSqr2 = ThePartitionManager->getDistanceSquared( source, &info.attackPoint2, FROM_BOUNDINGSPHERE_3D );
			if (distSqr2<distSqr1) {
				localVictimPos = info.attackPoint2;
			} else {
				localVictimPos = info.attackPoint1;
			}
		}
		else
		{
			localVictimPos = *victim->getPosition();
		}
	}
	else
	{
		localVictimPos = *victimPos;
	}

	localVictimPos.z = TheTerrainLogic->getLayerHeight( localVictimPos.x, localVictimPos.y, victimLayer );

	if (getObject()->isAboveTerrain() && !landBound)
	{
		weapon->computeApproachTarget(getObject(), victim, &localVictimPos, 0, localVictimPos);
		if (m_path) 
		{
			PathNode *startNode, *closeNode = NULL;
			startNode = m_path->getFirstNode();
			closeNode = startNode->getNextOptimized();
			if (closeNode && closeNode->getNextOptimized()==NULL) {
				Real dxSqr = localVictimPos.x - closeNode->getPosition()->x;
				dxSqr *= dxSqr;
				Real dySqr = localVictimPos.y - closeNode->getPosition()->y;
				dySqr *= dySqr;
				if (dxSqr+dySqr<0.25f) 
				{
					return TRUE;
				}
			}
		}
		destroyPath();
		m_path = newInstance(Path);
		m_path->prependNode( &localVictimPos, LAYER_GROUND );
		Coord3D pos = *getObject()->getPosition();
		pos.z = localVictimPos.z;
		m_path->prependNode( &pos, LAYER_GROUND );
		m_path->getFirstNode()->setNextOptimized(m_path->getFirstNode()->getNext());
		if (TheGlobalData->m_debugAI==AI_DEBUG_PATHS) 
		{
			TheAI->pathfinder()->setDebugPath(m_path);
		}
	}
	else
	{
		destroyPath();
		TheAI->pathfinder()->setIgnoreObstacleID( getIgnoredObstacleID() );
		m_path = pathServices->findAttackPath( getObject(), m_locomotorSet, getObject()->getPosition(), 
			victim, &localVictimPos, weapon);
		if (m_path) {
			Coord3D goal = *m_path->getLastNode()->getPosition();
			if (!weapon->isGoalPosWithinAttackRange(getObject(), &goal, victim, &localVictimPos)) {
				Coord3D objPos = *getObject()->getPosition();
				goal.sub(&objPos);
				if (goal.length()<3*PATHFIND_CELL_SIZE_F) {
					destroyPath();
					TheAI->pathfinder()->adjustDestination(getObject(), m_locomotorSet, &objPos);
					m_path = pathServices->findClosestPath(getObject(), m_locomotorSet, getObject()->getPosition(), 
								&objPos, false, 0.2f, true );
				}
				if (m_path==NULL) {
					return false;
				}
			}
			goal = *m_path->getLastNode()->getPosition();
			TheAI->pathfinder()->updateGoal(getObject(), &goal, TheTerrainLogic->getLayerForDestination(&goal));
			if (m_path->getBlockedByAlly()) 
			{
				if( !getObject()->isKindOf(KINDOF_NO_COLLIDE))
					TheAI->pathfinder()->moveAllies(getObject(), m_path);
			}
		}
		TheAI->pathfinder()->setIgnoreObstacleID( INVALID_ID );
	}

	m_pathTimestamp = TheGameLogic->getFrame();
	m_blockedFrames = 0;
	m_isBlockedAndStuck = FALSE;
	if (m_path)
		return TRUE;

	return FALSE;
}

// ?computeAttackPath@AIUpdateInterface@@AAE_NPAVPathfindServicesInterface@@PBVObject@@PBUCoord3D@@@Z
// partial score=0.55 date=2026-09-20
// ?computeAttackPath@AIUpdateInterface@@AAE_NPAVPathfindServicesInterface@@PBVObject@@PBUCoord3D@@@Z
// Extracted from Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate.cpp.
// This is the best semantic candidate; its complete TU remains the source of
// the compile experiment and the layout declarations used by the body.
Bool AIUpdateInterface::computeAttackPath( PathfindServicesInterface *pathServices, const Object *victim, const Coord3D* victimPos )
{
	//CRCDEBUG_LOG(("AIUpdateInterface::computeAttackPath() for object %d\n", getObject()->getID()));
	BFMEApproachPathFields *layout = reinterpret_cast<BFMEApproachPathFields *>(this);
	const BFMENeedToRotateFields *fields = reinterpret_cast<const BFMENeedToRotateFields *>(this);
	LocomotorSet *locomotorSet = reinterpret_cast<LocomotorSet *>(reinterpret_cast<char *>(this) + 0x1A8);
	if (layout->m_path)
	{
		BFMEComputeAttackPoint point;
		Object *pathObject = layout->m_object;
		typedef void (BFMENeedToRotatePath::*ComputePointCall)(Object *, BFMELocomotorOverride *, BFMEComputeAttackPoint *, Bool);
		union { void *asVoid; ComputePointCall asMember; } pointCast;
		pointCast.asVoid = (void *)j_00008a9e;
		(reinterpret_cast<BFMENeedToRotatePath *>(layout->m_path)->*pointCast.asMember)(
			pathObject, fields->m_curLocomotor, &point, FALSE);
		if (point.m_waypointID != INVALID_WAYPOINT_ID)
		{
			layout->m_pathTimestamp = TheGameLogic->getFrame();
			layout->m_blockedFrames = 0;
			layout->m_isBlockedAndStuck = FALSE;
			return TRUE;
		}
	}
	Bool landBound = FALSE;
	// Note - if a truck happens to pop into the air and gets a move to command, it still
	// needs to pathfind.  So only skip pathfinding for airborne things that can fly... jba.
	if (!(reinterpret_cast<const BFMEQuickPathFields *>(this)->getValidLocomotorSurfaces() & LOCOMOTORSURFACE_AIR))
	{
		landBound = TRUE;
	}

	Object* source = layout->m_object;
	if (!victim && !victimPos) 
	{
		return FALSE;
	}

	PathfindLayerEnum victimLayer = LAYER_GROUND;
	if (victim) {
		typedef Int (Rva0003A391Object::*GetLayerCall)() const;
		union { void *asVoid; GetLayerCall asMember; } layerCast;
		layerCast.asVoid = (void *)j_0003a391;
		victimLayer = (PathfindLayerEnum)(reinterpret_cast<const Rva0003A391Object *>(victim)->*layerCast.asMember)();
	}

	Weapon *weapon = source->getCurrentWeapon();
	if (!weapon)
	{
		DEBUG_CRASH(("no weapon in AIUpdateInterface::computeAttackPath"));
		return FALSE;
	}

	if (victim != NULL)
	{
		typedef Bool (Rva0002E85CWeapon::*AttackRangeCall)(const Object *, const Object *, Int) const;
		union { void *asVoid; AttackRangeCall asMember; } rangeCast;
		rangeCast.asVoid = (void *)j_0002e85c;
		if ((reinterpret_cast<const Rva0002E85CWeapon *>(weapon)->*rangeCast.asMember)(source, victim, 0))
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
		typedef Bool (Rva0003A4E5Weapon::*GoalRangeCall)(const Object *, const Coord3D *, const Object *, const Coord3D *, Int) const;
		union { void *asVoid; GoalRangeCall asMember; } goalRangeCast;
		goalRangeCast.asVoid = (void *)j_0003a4e5;
		if ((reinterpret_cast<const Rva0003A4E5Weapon *>(weapon)->*goalRangeCast.asMember)(source, source->getPosition(), NULL, victimPos, 0))
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
	typedef Bool (Rva0000B8ACTemplate::*IsContactCall)() const;
	union { void *asVoid; IsContactCall asMember; } contactCast;
	contactCast.asVoid = (void *)j_0000b8ac;
	Rva0000B8ACTemplate *weaponTemplate = *(Rva0000B8ACTemplate **)((char *)weapon + 4);
	if ((weaponTemplate->*contactCast.asMember)())
	{
		Coord3D tmp;
		tmp.x = victimPos->x;
		tmp.y = victimPos->y;
		tmp.z = victimPos->z;
		destroyPath();
		BFMELocomotorOverride *curLocomotor = reinterpret_cast<BFMELocomotorOverride *>(fields->m_curLocomotor);
		if (curLocomotor)
		{
			bfmeEnableNoSlowDown(curLocomotor);
		}
		if (g_012F0239 && g_012ED4FC)
			((BFMEPathDebugLogFunction)j_0003a17a)(g_012ED4FC, (const char *)0x010BA158);
		Bool ok = computePath(pathServices, &tmp);
		if (layout->m_path==NULL) return false;
		Real dx, dy;
		BFMEPathNodeView *lastNode = *reinterpret_cast<BFMEPathNodeView **>(
			reinterpret_cast<char *>(layout->m_path) + 0x08);
		dx = victimPos->x - lastNode->m_position.x;
		dy = victimPos->y - lastNode->m_position.y;
		if (sqr(dx)+sqr(dy) < sqr(PATHFIND_CELL_SIZE_F*3)) {
			if (layout->m_path) 
			{
				layout->m_path->updateLastNode(victimPos);
			}
		}
		lastNode = *reinterpret_cast<BFMEPathNodeView **>(
			reinterpret_cast<char *>(layout->m_path) + 0x08);
		dx = source->getPosition()->x - lastNode->m_position.x;
		dy = source->getPosition()->y - lastNode->m_position.y;
		if (sqr(dx)+sqr(dy) < sqr(PATHFIND_CELL_SIZE_F)) {
			destroyPath();
			return false;
		}
		return ok;
	}

	Coord3D localVictimPos;
	if (victim != NULL)
	{
		if (victim->isKindOf((KindOfType)0x16)) 
		{
			TBridgeAttackInfo info;
			TheTerrainLogic->getBridgeAttackPoints(victim, &info);
			typedef Real (Rva0002CEEEBoundaryObject::*BoundaryDistanceCall)(const Coord3D *, const Coord3D *) const;
			union { void *asVoid; BoundaryDistanceCall asMember; } distanceCast;
			distanceCast.asVoid = (void *)j_0002ceee;
			Real distSqr1 = (reinterpret_cast<const Rva0002CEEEBoundaryObject *>(source)->*distanceCast.asMember)(
				source->getPosition(), &info.attackPoint1);
			Real distSqr2 = (reinterpret_cast<const Rva0002CEEEBoundaryObject *>(source)->*distanceCast.asMember)(
				source->getPosition(), &info.attackPoint2);
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

	localVictimPos.z = reinterpret_cast<const Rva00275F30TerrainLogic *>(TheTerrainLogic)->getLayerHeight(
		localVictimPos.x, localVictimPos.y, victimLayer, NULL, TRUE );

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

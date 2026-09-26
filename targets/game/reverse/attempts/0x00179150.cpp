// ?update@AIFollowPathState@@UAE?AW4StateReturnType@@XZ
// partial score=0.25 date=2026-09-10
// ?update@AIFollowPathState@@UAE?AW4StateReturnType@@XZ
// Complete semantic reconstruction attempted at retail RVA 0x00179150 (809B).
// Identity: AIFollowPathState base vtable slot 6; named JetAIUpdate callers.
// This body is banked because the shared BFME headers place the state machine
// and path fields at different offsets from retail and resolve several callees
// to different bodies. It is retained as a complete failed candidate.
StateReturnType AIFollowPathState::update()
{
	getMachine()->setGoalPosition(&m_goalPosition);
	// do movement
	StateReturnType status = AIInternalMoveToState::update();
	// if move to has finished, move to next point on path
	if (status == STATE_SUCCESS || status == STATE_FAILURE)
	{
		Object *obj = getMachineOwner();
		AIUpdateInterface *ai = obj->getAI();
		if (status == STATE_FAILURE && m_retryCount>0) {
			// If we failed, & haven't reached retry limit, try again.  jba.
			m_retryCount--;
		} else {
			++m_index;
		}
		const Coord3D *pos = ai->friend_getGoalPathPosition( m_index );

		Bool tooClose=true;
		while (pos && tooClose) {
			Real dx = pos->x - obj->getPosition()->x;
			Real dy = pos->y - obj->getPosition()->y;
			tooClose = false;
			if (sqr(dx) + sqr(dy) < sqr(PATHFIND_CELL_SIZE_F)) {
				tooClose = true;
			}
			if (tooClose) {
				m_index++;
				pos = ai->friend_getGoalPathPosition(m_index);
			}
		}

		// Assign this value so objects can access the current waypoint index.
		ai->friend_setCurrentGoalPathIndex( m_index );
		ai->ignoreObstacleID(INVALID_ID);
		if (pos == NULL)
		{
			return STATE_SUCCESS;
		}

		ai->friend_startingMove();
		m_goalPosition = *pos;
		const Coord3D *nextPos = ai->friend_getGoalPathPosition( m_index+1 );

		if (nextPos)
		{
			Coord2D delta;
			delta.x = nextPos->x - pos->x;
			delta.y = nextPos->y - pos->y;
			Real offset = delta.length();
			const Coord3D *followingPos = ai->friend_getGoalPathPosition( m_index+2 );
			if (followingPos) offset += 4*PATHFIND_CELL_SIZE_F;
			ai->setPathExtraDistance(offset);
			setAdjustsDestination(false);
		}
		else
		{
			setAdjustsDestination(m_adjustFinal && (m_adjustFinalOverride || ai->isDoingGroundMovement()));
			if (getAdjustsDestination())
			{
				if (!TheAI->pathfinder()->adjustDestination(getMachineOwner(), ai->getLocomotorSet(), &m_goalPosition)) {
					return STATE_FAILURE;
				}
				TheAI->pathfinder()->updateGoal(getMachineOwner(), &m_goalPosition, TheTerrainLogic->getLayerForDestination(&m_goalPosition));
			}

			if (obj->isKindOf(KINDOF_PROJECTILE))
			{
				if (ai && ai->getCurLocomotor())
					ai->getCurLocomotor()->setUsePreciseZPos(true);
			}
		}
		computePath();
		return STATE_CONTINUE;
	}

	return status;
}

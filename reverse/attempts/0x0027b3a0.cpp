// ?d_0027b3a0@@YAXXZ
// partial score=0.99 date=2026-09-03
// ?doPathfind@AIUpdateInterface@@ present-unmatched
#define g_012F0239 BFME_PATH_DEBUG_FLAG
#define g_012ED4FC BFME_PATH_DEBUG_CONTEXT
#define TheGameLogic BFME_PATH_GAME_LOGIC
#define TheAI BFME_PATH_AI
void AIUpdateInterface::doPathfind( PathfindServicesInterface *pathfinder )
{
	BFMEApproachPathFields *retail = reinterpret_cast<BFMEApproachPathFields *>( this );

	if (g_012F0239 && g_012ED4FC)
	{
		((BFMEPathDebugLogFunction)j_0003a17a)(g_012ED4FC,
			"CritterDesync: doPathfind1 -- m_requestedDestination=%g,%g,%g",
			retail->m_requestedDestination.x, retail->m_requestedDestination.y,
			retail->m_requestedDestination.z);
	}
	if (!retail->m_waitingForPath)
	{
		return;
	}

	reinterpret_cast<Rva003D5620DwordSlot *>(BFME_PATH_AI->pathfinder())->set(
		*reinterpret_cast<const Int *>(reinterpret_cast<const char *>(this) + 0x164));
	retail->m_waitingForPath = FALSE;
	if (retail->m_isSafePath)
	{
		destroyPath();
		Coord3D pos1, pos2;
		pos1.x = -1000.0f;
		pos1.y = -1000.0f;
		pos1.z = 0.0f;
		Object *repulsor;
		BFMEObjectLookup * const gameLogic = BFME_PATH_GAME_LOGIC;
		repulsor = gameLogic->findObjectByID(retail->m_repulsor1);
		if (repulsor)
		{
			pos1 = *repulsor->getPosition();
		}
		pos2 = pos1;
		repulsor = gameLogic->findObjectByID(retail->m_repulsor2);
		if (repulsor)
		{
			pos2 = *repulsor->getPosition();
		}
		Object *object = retail->m_object;
		const TAiData *aiData = BFME_PATH_AI->getAiData();
		Int extraDistance = (Int)*reinterpret_cast<const volatile Real *>(
			reinterpret_cast<const char *>(object) + 0x18C);
		retail->m_path = pathfinder->findSafePath(object,
			*reinterpret_cast<LocomotorSet *>(reinterpret_cast<char *>( this ) + 0x1A8),
			object->getPosition(),
			&pos1, &pos2, object->getVisionRange() +
				*reinterpret_cast<const Real *>(reinterpret_cast<const char *>(aiData) + 0x60) +
				extraDistance);
		*reinterpret_cast<Int *>(reinterpret_cast<char *>(retail->m_object) + 0x18C) = 0;
		reinterpret_cast<Rva003D5620DwordSlot *>(BFME_PATH_AI->pathfinder())->set(0);
		if (g_012F0239 && g_012ED4FC)
		{
			((BFMEPathDebugLogFunction)j_0003a17a)(g_012ED4FC,
				"CritterDesync: doPathfind2 -- m_requestedDestination=%g,%g,%g",
				retail->m_requestedDestination.x, retail->m_requestedDestination.y,
				retail->m_requestedDestination.z);
		}
		return;
	}

	if (retail->m_isApproachPath &
		!reinterpret_cast<BFMEDestroyPathAIUpdate *>( this )->isDoingGroundMovement())
	{
		retail->m_isApproachPath = FALSE;
	}

	if (retail->m_isAttackPath)
	{
		Object *victim = NULL;
		if (retail->m_requestedVictimID != INVALID_ID)
		{
			victim = TheGameLogic->findObjectByID(retail->m_requestedVictimID);
		}
		if (g_012F0239 && g_012ED4FC)
		{
			((BFMEPathDebugLogFunction)j_0003a17a)(g_012ED4FC,
				"CritterDesync: doPathfind3 -- m_requestedDestination=%g,%g,%g",
				retail->m_requestedDestination.x, retail->m_requestedDestination.y,
				retail->m_requestedDestination.z);
		}
		if (((BFMEComputeAttackPathCall)j_00005637)(this, pathfinder, pathfinder, victim,
			&retail->m_requestedDestination))
		{
			if (g_012F0239 && g_012ED4FC)
			{
				((BFMEPathDebugLogFunction)j_0003a17a)(g_012ED4FC,
					"CritterDesync: doPathfind4 -- m_requestedDestination=%g,%g,%g",
					retail->m_requestedDestination.x, retail->m_requestedDestination.y,
					retail->m_requestedDestination.z);
			}
			if (retail->m_path)
			{
				BFMEPathNodeView *lastNode = *reinterpret_cast<BFMEPathNodeView **>(
					reinterpret_cast<char *>(retail->m_path) + 0x08);
				((BFMEUpdateGoalCall)j_000294e2)(TheAI->pathfinder(), retail->m_object,
					retail->m_object, &lastNode->m_position, lastNode->m_layer,
					"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Update\\AIUpdate.cpp", 0x20F);
				if (g_012F0239 && g_012ED4FC)
				{
					((BFMEPathDebugLogFunction)j_0003a17a)(g_012ED4FC,
						"CritterDesync: doPathfind5 -- m_requestedDestination=%g,%g,%g",
						retail->m_requestedDestination.x, retail->m_requestedDestination.y,
						retail->m_requestedDestination.z);
				}
			}
			retail->m_isAttackPath = TRUE;
			reinterpret_cast<Rva003D5620DwordSlot *>(BFME_PATH_AI->pathfinder())->set(0);
			if (g_012F0239 && g_012ED4FC)
			{
				((BFMEPathDebugLogFunction)j_0003a17a)(g_012ED4FC,
					"CritterDesync: doPathfind6 -- m_requestedDestination=%g,%g,%g",
					retail->m_requestedDestination.x, retail->m_requestedDestination.y,
					retail->m_requestedDestination.z);
			}
			return;
		}

		retail->m_isAttackPath = FALSE;
		if (victim)
		{
			retail->m_requestedDestination = *victim->getPosition();
			if (g_012F0239 && g_012ED4FC)
			{
				((BFMEPathDebugLogFunction)j_0003a17a)(g_012ED4FC,
					"CritterDesync: doPathfind7 -- m_requestedDestination=%g,%g,%g",
					retail->m_requestedDestination.x, retail->m_requestedDestination.y,
					retail->m_requestedDestination.z);
			}
			Object *object = retail->m_object;
			LocomotorSet *locomotor = reinterpret_cast<LocomotorSet *>(
				reinterpret_cast<char *>( this ) + 0x1A8);
			Bool adjusted = ((BFMEAdjustDestinationCall)j_00011252)(TheAI->pathfinder(),
				locomotor, object, locomotor, &retail->m_requestedDestination);
			if (g_012F0239 && g_012ED4FC)
			{
				((BFMEPathDebugLogFunction)j_0003a17a)(g_012ED4FC,
					"CritterDesync: doPathfind8 -- m_requestedDestination=%g,%g,%g",
					retail->m_requestedDestination.x, retail->m_requestedDestination.y,
					retail->m_requestedDestination.z);
			}
			ignoreObstacle(victim);
			if (!adjusted)
			{
				retail->m_isApproachPath = TRUE;
			}
		}
	}

	if (retail->m_isApproachPath)
	{
		destroyPath();
		if (g_012F0239 && g_012ED4FC)
		{
			((BFMEPathDebugLogFunction)j_0003a17a)(g_012ED4FC,
				"CritterDesync: doPathfind8.5 -- m_requestedDestination=%g,%g,%g",
				retail->m_requestedDestination.x, retail->m_requestedDestination.y,
				retail->m_requestedDestination.z);
		}
		retail->m_path = pathfinder->findClosestPath(retail->m_object,
			*reinterpret_cast<LocomotorSet *>(reinterpret_cast<char *>( this ) + 0x1A8),
			retail->m_object->getPosition(),
			&retail->m_requestedDestination, retail->m_isBlockedAndStuck, 0.05f, FALSE);
		if (g_012F0239 && g_012ED4FC)
		{
			((BFMEPathDebugLogFunction)j_0003a17a)(g_012ED4FC,
				"CritterDesync: doPathfind9 -- m_requestedDestination=%g,%g,%g",
				retail->m_requestedDestination.x, retail->m_requestedDestination.y,
				retail->m_requestedDestination.z);
		}
		if (reinterpret_cast<BFMEDestroyPathAIUpdate *>( this )->isDoingGroundMovement() && retail->m_path)
		{
			BFMEPathNodeView *lastNode = *reinterpret_cast<BFMEPathNodeView **>(
				reinterpret_cast<char *>(retail->m_path) + 0x08);
			((BFMEUpdateGoalCall)j_000294e2)(TheAI->pathfinder(), retail->m_object,
				retail->m_object, &lastNode->m_position, lastNode->m_layer,
				"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Update\\AIUpdate.cpp", 0x23C);
			if (g_012F0239 && g_012ED4FC)
			{
				((BFMEPathDebugLogFunction)j_0003a17a)(g_012ED4FC,
					"CritterDesync: doPathfind10 -- m_requestedDestination=%g,%g,%g",
					retail->m_requestedDestination.x, retail->m_requestedDestination.y,
					retail->m_requestedDestination.z);
			}
			Bool moveAllies;
			if (*reinterpret_cast<const Bool *>(reinterpret_cast<const char *>(retail->m_path) + 0x0D) &&
				!retail->m_object->isKindOf((KindOfType)0x1E))
			{
				moveAllies = TRUE;
			}
			else
			{
				moveAllies = FALSE;
			}
			Object *object = retail->m_object;
			if (object->isKindOf((KindOfType)0x6C) &&
				!*reinterpret_cast<const Bool *>(reinterpret_cast<const char *>(TheAI->getAiData()) + 0xB5))
			{
				moveAllies = FALSE;
			}
			if (reinterpret_cast<const Rva00216D20 *>(object)->field() ||
				object->isKindOf((KindOfType)0x7C))
			{
				moveAllies = TRUE;
			}
			if (!reinterpret_cast<const BFMEActionObject *>(object)->testStatus(0x38) &&
				!reinterpret_cast<const BFMEActionObject *>(object)->testStatus(0x31) &&
				!reinterpret_cast<const BFMESelectionStatusBits *>(object)->test(0x7C) &&
				moveAllies)
			{
				Pathfinder *alliesPathfinder = TheAI->pathfinder();
				char crushableLevel =
					reinterpret_cast<const BFMECrushableLevelQuery *>(object)->getCrushableLevel();
				reinterpret_cast<BFMEPathfinderMoveAllies *>(alliesPathfinder)->moveAllies(
					object, retail->m_path,
					!(crushableLevel < 4));
				if (g_012F0239 && g_012ED4FC)
				{
					((BFMEPathDebugLogFunction)j_0003a17a)(g_012ED4FC,
						"CritterDesync: doPathfind11 -- m_requestedDestination=%g,%g,%g",
						retail->m_requestedDestination.x, retail->m_requestedDestination.y,
						retail->m_requestedDestination.z);
				}
			}
		}
		reinterpret_cast<Rva003D5620DwordSlot *>(BFME_PATH_AI->pathfinder())->set(0);
		return;
	}

	if (g_012F0239 && g_012ED4FC)
	{
		((BFMEPathDebugLogFunction)j_0003a17a)(g_012ED4FC,
			"CritterDesync: ComputePath42 -- m_requestedDestination=%g,%g,%g",
			retail->m_requestedDestination.x, retail->m_requestedDestination.y,
			retail->m_requestedDestination.z);
	}
	computePath( pathfinder, &retail->m_requestedDestination );
	if (g_012F0239 && g_012ED4FC)
	{
		((BFMEPathDebugLogFunction)j_0003a17a)(g_012ED4FC,
			"CritterDesync: doPathfind12 -- m_requestedDestination=%g,%g,%g",
			retail->m_requestedDestination.x, retail->m_requestedDestination.y,
			retail->m_requestedDestination.z);
	}
	if (retail->m_isFinalGoal &&
		reinterpret_cast<BFMEDestroyPathAIUpdate *>( this )->isDoingGroundMovement() && retail->m_path)
	{
		BFMEPathNodeView *lastNode = *reinterpret_cast<BFMEPathNodeView **>(
			reinterpret_cast<char *>(retail->m_path) + 0x08);
		((BFMEUpdateGoalCall)j_000294e2)(TheAI->pathfinder(), retail->m_object,
			retail->m_object, &lastNode->m_position, lastNode->m_layer,
			"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Update\\AIUpdate.cpp", 0x26C);
		if (g_012F0239 && g_012ED4FC)
		{
			((BFMEPathDebugLogFunction)j_0003a17a)(g_012ED4FC,
				"CritterDesync: doPathfind13 -- m_requestedDestination=%g,%g,%g",
				retail->m_requestedDestination.x, retail->m_requestedDestination.y,
				retail->m_requestedDestination.z);
		}
	}
#ifdef SLEEPY_AI
	if (!retail->m_waitingForPath)
	{
		((BFMEWakeCall)j_0003611a)(this);
	}
	#endif
	reinterpret_cast<Rva003D5620DwordSlot *>(BFME_PATH_AI->pathfinder())->set(0);
}
#undef TheAI
#undef TheGameLogic
#undef g_012ED4FC
#undef g_012F0239

/* Requests a path to be found.  Note that if it is possible to do it without having to use the 
pathfinder (air units just move point to point) it generates the path immediately.  Otherwise the path
will be processed when we get to the front of the pathfind queue. jba */
//-------------------------------------------------------------------------------------------------
void AIUpdateInterface::requestPath( Coord3D *destination, Bool isFinalGoal ) 
{
	BFMEApproachPathFields *retail = reinterpret_cast<BFMEApproachPathFields *>( this );

	if (g_012F0239 && g_012ED4FC)
	{
		((BFMEPathDebugLogFunction)j_0003a17a)(g_012ED4FC,
			"CritterDesync: requestPath1-- m_requestedDestination changing from %g,%g,%g to %g,%g,%g",
			retail->m_requestedDestination.x, retail->m_requestedDestination.y,
			retail->m_requestedDestination.z, destination->x, destination->y, destination->z);
	}

	retail->m_requestedDestination = *destination;
	retail->m_isFinalGoal = isFinalGoal;

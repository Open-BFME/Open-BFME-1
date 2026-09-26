// ?computeAttackPath@AIUpdateInterface@@AAE_NPAVPathfindServicesInterface@@PBVObject@@PBUCoord3D@@@Z
// partial score=0.618 date=2026-09-26
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/iniexception /Iinputs/reference/shims/turretai /Iinputs/reference/shims/aiupdatelayout /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
// Graft this declaration block and body into AIUpdate.cpp at computeAttackPath.
extern void j_0003a391(void);
extern void j_0000b8ac(void);
extern void j_0002ceee(void);
extern void j_0003a4e5(void);
struct BFMEComputeAttackPoint { char pad[0x20]; Int m_waypointID; };
class Rva0003A391Object {};
class Rva0002E85CWeapon {};
class Rva0003A4E5Weapon {};
class Rva0000B8ACTemplate {};
class Rva0002CEEEBoundaryObject {};
struct BFMEAttackNode {
    BFMEAttackNode *m_next;
    BFMEAttackNode *m_prev;
    BFMEAttackNode *m_nextOptimized;
    Coord3D m_position;
    PathfindLayerEnum m_layer;
    BFMEAttackNode *getNext() { return m_next; }
    BFMEAttackNode *getNextOptimized() { return m_nextOptimized; }
    const Coord3D *getPosition() const { return &m_position; }
    void setNextOptimized(BFMEAttackNode *next) { reinterpret_cast<PathNode *>(this)->setNextOptimized(reinterpret_cast<PathNode *>(next)); }
};
struct BFMEAttackPath {
    char pad[4];
    BFMEAttackNode *m_first;
    BFMEAttackNode *m_last;
    Bool m_isOptimized;
    Bool m_blockedByAlly;
};
struct BFMEAttackGlobalData {
    char pad[0xA88];
    Int m_debugAI;
};
struct BFMEAttackField164 { char pad[0x164]; UnsignedInt m_field164; };
struct BFMEAttackMachineFields {
    char pad[0x30];
    void *m_machine;
    char rest[0x33B - 0x34];
    Bool m_field33B;
};
class BFMEAttackServices {
public:
    virtual void slot0() = 0;
    virtual void slot4() = 0;
    virtual Path *findAttackPath(const Object *, const LocomotorSet &, const Coord3D *,
        const Object *, const Coord3D *, const Weapon *, Bool) = 0;
};
extern void j_0001c675(void);
class BFMETerrainLayer {
public:
    PathfindLayerEnum getLayerForDestination(Object *object, const Coord3D *position) {
        typedef PathfindLayerEnum (BFMETerrainLayer::*Call)(Object *, const Coord3D *);
        union { void (*raw)(); Call member; } route = { j_0001c675 };
        return (this->*route.member)(object, position);
    }
};
class Rva00275F30TerrainLogic {
public:
    virtual void slot0() = 0;
    virtual void slot4() = 0;
    virtual void slot8() = 0;
    virtual void slotC() = 0;
    virtual void slot10() = 0;
    virtual void slot14() = 0;
    virtual void slot18() = 0;
    virtual Real getLayerHeight(Real, Real, PathfindLayerEnum, void *, Bool) const = 0;
};
inline void bfmeEnableNoSlowDown(BFMELocomotorOverride *loco) { *reinterpret_cast<UnsignedInt *>(reinterpret_cast<char *>(loco) + 0x40) |= 0x10; }
template<int N> class BFMEAttackSlots : public BFMEAttackSlots<N - 1> {
public: virtual void slot(char (*)[N]) = 0;
};
template<> class BFMEAttackSlots<0> {};
class BFMEAttackAI : public BFMEAttackSlots<123> {
public: virtual Bool isDoingGroundMovement() = 0;
};
Bool AIUpdateInterface::computeAttackPath( PathfindServicesInterface *pathServices, const Object *victim, const Coord3D* victimPos )
{
	//CRCDEBUG_LOG(("AIUpdateInterface::computeAttackPath() for object %d\n", layout->m_object->getID()));
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
			if (reinterpret_cast<BFMEAttackAI *>(this)->isDoingGroundMovement() && !victim->isSignificantlyAboveTerrain())
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
			if (reinterpret_cast<BFMEAttackAI *>(this)->isDoingGroundMovement())
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

	if (layout->m_object->isAboveTerrain() && !landBound)
	{
		weapon->computeApproachTarget(layout->m_object, victim, &localVictimPos, 0, localVictimPos);
		if (layout->m_path)
		{
			BFMEAttackNode *startNode, *closeNode = NULL;
			startNode = reinterpret_cast<BFMEAttackPath *>(layout->m_path)->m_first;
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
		layout->m_path = newInstance(Path);
		layout->m_path->prependNode( &localVictimPos, LAYER_GROUND );
		Coord3D pos = *layout->m_object->getPosition();
		pos.z = localVictimPos.z;
		layout->m_path->prependNode( &pos, LAYER_GROUND );
		reinterpret_cast<BFMEAttackPath *>(layout->m_path)->m_first->setNextOptimized(reinterpret_cast<BFMEAttackPath *>(layout->m_path)->m_first->getNext());
		if (reinterpret_cast<BFMEAttackGlobalData *>(TheWritableGlobalData)->m_debugAI==AI_DEBUG_PATHS)
		{
			TheAI->pathfinder()->setDebugPath(layout->m_path);
		}
	}
	else
	{
		destroyPath();
		TheAI->pathfinder()->setIgnoreObstacleID( (ObjectID)reinterpret_cast<BFMEAttackField164 *>(this)->m_field164 );
		Bool bfmeAttackFlag = FALSE;
		void *machine = reinterpret_cast<BFMEAttackMachineFields *>(this)->m_machine;
		if (machine) {
			void *state = *reinterpret_cast<void **>(reinterpret_cast<char *>(machine) + 0x1c);
			if (state && *reinterpret_cast<Int *>(reinterpret_cast<char *>(state) + 4) == 0x10)
				bfmeAttackFlag = reinterpret_cast<BFMEAttackMachineFields *>(this)->m_field33B;
		}
		layout->m_path = reinterpret_cast<BFMEAttackServices *>(pathServices)->findAttackPath(
			layout->m_object, *locomotorSet, layout->m_object->getPosition(),
			victim, &localVictimPos, weapon, bfmeAttackFlag);
		if (layout->m_path) {
			Coord3D goal = *reinterpret_cast<BFMEAttackPath *>(layout->m_path)->m_last->getPosition();
			if (!weapon->isGoalPosWithinAttackRange(layout->m_object, &goal, victim, &localVictimPos) && !bfmeAttackFlag) {
				Coord3D objPos = *layout->m_object->getPosition();
				goal.sub(&objPos);
				if (goal.length()<3*PATHFIND_CELL_SIZE_F) {
					destroyPath();
					TheAI->pathfinder()->adjustDestination(layout->m_object, *locomotorSet, &objPos);
					layout->m_path = pathServices->findClosestPath(layout->m_object, *locomotorSet, layout->m_object->getPosition(),
								&objPos, false, 0.2f, true );
				}
				if (layout->m_path==NULL) {
					return false;
				}
			}
			goal = *reinterpret_cast<BFMEAttackPath *>(layout->m_path)->m_last->getPosition();
			PathfindLayerEnum goalLayer = reinterpret_cast<BFMETerrainLayer *>(TheTerrainLogic)->getLayerForDestination(layout->m_object, &goal);
			((BFMEUpdateGoalCall)j_000294e2)(TheAI->pathfinder(), layout->m_object,
				layout->m_object, &goal, goalLayer,
				"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Update\\AIUpdate.cpp", 0xD84);
			Bool moveAllies;
			if (reinterpret_cast<BFMEAttackPath *>(layout->m_path)->m_blockedByAlly &&
				!layout->m_object->isKindOf((KindOfType)0x1E))
				moveAllies = TRUE;
			else
				moveAllies = FALSE;
			Object *object = layout->m_object;
			if (object->isKindOf((KindOfType)0x6C) &&
				!*reinterpret_cast<const Bool *>(reinterpret_cast<const char *>(TheAI->getAiData()) + 0xB5))
				moveAllies = FALSE;
			if (reinterpret_cast<const Rva00216D20 *>(object)->field() ||
				object->isKindOf((KindOfType)0x7C))
				moveAllies = TRUE;
			if (!reinterpret_cast<const BFMEActionObject *>(object)->testStatus(0x38) &&
				!reinterpret_cast<const BFMEActionObject *>(object)->testStatus(0x31) &&
				!reinterpret_cast<const BFMESelectionStatusBits *>(object)->test(0x7C) &&
				moveAllies)
			{
				Pathfinder *alliesPathfinder = TheAI->pathfinder();
				char crushableLevel = static_cast<char>(object->getCrushableLevel());
				reinterpret_cast<BFMEPathfinderMoveAllies *>(alliesPathfinder)->moveAllies(
					object, layout->m_path, !(crushableLevel < 4));
			}
		}
		TheAI->pathfinder()->setIgnoreObstacleID( INVALID_ID );
		if (bfmeAttackFlag) return TRUE;
	}

	layout->m_pathTimestamp = TheGameLogic->getFrame();
	layout->m_blockedFrames = 0;
	layout->m_isBlockedAndStuck = FALSE;
	if (layout->m_path)
		return TRUE;

	return FALSE;
}

// ?computeGoal@AIFollowWaypointPathState@@IAEX_N@Z
// partial score=0.19 date=2026-09-21
// at AIMoveAndTightenState::onEnter). hasNextWaypoint() is inlined here as
// the plain ALLOW_BACKTRACK form (m_currentWaypoint->getNumLinks() > 0):
// retail reads the waypoint's link count directly with no m_priorWaypoint
// check. BFME also keeps the ROTATE_OFFSETS math ZH left under an #ifdef,
// but factored out to a still-unconverted retail helper at 0x00150100
// (ILT 0x0003D104): it takes the "far" reference point (the prior waypoint,
// or plain dest if there is none), the "near" point (dest, or the next
// link's location when there is no prior waypoint), and &m_groupOffset, and
// rotates m_groupOffset in place. The gate for the whole rotation step is a
// formation id at object+0x31c (BFMEObjectFormationField, also read by
// AIMoveToPositionAndEnterState::onEnter in this file), not the
// useGroupOffsets parameter -- the parameter goes unused, matching ZH's own
// NO_ROTATE_OFFSETS build where it was already ignored.
extern void j_0003d104(void);
typedef void (__cdecl *BfmeRotateGroupOffset)(const Coord3D *farPoint, const Coord3D *nearPoint, Coord2D *groupOffset);
extern float g_bfmeDefaultBU;					///< retail 0x01075334

struct BFMEObjectFormationField
{
	unsigned char m_unreconstructed_000[0x31c];
	Int m_formationID;					///< retail this+0x31c
};

// Same drift as BfmeMoveStateFields/BfmeMoveStateObject above: the shared
// State/Object headers put m_machine and m_ai four bytes later than retail
// (this+0x20/this+0x19c vs this+0x1c/this+0x204), so getMachineOwner() and
// Object::getAI() cannot be used here -- read the retail offsets directly.
struct BFMEFollowStateMachineFields
{
	unsigned char m_unreconstructed_000[0x10];
	Object *m_owner;					///< retail this+0x10
};

struct BFMEFollowStateFields
{
	unsigned char m_unreconstructed_000[0x1c];
	BFMEFollowStateMachineFields *m_machine;		///< retail this+0x1c
};

struct BFMEFollowStateObject
{
	unsigned char m_unreconstructed_000[0x204];
	AIUpdateInterface *m_ai;				///< retail this+0x204
};

void AIFollowWaypointPathState::computeGoal(Bool useGroupOffsets)
{
	if (m_currentWaypoint == NULL)
		return;

	Object *obj = ((BFMEFollowStateFields *)this)->m_machine->m_owner;
	AIUpdateInterface *ai = ((BFMEFollowStateObject *)obj)->m_ai;
	Coord3D dest = *m_currentWaypoint->getLocation();

	m_goalLayer = LAYER_GROUND; // waypoints are always on the ground.

	ai->setPathExtraDistance(calcExtraPathDistance());
	if (m_currentWaypoint->getNumLinks() > 0) {
		// We are in the middle of a path, so don't set the final goal location yet.
		if (g_012F0239 && g_012ED4FC)
		{
			((BfmeCritterDesyncLog)j_0003a17a)(g_012ED4FC,
				"CritterDesync: setAdjustDestination(FALSE) 62");
		}
		setAdjustsDestination(false);
	} else {
		if (g_012F0239 && g_012ED4FC)
		{
			((BfmeCritterDesyncLog)j_0003a17a)(g_012ED4FC,
				"CritterDesync: setAdjustDestination(TRUE) 63");
		}
		setAdjustsDestination(true);
		// urg. hacky. if we are a projectile on the last segment, turn on precise z-pos.
		if (obj->isKindOf(KINDOF_PROJECTILE))
		{
			if (ai && ai->getCurLocomotor())
				ai->getCurLocomotor()->setUsePreciseZPos(true);
		}
	}

	if (((BFMEObjectFormationField *)obj)->m_formationID)
	{
		Coord3D nearPoint = dest;
		nearPoint.x -= g_bfmeDefaultBU;
		Coord3D farPoint;
		const Waypoint *nextLink = m_currentWaypoint->getLink(0);
		if (m_priorWaypoint) {
			farPoint = *m_priorWaypoint->getLocation();
		} else if (nextLink) {
			nearPoint = dest;
			farPoint = *nextLink->getLocation();
		}
		if (m_priorWaypoint || nextLink) {
			((BfmeRotateGroupOffset)j_0003d104)(&farPoint, &nearPoint, &m_groupOffset);
		}
	}

	m_goalPosition = dest;
	m_goalPosition.x += m_groupOffset.x;
	m_goalPosition.y += m_groupOffset.y;
	m_goalPosition.z = TheTerrainLogic->getGroundHeight(m_goalPosition.x, m_goalPosition.y);

	Region3D extent;
	TheTerrainLogic->getMaximumPathfindExtent(&extent);

	if (extent.isInRegionNoZ(&dest)) {
		// The waypoint is on the map.  Check & see if the adjusted position is off map [8/28/2003]
		if (!extent.isInRegionNoZ(&m_goalPosition)) {
			// clamp to in region. [8/28/2003]
			if (m_goalPosition.x < extent.lo.x+PATHFIND_CELL_SIZE_F) {
				m_goalPosition.x = extent.lo.x+PATHFIND_CELL_SIZE_F;
			}
			if (m_goalPosition.y < extent.lo.y+PATHFIND_CELL_SIZE_F) {
				m_goalPosition.y = extent.lo.y+PATHFIND_CELL_SIZE_F;
			}
			if (m_goalPosition.x > extent.hi.x-PATHFIND_CELL_SIZE_F) {
				m_goalPosition.x = extent.hi.x-PATHFIND_CELL_SIZE_F;
			}
			if (m_goalPosition.y > extent.hi.y-PATHFIND_CELL_SIZE_F) {
				m_goalPosition.y = extent.hi.y-PATHFIND_CELL_SIZE_F;
			}
		}
	}

	if (!extent.isInRegionNoZ(&m_goalPosition)) {
		if (g_012F0239 && g_012ED4FC)
		{
			((BfmeCritterDesyncLog)j_0003a17a)(g_012ED4FC,
				"CritterDesync: setAdjustDestination(FALSE) 64");
		}
		setAdjustsDestination(false); // moving off the map.
		ai->getCurLocomotor()->setAllowInvalidPosition(true); // allow it to move off the map.
		m_appendGoalPosition = true; // Moving off the map.
	}
}

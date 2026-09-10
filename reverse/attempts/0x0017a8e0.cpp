// ?onEnter@AIFollowWaypointPathState@@UAE?AW4StateReturnType@@XZ
// partial score=0.42 date=2026-09-10
// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /MD /EHsc
// BFME retail 0x0017A8E0: AIFollowWaypointPathState::onEnter (622 bytes).
//
// This TU deliberately carries a measured BFME view of the state and its
// callees.  The shared Zero Hour declarations put several of these fields at
// different offsets, while the retail body reads the BFME state at +0x1c,
// +0x24, +0x30 and +0x4c and the waypoint state at +0x50..+0x69.

typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef float Real;

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

enum KindOfType
{
	KINDOF_PROJECTILE = 0x19
};

struct Coord2D
{
	Real x;
	Real y;
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Object;
class Team;
class Waypoint;
class Rva0017A8E0AIGroup;
class Rva0017A8E0AIUpdateInterface;
class Locomotor;
class LocomotorSet;
class Rva0017A8E0Pathfinder;

template <int N>
class AIUpdateVirtualSlots : public AIUpdateVirtualSlots<N - 1>
{
public:
	virtual void unusedSlot(char (*)[N]);
};

template <>
class AIUpdateVirtualSlots<0>
{
};

class Rva0017A8E0StateMachine
{
public:
	void setGoalPosition(const Coord3D *position);

	Object *getOwner() const
	{
		return m_owner;
	}

	const Waypoint *getGoalWaypoint() const
	{
		return m_goalWaypoint;
	}

private:
	unsigned char m_pad00[0x10];
	Object *m_owner;
	unsigned char m_pad14[0x3c];
	const Waypoint *m_goalWaypoint;
};

class Rva0017A8E0Thing
{
public:
	Bool isKindOf(KindOfType kind) const;
};

class Object : public Rva0017A8E0Thing
{
public:
	Rva0017A8E0AIUpdateInterface *getAI() const
	{
		return m_ai;
	}

	const Coord3D *getPosition() const
	{
		return &m_position;
	}

	Team *getTeam() const
	{
		return m_team;
	}

private:
	unsigned char m_pad00[0x38];
	Coord3D m_position;
	unsigned char m_pad44[0x1c0];
	Rva0017A8E0AIUpdateInterface *m_ai;
	unsigned char m_pad208[0x34];
	Team *m_team;
};

class Team
{
public:
	void setCurrentWaypoint(const Waypoint *waypoint)
	{
		m_currentWaypoint = waypoint;
	}

	const Waypoint *getCurrentWaypoint() const
	{
		return m_currentWaypoint;
	}

private:
	unsigned char m_pad00[0x40];
	const Waypoint *m_currentWaypoint;
};

class Waypoint
{
public:
	const Coord3D *getLocation() const
	{
		return &m_location;
	}

	int getNumLinks() const
	{
		return m_numLinks;
	}

private:
	void *m_vftable;
	int m_id;
	void *m_name;
	Coord3D m_location;
	unsigned char m_pad18[0x20];
	unsigned char m_pad38[0x14];
	int m_numLinks;
};

class Rva0017A8E0AIGroup
{
public:
	Real getSpeed();
	Bool getCenter(Coord3D *center);
};

class LocomotorSet
{
};

class Rva0017A8E0AIUpdateInterface : public AIUpdateVirtualSlots<123>
{
public:
	Rva0017A8E0AIGroup *getGroup();
	void setDesiredSpeed(Real speed);
	void setPathExtraDistance(Real distance);
	virtual Bool isDoingGroundMovement() const;

	const LocomotorSet &getLocomotorSet() const
	{
		return *(const LocomotorSet *)((const unsigned char *)this + 0x1a8);
	}

	Locomotor *getCurLocomotor() const
	{
		return *(Locomotor **)((const unsigned char *)this + 0x1cc);
	}
};

class AI
{
public:
	Rva0017A8E0Pathfinder *pathfinder() const
	{
		return m_pathfinder;
	}

private:
	unsigned char m_pad00[0x0c];
	Rva0017A8E0Pathfinder *m_pathfinder;
};

class Rva0017A8E0Pathfinder
{
public:
	Bool adjustDestination(Object *object, const LocomotorSet &locomotorSet,
		Coord3D *destination, const Coord3D *groupDestination);
	void updateGoal(Object *object, const Coord3D *destination, int layer,
		const char *source, int line);
};

class Locomotor
{
public:
	void setUsePreciseZPos()
	{
		*(UnsignedInt *)((unsigned char *)this + 0x40) |= 8;
	}
};

class Rva0017A8E0AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
	Bool getAdjustsDestination() const;

protected:
	unsigned char m_pad04[0x18];
	Rva0017A8E0StateMachine *m_machine;
	unsigned char m_pad20[4];
	Coord3D m_goalPosition;
	int m_goalLayer;
	unsigned char m_pad34[0x18];
	Bool m_adjustDestinations;
};

class AIFollowWaypointPathState : public Rva0017A8E0AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();

protected:
	void computeGoal(Bool useGroupOffsets);
	Real calcExtraPathDistance();

	Coord2D m_groupOffset;
	Real m_angle;
	int m_framesSleeping;
	const Waypoint *m_currentWaypoint;
	const Waypoint *m_priorWaypoint;
	Bool m_appendGoalPosition;
	Bool m_moveAsGroup;
	Bool m_isFollowWaypointPathState;
};

extern AI *TheAI;
extern unsigned char g_012F0239;
extern void *g_012ED4FC;
extern "C" void __cdecl bfmeRetailCritterDesyncLog(void *, const char *, ...);

static const Real FAST_AS_POSSIBLE = 999999.0f;

StateReturnType AIFollowWaypointPathState::onEnter()
{
	m_appendGoalPosition = 0;
	m_priorWaypoint = 0;
	m_currentWaypoint = m_machine->getGoalWaypoint();
	Rva0017A8E0AIUpdateInterface *ai = m_machine->getOwner()->getAI();

	if (m_currentWaypoint == 0 && !m_moveAsGroup)
		return STATE_FAILURE;

	m_machine->setGoalPosition(m_currentWaypoint->getLocation());
	m_framesSleeping = 0;
	m_groupOffset.x = 0.0f;
	m_groupOffset.y = 0.0f;

	Object *object = m_machine->getOwner();
	Real speed = FAST_AS_POSSIBLE;
	if (m_moveAsGroup && m_currentWaypoint != 0)
	{
		object->getTeam()->setCurrentWaypoint(m_currentWaypoint);
		Rva0017A8E0AIGroup *group = ai->getGroup();
		if (group != 0)
		{
			speed = group->getSpeed();
			Coord3D center;
			group->getCenter(&center);
			m_groupOffset.x = object->getPosition()->x - center.x;
			m_groupOffset.y = object->getPosition()->y - center.y;
		}
	}
	if (m_currentWaypoint == 0 && m_moveAsGroup)
		m_currentWaypoint = object->getTeam()->getCurrentWaypoint();

	computeGoal(m_moveAsGroup);
	StateReturnType result = Rva0017A8E0AIInternalMoveToState::onEnter();
	ai->setDesiredSpeed(speed);
	ai->setPathExtraDistance(calcExtraPathDistance());

	if (m_currentWaypoint != 0 && m_currentWaypoint->getNumLinks() > 0)
	{
		if (g_012F0239 && g_012ED4FC)
			bfmeRetailCritterDesyncLog(g_012ED4FC,
				(const char *)0x01099FF0);
		m_adjustDestinations = 0;
	}
	else
	{
		Bool adjusts = ai->isDoingGroundMovement();
		if (g_012F0239 && g_012ED4FC)
			bfmeRetailCritterDesyncLog(g_012ED4FC,
				(const char *)0x01099F98,
				adjusts ? (const char *)0x0107FA58 : (const char *)0x01080180);
		m_adjustDestinations = adjusts;
		if (getAdjustsDestination())
		{
			if (!TheAI->pathfinder()->adjustDestination(
				m_machine->getOwner(), ai->getLocomotorSet(), &m_goalPosition, 0))
				return STATE_FAILURE;
			TheAI->pathfinder()->updateGoal(m_machine->getOwner(), &m_goalPosition,
				m_goalLayer, (const char *)0x0109769C, 0x23B6);
		}
		if (object->isKindOf(KINDOF_PROJECTILE))
		{
			Locomotor *locomotor = ai->getCurLocomotor();
			if (locomotor != 0)
				locomotor->setUsePreciseZPos();
		}
	}
	return result;
}

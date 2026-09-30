// ?onEnter@AIFollowWaypointPathState@@UAE?AW4StateReturnType@@XZ
// partial score=0.9839 date=2026-09-30
// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /MD /EHsc
//
// The constructor at 0x0017F980 installs vtable 0x0109A7B0.
// Slot +0x10 points to ILT RVA 0x000306BB, which jumps to 0x0017A8E0.
// The Open-BFME5 lift dated 2026-08-11 uses this name for the same body.

// This translation unit declares the measured BFME layout and callee signatures.
// The shared Zero Hour declarations place several members at different offsets.
// This body reads the
// BFME state at +0x1c (machine), +0x24 (goal position), +0x30 (goal layer),
// +0x4c (adjusts-destination flag) and +0x50..+0x69 (the waypoint fields),
// the AIUpdateInterface at +0x1a8/+0x1cc, and the owner Object at +0x38
// (position), +0x204 (AI), +0x23c (team).

// Two behaviours here have no Zero Hour counterpart and are reproduced from
// the disassembly alone:
//   * the formation offset may be taken from owner+0x320/+0x324 behind the
//     owner+0x31c condition instead of from AIGroup::getCenter, and
//   * the offset taken from the group centre is shortened to 150.0f whenever it
//     is LONGER than that: retail's `fdivr m32fp` is ST(0) <- m32fp / ST(0), so
//     the constant is the numerator and the guard is `length > 150.0f`, which is
//     the only spelling that emits retail's `test ah, 0x41 / jne`.  150.0f is a
//     .rdata float with no ledger name (0x0109A028), so it is declared here
//     under an address-derived name.

// The 0x31c/0x320/0x324 owner fields are read by exactly one body in the image
// (AIMoveToPositionAndEnterState::onEnter tests 0x31c alone) and written by no
// body at all, so they keep address-derived names rather than invented ones.

// The body shape follows GeneralsMD/Code/GameEngine/Source/GameLogic/AI/
// AIStates.cpp:4050-4096 (AIFollowWaypointPathState::onEnter) as written there:
// `Real speed` is declared at the middle of the body, not at the top, and
// `StateReturnType ret` is initialised in place after computeGoal().

// MEASURED RESIDUE, 10 bytes (probe: 10 non-reloc, shape 1.000, 622/622):
//   1. Frame. Retail reserves 16 bytes; this source reserves 20. Its /FAsc
//      table names `_speed$ = -20`, `_ret$ = -16`, and `_center$2615 = -12`.
//      Those negative offsets show that this source gives each value a local
//      slot. The table shows no reused positive incoming-argument slot. Moving
//      and scoping speed, ret, and center did not reduce the frame. A union
//      overlay reduced the frame to 16 bytes and introduced 192 byte differences.
//      A reference return did not reduce the frame. Deleting ret or speed did,
//      but neither version preserves the complete body.

//   2. x87 order. Retail loads m_groupOffset.x, then m_groupOffset.y. This
//      source reads x through a volatile pointer before the sum. MSVC then loads
//      x before y, which cuts two differences from the previous 12-byte result.
//      Source order, aliases, temporaries, Length2(), and __forceinline sqrt
//      did not change the load order.

// The remaining differences come from frame allocation. The instruction shapes
// match after register and constant names are normalised.

#include <math.h>

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
	unsigned char m_pad240[0xdc];

public:
	// The formation-offset gate and the Coord2D pair it guards.  Both are
	// unnamed in the ledger and unwritten anywhere in the image, so they keep
	// address-derived names.  Retail moves the pair as two dwords, which is
	// what a Coord2D copy compiles to.
	UnsignedInt m_rva0000031C;
	Coord2D m_rva00000320;
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

// BFME's Waypoint carries its link table at +0x4c and its location at +0xc;
// both offsets are read by the byte-exact calcExtraPathDistance sibling.
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

	Object *getMachineOwner() const
	{
		return m_machine->getOwner();
	}

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
extern Bool Glo012F0239;
extern void *TheCRCParameterCheck;
// 0x0109A028, the .rdata float 150.0f this body compares against and divides
// by.  The ledger names no symbol there, so the name carries the address.
extern const Real g_bfmeRva0109A028;
// The two-argument and three-argument DEBUG_LOG printer behind the
// "CritterDesync:" literals.  Callee 0x00043A17A is an unnamed thunk in the
// ledger; both strings below are read straight out of the retail image.
extern "C" void __cdecl BfmeDebugLogPrint(void *parameterCheck, const char *format, ...);

static const Real FAST_AS_POSSIBLE = 999999.0f;

// A float-taking sqrt wrapper, as the byte-exact TerrainLogicSetWaterHeight
// sibling does: the (float) cast keeps the whole computation in single
// precision, which is what produces the bare fsqrt.
static inline Real bfmeSqrt(Real value)
{
	return (Real)sqrt(value);
}

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
	// Retail clears y before x here; the order is in the bytes.
	m_groupOffset.y = 0.0f;
	m_groupOffset.x = 0.0f;

	// -- MIDDLE --
	Object *object = m_machine->getOwner();
	Real speed = FAST_AS_POSSIBLE;
	if (m_moveAsGroup && m_currentWaypoint != 0)
	{
			Coord3D center;
		object->getTeam()->setCurrentWaypoint(m_currentWaypoint);
		if (object->m_rva0000031C != 0)
		{
			center.x = object->m_rva00000320.x;
			center.y = object->m_rva00000320.y;
			*(Coord2D *)&m_groupOffset = *(const Coord2D *)&center;
		}
		else
		{
			Rva0017A8E0AIGroup *group = ai->getGroup();
			if (group != 0)
			{
				speed = group->getSpeed();
				group->getCenter(&center);
				m_groupOffset.x = object->getPosition()->x - center.x;
				m_groupOffset.y = object->getPosition()->y - center.y;
				const Coord2D &off = m_groupOffset;
				Real x = *(const volatile Real *)&off.x;
				Real length = bfmeSqrt(x * x + off.y * off.y);
				if (length > g_bfmeRva0109A028)
				{
					Real scale = g_bfmeRva0109A028 / length;
					m_groupOffset.x = m_groupOffset.x * scale;
					m_groupOffset.y = m_groupOffset.y * scale;
				}
			}
		}
	}
	if (m_currentWaypoint == 0 && m_moveAsGroup)
		m_currentWaypoint = object->getTeam()->getCurrentWaypoint();

	// -- TAIL --
	// set initial movement goal
	computeGoal(m_moveAsGroup);
	StateReturnType ret = Rva0017A8E0AIInternalMoveToState::onEnter();
	ai->setDesiredSpeed(speed);
	// AIInternalMoveToState::onEnter resets the extra path distance.
	ai->setPathExtraDistance(calcExtraPathDistance());

	if (m_currentWaypoint->getNumLinks() > 0)
	{
		if (Glo012F0239 && TheCRCParameterCheck)
			BfmeDebugLogPrint(TheCRCParameterCheck,
				"CritterDesync: setAdjustDestination(FALSE) 54");
		m_adjustDestinations = 0;
	}
	else
	{
		// Retail evaluates isDoingGroundMovement() once for the log and again
		// for the store, in that order.
		if (Glo012F0239 && TheCRCParameterCheck)
			BfmeDebugLogPrint(TheCRCParameterCheck,
				"CritterDesync: setAdjustDestination(ai->isDoingGroundMovement()=%s) 55",
				ai->isDoingGroundMovement() ? "TRUE" : "FALSE");
		m_adjustDestinations = ai->isDoingGroundMovement();
		if (getAdjustsDestination())
		{
			if (!TheAI->pathfinder()->adjustDestination(getMachineOwner(),
				ai->getLocomotorSet(), &m_goalPosition, 0))
				return STATE_FAILURE;
			TheAI->pathfinder()->updateGoal(getMachineOwner(), &m_goalPosition,
				m_goalLayer, "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Ai\\AIStates.cpp", 9142);
		}
		// urg. hacky. if we are a projectile on the last segment, turn on precise z-pos.
		if (object->isKindOf(KINDOF_PROJECTILE))
		{
			Locomotor *locomotor = ai->getCurLocomotor();
			if (locomotor != 0)
				locomotor->setUsePreciseZPos();
		}
	}
	return ret;

}

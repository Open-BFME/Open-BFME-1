// ?onEnter@AIFollowWaypointPathState@@UAE?AW4StateReturnType@@XZ
// partial score=0.98 date=2026-09-28
// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /MD /EHsc
//
// BFME retail 0x0017A8E0, 622 bytes.  The identity is proven, not guessed: the
// constructor at 0x0017F980 installs vtable VA 0x0109A7B0, its slot +0x10 holds
// the ILT thunk at RVA 0x000306BB, and that thunk's E9 target is 0x0017A8E0.
// The 2026-08-11 Open-BFME5 lift carried the name with the dump, so this is a
// real body under a real name rather than an opaque address-keyed one.
//
// This TU is deliberately self-contained: it carries a measured BFME view of
// the state and of every callee it touches.  The shared Zero Hour declarations
// put several of these members at different offsets, while this body reads the
// BFME state at +0x1c (machine), +0x24 (goal position), +0x30 (goal layer),
// +0x4c (adjusts-destination flag) and +0x50..+0x69 (the waypoint-path block),
// the AIUpdateInterface at +0x1a8/+0x1cc, and the owner Object at +0x38
// (position), +0x204 (AI), +0x23c (team).
//
// Two behaviours here have no Zero Hour counterpart and are reproduced from
// the disassembly alone:
//   * the formation offset may be taken from owner+0x320/+0x324 behind the
//     owner+0x31c gate instead of from AIGroup::getCenter, and
//   * the offset taken from the group centre is shortened to 150.0f whenever it
//     is LONGER than that: retail's `fdivr m32fp` is ST(0) <- m32fp / ST(0), so
//     the constant is the numerator and the guard is `length > 150.0f`, which is
//     the only spelling that emits retail's `test ah, 0x41 / jne`.  150.0f is a
//     .rdata float with no ledger name (0x0109A028), so it is declared here
//     under an address-derived name.
// The 0x31c/0x320/0x324 owner fields are read by exactly one body in the image
// (AIMoveToPositionAndEnterState::onEnter tests 0x31c alone) and written by no
// body at all, so they keep address-derived names rather than invented ones.
//
// The body shape follows GeneralsMD/Code/GameEngine/Source/GameLogic/AI/
// AIStates.cpp:4050-4096 (AIFollowWaypointPathState::onEnter) as written there:
// `Real speed` is declared at the middle of the body, not at the top, and
// `StateReturnType ret` is initialised in place after computeGoal().
//
// MEASURED RESIDUE, 9 bytes (probe: 12 non-reloc, shape 1.000, 622/622):
//   1. Frame.  Retail's `sub esp, 0x10` is four dwords and holds `speed` at
//      E-0x10 plus the three dwords of `Coord3D center` at E-0xc..E-0x4; the
//      value of `ret` is spilled onto a DEAD slot (written at E-0x10, re-read at
//      E-0xc), so retail's `ret` has no frame slot of its own.  Every spelling
//      tried here gives `ret` a slot and a 0x14 frame: `ret` at the top of the
//      body, `ret` block-scoped around the whole tail, `ret` block-scoped with
//      `speed` in an enclosing block, `speed` block-scoped so it could overlay
//      `ret`, `center` at function scope, every declaration permutation of
//      {speed, ret, center}, and `int ret` instead of the enum.  Deleting `ret`
//      alone gives 0x10 (as does deleting `speed` alone), which is what fixes the
//      diagnosis: retail must have carried the base result as a compiler `$T`
//      temporary rather than as a user local, and no C++ spelling of
//      `StateReturnType ret = base::onEnter();` that survives the 0x13e/0x143
//      call order produces one.
//   2. x87 operand order in the length.  Retail loads m_groupOffset.x and then
//      m_groupOffset.y into the square pair; this build always loads y first.
//      MSVC 7.1 canonicalises the commutative sum, so the source order does not
//      reach it: `x*x + y*y`, `y*y + x*x`, a swapped-member alias struct, a
//      `Real *` alias, a `Coord2D::Length2()` member, a free inline helper, named
//      product temporaries, an accumulating `len2`, parenthesised products,
//      individual `const Real &` member references, a by-value copy and a
//      __forceinline sqrt were all measured and all still load y first.  It is
//      compiler-internal in this build.
// Both residues are register/stack-slot ALLOCATION only: once registers and
// constants are normalised the two bodies are instruction-identical, and the
// `sub/add esp` bytes are the frame-size consequence, not a separate fault.

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
				Real length = bfmeSqrt(off.y * off.y + off.x * off.x);
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

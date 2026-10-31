// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// GiantBirdSwoopState::update, retail RVA 0x002C3550 (689 B, RET at
// 0x002C3800).  Constructor 0x002BE230 installs vtable 0x010C7868; its slots 4
// and 5 reach the matched onEnter 0x002C3020 and onExit 0x002BE320, and slot 6
// thunk 0x00446A92 jumps here (update, as in sibling vtable 0x010C78D8).  The
// class name is the only one of 979 ledger/combinatorial candidates whose
// update, onEnter and onExit decorations all fit retail's ILT windows
// (tools/ilt_oracle.py); the older rows spell it AIGiantBirdSwoopState.
// The state damps the owner's goal speed, routes toward its goal, and snaps
// the owner onto the goal position once in range.
// Retail loads the goal range and copies the goal position word by word in
// source order; the volatile word copies keep that load/store schedule.
// update calls the goal re-acquire helper 0x002C38B0 defined below.

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

#include "../../../../../../Libraries/Include/Lib/Coord3D.h"
#include <math.h>

extern void j_000309f4(void);

class GeometryInfo
{
public:
	GeometryInfo(const GeometryInfo &source);
	// ??1Rva000FFCA0@@QAE@XZ
	~GeometryInfo()
	{
		typedef void (__fastcall *DestroyCall)(GeometryInfo *);
		((DestroyCall)j_000309f4)(this);
	}
	__forceinline Real radius() const
	{
		return m_radius10;
	}

	void *m_vtable;
	unsigned char m_body[0x0c];
	Real m_radius10;
	unsigned char m_tail[0x48];
};

class Object;

class BfmeModelConditionFlags
{
public:
	enum Init
	{
		K_INIT = 0
	};

	BfmeModelConditionFlags(Init, unsigned int bit)
	{
		m_bits[4] = 1u << bit;
	}

	~BfmeModelConditionFlags()
	{
	}

	bool testForAny(const BfmeModelConditionFlags &that) const
	{
		return (m_bits[4] & that.m_bits[4]) != 0;
	}

	void setAny(const BfmeModelConditionFlags &that)
	{
		m_bits[4] |= that.m_bits[4];
	}

	unsigned int m_bits[5];
};

class Locomotor
{
public:
	unsigned char m_unreconstructed00[0x44];
	Real m_height44;
};

class AIUpdateInterface
{
public:
	Bool findNearestLabeledContactPointOnTarget(Object *target,
		Coord3D *pointOut, const Coord3D *callerPos, Bool flag);
	Bool testFlag3f0(Int bit) const { return (m_flags3f0 >> bit) & 1; }

	unsigned char m_unreconstructed000[0x1cc];
	Locomotor *m_curLocomotor;
	unsigned char m_unreconstructed1d0[0x3f0 - 0x1d0];
	UnsignedInt m_flags3f0;
	unsigned char m_unreconstructed3f4[4];
	UnsignedInt m_goalObjectID3f8;
	unsigned char m_unreconstructed3fc[0x424 - 0x3fc];
	bool m_isMoving424;
	unsigned char m_unreconstructed425[0x46c - 0x425];
	unsigned char m_flag46c;
	unsigned char m_unreconstructed46d[3];
	Real m_goalRange470;
	unsigned char m_unreconstructed474[8];
	Coord3D m_goalPosition47c;
	unsigned char m_unreconstructed488[0x494 - 0x488];
	Int m_mode494;
};

class Object
{
public:
	unsigned char m_unreconstructed000[0x38];
	Coord3D m_position38;
	unsigned char m_unreconstructed044[0x94 - 0x44];
	UnsignedInt m_status94;
	unsigned char m_unreconstructed098[0xac - 0x98];
	Bool getWorldspaceBestContactPoint(Coord3D *pointOut,
		const Coord3D *callerPos, const char *preferredPoint, Int arg4,
		Int seed, Bool skipCollideTest) const;
	void notifyModelConditionChanged();

	GeometryInfo m_geometryInfoAC;
	unsigned char m_unreconstructed108[0x110 - 0x108];
	BfmeModelConditionFlags m_modelConditionFlags;
	unsigned char m_unreconstructed124[0x204 - 0x124];
	AIUpdateInterface *m_ai;
	unsigned char m_unreconstructed208[0x344 - 0x208];
	unsigned char m_privateStatus;
};

class StateMachine
{
public:
	void setGoalPosition(const Coord3D *pos);

	unsigned char m_unreconstructed00[0x10];
	Object *m_owner;
};

class GameLogic
{
public:
	Object *findObjectByID(Int id);
};
extern GameLogic *TheGameLogic;

class TerrainLogic
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal);
};
extern TerrainLogic *TheTerrainLogic;

class Rva002BC260GoalOwner
{
public:
	void run(void *arg1, void *arg2, void *arg3, unsigned char arg4);
};
extern int g_012F02D4;
extern int g_Rva012F02DC;
Int GetGameLogicRandomValue(Int lo, Int hi, char *file, Int line);

extern void j_0001f253();
extern void j_00018e8a();
extern void j_00017607();
extern void j_0003daa5();
extern void j_0003ab20();
extern void j_00029e88();
extern void j_00008a26();
extern void j_0003a1a7();

struct GiantBirdSwoopStateCall
{
	Object *findObjectByID(UnsignedInt id);
	Int chooseGoal(Real height, bool fullRange);
	bool isMobile() const;
	Real getCurLocomotorSpeed();
	bool testStatus(Int bit) const;
	void routeToGoal(Real height, Coord3D *goal, Int source);
	Real getDistanceSquared(const Coord3D *position) const;
	void setPosition(const Coord3D *position);
};

template <class T>
static __forceinline T giantBirdSwoopMember(void (*raw)())
{
	union
	{
		void (*asRaw)();
		T asMember;
	} cast;
	cast.asRaw = raw;
	return cast.asMember;
}

class State
{
public:
	virtual void unused00() = 0;

	Int m_id;
	Int m_successStateID;
	Int m_failureStateID;
	void *m_transitions[3];
	StateMachine *m_machine;
};

class GiantBirdSwoopState : public State
{
public:
	virtual StateReturnType update();
	void rva002C38B0(Bool force);

	unsigned char m_unreconstructed20[8];
	Coord3D m_goal28;
	bool m_chooseGoal34;
	unsigned char m_unreconstructed35[7];
	Real m_damping3C;
};

static __forceinline Real giantBirdSwoopLength(const Coord3D &p)
{
	return (Real)sqrt(p.x * p.x + p.y * p.y + p.z * p.z);
}

// Retail 0x002C38B0 (578 B, thiscall, ret 4), reached from update through
// ILT 0x000163D3.  Re-acquires the victim's contact point, sets model
// condition bit 0x20000 near the victim and retargets the swoop goal once it
// has moved far enough (or when forced).  Control flow follows the BFME 2
// donor AIGiantBirdSwoopState::rva0036C438 (open-bfme-2
// Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/
// AIGiantBirdSwoopStateOnEnter.cpp), without BFME 2's weapon-target path,
// which BFME 1's body does not have.
void GiantBirdSwoopState::rva002C38B0(Bool force)
{
	Object *owner = m_machine->m_owner;
	AIUpdateInterface *ai = owner->m_ai;
	if (owner->m_modelConditionFlags.m_bits[4] & 0x20000)
	{
		owner->m_modelConditionFlags.m_bits[4] &= ~0x20000;
		owner->notifyModelConditionChanged();
	}
	if (ai == 0)
		return;
	Object *victim = TheGameLogic->findObjectByID(ai->m_goalObjectID3f8);
	if (victim == 0)
		return;

	Coord3D pos;
	const Coord3D *ownerPos = &owner->m_position38;
	if (!ai->findNearestLabeledContactPointOnTarget(victim, &pos, ownerPos, false))
	{
#line 622 "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Update\\AIUpdate\\GiantBirdAIUpdate.cpp"
		victim->getWorldspaceBestContactPoint(&pos, ownerPos, 0, 1,
			GetGameLogicRandomValue(0, 12345678, __FILE__, __LINE__), false);
	}

	const Coord3D *goal = &m_goal28;
	Coord3D delta;
	delta.x = pos.x - goal->x;
	delta.y = pos.y - goal->y;
	delta.z = pos.z - goal->z;
	Real moved = giantBirdSwoopLength(delta);
	delta = pos;
	delta.x -= ownerPos->x;
	delta.y -= ownerPos->y;
	delta.z -= ownerPos->z;
	Real range = giantBirdSwoopLength(delta);

	if (ai->m_goalRange470 * 4.0f > range)
	{
		BfmeModelConditionFlags nearMask(BfmeModelConditionFlags::K_INIT, 17);
		if (!owner->m_modelConditionFlags.testForAny(nearMask))
		{
			owner->m_modelConditionFlags.setAny(nearMask);
			owner->notifyModelConditionChanged();
		}
	}

	if (moved > 10.0f || force)
	{
		Real near8 = ai->m_goalRange470 * 8.0f;
		if (range < near8 || moved > near8 || force)
		{
			m_goal28 = pos;
			if (ai->m_mode494 == 0)
			{
				Locomotor *locomotor = ai->m_curLocomotor;
				if (locomotor != 0)
				{
					m_goal28.z = TheTerrainLogic->getGroundHeight(m_goal28.x, m_goal28.y, 0) + locomotor->m_height44;
					m_machine->setGoalPosition(&m_goal28);
				}
			}
			if (ai->testFlag3f0(2) || ai->testFlag3f0(3))
				((Rva002BC260GoalOwner *)ai)->run(&m_goal28, &g_Rva012F02DC, 0, 0);
			else
				((Rva002BC260GoalOwner *)ai)->run(&m_goal28, &g_012F02D4, 0, 0);
		}
	}
}

static __forceinline Real giantBirdSwoopLengthSquared(const Coord3D &p)
{
	return p.x * p.x + p.y * p.y + p.z * p.z;
}

StateReturnType GiantBirdSwoopState::update()
{
	Object *owner = m_machine->m_owner;
	if (owner->m_privateStatus & 1)
		return STATE_FAILURE;
	AIUpdateInterface *ai = owner->m_ai;
	if (!ai)
		return STATE_FAILURE;
	typedef Object *(GiantBirdSwoopStateCall::*FindObjectByIDCall)(UnsignedInt);
	UnsignedInt objectID = ai->m_goalObjectID3f8;
	Object *target = ((GiantBirdSwoopStateCall *)TheGameLogic->*giantBirdSwoopMember<FindObjectByIDCall>(j_0001f253))(objectID);
	if (target && !(target->m_status94 & 0x08000000))
	{
		if (target->m_privateStatus & 1)
			return STATE_SUCCESS;
		Real speed = (1.0f - m_damping3C) * ai->m_goalRange470;
		m_damping3C *= 0.8f;
		ai->m_goalRange470 = speed;
		rva002C38B0(false);
		if (m_chooseGoal34)
		{
			typedef Int (GiantBirdSwoopStateCall::*ChooseGoalCall)(Real, bool);
			if (((GiantBirdSwoopStateCall *)ai->*giantBirdSwoopMember<ChooseGoalCall>(j_00018e8a))(-5.0f, 1) == 1)
				return STATE_SUCCESS;
		}
		else
		{
			typedef bool (GiantBirdSwoopStateCall::*IsMobileCall)() const;
			typedef Real (GiantBirdSwoopStateCall::*GetSpeedCall)();
			bool still = !((const GiantBirdSwoopStateCall *)target->*giantBirdSwoopMember<IsMobileCall>(j_00017607))()
				|| (target->m_ai && ((GiantBirdSwoopStateCall *)target->m_ai->*giantBirdSwoopMember<GetSpeedCall>(j_0003daa5))() <= 0.0f);
			typedef bool (GiantBirdSwoopStateCall::*TestStatusCall)(Int) const;
			if (!((const GiantBirdSwoopStateCall *)owner->*giantBirdSwoopMember<TestStatusCall>(j_0003ab20))(0x91) || !still)
			{
				typedef void (GiantBirdSwoopStateCall::*RouteToGoalCall)(Real, Coord3D *, Int);
				((GiantBirdSwoopStateCall *)ai->*giantBirdSwoopMember<RouteToGoalCall>(j_00029e88))(5.0f, &m_goal28, 0);
			}
		}
		if (!ai->m_isMoving424)
			return STATE_FAILURE;
		GeometryInfo geometry(owner->m_geometryInfoAC);
		Coord3D delta;
		delta.x = m_goal28.x - owner->m_position38.x;
		delta.y = m_goal28.y - owner->m_position38.y;
		delta.z = m_goal28.z - owner->m_position38.z;
		Real distanceSquared = giantBirdSwoopLengthSquared(delta);
		Real radius = geometry.radius();
		if (distanceSquared < radius * geometry.radius() * 0.5f)
			rva002C38B0(true);
		Real range;
		*(Int *)&range = *(volatile Int *)&ai->m_goalRange470;
		Coord3D next;
		*(volatile Int *)&next.x = *(volatile Int *)&ai->m_goalPosition47c.x;
		*(volatile Int *)&next.y = *(volatile Int *)&ai->m_goalPosition47c.y;
		*(volatile Int *)&next.z = *(volatile Int *)&ai->m_goalPosition47c.z;
		typedef Real (GiantBirdSwoopStateCall::*GetDistanceSquaredCall)(const Coord3D *) const;
		bool close = ((const GiantBirdSwoopStateCall *)owner->*giantBirdSwoopMember<GetDistanceSquaredCall>(j_00008a26))(&next) < range * range;
		if ((Real)ai->m_flag46c == 0.0f && !close)
			return STATE_CONTINUE;
		typedef void (GiantBirdSwoopStateCall::*SetPositionCall)(const Coord3D *);
		((GiantBirdSwoopStateCall *)owner->*giantBirdSwoopMember<SetPositionCall>(j_0003a1a7))(&next);
	}
	return STATE_SUCCESS;
}

typedef char GiantBirdSwoopStateGeometrySize[(sizeof(GeometryInfo) == 0x5c) ? 1 : -1];
typedef char GiantBirdSwoopStateMemberSize[(sizeof(void (GiantBirdSwoopStateCall::*)(bool)) == 4) ? 1 : -1];

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

class AIUpdateInterface
{
public:
	unsigned char m_unreconstructed000[0x3f8];
	UnsignedInt m_goalObjectID3f8;
	unsigned char m_unreconstructed3fc[0x424 - 0x3fc];
	bool m_isMoving424;
	unsigned char m_unreconstructed425[0x46c - 0x425];
	unsigned char m_flag46c;
	unsigned char m_unreconstructed46d[3];
	Real m_goalRange470;
	unsigned char m_unreconstructed474[8];
	Coord3D m_goalPosition47c;
};

class Object
{
public:
	unsigned char m_unreconstructed000[0x38];
	Coord3D m_position38;
	unsigned char m_unreconstructed044[0x94 - 0x44];
	UnsignedInt m_status94;
	unsigned char m_unreconstructed098[0xac - 0x98];
	GeometryInfo m_geometryInfoAC;
	unsigned char m_unreconstructed108[0x204 - 0x108];
	AIUpdateInterface *m_ai;
	unsigned char m_unreconstructed208[0x344 - 0x208];
	unsigned char m_privateStatus;
};

class StateMachine
{
public:
	unsigned char m_unreconstructed00[0x10];
	Object *m_owner;
};

class GameLogic;
extern GameLogic *TheGameLogic;

extern void j_0001f253();
extern void j_000163d3();
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
	void setSwooping(bool swooping);
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

	unsigned char m_unreconstructed20[8];
	Coord3D m_goal28;
	bool m_chooseGoal34;
	unsigned char m_unreconstructed35[7];
	Real m_damping3C;

	void setSwooping(bool swooping)
	{
		typedef void (GiantBirdSwoopStateCall::*SetSwoopingCall)(bool);
		((GiantBirdSwoopStateCall *)this->*giantBirdSwoopMember<SetSwoopingCall>(j_000163d3))(swooping);
	}
};

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
		setSwooping(false);
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
			setSwooping(true);
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

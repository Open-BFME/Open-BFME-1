// cl: /DNDEBUG /DWIN32 /MD /EHsc
// Retail 0x00189660 is the update slot behind vtable 0x0109AD20.
// The same table's name getter returns "AIFaceState".

#include <math.h>

typedef unsigned char Bool;
typedef float Real;

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Object;

template<int N>
class BfmeVirtualSlots : public BfmeVirtualSlots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};

template<>
class BfmeVirtualSlots<0>
{
};

class AIUpdateInterface : public BfmeVirtualSlots<118>
{
public:
	virtual void setLocomotorGoalPosition(const Coord3D *) = 0;
	virtual void slot1dc() = 0;
	virtual void slot1e0() = 0;
	virtual void setLocomotorGoalOrientation(Real) = 0;
};

class GoalObject : public BfmeVirtualSlots<120>
{
public:
	virtual void setLocomotorGoalPosition(const Coord3D *) = 0;
};

class Object
{
public:
	unsigned char m_padding000[0x44];
	Real m_orientation;
	unsigned char m_padding048[0x204 - 0x48];
	AIUpdateInterface *m_ai;
};

class StateMachine
{
public:
	unsigned char m_padding000[0x10];
	Object *m_owner;
	unsigned char m_padding014[0x10];
	Coord3D m_goalPosition;
};

class AIFaceState
{
	unsigned char m_padding004[0x18];
	StateMachine *m_machine;
	unsigned char m_padding020[8];
	int m_mode;
	Bool m_canTurnInPlace;

public:
	virtual StateReturnType update();
};

extern void j_0000e570();
extern void j_0002be77();
extern void j_00049413();
extern void j_00003b39();

typedef Object *(__fastcall *GetGoalObject)(StateMachine *);
typedef Real (Object::*GetRelativeAngle)(const Coord3D *);
typedef GoalObject *(__fastcall *GetGoalThing)(Object *);
typedef StateReturnType (__fastcall *ContinueIdle)(AIFaceState *);

StateReturnType AIFaceState::update()
{
	StateMachine *machine = m_machine;
	Object *owner = machine->m_owner;
	AIUpdateInterface *ai = owner->m_ai;
	const Coord3D *position = &machine->m_goalPosition;

	if (m_mode)
	{
		Object *goal = ((GetGoalObject)j_0000e570)(machine);
		if (!goal)
			return STATE_FAILURE;
		position = (const Coord3D *)((const unsigned char *)goal + 0x38);
	}

	union
	{
		void *asVoid;
		GetRelativeAngle asMember;
	} relativeAngleCast;
	relativeAngleCast.asVoid = (void *)j_00049413;
	Real relativeAngle = (owner->*relativeAngleCast.asMember)(position);
	if (fabs(relativeAngle) < *(const Real *)0x010977F0)
		return STATE_SUCCESS;

	if (m_canTurnInPlace)
	{
		relativeAngle += owner->m_orientation;
		if (m_mode == 2)
		{
			GoalObject *goalThing = ((GetGoalThing)j_0002be77)(owner);
			if (goalThing)
			{
				goalThing->setLocomotorGoalPosition(position);
				goto turnComplete;
			}
		}
		ai->setLocomotorGoalOrientation(relativeAngle);
	}
	else
	{
		ai->setLocomotorGoalPosition(position);
	}

turnComplete:
	if (m_mode == 2)
	{
		return ((ContinueIdle)j_00003b39)(this);
	}
	return STATE_CONTINUE;
}

// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// ?onEnter@AIPanicState@@UAE?AW4StateReturnType@@XZ
// stlport
// Clean C++ recovery of AIPanicState::onEnter, the Zero Hour AIStates.cpp
// body.  Retail boundary: 0x0017B680, 353 bytes, ends RET at 0x0017B7E0.
// Identity: the body is ZH AIPanicState::onEnter statement for statement (the
// only waypoint-path onEnter that sets MODELCONDITION_PANICKING), with the call
// order (computeGoal ILT 0x00019DC1, AIInternalMoveToState::onEnter ILT
// 0x00021E27, calcExtraPathDistance ILT 0x000428E8, setPathExtraDistance on
// the witnessed AIUpdateInterface+0x168, notifyModelConditionChanged ILT
// 0x0002191D) and the AIStates.cpp random-value line numbers 9810/9811.
// Locomotor::m_template is Zero Hour's OVERRIDE<LocomotorTemplate> with the
// reference's inline recursive Overridable::getFinalOverride, and the model
// condition flags are STLport bitset BitFlags.

typedef bool Bool;
typedef int Int;
typedef float Real;
typedef unsigned int UnsignedInt;

extern "C" __declspec(dllimport) double __cdecl floor(double);

__forceinline long fast_float2long_round(float value)
{
	long result;
	__asm {
		fld [value]
		fistp [result]
	}
	return result;
}

#define REAL_TO_INT_FLOOR(x) (fast_float2long_round((float)floor((double)(x))))

int GetGameLogicRandomValue(int lo, int hi, char *file, int line);
#define GameLogicRandomValue(lo, hi) GetGameLogicRandomValue(lo, hi, __FILE__, __LINE__)

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

enum { PATHFIND_CELL_SIZE = 10 };

#include "../../../../Libraries/Include/Lib/Coord2D.h"

#include <bitset>

class Waypoint;

template <int NUMBITS>
class BitFlags
{
public:
	Bool test(Int idx) const { return m_bits.test(idx); }
	void set(Int idx) { m_bits.set(idx); }

private:
	_STL::bitset<NUMBITS> m_bits;
};

enum ModelConditionFlagType { MODELCONDITION_PANICKING = 12 };

class Overridable
{
public:
	const Overridable *getFinalOverride() const
	{
		if (m_nextOverride)
			return m_nextOverride->getFinalOverride();
		return this;
	}

	void *m_vtable;
	Overridable *m_nextOverride;
};

template <class T> class OVERRIDE
{
public:
	const T *operator->() const
	{
		if (!m_overridable) return 0;
		return (const T *)m_overridable->getFinalOverride();
	}
	const T *operator*() const
	{
		if (!m_overridable) return 0;
		return (const T *)m_overridable->getFinalOverride();
	}
	operator const T *() const { return operator*(); }

	const T *m_overridable;
};

class LocomotorTemplate : public Overridable
{
public:
	unsigned char m_pad08[0xEC - 8];
	Real m_wanderWidthFactor;
};

class Locomotor
{
public:
	Real getWanderWidthFactor() const { return m_template->m_wanderWidthFactor; }

	void *m_vtable;
	OVERRIDE<LocomotorTemplate> m_template;
};

class AIUpdateInterface
{
public:
	Locomotor *getCurLocomotor() const { return m_curLocomotor; }
	void setPathExtraDistance(Real dist);

private:
	unsigned char m_pad00[0x1CC];
	Locomotor *m_curLocomotor;
};

class Object
{
public:
	AIUpdateInterface *getAI() const { return m_ai; }
	UnsignedInt getID() const { return m_id; }
	void notifyModelConditionChanged();
	void setModelConditionState(ModelConditionFlagType a)
	{
		if (!m_modelConditionFlags.test(a))
		{
			m_modelConditionFlags.set(a);
			notifyModelConditionChanged();
		}
	}

private:
	unsigned char m_pad00[0x74];
	UnsignedInt m_id;
	unsigned char m_pad78[0x118 - 0x78];
	BitFlags<32> m_modelConditionFlags;
	unsigned char m_pad11C[0x204 - 0x11C];
	AIUpdateInterface *m_ai;
};

class StateMachine
{
public:
	Object *getOwner() const { return m_owner; }
	Waypoint *getGoalWaypoint() const { return m_goalWaypoint; }

private:
	unsigned char m_pad00[0x10];
	Object *m_owner;
	unsigned char m_pad14[0x50 - 0x14];
	Waypoint *m_goalWaypoint;
};

class State
{
public:
	virtual ~State();
	StateMachine *getMachine() const { return m_machine; }
	Object *getMachineOwner() const { return m_machine->getOwner(); }

protected:
	UnsignedInt m_id;
	UnsignedInt m_successStateID;
	UnsignedInt m_failureStateID;
	void *m_transitions[3];
	StateMachine *m_machine;
};

class AIInternalMoveToState : public State
{
public:
	virtual StateReturnType onEnter();

protected:
	unsigned char m_pad20[0x50 - 0x20];
};

class AIFollowWaypointPathState : public AIInternalMoveToState
{
public:
	void computeGoal(Bool useGroupOffsets);

protected:
	Real calcExtraPathDistance();

	Coord2D m_groupOffset;
	unsigned char m_pad58[8];
	Waypoint *m_currentWaypoint;
};

class AIPanicState : public AIFollowWaypointPathState
{
public:
	virtual StateReturnType onEnter();

protected:
	unsigned char m_pad64[8];
	Int m_waitFrames;
	UnsignedInt m_timer;
};

// setPathExtraDistance is reached through ILT 0x0000EBAB, whose body 0x0026FE90 the
// ledger defines as ?set@Rva0026FE90DwordSlot@@QAEXH@Z; the call names it through a
// member pointer that keeps the Real argument.
typedef void (AIUpdateInterface::*Rva0026FE90RealCall)(Real);
extern "C" void __identifier("?set@Rva0026FE90DwordSlot@@QAEXH@Z")(void);
StateReturnType AIPanicState::onEnter()
{
	m_currentWaypoint = getMachine()->getGoalWaypoint();

	Object *obj = getMachineOwner();
	AIUpdateInterface *ai = obj->getAI();
	if (m_currentWaypoint == 0)
		return STATE_FAILURE;
	// set initial movement goal
	Locomotor *curLoco = ai->getCurLocomotor();
	if (curLoco && curLoco->getWanderWidthFactor() > 0.0f)
	{
		Int delta = REAL_TO_INT_FLOOR(curLoco->getWanderWidthFactor() + 0.5f);
		if (delta < 1)
			delta = 1;
#line 9810 "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Ai\\AIStates.cpp"
		m_groupOffset.x = GameLogicRandomValue(-delta, delta) * PATHFIND_CELL_SIZE;
		m_groupOffset.y = GameLogicRandomValue(-delta, delta) * PATHFIND_CELL_SIZE;
	}
	computeGoal(false);
	StateReturnType ret = AIInternalMoveToState::onEnter();

	m_timer = 0;
	m_waitFrames = 10 + (getMachineOwner()->getID() & 0x7);
	// Update the extra path distance.   AIInternalMoveToState::onEnter resets it.
	union { void (*raw)(void); Rva0026FE90RealCall member; } setExtra;
	setExtra.raw = __identifier("?set@Rva0026FE90DwordSlot@@QAEXH@Z");
	(ai->*setExtra.member)(calcExtraPathDistance());
	if (obj)
	{
		obj->setModelConditionState(MODELCONDITION_PANICKING);
	}

	return ret;
}

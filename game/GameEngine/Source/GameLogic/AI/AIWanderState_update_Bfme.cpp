// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// BFME layout for the retail AIWanderState::update body at 0x0017B060.

typedef unsigned char Bool;
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

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

struct Coord2D
{
	float x;
	float y;
};

class Object;
class Waypoint;

extern void j_0000ab1e();
extern void j_000022bb();
extern void j_00012ebd();
extern void j_00019dc1();
extern void j_0002191d();
extern void j_0002bdb4();
extern void j_0002d24f();
extern void j_0003a17a();
extern int GetGameLogicRandomValue(int, int, char *, int);

class StateMachine
{
public:
	Object *getOwner() const
	{
		return m_owner;
	}

private:
	virtual void bfmeVSlot0() {}
	void *m_stateMap[3];
	class Object *m_owner;
};

class State
{
public:
	virtual void bfmeVSlot00() {}
	virtual void bfmeVSlot01() {}
	virtual void bfmeVSlot02() {}
	virtual StateReturnType update();
	virtual void bfmeVSlot04() {}
	virtual void bfmeVSlot05() {}
	virtual void bfmeVSlot06() {}
	virtual void bfmeVSlot07() {}
	virtual void bfmeVSlot08() {}
	virtual void bfmeVSlot09() {}
	virtual void bfmeVSlot10() {}
	virtual void bfmeVSlot11() {}
	virtual void bfmeVSlot12() {}
	virtual void bfmeVSlot13() {}
	virtual void bfmeVSlot14() {}
	virtual void bfmeVSlot15() {}
	virtual void bfmeVSlot16() {}

protected:
	UnsignedInt m_stateID;
	UnsignedInt m_successStateID;
	UnsignedInt m_failureStateID;
	void *m_transitions[3];
	StateMachine *m_machine;
};

class BfmeThingTemplate
{
public:
	void *m_vptr;
	BfmeThingTemplate *m_nextOverride;
	unsigned char m_pad08[0xc4];
	UnsignedInt m_kindOfFlags;
};

class BfmeLocomotorTemplate
{
public:
	void *m_vptr;
	BfmeLocomotorTemplate *m_nextOverride;
	unsigned char m_pad08[0xe4];
	float m_wanderWidthFactor;

	float getWanderWidthFactor() const
	{
		return m_wanderWidthFactor;
	}
};

class BfmeLocomotor
{
public:
	void *m_vptr;
	BfmeLocomotorTemplate *m_template;
};

class BfmeAIUpdateInterface
{
public:
	BfmeLocomotor *getCurLocomotor() const
	{
		return m_curLocomotor;
	}

private:
	unsigned char m_pad00[0x1cc];
	BfmeLocomotor *m_curLocomotor;
};

class ModelConditionFlags
{
public:
	UnsignedInt m_bits() const
	{
		return m_bitsValue;
	}

	Bool test(UnsignedInt condition) const
	{
		return (m_bitsValue & condition) != 0;
	}

	void set(UnsignedInt condition)
	{
		m_bitsValue |= condition;
	}

private:
	UnsignedInt m_bitsValue;
};

class Object
{
public:
	BfmeAIUpdateInterface *getAI() const
	{
		return m_ai;
	}

	float getVisionRange() const;

	void setModelConditionState()
	{
		UnsignedInt condition = 0x04000000;
		UnsignedInt flags = m_modelConditionFlags.m_bits();
		if ((condition & flags) == 0)
		{
			m_modelConditionFlags.set(condition);
			typedef void (Object::*NotifyCall)();
			union { void *asVoid; NotifyCall asMember; } notifyCast;
			notifyCast.asVoid = (void *)j_0002191d;
			(this->*notifyCast.asMember)();
		}
	}

	Bool isKindOfCanBeRepulsed() const
	{
		BfmeThingTemplate *thing = m_template;
		if (thing == 0)
			return 0;
		if (thing->m_nextOverride != 0)
		{
			typedef BfmeThingTemplate *(BfmeThingTemplate::*FinalOverrideCall)();
			union { void *asVoid; FinalOverrideCall asMember; } overrideCast;
			overrideCast.asVoid = (void *)j_000022bb;
			thing = (thing->m_nextOverride->*overrideCast.asMember)();
		}
		return (thing->m_kindOfFlags & 0x00200000) != 0;
	}

	void *m_vptr;
	BfmeThingTemplate *m_template;
	unsigned char m_pad08[0x114];
	ModelConditionFlags m_modelConditionFlags;
	unsigned char m_pad120[0xe4];
	BfmeAIUpdateInterface *m_ai;
};

class AI
{
public:
	Object *findClosestRepulsor(const Object *object, float visionRange);
};

class AIInternalMoveToState : public State
{
public:
	virtual StateReturnType update();
	virtual Bool computePath();

	Object *getMachineOwner() const
	{
		return m_machine->getOwner();
	}

protected:
	unsigned char m_pad20[0x30];
};

class BfmeAIFollowWaypointPathState : public AIInternalMoveToState
{
protected:
	Coord2D m_groupOffset;
	float m_angle;
	int m_framesSleeping;
	const Waypoint *m_currentWaypoint;
	const Waypoint *m_priorWaypoint;
	Bool m_appendGoalPosition;
	Bool m_moveAsGroup;
	Bool m_isFollowWaypointPathState;

	void computeGoal(Bool useGroupOffsets)
	{
		typedef void (BfmeAIFollowWaypointPathState::*ComputeGoalCall)(Bool);
		union { void *asVoid; ComputeGoalCall asMember; } goalCast;
		goalCast.asVoid = (void *)j_00019dc1;
		(this->*goalCast.asMember)(useGroupOffsets);
	}

	const Waypoint *getNextWaypoint()
	{
		typedef const Waypoint *(BfmeAIFollowWaypointPathState::*NextWaypointCall)();
		union { void *asVoid; NextWaypointCall asMember; } nextCast;
		nextCast.asVoid = (void *)j_0000ab1e;
		return (this->*nextCast.asMember)();
	}
};

class AIWanderState : public BfmeAIFollowWaypointPathState
{
public:
	virtual StateReturnType update();

protected:
	int m_waitFrames;
	int m_timer;
};

#define TheAI (*(AI **)0x012EF214)
#define CritterDesyncFlag (*(unsigned char *)0x012F0239)
#define CritterDesyncSink (*(void **)0x012ED4FC)
#define BfmeZeroRange (*(const float *)0x01075350)
#define BfmeK1253 (*(const float *)0x0107533C)
#define BfmeRandomFile ((char *)0x0109769C)
#define BfmeWanderMessage ((const char *)0x0109A064)

typedef void (__cdecl *DebugLogFunction)(void *, const char *);

StateReturnType AIWanderState::update()
{
	StateReturnType status;
	int delta;
	Object *obj = getMachineOwner();
	obj->setModelConditionState();
	status = AIInternalMoveToState::update();
	BfmeThingTemplate *thing = obj->m_template;
	if (thing != 0 && thing->m_nextOverride != 0)
	{
		typedef BfmeThingTemplate *(BfmeThingTemplate::*FinalOverrideCall)();
		union { void *asVoid; FinalOverrideCall asMember; } overrideCast;
		overrideCast.asVoid = (void *)j_000022bb;
		thing = (thing->m_nextOverride->*overrideCast.asMember)();
	}
	if ((thing->m_kindOfFlags & 0x00002000) != 0)
	{
		m_timer--;
		if (m_timer < 0)
		{
			m_timer = m_waitFrames;
			Object *enemy = TheAI->findClosestRepulsor(getMachineOwner(), obj->getVisionRange());
			if (enemy)
				return STATE_FAILURE;
		}
	}

	if (status != STATE_CONTINUE)
	{
		BfmeAIUpdateInterface *ai = obj->getAI();
		m_currentWaypoint = getNextWaypoint();
		if (m_currentWaypoint == 0)
		{
			typedef void (BfmeAIUpdateInterface::*CompletedWaypointCall)(const Waypoint *);
			union { void *asVoid; CompletedWaypointCall asMember; } completedCast;
			completedCast.asVoid = (void *)j_0002d24f;
			(ai->*completedCast.asMember)(m_priorWaypoint);
			return STATE_SUCCESS;
		}

		BfmeLocomotor *curLoco;
		if ((curLoco = ai->getCurLocomotor()) != 0)
		{
			BfmeLocomotorTemplate *locoTemplate = curLoco->m_template;
			if (locoTemplate != 0 && locoTemplate->m_nextOverride != 0)
			{
				typedef BfmeLocomotorTemplate *(BfmeLocomotorTemplate::*FinalOverrideCall)();
				union { void *asVoid; FinalOverrideCall asMember; } overrideCast;
				overrideCast.asVoid = (void *)j_000022bb;
				locoTemplate = (locoTemplate->m_nextOverride->*overrideCast.asMember)();
			}
			if (locoTemplate->getWanderWidthFactor() > BfmeZeroRange)
			{
				typedef float (BfmeLocomotor::*WanderWidthCall)();
				union { void *asVoid; WanderWidthCall asMember; } widthCast;
				widthCast.asVoid = (void *)j_00012ebd;
				float width = (curLoco->*widthCast.asMember)();
				delta = REAL_TO_INT_FLOOR(width + BfmeK1253);
				if (delta < 1)
					delta = 1;
				int negativeDelta = -delta;
				int offsetX = GetGameLogicRandomValue(
					negativeDelta, delta, BfmeRandomFile, 0x25ab);
				m_groupOffset.x = (float)(offsetX * 10);
				int offsetY = GetGameLogicRandomValue(
					negativeDelta, delta, BfmeRandomFile, 0x25ac);
				m_groupOffset.y = (float)(offsetY * 10);
			}
		}

		computeGoal(0);
		if (CritterDesyncFlag && CritterDesyncSink)
			((DebugLogFunction)j_0003a17a)(CritterDesyncSink, BfmeWanderMessage);
		computePath();
		return STATE_CONTINUE;
	}
	return STATE_CONTINUE;
}

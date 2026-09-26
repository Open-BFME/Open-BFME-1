// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail 0x0017B490 is AIWanderInPlaceState::update.

typedef unsigned char Bool;

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

extern "C" __declspec(dllimport) double __cdecl floor(double value);

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

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object;

struct StateMachine
{
	char m_unknown00[0x10];
	Object *m_owner;
};

class BfmeThingTemplate
{
	public:
	void *m_vtable;
	BfmeThingTemplate *m_nextOverride;
	char m_unknown08[0xc4];
	unsigned int m_kindOfFlags;
};

class BfmeLocomotorTemplate
{
	public:
	void *m_vtable;
	BfmeLocomotorTemplate *m_nextOverride;
	char m_unknown08[0xf4 - 0x08];
	float m_wanderAboutPointRadius;
};

class BfmeLocomotor
{
	public:
	void *m_vtable;
	BfmeLocomotorTemplate *m_template;
};

class BfmeAIUpdateInterface
{
	public:
	char m_unknown00[0x1cc];
	BfmeLocomotor *m_curLocomotor;
};

class Object
{
	public:
	void *m_vtable;
	BfmeThingTemplate *m_template;
	char m_unknown08[0x204 - 0x08];
	BfmeAIUpdateInterface *m_ai;

	BfmeAIUpdateInterface *getAI() const
	{
		return m_ai;
	}

	float getVisionRange() const;
};

class State
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual StateReturnType update() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;

protected:
	char m_unknown04[0x18];
	StateMachine *m_machine;
};

class AIInternalMoveToState : public State
{
public:
	virtual StateReturnType update();
	virtual Bool computePath();
	virtual StateReturnType onEnter();

	protected:
	char m_unknown20[4];
	Coord3D m_goalPosition;
	char m_unknown30[0x20];

	Object *getMachineOwner() const
	{
		return m_machine->m_owner;
	}
};

class AIWanderInPlaceState : public AIInternalMoveToState
{
public:
	virtual StateReturnType update();

private:
	Coord3D m_origin;
	int m_waitFrames;
	int m_timer;
};

class AI
{
public:
	Object *findClosestRepulsor(const Object *object, float visionRange);
};

extern AI *TheAI;
extern void j_000022bb();
extern int GetGameLogicRandomValue(int low, int high, char *file, int line);

#define BfmeScaleBK (*(const float *)0x01075c70)

StateReturnType AIWanderInPlaceState::update()
{
	StateReturnType status = AIInternalMoveToState::update();
	StateMachine *machine = m_machine;
	Object *obj = machine->m_owner;
	BfmeAIUpdateInterface *ai = obj->getAI();
	if (ai == 0)
		return STATE_FAILURE;

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
			Object *owner = machine->m_owner;
			Object *enemy = TheAI->findClosestRepulsor(owner, obj->getVisionRange());
			if (enemy != 0)
				return STATE_FAILURE;
		}
	}

	if (status != STATE_CONTINUE)
	{
		int delta = 3;
		BfmeLocomotor *curLoco = ai->m_curLocomotor;
		if (curLoco != 0)
		{
			BfmeLocomotorTemplate *locoTemplate = curLoco->m_template;
			if (locoTemplate != 0 && locoTemplate->m_nextOverride != 0)
			{
				typedef BfmeLocomotorTemplate *(BfmeLocomotorTemplate::*FinalOverrideCall)();
				union { void *asVoid; FinalOverrideCall asMember; } overrideCast;
				overrideCast.asVoid = (void *)j_000022bb;
				locoTemplate = (locoTemplate->m_nextOverride->*overrideCast.asMember)();
			}
			delta = REAL_TO_INT_FLOOR(locoTemplate->m_wanderAboutPointRadius * BfmeScaleBK + 0.5f);
		}
		int negativeDelta = -delta;
		Coord3D offset;
		int offsetX = GetGameLogicRandomValue(negativeDelta, delta, (char *)0x0109769c, 0x2618);
		offset.x = (float)(offsetX * 10);
		int offsetY = GetGameLogicRandomValue(negativeDelta, delta, (char *)0x0109769c, 0x2619);
		offset.y = (float)(offsetY * 10);
		m_goalPosition = m_origin;
		m_goalPosition.x += offset.x;
		m_goalPosition.y += offset.y;
		AIInternalMoveToState::onEnter();
	}
	return STATE_CONTINUE;
}

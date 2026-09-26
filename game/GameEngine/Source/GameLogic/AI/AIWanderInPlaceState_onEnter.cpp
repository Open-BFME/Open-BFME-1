// Retail RVA 0x0017B310, 301 bytes.
// cl: /O2 /Ob1 /QIfist /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// AIStates.cpp and the adjacent matched AIWanderState methods prove the
// AIWanderInPlaceState::onEnter identity and its vtable family.

typedef unsigned char Bool;

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

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

class BfmeLocomotorTemplate
{
public:
	void *m_vtable;
	BfmeLocomotorTemplate *m_nextOverride;
	char m_unknown08[0xec];
	float m_wanderAboutPointRadius;
};

class BfmeLocomotor
{
public:
	void *m_vtable;
	BfmeLocomotorTemplate *m_template;

	__forceinline BfmeLocomotorTemplate *getFinalTemplate() const;
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
	char m_unknown04[0x34];
	Coord3D m_position;
	char m_unknown44[0x30];
	unsigned int m_id;
	char m_unknown78[0x18c];
	BfmeAIUpdateInterface *m_ai;
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
	Object *getMachineOwner() const
	{
		return m_machine->m_owner;
	}

	char m_unknown20[4];
	Coord3D m_goalPosition;
	char m_unknown30[0x20];
};

class AIWanderInPlaceState : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();

private:
	Coord3D m_origin;
	int m_waitFrames;
	int m_timer;
};

extern "C" __declspec(dllimport) double __cdecl floor(double value);
extern int GetGameLogicRandomValue(int low, int high, char *file, int line);
extern void j_000022bb();

__forceinline int fast_float2long_round(float value)
{
	int result;
	__asm {
		fld [value]
		fistp [result]
	}
	return result;
}

// ?getFinalTemplate@BfmeLocomotor@@QBEPAVBfmeLocomotorTemplate@@XZ absent-from-retail
__forceinline BfmeLocomotorTemplate *BfmeLocomotor::getFinalTemplate() const
{
	BfmeLocomotorTemplate *locoTemplate = m_template;
	if (locoTemplate == 0)
		return 0;
	if (locoTemplate->m_nextOverride != 0)
	{
		typedef BfmeLocomotorTemplate *(BfmeLocomotorTemplate::*FinalOverrideCall)();
		union { void *asVoid; FinalOverrideCall asMember; } finalOverride;
		finalOverride.asVoid = (void *)j_000022bb;
		return (locoTemplate->m_nextOverride->*finalOverride.asMember)();
	}
	return locoTemplate;
}

StateReturnType AIWanderInPlaceState::onEnter()
{
	m_origin = getMachineOwner()->m_position;

	BfmeAIUpdateInterface *ai = getMachineOwner()->m_ai;
	if (ai != 0)
	{
		typedef void (BfmeAIUpdateInterface::*ChooseLocomotorSetCall)(int);
		union { void *asVoid; ChooseLocomotorSetCall asMember; } choose;
		choose.asVoid = (*(void ***)ai)[127];
		(ai->*choose.asMember)(3);
	}

	int delta = 3;
	BfmeLocomotor *locomotor = ai->m_curLocomotor;
	if (locomotor != 0)
	{
		BfmeLocomotorTemplate *locoTemplate = locomotor->getFinalTemplate();
		float rounded = (float)floor((double)(
			locoTemplate->m_wanderAboutPointRadius *
			*(const float *)0x01075c70 + *(const float *)0x0107533c));
		delta = fast_float2long_round(rounded);
	}

	int negativeDelta = -delta;
	Coord3D offset;
	offset.x = (float)(GetGameLogicRandomValue(negativeDelta, delta,
		(char *)0x0109769c, 0x25f1) * 10);
	offset.y = (float)(GetGameLogicRandomValue(negativeDelta, delta,
		(char *)0x0109769c, 0x25f2) * 10);
	m_goalPosition = m_origin;
	m_goalPosition.x += offset.x;
	m_goalPosition.y += offset.y;
	m_timer = 0;
	m_waitFrames = 10 + (getMachineOwner()->m_id & 7);
	return AIInternalMoveToState::onEnter();
}

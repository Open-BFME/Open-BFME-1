// ?update@AIGuardOuterState@@UAE?AW4StateReturnType@@XZ
// Open-BFME: clean reconstruction of retail 0x0015E2F0.

typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef int ObjectID;
typedef float Real;

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

enum StateExitType
{
	STATE_EXIT_NORMAL = 0
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Object
{
public:
	unsigned char m_pad000[0x38];
	Coord3D m_position;
	unsigned char m_pad044[0x300];
	unsigned char m_deadFlags;

	const Coord3D *getPosition() const { return &m_position; }
	int getLayer() const;
};

class GameLogic
{
public:
	unsigned char m_pad000[0x3c];
	UnsignedInt m_frame;
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheBfmeGameLogic;

class Team
{
public:
	void getPosition(Coord3D *position);
};

class TeamFactory
{
public:
	Team *findTeamByID(UnsignedInt id);
};

extern TeamFactory *TheTeamFactory;

class AIData
{
public:
	unsigned char m_pad000[0x3c];
	UnsignedInt m_guardChaseUnitFrames;
};

class AI
{
public:
	unsigned char m_pad000[0x14];
	AIData *m_aiData;
};

extern AI *TheAI;

class StateMachine
{
public:
	Object *getGoalObject();
};

class AttackState
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual StateReturnType slot10();
	virtual void slot14();
	virtual StateReturnType update();

	unsigned char m_pad004[0x18];
	StateMachine *m_machine;

	Object *getMachineGoalObject()
	{
		return m_machine->getGoalObject();
	}
};

class AIGuardMachine
{
public:
	Object *findTargetToGuardByID()
	{
		return TheBfmeGameLogic->findObjectByID(m_targetToGuard);
	}
	Bool lookForInnerTarget();

	unsigned char m_pad000[0x10];
	Object *m_owner;
	unsigned char m_pad014[0x30];
	ObjectID m_targetToGuard;
	UnsignedInt m_teamToGuard;
};

class ExitConditions
{
public:
	int m_conditionsToConsider;
	Coord3D m_center;
	Real m_radiusSqr;
	UnsignedInt m_attackGiveUpFrame;
};

class State
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();

	unsigned char m_pad004[0x18];
	StateMachine *m_machine;
};

class AIGuardOuterState : public State
{
public:
	virtual StateReturnType update();

	unsigned char m_pad020[0x08];
	ExitConditions m_exitConditions;
	AttackState *m_attackState;
	unsigned char m_unusedFlag;
};

extern void j_0000e570();
extern void j_00004c37();
extern void j_0001f253();
extern void j_000241fe();
extern void j_000317a5();
extern void j_00043892();
extern void j_00044c2e();

typedef Bool (__cdecl *BfmeCallENJCall)(void *, void *);
typedef Real (__cdecl *GetStdGuardRangeCall)(const Object *);

static Real sqr(Real input)
{
	return input * input;
}

StateReturnType AIGuardOuterState::update()
{
	if (m_unusedFlag)
	{
		m_unusedFlag = 0;
		State *self = this;
		return self->onEnter();
	}

	if (m_attackState == 0)
		return STATE_SUCCESS;

	StateReturnType result;
	AIGuardMachine *guardMachine = (AIGuardMachine *)m_machine;
	Object *owner;
	Object *targetToGuard = guardMachine->findTargetToGuardByID();
	Team *teamToGuard = TheTeamFactory->findTeamByID(guardMachine->m_teamToGuard);

	if (targetToGuard)
	{
		m_exitConditions.m_center = *targetToGuard->getPosition();
	}
	else if (teamToGuard)
	{
		teamToGuard->getPosition(&m_exitConditions.m_center);
	}

	result = m_attackState->update();
	Object *goalObject = m_attackState->getMachineGoalObject();
	owner = *(Object **)((unsigned char *)m_machine + 0x10);
	if (goalObject == 0)
		goto fallback;

	if (owner->getLayer() != 1)
	{
		if (!((BfmeCallENJCall)j_00004c37)(owner, goalObject))
			return STATE_SUCCESS;
	}

	if ((goalObject->m_deadFlags & 1) == 0)
	{
		Coord3D delta;
		delta.x = m_exitConditions.m_center.x - goalObject->m_position.x;
		delta.y = m_exitConditions.m_center.y - goalObject->m_position.y;
		delta.z = m_exitConditions.m_center.z - goalObject->m_position.z;
		if (delta.x * delta.x + delta.y * delta.y + delta.z * delta.z <=
			sqr(((GetStdGuardRangeCall)j_00043892)(
				*(Object **)((unsigned char *)m_machine + 0x10))))
		{
			volatile AI *ai = TheAI;
			m_exitConditions.m_attackGiveUpFrame = ai->m_aiData->m_guardChaseUnitFrames +
				TheBfmeGameLogic->m_frame;
		}
		return result;
	}

fallback:
	if (((AIGuardMachine *)m_machine)->lookForInnerTarget())
	{
		State *self = this;
		self->onExit(STATE_EXIT_NORMAL);
		return self->onEnter();
	}

	return result;
}

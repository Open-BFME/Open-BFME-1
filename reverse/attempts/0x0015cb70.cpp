// ?onEnter@AIGuardAttackAggressorState@@UAE?AW4StateReturnType@@XZ
// partial score=0.98 date=2026-09-11
// cl: /DNDEBUG /MD /EHsc
// BFME reconstruction of AIGuardAttackAggressorState::onEnter at retail 0x0015CB70.


typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef int ObjectID;

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1
};

class Object;

class BodyModule
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual const struct DamageInfo *getLastDamageInfo() const;
};

struct DamageInfo
{
	unsigned char m_pad00[8];
	ObjectID m_sourceID;
};

class Object
{
public:
	BodyModule *getBodyModule() const
	{
		return *(BodyModule **)((const unsigned char *)this + 0x200);
	}
};

class StateMachine
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2c();
	virtual void slot30();
	virtual void slot34();
	virtual void setGoalObject(const Object *object);

	unsigned char m_pad04[0x0c];
	Object *m_owner;
};

class GameLogicFrameBase
{
public:
	unsigned char m_pad00[0x3c];
	UnsignedInt m_frame;
	UnsignedInt getFrame()
	{
		return m_frame;
	}
};

class GameLogic : public GameLogicFrameBase
{
public:
	Object *findObjectByID(ObjectID id);
};

class AIData
{
public:
	unsigned char m_pad00[0x3c];
	UnsignedInt m_guardChaseUnitFrames;
	UnsignedInt getGuardChaseUnitFrames() const
	{
		return m_guardChaseUnitFrames;
	}
};

class AI
{
public:
	unsigned char m_pad00[0x14];
	AIData *m_aiData;
	const AIData *getAiData() const
	{
		return m_aiData;
	}
};

#define TheBfmeGameLogic (*(GameLogic **)0x012F0898)
#define TheAI (*(AI **)0x012EF214)

class BfmeGuardMachine : public StateMachine
{
public:
	unsigned char m_pad14[0x58];
	volatile ObjectID m_nemesisID;
};

class State
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual StateReturnType onEnter();
	virtual void onExit(Int status);
	virtual StateReturnType update();

	unsigned char m_pad04[0x18];
	StateMachine *m_machine;
	unsigned char m_pad20[4];
	StateMachine *getMachine() const
	{
		return m_machine;
	}
};

class AttackExitConditionsInterface
{
public:
	virtual Bool shouldExit(const StateMachine *machine) const;
};

class ExitConditions : public AttackExitConditionsInterface
{
public:
	Int m_conditionsToConsider;
	float m_centerX;
	float m_centerY;
	float m_centerZ;
	float m_radiusSqr;
	UnsignedInt m_attackGiveUpFrame;
};

class AIAttackState
{
public:
	AIAttackState(StateMachine *machine, Bool follow, Bool attackingObject,
		Bool forceAttacking, AttackExitConditionsInterface *attackParameters);

	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual StateReturnType onEnter();
	virtual void slot14();
	virtual StateReturnType update();

	unsigned char m_pad04[0x18];
	StateMachine *m_machine;
	unsigned char m_tail[0x34];
};

// ?onEnter@AIGuardAttackAggressorState@@UAE?AW4StateReturnType@@XZ
class Rva0015CB70AIGuardAttackAggressorState : public State
{
public:
	virtual StateReturnType onEnter();

	ExitConditions m_exitConditions;
	AIAttackState *m_attackState;
	Bool m_unusedFlag;
};

// ?onEnter@AIGuardAttackAggressorState@@UAE?AW4StateReturnType@@XZ
StateReturnType Rva0015CB70AIGuardAttackAggressorState::onEnter()
{
	if (m_unusedFlag)
	{
		m_unusedFlag = false;
		State *self = this;
		return self->onEnter();
	}

	Object *owner = ((BfmeGuardMachine *)m_machine)->m_owner;
	if (owner->getBodyModule() != 0 &&
		owner->getBodyModule()->getLastDamageInfo()->m_sourceID != 0)
	{
		ObjectID nemID = owner->getBodyModule()->getLastDamageInfo()->m_sourceID;
		((BfmeGuardMachine *)m_machine)->m_nemesisID = nemID;
	}

	BfmeGuardMachine *machineForID = (BfmeGuardMachine *)m_machine;
	ObjectID nemID = machineForID->m_nemesisID;
	GameLogic *const logic = TheBfmeGameLogic;
	Object *nemesis = logic->findObjectByID(nemID);
	if (nemesis == 0)
		return STATE_SUCCESS;

	m_exitConditions.m_attackGiveUpFrame =
		TheAI->getAiData()->m_guardChaseUnitFrames + logic->getFrame();
	m_exitConditions.m_conditionsToConsider = 6;

	m_attackState = new AIAttackState(
		getMachine(), true, true, false, &m_exitConditions);
	m_attackState->m_machine->setGoalObject(nemesis);

	StateReturnType returnVal = m_attackState->onEnter();
	if (returnVal == STATE_CONTINUE)
		return STATE_CONTINUE;
	return STATE_SUCCESS;
}

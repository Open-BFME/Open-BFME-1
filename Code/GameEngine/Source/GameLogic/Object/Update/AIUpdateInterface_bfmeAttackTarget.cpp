// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// BFME target handoff: preserve a live attack/retaliate state, otherwise route
// the target through the command interface; an already-owned state machine gets
// its goal replaced under the retail lock protocol.

typedef bool Bool;
typedef int Int;

class Object;

enum CommandSourceType
{
	CMD_FROM_AI = 2
};

class AICommandInterface
{
public:
	void aiAttackObject(Object *victim, Int maxShotsToFire,
		CommandSourceType cmdSource);
};

class State
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual Bool slot20() = 0;

	int m_id;

	Int getID() const
	{
		return m_id;
	}
};

class StateMachine
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void setGoalObject(const Object *object) = 0;

	Int getCurrentStateID() const
	{
		return m_state != 0 ? m_state->getID() : 0xf423f;
	}

	State *getCurrentState() const
	{
		return m_state;
	}

	Bool isInBusyState() const
	{
		return m_state != 0 ? m_state->slot20() : false;
	}

	Bool isInIdleState() const
	{
		return m_state != 0 ? m_state->slot20() : true;
	}

	char m_unmodelled_004[0x1c - 4];
	State *m_state;
	char m_unmodelled_020[0x40 - 0x20];
	Bool m_locked;
};

static State *loadCurrentState(const StateMachine *machine)
{
	return machine->m_state;
}

extern Bool bfmeMeleeHordeTargetInvalid(Object *source, Object *target);

class BfmeUnit988
{
public:
	void bfmeReset988D();
};

class AIUpdateInterface
{
public:
	void bfmeAttackTarget(Object *target);

	char m_unmodelled_000[0x08];
	Object *m_object;
	char m_unmodelled_00c[0x30 - 0x0c];
	StateMachine *m_stateMachine;
	void *m_field34;
	char m_unmodelled_038[0x20 - 4];
};

void AIUpdateInterface::bfmeAttackTarget(Object *target)
{
	Int stateID = m_stateMachine->getCurrentStateID();
	Bool preserve = stateID == 0x21 || stateID == 0x3d;

	if (!m_stateMachine->isInIdleState() && !preserve)
	{
		if (m_field34 == 0)
		{
			((AICommandInterface *)((char *)this + 0x20))->aiAttackObject(
				target, 0x7fffffff, CMD_FROM_AI);
			return;
		}
		return;
	}

	Bool locked = ((StateMachine *)m_stateMachine)->m_locked;
	((StateMachine *)m_stateMachine)->m_locked = 0;
	((StateMachine *)m_stateMachine)->setGoalObject(target);
	if (locked)
		((StateMachine *)m_stateMachine)->m_locked = 1;
	Object *source = m_object;
	if (!bfmeMeleeHordeTargetInvalid(source, target))
		((BfmeUnit988 *)this)->bfmeReset988D();
}

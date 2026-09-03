// cl: /DNDEBUG /MD /EHsc
// Open-BFME: AIMoveAndEvacuateState::update, retail 0x00188520.
// BFME's State stores its machine at +0x1c.  The corresponding ZH source
// uses +0x20, while BFME's Object, AI module, Team, and dead flag are at
// +0x204, +0x23c, and +0x344 respectively.

typedef bool Bool;

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_FAILURE = -2
};

enum StateExitType
{
};

enum CommandSourceType
{
	CMD_FROM_AI = 2
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AICommandInterface
{
public:
	void aiEvacuate(Bool exposeStealthUnits, CommandSourceType cmdSource);
};

class AIUpdateInterfacePrefix
{
	unsigned char m_unmodelled_000[0x20];
};

class AIUpdateInterface : public AIUpdateInterfacePrefix, public AICommandInterface
{
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
	unsigned char m_pad[0x31];

public:
	unsigned char m_b31; // +0x31
	unsigned char m_b32; // +0x32

	void setActive()
	{
		if (!m_b31)
		{
			m_b32 = 1;
			m_b31 = 1;
		}
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
	unsigned char m_unmodelled_000[0x204];
	AIUpdateInterface *m_ai; // +0x204
	unsigned char m_unmodelled_208[0x23c - 0x208];
	Team *m_team; // +0x23c
	unsigned char m_unmodelled_240[0x344 - 0x240];
	unsigned char m_deadFlags; // +0x344

public:
	Bool isEffectivelyDead() const { return (m_deadFlags & 1) != 0; }
	AIUpdateInterface *getAI() const { return m_ai; }
	Team *getTeam() const { return m_team; }
};

// BFME's state-machine owner is at +0x10.
class StateMachine
{
	unsigned char m_unmodelled_000[0x10];
	Object *m_owner; // +0x10

public:
	Object *getOwner() const { return m_owner; }
};

// BFME's State base has the machine pointer at +0x1c.
class AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType);
	virtual StateReturnType update();

protected:
	unsigned char m_unmodelled_004[0x18];
	StateMachine *m_machine; // +0x1c

	StateMachine *getMachine() const { return m_machine; }
	Object *getMachineOwner() const { return m_machine->getOwner(); }
};

class AIMoveAndEvacuateState : public AIInternalMoveToState
{
public:
	virtual StateReturnType update();
};

StateReturnType AIMoveAndEvacuateState::update()
{
	Object *obj = getMachine()->getOwner();
	if (obj->isEffectivelyDead())
	{
		return STATE_FAILURE;
	}

	StateReturnType status = AIInternalMoveToState::update();
	if (status != STATE_CONTINUE)
	{
		Object *obj = getMachineOwner();
		if (obj->isEffectivelyDead())
		{
			return STATE_FAILURE;
		}

		AIUpdateInterface *ai = obj->getAI();
		ai->aiEvacuate(false, CMD_FROM_AI);
		obj->getTeam()->setActive();
	}

	return status;
}

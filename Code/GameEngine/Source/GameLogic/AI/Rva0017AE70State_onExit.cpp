// BFME layout view for the anonymous 0x0017AE70 state-exit body.

enum StateExitType
{
	STATE_EXIT_NORMAL = 0
};

class Object;

class StateMachine
{
public:
	unsigned char m_pad00[0x10];
	Object *m_owner;
};

class AIUpdateInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void setCanPathThroughUnits(bool) = 0;
};

class Locomotor
{
public:
	unsigned char m_pad00[0x40];
	unsigned int m_flags;
};

class Object
{
public:
	unsigned char m_pad00[0x204];
	AIUpdateInterface *m_ai;
};

class AIInternalMoveToState
{
public:
	virtual void onExit(StateExitType);

protected:
	unsigned char m_pad00[0x18];
	StateMachine *m_machine;
};

class Rva0017AE70State : public AIInternalMoveToState
{
public:
	virtual void onExit(StateExitType);

private:
	unsigned char m_pad20[0x4c];
	AIUpdateInterface *m_stateAI;
};

void Rva0017AE70State::onExit(StateExitType status)
{
	m_stateAI->setCanPathThroughUnits(false);
	AIInternalMoveToState::onExit(status);
	AIUpdateInterface *ai = m_machine->m_owner->m_ai;
	if (ai)
	{
		Locomotor *locomotor = *(Locomotor **)((char *)ai + 0x1cc);
		if (locomotor)
			locomotor->m_flags &= ~8u;
	}
}

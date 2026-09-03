// cl: /DNDEBUG /MD /EHsc
// BFME state-exit reconstruction for retail RVA 0x0017DC90.
// The body carries two object IDs: the first is restored to the state
// machine before the common move-state exit, and the second clears the
// object's containment intent afterward.

typedef int ObjectID;

enum StateExitType
{
	STATE_EXIT_NORMAL = 0,
	STATE_EXIT_RESET = 1
};

enum ObjectEnterExitType
{
	WANTS_TO_ENTER = 0,
	WANTS_TO_EXIT = 1,
	WANTS_NEITHER = 2
};

class Object;

class ContainModuleInterface
{
public:
	virtual void unused00();
	virtual void unused01();
	virtual void unused02();
	virtual void unused03();
	virtual void unused04();
	virtual void unused05();
	virtual void unused06();
	virtual void unused07();
	virtual void unused08();
	virtual void unused09();
	virtual void unused10();
	virtual void unused11();
	virtual void unused12();
	virtual void onObjectWantsToEnterOrExit(Object *, ObjectEnterExitType);
};

class Locomotor
{
public:
	void clearAllowInvalidPosition()
	{
		m_flags &= ~2u;
	}

private:
	unsigned char m_unreconstructed[ 0x40 ];
	unsigned int m_flags;
};

class AIUpdateInterface
{
public:
	void ignoreObstacle(Object *);

	Locomotor *getCurLocomotor() const
	{
		return m_locomotor;
	}

private:
	unsigned char m_unreconstructed[ 0x1cc ];
	Locomotor *m_locomotor;
};

class Object
{
public:
	ContainModuleInterface *getContain() const
	{
		return m_contain;
	}

	AIUpdateInterface *getAI() const
	{
		return m_ai;
	}

private:
	unsigned char m_unreconstructed[ 0x1fc ];
	ContainModuleInterface *m_contain;
	unsigned char m_between[ 4 ];
	AIUpdateInterface *m_ai;
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

class StateMachine
{
public:
	virtual void unused00();
	virtual void unused01();
	virtual void unused02();
	virtual void unused03();
	virtual void unused04();
	virtual void unused05();
	virtual void unused06();
	virtual void unused07();
	virtual void unused08();
	virtual void unused09();
	virtual void unused10();
	virtual void unused11();
	virtual void unused12();
	virtual void unused13();
	virtual void setGoalObject(const Object *);
	Object *getOwner() const
	{
		return m_owner;
	}

	private:
	unsigned char m_unreconstructed[ 0x0c ];
	Object *m_owner;
};

class AIInternalMoveToState
{
public:
	virtual void onExit(StateExitType);

protected:
	unsigned char m_unreconstructed[ 0x18 ];
	StateMachine *m_machine;
};

class Rva0017DC90State : public AIInternalMoveToState
{
public:
	virtual void onExit(StateExitType);

private:
	unsigned char m_unreconstructed[ 0x30 ];
	ObjectID m_entryToClear;
	ObjectID m_restoreGoalObject;
};

void Rva0017DC90State::onExit(StateExitType status)
{
	Object *goal = TheGameLogic->findObjectByID(m_restoreGoalObject);
	if (goal)
		m_machine->setGoalObject(goal);

	Object *owner = m_machine->getOwner();
	AIInternalMoveToState::onExit(status);

	AIUpdateInterface *ai = owner->getAI();
	if (ai)
	{
		ai->ignoreObstacle(0);
		Locomotor *locomotor = ai->getCurLocomotor();
		if (locomotor)
			locomotor->clearAllowInvalidPosition();
	}

	if (m_entryToClear)
	{
		goal = TheGameLogic->findObjectByID(m_entryToClear);
		if (goal)
		{
			ContainModuleInterface *contain = goal->getContain();
			if (contain)
				contain->onObjectWantsToEnterOrExit(owner, WANTS_NEITHER);
		}
	}
}

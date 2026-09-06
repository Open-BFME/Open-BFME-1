// ?update@GiantBirdGuardInnerState@@UAE?AW4StateReturnType@@XZ
// partial score=0.9 date=2026-09-06
// cl: /DNDEBUG /MD
//
// GiantBirdGuardInnerState::update at retail RVA 0x002BD230.

typedef int Int;

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_COMPLETE = -1,
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object
{
public:
	unsigned char m_unreconstructed000[0x344];
	unsigned char m_status;
};

class GameLogic
{
public:
	Object *findObjectByID(Int id);
};

class StateMachine
{
public:
	Object *getGoalObject();
};

class Rva002BD630TeamFactory
{
public:
	void *find(Int id);
};

class Team
{
public:
	Coord3D *getEstimateTeamPosition_000EDCD0(Coord3D *position) const;

	unsigned char m_unreconstructed000[0x38];
	Coord3D m_position;
};

class GiantBirdGuardInnerMachine
{
public:
	virtual void unused000() = 0;
	virtual void unused004() = 0;
	virtual void unused008() = 0;
	virtual void unused00c() = 0;
	virtual Int unused010() = 0;
	virtual StateReturnType unused014() = 0;
	virtual Int update() = 0;
	virtual void unused01c() = 0;
	virtual void unused020() = 0;
	virtual void unused024() = 0;
	virtual void unused028() = 0;
	virtual void unused02c() = 0;
	virtual void unused030() = 0;
	virtual void unused034() = 0;
	virtual void unused038() = 0;
	virtual void unused03c() = 0;
	virtual void unused040() = 0;
	virtual void unused044() = 0;
	virtual bool isComplete() = 0;

	unsigned char m_unreconstructed004[0x18];
	StateMachine *m_stateMachine;
	unsigned char m_unreconstructed020[0x24];
	Int m_teamID;
	Int m_otherID;

};

extern GameLogic *TheBfmeGameLogic;
extern Rva002BD630TeamFactory *TheBfmeTeamFactory;

class GiantBirdGuardInnerState
{
public:
	virtual void unused000() = 0;
	virtual void unused004() = 0;
	virtual void unused008() = 0;
	virtual void unused00c() = 0;
	virtual StateReturnType onEnter() = 0;
	virtual void onExit() = 0;
	virtual StateReturnType update();

private:
	unsigned char m_unreconstructed004[0x18];
	GiantBirdGuardInnerMachine *m_machine;
	unsigned char m_unreconstructed020[0x0c];
	Coord3D m_position;
	unsigned char m_unreconstructed038[8];
	GiantBirdGuardInnerMachine *m_subMachine;
	unsigned char m_active;
};

static StateMachine *getStateMachine(GiantBirdGuardInnerMachine *machine)
{
	return machine->m_stateMachine;
}

StateReturnType GiantBirdGuardInnerState::update()
{
	if (m_active)
	{
		m_active = 0;
		return onEnter();
	}

	if (m_subMachine == 0)
		return STATE_COMPLETE;

	GiantBirdGuardInnerMachine *machine = m_machine;
	Object *object = TheBfmeGameLogic->findObjectByID(machine->m_teamID);
	Team *teamResult = (Team *)TheBfmeTeamFactory->find(machine->m_otherID);
	if (object)
	{
		Coord3D *objectPosition = (Coord3D *)((char *)object + 0x38);
		m_position = *objectPosition;
	}
	else if (teamResult)
	{
		teamResult->getEstimateTeamPosition_000EDCD0(&m_position);
	}

	Int result = m_subMachine->update();
	Object *goalObject = m_subMachine->m_stateMachine->getGoalObject();
	if (goalObject == 0 || (goalObject->m_status & 1) != 0)
	{
		if (m_subMachine != 0)
		{
			if (m_subMachine->isComplete())
				return STATE_COMPLETE;
		}
	}
	return (StateReturnType)result;
}

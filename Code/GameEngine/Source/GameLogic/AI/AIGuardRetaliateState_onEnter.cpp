// cl: /DNDEBUG /MD /EHsc
// readable body of ?onEnter@AIGuardRetaliateState@@UAE?AW4StateReturnType@@XZ: Code/GameEngine/Source/GameLogic/AI/AIStates.cpp
//
// AIGuardRetaliateState::onEnter — retail 0x0017E1F0 (199B).
//
// ZH onEnter plus BFME's kindFlags 0x20 melee-target resolve. Accessors match
// the inlines in StateMachine.h / AIUpdate.h / AIGuardRetaliate.h so the
// goal-position copy is `add`-based (src +0x24, dest +0x44) and the second
// getMachineOwner reload can land in ecx.

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

class StateMachine;
class Object;

class AIUpdateInterface
{
public:
	StateMachine *getStateMachine() { return m_stateMachine; }
	const StateMachine *getStateMachine() const { return m_stateMachine; }
	Object *getGoalObject();
	const Coord3D *getGoalPosition() const;

	unsigned char m_aiFields[0x30];
	StateMachine *m_stateMachine;
};

class Object
{
public:
	Object *bfmeResolveMeleeTarget(int index);
	AIUpdateInterface *getAI() { return m_ai; }
	unsigned int getID() const { return m_id; }

	unsigned char m_objectFields00[0x74];
	unsigned int m_id;
	unsigned char m_objectFields78[0x1c];
	unsigned char m_kindFlags;
	unsigned char m_objectFields95[0x16f];
	AIUpdateInterface *m_ai;
};

#pragma comment(linker, "/alternatename:?bfmeResolveMeleeTarget@Object@@QAEPAV1@H@Z=?j_0000faa6@@YAXXZ")

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
	virtual StateReturnType initDefaultState();

	Object *getOwner() { return m_owner; }
	const Coord3D *getGoalPosition() const { return &m_goalPosition; }
	Object *getGoalObject();

	unsigned char m_machineFields04[0x0c];
	Object *m_owner;
	unsigned char m_machineFields14[0x10];
	Coord3D m_goalPosition;
};

#pragma comment(linker, "/alternatename:?getGoalObject@StateMachine@@QAEPAVObject@@XZ=?j_0000e570@@YAXXZ")

inline Object *AIUpdateInterface::getGoalObject()
{
	return getStateMachine()->getGoalObject();
}

inline const Coord3D *AIUpdateInterface::getGoalPosition() const
{
	return getStateMachine()->getGoalPosition();
}

class AIGuardRetaliateMachine
{
public:
	AIGuardRetaliateMachine(Object *owner);

	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual StateReturnType initDefaultState();

	void setTargetPositionToGuard(const Coord3D *pos) { m_positionToGuard = *pos; }
	void setNemesisID(unsigned int id) { m_nemesisToAttack = id; }

	unsigned char m_machineFields04[0x40];
	Coord3D m_positionToGuard;
	unsigned int m_nemesisToAttack;
};

#pragma comment(linker, "/alternatename:??0AIGuardRetaliateMachine@@QAE@PAVObject@@@Z=?j_0003e8d3@@YAXXZ")

class AIGuardRetaliateState
{
public:
	virtual StateReturnType onEnter();

	Object *getMachineOwner() { return m_machine->getOwner(); }

	unsigned char m_stateFields04[0x18];
	StateMachine *m_machine;
	unsigned char m_stateFields20[4];
	AIGuardRetaliateMachine *m_guardRetaliateMachine;
};

StateReturnType AIGuardRetaliateState::onEnter()
{
	Object *obj = getMachineOwner();
	AIUpdateInterface *ai = obj->getAI();

	m_guardRetaliateMachine = new AIGuardRetaliateMachine(getMachineOwner());
	m_guardRetaliateMachine->setTargetPositionToGuard(ai->getGoalPosition());

	Object *goalObject = ai->getGoalObject();
	if (goalObject)
	{
		if ((goalObject->m_kindFlags & 0x20) != 0)
		{
			Object *resolved = goalObject->bfmeResolveMeleeTarget(0);
			if (resolved != 0)
				goalObject = goalObject->bfmeResolveMeleeTarget(0);
		}
		m_guardRetaliateMachine->setNemesisID(goalObject->getID());
	}

	return m_guardRetaliateMachine->initDefaultState();
}

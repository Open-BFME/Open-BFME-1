// ?onEnter@AIGuardRetaliateState@@UAE?AW4StateReturnType@@XZ
// partial score=0.99 date=2026-09-03
// cl: /DNDEBUG /MD /EHsc

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

class AIUpdateInterface
{
public:
	unsigned char m_aiFields[0x30];
	StateMachine *m_stateMachine;
};

class Object
{
public:
	Object *bfmeResolveMeleeTarget(int index);

	__forceinline AIUpdateInterface *getAI() { return m_ai; }
	__forceinline const AIUpdateInterface *getAI() const { return m_ai; }

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

	unsigned char m_machineFields04[0x0c];
	Object *m_owner;
	unsigned char m_machineFields14[0x10];
	Coord3D m_goalPosition;

	Object *getGoalObject();
};

#pragma comment(linker, "/alternatename:?getGoalObject@StateMachine@@QAEPAVObject@@XZ=?j_0000e570@@YAXXZ")

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

	unsigned char m_machineFields04[0x40];
	Coord3D m_position;
	unsigned int m_nemesisID;
};

class AIGuardRetaliateState
{
public:
	virtual StateReturnType onEnter();

	unsigned char m_stateFields04[0x18];
	StateMachine *m_machine;
	unsigned char m_stateFields20[4];
	AIGuardRetaliateMachine *m_guardRetaliateMachine;
};

// ?onEnter@AIGuardRetaliateState@@UAE?AW4StateReturnType@@XZ
StateReturnType AIGuardRetaliateState::onEnter()
{
	AIUpdateInterface *ai = m_machine->m_owner->m_ai;
	m_guardRetaliateMachine = new AIGuardRetaliateMachine(m_machine->m_owner);
	m_guardRetaliateMachine->m_position = ai->m_stateMachine->m_goalPosition;

	Object *goalObject = ai->m_stateMachine->getGoalObject();
	if (goalObject != 0)
	{
		if ((goalObject->m_kindFlags & 0x20) != 0)
		{
			Object *resolved = goalObject->bfmeResolveMeleeTarget(0);
			if (resolved != 0)
				goalObject = goalObject->bfmeResolveMeleeTarget(0);
		}
		m_guardRetaliateMachine->m_nemesisID = goalObject->m_id;
	}

	return m_guardRetaliateMachine->initDefaultState();
}

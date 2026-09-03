// cl: /DNDEBUG /MD /EHsc
// Retail 0x00170460: AIStateMachine::clear.

typedef int ObjectID;

enum StateExitType
{
	EXIT_NORMAL = 0,
	EXIT_RESET = 1
};

class Object
{
	unsigned char m_unreconstructed_000[0x1f8];

public:
	void *m_tail;
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;
extern void j_0003d613();

class State
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void onExit(StateExitType status) = 0;
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Rva00170460GoalHelper
{
public:
	void setGoalObject(const Object *object);
};

#pragma comment(linker, "/alternatename:?setGoalObject@Rva00170460GoalHelper@@QAEXPBVObject@@@Z=?j_00027b42@@YAXXZ")

class StateMachine
{
public:
	void setGoalPosition(const Coord3D *position);
};

class Rva00170460AIStateMachine
{
	unsigned char m_unreconstructed_004[0x0c];
	Object *m_owner;
	unsigned char m_unreconstructed_014[0x44];
	State *m_temporaryState;
	int m_temporaryStateFrameEnd;
	ObjectID m_goalObjectID;
	Coord3D m_goalPosition;

public:
	virtual void clear();
};

typedef void (__fastcall *Rva00170460Tail)(void *);

void Rva00170460AIStateMachine::clear()
{
	if (m_temporaryState)
	{
		m_temporaryState->onExit(EXIT_RESET);
		Object *goalObject = TheGameLogic->findObjectByID(m_goalObjectID);
		((Rva00170460GoalHelper *)this)->setGoalObject(goalObject);
		((StateMachine *)this)->setGoalPosition(&m_goalPosition);
		m_goalObjectID = 0;
		m_temporaryState = 0;

		Object *owner = m_owner;
		if (owner && owner->m_tail)
		{
			((Rva00170460Tail)j_0003d613)(owner->m_tail);
		}
	}
}

// cl: /DNDEBUG /MD /EHsc
// Rva0016CF40State::onEnter, retail 0x0016D050 (118B).
// The sibling xfer body at 0x0016CF40 fixes the state and child-machine
// layout. The child constructor is the retail ILT at 0x0003FE4F.

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

class Object;

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

	char m_machineFields04[0x0c];
	Object *m_owner;
	char m_machineFields14[0x10];
	Coord3D m_goalPosition;
	char m_machineTail[0x14];

	Object *getOwner() const
	{
		return m_owner;
	}

	void setGoalPosition(const Coord3D *position);
};

#pragma comment(linker, "/alternatename:?setGoalPosition@StateMachine@@QAEXPBUCoord3D@@@Z=?j_0000314d@@YAXXZ")

class Rva0016CF40Machine : public StateMachine
{
public:
	Rva0016CF40Machine(Object *owner);
};

#pragma comment(linker, "/alternatename:??0Rva0016CF40Machine@@QAE@PAVObject@@@Z=?j_0003fe4f@@YAXXZ")

class Rva0016CF40State
{
public:
	virtual StateReturnType onEnter();

	char m_stateFields04[0x18];
	StateMachine *m_machine;
	char m_stateFields20[4];
	Rva0016CF40Machine *m_stateMachine0016CF40;
};

StateReturnType Rva0016CF40State::onEnter()
{
	m_stateMachine0016CF40 = new Rva0016CF40Machine(m_machine->getOwner());
	m_stateMachine0016CF40->setGoalPosition(&m_machine->m_goalPosition);
	return m_stateMachine0016CF40->initDefaultState();
}

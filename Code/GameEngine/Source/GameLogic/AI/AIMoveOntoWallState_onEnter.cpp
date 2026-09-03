// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline

#include "StringInline.h"

enum StateReturnType
{
	STATE_CONTINUE = 0
};

class Object;

struct Coord3D
{
	float x;
	float y;
	float z;
};

class StateMachine
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual StateReturnType initDefaultState();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void setGoalObject( const Object *object );
	virtual void slot15();

	public:
	unsigned char m_machineFields[ 0x0C ];
	Object *m_owner;
	unsigned char m_machineFields14[ 0x10 ];
	Coord3D m_goalPosition;
	unsigned char m_machineTail[ 0x14 ];

	public:
	Object *getOwner() const { return m_owner; }
	Object *getGoalObject();
	void setGoalPosition( const Coord3D *position );
};

#pragma comment(linker, "/alternatename:?getGoalObject@StateMachine@@QAEPAVObject@@XZ=?j_0000e570@@YAXXZ")
#pragma comment(linker, "/alternatename:?setGoalPosition@StateMachine@@QAEXPBUCoord3D@@@Z=?j_0000314d@@YAXXZ")

class MoveOntoWallStateMachine : public StateMachine
{
public:
	MoveOntoWallStateMachine( Object *, AsciiString );
};

class AIMoveOntoWallState
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual StateReturnType onEnter();

	Object *getMachineOwner() const;

private:
	unsigned char m_stateFields[ 0x18 ];
	StateMachine *m_machine;
	unsigned char m_stateFields20[ 4 ];
	MoveOntoWallStateMachine *m_moveMachine;
};

#pragma comment(linker, "/alternatename:?getMachineOwner@AIMoveOntoWallState@@QBEPAVObject@@XZ=?j_0000e570@@YAXXZ")

// ?onEnter@AIMoveOntoWallState@@UAE?AW4StateReturnType@@XZ
StateReturnType AIMoveOntoWallState::onEnter()
{
	m_moveMachine = new MoveOntoWallStateMachine(
		m_machine->getOwner(), AsciiString( "MoveOntoWallStateMachine" ) );
	m_moveMachine->setGoalObject( m_machine->getGoalObject() );
	m_moveMachine->setGoalPosition( &m_machine->m_goalPosition );
	m_moveMachine->initDefaultState();
	return STATE_CONTINUE;
}

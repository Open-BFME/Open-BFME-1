// cl: /DNDEBUG /MD /EHsc
// readable body of ?getGoalObject@StateMachine@@: game/GameEngine/Source/Common/StateMachine.cpp

// StateMachine::getGoalObject, retail 0x000A1490. Sixteen bytes: read the goal
// id at +0x20 and hand it to TheGameLogic's lookup, as a tail call - the id is
// pushed before the global is even loaded, and nothing is done with the result.

typedef int ObjectID;

class Object;
class State;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	Object *findObjectByID( ObjectID id );
};

extern GameLogic *TheGameLogic;				// 0x012F0898

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class StateMachine
{
public:
	virtual void halt( void );
	Object *getGoalObject( void );

private:
	unsigned char m_unmodelled_00[ 0x18 ];
	State *m_currentState;				// +0x1c
	ObjectID m_goalObjectID;				// +0x20
	unsigned char m_unmodelled_24[ 0x1c ];
	unsigned char m_locked;				// +0x40
};

// ?getGoalObject@StateMachine@@QAEPAVObject@@XZ
Object *StateMachine::getGoalObject( void )
{
	return TheGameLogic->findObjectByID( m_goalObjectID );
}

// Retail 0x000A00A0 is one 12-byte body through RET at +0x0b.
// Identity/extent: targets/game/reverse/identity_evidence/000a00a0-halt.md
void StateMachine::halt( void )
{
	m_locked = 1;
	m_currentState = 0; // Halt does not call the current state's onExit.
}

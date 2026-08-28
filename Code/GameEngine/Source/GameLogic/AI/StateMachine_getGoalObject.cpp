// cl: /DNDEBUG /MD /EHsc
// readable body of ?getGoalObject@StateMachine@@: Code/GameEngine/Source/Common/StateMachine.cpp

// StateMachine::getGoalObject, retail 0x000A1490. Sixteen bytes: read the goal
// id at +0x20 and hand it to TheGameLogic's lookup, as a tail call - the id is
// pushed before the global is even loaded, and nothing is done with the result.

typedef int ObjectID;

class Object;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	Object *findObjectByID( ObjectID id );
};

extern GameLogic *TheGameLogic;				// 0x012F0898

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class StateMachine
{
public:
	Object *getGoalObject( void );

private:
	unsigned char m_unmodelled_00[ 0x20 ];
	ObjectID m_goalObjectID;				// +0x20
};

// ?getGoalObject@StateMachine@@QAEPAVObject@@XZ
Object *StateMachine::getGoalObject( void )
{
	return TheGameLogic->findObjectByID( m_goalObjectID );
}

// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringinline

#include "StringInline.h"

class Object;
class State;
class Xfer;
struct StateConditionInfo;

class StateMachine
{
public:
	StateMachine( Object *owner, AsciiString name, bool flag );
	virtual ~StateMachine();

protected:
	void defineState( unsigned int id, State *state,
		unsigned int successID, unsigned int failureID,
		const StateConditionInfo *conditions );
};

class Rva0014F280StateBase
{
public:
	Rva0014F280StateBase( void *machine, AsciiString name );
};

class Rva000A19E0StateBase
{
public:
	Rva000A19E0StateBase( void *machine, AsciiString name );
};

class AttackExitConditionsInterface;

class AIAttackState
{
public:
	AIAttackState( StateMachine *machine, bool follow, bool attackingObject,
		bool forceAttacking, AttackExitConditionsInterface *attackParameters );

private:
	char m_layout[ 0x54 ];
};

extern int g_AIPickUpCrateStateVTable;

class AIPickUpCrateState : public Rva0014F280StateBase
{
public:
	AIPickUpCrateState( void *machine );

private:
	int *volatile m_vftable;
	char m_gap0[ 0x4C ];
	volatile int m_delayCounter;
};

AIPickUpCrateState::AIPickUpCrateState( void *machine )
	: Rva0014F280StateBase( machine, AsciiString( "AIAttackPickUpCrateState" ) )
{
	m_vftable = &g_AIPickUpCrateStateVTable;
	m_delayCounter = 0;
}

extern int g_AIIdleStateVTable;

class AIIdleState : public Rva000A19E0StateBase
{
public:
	AIIdleState( void *machine );

private:
	int *volatile m_vftable;
	char m_gap0[ 0x20 ];
	volatile unsigned short m_nextState;
	volatile unsigned char m_finished;
	volatile unsigned char m_finishedExit;
};

AIIdleState::AIIdleState( void *machine )
	: Rva000A19E0StateBase( machine, AsciiString( "AIIdleState" ) )
{
	m_vftable = &g_AIIdleStateVTable;
	m_finished = 0;
	m_finishedExit = 0;
	m_nextState = 0xFFFF;
}

class AIAttackMoveStateMachine : public StateMachine
{
public:
	AIAttackMoveStateMachine( Object *owner, AsciiString name );

protected:
	virtual void crc( Xfer *xfer );
	virtual void xfer( Xfer *xfer );
	virtual void loadPostProcess();
};

// ??0AIAttackMoveStateMachine@@QAE@PAVObject@@VAsciiString@@@Z
AIAttackMoveStateMachine::AIAttackMoveStateMachine(
	Object *owner, AsciiString name )
	: StateMachine( owner, name, false )
{
	AIIdleState *idle = new AIIdleState( this );
	defineState( 0, (State *)idle, 0, 0, 0 );

	AIPickUpCrateState *pickUpCrate = new AIPickUpCrateState( this );
	defineState( 39, (State *)pickUpCrate, 0, 0, 0 );

	AIAttackState *attack = new AIAttackState( this, false, true, false, 0 );
	defineState( 10, (State *)attack, 0, 0, 0 );
}

// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringinline

#include "StringInline.h"

class Object;
class State;
struct StateConditionInfo;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
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
	volatile int m_field50;
};

AIPickUpCrateState::AIPickUpCrateState( void *machine )
	: Rva0014F280StateBase( machine, AsciiString( "AIAttackPickUpCrateState" ) )
{
	m_vftable = &g_AIPickUpCrateStateVTable;
	m_field50 = 0;
}

extern int g_AIIdleStateVTable;

class AIIdleState : public Rva000A19E0StateBase
{
public:
	AIIdleState( void *machine );

private:
	int *volatile m_vftable;
	char m_gap0[ 0x20 ];
	volatile unsigned short m_field24;
	volatile unsigned char m_field26;
	volatile unsigned char m_field27;
};

AIIdleState::AIIdleState( void *machine )
	: Rva000A19E0StateBase( machine, AsciiString( "AIIdleState" ) )
{
	m_vftable = &g_AIIdleStateVTable;
	m_field26 = 0;
	m_field27 = 0;
	m_field24 = 0xFFFF;
}

class AIAttackThenIdleStateMachine : public StateMachine
{
public:
	AIAttackThenIdleStateMachine( Object *owner, AsciiString name );
};

// ??0AIAttackThenIdleStateMachine@@QAE@PAVObject@@VAsciiString@@@Z
AIAttackThenIdleStateMachine::AIAttackThenIdleStateMachine(
	Object *owner, AsciiString name )
	: StateMachine( owner, name, false )
{
	AIAttackState *attack = new AIAttackState( this, false, true, false, 0 );
	defineState( 10, (State *)attack, 0, 0, 0 );

	AIPickUpCrateState *pickUpCrate = new AIPickUpCrateState( this );
	defineState( 39, (State *)pickUpCrate, 0, 0, 0 );

	AIIdleState *idle = new AIIdleState( this );
	defineState( 0, (State *)idle, 0, 0, 0 );
}

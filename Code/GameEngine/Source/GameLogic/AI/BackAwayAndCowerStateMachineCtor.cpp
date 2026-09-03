// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline

#include "StringInline.h"

class Object;
class State;
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

class Rva00170460GoalHelper
{
public:
	void setGoalObject( const Object *object );
};

#pragma comment(linker, "/alternatename:?setGoalObject@Rva00170460GoalHelper@@QAEXPBVObject@@@Z=?j_00027b42@@YAXXZ")

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

extern int g_AIBackAwayStateVTable;
extern int g_AICowerStateVTable;

class AIBackAwayState : public Rva0014F280StateBase
{
public:
	AIBackAwayState( void *machine );

private:
	int *volatile m_vftable;
	char m_gap0[ 0x4C ];
	volatile int m_field50;
	volatile unsigned char m_field54;
	char m_gap1[ 0x3 ];
	volatile unsigned char m_field58;
};

AIBackAwayState::AIBackAwayState( void *machine )
	: Rva0014F280StateBase( machine, AsciiString( "AIBackAwayState" ) )
{
	m_field54 = 0;
	m_field50 = 0;
	m_vftable = &g_AIBackAwayStateVTable;
	m_field58 = 0;
}

class AICowerState : public Rva000A19E0StateBase
{
public:
	AICowerState( void *machine );

private:
	int *volatile m_vftable;
	char m_gap0[ 0x20 ];
};

AICowerState::AICowerState( void *machine )
	: Rva000A19E0StateBase( machine, AsciiString( "AICowerState" ) )
{
	m_vftable = &g_AICowerStateVTable;
}

class BackAwayAndCowerStateMachine : public StateMachine
{
public:
	BackAwayAndCowerStateMachine( Object *owner, Object *goal, AsciiString name );
};

// ??0BackAwayAndCowerStateMachine@@QAE@PAVObject@@0VAsciiString@@@Z
BackAwayAndCowerStateMachine::BackAwayAndCowerStateMachine(
	Object *owner, Object *goal, AsciiString name )
	: StateMachine( owner, name, false )
{
	((Rva00170460GoalHelper *)this)->setGoalObject( goal );

	AIBackAwayState *backAway = new AIBackAwayState( this );
	defineState( 0, (State *)backAway, 1, 9999, 0 );

	AICowerState *cower = new AICowerState( this );
	defineState( 1, (State *)cower, 9998, 9999, 0 );
}

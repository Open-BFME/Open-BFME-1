// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringinline
//
// BFME's MoveOntoWallStateMachine constructor.  The matched
// AIMoveOntoWallState::onEnter and xfer bodies both call this two-argument
// constructor.  Its three child-state vtables and literal names identify the
// enter, exit and move-to sequence below; the middle state deliberately keeps
// an address-neutral class name because its vtable is distinct from the
// canonical AIExitState vtable.

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

extern int g_AIEnterStateVTable;
extern int g_Rva01098188StateVTable;
extern int g_AIMoveToStateVTable;

class AIEnterState : public Rva0014F280StateBase
{
public:
	AIEnterState( void *machine );

private:
	int *volatile m_vftable;
	char m_gap04[ 0x4C ];
	volatile int m_field50;
};

AIEnterState::AIEnterState( void *machine )
	: Rva0014F280StateBase( machine, AsciiString( "AIEnterState" ) )
{
	m_vftable = &g_AIEnterStateVTable;
	m_field50 = 0;
}

class Rva01098188State : public Rva000A19E0StateBase
{
public:
	Rva01098188State( void *machine );

private:
	int *volatile m_vftable;
	char m_gap04[ 0x20 ];
	volatile int m_field24;
};

Rva01098188State::Rva01098188State( void *machine )
	: Rva000A19E0StateBase( machine, AsciiString( "AIExitState" ) )
{
	m_field24 = 0;
	m_vftable = &g_Rva01098188StateVTable;
}

class AIMoveToState : public Rva0014F280StateBase
{
public:
	AIMoveToState( void *machine );

private:
	int *volatile m_vftable;
	char m_gap04[ 0x4C ];
	volatile bool m_field50;
};

AIMoveToState::AIMoveToState( void *machine )
	: Rva0014F280StateBase( machine, AsciiString( "AIMoveToState" ) )
{
	m_vftable = &g_AIMoveToStateVTable;
	m_field50 = true;
}

class MoveOntoWallStateMachine : public StateMachine
{
public:
	MoveOntoWallStateMachine( Object *owner, AsciiString name );
};

// ??0MoveOntoWallStateMachine@@QAE@PAVObject@@VAsciiString@@@Z
MoveOntoWallStateMachine::MoveOntoWallStateMachine(
	Object *owner, AsciiString name )
	: StateMachine( owner, name, false )
{
	AIEnterState *enter = new AIEnterState( this );
	defineState( 0, (State *)enter, 1, 9999, 0 );

	Rva01098188State *exit = new Rva01098188State( this );
	defineState( 1, (State *)exit, 2, 9999, 0 );

	AIMoveToState *moveTo = new AIMoveToState( this );
	defineState( 2, (State *)moveTo, 9998, 9998, 0 );
}

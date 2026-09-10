// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline

#include "../../../../../../../reference/shims/stringinline/StringInline.h"

class Object;
class State;

typedef unsigned int StateID;

struct StateConditionInfo
{
	void *test;
	StateID toStateID;
	void *userData;
};

class StateMachine
{
public:
	StateMachine( Object *owner, AsciiString name, bool flag );
	virtual ~StateMachine();

protected:
	void defineState( StateID id, State *state, StateID successID,
		StateID failureID, const StateConditionInfo *conditions );
	void setDefaultState( StateID id );
private:
 // StateMachine's constructor initializes fields through byte +0x42.
 unsigned char m_baseFields04[0x40];
};

// Retail 0x000A19E0 is State::State(StateMachine *, AsciiString), a 59-byte
// body ending in ret 8. Fields through +0x20 establish the 0x24-byte
// base extent used by each derived state. The explicit vtable member models
// the retail layout without inventing virtual method definitions.
class State
{
public:
	State( StateMachine *machine, AsciiString name );
protected:
 int *volatile m_vftable;
 StateID m_id, m_success, m_failure;
 void *m_transitionBegin, *m_transitionEnd, *m_transitionCapacity;
 StateMachine *m_machine;
 unsigned char m_flag20;
 unsigned char m_padding21[3];
};

class AIGuardMachine : public StateMachine
{
public:
	// The retail call at 0x002C05F9 goes through ILT 0x00026C15 to the
	// existing 691-byte body at 0x0015D1D0.  Its caller reserves the
	// AsciiString value slot and the body ends in ret 8, so this is the
	// two-stack-argument ABI rather than the inherited Object-only spelling.
	AIGuardMachine( Object *owner, AsciiString name );
	virtual ~AIGuardMachine(); // retail unwind35D46 reaches15B9D0
private:
 // The guard constructor writes fields +0x44 through +0x74.
 unsigned char m_guardFields44[0x34];
};

class GiantBirdGuardReturnState : public State
{
public:
	GiantBirdGuardReturnState( void *machine )
		: State( (StateMachine *)machine, AsciiString( "GiantBirdNormalFlightState" ) )
	{
		m_byte24 = 1;
		m_vftable = reinterpret_cast<int *>( 0x010C7CB8 );
		m_int28 = 0;
		m_int2c = 0;
		m_int30 = 0;
		m_int34 = 0;
	}

private:
	volatile unsigned char m_byte24;
	char m_gap25[ 3 ];
	volatile int m_int28;
	volatile int m_int2c;
	volatile int m_int30;
	volatile int m_int34;
};

class GiantBirdGuardIdleState : public State
{
public:
	GiantBirdGuardIdleState( void *machine )
		: State( (StateMachine *)machine, AsciiString( "GiantBirdGuardIdleState" ) )
	{
		m_vftable = reinterpret_cast<int *>( 0x010C7BB8 );
		m_int24 = 0;
	}

private:
	volatile int m_int24;
	char m_tail28[ 0x0C ];
};

class Rva002C03F0State : public State
{
public:
	Rva002C03F0State( void *machine );

private:
	volatile int m_int24;
	volatile int m_int28;
	volatile int m_int2c;
	volatile int m_int30;
	volatile int m_int34;
	volatile int m_int38;
	volatile int m_int3c;
	volatile int m_int40;
	volatile unsigned char m_byte44;
};

class Rva002C04D0State : public State
{
public:
	Rva002C04D0State( void *machine );

private:
	volatile int m_int24;
	volatile int m_int28;
	volatile int m_int2c;
	volatile int m_int30;
	volatile int m_int34;
	volatile int m_int38;
	volatile int m_int3c;
	volatile int m_int40;
	volatile unsigned char m_byte44;
};

class GiantBirdGuardMachine : public AIGuardMachine
{
public:
	GiantBirdGuardMachine( Object *owner );
};

GiantBirdGuardMachine::GiantBirdGuardMachine( Object *owner )
	: AIGuardMachine( owner, AsciiString( "GiantBirdGuardMachine" ) )
{
	*reinterpret_cast<int **>( this ) = reinterpret_cast<int *>( 0x010C74D8 );

	defineState( 0xB79B, (State *)new GiantBirdGuardReturnState( this ),
		0xB799, 0xB798, 0 );
	defineState( 0xB799, (State *)new GiantBirdGuardIdleState( this ),
		0xB798, 0xB79B, 0 );
	defineState( 0xB798, (State *)new Rva002C03F0State( this ),
		0xB79A, 0xB79A, 0 );
	defineState( 0xB79A, (State *)new Rva002C04D0State( this ),
		0xB79B, 0xB79B, 0 );
	setDefaultState( 0xB79B );
}

typedef char StateExtentCheck[sizeof(State) == 0x24 ? 1 : -1];
typedef char StateMachineExtentCheck[sizeof(StateMachine) == 0x44 ? 1 : -1];
typedef char GiantBirdGuardMachineExtentCheck[sizeof(GiantBirdGuardMachine) == 0x78 ? 1 : -1];

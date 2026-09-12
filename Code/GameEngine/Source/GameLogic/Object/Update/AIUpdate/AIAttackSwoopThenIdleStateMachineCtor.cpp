// ??0AIAttackSwoopThenIdleStateMachine@@QAE@PAXVAsciiString@@@Z
// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline

#include "StringInline.h"

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
	unsigned char m_rva002BF480_stateMachineTail[0x40]; // factories allocate 0x44 bytes
	void defineState( StateID id, State *state, StateID successID,
		StateID failureID, const StateConditionInfo *conditions );
};

// Rva000A19E0StateBase is the ledger's address-derived name for
// State::State(StateMachine*, AsciiString) at retail 0x000A19E0 (thunk
// 0x000035B2); kept verbatim so the already-landed sibling ctors below match
// the same shape they were proven with in GiantBirdStateConstructors.cpp.
class Rva000A19E0StateBase
{
public:
	Rva000A19E0StateBase( void *machine, AsciiString name );

	virtual void stateBaseAnchor();
};

// byte-exact reconstruction, verbatim from GiantBirdStateConstructors.cpp
// (matched out of line at 0x002BE230); inlined here at the new call site.
class AIGiantBirdSwoopState : public Rva000A19E0StateBase
{
public:
	AIGiantBirdSwoopState( void *machine, int targetID, bool enabled );

private:
	char m_gap04[ 0x20 ];
	int m_rva002BE230_024;
	char m_gap28[ 0x0C ];
	bool m_field034;
	char m_gap35[ 3 ];
	int m_field038;
	float m_rva002BE230_03C;
};

AIGiantBirdSwoopState::AIGiantBirdSwoopState( void *machine, int targetID, bool enabled )
	: Rva000A19E0StateBase( machine, AsciiString( "AIGiantBirdSwoopState" ) )
{
	m_rva002BE230_024 = targetID;
	m_field034 = enabled;
	m_field038 = 0;
	m_rva002BE230_03C = 1.0f;
}

// byte-exact reconstruction, verbatim from GiantBirdStateConstructors.cpp
// (matched out of line at 0x002BE400); inlined here at the new call site.
class AIGiantBirdAttackState : public Rva000A19E0StateBase
{
public:
	AIGiantBirdAttackState( void *machine, int mode );

private:
	char m_gap04[ 0x20 ];
	int m_rva002BE400_024;
};

AIGiantBirdAttackState::AIGiantBirdAttackState( void *machine, int mode )
	: Rva000A19E0StateBase( machine, AsciiString( "AIGiantBirdAttackState" ) )
{
	m_rva002BE400_024 = mode;
}

// byte-exact reconstruction, verbatim from GiantBirdStateConstructors.cpp
// (matched out of line at 0x002BEC00); inlined here at the new call site.
class AIGiantBirdFollowThruState : public Rva000A19E0StateBase
{
public:
	AIGiantBirdFollowThruState( void *machine, bool enabled );

private:
	char m_gap04[ 0x20 ];
	bool m_field024;
	char m_gap25[ 3 ];
	int m_field028;
};

AIGiantBirdFollowThruState::AIGiantBirdFollowThruState( void *machine, bool enabled )
	: Rva000A19E0StateBase( machine, AsciiString( "AIGiantBirdFollowThruState" ) )
{
	m_field024 = enabled;
	m_field028 = 0;
}

// Declared only: retail keeps this ctor out of line at 0x001720D0 (matched,
// Rva001720D0AIIdleLikeStateCtor.cpp) and calls it rather than inlining it.
class Rva001720D0AIIdleLikeState : public Rva000A19E0StateBase
{
public:
	Rva001720D0AIIdleLikeState( void *machine, int targetingType );

private:
	char m_stateBaseTail[ 0x20 ];
	unsigned short m_rva001720D0_024;
	bool m_rva001720D0_026;
	bool m_rva001720D0_027;
};

class AIAttackSwoopThenIdleStateMachine : public StateMachine
{
public:
	AIAttackSwoopThenIdleStateMachine( void *owner, AsciiString name );
};

// Native C++ virtual construction emits the outer vptr; no literal vptr write.
// Retail 0x006BF49A preserves incoming this in ESI; 0x006BF4D3 installs
// 0x010C7460 into [ESI]. Later [EDI] stores belong to separately allocated states.
// retail RVA 0x002BF480, 472B. Identity: this constructor installs vtable
// 0x010C7460 and defines the Swoop/Attack/FollowThru/Idle-like states whose
// own ctors are matched at 0x002BE230/0x002BE400/0x002BEC00/0x001720D0; the
// factories at 0x002BFA80 and 0x002C0370 (Rva002BFA80Factory/Rva002C0370Factory
// ::createAttackMachine) and GiantBirdAttackMoveToState's ctor already declare
// this exact class and signature, naming its return type.
AIAttackSwoopThenIdleStateMachine::AIAttackSwoopThenIdleStateMachine( void *owner, AsciiString name )
	: StateMachine( (Object *)owner, name, false )
{

	AIGiantBirdSwoopState *swoop = new AIGiantBirdSwoopState( this, 1, false );
	defineState( 10, (State *)swoop, 1012, 0, 0 );

	AIGiantBirdAttackState *attack = new AIGiantBirdAttackState( this, 1 );
	defineState( 1012, (State *)attack, 1013, 1013, 0 );

	AIGiantBirdFollowThruState *followThru = new AIGiantBirdFollowThruState( this, false );
	defineState( 1013, (State *)followThru, 0, 0, 0 );

	Rva001720D0AIIdleLikeState *idle = new Rva001720D0AIIdleLikeState( this, 1 );
	defineState( 0, (State *)idle, 0, 0, 0 );
}

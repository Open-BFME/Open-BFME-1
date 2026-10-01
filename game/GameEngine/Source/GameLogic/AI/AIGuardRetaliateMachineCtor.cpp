// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringinline
// AIGuardRetaliateMachine constructor, RVA 0x0015F240 (327 bytes).
//
// IDENTITY.  targets/game/reverse/symbols.csv pins
// ??_7AIGuardRetaliateMachine@@6B@ at 0x01096420 with the note "exact
// constructor 0x0015F240 installs this dedicated vtable", and that is the
// store at +0x48 here; the two callers are the matched
// ?onEnter@AIGuardRetaliateState@@ and ?xfer@AIGuardRetaliateState@@ bodies.
// The name literal built for the StateMachine base is "AIGuardRetaliateMachine"
// (read from the retail rdata word pushed at +0x27), the guard state's literal
// is "AIGuardRetaliateAttackAggressorState" (the twin ctor
// Rva0015F070GuardStateCtor.cpp) and the return state's is
// "AIGuardRetaliateReturn" (the twin ctor 0x0015EC40).
//
// LAYOUT.  Zero Hour's AIGuardRetaliateMachine declares exactly
// `Coord3D m_positionToGuard; ObjectID m_nemesisToAttack;` in that order, and
// this body stores three floats then one dword in that order, at +0x44..+0x4c
// and +0x50.  The base StateMachine is 0x44 bytes here against ZH's 0x38, so
// the base contribution is a gap of 0x40 after the vptr rather than a
// transcribed member list.
//
// THE STORE ORDER IS THE WHOLE BODY.  MSVC 7.1 emits the derived vptr store
// and the EH-scope entry (`mov [esp+0x1c], ebx`) as one unit at the head of
// the constructor's own region, so three scalar `= 0.0f` assignments written in
// the body let the entry sink between the second and the third of them and
// drag the vptr down with it.  Typing the position as a `Coord3D` and clearing
// it through `zero()` keeps the three stores one group, which pins the whole
// prologue: test guard / vptr / m_nemesisToAttack / EH entry / XYZ.  Same lever
// as the matched AITNGuardMachine constructor 0x0018AFB0
// (AITNGuardMachine_ctor_Bfme.cpp, "typed Coord3D zero fixes EH store order").
//
// NOT A HEADER TU.  game/GameEngine/Source/GameLogic/AI/AIGuardRetaliate.cpp is
// the Zero Hour port and its StateMachine/AIGuardRetaliateReturnState
// declarations are the reference ones, which cannot hold this BFME layout; the
// two constructors whose bodies are inlined below (AIInternalMoveToState's at
// 0x0014F280 and Rva0015F070GuardState's at 0x0015F070) are declared only,
// because both are already matched in their own TUs.

#include "StringInline.h"

class Object;
class State;

typedef bool (*StateTransFuncPtr)( State *, void * );

struct StateConditionInfo
{
	StateConditionInfo( StateTransFuncPtr testFunction, unsigned int stateID, void *data )
		: test( testFunction ), toStateID( stateID ), userData( data ) {}

	StateTransFuncPtr test;
	unsigned int toStateID;
	void *userData;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
// The matched base constructor is game/GameEngine/Source/Common/thunks_006.cpp
// (0x000A1BD0, reached here through ILT thunk 0x0000F123).
class StateMachine
{
public:
	StateMachine( Object *owner, AsciiString name, bool flag );

protected:
	// retail declares the virtual destructor protected; that access level is
	// part of the mangled name the compiler-emitted cleanup path calls.
	virtual ~StateMachine();
	void defineState( unsigned int id, State *state,
		unsigned int successID, unsigned int failureID,
		const StateConditionInfo *conditions );

private:
	char m_stateMachineData[ 0x40 ];
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x;
	float y;
	float z;

	void zero()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}
};

// The base of the return state: retail ctor 0x0014F280, matched in
// game/GameEngine/Source/GameLogic/AI/AIInternalMoveToStateCtor.cpp.
class AIInternalMoveToState
{
public:
	AIInternalMoveToState( StateMachine *machine, AsciiString name );

	virtual void stateBaseAnchor();
};

// The out-of-line twin of this class's constructor is 0x0015EC40
// (StateSelfNamingCtorsWithFields.cpp), which seats the same vtable
// 0x01096520 and zeroes the same +0x50 field; the layout below is the one
// AIGuardRetaliateReturnState_onEnter_Bfme.cpp already uses for this class.
class AIGuardRetaliateReturnState : public AIInternalMoveToState
{
public:
	AIGuardRetaliateReturnState( StateMachine *machine )
		: AIInternalMoveToState( machine, AsciiString( "AIGuardRetaliateReturn" ) ),
		  m_nextReturnScanTime( 0 )
	{
	}

private:
	char m_gap04[ 0x4C ];
	volatile unsigned int m_nextReturnScanTime;
};

// The attack state: retail ctor 0x0015F070, matched in
// game/GameEngine/Source/GameLogic/AI/Rva0015F070GuardStateCtor.cpp.  Only
// its size (0x48) is read here, by the `new` at +0x95.
class Rva0015F070GuardState
{
public:
	Rva0015F070GuardState( StateMachine *machine );

private:
	char m_stateData[ 0x48 ];
};

// The static condition table this constructor guard-initialises at 0x012EF288
// stores this address in its first `test` field.  The retail body is three
// bytes, `xor al, al` / `ret`; it is a table of code addresses and no source
// body claims it, so the pin names the address only.
extern "C" bool __cdecl Rva0015E720StatePredicate( State *, void * );

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIGuardRetaliate.h
class AIGuardRetaliateMachine : public StateMachine
{
public:
	AIGuardRetaliateMachine( Object *owner );

protected:
	// snapshot interface
	virtual void crc( void *xfer );
	virtual void xfer( void *xfer );
	virtual void loadPostProcess();

private:
	Coord3D m_positionToGuard;
	volatile unsigned int m_nemesisToAttack;
};

// ??0AIGuardRetaliateMachine@@QAE@PAVObject@@@Z
AIGuardRetaliateMachine::AIGuardRetaliateMachine( Object *owner )
	: StateMachine( owner, AsciiString( "AIGuardRetaliateMachine" ), false ),
	  m_nemesisToAttack( 0 )
{
	m_positionToGuard.zero();

	static const StateConditionInfo attackAggressors[] =
	{
		StateConditionInfo( Rva0015E720StatePredicate, 5005, 0 ),
		StateConditionInfo( 0, 0, 0 )	// keep last
	};

	// order matters: the first state defined is the machine's start state.
	Rva0015F070GuardState *attack = new Rva0015F070GuardState( this );
	defineState( 5005, (State *)attack, 5003, 5003, 0 );

	AIGuardRetaliateReturnState *returnState = new AIGuardRetaliateReturnState( this );
	defineState( 5003, (State *)returnState, 9998, 5005, attackAggressors );
}

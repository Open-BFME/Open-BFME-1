// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline

#include "StringInline.h"

class Object;
class State;
class AIAttackState;
struct StateConditionInfo;
class NotifyWeaponFiredInterface;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class State
{
public:
	State( StateMachine *machine, AsciiString name );
	virtual ~State();

private:
	unsigned char m_head[ 0x20 ];
};

typedef bool (*Rva00171B40StateTransFunc)( State *state,
	void *userData );

struct StateConditionInfo
{
	Rva00171B40StateTransFunc test;
	unsigned int toStateID;
	void *userData;

	StateConditionInfo( Rva00171B40StateTransFunc t, unsigned int id,
		void *ud )
		: test( t ), toStateID( id ), userData( ud )
	{
	}
};

class Rva00171B40AIAttackFireWeaponState : public State
{
public:
	Rva00171B40AIAttackFireWeaponState(
		StateMachine *machine, NotifyWeaponFiredInterface *notify );

private:
	NotifyWeaponFiredInterface *m_notify;
	bool m_finished;
};

// ??0Rva00171B40AIAttackFireWeaponState@@QAE@XZ absent-from-retail
Rva00171B40AIAttackFireWeaponState::Rva00171B40AIAttackFireWeaponState(
StateMachine *machine, NotifyWeaponFiredInterface *notify )
	: State( machine, AsciiString( "AIAttackFireWeaponState" ) ),
	  m_notify( notify ),
	  m_finished( false )
{
}

class Rva00171B40AIWaitUntilFinishedFiringState : public State
{
public:
	Rva00171B40AIWaitUntilFinishedFiringState(
		StateMachine *machine );
};

Rva00171B40AIWaitUntilFinishedFiringState::
	Rva00171B40AIWaitUntilFinishedFiringState(
		StateMachine *machine )
	: State( machine,
		AsciiString( "AIWaitUntilFinishedFiringState" ) )
{
}

class Rva00171B40AttackHordeStateMachine : public StateMachine
{
public:
	Rva00171B40AttackHordeStateMachine(
		Object *owner, AIAttackState *attack, AsciiString name );
};

// ??0AttackHordeStateMachine@@QAE@PAVObject@@PAVAIAttackState@@VAsciiString@@@Z
Rva00171B40AttackHordeStateMachine::Rva00171B40AttackHordeStateMachine(
	Object *owner, AIAttackState *attack, AsciiString name )
: StateMachine( owner, name, false )
{
	static const StateConditionInfo conditions[] =
	{
		StateConditionInfo(
			(Rva00171B40StateTransFunc)0x00571B20, 0x270f, 0 ),
		StateConditionInfo(
			(Rva00171B40StateTransFunc)0x0056af70, 0x270f, (void *)2 ),
		StateConditionInfo( 0, 0, 0 )
	};

	Rva00171B40AIAttackFireWeaponState *fire =
		new Rva00171B40AIAttackFireWeaponState(
			this, attack ? (NotifyWeaponFiredInterface *)((char *)attack + 0x24) : 0 );
	defineState( 0x1f4, (State *)fire, 0x1f5, 0x270f,
		(const StateConditionInfo *)conditions );

	Rva00171B40AIWaitUntilFinishedFiringState *wait =
		new Rva00171B40AIWaitUntilFinishedFiringState( this );
	defineState( 0x1f5, (State *)wait, 0x1f4, 0x270f,
		(const StateConditionInfo *)conditions );
}

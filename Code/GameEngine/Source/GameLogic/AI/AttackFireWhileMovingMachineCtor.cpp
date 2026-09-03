// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline

#include "StringInline.h"

class Object;
class AIAttackState;
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

class Rva000A19E0StateBase
{
public:
	Rva000A19E0StateBase( void *machine, AsciiString name );

	virtual void stateBaseAnchor();

private:
	unsigned char m_head[ 0x20 ];
};

class Rva0014F280StateBase
{
public:
	Rva0014F280StateBase( void *machine, AsciiString name );
};

class AIAttackFireDuringApproachState
{
public:
	AIAttackFireDuringApproachState( StateMachine *machine );

private:
	char m_storage[ 0x70 ];
};

class AIAttackAimAtTargetState : public Rva000A19E0StateBase
{
public:
	AIAttackAimAtTargetState( StateMachine *machine, bool canTurnInPlace,
		bool setLocomotor );

private:
	bool m_canTurnInPlace;
	bool m_reserved25;
	bool m_reserved26;
	bool m_setLocomotor;
};

AIAttackAimAtTargetState::AIAttackAimAtTargetState(
	StateMachine *machine, bool canTurnInPlace, bool setLocomotor )
	: Rva000A19E0StateBase( machine, AsciiString( "AIAttackAimAtTargetState" ) )
{
	m_canTurnInPlace = canTurnInPlace;
	m_reserved25 = false;
	m_reserved26 = false;
	m_setLocomotor = setLocomotor;
}

class NotifyWeaponFiredInterface;

class AIAttackFireWeaponState : public Rva000A19E0StateBase
{
public:
	AIAttackFireWeaponState( StateMachine *machine,
		NotifyWeaponFiredInterface *notify );

private:
	NotifyWeaponFiredInterface *m_notify;
	bool m_finished;
};

AIAttackFireWeaponState::AIAttackFireWeaponState(
	StateMachine *machine, NotifyWeaponFiredInterface *notify )
	: Rva000A19E0StateBase( machine, AsciiString( "AIAttackFireWeaponState" ) ),
	  m_notify( notify ),
	  m_finished( false )
{
}

class AIWaitUntilFinishedFiringState : public Rva000A19E0StateBase
{
public:
	AIWaitUntilFinishedFiringState( StateMachine *machine );
};

AIWaitUntilFinishedFiringState::AIWaitUntilFinishedFiringState(
	StateMachine *machine )
	: Rva000A19E0StateBase( machine,
		AsciiString( "AIWaitUntilFinishedFiringState" ) )
{
}

class AttackFireWhileMovingMachine : public StateMachine
{
public:
	AttackFireWhileMovingMachine( Object *owner, AIAttackState *attack,
		AsciiString name );
};

// ??0AttackFireWhileMovingMachine@@QAE@PAVObject@@PAVAIAttackState@@VAsciiString@@@Z
AttackFireWhileMovingMachine::AttackFireWhileMovingMachine(
	Object *owner, AIAttackState *attack, AsciiString name )
	: StateMachine( owner, name, false )
{
	AIAttackFireDuringApproachState *approach =
		new AIAttackFireDuringApproachState( this );
	defineState( 0x12D, (State *)approach, 0x12E, 0x270F, 0 );

	AIAttackAimAtTargetState *aim =
		new AIAttackAimAtTargetState( this, true, false );
	defineState( 0x12E, (State *)aim, 0x12F, 0x12D, 0 );

	AIAttackFireWeaponState *fire =
		new AIAttackFireWeaponState(
			this, attack ? (NotifyWeaponFiredInterface *)((char *)attack + 0x24) : 0 );
	defineState( 0x12F, (State *)fire, 0x130, 0x12D, 0 );

	AIWaitUntilFinishedFiringState *wait =
		new AIWaitUntilFinishedFiringState( this );
	defineState( 0x130, (State *)wait, 0x12D, 0x12D, 0 );
}

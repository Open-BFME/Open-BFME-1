// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline

#include "StringInline.h"

class Object;
class AIAttackState;
class State;
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

// Witnessed BFME layout: the movement-state objects carry their derived
// vftable at +0 and the path/movement slice through +0x50.  The complete
// header is intentionally not reproduced here; this TU-local ABI view keeps
// the base call named while spelling the bytes that this constructor owns.
class AIInternalMoveToState
{
public:
	AIInternalMoveToState( StateMachine *machine, AsciiString name );
};

extern int g_AIAttackMeleeApproachStateVTable;

class AIAttackMeleeApproachState : public AIInternalMoveToState
{
public:
	AIAttackMeleeApproachState( StateMachine *machine );

private:
	int *volatile m_vftable;
	char m_baseFields[ 0x4c ];
	volatile int m_field50;
	volatile int m_field54;
	volatile int m_field58;
	volatile int m_field5c;
	volatile int m_field60;
	volatile int m_field64;
};

// ??0AIAttackMeleeApproachState@@QAE@PAVStateMachine@@@Z absent-from-retail
AIAttackMeleeApproachState::AIAttackMeleeApproachState(
	StateMachine *machine )
	: AIInternalMoveToState(
		machine, AsciiString( "AIAttackMeleeApproachState" ) )
{
	m_vftable = &g_AIAttackMeleeApproachStateVTable;
	m_field50 = 0;
	m_field54 = 0;
	m_field58 = 0;
	m_field5c = 0;
	m_field60 = 0;
	m_field64 = 0;
}

class AIAttackMeleeSquishState : public AIInternalMoveToState
{
public:
	AIAttackMeleeSquishState( StateMachine *machine );

private:
	int *volatile m_vftable;
	char m_baseFields[ 0x4c ];
	volatile int m_field50;
	volatile int m_field54;
	volatile int m_field58;
	volatile int m_field5c;
	volatile int m_field60;
	volatile int m_field64;
	volatile bool m_field68;
};

class AIAttackMeleeEngageState : public AIInternalMoveToState
{
public:
	AIAttackMeleeEngageState( StateMachine *machine, int targetID );

private:
	int *volatile m_vftable;
	char m_baseFields[ 0x4c ];
	volatile int m_field50;
	volatile int m_field54;
	volatile int m_field58;
	volatile int m_field5c;
	volatile int m_field60;
	volatile int m_field64;
	volatile int m_field68;
	volatile int m_field6c;
	volatile int m_field70;
	volatile bool m_field74;
	volatile bool m_field75;
	char m_padding76[ 2 ];
	volatile int m_targetID;
};

class AIMeleeReAcquireState : public State
{
public:
	AIMeleeReAcquireState( StateMachine *machine );

private:
	int m_field24;
};

// ??0AIMeleeReAcquireState@@QAE@PAVStateMachine@@@Z absent-from-retail
AIMeleeReAcquireState::AIMeleeReAcquireState( StateMachine *machine )
	: State( machine, AsciiString( "AIMeleeReAcquireState" ) )
{
	m_field24 = 0;
}

class AIAttackAimAtTargetState : public State
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
	: State( machine, AsciiString( "AIAttackAimAtTargetState" ) )
{
	m_canTurnInPlace = canTurnInPlace;
	m_reserved25 = false;
	m_reserved26 = false;
	m_setLocomotor = setLocomotor;
}

class AIAttackFireWeaponState : public State
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
	: State( machine, AsciiString( "AIAttackFireWeaponState" ) ),
	  m_notify( notify ),
	  m_finished( false )
{
}

class AIWaitUntilFinishedFiringState : public State
{
public:
	AIWaitUntilFinishedFiringState( StateMachine *machine );
};

// ??0AIWaitUntilFinishedFiringState@@QAE@PAVStateMachine@@@Z absent-from-retail
AIWaitUntilFinishedFiringState::AIWaitUntilFinishedFiringState(
	StateMachine *machine )
	: State( machine, AsciiString( "AIWaitUntilFinishedFiringState" ) )
{
}

class AttackMeleeStateMachine : public StateMachine
{
public:
	AttackMeleeStateMachine( Object *owner, AIAttackState *attack,
		AsciiString name );
};

// ??0AttackMeleeStateMachine@@QAE@PAVObject@@PAVAIAttackState@@VAsciiString@@@Z
AttackMeleeStateMachine::AttackMeleeStateMachine(
	Object *owner, AIAttackState *attack, AsciiString name )
	: StateMachine( owner, name, false )
{
	AIAttackMeleeApproachState *approach =
		new AIAttackMeleeApproachState( this );
	defineState( 0xe1, (State *)approach, 0xe2, 0x270f, 0 );

	AIAttackMeleeSquishState *squish =
		new AIAttackMeleeSquishState( this );
	defineState( 0xe9, (State *)squish, 0xe2, 0x270f, 0 );

	AIAttackMeleeEngageState *engage =
		new AIAttackMeleeEngageState(
			this, attack ? (int)((char *)attack + 0x24) : 0 );
	defineState( 0xe2, (State *)engage, 0xe6, 0xe5, 0 );

	AIMeleeReAcquireState *reacquire =
		new AIMeleeReAcquireState( this );
	defineState( 0xe5, (State *)reacquire, 0xe1, 0x270f, 0 );

	AIAttackAimAtTargetState *aim =
		new AIAttackAimAtTargetState( this, true, false );
	defineState( 0xe6, (State *)aim, 0xe7, 0xe1, 0 );

	AIAttackFireWeaponState *fire =
		new AIAttackFireWeaponState(
			this, attack ? (NotifyWeaponFiredInterface *)((char *)attack + 0x24) : 0 );
	defineState( 0xe7, (State *)fire, 0xe8, 0xe1, 0 );

	AIWaitUntilFinishedFiringState *wait =
		new AIWaitUntilFinishedFiringState( this );
	defineState( 0xe8, (State *)wait, 0xe1, 0xe1, 0 );
}

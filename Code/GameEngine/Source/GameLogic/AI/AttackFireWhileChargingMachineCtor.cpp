// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline

#include "StringInline.h"

class Object;
class AIAttackState;
class State;
struct StateConditionInfo;

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

class Rva0014F280StateBase
{
public:
	Rva0014F280StateBase( void *machine, AsciiString name );

	virtual void stateBaseAnchor();
};

class AIChargeTargetState : public Rva0014F280StateBase
{
public:
	AIChargeTargetState( void *machine );

private:
	char m_gap0[ 0x4C ];
	unsigned char m_field50;
	char m_gap1[ 0x3 ];
	int m_field54;
	unsigned char m_field58;
	unsigned char m_field59;
};

AIChargeTargetState::AIChargeTargetState( void *machine )
	: Rva0014F280StateBase( machine, AsciiString( "AIChargeTargetState" ) ),
	  m_field50( 0 ),
	  m_field54( 1 ),
	  m_field58( 0 ),
	  m_field59( 0 )
{
}

class AttackFireWhileChargingMachine : public StateMachine
{
public:
	AttackFireWhileChargingMachine( Object *owner, AIAttackState *attack,
		AsciiString name, bool flag );
};

// ??0AttackFireWhileChargingMachine@@QAE@PAVObject@@PAVAIAttackState@@VAsciiString@@_N@Z
AttackFireWhileChargingMachine::AttackFireWhileChargingMachine(
	Object *owner, AIAttackState *attack, AsciiString name, bool flag )
	: StateMachine( owner, name, flag )
{
	AIChargeTargetState *state = new AIChargeTargetState( this );
	defineState( 0, (State *)state, 9998, 9999, 0 );
}

// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline
// Near-twin of AIGuardInnerState::AIGuardInnerState (twin 0x0015CE00,
// Code/GameEngine/Source/GameLogic/AI/AIGuardStateConstructors.cpp): same
// State-derived constructor shape, but the trailing member here is stored as
// a full dword rather than a byte -- the one non-relocation byte the twin
// scan found.
//
// The name string, read straight from the retail rdata at the pushed
// literal address, is "AIGuardRetaliateAttackAggressorState" -- ZH's class of
// that exact name (GeneralsMD/.../AIGuardRetaliate.h:239) declares only
// `GuardRetaliateExitConditions m_exitConditions;` and
// `AIAttackState *m_attackState;`, one pointer after the exit-conditions
// block, but these bytes null TWO trailing dwords after that block (+0x40
// and +0x44). BFME evidently added a field to this class beyond the ZH
// declaration, so the class here is address-derived rather than claiming the
// ZH layout outright; the proven string is kept as evidence.

#include "StringInline.h"

class StateMachine;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x;
	float y;
	float z;
	void zero() { x = 0.0f; y = 0.0f; z = 0.0f; }
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class State
{
public:
	State( StateMachine *machine, AsciiString name );
	virtual void stateAnchor();

private:
	char m_stateData[ 0x20 ];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIGuard.h
class ExitConditions
{
public:
	ExitConditions() :
		m_conditionsToConsider( 0 ),
		m_attackGiveUpFrame( 0 ),
		m_radiusSqr( 0.0f )
	{
		m_center.zero();
	}

	virtual bool shouldExit( const StateMachine *machine ) const { return false; }

private:
	int m_conditionsToConsider;
	Coord3D m_center;
	float m_radiusSqr;
	unsigned int m_attackGiveUpFrame;
};

// address-derived: exit-conditions block matching GuardRetaliateExitConditions
// (same fields/size as ExitConditions), plus two trailing pointer-sized
// members -- one more than ZH's declared AIGuardRetaliateAttackAggressorState.
class Rva0015F070GuardState : public State
{
public:
	Rva0015F070GuardState( StateMachine *machine );
	virtual bool isAttack() const;

private:
	ExitConditions m_exitConditions;
	void *m_attackState;
	void *m_field44;
};

// @??0Rva0015F070GuardState@@QAE@PAVStateMachine@@@Z 0x0015F070
Rva0015F070GuardState::Rva0015F070GuardState( StateMachine *machine ) :
	State( machine, AsciiString( "AIGuardRetaliateAttackAggressorState" ) )
{
	m_attackState = 0;
	m_field44 = 0;
}

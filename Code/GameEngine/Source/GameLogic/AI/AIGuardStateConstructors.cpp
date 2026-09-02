// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline
// BFME AIGuard state constructors.  The inline AsciiString forwarders preserve
// MSVC 7.1's in-place by-value temporary and saved-ESP ordering.

#include "StringInline.h"

class StateMachine;

struct Coord3D
{
	float x;
	float y;
	float z;
	void zero() { x = 0.0f; y = 0.0f; z = 0.0f; }
};

class State
{
public:
	State( StateMachine *machine, AsciiString name );
	virtual void stateAnchor();

private:
	char m_stateData[ 0x20 ];
};

class ExitConditions
{
public:
	ExitConditions() :
		m_attackGiveUpFrame( 0 ),
		m_conditionsToConsider( 0 ),
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

class AIGuardInnerState : public State
{
public:
	AIGuardInnerState( StateMachine *machine );
	virtual bool isAttack() const;

private:
	ExitConditions m_exitConditions;
	void *m_attackState;
	bool m_enterState;
};

AIGuardInnerState::AIGuardInnerState( StateMachine *machine ) :
	State( machine, AsciiString( "AIGuardInner" ) )
{
	m_attackState = 0;
	m_enterState = false;
}

class AIGuardOuterState : public State
{
public:
	AIGuardOuterState( StateMachine *machine );
	virtual bool isAttack() const;

private:
	ExitConditions m_exitConditions;
	void *m_attackState;
	bool m_unusedFlag;
};

AIGuardOuterState::AIGuardOuterState( StateMachine *machine ) :
	State( machine, AsciiString( "AIGuardOuter" ) )
{
	m_unusedFlag = false;
	m_attackState = 0;
}

class AIGuardAttackAggressorState : public State
{
public:
	AIGuardAttackAggressorState( StateMachine *machine );
	virtual bool isAttack() const;

private:
	ExitConditions m_exitConditions;
	void *m_attackState;
	bool m_unusedFlag;
};

AIGuardAttackAggressorState::AIGuardAttackAggressorState( StateMachine *machine ) :
	State( machine, AsciiString( "AIGuardAttackAggressorState" ) )
{
	m_unusedFlag = false;
	m_attackState = 0;
}

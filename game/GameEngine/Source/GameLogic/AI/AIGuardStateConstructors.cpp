// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringinline
// readable body of ??0AIGuardAttackAggressorState@@: game/GameEngine/Source/GameLogic/AI/AIGuard.cpp
// BFME AIGuard state constructors.  The inline AsciiString forwarders preserve
// MSVC 7.1's in-place by-value temporary and saved-ESP ordering.

#include "StringInline.h"

class StateMachine;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
#include "../../../../Libraries/Include/Lib/Coord3D.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class State
{
public:
	State( StateMachine *machine, AsciiString name );
	virtual void stateAnchor();

private:
	char m_stateData[ 0x20 ];
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIGuard.h
class ExitConditions
{
public:
	ExitConditions() :
		m_attackGiveUpFrame( 0 ),
		m_conditionsToConsider( 0 ),
		m_radiusSqr( 0.0f )
	{
		{ Coord3D *const position = &m_center; position->x = 0.0f; position->y = 0.0f; position->z = 0.0f; }
	}

	virtual bool shouldExit( const StateMachine *machine ) const { return false; }

private:
	int m_conditionsToConsider;
	Coord3D m_center;
	float m_radiusSqr;
	unsigned int m_attackGiveUpFrame;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIGuard.h
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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIGuard.h
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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIGuard.h
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

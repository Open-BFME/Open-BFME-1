// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

#include "string_base.h"

#include "ascii_string.h"

class StateMachine;

class AIInternalMoveToState
{
public:
	AIInternalMoveToState( void *machine, AsciiString name );

	virtual void stateBaseAnchor();
};

class AIFollowPathState : public AIInternalMoveToState
{
public:
	AIFollowPathState( StateMachine *machine, AsciiString name );

private:
	// Names and initial values agree with AIStateMachine.h and the BFME layout witness.
	char m_baseFields[ 0x4C ];
	int m_index;
	unsigned char m_adjustFinal;
	unsigned char m_adjustFinalOverride;
	char m_field56And57[ 2 ];
	int m_retryCount;
};

AIFollowPathState::AIFollowPathState( StateMachine *machine, AsciiString name )
	: AIInternalMoveToState( machine, name ),
	  m_index( 0x0 ),
	  m_adjustFinal( 0x1 ),
	  m_adjustFinalOverride( 0x0 ),
	  m_retryCount( 0xA )
{
}

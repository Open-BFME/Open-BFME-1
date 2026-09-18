// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib

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
	char m_baseFields[ 0x4C ];
	int m_field50;
	unsigned char m_field54;
	unsigned char m_field55;
	char m_field56And57[ 2 ];
	int m_field58;
};

AIFollowPathState::AIFollowPathState( StateMachine *machine, AsciiString name )
	: AIInternalMoveToState( machine, name ),
	  m_field50( 0x0 ),
	  m_field54( 0x1 ),
	  m_field55( 0x0 ),
	  m_field58( 0xA )
{
}

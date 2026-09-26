// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

#include "../../../../../../Libraries/Source/WWVegas/WWLib/string_base.h"

#include "ascii_string.h"

class AIAttackSwoopThenIdleStateMachine
{
public:
	AIAttackSwoopThenIdleStateMachine( void *owner, AsciiString name );

private:
	unsigned char m_unreconstructed[ 0x44 ];
};

class Rva002BFA80Factory
{
public:
	AIAttackSwoopThenIdleStateMachine *createAttackMachine();

private:
	unsigned char m_unreconstructed00[ 0x10 ];
	void *m_owner;
};

AIAttackSwoopThenIdleStateMachine *Rva002BFA80Factory::createAttackMachine()
{
	return new AIAttackSwoopThenIdleStateMachine(
		m_owner, AsciiString( "AIAttackSwoopThenIdleStateMachine" ) );
}

// cl: /DNDEBUG /MD /EHsc

#include "../../../../../../Libraries/Source/WWVegas/WWLib/string_base.h"

class AsciiString
{
public:
	AsciiString( const char *text ) : m_string( text ) {}

private:
	StringBase<char> m_string;
};

class AIAttackSwoopThenIdleStateMachine
{
public:
	AIAttackSwoopThenIdleStateMachine( void *owner, AsciiString name );

private:
	unsigned char m_unreconstructed[ 0x44 ];
};

class Rva002C0370Factory
{
public:
	AIAttackSwoopThenIdleStateMachine *createAttackMachine();

private:
	unsigned char m_unreconstructed00[ 0x10 ];
	void *m_owner;
};

AIAttackSwoopThenIdleStateMachine *Rva002C0370Factory::createAttackMachine()
{
	return new AIAttackSwoopThenIdleStateMachine(
		m_owner, AsciiString( "AIAttackSwoopThenIdleStateMachine" ) );
}

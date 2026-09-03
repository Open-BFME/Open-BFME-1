// cl: /DNDEBUG /MD /EHsc

#include "../../../../../../Libraries/Source/WWVegas/WWLib/string_base.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
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

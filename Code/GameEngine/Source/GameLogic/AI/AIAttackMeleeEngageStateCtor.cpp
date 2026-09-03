// cl: /DNDEBUG /MD /EHsc

#include "../../../../Libraries/Source/WWVegas/WWLib/string_base.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString( const char *text ) : m_string( text ) {}
	StringBase<char> m_string;
};

class StateMachine;

class Rva0014F280StateBase
{
public:
	Rva0014F280StateBase( void *machine, AsciiString name );
};

extern int g_AIAttackMeleeEngageStateVTable;

class AIAttackMeleeEngageState : public Rva0014F280StateBase
{
public:
	AIAttackMeleeEngageState( StateMachine *machine, int targetId );

private:
	int *volatile m_vftable;
	char m_baseFields[ 0x4C ];
	volatile int m_field50;
	volatile int m_field54;
	volatile int m_field58;
	volatile int m_field5C;
	volatile int m_field60;
	volatile int m_field64;
	volatile int m_field68;
	volatile int m_field6C;
	volatile int m_field70;
	volatile bool m_field74;
	volatile bool m_field75;
	char m_padding76[ 2 ];
	volatile int m_targetId;
};

AIAttackMeleeEngageState::AIAttackMeleeEngageState( StateMachine *machine, int targetId )
	: Rva0014F280StateBase( machine, AsciiString( "AIAttackMeleeEngageState" ) )
{
	int savedTargetId = targetId;
	m_field50 = 0;
	m_field58 = 0;
	m_vftable = &g_AIAttackMeleeEngageStateVTable;
	m_field54 = -1;
	m_field5C = 0;
	m_field60 = 0;
	m_field64 = 0;
	m_field68 = 0;
	m_field6C = 0;
	m_field70 = 0;
	m_field74 = false;
	m_field75 = false;
	m_targetId = savedTargetId;
}

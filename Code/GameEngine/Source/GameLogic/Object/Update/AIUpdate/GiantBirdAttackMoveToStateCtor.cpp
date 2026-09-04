// cl: /DNDEBUG /MD /EHsc
//
// GiantBirdAttackMoveToState constructor.  The retail constructor directly
// invokes the State base with the normal-flight name, installs the derived
// vtable, and creates the AIAttackMoveMachine sub-machine.

#include "../../../../../../Libraries/Source/WWVegas/WWLib/string_base.h"

class AsciiString
{
public:
	AsciiString( const char *text ) : m_string( text ) {}

	StringBase<char> m_string;
};

class Rva000A19E0StateBase
{
public:
	Rva000A19E0StateBase( void *machine, AsciiString name );

	virtual ~Rva000A19E0StateBase();

protected:
	char m_baseGap04[ 0x18 ];
	void *m_machine;
	char m_baseTail20[ 4 ];
};

class AIAttackSwoopThenIdleStateMachine
{
public:
	AIAttackSwoopThenIdleStateMachine( void *owner, AsciiString name );
	virtual ~AIAttackSwoopThenIdleStateMachine();
	virtual void unused04();
	virtual void unused08();
	virtual void unused0c();
	virtual void unused10();
	virtual void unused14();
	virtual void unused18();
	virtual void initDefaultState();

private:
	char m_unreconstructed04[ 0x40 ];
};

class Rva002BF6D0StateMachine
{
private:
	char m_gap00[ 0x10 ];

public:
	void *m_owner;

	void *getOwner() { return m_owner; }
};

extern int g_GiantBirdAttackMoveToStateVTable;

class GiantBirdAttackMoveToState : public Rva000A19E0StateBase
{
public:
	GiantBirdAttackMoveToState( void *machine );

private:
	volatile unsigned char m_byte24;
	char m_gap25[ 3 ];
	volatile int m_goalHandle;
	AIAttackSwoopThenIdleStateMachine *m_attackMachine;
	volatile int m_retryCount;
};

GiantBirdAttackMoveToState::GiantBirdAttackMoveToState( void *machine )
	: Rva000A19E0StateBase( machine,
		AsciiString( "GiantBirdNormalFlightState" ) ),
	m_byte24( 0 ),
	m_retryCount( 5 )
{
	// The derived vtable is installed by the polymorphic constructor.
	m_attackMachine = new AIAttackSwoopThenIdleStateMachine(
		((Rva002BF6D0StateMachine *)m_machine)->getOwner(),
		AsciiString( "AIAttackMoveMachine" ) );
	m_attackMachine->initDefaultState();
	m_goalHandle = 0;
}

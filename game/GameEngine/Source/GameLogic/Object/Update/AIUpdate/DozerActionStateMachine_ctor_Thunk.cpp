// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringinline

#include "StringInline.h"

class Object;
class State;
struct StateConditionInfo;

enum DozerTask
{
	DOZER_TASK_INVALID = 0
};

class StateMachine
{
public:
	StateMachine( Object *owner, AsciiString name, bool flag );

protected:
	// retail declares the virtual destructor protected; that access level is
	// part of the mangled name the compiler-emitted cleanup path calls.
	virtual ~StateMachine();
	void defineState( unsigned int id, State *state,
		unsigned int successID, unsigned int failureID,
		const StateConditionInfo *conditions );

private:
	unsigned char m_fields[ 0x40 ];
};

class State
{
public:
	State( StateMachine *machine, AsciiString name );
	virtual ~State();

private:
	unsigned char m_fields[ 0x20 ];
};

// Retail vftable 0x010C6D28 is ??_7DozerActionPickActionPosState@@6B@, so the
// class keeps that name outside an anonymous namespace (whose decorated name
// changes with the source path).  The ctor stays inline (retail inlines it);
// the destructor is declared, not defined: its body lives elsewhere.
class DozerActionPickActionPosState : public State
{
public:
	DozerActionPickActionPosState( StateMachine *machine, DozerTask task )
		: State( machine, AsciiString( "DozerActionPickActionPosState" ) ),
		  m_task( task ),
		  m_failedAttempts( 0 )
	{
	}
	virtual ~DozerActionPickActionPosState();

private:
	DozerTask m_task;
	int m_failedAttempts;
};

class DozerActionMoveToActionPosState : public State
{
public:
	DozerActionMoveToActionPosState( StateMachine *machine, DozerTask task )
		: State( machine, AsciiString( "DozerActionMoveToActionPosState" ) ),
		  m_task( task )
	{
	}

private:
	DozerTask m_task;
};

class DozerActionDoActionState : public State
{
public:
	DozerActionDoActionState( StateMachine *machine, DozerTask task )
		: State( machine, AsciiString( "DozerActionDoActionState" ) ),
		  m_task( task ),
		  m_failedAttempts( 0 )
	{
	}

private:
	DozerTask m_task;
	int m_failedAttempts;
};

class DozerActionStateMachine : public StateMachine
{
public:
	DozerActionStateMachine( Object *owner, DozerTask task );

protected:
	virtual void crc( void *xfer );
	virtual void xfer( void *xfer );
	virtual void loadPostProcess();

private:
	DozerTask m_task;
};

DozerActionStateMachine::DozerActionStateMachine( Object *owner, DozerTask task )
	: StateMachine( owner, AsciiString( "DozerActionStateMachine" ), false ),
	  m_task( task )
{
	defineState( 0, new DozerActionPickActionPosState( this, task ), 1, 9999, 0 );
	defineState( 1, new DozerActionMoveToActionPosState( this, task ), 2, 0, 0 );
	defineState( 2, new DozerActionDoActionState( this, task ), 9998, 9999, 0 );
}

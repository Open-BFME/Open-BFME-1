// cl: /DNDEBUG /MD /EHsc
// readable body of ??0State@@: Code/GameEngine/Source/Common/StateMachine.cpp

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	~AsciiString();

private:
	void *m_data;
};

class StateMachine;

class TransitionVector
{
public:
	TransitionVector() : m_begin( 0 ), m_end( 0 ), m_storageEnd( 0 ) {}

private:
	void *m_begin;
	void *m_end;
	void *m_storageEnd;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class State
{
public:
	State( StateMachine *machine, AsciiString name );
	virtual ~State();

private:
	int m_ID;
	int m_successStateID;
	int m_failureStateID;
	TransitionVector m_transitions;
	StateMachine *m_machine;
	bool m_sleepTransitionPending;
};

State::State( StateMachine *machine, AsciiString name )
{
	m_ID = 999999;
	m_successStateID = 999999;
	m_failureStateID = 999999;
	m_machine = machine;
	m_sleepTransitionPending = false;
}

// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: clean ABI-slice reconstruction of StateMachine::~StateMachine.
// Retail 0x000A1130/224.  The BFME object has one base vptr, an STLport map
// at +0x04, and current state at +0x1c; the vendored StateMachine headers have
// a different multiple-inheritance layout, so this TU keeps only the proven
// destructor-facing slice.

#define _STLP_NO_EXCEPTIONS 1
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <map>

typedef unsigned int StateID;

enum StateExitType
{
	EXIT_RESET = 1
};

class State
{
protected:
	virtual ~State();

public:
	virtual void stateSlot02();
	virtual void stateSlot03();
	virtual void stateSlot04();
	virtual void stateSlot05();
	virtual void onExit(StateExitType status);

	void deleteInstance()
	{
		delete this;
	}
};

class StateMachineBase
{
public:
	virtual ~StateMachineBase() {}
};

// The target's two map helpers are the existing int-keyed STLport bodies at
// 0x000A0A60/0x000A0F40.  The dtor never reads the key, so this four-byte
// value shim preserves the proven node layout while selecting those helpers.
struct Gen_t_000a0f40_p4pod
{
	State *state;
};

typedef std::map<int, Gen_t_000a0f40_p4pod> StateMap;

class StateMachine : public StateMachineBase
{
protected:
	virtual ~StateMachine();

private:
	StateMap m_stateMap;
	void *m_owner;
	unsigned int m_sleepTill;
	StateID m_defaultStateID;
	State *m_currentState;
	unsigned int m_goalObjectID;
	unsigned char m_goalPosition[12];
	unsigned char m_locked;
	unsigned char m_defaultStateInited;
};

// ??1StateMachine@@MAE@XZ
StateMachine::~StateMachine()
{
	if (m_currentState)
		m_currentState->onExit(EXIT_RESET);

	StateMap::iterator i;
	for (i = m_stateMap.begin(); i != m_stateMap.end(); ++i)
	{
		if ((*i).second.state)
			(*i).second.state->deleteInstance();
	}

	m_stateMap.clear();
	m_defaultStateID = 999999;
	m_currentState = 0;
}

// ?internalSetState@StateMachine@@QAE?AW4StateReturnType@@I@Z
// partial score=0.88 date=2026-09-04
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// StateMachine::internalSetState at 0x000A1360. Retail inlines map::find and
// throws ERROR_BAD_ARG on a missing id; sibling friend_checkForSleepTransitions
// already names this body via its ILT pin.

#include <map>

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

enum
{
	MACHINE_DONE_STATE_ID = 999998,
	INVALID_STATE_ID = 999999,
	EXIT_NORMAL = 0
};

enum ErrorCode
{
	ERROR_BAD_ARG = 0xdead0003
};

class GameLogic
{
public:
	unsigned int getFrame() const { return m_frame; }

	char m_pad[0x3C];
	unsigned int m_frame;
};

class GameLogic *TheGameLogic;

class State
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual StateReturnType onEnter();
	virtual void onExit(int status);

	StateReturnType friend_checkForTransitions(StateReturnType status);
	StateReturnType friend_checkForSleepTransitions(StateReturnType status);
};

class StateMachine
{
public:
	virtual void unused();

	StateReturnType internalSetState(unsigned int newStateID);

private:
	std::map<unsigned int, State *> m_stateMap;
	void *m_owner;
	unsigned int m_sleepTill;
	unsigned int m_defaultStateID;
	State *m_currentState;
};

StateReturnType StateMachine::internalSetState(unsigned int newStateID)
{
	State *newState = 0;

	m_sleepTill = 0;
	if (newStateID != MACHINE_DONE_STATE_ID)
	{
		if (newStateID != INVALID_STATE_ID)
			goto do_lookup;
		newStateID = m_defaultStateID;
		if (newStateID != INVALID_STATE_ID)
			goto do_lookup;
	early_fail:
		return STATE_FAILURE;
	do_lookup:
		volatile unsigned int key = newStateID;
		std::map<unsigned int, State *>::iterator it = m_stateMap.find((unsigned int &)key);
		if (it == m_stateMap.end())
			throw ERROR_BAD_ARG;
		newState = it->second;
	}

	if (m_currentState)
		m_currentState->onExit(EXIT_NORMAL);

	m_currentState = newState;
	if (!newState)
		return STATE_CONTINUE;

	StateReturnType status = newState->onEnter();
	if (!m_currentState)
		goto early_fail;

	if (newState != m_currentState)
		return m_currentState->friend_checkForTransitions(STATE_CONTINUE);
	if ((int)status > 0)
	{
		unsigned int now = TheGameLogic->getFrame();
		m_sleepTill = now + (unsigned int)status;
		return m_currentState->friend_checkForSleepTransitions((StateReturnType)(m_sleepTill - now));
	}
	return m_currentState->friend_checkForTransitions(status);
}

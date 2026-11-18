// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// readable body of ?internalSetState@StateMachine@@: game/GameEngine/Source/Common/StateMachine.cpp

// StateMachine::internalSetState, retail 0x000A1360 (200 B, ret 4). The Zero
// Hour body as written, against BFME's StateMachine layout: the state map at
// +0x04, m_sleepTill at +0x14, m_defaultStateID at +0x18 and m_currentState at
// +0x1C. internalGetState inlines here (find, then throw ERROR_BAD_ARG), which
// the Zero Hour-layout StateMachine.cpp cannot express, so the body lives in
// its own file as getGoalObject does.

#include <map>

typedef unsigned int UnsignedInt;
typedef UnsignedInt StateID;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
#include "../../Include/Common/Enums/StateReturnType.h"






enum
{
	MACHINE_DONE_STATE_ID = 999998,
	INVALID_STATE_ID = 999999
};

enum StateExitType
{
	EXIT_NORMAL = 0
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Errors.h
enum ErrorCode
{
	ERROR_BAD_ARG = 0xDEAD0003
};

#define IS_STATE_SLEEP(n) ((int)(n) > 0)

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	UnsignedInt getFrame() const { return m_frame; }

private:
	unsigned char m_unmodelled_00[0x3C];
	UnsignedInt m_frame;						// +0x3C
};

extern GameLogic *TheGameLogic;				// 0x012F0898

class State
{
public:
	virtual void v00();
	virtual void v04();
	virtual void v08();
	virtual void v0C();
	virtual StateReturnType onEnter();			// slot 0x10
	virtual void onExit(StateExitType status);	// slot 0x14

	StateReturnType friend_checkForTransitions(StateReturnType status);
	StateReturnType friend_checkForSleepTransitions(StateReturnType status);
};

class StateMachine
{
public:
	virtual void halt();

	StateReturnType internalSetState(StateID newStateID);

private:
	State *internalGetState(StateID id)
	{
		std::map<StateID, State *>::iterator i = m_stateMap.find(id);
		if (i == m_stateMap.end())
			throw ERROR_BAD_ARG;
		return (*i).second;
	}

	std::map<StateID, State *> m_stateMap;		// +0x04
	void *m_owner;								// +0x10
	UnsignedInt m_sleepTill;					// +0x14
	StateID m_defaultStateID;					// +0x18
	State *m_currentState;						// +0x1C
};

// ?internalSetState@StateMachine@@QAE?AW4StateReturnType@@I@Z
StateReturnType StateMachine::internalSetState(StateID newStateID)
{
	State *newState = 0;

	// anytime the state changes, stop sleeping
	m_sleepTill = 0;

	if (newStateID != MACHINE_DONE_STATE_ID)
	{
		// if incoming state is invalid, go to the machine's default state
		if (newStateID == INVALID_STATE_ID)
		{
			newStateID = m_defaultStateID;
			if (newStateID == INVALID_STATE_ID)
				return STATE_FAILURE;
		}

		newState = internalGetState(newStateID);
	}

	if (m_currentState)
		m_currentState->onExit(EXIT_NORMAL);

	m_currentState = newState;

	if (m_currentState)
	{
		State *stateBeforeEnter = m_currentState;

		StateReturnType status = m_currentState->onEnter();

		// onEnter() may have caused a transition to clear the machine
		if (m_currentState == 0)
			return STATE_FAILURE;

		// onEnter() switched states: let the new state run normally
		if (stateBeforeEnter != m_currentState)
			status = STATE_CONTINUE;

		if (IS_STATE_SLEEP(status))
		{
			UnsignedInt now = TheGameLogic->getFrame();
			m_sleepTill = now + (UnsignedInt)status;
			return m_currentState->friend_checkForSleepTransitions((StateReturnType)(m_sleepTill - now));
		}
		else
		{
			return m_currentState->friend_checkForTransitions(status);
		}
	}
	else
	{
		return STATE_CONTINUE;  // irrelevant return code, but we must return something
	}
}

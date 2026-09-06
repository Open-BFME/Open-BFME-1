// ?updateStateMachine@StateMachine@@UAE?AW4StateReturnType@@XZ
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// StateMachine::updateStateMachine at 0x000A0760. Self-contained twin, same
// shape as the stashed StateMachine::internalSetState attempt
// (reverse/attempts/0x000a1360.cpp): State gets two unidentified vtable slots
// between the destructor and onEnter/onExit, and StateMachine keeps
// m_sleepTill at +0x14 and m_currentState at +0x1c (four bytes earlier than
// the real header's layout, which the tracked StateMachine.cpp definition
// still uses -- present-unmatched there). Kept independent of the real
// Common/StateMachine.h so field offsets compile exactly as retail wrote them,
// without disturbing the landed friend_checkForTransitions/
// friend_checkForSleepTransitions definitions in that header's own TU.

typedef unsigned int UnsignedInt;
typedef int Int;
typedef bool Bool;

#define NULL 0

enum StateReturnType
{
	STATE_CONTINUE	= 0,
	STATE_SUCCESS	= -1,
	STATE_FAILURE	= -2
};

#define STATE_SLEEP(numFrames)				((StateReturnType)(numFrames))
#define IS_STATE_SLEEP(ret)						((Int)(ret) > 0)
#define GET_STATE_SLEEP_FRAMES(ret)		((UnsignedInt)(ret))

void DEBUG_CRASH_STUB(const char *);
#define DEBUG_CRASH(x) DEBUG_CRASH_STUB

class GameLogic
{
public:
	unsigned int getFrame() const { return m_frame; }

	char m_pad[0x3C];
	unsigned int m_frame;
};

extern class GameLogic *TheGameLogic;

class State
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual StateReturnType onEnter();
	virtual void onExit(int status);
	virtual StateReturnType update();

	StateReturnType friend_checkForTransitions(StateReturnType status);
	StateReturnType friend_checkForSleepTransitions(StateReturnType status);
};

class StateMachine
{
public:
	virtual void unused();

	virtual StateReturnType updateStateMachine();

private:
	char m_unreconstructed_04[0x14 - 0x04];
	UnsignedInt m_sleepTill;			///< retail this+0x14
	UnsignedInt m_defaultStateID;		///< retail this+0x18
	State *m_currentState;			///< retail this+0x1c
};

StateReturnType StateMachine::updateStateMachine()
{
	UnsignedInt now = TheGameLogic->getFrame();
	if (m_sleepTill != 0 && now < m_sleepTill)
	{
		if( m_currentState == NULL )
		{
			return STATE_FAILURE;
		}
		return m_currentState->friend_checkForSleepTransitions( STATE_SLEEP(m_sleepTill - now) );
	}

	// not sleeping anymore
	m_sleepTill = 0;

	if (m_currentState)
	{
		// update() can change m_currentState, so save it for a moment...
		State* stateBeforeUpdate = m_currentState;

		// execute this state
		StateReturnType status = m_currentState->update();

		// it is possible that the state's update() method may cause the state to be destroyed
		if (m_currentState == NULL)
		{
			return STATE_FAILURE;
		}

		// here's the scenario:
		// -- State A calls foo() and then says "sleep for 2000 frames".
		// -- however, foo() called setState() to State B. thus our current state is not the same.
		// -- thus, if the state changed, we must ignore any sleep result and pretend we got STATE_CONTINUE,
		// so that the new state will be called immediately.
		if (stateBeforeUpdate != m_currentState)
		{
			status = STATE_CONTINUE;
		}

		if (IS_STATE_SLEEP(status))
		{
			// hey, we're sleepy!
			m_sleepTill = now + GET_STATE_SLEEP_FRAMES(status);
			return m_currentState->friend_checkForSleepTransitions( STATE_SLEEP(m_sleepTill - now) );
		}
		else
		{
			// check for state transitions, possibly exiting this machine
			return m_currentState->friend_checkForTransitions( status );
		}
	}
	else
	{
		return STATE_FAILURE;
	}
}

// cl: /DNDEBUG /MD /EHsc
// readable body of ?getAIStateType@AIUpdateInterface@@: Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate.cpp

// AIUpdateInterface::getAIStateType, retail 0x0026F8F0. Zero Hour's one-liner -
// the current state id off the state machine, cast - with the machine's own
// getCurrentStateID inlined, and BFME's version of that is not Zero Hour's.
//
// It reads the current state at +0x58 and its id at +0x04, taking the invalid
// id when there is none, and then, ONLY if the answer came back invalid, falls
// back to a second state at +0x1C and takes its id instead. That second lookup
// is why the invalid constant appears twice: once as the value for an absent
// current state, once as the value the comparison tests for.

enum AIStateType {};

enum StateID
{
	INVALID_STATE_ID = 999999
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class State
{
public:
	StateID getID() const
	{
		return m_id;
	}

private:
	unsigned int m_unmodelled_00;
	StateID m_id;							// +0x04
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class StateMachine
{
public:
	StateID getCurrentStateID() const
	{
		StateID id = m_currentState ? m_currentState->getID() : INVALID_STATE_ID;

		if( id == INVALID_STATE_ID )
		{
			if( m_fallbackState )
				return m_fallbackState->getID();

			return INVALID_STATE_ID;
		}

		return id;
	}

private:
	unsigned char m_unmodelled_00[ 0x1C ];
	State *m_fallbackState;					// +0x1C
	unsigned char m_unmodelled_20[ 0x58 - 0x20 ];
	State *m_currentState;					// +0x58
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface
{
public:
	AIStateType getAIStateType() const;

private:
	StateMachine *getStateMachine() const
	{
		return m_stateMachine;
	}

	unsigned char m_unmodelled_00[ 0x30 ];
	StateMachine *m_stateMachine;			// +0x30
};

// ?getAIStateType@AIUpdateInterface@@QBE?AW4AIStateType@@XZ
AIStateType AIUpdateInterface::getAIStateType() const
{
	return (AIStateType)getStateMachine()->getCurrentStateID();
}

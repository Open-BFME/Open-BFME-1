// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// readable body of ?getEnterTarget@AIUpdateInterface@@: Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate.cpp
// readable body: Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate.cpp

class Object;

enum StateID
{
	INVALID_STATE_ID = 999999
};

enum AIStateType
{
	AI_ENTER = 0x0F,
	AI_ENTER_TUNNEL = 0x31,
	AI_GET_REPAIRED = 0x18,
	AI_ENTER_HORDE = 0x2B,
	AI_ENTER_GARRISON = 0x19,
	AI_ENTER_TRANSPORT = 0x34
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class State
{
public:
	StateID getID() const
	{
		return m_stateID;
	}

	unsigned char m_unmodelled_000[ 4 ];
	StateID m_stateID;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class StateMachine
{
public:
	Object *getGoalObject();
	StateID getCurrentStateID() const
	{
		StateID id = m_currentState ? m_currentState->getID() : INVALID_STATE_ID;

		if( id == INVALID_STATE_ID )
			id = m_fallbackState ? m_fallbackState->getID() : INVALID_STATE_ID;

		return id;
	}

	unsigned char m_unmodelled_000[ 0x1C ];
	State *m_fallbackState;
	unsigned char m_unmodelled_020[ 0x58 - 0x20 ];
	State *m_currentState;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface
{
public:
	virtual Object *getEnterTarget();

private:
	StateMachine *getStateMachine() const
	{
		return m_stateMachine;
	}

	AIStateType getAIStateType() const
	{
		return static_cast<AIStateType>( getStateMachine()->getCurrentStateID() );
	}

	unsigned char m_unmodelled_004[ 0x30 - 4 ];
	StateMachine *m_stateMachine;
};

Object *AIUpdateInterface::getEnterTarget()
{
	AIStateType stateType = getAIStateType();

	if( stateType != AI_ENTER &&
			stateType != AI_ENTER_TUNNEL &&
			stateType != AI_GET_REPAIRED &&
			stateType != AI_ENTER_HORDE &&
			stateType != AI_ENTER_GARRISON &&
			stateType != AI_ENTER_TRANSPORT )
		return 0;

	return getStateMachine()->getGoalObject();
}

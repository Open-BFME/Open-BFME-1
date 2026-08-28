// cl: /DNDEBUG /MD /EHsc
// readable body: Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate.cpp

typedef bool Bool;
typedef unsigned int UnsignedInt;

enum AICommandType
{
	AICMD_MOVE_TO_POSITION_EVEN_IF_SLEEPING = 0x36
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_AI = 1
};

struct AICommandParms
{
	AICommandType m_cmd;
	CommandSourceType m_cmdSource;
};

class Object
{
public:
	Bool isEffectivelyDead() const
	{
		return (m_deadFlags & 1) != 0;
	}

private:
	unsigned char m_unmodelled_000[ 0x344 ];
	unsigned char m_deadFlags;
};

class AIStateMachine
{
public:
	Bool hasCurrentState() const { return m_currentState != 0; }
	int getGoalObjectID() const { return m_goalObjectID; }

private:
	unsigned char m_unmodelled_000[ 0x58 ];
	void *m_currentState;
	int m_goalObjectID;
};

class AIUpdateInterface
{
public:
	UnsignedInt getMoodMatrixValue() const;

protected:
	virtual Bool isAllowedToRespondToAiCommands( const AICommandParms *parms ) const;

private:
	unsigned char m_unmodelled_004[ 4 ];
	Object *m_object;
	unsigned char m_unmodelled_00C[ 0x30 - 0x0C ];
	AIStateMachine *m_stateMachine;
	unsigned char m_unmodelled_034[ 0x333 - 0x034 ];
	Bool m_forbidPlayerCommands;
	Bool m_forbidAICommands;
};

// ?isAllowedToRespondToAiCommands@AIUpdateInterface@@MBE_NPBUAICommandParms@@@Z
Bool AIUpdateInterface::isAllowedToRespondToAiCommands( const AICommandParms *parms ) const
{
	if( m_object->isEffectivelyDead() )
		return false;

	UnsignedInt moodParms = getMoodMatrixValue();
	if( (moodParms & 0x02) && (moodParms & 0x100) &&
		parms->m_cmd != AICMD_MOVE_TO_POSITION_EVEN_IF_SLEEPING )
		return false;

	if( m_forbidPlayerCommands && parms->m_cmdSource == CMD_FROM_PLAYER )
		return false;

	if( m_forbidAICommands && parms->m_cmdSource == CMD_FROM_AI )
		return false;

	if( m_stateMachine->hasCurrentState() && m_stateMachine->getGoalObjectID() == -1 )
		return false;

	return true;
}

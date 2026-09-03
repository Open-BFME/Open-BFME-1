// cl: /DNDEBUG /MD
// readable body of ?onEnter@AITNGuardIdleState@@: Code/GameEngine/Source/GameLogic/AI/AITNGuard.cpp
//
// Retail 0x00189C90: AITNGuardIdleState::onEnter.  The string DIR32 is the
// BFME compile path baked into GetGameLogicRandomValue's file argument, and
// 0x24A is that file's line.  State+0x1C is the machine, machine+0x10 is the
// owner, Object+0x204 is the AI module, AIData+0x40 is m_guardEnemyScanRate.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	unsigned int getFrame() const { return m_frame; }

	char m_pad[ 0x3C ];
	unsigned int m_frame;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class TAiData
{
public:
	char m_pad[ 0x40 ];
	int m_guardEnemyScanRate;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AI
{
public:
	TAiData *getAiData() { return m_data; }

	char m_pad[ 0x14 ];
	TAiData *m_data;
};

class Object;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface
{
public:
	void friend_setGoalObject( Object *obj );
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	AIUpdateInterface *getAI() { return m_ai; }

	char m_pad[ 0x204 ];
	AIUpdateInterface *m_ai;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class StateMachine
{
public:
	Object *getOwner() { return m_owner; }

	char m_pad[ 0x10 ];
	Object *m_owner;
};

enum StateReturnType
{
	STATE_CONTINUE = 0
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AITNGuard.h
class AITNGuardIdleState
{
public:
	virtual StateReturnType onEnter();

	Object *getMachineOwner() { return m_machine->getOwner(); }

private:
	char m_pad[ 0x18 ];
	StateMachine *m_machine;
	int m_unused20;
	unsigned int m_nextEnemyScanTime;
};

extern GameLogic *TheGameLogic;
extern "C" AI *TheAIParseDefinitionAI;

int GetGameLogicRandomValue( int lo, int hi, char *file, int line );

StateReturnType AITNGuardIdleState::onEnter()
{
	unsigned int now = TheGameLogic->getFrame();
	m_nextEnemyScanTime = now + GetGameLogicRandomValue(
		0,
		TheAIParseDefinitionAI->getAiData()->m_guardEnemyScanRate,
		"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Ai\\AITNGuard.cpp",
		0x24A );
	getMachineOwner()->getAI()->friend_setGoalObject( 0 );
	return STATE_CONTINUE;
}

// cl: /DNDEBUG /MD
// readable body of ?onEnter@AITNGuardIdleState@@: game/GameEngine/Source/GameLogic/AI/AITNGuard.cpp
//
// Retail 0x00189C90: AITNGuardIdleState::onEnter.  The string DIR32 is the
// BFME compile path baked into GetGameLogicRandomValue's file argument, and
// 0x24A is that file's line.  State+0x1C is the machine, machine+0x10 is the
// owner, Object+0x204 is the AI module, AIData+0x40 is m_guardEnemyScanRate.

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	unsigned int getFrame() const { return m_frame; }

	char m_pad[ 0x3C ];
	unsigned int m_frame;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class TAiData
{
public:
	char m_pad00[ 4 ];
	float m_structureSeconds;
	float m_teamSeconds;
	int m_resourcesWealthy;
	int m_resourcesPoor;
	unsigned int m_forceIdleFramesCount;
	float m_structuresWealthyMod;
	float m_teamWealthyMod;
	float m_structuresPoorMod;
	float m_teamPoorMod;
	float m_teamResourcesToBuild;
	float m_guardInnerModifierAI;
	float m_guardOuterModifierAI;
	float m_guardInnerModifierHuman;
	float m_guardOuterModifierHuman;
	unsigned int m_guardChaseUnitFrames;
	int m_guardEnemyScanRate;
};

// AI is only forward-declared: game/GameEngine/Source/Common/System/
// game_engine_subsystems.h already declares class AI (a SubsystemInterface stub
// with no members), so a second body here would be a redeclaration. The name is
// all the global's mangling needs; the +0x14 member the body reads is spelled as
// the view below (upstream layout:
// inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h).
class AI;

struct BfmeAIView
{
	TAiData *getAiData() { return m_data; }

	char m_pad[ 0x14 ];
	TAiData *m_data;
};

class Object;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface
{
public:
	void friend_setGoalObject( Object *goalObject );
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	AIUpdateInterface *getAI() { return m_ai; }

	char m_pad[ 0x204 ];
	AIUpdateInterface *m_ai;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AITNGuard.h
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
// 0x012EF214 is retail's TheAI singleton, defined as `AI *TheAI` in
// game/GameEngine/Source/GameLogic/AI/ai.cpp. The old stand-in was C-linkage, so
// it emitted an unmangled TheAIParseDefinitionAI; retail's own bytes name the
// global ?TheAI@@3PAVAI@@A, so the C++ spelling is the one to bind.
extern AI *TheAI;

int GetGameLogicRandomValue( int lo, int hi, char *file, int line );

StateReturnType AITNGuardIdleState::onEnter()
{
	unsigned int now = TheGameLogic->getFrame();
	m_nextEnemyScanTime = now + GetGameLogicRandomValue(
		0,
		reinterpret_cast<BfmeAIView *>(TheAI)->getAiData()->m_guardEnemyScanRate,
		"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Ai\\AITNGuard.cpp",
		0x24A );
	getMachineOwner()->getAI()->friend_setGoalObject( 0 );
	return STATE_CONTINUE;
}

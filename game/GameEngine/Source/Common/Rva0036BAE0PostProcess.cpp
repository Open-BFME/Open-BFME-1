class Object;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Pathfinder
{
public:
	void removeObjectFromPathfindMap(Object *object);
};

// AI is only forward-declared: game/GameEngine/Source/Common/System/
// game_engine_subsystems.h already declares class AI (a SubsystemInterface stub
// with no members), so a second body here would be a redeclaration. The name is
// all the global's mangling needs; the +0x0C member the body reads is spelled as
// the view below (upstream layout:
// inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h).
class AI;

struct BfmeAIView
{
	Pathfinder *pathfinder(void) { return m_pathfinder; }

	char m_unreconstructed00[ 0x0C ];
	Pathfinder *m_pathfinder;
};

// 0x012EF214 is retail's TheAI singleton, defined as `AI *TheAI` in
// game/GameEngine/Source/GameLogic/AI/ai.cpp. The old stand-in was C-linkage, so
// it emitted an unmangled TheAIParseDefinitionAI. Retail's own bytes name the
// global ?TheAI@@3PAVAI@@A, so the C++ spelling is the one to bind.
extern AI *TheAI;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule
{
protected:
	virtual void loadPostProcess(void);
};

class Rva0036BAE0Update : public UpdateModule
{
public:
	virtual void loadPostProcess(void);

private:
	char m_unreconstructed04[ 4 ];
	Object *m_object;
	char m_unreconstructed0C[ 0x90 ];
	int m_isOnPathfindMap;
};

void Rva0036BAE0Update::loadPostProcess(void)
{
	UpdateModule::loadPostProcess();
	if( m_isOnPathfindMap )
	{
		reinterpret_cast<BfmeAIView *>(TheAI)->pathfinder()->removeObjectFromPathfindMap(m_object);
	}
}

// @?loadPostProcess@Rva0036BAE0Update@@UAEXXZ 0x0036BAE0

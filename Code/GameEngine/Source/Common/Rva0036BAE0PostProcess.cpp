class Object;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Pathfinder
{
public:
	void removeObjectFromPathfindMap(Object *object);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AI
{
public:
	Pathfinder *pathfinder(void) { return m_pathfinder; }

private:
	char m_unreconstructed00[ 0x0C ];
	Pathfinder *m_pathfinder;
};

extern "C" AI *TheAIParseDefinitionAI;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
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
		TheAIParseDefinitionAI->pathfinder()->removeObjectFromPathfindMap(m_object);
	}
}

// @?loadPostProcess@Rva0036BAE0Update@@UAEXXZ 0x0036BAE0

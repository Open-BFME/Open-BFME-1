// cl: /DNDEBUG /MD /GX- /O2 /Ob2

class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpawnPointProductionExitUpdate.h
class SpawnPointProductionExitUpdateModuleData
{
public:
	SpawnPointProductionExitUpdateModuleData();
	virtual ~SpawnPointProductionExitUpdateModuleData();

private:
	int m_tag;
	int m_field8;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char SpawnPointProductionExitUpdateFieldParse;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpawnPointProductionExitUpdate.h
class SpawnPointProductionExitUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ??0SpawnPointProductionExitUpdateModuleData@@QAE@XZ
SpawnPointProductionExitUpdateModuleData::SpawnPointProductionExitUpdateModuleData()
{
	m_field8 = 0;
}

// ?friend_newModuleData@SpawnPointProductionExitUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *SpawnPointProductionExitUpdate::friend_newModuleData(INI *ini)
{
	SpawnPointProductionExitUpdateModuleData *data = new SpawnPointProductionExitUpdateModuleData;
	if (ini)
		ini->initFromINI(data, &SpawnPointProductionExitUpdateFieldParse);
	return (ModuleData *)data;
}
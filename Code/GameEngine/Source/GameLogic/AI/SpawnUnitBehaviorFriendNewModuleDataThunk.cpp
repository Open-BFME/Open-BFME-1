// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: SpawnUnitBehavior::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class SpawnUnitBehaviorModuleData
{
public:
	SpawnUnitBehaviorModuleData();
	virtual ~SpawnUnitBehaviorModuleData();

private:
	unsigned char m_pad[0x1c];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char SpawnUnitBehaviorFieldParse;

class SpawnUnitBehavior
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@SpawnUnitBehavior@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *SpawnUnitBehavior::friend_newModuleData(INI *ini)
{
	SpawnUnitBehaviorModuleData *data = new SpawnUnitBehaviorModuleData;
	if (ini)
		ini->initFromINI(data, &SpawnUnitBehaviorFieldParse);
	return (ModuleData *)data;
}

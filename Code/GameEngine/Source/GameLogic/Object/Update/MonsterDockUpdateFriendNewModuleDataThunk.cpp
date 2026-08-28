// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: MonsterDockUpdate::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class MonsterDockUpdateModuleData
{
public:
	MonsterDockUpdateModuleData();
	virtual ~MonsterDockUpdateModuleData();

private:
	unsigned char m_pad[0x14];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char MonsterDockUpdateFieldParse;

class MonsterDockUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@MonsterDockUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *MonsterDockUpdate::friend_newModuleData(INI *ini)
{
	MonsterDockUpdateModuleData *data = new MonsterDockUpdateModuleData;
	if (ini)
		ini->initFromINI(data, &MonsterDockUpdateFieldParse);
	return (ModuleData *)data;
}

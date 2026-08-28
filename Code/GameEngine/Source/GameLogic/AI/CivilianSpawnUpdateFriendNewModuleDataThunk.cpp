// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: CivilianSpawnUpdate::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class CivilianSpawnUpdateModuleData
{
public:
	CivilianSpawnUpdateModuleData();
	virtual ~CivilianSpawnUpdateModuleData();

private:
	unsigned char m_pad[0x1c];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char CivilianSpawnUpdateFieldParse;

class CivilianSpawnUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@CivilianSpawnUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *CivilianSpawnUpdate::friend_newModuleData(INI *ini)
{
	CivilianSpawnUpdateModuleData *data = new CivilianSpawnUpdateModuleData;
	if (ini)
		ini->initFromINI(data, &CivilianSpawnUpdateFieldParse);
	return (ModuleData *)data;
}

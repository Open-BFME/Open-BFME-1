// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: CivilianSpawnCollide::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class CivilianSpawnCollideModuleData
{
public:
	CivilianSpawnCollideModuleData();
	virtual ~CivilianSpawnCollideModuleData();

private:
	unsigned char m_pad[0x8];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char CivilianSpawnCollideFieldParse;

class CivilianSpawnCollide
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@CivilianSpawnCollide@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *CivilianSpawnCollide::friend_newModuleData(INI *ini)
{
	CivilianSpawnCollideModuleData *data = new CivilianSpawnCollideModuleData;
	if (ini)
		ini->initFromINI(data, &CivilianSpawnCollideFieldParse);
	return (ModuleData *)data;
}

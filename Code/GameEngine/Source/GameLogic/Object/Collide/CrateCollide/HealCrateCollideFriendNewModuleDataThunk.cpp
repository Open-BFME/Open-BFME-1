// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: HealCrateCollide::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class HealCrateCollideModuleData
{
public:
	HealCrateCollideModuleData();
	virtual ~HealCrateCollideModuleData();

private:
	unsigned char m_pad[0x50];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char HealCrateCollideFieldParse;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/HealCrateCollide.h
class HealCrateCollide
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@HealCrateCollide@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *HealCrateCollide::friend_newModuleData(INI *ini)
{
	HealCrateCollideModuleData *data = new HealCrateCollideModuleData;
	if (ini)
		ini->initFromINI(data, &HealCrateCollideFieldParse);
	return (ModuleData *)data;
}

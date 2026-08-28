// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: LevelGrantSpecialPower::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class LevelGrantSpecialPowerModuleData
{
public:
	LevelGrantSpecialPowerModuleData();
	virtual ~LevelGrantSpecialPowerModuleData();

private:
	unsigned char m_pad[0x280];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char LevelGrantSpecialPowerFieldParse;

class LevelGrantSpecialPower
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@LevelGrantSpecialPower@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *LevelGrantSpecialPower::friend_newModuleData(INI *ini)
{
	LevelGrantSpecialPowerModuleData *data = new LevelGrantSpecialPowerModuleData;
	if (ini)
		ini->initFromINI(data, &LevelGrantSpecialPowerFieldParse);
	return (ModuleData *)data;
}

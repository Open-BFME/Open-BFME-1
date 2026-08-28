// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: PlayerUpgradeSpecialPower::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class PlayerUpgradeSpecialPowerModuleData
{
public:
	PlayerUpgradeSpecialPowerModuleData();
	virtual ~PlayerUpgradeSpecialPowerModuleData();

private:
	unsigned char m_pad[0x218];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char PlayerUpgradeSpecialPowerFieldParse;

class PlayerUpgradeSpecialPower
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@PlayerUpgradeSpecialPower@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *PlayerUpgradeSpecialPower::friend_newModuleData(INI *ini)
{
	PlayerUpgradeSpecialPowerModuleData *data = new PlayerUpgradeSpecialPowerModuleData;
	if (ini)
		ini->initFromINI(data, &PlayerUpgradeSpecialPowerFieldParse);
	return (ModuleData *)data;
}

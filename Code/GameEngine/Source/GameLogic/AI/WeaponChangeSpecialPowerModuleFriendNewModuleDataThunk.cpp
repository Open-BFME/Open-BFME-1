// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: WeaponChangeSpecialPowerModule::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class WeaponChangeSpecialPowerModuleModuleData
{
public:
	WeaponChangeSpecialPowerModuleModuleData();
	virtual ~WeaponChangeSpecialPowerModuleModuleData();

private:
	unsigned char m_pad[0x220];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char WeaponChangeSpecialPowerModuleFieldParse;

class WeaponChangeSpecialPowerModule
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@WeaponChangeSpecialPowerModule@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *WeaponChangeSpecialPowerModule::friend_newModuleData(INI *ini)
{
	WeaponChangeSpecialPowerModuleModuleData *data = new WeaponChangeSpecialPowerModuleModuleData;
	if (ini)
		ini->initFromINI(data, &WeaponChangeSpecialPowerModuleFieldParse);
	return (ModuleData *)data;
}

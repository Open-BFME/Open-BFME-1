// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: WeaponModeSpecialPowerUpdate::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class WeaponModeSpecialPowerUpdateModuleData
{
public:
	WeaponModeSpecialPowerUpdateModuleData();
	virtual ~WeaponModeSpecialPowerUpdateModuleData();

private:
	unsigned char m_pad[0x1dc];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char WeaponModeSpecialPowerUpdateFieldParse;

class WeaponModeSpecialPowerUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@WeaponModeSpecialPowerUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *WeaponModeSpecialPowerUpdate::friend_newModuleData(INI *ini)
{
	WeaponModeSpecialPowerUpdateModuleData *data = new WeaponModeSpecialPowerUpdateModuleData;
	if (ini)
		ini->initFromINI(data, &WeaponModeSpecialPowerUpdateFieldParse);
	return (ModuleData *)data;
}

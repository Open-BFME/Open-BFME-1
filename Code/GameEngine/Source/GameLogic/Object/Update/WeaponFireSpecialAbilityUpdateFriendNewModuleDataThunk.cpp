// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: WeaponFireSpecialAbilityUpdate::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class WeaponFireSpecialAbilityUpdateModuleData
{
public:
	WeaponFireSpecialAbilityUpdateModuleData();
	virtual ~WeaponFireSpecialAbilityUpdateModuleData();

private:
	unsigned char m_pad[0x264];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char WeaponFireSpecialAbilityUpdateFieldParse;

class WeaponFireSpecialAbilityUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@WeaponFireSpecialAbilityUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *WeaponFireSpecialAbilityUpdate::friend_newModuleData(INI *ini)
{
	WeaponFireSpecialAbilityUpdateModuleData *data = new WeaponFireSpecialAbilityUpdateModuleData;
	if (ini)
		ini->initFromINI(data, &WeaponFireSpecialAbilityUpdateFieldParse);
	return (ModuleData *)data;
}

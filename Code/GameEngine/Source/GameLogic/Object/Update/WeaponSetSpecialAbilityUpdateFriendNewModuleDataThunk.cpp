// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: WeaponSetSpecialAbilityUpdate::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class WeaponSetSpecialAbilityUpdateModuleData
{
public:
	WeaponSetSpecialAbilityUpdateModuleData();
	virtual ~WeaponSetSpecialAbilityUpdateModuleData();

private:
	unsigned char m_pad[0x258];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char WeaponSetSpecialAbilityUpdateFieldParse;

class WeaponSetSpecialAbilityUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@WeaponSetSpecialAbilityUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *WeaponSetSpecialAbilityUpdate::friend_newModuleData(INI *ini)
{
	WeaponSetSpecialAbilityUpdateModuleData *data = new WeaponSetSpecialAbilityUpdateModuleData;
	if (ini)
		ini->initFromINI(data, &WeaponSetSpecialAbilityUpdateFieldParse);
	return (ModuleData *)data;
}

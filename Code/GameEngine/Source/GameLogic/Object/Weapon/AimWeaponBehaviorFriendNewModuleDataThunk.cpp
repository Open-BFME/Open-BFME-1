// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: AimWeaponBehavior::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class AimWeaponBehaviorModuleData
{
public:
	AimWeaponBehaviorModuleData();
	virtual ~AimWeaponBehaviorModuleData();

private:
	unsigned char m_pad[0x14];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char AimWeaponBehaviorFieldParse;

class AimWeaponBehavior
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@AimWeaponBehavior@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *AimWeaponBehavior::friend_newModuleData(INI *ini)
{
	AimWeaponBehaviorModuleData *data = new AimWeaponBehaviorModuleData;
	if (ini)
		ini->initFromINI(data, &AimWeaponBehaviorFieldParse);
	return (ModuleData *)data;
}

// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: DualWeaponBehavior::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class DualWeaponBehaviorModuleData
{
public:
	DualWeaponBehaviorModuleData();
	virtual ~DualWeaponBehaviorModuleData();

private:
	unsigned char m_pad[0x14];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char DualWeaponBehaviorFieldParse;

class DualWeaponBehavior
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@DualWeaponBehavior@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *DualWeaponBehavior::friend_newModuleData(INI *ini)
{
	DualWeaponBehaviorModuleData *data = new DualWeaponBehaviorModuleData;
	if (ini)
		ini->initFromINI(data, &DualWeaponBehaviorFieldParse);
	return (ModuleData *)data;
}

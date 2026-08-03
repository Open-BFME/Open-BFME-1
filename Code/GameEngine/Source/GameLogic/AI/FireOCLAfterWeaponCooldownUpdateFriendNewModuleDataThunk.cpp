// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: FireOCLAfterWeaponCooldownUpdate::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class CostModifierUpgradeModuleData
{
public:
	CostModifierUpgradeModuleData();
	virtual ~CostModifierUpgradeModuleData();

private:
	unsigned char m_pad[0x70];
};

class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char FireOCLAfterWeaponCooldownUpdateFieldParse;

class FireOCLAfterWeaponCooldownUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@FireOCLAfterWeaponCooldownUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *FireOCLAfterWeaponCooldownUpdate::friend_newModuleData(INI *ini)
{
	CostModifierUpgradeModuleData *data = new CostModifierUpgradeModuleData;
	if (ini)
		ini->initFromINI(data, &FireOCLAfterWeaponCooldownUpdateFieldParse);
	return (ModuleData *)data;
}

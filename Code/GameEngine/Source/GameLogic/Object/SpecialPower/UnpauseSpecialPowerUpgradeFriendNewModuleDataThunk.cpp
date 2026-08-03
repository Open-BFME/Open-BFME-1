// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: UnpauseSpecialPowerUpgrade::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class UnpauseSpecialPowerUpgradeModuleData
{
public:
	UnpauseSpecialPowerUpgradeModuleData();
	virtual ~UnpauseSpecialPowerUpgradeModuleData();

private:
	unsigned char m_pad[0x74];
};

class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char UnpauseSpecialPowerUpgradeFieldParse;

class UnpauseSpecialPowerUpgrade
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@UnpauseSpecialPowerUpgrade@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *UnpauseSpecialPowerUpgrade::friend_newModuleData(INI *ini)
{
	UnpauseSpecialPowerUpgradeModuleData *data = new UnpauseSpecialPowerUpgradeModuleData;
	if (ini)
		ini->initFromINI(data, &UnpauseSpecialPowerUpgradeFieldParse);
	return (ModuleData *)data;
}

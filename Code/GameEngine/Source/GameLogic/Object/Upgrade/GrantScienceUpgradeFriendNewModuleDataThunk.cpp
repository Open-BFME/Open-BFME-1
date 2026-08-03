// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: GrantScienceUpgrade::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class ActiveShroudUpgradeModuleData
{
public:
	ActiveShroudUpgradeModuleData();
	virtual ~ActiveShroudUpgradeModuleData();

private:
	unsigned char m_pad[0x60];
};

class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char GrantScienceUpgradeFieldParse;

class GrantScienceUpgrade
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@GrantScienceUpgrade@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *GrantScienceUpgrade::friend_newModuleData(INI *ini)
{
	ActiveShroudUpgradeModuleData *data = new ActiveShroudUpgradeModuleData;
	if (ini)
		ini->initFromINI(data, &GrantScienceUpgradeFieldParse);
	return (ModuleData *)data;
}

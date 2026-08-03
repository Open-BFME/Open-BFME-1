// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: ReplaceObjectUpgrade::friend_newModuleData factory.

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

extern "C" char ReplaceObjectUpgradeFieldParse;

class ReplaceObjectUpgrade
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@ReplaceObjectUpgrade@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *ReplaceObjectUpgrade::friend_newModuleData(INI *ini)
{
	ActiveShroudUpgradeModuleData *data = new ActiveShroudUpgradeModuleData;
	if (ini)
		ini->initFromINI(data, &ReplaceObjectUpgradeFieldParse);
	return (ModuleData *)data;
}

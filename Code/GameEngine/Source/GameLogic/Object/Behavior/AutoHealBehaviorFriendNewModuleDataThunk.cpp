// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: AutoHealBehavior::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class AutoHealBehaviorModuleData
{
public:
	AutoHealBehaviorModuleData();
	virtual ~AutoHealBehaviorModuleData();

private:
	unsigned char m_pad[0xa4];
};

class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char AutoHealBehaviorFieldParse;

class AutoHealBehavior
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@AutoHealBehavior@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *AutoHealBehavior::friend_newModuleData(INI *ini)
{
	AutoHealBehaviorModuleData *data = new AutoHealBehaviorModuleData;
	if (ini)
		ini->initFromINI(data, &AutoHealBehaviorFieldParse);
	return (ModuleData *)data;
}

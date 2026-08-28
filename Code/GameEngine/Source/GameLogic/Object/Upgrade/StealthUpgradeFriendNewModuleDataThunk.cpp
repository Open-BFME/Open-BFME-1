// cl: /DNDEBUG /MD /GX- /O2 /Ob2

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

// Retail constructs this at this+8 after installing the outer vtable.
class UpgradeModuleDataSub
{
public:
	UpgradeModuleDataSub();

private:
	char opaque[0x68];
};

class StealthUpgradeModuleData
{
public:
	StealthUpgradeModuleData() {}
	virtual void dummy();

private:
	int m_pad;
	UpgradeModuleDataSub m_sub;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char StealthUpgradeFieldParse;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/StealthUpgrade.h
class StealthUpgrade
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@StealthUpgrade@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *StealthUpgrade::friend_newModuleData(INI *ini)
{
	StealthUpgradeModuleData *data = new StealthUpgradeModuleData;
	if (ini)
		ini->initFromINI(data, &StealthUpgradeFieldParse);
	return (ModuleData *)data;
}

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

class MultiIniFieldParse;

// Retail's module-data factories reach INI through initFromINIMultiProc
// (0x00852130), which takes the class's buildFieldParse proc; the
// FieldParse-table overload this TU used to name lives at 0x008520A0.
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINIMultiProc(void *what,
		void (__cdecl *buildFieldParse)(MultiIniFieldParse &));
};

extern "C" void __cdecl StealthUpgradeFieldParse(MultiIniFieldParse &parse);

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/StealthUpgrade.h
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
		ini->initFromINIMultiProc(data, &StealthUpgradeFieldParse);
	return (ModuleData *)data;
}

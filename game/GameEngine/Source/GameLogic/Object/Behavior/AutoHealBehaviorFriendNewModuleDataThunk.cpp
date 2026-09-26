// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: AutoHealBehavior::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AutoHealBehavior.h
class AutoHealBehaviorModuleData
{
public:
	AutoHealBehaviorModuleData();
	virtual ~AutoHealBehaviorModuleData();

private:
	unsigned char m_pad[0xa4];
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

extern "C" void __cdecl AutoHealBehaviorFieldParse(MultiIniFieldParse &parse);

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AutoHealBehavior.h
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
		ini->initFromINIMultiProc(data, &AutoHealBehaviorFieldParse);
	return (ModuleData *)data;
}

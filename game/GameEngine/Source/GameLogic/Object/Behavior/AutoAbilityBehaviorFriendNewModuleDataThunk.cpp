// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: AutoAbilityBehavior::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class AutoAbilityBehaviorModuleData
{
public:
	AutoAbilityBehaviorModuleData();
	virtual ~AutoAbilityBehaviorModuleData();

private:
	unsigned char m_pad[0x8];
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

extern "C" void __cdecl AutoAbilityBehaviorFieldParse(MultiIniFieldParse &parse);

class AutoAbilityBehavior
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@AutoAbilityBehavior@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *AutoAbilityBehavior::friend_newModuleData(INI *ini)
{
	AutoAbilityBehaviorModuleData *data = new AutoAbilityBehaviorModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, &AutoAbilityBehaviorFieldParse);
	return (ModuleData *)data;
}

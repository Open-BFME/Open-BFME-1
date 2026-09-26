// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: ModelConditionUpgrade::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ModelConditionUpgrade.h
class ModelConditionUpgradeModuleData
{
public:
	ModelConditionUpgradeModuleData();
	virtual ~ModelConditionUpgradeModuleData();

private:
	unsigned char m_pad[0xbc];
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

extern "C" void __cdecl ModelConditionUpgradeFieldParse(MultiIniFieldParse &parse);

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ModelConditionUpgrade.h
class ModelConditionUpgrade
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@ModelConditionUpgrade@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *ModelConditionUpgrade::friend_newModuleData(INI *ini)
{
	ModelConditionUpgradeModuleData *data = new ModelConditionUpgradeModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, &ModelConditionUpgradeFieldParse);
	return (ModuleData *)data;
}

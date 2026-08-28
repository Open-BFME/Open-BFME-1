// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: ModelConditionUpgrade::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ModelConditionUpgrade.h
class ModelConditionUpgradeModuleData
{
public:
	ModelConditionUpgradeModuleData();
	virtual ~ModelConditionUpgradeModuleData();

private:
	unsigned char m_pad[0xbc];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char ModelConditionUpgradeFieldParse;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ModelConditionUpgrade.h
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
		ini->initFromINI(data, &ModelConditionUpgradeFieldParse);
	return (ModuleData *)data;
}

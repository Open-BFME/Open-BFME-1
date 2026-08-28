// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: ModelConditionSpecialAbilityUpdate::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class ModelConditionSpecialAbilityUpdateModuleData
{
public:
	ModelConditionSpecialAbilityUpdateModuleData();
	virtual ~ModelConditionSpecialAbilityUpdateModuleData();

private:
	unsigned char m_pad[0x25c];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char ModelConditionSpecialAbilityUpdateFieldParse;

class ModelConditionSpecialAbilityUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@ModelConditionSpecialAbilityUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *ModelConditionSpecialAbilityUpdate::friend_newModuleData(INI *ini)
{
	ModelConditionSpecialAbilityUpdateModuleData *data = new ModelConditionSpecialAbilityUpdateModuleData;
	if (ini)
		ini->initFromINI(data, &ModelConditionSpecialAbilityUpdateFieldParse);
	return (ModuleData *)data;
}

// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: ModelConditionSoundSelectorClientBehavior::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class ModelConditionSoundSelectorClientBehaviorModuleData
{
public:
	ModelConditionSoundSelectorClientBehaviorModuleData();
	virtual ~ModelConditionSoundSelectorClientBehaviorModuleData();

private:
	unsigned char m_pad[0x10];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char ModelConditionSoundSelectorClientBehaviorFieldParse;

class ModelConditionSoundSelectorClientBehavior
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@ModelConditionSoundSelectorClientBehavior@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *ModelConditionSoundSelectorClientBehavior::friend_newModuleData(INI *ini)
{
	ModelConditionSoundSelectorClientBehaviorModuleData *data = new ModelConditionSoundSelectorClientBehaviorModuleData;
	if (ini)
		ini->initFromINI(data, &ModelConditionSoundSelectorClientBehaviorFieldParse);
	return (ModuleData *)data;
}

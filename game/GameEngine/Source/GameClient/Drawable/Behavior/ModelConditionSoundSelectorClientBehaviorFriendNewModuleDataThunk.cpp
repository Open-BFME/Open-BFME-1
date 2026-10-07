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

// Retail pushes 0x0042E703, the matched ILT thunk to 0x00607930.
extern void j_0002e703(void);

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
		ini->initFromINIMultiProc(data, 
			reinterpret_cast<void (__cdecl *)(MultiIniFieldParse &)>(&j_0002e703));
	return (ModuleData *)data;
}

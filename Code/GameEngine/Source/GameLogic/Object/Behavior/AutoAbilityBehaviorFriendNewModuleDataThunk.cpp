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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char AutoAbilityBehaviorFieldParse;

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
		ini->initFromINI(data, &AutoAbilityBehaviorFieldParse);
	return (ModuleData *)data;
}

// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: PassiveAreaEffectBehavior::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class PassiveAreaEffectBehaviorModuleData
{
public:
	PassiveAreaEffectBehaviorModuleData();
	virtual ~PassiveAreaEffectBehaviorModuleData();

private:
	unsigned char m_pad[0x20];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char PassiveAreaEffectBehaviorFieldParse;

class PassiveAreaEffectBehavior
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@PassiveAreaEffectBehavior@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *PassiveAreaEffectBehavior::friend_newModuleData(INI *ini)
{
	PassiveAreaEffectBehaviorModuleData *data = new PassiveAreaEffectBehaviorModuleData;
	if (ini)
		ini->initFromINI(data, &PassiveAreaEffectBehaviorFieldParse);
	return (ModuleData *)data;
}

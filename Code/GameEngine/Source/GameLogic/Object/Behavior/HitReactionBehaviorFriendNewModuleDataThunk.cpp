// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: HitReactionBehavior::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class HitReactionBehaviorModuleData
{
public:
	HitReactionBehaviorModuleData();
	virtual ~HitReactionBehaviorModuleData();

private:
	unsigned char m_pad[0x2c];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char HitReactionBehaviorFieldParse;

class HitReactionBehavior
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@HitReactionBehavior@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *HitReactionBehavior::friend_newModuleData(INI *ini)
{
	HitReactionBehaviorModuleData *data = new HitReactionBehaviorModuleData;
	if (ini)
		ini->initFromINI(data, &HitReactionBehaviorFieldParse);
	return (ModuleData *)data;
}

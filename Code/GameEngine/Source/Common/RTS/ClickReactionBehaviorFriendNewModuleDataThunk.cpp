// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: ClickReactionBehavior::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class ClickReactionBehaviorModuleData
{
public:
	ClickReactionBehaviorModuleData();
	virtual ~ClickReactionBehaviorModuleData();

private:
	unsigned char m_pad[0x20];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char ClickReactionBehaviorFieldParse;

class ClickReactionBehavior
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@ClickReactionBehavior@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *ClickReactionBehavior::friend_newModuleData(INI *ini)
{
	ClickReactionBehaviorModuleData *data = new ClickReactionBehaviorModuleData;
	if (ini)
		ini->initFromINI(data, &ClickReactionBehaviorFieldParse);
	return (ModuleData *)data;
}

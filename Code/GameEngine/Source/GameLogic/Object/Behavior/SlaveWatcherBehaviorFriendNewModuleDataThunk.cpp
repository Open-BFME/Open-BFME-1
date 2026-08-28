// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: SlaveWatcherBehavior::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class SlaveWatcherBehaviorModuleData
{
public:
	SlaveWatcherBehaviorModuleData();
	virtual ~SlaveWatcherBehaviorModuleData();

private:
	unsigned char m_pad[0xc];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char SlaveWatcherBehaviorFieldParse;

class SlaveWatcherBehavior
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@SlaveWatcherBehavior@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *SlaveWatcherBehavior::friend_newModuleData(INI *ini)
{
	SlaveWatcherBehaviorModuleData *data = new SlaveWatcherBehaviorModuleData;
	if (ini)
		ini->initFromINI(data, &SlaveWatcherBehaviorFieldParse);
	return (ModuleData *)data;
}

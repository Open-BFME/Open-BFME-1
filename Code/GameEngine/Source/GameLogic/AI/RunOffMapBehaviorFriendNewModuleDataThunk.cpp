// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: RunOffMapBehavior::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class RunOffMapBehaviorModuleData
{
public:
	RunOffMapBehaviorModuleData();
	virtual ~RunOffMapBehaviorModuleData();

private:
	unsigned char m_pad[0x18];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char RunOffMapBehaviorFieldParse;

class RunOffMapBehavior
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@RunOffMapBehavior@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *RunOffMapBehavior::friend_newModuleData(INI *ini)
{
	RunOffMapBehaviorModuleData *data = new RunOffMapBehaviorModuleData;
	if (ini)
		ini->initFromINI(data, &RunOffMapBehaviorFieldParse);
	return (ModuleData *)data;
}

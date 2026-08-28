// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: SiegeDockingBehavior::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class SiegeDockingBehaviorModuleData
{
public:
	SiegeDockingBehaviorModuleData();
	virtual ~SiegeDockingBehaviorModuleData();

private:
	unsigned char m_pad[0x8];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char SiegeDockingBehaviorFieldParse;

class SiegeDockingBehavior
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@SiegeDockingBehavior@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *SiegeDockingBehavior::friend_newModuleData(INI *ini)
{
	SiegeDockingBehaviorModuleData *data = new SiegeDockingBehaviorModuleData;
	if (ini)
		ini->initFromINI(data, &SiegeDockingBehaviorFieldParse);
	return (ModuleData *)data;
}

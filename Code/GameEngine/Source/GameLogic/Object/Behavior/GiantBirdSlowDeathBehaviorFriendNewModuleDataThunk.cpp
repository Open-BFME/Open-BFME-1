// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: GiantBirdSlowDeathBehavior::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class GiantBirdSlowDeathBehaviorModuleData
{
public:
	GiantBirdSlowDeathBehaviorModuleData();
	virtual ~GiantBirdSlowDeathBehaviorModuleData();

private:
	unsigned char m_pad[0x244];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char GiantBirdSlowDeathBehaviorFieldParse;

class GiantBirdSlowDeathBehavior
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@GiantBirdSlowDeathBehavior@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *GiantBirdSlowDeathBehavior::friend_newModuleData(INI *ini)
{
	GiantBirdSlowDeathBehaviorModuleData *data = new GiantBirdSlowDeathBehaviorModuleData;
	if (ini)
		ini->initFromINI(data, &GiantBirdSlowDeathBehaviorFieldParse);
	return (ModuleData *)data;
}

// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: OathbreakersFadeAwayBehavior::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class OathbreakersFadeAwayBehaviorModuleData
{
public:
	OathbreakersFadeAwayBehaviorModuleData();
	virtual ~OathbreakersFadeAwayBehaviorModuleData();

private:
	unsigned char m_pad[0x1c];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char OathbreakersFadeAwayBehaviorFieldParse;

class OathbreakersFadeAwayBehavior
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@OathbreakersFadeAwayBehavior@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *OathbreakersFadeAwayBehavior::friend_newModuleData(INI *ini)
{
	OathbreakersFadeAwayBehaviorModuleData *data = new OathbreakersFadeAwayBehaviorModuleData;
	if (ini)
		ini->initFromINI(data, &OathbreakersFadeAwayBehaviorFieldParse);
	return (ModuleData *)data;
}

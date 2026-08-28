// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: ShareExperienceBehavior::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class ShareExperienceBehaviorModuleData
{
public:
	ShareExperienceBehaviorModuleData();
	virtual ~ShareExperienceBehaviorModuleData();

private:
	unsigned char m_pad[0x14];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char ShareExperienceBehaviorFieldParse;

class ShareExperienceBehavior
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@ShareExperienceBehavior@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *ShareExperienceBehavior::friend_newModuleData(INI *ini)
{
	ShareExperienceBehaviorModuleData *data = new ShareExperienceBehaviorModuleData;
	if (ini)
		ini->initFromINI(data, &ShareExperienceBehaviorFieldParse);
	return (ModuleData *)data;
}

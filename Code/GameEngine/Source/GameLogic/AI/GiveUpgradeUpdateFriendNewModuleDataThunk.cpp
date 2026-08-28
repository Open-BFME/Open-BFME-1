// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: GiveUpgradeUpdate::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class GiveUpgradeUpdateModuleData
{
public:
	GiveUpgradeUpdateModuleData();
	virtual ~GiveUpgradeUpdateModuleData();

private:
	unsigned char m_pad[0x270];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char GiveUpgradeUpdateFieldParse;

class GiveUpgradeUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@GiveUpgradeUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *GiveUpgradeUpdate::friend_newModuleData(INI *ini)
{
	GiveUpgradeUpdateModuleData *data = new GiveUpgradeUpdateModuleData;
	if (ini)
		ini->initFromINI(data, &GiveUpgradeUpdateFieldParse);
	return (ModuleData *)data;
}

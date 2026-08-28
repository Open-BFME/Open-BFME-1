// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: BaseUpgrade::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class BaseUpgradeModuleData
{
public:
	BaseUpgradeModuleData();
	virtual ~BaseUpgradeModuleData();

private:
	unsigned char m_pad[0x78];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char BaseUpgradeFieldParse;

class BaseUpgrade
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@BaseUpgrade@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *BaseUpgrade::friend_newModuleData(INI *ini)
{
	BaseUpgradeModuleData *data = new BaseUpgradeModuleData;
	if (ini)
		ini->initFromINI(data, &BaseUpgradeFieldParse);
	return (ModuleData *)data;
}

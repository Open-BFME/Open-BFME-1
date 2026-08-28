// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: TooltipUpgrade::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class TooltipUpgradeModuleData
{
public:
	TooltipUpgradeModuleData();
	virtual ~TooltipUpgradeModuleData();

private:
	unsigned char m_pad[0x74];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char TooltipUpgradeFieldParse;

class TooltipUpgrade
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@TooltipUpgrade@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *TooltipUpgrade::friend_newModuleData(INI *ini)
{
	TooltipUpgradeModuleData *data = new TooltipUpgradeModuleData;
	if (ini)
		ini->initFromINI(data, &TooltipUpgradeFieldParse);
	return (ModuleData *)data;
}

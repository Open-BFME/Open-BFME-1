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

class MultiIniFieldParse;

// Retail's module-data factories reach INI through initFromINIMultiProc
// (0x00852130), which takes the class's buildFieldParse proc; the
// FieldParse-table overload this TU used to name lives at 0x008520A0.
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINIMultiProc(void *what,
		void (__cdecl *buildFieldParse)(MultiIniFieldParse &));
};

extern "C" void __cdecl TooltipUpgradeFieldParse(MultiIniFieldParse &parse);

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
		ini->initFromINIMultiProc(data, &TooltipUpgradeFieldParse);
	return (ModuleData *)data;
}

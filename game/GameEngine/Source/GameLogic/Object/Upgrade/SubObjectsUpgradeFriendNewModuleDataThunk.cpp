// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: SubObjectsUpgrade::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SubObjectsUpgrade.h
class SubObjectsUpgradeModuleData
{
public:
	SubObjectsUpgradeModuleData();
	virtual ~SubObjectsUpgradeModuleData();

private:
	unsigned char m_pad[0xa8];
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

extern "C" void __cdecl SubObjectsUpgradeFieldParse(MultiIniFieldParse &parse);

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SubObjectsUpgrade.h
class SubObjectsUpgrade
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@SubObjectsUpgrade@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *SubObjectsUpgrade::friend_newModuleData(INI *ini)
{
	SubObjectsUpgradeModuleData *data = new SubObjectsUpgradeModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, &SubObjectsUpgradeFieldParse);
	return (ModuleData *)data;
}

// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: ObjectCreationUpgrade::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ObjectCreationUpgrade.h
class ObjectCreationUpgradeModuleData
{
public:
	ObjectCreationUpgradeModuleData();
	virtual ~ObjectCreationUpgradeModuleData();

private:
	unsigned char m_pad[0xa0];
};

class MultiIniFieldParse;

// Retail's module-data factories reach INI through initFromINIMultiProc
// (0x00852130), which takes the class's buildFieldParse proc; the
// FieldParse-table overload this TU used to name lives at 0x008520A0.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINIMultiProc(void *what,
		void (__cdecl *buildFieldParse)(MultiIniFieldParse &));
};

extern "C" void __cdecl ObjectCreationUpgradeFieldParse(MultiIniFieldParse &parse);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ObjectCreationUpgrade.h
class ObjectCreationUpgrade
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@ObjectCreationUpgrade@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *ObjectCreationUpgrade::friend_newModuleData(INI *ini)
{
	ObjectCreationUpgradeModuleData *data = new ObjectCreationUpgradeModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, &ObjectCreationUpgradeFieldParse);
	return (ModuleData *)data;
}

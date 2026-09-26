// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: GeometryUpgrade module-data and instance factories.

class Module;
class Thing;
class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class GeometryUpgradeModuleData
{
public:
	GeometryUpgradeModuleData();
	virtual ~GeometryUpgradeModuleData();

private:
	unsigned char m_pad[0x90];
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

extern "C" void __cdecl GeometryUpgradeFieldParse(MultiIniFieldParse &parse);

class GeometryUpgrade
{
public:
	GeometryUpgrade(Thing *, const ModuleData *);
	static ModuleData *friend_newModuleData(INI *ini);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0x20];
};

// ?friend_newModuleData@GeometryUpgrade@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *GeometryUpgrade::friend_newModuleData(INI *ini)
{
	GeometryUpgradeModuleData *data = new GeometryUpgradeModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, &GeometryUpgradeFieldParse);
	return (ModuleData *)data;
}

// ?friend_newModuleInstance@GeometryUpgrade@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *GeometryUpgrade::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new GeometryUpgrade(thing, data);
}

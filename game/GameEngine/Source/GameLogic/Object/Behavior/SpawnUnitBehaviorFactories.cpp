// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: SpawnUnitBehavior module-data and instance factories.

class Module;
class Thing;
class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class SpawnUnitBehaviorModuleData
{
public:
	SpawnUnitBehaviorModuleData();
	virtual ~SpawnUnitBehaviorModuleData();

private:
	unsigned char m_pad[0x1c];
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

extern "C" void __cdecl SpawnUnitBehaviorFieldParse(MultiIniFieldParse &parse);

class SpawnUnitBehavior
{
public:
	SpawnUnitBehavior(Thing *, const ModuleData *);
	static ModuleData *friend_newModuleData(INI *ini);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0x28];
};

// ?friend_newModuleData@SpawnUnitBehavior@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *SpawnUnitBehavior::friend_newModuleData(INI *ini)
{
	SpawnUnitBehaviorModuleData *data = new SpawnUnitBehaviorModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, &SpawnUnitBehaviorFieldParse);
	return (ModuleData *)data;
}

// ?friend_newModuleInstance@SpawnUnitBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *SpawnUnitBehavior::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new SpawnUnitBehavior(thing, data);
}

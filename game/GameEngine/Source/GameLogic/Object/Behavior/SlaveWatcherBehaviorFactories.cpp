// cl: /DNDEBUG /MD /EHsc
// SlaveWatcherBehavior factories: retail 0x00117540 allocates 0x10
// bytes for module data; 0x001174C0 allocates 0x24 for the instance.
// Preserve both constructor views and the named INI proc contract.

class Module;
class Thing;
class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class SlaveWatcherBehaviorModuleData
{
public:
	SlaveWatcherBehaviorModuleData();
	virtual ~SlaveWatcherBehaviorModuleData();

private:
	unsigned char m_pad[0xc];
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

extern "C" void __cdecl SlaveWatcherBehaviorFieldParse(MultiIniFieldParse &parse);

class SlaveWatcherBehavior
{
public:
	SlaveWatcherBehavior(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x24];
};

// ?friend_newModuleData@SlaveWatcherBehavior@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *SlaveWatcherBehavior::friend_newModuleData(INI *ini)
{
	SlaveWatcherBehaviorModuleData *data = new SlaveWatcherBehaviorModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, &SlaveWatcherBehaviorFieldParse);
	return (ModuleData *)data;
}

// ?friend_newModuleInstance@SlaveWatcherBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *SlaveWatcherBehavior::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new SlaveWatcherBehavior(thing, data);
}

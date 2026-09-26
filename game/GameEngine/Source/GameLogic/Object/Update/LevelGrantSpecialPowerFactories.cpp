// cl: /DNDEBUG /MD /EHsc
// LevelGrantSpecialPower factories: 0x284-byte data and 0xe8-byte instance.
// Retail EH metadata links 0x0011FF90 to 0x00C00B00 and 0x00120010
// to 0x00C00B20; both cleanup handlers release the failed allocation.

class INI;
class Thing;
class Module;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class LevelGrantSpecialPowerModuleData
{
public:
	LevelGrantSpecialPowerModuleData();
	virtual ~LevelGrantSpecialPowerModuleData();

private:
	unsigned char m_pad[0x280];
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

extern "C" void __cdecl LevelGrantSpecialPowerFieldParse(MultiIniFieldParse &parse);

class LevelGrantSpecialPower
{
public:
	LevelGrantSpecialPower(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0xe8];
};

// ?friend_newModuleData@LevelGrantSpecialPower@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *LevelGrantSpecialPower::friend_newModuleData(INI *ini)
{
	LevelGrantSpecialPowerModuleData *data = new LevelGrantSpecialPowerModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, &LevelGrantSpecialPowerFieldParse);
	return (ModuleData *)data;
}

// ?friend_newModuleInstance@LevelGrantSpecialPower@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *LevelGrantSpecialPower::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new LevelGrantSpecialPower(thing, data);
}

// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: WeaponChangeSpecialPowerModule::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class WeaponChangeSpecialPowerModuleModuleData
{
public:
	WeaponChangeSpecialPowerModuleModuleData();
	virtual ~WeaponChangeSpecialPowerModuleModuleData();

private:
	unsigned char m_pad[0x220];
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

// Retail's factory at WeaponChangeSpecialPowerModule pushes 0x0043FD3C here (see
// ?friend_newModuleData@WeaponChangeSpecialPowerModule@@SAPAVModuleData@@PAVINI@@@Z), and the only symbol the
// build defines at that address is the five-byte ILT thunk ?j_0003fd3c@@YAXXZ, which
// game/gen_small/gthunks_071.cpp implements as a `jmp` to the module-data
// class's static field-parse builder; the thunk is retail's real spelling of
// this operand.
void __cdecl j_0003fd3c(); // ?j_0003fd3c@@YAXXZ, ILT 0x0043FD3C

class WeaponChangeSpecialPowerModule
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@WeaponChangeSpecialPowerModule@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *WeaponChangeSpecialPowerModule::friend_newModuleData(INI *ini)
{
	WeaponChangeSpecialPowerModuleModuleData *data = new WeaponChangeSpecialPowerModuleModuleData;
	if (ini)
		ini->initFromINIMultiProc(data,
			reinterpret_cast<void (__cdecl *)(MultiIniFieldParse &)>(j_0003fd3c));
	return (ModuleData *)data;
}

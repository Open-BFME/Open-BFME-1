// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: FreezingRainSpecialPower::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class FreezingRainSpecialPowerModuleData
{
public:
	FreezingRainSpecialPowerModuleData();
	virtual ~FreezingRainSpecialPowerModuleData();

private:
	unsigned char m_pad[0x214];
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

// Retail's factory at FreezingRainSpecialPower pushes 0x0044157E here (see
// ?friend_newModuleData@FreezingRainSpecialPower@@SAPAVModuleData@@PAVINI@@@Z), and the only symbol the
// build defines at that address is the five-byte ILT thunk ?j_0004157e@@YAXXZ, which
// game/gen_small/gthunks_073.cpp implements as a `jmp` to the module-data
// class's static field-parse builder.  The old
// `extern "C" FreezingRainSpecialPowerFieldParse` was invented in this TU and nothing
// defines it; the thunk is retail's real spelling of this operand.
extern "C" void __cdecl __identifier("FreezingRainSpecialPowerFieldParse")();

class FreezingRainSpecialPower
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@FreezingRainSpecialPower@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *FreezingRainSpecialPower::friend_newModuleData(INI *ini)
{
	FreezingRainSpecialPowerModuleData *data = new FreezingRainSpecialPowerModuleData;
	if (ini)
		ini->initFromINIMultiProc(data,
			reinterpret_cast<void (__cdecl *)(MultiIniFieldParse &)>(__identifier("FreezingRainSpecialPowerFieldParse")));
	return (ModuleData *)data;
}

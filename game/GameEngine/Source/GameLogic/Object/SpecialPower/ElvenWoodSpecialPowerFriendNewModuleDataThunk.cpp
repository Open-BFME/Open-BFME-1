// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: ElvenWoodSpecialPower::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class ElvenWoodSpecialPowerModuleData
{
public:
	ElvenWoodSpecialPowerModuleData();
	virtual ~ElvenWoodSpecialPowerModuleData();

private:
	unsigned char m_pad[0x22c];
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

// Retail's factory at ElvenWoodSpecialPower pushes 0x00439176 here (see
// ?friend_newModuleData@ElvenWoodSpecialPower@@SAPAVModuleData@@PAVINI@@@Z), and the only symbol the
// build defines at that address is the five-byte ILT thunk ?j_00039176@@YAXXZ, which
// game/gen_small/gthunks_063.cpp implements as a `jmp` to the module-data
// class's static field-parse builder.  The old
// address-of spelling was an invented extern "C" name that nothing
// defines it; the thunk is retail's real spelling of this operand.
void __cdecl j_00039176(); // ?j_00039176@@YAXXZ, ILT 0x00439176

class ElvenWoodSpecialPower
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@ElvenWoodSpecialPower@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *ElvenWoodSpecialPower::friend_newModuleData(INI *ini)
{
	ElvenWoodSpecialPowerModuleData *data = new ElvenWoodSpecialPowerModuleData;
	if (ini)
		ini->initFromINIMultiProc(data,
			reinterpret_cast<void (__cdecl *)(MultiIniFieldParse &)>(&j_00039176));
	return (ModuleData *)data;
}

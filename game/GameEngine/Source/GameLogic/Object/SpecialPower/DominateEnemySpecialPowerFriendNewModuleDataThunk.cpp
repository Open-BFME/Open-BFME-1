// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: DominateEnemySpecialPower::friend_newModuleData factory, retail 0x001221C0,
// converted out of a machine byte dump.
//
// Every module's data factory is this same body -- allocate the module data,
// hand it and the class's field-parse table to INI::initFromINI when there is
// an INI to parse from, return it -- so only the registration block names it,
// by pushing this address beside the AsciiString "DominateEnemySpecialPower".
//
// Retail allocates 0x260 bytes, which is sizeof(DominateEnemySpecialPowerModuleData) with its
// vptr, and calls the constructor through 0x00018985.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class DominateEnemySpecialPowerModuleData
{
public:
	DominateEnemySpecialPowerModuleData();
	virtual ~DominateEnemySpecialPowerModuleData();

private:
	unsigned char m_pad[0x25C];
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

// Retail's factory does not push the field-parse builder itself: at +0x51 it
// pushes VA 0x00413C23, which is the 5-byte ILT thunk RVA 0x00013C23
// (e9 98 70 24 00 -> RVA 0x0025ACC0, the 30-byte builder
// ?buildFieldParse@Rva0025ACC0@@SAXAAVWideMulti@@@Z in
// Common/WideBuildFieldParse.cpp, which chains the base builder at the thunk
// RVA 0x0000629E then registers its own .rdata table).  The thunk is the address
// retail pushes, so the reference spells the thunk the ledger owns there; the real
// EA identity of the builder it reaches is
// ?buildFieldParse@DominateEnemySpecialPowerModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// still address-derived in the ledger.
void __cdecl j_00013c23();

class DominateEnemySpecialPower
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@DominateEnemySpecialPower@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *DominateEnemySpecialPower::friend_newModuleData(INI *ini)
{
	DominateEnemySpecialPowerModuleData *data = new DominateEnemySpecialPowerModuleData;
	if (ini)
		ini->initFromINIMultiProc(data,
			reinterpret_cast<void (__cdecl *)(MultiIniFieldParse &)>( &j_00013c23 ));
	return (ModuleData *)data;
}

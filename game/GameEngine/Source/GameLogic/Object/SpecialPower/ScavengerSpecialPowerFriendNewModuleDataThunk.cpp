// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: ScavengerSpecialPower::friend_newModuleData factory, retail 0x00120560,
// converted out of a machine byte dump.
//
// Every module's data factory is this same body -- allocate the module data,
// hand it and the class's field-parse table to INI::initFromINI when there is
// an INI to parse from, return it -- so only the registration block names it,
// by pushing this address beside the AsciiString "ScavengerSpecialPower".
//
// Retail allocates 0x214 bytes, which is sizeof(ScavengerSpecialPowerModuleData) with its
// vptr, and calls the constructor through 0x00019461.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class ScavengerSpecialPowerModuleData
{
public:
	ScavengerSpecialPowerModuleData();
	virtual ~ScavengerSpecialPowerModuleData();

private:
	unsigned char m_pad[0x210];
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
// pushes VA 0x0040F9E3, which is the 5-byte ILT thunk RVA 0x0000F9E3
// (e9 98 5e 25 00 -> RVA 0x00265880, the 30-byte builder
// ?buildFieldParse@Rva00265880@@SAXAAVWideMulti@@@Z in
// Common/WideBuildFieldParse.cpp, which chains the base builder at the thunk
// RVA 0x0002AF8B then registers its own .rdata table).  The thunk is the address
// retail pushes, so the reference spells the thunk the ledger owns there; the real
// EA identity of the builder it reaches is
// ?buildFieldParse@ScavengerSpecialPowerModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// still address-derived in the ledger.
void __cdecl j_0000f9e3();

class ScavengerSpecialPower
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@ScavengerSpecialPower@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *ScavengerSpecialPower::friend_newModuleData(INI *ini)
{
	ScavengerSpecialPowerModuleData *data = new ScavengerSpecialPowerModuleData;
	if (ini)
		ini->initFromINIMultiProc(data,
			reinterpret_cast<void (__cdecl *)(MultiIniFieldParse &)>( &j_0000f9e3 ));
	return (ModuleData *)data;
}

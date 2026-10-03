// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: CloudBreakSpecialPower::friend_newModuleData factory, retail 0x00120670,
// converted out of a machine byte dump.
//
// Every module's data factory is this same body -- allocate the module data,
// hand it and the class's field-parse table to INI::initFromINI when there is
// an INI to parse from, return it -- so only the registration block names it,
// by pushing this address beside the AsciiString "CloudBreakSpecialPower".
//
// Retail allocates 0x220 bytes, which is sizeof(CloudBreakSpecialPowerModuleData) with its
// vptr, and calls the constructor through 0x0002DF3D.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class CloudBreakSpecialPowerModuleData
{
public:
	CloudBreakSpecialPowerModuleData();
	virtual ~CloudBreakSpecialPowerModuleData();

private:
	unsigned char m_pad[0x21C];
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
// pushes VA 0x0043EC8E, which is the 5-byte ILT thunk RVA 0x0003EC8E
// (e9 4d a3 21 00 -> RVA 0x00258FE0, the 30-byte builder
// ?buildFieldParse@Rva00258FE0@@SAXAAVWideMulti@@@Z in
// Common/WideBuildFieldParse.cpp, which chains the base builder at the thunk
// RVA 0x0002AF8B then registers its own .rdata table).  The thunk is the address
// retail pushes, so the reference spells the thunk the ledger owns there; the real
// EA identity of the builder it reaches is
// ?buildFieldParse@CloudBreakSpecialPowerModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// still address-derived in the ledger.
void __cdecl j_0003ec8e();

class CloudBreakSpecialPower
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@CloudBreakSpecialPower@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *CloudBreakSpecialPower::friend_newModuleData(INI *ini)
{
	CloudBreakSpecialPowerModuleData *data = new CloudBreakSpecialPowerModuleData;
	if (ini)
		ini->initFromINIMultiProc(data,
			reinterpret_cast<void (__cdecl *)(MultiIniFieldParse &)>( &j_0003ec8e ));
	return (ModuleData *)data;
}

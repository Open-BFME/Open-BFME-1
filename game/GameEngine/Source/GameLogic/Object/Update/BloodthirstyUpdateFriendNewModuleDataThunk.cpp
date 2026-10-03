// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: BloodthirstyUpdate::friend_newModuleData factory, retail 0x00114030,
// converted out of a machine byte dump.
//
// Every module's data factory is this same body -- allocate the module data,
// hand it and the class's field-parse table to INI::initFromINI when there is
// an INI to parse from, return it -- so only the registration block names it,
// by pushing this address beside the AsciiString "BloodthirstyUpdate".
//
// Retail allocates 0xF0 bytes, which is sizeof(BloodthirstyUpdateModuleData) with its
// vptr, and calls the constructor through 0x0001C684.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class BloodthirstyUpdateModuleData
{
public:
	BloodthirstyUpdateModuleData();
	virtual ~BloodthirstyUpdateModuleData();

private:
	unsigned char m_pad[0xEC];
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
// pushes VA 0x0042C822, which is the 5-byte ILT thunk RVA 0x0002C822
// (e9 39 a7 25 00 -> RVA 0x00286F60, the 17-byte table-register forwarder
// ?Rva00286F60@@YAXPAVGen00850920@@@Z in Common/MidTableRegisterForwarders.cpp,
// which registers the .rdata table 0x010BC738).  The thunk is the address retail
// pushes, so the reference spells the thunk the ledger owns there; the real EA
// identity of the builder it reaches is
// ?buildFieldParse@BloodthirstyUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// still address-derived in the ledger.
void __cdecl j_0002c822();

class BloodthirstyUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@BloodthirstyUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *BloodthirstyUpdate::friend_newModuleData(INI *ini)
{
	BloodthirstyUpdateModuleData *data = new BloodthirstyUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data,
			reinterpret_cast<void (__cdecl *)(MultiIniFieldParse &)>( &j_0002c822 ));
	return (ModuleData *)data;
}

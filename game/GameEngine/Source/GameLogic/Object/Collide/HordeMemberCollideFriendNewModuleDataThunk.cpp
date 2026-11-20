// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: HordeMemberCollide::friend_newModuleData factory, retail 0x00124890,
// converted out of a machine byte dump.
//
// Every module's data factory is this same body -- allocate the module data,
// hand it and the class's field-parse table to INI::initFromINI when there is
// an INI to parse from, return it -- so only the registration block names it,
// by pushing this address beside the AsciiString "HordeMemberCollide".
//
// Retail allocates 0x8 bytes, which is sizeof(HordeMemberCollideModuleData) with its
// vptr, and calls the constructor through 0x000317C8.


class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class HordeMemberCollideModuleData
{
public:
	HordeMemberCollideModuleData();
	virtual ~HordeMemberCollideModuleData();

private:
	unsigned char m_pad[0x4];
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

// The proc retail passes is VA 0x004173DC, the ILT stub at RVA 0x000173DC,
// which jumps to the one-byte no-op builder at 0x00122E80 shared by the
// HordeMemberCollide and SquishCollide factories.  No class-specific builder
// name is provable for the shared stub, so the reference names the matched
// address-derived ?Rva00122E80Noop@@YAXXZ that the stub reaches and casts it
// to the initFromINIMultiProc parameter type (no code: push offset either
// way).  That defined name lets the reference link.
void Rva00122E80Noop();
typedef void (__cdecl *Rva00122E80BuildFieldParse)(MultiIniFieldParse &);

class HordeMemberCollide
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@HordeMemberCollide@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *HordeMemberCollide::friend_newModuleData(INI *ini)
{
	HordeMemberCollideModuleData *data = new HordeMemberCollideModuleData;
	if (ini)
		ini->initFromINIMultiProc(data,
			(Rva00122E80BuildFieldParse)Rva00122E80Noop);
	return (ModuleData *)data;
}

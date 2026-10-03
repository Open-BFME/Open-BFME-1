// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: W3DLightDraw::friend_newModuleData factory, retail 0x006BFB50,
// converted out of a machine byte dump.
//
// Every module's data factory is this same body -- allocate the module data,
// hand it and the class's field-parse table to INI::initFromINI when there is
// an INI to parse from, return it -- so only the registration block names it,
// by pushing this address beside the AsciiString "W3DLightDraw".
//
// Retail allocates 0x48 bytes, which is sizeof(W3DLightDrawModuleData) with its
// vptr, and calls the constructor through 0x00028D9E.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class W3DLightDrawModuleData
{
public:
	W3DLightDrawModuleData();
	virtual ~W3DLightDrawModuleData();

private:
	unsigned char m_pad[0x44];
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

// Retail pushes the incremental-link thunk at 0x0003B5D9, not a body: that
// thunk forwards to the 17-byte field-parse builder at 0x00758840 (matched row
// ?Rva00758840@@YAXPAVGen00850920@@@Z in MidTableRegisterForwarders.cpp), so
// the linked name of the value this factory hands initFromINIMultiProc is the
// address-identified thunk ?j_0003b5d9@@YAXXZ (matched row in
// game/gen_small/gthunks_066.cpp). No retail body carries a free-function
// W3DLightDrawFieldParse, so nothing may be declared under that name here.
extern void j_0003b5d9();

class W3DLightDraw
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@W3DLightDraw@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *W3DLightDraw::friend_newModuleData(INI *ini)
{
	W3DLightDrawModuleData *data = new W3DLightDrawModuleData;
	if (ini)
		ini->initFromINIMultiProc(data,
			reinterpret_cast<void (__cdecl *)(MultiIniFieldParse &)>(&j_0003b5d9));
	return (ModuleData *)data;
}

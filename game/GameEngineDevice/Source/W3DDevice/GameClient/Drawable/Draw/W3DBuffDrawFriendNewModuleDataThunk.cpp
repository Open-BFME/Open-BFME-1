// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: W3DBuffDraw::friend_newModuleData factory, retail 0x006BF820,
// converted out of a machine byte dump.
//
// Every module's data factory is this same body -- allocate the module data,
// hand it and the class's field-parse table to INI::initFromINI when there is
// an INI to parse from, return it -- so only the registration block names it,
// by pushing this address beside the AsciiString "W3DBuffDraw".
//
// Retail allocates 0x10 bytes, which is sizeof(W3DBuffDrawModuleData) with its
// vptr, and calls the constructor through 0x0001F7FD.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class W3DBuffDrawModuleData
{
public:
	W3DBuffDrawModuleData();
	virtual ~W3DBuffDrawModuleData();

private:
	unsigned char m_pad[0xC];
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

// Retail pushes the incremental-link thunk at 0x0001AB2C, not a body: that
// thunk forwards to the 17-byte field-parse builder at 0x007504A0 (matched row
// ?Rva007504A0@@YAXPAVGen00850920@@@Z in MidTableRegisterForwarders.cpp), so
// the linked name of the value this factory hands initFromINIMultiProc is the
// address-identified thunk ?j_0001ab2c@@YAXXZ (matched row in
// game/gen_small/gthunks_029.cpp). No retail body carries a free-function
// W3DBuffDrawFieldParse, so nothing may be declared under that name here.
extern "C" void __cdecl __identifier("W3DBuffDrawFieldParse")();

class W3DBuffDraw
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@W3DBuffDraw@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *W3DBuffDraw::friend_newModuleData(INI *ini)
{
	W3DBuffDrawModuleData *data = new W3DBuffDrawModuleData;
	if (ini)
		ini->initFromINIMultiProc(data,
			reinterpret_cast<void (__cdecl *)(MultiIniFieldParse &)>(&__identifier("W3DBuffDrawFieldParse")));
	return (ModuleData *)data;
}

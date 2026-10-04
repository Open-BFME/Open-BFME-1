// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: W3DScriptedModelDraw::friend_newModuleData factory, retail 0x006BF0C0,
// converted out of a machine byte dump.
//
// Every module's data factory is this same body -- allocate the module data,
// hand it and the class's field-parse table to INI::initFromINI when there is
// an INI to parse from, return it -- so only the registration block names it,
// by pushing this address beside the AsciiString "W3DScriptedModelDraw".
//
// Retail allocates 0x15C bytes, which is sizeof(W3DScriptedModelDrawModuleData) with its
// vptr, and calls the constructor through 0x0000289C.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class W3DScriptedModelDrawModuleData
{
public:
	W3DScriptedModelDrawModuleData();
	virtual ~W3DScriptedModelDrawModuleData();

private:
	unsigned char m_pad[0x158];
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

// Retail pushes 0x00422584 here: the ILT thunk at RVA 0x00022584
// (game/gen_small/thunks_016.cpp, ?j_00022584@@YAXXZ) that reaches the real
// builder at 0x00B7D380, so the address taken is the thunk's, not the body's.
extern void j_00022584(void);

class W3DScriptedModelDraw
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@W3DScriptedModelDraw@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *W3DScriptedModelDraw::friend_newModuleData(INI *ini)
{
	W3DScriptedModelDrawModuleData *data = new W3DScriptedModelDrawModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, (void (__cdecl *)(MultiIniFieldParse &))j_00022584);
	return (ModuleData *)data;
}

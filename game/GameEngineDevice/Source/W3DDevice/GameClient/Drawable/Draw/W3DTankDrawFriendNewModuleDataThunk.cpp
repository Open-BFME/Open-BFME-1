// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: W3DTankDraw::friend_newModuleData factory, retail 0x006BF600,
// converted out of a machine byte dump.
//
// Same body as every other module-data factory -- allocate, hand it and the
// class's field-parse table to INI::initFromINI when there is an INI, return it
// -- and the draw-module registration block pushes this address beside the
// AsciiString "W3DTankDraw".
//
// Retail allocates 0x170 bytes, which is sizeof(W3DTankDrawModuleData) counting
// its vptr, and calls the constructor through link thunk 0x0003D451.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DTankDraw.h
class W3DTankDrawModuleData
{
public:
	W3DTankDrawModuleData();
	virtual ~W3DTankDrawModuleData();

private:
	unsigned char m_pad[0x16C];
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

extern "C" void __cdecl W3DTankDrawFieldParse(MultiIniFieldParse &parse);

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DTankDraw.h
class W3DTankDraw
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@W3DTankDraw@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *W3DTankDraw::friend_newModuleData(INI *ini)
{
	W3DTankDrawModuleData *data = new W3DTankDrawModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, &W3DTankDrawFieldParse);
	return (ModuleData *)data;
}

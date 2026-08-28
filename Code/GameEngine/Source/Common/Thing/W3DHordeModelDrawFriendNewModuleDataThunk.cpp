// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: W3DHordeModelDraw::friend_newModuleData factory, retail 0x006BFC60,
// converted out of a machine byte dump.
//
// Every module's data factory is this same body -- allocate the module data,
// hand it and the class's field-parse table to INI::initFromINI when there is
// an INI to parse from, return it -- so only the registration block names it,
// by pushing this address beside the AsciiString "W3DHordeModelDraw".
//
// Retail allocates 0x198 bytes, which is sizeof(W3DHordeModelDrawModuleData) with its
// vptr, and calls the constructor through 0x00037187.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class W3DHordeModelDrawModuleData
{
public:
	W3DHordeModelDrawModuleData();
	virtual ~W3DHordeModelDrawModuleData();

private:
	unsigned char m_pad[0x194];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char W3DHordeModelDrawFieldParse;

class W3DHordeModelDraw
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@W3DHordeModelDraw@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *W3DHordeModelDraw::friend_newModuleData(INI *ini)
{
	W3DHordeModelDrawModuleData *data = new W3DHordeModelDrawModuleData;
	if (ini)
		ini->initFromINI(data, &W3DHordeModelDrawFieldParse);
	return (ModuleData *)data;
}

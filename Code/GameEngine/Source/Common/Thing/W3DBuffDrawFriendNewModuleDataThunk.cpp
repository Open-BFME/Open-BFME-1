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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char W3DBuffDrawFieldParse;

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
		ini->initFromINI(data, &W3DBuffDrawFieldParse);
	return (ModuleData *)data;
}

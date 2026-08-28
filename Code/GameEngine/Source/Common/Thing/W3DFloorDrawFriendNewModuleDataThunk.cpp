// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: W3DFloorDraw::friend_newModuleData factory, retail 0x006BFA40,
// converted out of a machine byte dump.
//
// Every module's data factory is this same body -- allocate the module data,
// hand it and the class's field-parse table to INI::initFromINI when there is
// an INI to parse from, return it -- so only the registration block names it,
// by pushing this address beside the AsciiString "W3DFloorDraw".
//
// Retail allocates 0x14 bytes, which is sizeof(W3DFloorDrawModuleData) with its
// vptr, and calls the constructor through 0x0003B0A7.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class W3DFloorDrawModuleData
{
public:
	W3DFloorDrawModuleData();
	virtual ~W3DFloorDrawModuleData();

private:
	unsigned char m_pad[0x10];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char W3DFloorDrawFieldParse;

class W3DFloorDraw
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@W3DFloorDraw@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *W3DFloorDraw::friend_newModuleData(INI *ini)
{
	W3DFloorDrawModuleData *data = new W3DFloorDrawModuleData;
	if (ini)
		ini->initFromINI(data, &W3DFloorDrawFieldParse);
	return (ModuleData *)data;
}

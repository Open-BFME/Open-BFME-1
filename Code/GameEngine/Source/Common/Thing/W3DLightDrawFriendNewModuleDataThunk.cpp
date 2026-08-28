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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char W3DLightDrawFieldParse;

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
		ini->initFromINI(data, &W3DLightDrawFieldParse);
	return (ModuleData *)data;
}

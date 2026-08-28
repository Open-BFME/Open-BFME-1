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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char W3DScriptedModelDrawFieldParse;

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
		ini->initFromINI(data, &W3DScriptedModelDrawFieldParse);
	return (ModuleData *)data;
}

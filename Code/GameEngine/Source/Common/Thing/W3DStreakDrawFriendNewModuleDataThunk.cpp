// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: W3DStreakDraw::friend_newModuleData factory, retail 0x006BFD70,
// converted out of a machine byte dump.
//
// Every module's data factory is this same body -- allocate the module data,
// hand it and the class's field-parse table to INI::initFromINI when there is
// an INI to parse from, return it -- so only the registration block names it,
// by pushing this address beside the AsciiString "W3DStreakDraw".
//
// Retail allocates 0x24 bytes, which is sizeof(W3DStreakDrawModuleData) with its
// vptr, and calls the constructor through 0x000302EC.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class W3DStreakDrawModuleData
{
public:
	W3DStreakDrawModuleData();
	virtual ~W3DStreakDrawModuleData();

private:
	unsigned char m_pad[0x20];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char W3DStreakDrawFieldParse;

class W3DStreakDraw
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@W3DStreakDraw@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *W3DStreakDraw::friend_newModuleData(INI *ini)
{
	W3DStreakDrawModuleData *data = new W3DStreakDrawModuleData;
	if (ini)
		ini->initFromINI(data, &W3DStreakDrawFieldParse);
	return (ModuleData *)data;
}

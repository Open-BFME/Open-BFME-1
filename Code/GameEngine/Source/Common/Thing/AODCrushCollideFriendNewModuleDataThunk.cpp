// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: AODCrushCollide::friend_newModuleData factory, retail 0x0011ECA0,
// converted out of a machine byte dump.
//
// Every module's data factory is this same body -- allocate the module data,
// hand it and the class's field-parse table to INI::initFromINI when there is
// an INI to parse from, return it -- so only the registration block names it,
// by pushing this address beside the AsciiString "AODCrushCollide".
//
// Retail allocates 0x48 bytes, which is sizeof(AODCrushCollideModuleData) with its
// vptr, and calls the constructor through 0x000103E8.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class AODCrushCollideModuleData
{
public:
	AODCrushCollideModuleData();
	virtual ~AODCrushCollideModuleData();

private:
	unsigned char m_pad[0x44];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char AODCrushCollideFieldParse;

class AODCrushCollide
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@AODCrushCollide@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *AODCrushCollide::friend_newModuleData(INI *ini)
{
	AODCrushCollideModuleData *data = new AODCrushCollideModuleData;
	if (ini)
		ini->initFromINI(data, &AODCrushCollideFieldParse);
	return (ModuleData *)data;
}

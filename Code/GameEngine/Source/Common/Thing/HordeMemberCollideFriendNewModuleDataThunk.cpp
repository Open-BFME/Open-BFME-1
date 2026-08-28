// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: HordeMemberCollide::friend_newModuleData factory, retail 0x00124890,
// converted out of a machine byte dump.
//
// Every module's data factory is this same body -- allocate the module data,
// hand it and the class's field-parse table to INI::initFromINI when there is
// an INI to parse from, return it -- so only the registration block names it,
// by pushing this address beside the AsciiString "HordeMemberCollide".
//
// Retail allocates 0x8 bytes, which is sizeof(HordeMemberCollideModuleData) with its
// vptr, and calls the constructor through 0x000317C8.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class HordeMemberCollideModuleData
{
public:
	HordeMemberCollideModuleData();
	virtual ~HordeMemberCollideModuleData();

private:
	unsigned char m_pad[0x4];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char HordeMemberCollideFieldParse;

class HordeMemberCollide
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@HordeMemberCollide@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *HordeMemberCollide::friend_newModuleData(INI *ini)
{
	HordeMemberCollideModuleData *data = new HordeMemberCollideModuleData;
	if (ini)
		ini->initFromINI(data, &HordeMemberCollideFieldParse);
	return (ModuleData *)data;
}

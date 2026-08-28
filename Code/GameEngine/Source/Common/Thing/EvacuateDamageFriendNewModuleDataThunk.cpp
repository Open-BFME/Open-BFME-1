// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: EvacuateDamage::friend_newModuleData factory, retail 0x0011EA90,
// converted out of a machine byte dump.
//
// Every module's data factory is this same body -- allocate the module data,
// hand it and the class's field-parse table to INI::initFromINI when there is
// an INI to parse from, return it -- so only the registration block names it,
// by pushing this address beside the AsciiString "EvacuateDamage".
//
// Retail allocates 0x18 bytes, which is sizeof(EvacuateDamageModuleData) with its
// vptr, and calls the constructor through 0x00018BC9.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class EvacuateDamageModuleData
{
public:
	EvacuateDamageModuleData();
	virtual ~EvacuateDamageModuleData();

private:
	unsigned char m_pad[0x14];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char EvacuateDamageFieldParse;

class EvacuateDamage
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@EvacuateDamage@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *EvacuateDamage::friend_newModuleData(INI *ini)
{
	EvacuateDamageModuleData *data = new EvacuateDamageModuleData;
	if (ini)
		ini->initFromINI(data, &EvacuateDamageFieldParse);
	return (ModuleData *)data;
}

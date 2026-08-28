// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: CloudBreakSpecialPower::friend_newModuleData factory, retail 0x00120670,
// converted out of a machine byte dump.
//
// Every module's data factory is this same body -- allocate the module data,
// hand it and the class's field-parse table to INI::initFromINI when there is
// an INI to parse from, return it -- so only the registration block names it,
// by pushing this address beside the AsciiString "CloudBreakSpecialPower".
//
// Retail allocates 0x220 bytes, which is sizeof(CloudBreakSpecialPowerModuleData) with its
// vptr, and calls the constructor through 0x0002DF3D.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class CloudBreakSpecialPowerModuleData
{
public:
	CloudBreakSpecialPowerModuleData();
	virtual ~CloudBreakSpecialPowerModuleData();

private:
	unsigned char m_pad[0x21C];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char CloudBreakSpecialPowerFieldParse;

class CloudBreakSpecialPower
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@CloudBreakSpecialPower@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *CloudBreakSpecialPower::friend_newModuleData(INI *ini)
{
	CloudBreakSpecialPowerModuleData *data = new CloudBreakSpecialPowerModuleData;
	if (ini)
		ini->initFromINI(data, &CloudBreakSpecialPowerFieldParse);
	return (ModuleData *)data;
}

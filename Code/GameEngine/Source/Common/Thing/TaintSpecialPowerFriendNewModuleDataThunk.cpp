// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: TaintSpecialPower::friend_newModuleData factory, retail 0x00120780,
// converted out of a machine byte dump.
//
// Every module's data factory is this same body -- allocate the module data,
// hand it and the class's field-parse table to INI::initFromINI when there is
// an INI to parse from, return it -- so only the registration block names it,
// by pushing this address beside the AsciiString "TaintSpecialPower".
//
// Retail allocates 0x220 bytes, which is sizeof(TaintSpecialPowerModuleData) with its
// vptr, and calls the constructor through 0x00021012.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class TaintSpecialPowerModuleData
{
public:
	TaintSpecialPowerModuleData();
	virtual ~TaintSpecialPowerModuleData();

private:
	unsigned char m_pad[0x21C];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char TaintSpecialPowerFieldParse;

class TaintSpecialPower
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@TaintSpecialPower@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *TaintSpecialPower::friend_newModuleData(INI *ini)
{
	TaintSpecialPowerModuleData *data = new TaintSpecialPowerModuleData;
	if (ini)
		ini->initFromINI(data, &TaintSpecialPowerFieldParse);
	return (ModuleData *)data;
}

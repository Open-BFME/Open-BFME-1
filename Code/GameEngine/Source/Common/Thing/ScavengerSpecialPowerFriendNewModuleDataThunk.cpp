// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: ScavengerSpecialPower::friend_newModuleData factory, retail 0x00120560,
// converted out of a machine byte dump.
//
// Every module's data factory is this same body -- allocate the module data,
// hand it and the class's field-parse table to INI::initFromINI when there is
// an INI to parse from, return it -- so only the registration block names it,
// by pushing this address beside the AsciiString "ScavengerSpecialPower".
//
// Retail allocates 0x214 bytes, which is sizeof(ScavengerSpecialPowerModuleData) with its
// vptr, and calls the constructor through 0x00019461.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class ScavengerSpecialPowerModuleData
{
public:
	ScavengerSpecialPowerModuleData();
	virtual ~ScavengerSpecialPowerModuleData();

private:
	unsigned char m_pad[0x210];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char ScavengerSpecialPowerFieldParse;

class ScavengerSpecialPower
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@ScavengerSpecialPower@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *ScavengerSpecialPower::friend_newModuleData(INI *ini)
{
	ScavengerSpecialPowerModuleData *data = new ScavengerSpecialPowerModuleData;
	if (ini)
		ini->initFromINI(data, &ScavengerSpecialPowerFieldParse);
	return (ModuleData *)data;
}

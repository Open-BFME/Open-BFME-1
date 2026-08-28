// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: DominateEnemySpecialPower::friend_newModuleData factory, retail 0x001221C0,
// converted out of a machine byte dump.
//
// Every module's data factory is this same body -- allocate the module data,
// hand it and the class's field-parse table to INI::initFromINI when there is
// an INI to parse from, return it -- so only the registration block names it,
// by pushing this address beside the AsciiString "DominateEnemySpecialPower".
//
// Retail allocates 0x260 bytes, which is sizeof(DominateEnemySpecialPowerModuleData) with its
// vptr, and calls the constructor through 0x00018985.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class DominateEnemySpecialPowerModuleData
{
public:
	DominateEnemySpecialPowerModuleData();
	virtual ~DominateEnemySpecialPowerModuleData();

private:
	unsigned char m_pad[0x25C];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char DominateEnemySpecialPowerFieldParse;

class DominateEnemySpecialPower
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@DominateEnemySpecialPower@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *DominateEnemySpecialPower::friend_newModuleData(INI *ini)
{
	DominateEnemySpecialPowerModuleData *data = new DominateEnemySpecialPowerModuleData;
	if (ini)
		ini->initFromINI(data, &DominateEnemySpecialPowerFieldParse);
	return (ModuleData *)data;
}

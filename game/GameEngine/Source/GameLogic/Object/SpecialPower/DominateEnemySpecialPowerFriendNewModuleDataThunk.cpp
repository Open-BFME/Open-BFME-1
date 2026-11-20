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

class MultiIniFieldParse;

// Retail's module-data factories reach INI through initFromINIMultiProc
// (0x00852130), which takes the class's buildFieldParse proc; the
// FieldParse-table overload this TU used to name lives at 0x008520A0.
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINIMultiProc(void *what,
		void (__cdecl *buildFieldParse)(MultiIniFieldParse &));
};

// Retail pushes VA 0x00413C23, the five-byte ILT thunk at RVA 0x00013C23,
// which jumps to the matched address-derived builder
// ?buildFieldParse@Rva0025ACC0@@SAXAAVWideMulti@@@Z (body 0x0025ACC0 in
// Common/WideBuildFieldParse.cpp); its WideMulti receiver is that row's
// spelling, so the proc is cast to the initFromINIMultiProc parameter type.
// Naming that defined, matched body (instead of an undefined alias) lets the
// reference link; the pushed operand is a relocation either way.
class WideMulti;
class Rva0025ACC0
{
public:
	static void buildFieldParse(WideMulti &);
};
typedef void (__cdecl *DominateEnemySpecialPowerBuildFieldParse)(MultiIniFieldParse &);

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
		ini->initFromINIMultiProc(data,
			(DominateEnemySpecialPowerBuildFieldParse)Rva0025ACC0::buildFieldParse);
	return (ModuleData *)data;
}

// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: SiegeDeployHordeSpecialPower::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class SiegeDeployHordeSpecialPowerModuleData
{
public:
	SiegeDeployHordeSpecialPowerModuleData();
	virtual ~SiegeDeployHordeSpecialPowerModuleData();

private:
	unsigned char m_pad[0x1d0];
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

// The proc retail passes is VA 0x0040DD8C, the ILT stub ?j_0000dd8c@@YAXXZ (jumps to 0x00265AF0).
extern void j_0000dd8c();

class SiegeDeployHordeSpecialPower
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@SiegeDeployHordeSpecialPower@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *SiegeDeployHordeSpecialPower::friend_newModuleData(INI *ini)
{
	SiegeDeployHordeSpecialPowerModuleData *data = new SiegeDeployHordeSpecialPowerModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, (void (__cdecl *)(MultiIniFieldParse &))&j_0000dd8c);
	return (ModuleData *)data;
}

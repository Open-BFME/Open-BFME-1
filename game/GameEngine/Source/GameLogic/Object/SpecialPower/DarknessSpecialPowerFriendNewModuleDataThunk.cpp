// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: DarknessSpecialPower::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class DarknessSpecialPowerModuleData
{
public:
	DarknessSpecialPowerModuleData();
	virtual ~DarknessSpecialPowerModuleData();

private:
	unsigned char m_pad[0x214];
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

// The proc retail passes is VA 0x00419934, the ILT stub ?j_00019934@@YAXXZ (jumps to 0x00259B50).
extern void j_00019934();

class DarknessSpecialPower
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@DarknessSpecialPower@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *DarknessSpecialPower::friend_newModuleData(INI *ini)
{
	DarknessSpecialPowerModuleData *data = new DarknessSpecialPowerModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, (void (__cdecl *)(MultiIniFieldParse &))&j_00019934);
	return (ModuleData *)data;
}

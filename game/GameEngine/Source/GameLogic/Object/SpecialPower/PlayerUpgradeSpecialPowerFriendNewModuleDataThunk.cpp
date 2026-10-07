// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: PlayerUpgradeSpecialPower::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class PlayerUpgradeSpecialPowerModuleData
{
public:
	PlayerUpgradeSpecialPowerModuleData();
	virtual ~PlayerUpgradeSpecialPowerModuleData();

private:
	unsigned char m_pad[0x218];
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

// The proc retail passes is VA 0x0044106A, the ILT stub ?j_0004106a@@YAXXZ (jumps to 0x002643F0).
extern void j_0004106a();

class PlayerUpgradeSpecialPower
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@PlayerUpgradeSpecialPower@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *PlayerUpgradeSpecialPower::friend_newModuleData(INI *ini)
{
	PlayerUpgradeSpecialPowerModuleData *data = new PlayerUpgradeSpecialPowerModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, (void (__cdecl *)(MultiIniFieldParse &))&j_0004106a);
	return (ModuleData *)data;
}

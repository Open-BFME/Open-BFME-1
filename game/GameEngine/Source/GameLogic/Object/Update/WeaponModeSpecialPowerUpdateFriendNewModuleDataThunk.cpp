// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: WeaponModeSpecialPowerUpdate::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class WeaponModeSpecialPowerUpdateModuleData
{
public:
	WeaponModeSpecialPowerUpdateModuleData();
	virtual ~WeaponModeSpecialPowerUpdateModuleData();

private:
	unsigned char m_pad[0x1dc];
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

// The proc operand is ILT 0x00038F87 -> 0x002B2A80, the matched
// ?buildFieldParse@Rva002B2A80@@SAXAAVWideMulti@@@Z.
void j_00038f87();

class WeaponModeSpecialPowerUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@WeaponModeSpecialPowerUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *WeaponModeSpecialPowerUpdate::friend_newModuleData(INI *ini)
{
	WeaponModeSpecialPowerUpdateModuleData *data = new WeaponModeSpecialPowerUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, (void (__cdecl *)(MultiIniFieldParse &))j_00038f87);
	return (ModuleData *)data;
}

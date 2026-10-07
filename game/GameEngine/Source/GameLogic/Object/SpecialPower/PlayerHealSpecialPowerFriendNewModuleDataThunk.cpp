// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: PlayerHealSpecialPower::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class MultiIniFieldParse;

class PlayerHealSpecialPowerModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &p);	// 0x002639A0 via ILT 0x0003023D
	PlayerHealSpecialPowerModuleData();
	virtual ~PlayerHealSpecialPowerModuleData();

private:
	unsigned char m_pad[0x234];
};

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

class PlayerHealSpecialPower
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@PlayerHealSpecialPower@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *PlayerHealSpecialPower::friend_newModuleData(INI *ini)
{
	PlayerHealSpecialPowerModuleData *data = new PlayerHealSpecialPowerModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, &PlayerHealSpecialPowerModuleData::buildFieldParse);
	return (ModuleData *)data;
}

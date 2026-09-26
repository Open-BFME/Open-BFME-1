// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: RadarUpgrade::friend_newModuleData
// Retail: new(0x74); sub-ctor at +8; outer vtbl; byte +0x70 = 0.

class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class UpgradeModuleDataSub
{
public:
	UpgradeModuleDataSub();

private:
	char opaque[0x68];
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/RadarUpgrade.h
class RadarUpgradeModuleData
{
public:
	RadarUpgradeModuleData()
	{
		m_flag = 0;
	}
	virtual void dummy();

private:
	int m_pad;
	char m_sub_space[0x68];
	unsigned char m_flag;
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

extern "C" void __cdecl RadarUpgradeFieldParse(MultiIniFieldParse &parse);

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/RadarUpgrade.h
class RadarUpgrade
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@RadarUpgrade@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *RadarUpgrade::friend_newModuleData(INI *ini)
{
	RadarUpgradeModuleData *data =
		(RadarUpgradeModuleData *)operator new(0x74);
	if (data)
	{
		UpgradeModuleDataSub *sub =
			(UpgradeModuleDataSub *)((char *)data + 8);
		sub->UpgradeModuleDataSub::UpgradeModuleDataSub();
		data->RadarUpgradeModuleData::RadarUpgradeModuleData();
	}
	else
		data = 0;
	if (ini)
		ini->initFromINIMultiProc(data, &RadarUpgradeFieldParse);
	return (ModuleData *)data;
}

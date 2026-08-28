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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/RadarUpgrade.h
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char RadarUpgradeFieldParse;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/RadarUpgrade.h
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
		ini->initFromINI(data, &RadarUpgradeFieldParse);
	return (ModuleData *)data;
}

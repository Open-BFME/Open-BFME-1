// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: ArmorUpgrade::friend_newModuleData
// Retail: new(0x78); sub at +8; vtbl; bytes +0x70/+0x71=0; dword +0x74=3.

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

class ArmorUpgradeModuleData
{
public:
	ArmorUpgradeModuleData()
	{
		m_70 = 0;
		m_71 = 0;
		m_74 = 3;
	}
	virtual void dummy();

private:
	int m_pad;
	char m_sub_space[0x68];
	unsigned char m_70;
	unsigned char m_71;
	unsigned char m_pad72;
	unsigned char m_pad73;
	unsigned int m_74;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char ArmorUpgradeFieldParse;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ArmorUpgrade.h
class ArmorUpgrade
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@ArmorUpgrade@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *ArmorUpgrade::friend_newModuleData(INI *ini)
{
	ArmorUpgradeModuleData *data =
		(ArmorUpgradeModuleData *)operator new(0x78);
	if (data)
	{
		UpgradeModuleDataSub *sub =
			(UpgradeModuleDataSub *)((char *)data + 8);
		sub->UpgradeModuleDataSub::UpgradeModuleDataSub();
		data->ArmorUpgradeModuleData::ArmorUpgradeModuleData();
	}
	else
		data = 0;
	if (ini)
		ini->initFromINI(data, &ArmorUpgradeFieldParse);
	return (ModuleData *)data;
}

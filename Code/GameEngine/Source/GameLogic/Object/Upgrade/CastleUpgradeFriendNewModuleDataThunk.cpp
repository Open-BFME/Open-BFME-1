// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: CastleUpgrade::friend_newModuleData
// Retail: new(0x74); sub-ctor at +8; outer vtbl; dword +0x70 = 0.

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

class CastleUpgradeModuleData
{
public:
	CastleUpgradeModuleData()
	{
		m_extra = 0;
	}
	virtual void dummy();

private:
	int m_pad;
	char m_sub_space[0x68];
	unsigned int m_extra;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char CastleUpgradeFieldParse;

class CastleUpgrade
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@CastleUpgrade@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *CastleUpgrade::friend_newModuleData(INI *ini)
{
	CastleUpgradeModuleData *data =
		(CastleUpgradeModuleData *)operator new(0x74);
	if (data)
	{
		UpgradeModuleDataSub *sub =
			(UpgradeModuleDataSub *)((char *)data + 8);
		sub->UpgradeModuleDataSub::UpgradeModuleDataSub();
		data->CastleUpgradeModuleData::CastleUpgradeModuleData();
	}
	else
		data = 0;
	if (ini)
		ini->initFromINI(data, &CastleUpgradeFieldParse);
	return (ModuleData *)data;
}

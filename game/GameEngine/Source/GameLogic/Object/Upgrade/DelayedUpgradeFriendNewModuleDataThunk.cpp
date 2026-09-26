// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: DelayedUpgrade::friend_newModuleData
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

class DelayedUpgradeModuleData
{
public:
	DelayedUpgradeModuleData()
	{
		m_extra = 0;
	}
	virtual void dummy();

private:
	int m_pad;
	char m_sub_space[0x68];
	unsigned int m_extra;
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

extern "C" void __cdecl DelayedUpgradeFieldParse(MultiIniFieldParse &parse);

class DelayedUpgrade
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@DelayedUpgrade@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *DelayedUpgrade::friend_newModuleData(INI *ini)
{
	DelayedUpgradeModuleData *data =
		(DelayedUpgradeModuleData *)operator new(0x74);
	if (data)
	{
		UpgradeModuleDataSub *sub =
			(UpgradeModuleDataSub *)((char *)data + 8);
		sub->UpgradeModuleDataSub::UpgradeModuleDataSub();
		data->DelayedUpgradeModuleData::DelayedUpgradeModuleData();
	}
	else
		data = 0;
	if (ini)
		ini->initFromINIMultiProc(data, &DelayedUpgradeFieldParse);
	return (ModuleData *)data;
}

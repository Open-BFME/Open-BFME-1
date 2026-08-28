// cl: /DNDEBUG /MD /GX- /O2 /Ob2
// readable body of ??0MaxHealthUpgradeModuleData@@QAE@XZ: Code/GameEngine/Source/GameLogic/Object/Upgrade/MaxHealthUpgrade.cpp

// Open-BFME5: MaxHealthUpgradeModuleData ctor
// Retail: sub at +8, zero +0x70/+0x74, then outer vtbl.

class UpgradeModuleDataSub
{
public:
	UpgradeModuleDataSub();

private:
	char opaque[0x68];
};

class __declspec(novtable) MaxHealthUpgradeModuleData
{
public:
	MaxHealthUpgradeModuleData();
	virtual void dummy();

private:
	int m_pad;
	char m_sub_space[0x68];
	unsigned int m_70;
	unsigned int m_74;
};

class MaxHealthUpgradeModuleDataVtbl
{
public:
	MaxHealthUpgradeModuleDataVtbl() {}
	virtual void dummy();

private:
	int m_pad;
	char m_sub_space[0x68];
	unsigned int m_70;
	unsigned int m_74;
};

// ??0MaxHealthUpgradeModuleData@@QAE@XZ
MaxHealthUpgradeModuleData::MaxHealthUpgradeModuleData()
{
	UpgradeModuleDataSub *sub =
		(UpgradeModuleDataSub *)((char *)this + 8);
	sub->UpgradeModuleDataSub::UpgradeModuleDataSub();
	m_70 = 0;
	m_74 = 0;
	MaxHealthUpgradeModuleDataVtbl *v =
		(MaxHealthUpgradeModuleDataVtbl *)this;
	v->MaxHealthUpgradeModuleDataVtbl::MaxHealthUpgradeModuleDataVtbl();
}

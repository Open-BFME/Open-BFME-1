// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: UnpauseSpecialPowerUpgradeModuleData ctor
// Retail: sub at +8, dword +0x70=0, byte +0x74=0, outer vtbl.

class UpgradeModuleDataSub
{
public:
	UpgradeModuleDataSub();

private:
	char opaque[0x68];
};

class __declspec(novtable) UnpauseSpecialPowerUpgradeModuleData
{
public:
	UnpauseSpecialPowerUpgradeModuleData();
	virtual void dummy();

private:
	int m_pad;
	char m_sub_space[0x68];
	unsigned int m_specialPower;
	unsigned char m_obeyRechargeOnTrigger;
};

class UnpauseSpecialPowerUpgradeModuleDataVtbl
{
public:
	UnpauseSpecialPowerUpgradeModuleDataVtbl() {}
	virtual void dummy();

private:
	int m_pad;
	char m_sub_space[0x68];
	unsigned int m_specialPower;
	unsigned char m_obeyRechargeOnTrigger;
};

// ??0UnpauseSpecialPowerUpgradeModuleData@@QAE@XZ
UnpauseSpecialPowerUpgradeModuleData::UnpauseSpecialPowerUpgradeModuleData()
{
	UpgradeModuleDataSub *sub =
		(UpgradeModuleDataSub *)((char *)this + 8);
	sub->UpgradeModuleDataSub::UpgradeModuleDataSub();
	m_specialPower = 0;
	m_obeyRechargeOnTrigger = 0;
	UnpauseSpecialPowerUpgradeModuleDataVtbl *v =
		(UnpauseSpecialPowerUpgradeModuleDataVtbl *)this;
	v->UnpauseSpecialPowerUpgradeModuleDataVtbl::UnpauseSpecialPowerUpgradeModuleDataVtbl();
}

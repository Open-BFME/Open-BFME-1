// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: ExperienceScalarUpgradeModuleData ctor
// Retail: sub at +8, outer vtbl, dword +0x70 = 0.

class UpgradeModuleDataSub
{
public:
	UpgradeModuleDataSub();

private:
	char opaque[0x68];
};

class __declspec(novtable) ExperienceScalarUpgradeModuleData
{
public:
	ExperienceScalarUpgradeModuleData();
	virtual void dummy();

private:
	int m_pad;
	char m_sub_space[0x68];
	unsigned int m_scalar;
};

class ExperienceScalarUpgradeModuleDataVtbl
{
public:
	ExperienceScalarUpgradeModuleDataVtbl() {}
	virtual void dummy();

private:
	int m_pad;
	char m_sub_space[0x68];
	unsigned int m_scalar;
};

// ??0ExperienceScalarUpgradeModuleData@@QAE@XZ
ExperienceScalarUpgradeModuleData::ExperienceScalarUpgradeModuleData()
{
	UpgradeModuleDataSub *sub =
		(UpgradeModuleDataSub *)((char *)this + 8);
	sub->UpgradeModuleDataSub::UpgradeModuleDataSub();
	ExperienceScalarUpgradeModuleDataVtbl *v =
		(ExperienceScalarUpgradeModuleDataVtbl *)this;
	v->ExperienceScalarUpgradeModuleDataVtbl::ExperienceScalarUpgradeModuleDataVtbl();
	m_scalar = 0;
}

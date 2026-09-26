// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: ExperienceScalarUpgradeModuleData dtor. SEH member@+0x8 pin 0x1B97D.

class UnpauseSpecialPowerUpgradeModuleDataMember
{
public:
	~UnpauseSpecialPowerUpgradeModuleDataMember();
};

class ExperienceScalarUpgradeModuleDataBase
{
public:
	virtual ~ExperienceScalarUpgradeModuleDataBase() {}
private:
	unsigned char m_pad[0x4];
};

class __declspec(novtable) ExperienceScalarUpgradeModuleData : public ExperienceScalarUpgradeModuleDataBase
{
public:
	virtual ~ExperienceScalarUpgradeModuleData();
private:
	UnpauseSpecialPowerUpgradeModuleDataMember m_member;
};

// ??1ExperienceScalarUpgradeModuleData@@UAE@XZ
ExperienceScalarUpgradeModuleData::~ExperienceScalarUpgradeModuleData()
{
}

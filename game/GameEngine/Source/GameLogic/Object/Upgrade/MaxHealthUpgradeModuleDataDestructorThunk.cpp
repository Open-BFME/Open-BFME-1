// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: MaxHealthUpgradeModuleData dtor. SEH member@+0x8 pin 0x1B97D.

class UnpauseSpecialPowerUpgradeModuleDataMember
{
public:
	~UnpauseSpecialPowerUpgradeModuleDataMember();
};

class MaxHealthUpgradeModuleDataBase
{
public:
	virtual ~MaxHealthUpgradeModuleDataBase() {}
private:
	unsigned char m_pad[0x4];
};

class __declspec(novtable) MaxHealthUpgradeModuleData : public MaxHealthUpgradeModuleDataBase
{
public:
	virtual ~MaxHealthUpgradeModuleData();
private:
	UnpauseSpecialPowerUpgradeModuleDataMember m_member;
};

// ??1MaxHealthUpgradeModuleData@@UAE@XZ
MaxHealthUpgradeModuleData::~MaxHealthUpgradeModuleData()
{
}

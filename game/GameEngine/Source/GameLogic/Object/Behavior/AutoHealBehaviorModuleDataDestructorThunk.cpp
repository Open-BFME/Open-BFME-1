// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: AutoHealBehaviorModuleData dtor. SEH member@+0x8 pin 0x1B97D.

class UnpauseSpecialPowerUpgradeModuleDataMember
{
public:
	~UnpauseSpecialPowerUpgradeModuleDataMember();
};

class AutoHealBehaviorModuleDataBase
{
public:
	virtual ~AutoHealBehaviorModuleDataBase() {}
private:
	unsigned char m_pad[0x4];
};

class __declspec(novtable) AutoHealBehaviorModuleData : public AutoHealBehaviorModuleDataBase
{
public:
	virtual ~AutoHealBehaviorModuleData();
private:
	UnpauseSpecialPowerUpgradeModuleDataMember m_member;
};

// ??1AutoHealBehaviorModuleData@@UAE@XZ
AutoHealBehaviorModuleData::~AutoHealBehaviorModuleData()
{
}

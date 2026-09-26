// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: ModelConditionUpgradeModuleData dtor. SEH member@+0x8 pin 0x1B97D.

class UnpauseSpecialPowerUpgradeModuleDataMember
{
public:
	~UnpauseSpecialPowerUpgradeModuleDataMember();
};

class ModelConditionUpgradeModuleDataBase
{
public:
	virtual ~ModelConditionUpgradeModuleDataBase() {}
private:
	unsigned char m_pad[0x4];
};

class __declspec(novtable) ModelConditionUpgradeModuleData : public ModelConditionUpgradeModuleDataBase
{
public:
	virtual ~ModelConditionUpgradeModuleData();
private:
	UnpauseSpecialPowerUpgradeModuleDataMember m_member;
};

// ??1ModelConditionUpgradeModuleData@@UAE@XZ
ModelConditionUpgradeModuleData::~ModelConditionUpgradeModuleData()
{
}

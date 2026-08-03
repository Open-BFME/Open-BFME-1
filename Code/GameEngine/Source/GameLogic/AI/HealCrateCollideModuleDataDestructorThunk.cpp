// cl: /DNDEBUG /MD /EHsc

class CrateCollideModuleData
{
public:
    virtual ~CrateCollideModuleData() {}

private:
    unsigned char m_base[0x3c];
};

class UpgradeList
{
public:
    ~UpgradeList();
};

class __declspec(novtable) HealCrateCollideModuleData : public CrateCollideModuleData
{
public:
    virtual ~HealCrateCollideModuleData();

private:
    unsigned int m_healAmount;
    UpgradeList m_upgradeBoost;
};

// ??1HealCrateCollideModuleData@@UAE@XZ
HealCrateCollideModuleData::~HealCrateCollideModuleData()
{
}

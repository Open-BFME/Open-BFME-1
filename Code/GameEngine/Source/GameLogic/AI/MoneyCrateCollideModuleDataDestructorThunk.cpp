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

class __declspec(novtable) MoneyCrateCollideModuleData : public CrateCollideModuleData
{
public:
    virtual ~MoneyCrateCollideModuleData();

private:
    unsigned int m_moneyProvided;
    UpgradeList m_upgradeBoost;
};

// ??1MoneyCrateCollideModuleData@@UAE@XZ
MoneyCrateCollideModuleData::~MoneyCrateCollideModuleData()
{
}

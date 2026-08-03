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

class __declspec(novtable) ShroudCrateCollideModuleData : public CrateCollideModuleData
{
public:
    virtual ~ShroudCrateCollideModuleData();

private:
    unsigned int m_shroudAmount;
    UpgradeList m_upgradeBoost;
};

// ??1ShroudCrateCollideModuleData@@UAE@XZ
ShroudCrateCollideModuleData::~ShroudCrateCollideModuleData()
{
}

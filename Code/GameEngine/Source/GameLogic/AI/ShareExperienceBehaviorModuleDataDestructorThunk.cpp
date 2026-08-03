// cl: /DNDEBUG /MD /EHsc

class BehaviorModuleData
{
public:
    virtual ~BehaviorModuleData() {}

private:
    unsigned char m_base[0x10];
};

class UpgradeVector
{
public:
    ~UpgradeVector();
};

class __declspec(novtable) ShareExperienceBehaviorModuleData : public BehaviorModuleData
{
public:
    virtual ~ShareExperienceBehaviorModuleData();

private:
    UpgradeVector m_upgrades;
};

// ??1ShareExperienceBehaviorModuleData@@UAE@XZ
ShareExperienceBehaviorModuleData::~ShareExperienceBehaviorModuleData()
{
}

// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift ModuleData dtor __emit thunk to clean C++.
// Retail destroys the member subobject at this+8 under an SEH frame, then
// runs the inlined base dtor (base vtable store) on the normal and unwind
// paths. The derived class emits no vtable store of its own.

class UnpauseSpecialPowerUpgradeModuleDataMember
{
public:
    ~UnpauseSpecialPowerUpgradeModuleDataMember();
};

class UnpauseSpecialPowerUpgradeModuleDataBase
{
public:
    virtual ~UnpauseSpecialPowerUpgradeModuleDataBase() {}

private:
    unsigned int m_04;
};

class __declspec(novtable) UnpauseSpecialPowerUpgradeModuleData : public UnpauseSpecialPowerUpgradeModuleDataBase
{
public:
    virtual ~UnpauseSpecialPowerUpgradeModuleData();

private:
    UnpauseSpecialPowerUpgradeModuleDataMember m_08;
};

// ??1UnpauseSpecialPowerUpgradeModuleData@@UAE@XZ
UnpauseSpecialPowerUpgradeModuleData::~UnpauseSpecialPowerUpgradeModuleData()
{
}

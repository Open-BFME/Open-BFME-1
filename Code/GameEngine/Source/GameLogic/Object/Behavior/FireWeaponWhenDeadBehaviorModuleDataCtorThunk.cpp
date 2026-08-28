// cl: /DNDEBUG /MD /EHsc
// ModuleFactory's verified friend allocator fixes the 0xB4-byte BFME layout.
// EA's header and the clean destructor independently locate the mux members.

class FWWDead_UpgradeMuxData
{
public:
    FWWDead_UpgradeMuxData();
    ~FWWDead_UpgradeMuxData();

private:
    unsigned char m_storage[0x68];
};

class FWWDead_DieMuxData
{
public:
    FWWDead_DieMuxData();

private:
    unsigned char m_storage[0x2c];
};

class FWWDead_ModuleDataBase
{
public:
    virtual ~FWWDead_ModuleDataBase() {}

private:
    unsigned int m_field04;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/FireWeaponWhenDeadBehavior.h
class FireWeaponWhenDeadBehaviorModuleData : public FWWDead_ModuleDataBase
{
public:
    FireWeaponWhenDeadBehaviorModuleData();
    virtual ~FireWeaponWhenDeadBehaviorModuleData();

private:
    FWWDead_UpgradeMuxData m_upgradeMuxData;
    bool m_field70;
    bool m_field71;
    unsigned int m_field74;
    unsigned int m_field78;
    unsigned int m_field7c;
    unsigned int m_field80;
    FWWDead_DieMuxData m_dieMuxData;
    void *m_deathWeapon;
};

// ??0FireWeaponWhenDeadBehaviorModuleData@@QAE@XZ
FireWeaponWhenDeadBehaviorModuleData::FireWeaponWhenDeadBehaviorModuleData()
{
    m_field70 = false;
    m_field71 = false;
    m_field74 = 0;
    m_deathWeapon = 0;
    m_field78 = 0;
    m_field7c = 0;
    m_field80 = 0;
}

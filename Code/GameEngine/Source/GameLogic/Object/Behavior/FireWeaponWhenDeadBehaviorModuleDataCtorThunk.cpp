// cl: /DNDEBUG /MD /EHsc
// ModuleFactory's verified friend allocator fixes the 0xB4-byte BFME layout.
// EA's header and the clean destructor independently locate the mux members.
//
// m_initiallyActive is retail's own name for +0x70: its INI field table at
// 0x00C8B468 puts the StartsActive key there, and upstream's parse table for
// this same class writes that key to m_initiallyActive with parseBool -- which
// is the bool declared here, zeroed by this constructor exactly as upstream's
// zeroes m_initiallyActive. m_deathWeapon at +0xB0 was already the table's
// name. The two remaining keys are BFME's own (ActiveDuringConstruction at
// +0x71, WeaponOffset at +0x78); Zero Hour has no member for either, so those
// stay offset-named.

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
    bool m_initiallyActive;
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
    m_initiallyActive = false;
    m_field71 = false;
    m_field74 = 0;
    m_deathWeapon = 0;
    m_field78 = 0;
    m_field7c = 0;
    m_field80 = 0;
}

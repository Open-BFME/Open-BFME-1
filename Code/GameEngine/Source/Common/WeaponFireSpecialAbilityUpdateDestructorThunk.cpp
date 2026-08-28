// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift WeaponFireSpecialAbilityUpdate dtor __emit thunk to clean
// C++. Four entry vtables (+0x00/+0x0C/+0x10/+0x20), virtual-delete of the
// heap pointer at +0xE8 with clear-to-zero, out-of-line SpecialAbilityUpdate
// base dtor.

class WFS_RootBase
{
public:
    virtual ~WFS_RootBase();

private:
    unsigned char m_pad[8];
};

class WFS_Iface1 { public: virtual void slot(); };
class WFS_Iface2 { public: virtual void slot(); private: unsigned char m_pad[0xC]; };
class WFS_Iface3 { public: virtual void slot(); };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialAbilityUpdate.h
class SpecialAbilityUpdate : public WFS_RootBase, public WFS_Iface1, public WFS_Iface2, public WFS_Iface3
{
public:
    virtual ~SpecialAbilityUpdate();

private:
    unsigned char m_pad[0xC4];
};

class WFS_HeapObj
{
public:
    virtual ~WFS_HeapObj();
};

class WeaponFireSpecialAbilityUpdate : public SpecialAbilityUpdate
{
public:
    virtual ~WeaponFireSpecialAbilityUpdate();

private:
    WFS_HeapObj *m_ptr;
};

// ??1WeaponFireSpecialAbilityUpdate@@UAE@XZ
WeaponFireSpecialAbilityUpdate::~WeaponFireSpecialAbilityUpdate()
{
    delete m_ptr;
    m_ptr = 0;
}

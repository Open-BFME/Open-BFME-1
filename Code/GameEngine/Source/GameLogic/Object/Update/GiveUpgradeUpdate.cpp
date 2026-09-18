// cl: /DNDEBUG /MD /EHs-
// Open-BFME5: lift GiveUpgradeUpdate ctor __emit thunk to clean C++.
// Retail shape: out-of-line base ctor call with both args, zero the three
// fields at +0xE8/+0xE9/+0xEC, then the four most-derived vtable stores at
// +0x00/+0x0C/+0x10/+0x20. The +0x20 subobject is a polymorphic member.
// /EHs- because retail has no unwind frame.

class Thing;
class ModuleData;

class GiveUpgradeUpdateGrandBase
{
public:
    GiveUpgradeUpdateGrandBase(Thing *, const ModuleData *);
    virtual ~GiveUpgradeUpdateGrandBase();

private:
    unsigned char m_pad[8];
};

class GiveUpgradeUpdateIface1
{
public:
    virtual ~GiveUpgradeUpdateIface1();
};

class GiveUpgradeUpdateIface2
{
public:
    virtual ~GiveUpgradeUpdateIface2();

private:
    unsigned char m_pad[0xC];
};

class GiveUpgradeUpdateIface3
{
public:
    GiveUpgradeUpdateIface3() {}
    virtual ~GiveUpgradeUpdateIface3();
};

class SpecialAbilityUpdate : public GiveUpgradeUpdateGrandBase, public GiveUpgradeUpdateIface1, public GiveUpgradeUpdateIface2, public GiveUpgradeUpdateIface3
{
public:
    SpecialAbilityUpdate(Thing *, const ModuleData *);
    virtual ~SpecialAbilityUpdate();

private:
    unsigned char m_pad[0xC4];
};

class GiveUpgradeUpdate : public SpecialAbilityUpdate
{
public:
    GiveUpgradeUpdate(Thing *, const ModuleData *);

protected:
    __declspec(noinline) virtual ~GiveUpgradeUpdate();

private:
    bool m_e8;
    bool m_e9;
    unsigned char m_pad2[2];
    unsigned int m_ec;
};

// ??0GiveUpgradeUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
GiveUpgradeUpdate::GiveUpgradeUpdate(Thing *t, const ModuleData *m)
    : SpecialAbilityUpdate(t, m), m_e8(false), m_e9(false), m_ec(0)
{
}

GiveUpgradeUpdate::~GiveUpgradeUpdate()
{
}

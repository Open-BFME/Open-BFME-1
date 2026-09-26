// cl: /DNDEBUG /MD /EHsc
// ModuleFactory reaches this constructor through ILT 0x000212B5. The
// registration string and 0x24-byte allocation identify the retail-only
// DelayedWeaponSetUpgradeUpdate class.
//
// Two rounds of vftable stores: the UpdateModule base is inline, so its own
// +0x0C/+0x10 stores and its three member inits come first, then the fourth
// interface base stores +0x20, then the most-derived class overwrites all
// four slots.

class Thing;
class ModuleData;
class Object;

class DWSU_DeepBase
{
public:
    DWSU_DeepBase(Thing *, const ModuleData *);
    virtual ~DWSU_DeepBase();

protected:
    const ModuleData *m_moduleData;
    Object *m_object;
};

class DWSU_Iface1 { public: virtual void slot(); };
class DWSU_Iface2 { public: virtual void slot(); };

class DWSU_UpdateModule : public DWSU_DeepBase, public DWSU_Iface1, public DWSU_Iface2
{
public:
    DWSU_UpdateModule(Thing *thing, const ModuleData *moduleData)
        : DWSU_DeepBase(thing, moduleData), m_f14(0), m_f18(-1), m_f1c(-1) {}

private:
    unsigned int m_f14;
    int m_f18;
    int m_f1c;
};

class DWSU_Iface3 { public: virtual void slot(); };

class DelayedWeaponSetUpgradeUpdate : public DWSU_UpdateModule, public DWSU_Iface3
{
public:
    DelayedWeaponSetUpgradeUpdate(Thing *, const ModuleData *);
};

// ??0DelayedWeaponSetUpgradeUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
DelayedWeaponSetUpgradeUpdate::DelayedWeaponSetUpgradeUpdate(
    Thing *thing, const ModuleData *moduleData)
    : DWSU_UpdateModule(thing, moduleData)
{
}

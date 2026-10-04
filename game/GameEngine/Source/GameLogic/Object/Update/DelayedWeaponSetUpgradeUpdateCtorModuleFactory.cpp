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

// The base subobject here is retail's ObjectModule: this constructor calls
// the shared ObjectModule ctor ILT 0x000170E4 (which routes to the matched
// body at 0x00113C60 in game/GameEngine/Source/Common/Thing/
// ObjectModuleConstructor.cpp) and the class carries ObjectModule's
// m_moduleData/m_object pair. Naming it DWSU_DeepBase left both the ctor and
// the virtual destructor undefined at link; the real names are the ones
// that resolve.
//
// LINK RESIDUAL (not fixable from this TU): the link keeps game/GameEngine/
// Source/Common/Thing/Module.cpp's `??0ObjectModule@@` body (an ordinary
// .text definition earlier in link order, judged not retail's; the ledger
// owner of the name is ObjectModuleConstructor.cpp's matched 131-byte body at
// 0x00113C60). link_check therefore still reports
//   selected  ??0ObjectModule@@QAE@PAVThing@@PBVModuleData@@@Z
// for this file. Nothing here can change that; Module.cpp must stop defining
// the symbol exclusively.
//
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ObjectModule
{
public:
    ObjectModule(Thing *, const ModuleData *);
    virtual ~ObjectModule();

protected:
    const ModuleData *m_moduleData;
    Object *m_object;
};

// The three interface vtables this object emits are retail's abstract
// interface tables: at 0x0109C9D0 and 0x0109CBA0 every slot is the CRT
// __purecall (0x00C8C500), and the fourth sub-table at 0x010BD3E8 opens
// the same way. Declaring the slot pure virtual is what makes the emitted
// table reference __purecall instead of an undefined body.
class DWSU_Iface1 { public: virtual void slot() = 0; };
class DWSU_Iface2 { public: virtual void slot() = 0; };

class DWSU_UpdateModule : public ObjectModule, public DWSU_Iface1, public DWSU_Iface2
{
public:
    DWSU_UpdateModule(Thing *thing, const ModuleData *moduleData)
        : ObjectModule(thing, moduleData), m_f14(0), m_f18(-1), m_f1c(-1) {}

private:
    unsigned int m_f14;
    int m_f18;
    int m_f1c;
};

class DWSU_Iface3 { public: virtual void slot() = 0; };

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

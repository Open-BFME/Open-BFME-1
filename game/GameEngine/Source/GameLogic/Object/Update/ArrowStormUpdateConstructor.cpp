// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Retail 0x002576E0 (207 B, extent ends at the `ret 8`, not the 0x207B the
// lift claimed).  This installs vtables 0x010B37C0/0x010B36F8/0x010B36E8/
// 0x010B36BC -- the same four the MATCHED destructor 0x00257940 tears down --
// then runs the base ctor through ILT 0x00013462 -> 0x002A6360, default
// constructs a 12-byte _STL::list node at +0xE8, clears it, and zeroes four
// trailing PODs.  ModuleData identity comes from the factory
// ?friend_newModuleInstance@ArrowStormUpdate (0x00257C70 wrapper/0x002576E0
// ctor pair share vtable 0x00CB37C0 with the landed scalar wrapper).
// Layout source: ArrowStormUpdateDestructors.cpp (matched dtor, same TU family).

#include <list>

class Thing;
class ModuleData;

class ArrowStormUpdateRootBase
{
public:
    virtual ~ArrowStormUpdateRootBase();

private:
    unsigned char m_pad[8];
};

class ArrowStormUpdateBaseInterface1 { public: virtual void slot(); };
class ArrowStormUpdateBaseInterface2 { public: virtual void slot(); private: unsigned char m_pad[0xC]; };
class ArrowStormUpdateBaseInterface3 { public: virtual void slot(); };

class ArrowStormUpdateObjectModule : public ArrowStormUpdateRootBase
{
};

class ArrowStormUpdateBehaviorModule : public ArrowStormUpdateObjectModule,
    public ArrowStormUpdateBaseInterface1
{
public:
    virtual ~ArrowStormUpdateBehaviorModule() {}
};

class ArrowStormUpdateUpdateModule : public ArrowStormUpdateBehaviorModule,
    public ArrowStormUpdateBaseInterface2,
    public ArrowStormUpdateBaseInterface3
{
public:
    virtual ~ArrowStormUpdateUpdateModule() {}
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialAbilityUpdate.h
class SpecialAbilityUpdate : public ArrowStormUpdateUpdateModule
{
public:
    SpecialAbilityUpdate(Thing *, const ModuleData *);
    virtual ~SpecialAbilityUpdate();

private:
    unsigned char m_pad[0xC4];
};

// Member names are address-derived: the retail ctor zeroes +0xEC, +0xF0 and
// +0xF4 as dwords and +0xF8 as a byte, and the evidence carries no semantic
// name for any of them.
class ArrowStormUpdate : public SpecialAbilityUpdate
{
public:
    ArrowStormUpdate(Thing *, const ModuleData *);
protected:
    virtual ~ArrowStormUpdate();

private:
    _STL::list<int> m_specialObjectIDList;
    unsigned int m_dw0xEC;
    unsigned int m_dw0xF0;
    unsigned int m_dw0xF4;
    unsigned char m_b0xF8;
};

// ??0ArrowStormUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
ArrowStormUpdate::ArrowStormUpdate(Thing *thing, const ModuleData *data)
    : SpecialAbilityUpdate(thing, data)
{
    m_specialObjectIDList.clear();
    m_dw0xEC = 0;
    m_dw0xF0 = 0;
    m_dw0xF4 = 0;
    m_b0xF8 = 0;
}

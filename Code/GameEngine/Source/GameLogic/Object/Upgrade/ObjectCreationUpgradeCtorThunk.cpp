// cl: /DNDEBUG /MD /EHs-
// Open-BFME5: lift ObjectCreationUpgrade ctor __emit thunk to clean C++.
// Retail: grandbase ctor call at +0, then the middle base at +8 (args ctor
// call, interface vtable pairs at +0x14/+0x18, middle finals and fields 0,
// -1, -1), then this class's fields (+0x28, byte +0x2C) and the four
// most-derived vtable stores (+0x00, +0x14, +0x18, +0x08).

class Thing;
class ModuleData;

class OCU_GrandBase
{
public:
    OCU_GrandBase();
    virtual ~OCU_GrandBase();

private:
    unsigned int m_04;
};

class OCU_MidGrand
{
public:
    OCU_MidGrand(Thing *, const ModuleData *);
    virtual ~OCU_MidGrand();

private:
    unsigned int m_04;
    unsigned char m_pad[4];
};

class OCU_Iface1
{
public:
    virtual ~OCU_Iface1();
};

class OCU_Iface2
{
public:
    virtual ~OCU_Iface2();
};

class OCU_MiddleBase : public OCU_MidGrand, public OCU_Iface1, public OCU_Iface2
{
public:
    OCU_MiddleBase(Thing *t, const ModuleData *m)
        : OCU_MidGrand(t, m), m_1C(0), m_20(-1), m_24(-1) {}
    virtual ~OCU_MiddleBase();

private:
    unsigned int m_1C;
    int m_20;
    int m_24;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ObjectCreationUpgrade.h
class ObjectCreationUpgrade : public OCU_GrandBase, public OCU_MiddleBase
{
public:
    ObjectCreationUpgrade(Thing *, const ModuleData *);

private:
    unsigned int m_28;
    bool m_2C;
};

// ??0ObjectCreationUpgrade@@QAE@PAVThing@@PBVModuleData@@@Z
ObjectCreationUpgrade::ObjectCreationUpgrade(Thing *t, const ModuleData *m)
    : OCU_MiddleBase(t, m), m_28(0), m_2C(false)
{
}

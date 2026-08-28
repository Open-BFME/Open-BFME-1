// cl: /DNDEBUG /MD /EHs-
// Open-BFME5: lift TunnelContain ctor __emit thunk to clean C++. Retail:
// out-of-line base ctor call, nine most-derived vtable stores (+0x00/+0x0C/
// +0x10/+0x20/+0x24/+0x28/+0x2C/+0x30/+0x34), then byte at +0xD4 = 1 and
// byte at +0xD5 = 0. Interfaces nested in the base; /EHs- because retail
// has no unwind frame.

class Thing;
class ModuleData;

class TC_GrandBase
{
public:
    TC_GrandBase(Thing *, const ModuleData *);
    virtual ~TC_GrandBase();

private:
    unsigned char m_pad[8];
};

class TC_Iface1 { public: virtual ~TC_Iface1(); };
class TC_Iface2 { public: virtual ~TC_Iface2(); private: unsigned char m_pad[0xC]; };
class TC_Iface3 { public: virtual ~TC_Iface3(); };
class TC_Iface4 { public: virtual ~TC_Iface4(); };
class TC_Iface5 { public: virtual ~TC_Iface5(); };
class TC_Iface6 { public: virtual ~TC_Iface6(); };
class TC_Iface7 { public: virtual ~TC_Iface7(); };
class TC_Iface8 { public: virtual ~TC_Iface8(); };

class TC_Base : public TC_GrandBase,
                public TC_Iface1,
                public TC_Iface2,
                public TC_Iface3,
                public TC_Iface4,
                public TC_Iface5,
                public TC_Iface6,
                public TC_Iface7,
                public TC_Iface8
{
public:
    TC_Base(Thing *, const ModuleData *);
    virtual ~TC_Base();

private:
    unsigned char m_pad[0x9C];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/TunnelContain.h
class TunnelContain : public TC_Base
{
public:
    TunnelContain(Thing *, const ModuleData *);

private:
    bool m_d4;
    bool m_d5;
};

// ??0TunnelContain@@QAE@PAVThing@@PBVModuleData@@@Z
TunnelContain::TunnelContain(Thing *t, const ModuleData *m)
    : TC_Base(t, m), m_d4(true), m_d5(false)
{
}

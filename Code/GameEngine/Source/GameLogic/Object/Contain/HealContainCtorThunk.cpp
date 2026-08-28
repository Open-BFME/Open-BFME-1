// cl: /DNDEBUG /MD /EHs-
// Open-BFME5: lift HealContain ctor __emit thunk to clean C++. Retail calls
// the out-of-line base ctor with both args, then batches nine most-derived
// vtable stores at +0x00/+0x0C/+0x10/+0x20/+0x24/+0x28/+0x2C/+0x30/+0x34;
// every polymorphic subobject is nested inside the base. /EHs- because
// retail has no unwind frame.

class Thing;
class ModuleData;

class HealContainGrandBase
{
public:
    HealContainGrandBase(Thing *, const ModuleData *);
    virtual ~HealContainGrandBase();

private:
    unsigned char m_pad[8];
};

class HealContainIface1 { public: virtual ~HealContainIface1(); };
class HealContainIface2 { public: virtual ~HealContainIface2(); private: unsigned char m_pad[0xC]; };
class HealContainIface3 { public: virtual ~HealContainIface3(); };
class HealContainIface4 { public: virtual ~HealContainIface4(); };
class HealContainIface5 { public: virtual ~HealContainIface5(); };
class HealContainIface6 { public: virtual ~HealContainIface6(); };
class HealContainIface7 { public: virtual ~HealContainIface7(); };
class HealContainIface8 { public: virtual ~HealContainIface8(); };

class HealContainBase : public HealContainGrandBase,
                        public HealContainIface1,
                        public HealContainIface2,
                        public HealContainIface3,
                        public HealContainIface4,
                        public HealContainIface5,
                        public HealContainIface6,
                        public HealContainIface7,
                        public HealContainIface8
{
public:
    HealContainBase(Thing *, const ModuleData *);
    virtual ~HealContainBase();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/HealContain.h
class HealContain : public HealContainBase
{
public:
    HealContain(Thing *, const ModuleData *);
};

// ??0HealContain@@QAE@PAVThing@@PBVModuleData@@@Z
HealContain::HealContain(Thing *t, const ModuleData *m)
    : HealContainBase(t, m)
{
}

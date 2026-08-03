// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: W3DDebrisDraw constructor reconstructed from retail layout.

class Thing;
class ModuleData;

class Slot
{
    unsigned long m_value;

public:
    Slot() {}
    Slot &operator=(unsigned long value)
    {
        m_value = value;
        return *this;
    }
};

class ClientUpdateModule
{
protected:
    unsigned char m_padding04[8];

public:
    ClientUpdateModule(Thing *, const ModuleData *);
    virtual ~ClientUpdateModule() {}
    virtual void f00() = 0;
    virtual void f01() = 0;
    virtual void f02() = 0;
    virtual void f03() = 0;
    virtual void f04() = 0;
    virtual void f05() = 0;
    virtual void f06() = 0;
    virtual void f07() = 0;
    virtual void f08() = 0;
    virtual void f09() = 0;
    virtual void f10() = 0;
    virtual void f11() = 0;
    virtual void f12() = 0;
    virtual void f13() = 0;
    virtual void f14() = 0;
    virtual void f15() = 0;
    virtual void f16() = 0;
    virtual void f17() = 0;
    virtual void f18() = 0;
    virtual void f19() = 0;
};

class DebrisDrawInterface
{
public:
    virtual void setModelName(int, int, int) = 0;
    virtual void setAnimNames(int, int, int, int) = 0;
};

class W3DDebrisDraw : public ClientUpdateModule, public DebrisDrawInterface
{
    Slot m_10;
    Slot m_14;
    unsigned long m_18;
    unsigned long m_1c;
    unsigned long m_20;
    unsigned long m_24;
    unsigned long m_28;
    unsigned long m_2c;
    unsigned long m_30;
    unsigned long m_34;
    unsigned long m_38;
    unsigned long m_3c;
    unsigned char m_40;
    unsigned char m_padding41[3];
    unsigned long m_44;

public:
    W3DDebrisDraw(Thing *, const ModuleData *);
    virtual ~W3DDebrisDraw();
    virtual void f00();
    virtual void f01();
    virtual void f02();
    virtual void f03();
    virtual void f04();
    virtual void f05();
    virtual void f06();
    virtual void f07();
    virtual void f08();
    virtual void f09();
    virtual void f10();
    virtual void f11();
    virtual void f12();
    virtual void f13();
    virtual void f14();
    virtual void f15();
    virtual void f16();
    virtual void f17();
    virtual void f18();
    virtual void f19();
    virtual void setModelName(int, int, int);
    virtual void setAnimNames(int, int, int, int);
};

// ??0W3DDebrisDraw@@QAE@PAVThing@@PBVModuleData@@@Z
W3DDebrisDraw::W3DDebrisDraw(Thing *thing, const ModuleData *moduleData)
    : ClientUpdateModule(thing, moduleData)
{
    m_10 = 0;
    m_14 = 0xffffffff;
    m_18 = 0;
    m_1c = 0;
    m_20 = 0;
    m_24 = 0;
    m_34 = 0;
    m_38 = 0;
    m_3c = 0;
    m_40 = 0;
    m_44 = 0;
    m_28 = 0;
    m_2c = 0;
    m_30 = 0;
}

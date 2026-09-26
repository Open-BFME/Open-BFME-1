// cl: /DNDEBUG /DWIN32 /MD /EHsc /O2 /Ob2

struct Rva0016DED0Flags
{
    bool m_first;
    bool m_second;
};

class Rva0016DED0Target
{
public:
    virtual void slot00(); virtual void slot04(); virtual void slot08();
    virtual void slot0C(); virtual void slot10(); virtual void slot14();
    virtual void slot18(); virtual void slot1C(); virtual void slot20();
    virtual void slot24();
    virtual Rva0016DED0Target *applyFlags(const Rva0016DED0Flags &flags);
    virtual void slot2C(); virtual void slot30(); virtual void slot34();
    virtual void slot38(); virtual void slot3C(); virtual void slot40();
    virtual void slot44(); virtual void slot48(); virtual void slot4C();
    virtual void slot50(); virtual void slot54(); virtual void slot58();
    virtual void slot5C(); virtual void slot60(); virtual void slot64();
    virtual void slot68(); virtual void slot6C(); virtual void slot70();
    virtual void slot74(); virtual void slot78(); virtual void slot7C(void *value);
    virtual void slot80(); virtual void slot84(); virtual void slot88();
    virtual void slot8C(void *value);
};

class Rva0016DED0
{
public:
    void invoke(Rva0016DED0Target *target);

private:
    char m_pad00[0x2C];
};

void Rva0016DED0::invoke(Rva0016DED0Target *target)
{
    Rva0016DED0Flags first;
    first.m_first = true;
    first.m_second = true;
    target->applyFlags(first);
    target->slot7C((char *)this + 0x24);
    target->slot8C((char *)this + 0x26);
    target->slot8C((char *)this + 0x27);

    Rva0016DED0Flags second;
    second.m_first = true;
    second.m_second = true;
    Rva0016DED0Target *result = target->applyFlags(second);
    result->slot8C((char *)this + 0x2C);
}

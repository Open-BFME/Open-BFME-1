// ?seed@Rva005CC860Particle@@QAEXPAVBfmeSeedTarget@@@Z
// partial score=0.83 date=2026-09-26
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Retail seed/transfer method at 0x005CC860; class identity is not yet proven.

struct Rva005CC860Pair
{
    unsigned char first;
    unsigned char second;
};

class BfmeSeedTarget
{
public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0C();
    virtual bool skipTransfer();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1C();
    virtual void slot20();
    virtual void slot24();
    virtual void beginPair(Rva005CC860Pair *pair);
    virtual void slot2C();
    virtual void slot30();
    virtual void slot34();
    virtual void slot38();
    virtual void slot3C();
    virtual void slot40();
    virtual void slot44();
    virtual void slot48();
    virtual void slot4C();
    virtual void slot50();
    virtual void slot54();
    virtual void slot58();
    virtual void slot5C();
    virtual void take60(void *field);
    virtual void slot64();
    virtual void slot68();
    virtual void slot6C();
    virtual void slot70();
    virtual void take74(void *field);
};

class Rva005CC860Notifier
{
public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void notify(BfmeSeedTarget *target);
};

class Gen00001B18
{
public:
    unsigned char padding[0xac];
    void *fieldAC;
};
Gen00001B18 *Make00001B18();

class Gen_005BDC70
{
public:
    void bfmeSeed(BfmeSeedTarget *target);
};

class Y3NotifyTail_005C9740
{
public:
    void notifyAll(void *target);
};

void bfmeHandOver_0000240A(BfmeSeedTarget *target, void *item);

class Rva005CC860Particle
{
public:
    void seed(BfmeSeedTarget *target);
    void *readSeedField() const;
private:
    unsigned char padding[0x58];
    unsigned int field58;
    unsigned int field5C;
    unsigned char pad60[8];
    unsigned int field68;
    unsigned int field6C;
    unsigned char pad70[0xc];
    Gen00001B18 *volatile field7C;
    unsigned char pad80[0xc];
    Rva005CC860Notifier *field8C;
    Rva005CC860Notifier *field90;
    Rva005CC860Notifier *field94;
    Y3NotifyTail_005C9740 field98;
};

void *Rva005CC860Particle::readSeedField() const
{
    Gen00001B18 *system = field7C;
    if (!system) system = Make00001B18();
    return system->fieldAC;
}

void Rva005CC860Particle::seed(BfmeSeedTarget *target)
{
    if (target->skipTransfer())
        return;
    Rva005CC860Pair pair = {1, 1};
    target->beginPair(&pair);
    reinterpret_cast<Gen_005BDC70 *>(this)->bfmeSeed(target);
    Rva005CC860Notifier *notifier = field8C;
    if (notifier) notifier->notify(target);
    notifier = field90;
    if (notifier) notifier->notify(target);
    notifier = field94;
    if (notifier) notifier->notify(target);
    field98.notifyAll(target);
    target->take74(&field58);
    target->take60(&field5C);
    target->take74(&field68);
    target->take74(&field6C);
    void *value = field7C ? readSeedField() : 0;
    bfmeHandOver_0000240A(target, &value);
}

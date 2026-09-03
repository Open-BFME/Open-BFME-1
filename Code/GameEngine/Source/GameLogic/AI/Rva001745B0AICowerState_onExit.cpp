// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport
// Retail 0x001745B0: AICowerState::onExit.

#define _STLP_NO_EXCEPTIONS 1
#include <bitset>

typedef bool Bool;

enum StateReturnType
{
    STATE_FAILURE = -2
};

enum StateExitType
{
    STATE_EXIT_UNKNOWN = 0
};

template <int NUMBITS>
class BitFlags
{
public:
    enum _dummy_kInit { kInit };

    BitFlags(_dummy_kInit, int idx1)
    {
        m_bits.set(idx1);
    }

    BitFlags()
    {
    }

private:
    _STL::bitset<NUMBITS> m_bits;
};

typedef BitFlags<86> ObjectStatusMaskType;

class Rva001745B0FlagWord
{
public:
    Bool test(int index) const
    {
        return m_bits.test(index);
    }

    void reset(int index)
    {
        m_bits.reset(index);
    }

private:
    _STL::bitset<32> m_bits;
};

class Rva001745B0ReturnObject
{
public:
    virtual void slot000();
    virtual void slot004();
    virtual void slot008();
    virtual void slot00c();
    virtual void slot010();
    virtual void slot014();
    virtual void slot018();
    virtual void slot01c();
    virtual void slot020();
    virtual void slot024();
    virtual void slot028();
    virtual void slot02c();
    virtual void slot030();
    virtual void slot034();
    virtual void slot038();
    virtual void slot03c();
    virtual void slot040();
    virtual void slot044();
    virtual void slot048();
    virtual void slot04c();
    virtual void slot050();
    virtual void slot054();
    virtual void slot058();
    virtual void slot05c();
    virtual void slot060();
    virtual void slot064();
    virtual void slot068();
    virtual void slot06c();
    virtual void slot070();
    virtual void slot074();
    virtual void slot078();
    virtual void slot07c();
    virtual void slot080();
    virtual void slot084();
    virtual void slot088();
    virtual void slot08c();
    virtual void slot090();
    virtual void slot094();
    virtual void slot098();
    virtual void slot09c();
    virtual void slot0a0();
    virtual void slot0a4();
    virtual void slot0a8();
    virtual void slot0ac();
    virtual void slot0b0();
    virtual void slot0b4();
    virtual void slot0b8();
    virtual void slot0bc();
    virtual void slot0c0();
    virtual void slot0c4();
    virtual void slot0c8();
    virtual void slot0cc();
    virtual void slot0d0();
    virtual void slot0d4();
    virtual void slot0d8();
    virtual void slot0dc();
    virtual void slot0e0();
    virtual void slot0e4();
    virtual void slot0e8();
    virtual void slot0ec();
    virtual void slot0f0();
    virtual void slot0f4();
    virtual void slot0f8();
    virtual void slot0fc();
    virtual void slot100();
    virtual void slot104();
    virtual void slot108();
    virtual void slot10c();
    virtual void slot110();
    virtual void slot114();
    virtual void slot118();
    virtual void slot11c();
    virtual void slot120();
    virtual void slot124();
    virtual void slot128();
    virtual void slot12c();
    virtual void slot130();
    virtual void slot134();
    virtual void slot138();
    virtual void slot13c();
    virtual void slot140();
    virtual void slot144();
    virtual void slot148();
    virtual void slot14c();
    virtual void slot150();
    virtual void slot154();
    virtual void slot158();
    virtual void slot15c();
    virtual void slot160();
    virtual void slot164();
    virtual void slot168();
    virtual void slot16c();
    virtual void clearSomething(Bool enabled);
};

class Rva001745B0AIUpdate
{
public:
    virtual void slot000();
    virtual void slot004();
    virtual void slot008();
    virtual void slot00c();
    virtual void slot010();
    virtual void slot014();
    virtual void slot018();
    virtual void slot01c();
    virtual void slot020();
    virtual void slot024();
    virtual void slot028();
    virtual void slot02c();
    virtual void slot030();
    virtual void slot034();
    virtual void slot038();
    virtual void slot03c();
    virtual void slot040();
    virtual void slot044();
    virtual void slot048();
    virtual void slot04c();
    virtual void slot050();
    virtual void slot054();
    virtual void slot058();
    virtual void slot05c();
    virtual void slot060();
    virtual void slot064();
    virtual Rva001745B0ReturnObject *getThing();
};

class Object
{
public:
    Bool isSelectable() const;
    void setSelectable(Bool selectable);
    void setStatus(const ObjectStatusMaskType &status, Bool set);
    void notifyModelConditionChanged();

    unsigned char m_unreconstructed_000[0x130];
    Rva001745B0FlagWord m_flags_130;
    unsigned char m_unreconstructed_134[0xc8];
    Rva001745B0AIUpdate *m_ai;
};

class BfmeSubAED
{
public:
    void bfmeStepAED(int value);
};

struct Rva001745B0StateMachine
{
    unsigned char m_unreconstructed_000[0x10];
    Object *m_owner;
    unsigned char m_unreconstructed_014[0x2c];
    unsigned char m_field_040;
};

class Rva000A19E0StateBase
{
public:
    virtual StateReturnType onEnter();
    virtual void onExit(StateExitType status);
};

class Rva001744C0State : public Rva000A19E0StateBase
{
    unsigned char m_unreconstructed_004[0x18];
    Rva001745B0StateMachine *m_machine;
    unsigned char m_unreconstructed_020[4];
    Bool m_selectable;

public:
    virtual void onExit(StateExitType status);
};

void Rva001744C0State::onExit(StateExitType status)
{
    Object *owner = m_machine->m_owner;
    owner->setSelectable(m_selectable);
    owner->setStatus(ObjectStatusMaskType(ObjectStatusMaskType::kInit, 68), false);
    if (owner->m_flags_130.test(25))
    {
        owner->m_flags_130.reset(25);
        owner->notifyModelConditionChanged();
    }
    m_machine->m_field_040 = 0;

    Object *source = m_machine->m_owner;
    if (source)
    {
        ((BfmeSubAED *)source)->bfmeStepAED(4);
        Rva001745B0AIUpdate *ai = source->m_ai;
        if (ai)
        {
            Rva001745B0ReturnObject *target = ai->getThing();
            if (target)
                target->clearSomething(false);
        }
    }
}

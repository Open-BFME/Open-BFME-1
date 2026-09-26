// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// The 83-byte retail body at 0x002C48A0 is slot 12 of secondary vtables
// installed by both HordeAIUpdate and HordeWorkerAIUpdate. The shared slot
// does not identify its original declaring class, so this owner keeps the RVA.
// Its this pointer is adjusted by +0x338 from the field holding Object *.
// Object+0x1FC is the containment module; its slot +0x68 returns a target
// whose slot +0x20 receives the explicit Object argument. Between those two
// calls, Object::setStatus sets bit 37 (OBJECT_STATUS_HORDE_MEMBER).

#define _STLP_NO_EXCEPTIONS 1
#include <bitset>

enum ObjectStatusTypes
{
    OBJECT_STATUS_HORDE_MEMBER = 37
};

template <int N> class BitFlags
{
public:
    BitFlags() {}
    void set(int bit) { m_bits._Unchecked_set(bit); }
private:
    _STL::bitset<N> m_bits;
};

class Object
{
public:
    void setStatus(const BitFlags<86> &mask, bool enabled);
};

class Rva002C48A0Target;

class Rva002C48A0Query
{
public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0c();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1c();
    virtual void slot20();
    virtual void slot24();
    virtual void slot28();
    virtual void slot2c();
    virtual void slot30();
    virtual void slot34();
    virtual void slot38();
    virtual void slot3c();
    virtual void slot40();
    virtual void slot44();
    virtual void slot48();
    virtual void slot4c();
    virtual void slot50();
    virtual void slot54();
    virtual void slot58();
    virtual void slot5c();
    virtual void slot60();
    virtual void slot64();
    virtual Rva002C48A0Target *slot68();
};

class Rva002C48A0Target
{
public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0c();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1c();
    virtual void slot20(Object *);
};

struct Rva002C48A0Root
{
    char unknown[0x1fc];
    Rva002C48A0Query *query;
};

class Rva002C48A0Owner
{
public:
    bool applyHordeMemberStatus(Object *object, int unused);
};

// ?applyHordeMemberStatus@Rva002C48A0Owner@@QAE_NPAVObject@@H@Z
bool Rva002C48A0Owner::applyHordeMemberStatus(Object *object, int)
{
    Rva002C48A0Root *root = *(Rva002C48A0Root **)((char *)this - 0x338);
    Rva002C48A0Query *query = root->query;
    Rva002C48A0Target *target = query->slot68();
    if (!target)
        return false;
    BitFlags<86> mask;
    mask.set(OBJECT_STATUS_HORDE_MEMBER);
    object->setStatus(mask, true);
    target->slot20(object);
    return false;
}

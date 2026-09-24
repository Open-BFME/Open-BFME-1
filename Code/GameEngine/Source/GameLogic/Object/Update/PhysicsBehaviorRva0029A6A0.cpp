// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Retail 0x0029A6A0 is a complete 196-byte PhysicsBehavior thiscall(bool).
// The matched Object::rva001C7CF0 passes its PhysicsBehavior* (Object+0x208)
// with one Boolean stack argument through ILT 0x0000D81E. This call and the
// matched constructor/destructor prove the owner and ABI, but not the exact
// method name, so the address remains in the method spelling.
//
// The two final-template byte checks share one false path in retail. Keeping
// them in a short-circuit OR preserves its branch layout. On false the body
// clears shipped model-condition indices 153 STUNNED_STANDING_UP, 120
// STUNNED_FLAILING, and 121 STUNNED, notifying after each changed bit.
// Native bitset accessors preserve the retail mask and word code generation.
#define _STLP_NO_EXCEPTIONS 1
#include <bitset>

class Rva0029A6A0Conditions
{
public:
    bool test(int bit) const { return m_bits.test(bit); }
    void reset(int bit) { m_bits.reset(bit); }
private:
    _STL::bitset<320> m_bits;
};

class Object
{
public:
    void notifyModelConditionChanged();
    char m_prefix[0x110];
    Rva0029A6A0Conditions m_conditions;
};

class Overridable
{
public:
    const Overridable *getFinalOverride() const;
};

class PhysicsBehavior
{
public:
    void rva0029A6A0(bool flag);
};

static char *finalTemplate(char *object)
{
    char *type = *(char **)(object + 4);
    if (type != 0)
    {
        const Overridable *base = *(const Overridable **)(type + 4);
        if (base != 0)
            type = (char *)base->getFinalOverride();
    }
    return type;
}

static __forceinline void clearCondition(Object *object, int bit)
{
    if (object->m_conditions.test(bit))
    {
        object->m_conditions.reset(bit);
        object->notifyModelConditionChanged();
    }
}

void PhysicsBehavior::rva0029A6A0(bool flag)
{
    char *self = (char *)this;
    char *object = *(char **)(self + 8);
    char *containedBy = *(char **)(object + 0x214);

    if (*(bool *)(finalTemplate(object) + 0x4b0) ||
        (containedBy != 0 && *(bool *)(finalTemplate(containedBy) + 0x4b0)))
        flag = false;

    *(bool *)(self + 0x5c) = flag;
    if (flag)
        return;

    Object *owner = (Object *)object;
    clearCondition(owner, 153);
    clearCondition(owner, 120);
    clearCondition(owner, 121);
    *(unsigned int *)(self + 0x58) = 0;
}

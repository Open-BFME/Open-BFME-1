// ?rva0029A7D0@PhysicsBehavior@@QAEXXZ
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Retail 0x0029A7D0 is a complete 133-byte PhysicsBehavior thiscall. The
// Object caller at 0x001CDE30 passes Object+0x208 through ILT 0x00029B68;
// matched Object_rva001C7CF0.cpp independently identifies that field as
// PhysicsBehavior*. The matched constructor/destructor prove this+0x04 is
// module data and this+0x08 is the Object. The method name is unresolved.
//
// Retail checks the final ThingTemplate of the Object and its contained-by
// Object for an unnamed byte at +0x4B0. It then sets Object model condition
// bit 121 (STUNNED in the shipped table at VA 0x012A6918), writes the
// PhysicsBehavior fields at +0x58/+0x5C, and wakes the module. The field
// identities at +0x58/+0x5C and the template byte remain unclaimed.
// The native bitset accessor layers reproduce retail's EAX mask materialization.
#define _STLP_NO_EXCEPTIONS 1
#include <bitset>

class Rva0029A7D0Conditions
{
public:
    bool test(int bit) const { return m_bits.test(bit); }
    void set(int bit) { m_bits.set(bit); }
private:
    _STL::bitset<320> m_bits;
};

class Object
{
public:
    void notifyModelConditionChanged();
    char m_prefix[0x110];
    Rva0029A7D0Conditions m_conditions;
};

class Overridable
{
public:
    const Overridable *getFinalOverride() const;
};

class UpdateModule
{
public:
    void setWakeFrame(Object *, unsigned int);
};

class PhysicsBehavior : public UpdateModule
{
public:
    void rva0029A7D0();
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

static __forceinline void setCondition(Object *object)
{
    if (!object->m_conditions.test(121))
    {
        object->m_conditions.set(121);
        object->notifyModelConditionChanged();
    }
}

void PhysicsBehavior::rva0029A7D0()
{
    char *self = (char *)this;
    char *object = *(char **)(self + 8);
    char *containedBy = *(char **)(object + 0x214);

    if (*(bool *)(finalTemplate(object) + 0x4b0))
        return;
    if (containedBy != 0 && *(bool *)(finalTemplate(containedBy) + 0x4b0))
        return;

    setCondition((Object *)object);

    *(bool *)(self + 0x5c) = true;
    char *data = *(char **)(self + 4);
    *(unsigned int *)(self + 0x58) = *(unsigned int *)(data + 0x20);
    setWakeFrame((Object *)object, 1);
}

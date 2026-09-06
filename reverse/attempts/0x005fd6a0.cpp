// ?d_005fd6a0@@YAXXZ
// partial score=0.55 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc

namespace FXParticleSystem {

class FXList;

class BfmeVal1027 {
public:
    float bfmeVal1027() const;
};

class TerrainCollisionEventFXLookupShim {
public:
    const FXList *lookup(const char *name) const;
};

extern "C" TerrainCollisionEventFXLookupShim *g_terrainCollisionEventFXListStore;

template <int Category>
struct DefaultModuleName {
    static const char VALUE[1];
};

struct OwnerY005FD6A0;

// Retail layout: address-derived (identity of the concrete owner/module class
// unproven -- see reverse/re_attempts.log for 0x005FD6A0). BaseY005E4C10 is
// the ctor's inlined base: it installs two interim "CategoryModuleTemplate<8>"
// -family vtables (m_vtbl1/m_vtbl2) and zeroes the remaining fields; its
// declared-only destructor gives retail's SEH frame and construction-state
// byte (the base could still be unwound if the lookup call below throws).
// The derived ctor then finalizes all three vtable slots (+0, +4, +0xc),
// evaluates a BfmeVal1027 member of the owner at +0x28 into +0x10, and
// copies the owner's lazily-cached TerrainCollisionEventFX lookup
// (owner+0x38, keyed by the name pointer at owner+0x24 with the same
// name->m_text ? name->m_text+8 : DefaultModuleName<8>::VALUE idiom already
// landed for LifeEventModuleInfo::getEventFX / TerrainCollisionModuleInfo::
// getEventFX in fx_particle_system_bulk.cpp) into +0x14, plus two owner bytes
// (+0x34 -> +0x18, +0x1d -> +0x8).
class BaseY005E4C10 {
public:
    BaseY005E4C10(OwnerY005FD6A0 *owner);
    ~BaseY005E4C10();

protected:
    unsigned int m_vtbl1;
    bool m_flag1;
    unsigned int m_vtbl2;
    unsigned int m_zero1;
    unsigned int m_zero2;
    bool m_flag2;
};

BaseY005E4C10::BaseY005E4C10(OwnerY005FD6A0 *)
    : m_vtbl1(0x0107375c), m_flag1(true), m_vtbl2(0x01112abc),
      m_zero1(0), m_zero2(0), m_flag2(false)
{
}

class Rva005FD6A0 : public BaseY005E4C10 {
public:
    Rva005FD6A0(OwnerY005FD6A0 *owner);
};

Rva005FD6A0::Rva005FD6A0(OwnerY005FD6A0 *owner)
    : BaseY005E4C10(owner)
{
    unsigned char *ownerBytes = (unsigned char *)owner;
    BfmeVal1027 *val = (BfmeVal1027 *)(ownerBytes + 0x28);

    m_vtbl1 = 0x01112aac;
    m_vtbl2 = 0x01111d38;
    m_zero1 = 0x01111d24;

    *(float *)&m_zero2 = val->bfmeVal1027();

    const FXList **cached = (const FXList **)(ownerBytes + 0x38);
    if (!*cached) {
        const char *name = *(const char **)(ownerBytes + 0x24);
        *cached = g_terrainCollisionEventFXListStore->lookup(
            name ? name + 8 : DefaultModuleName<8>::VALUE);
    }

    *(unsigned int *)((unsigned char *)this + 0x14) = (unsigned int)*cached;
    m_flag2 = *(ownerBytes + 0x34) != 0;
    m_flag1 = *(ownerBytes + 0x1d) != 0;
}

}

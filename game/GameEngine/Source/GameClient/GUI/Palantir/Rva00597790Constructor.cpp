// cl: /O2 /Ob2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Evidence: targets/game/reverse/identity_evidence/00597790-constructor.md
#include "ascii_string.h"
#include <algorithm>

typedef int (__cdecl *BigObfHook)(void *, void *, __int64);

struct BigObfSlot
{
    BigObfHook m_hook, m_alt;
    char m_pad[0x80];
    void *m_a, *m_b;
};

extern BigObfSlot g_Slot012BC6C8;

class Obf00590B50
{
public:
    __declspec(noinline) Obf00590B50(int *, int *);
    unsigned m_bits[8];
};

struct BigObfSelectorRecord
{
    unsigned m_key[5], m_seed[5];
};

extern BigObfSelectorRecord g_ObfRecord012B82C4;

// The selector reads the caller's frame register; the remaining helper is C++.
inline Obf00590B50::Obf00590B50(int *a, int *b)
{
    unsigned selector = 0;
    __asm { mov selector, ebp }
    unsigned index = selector & 3;
    unsigned key = g_ObfRecord012B82C4.m_key[index];
    m_bits[0] = g_ObfRecord012B82C4.m_seed[index];
    m_bits[1] = 0x04A85801;
    m_bits[2] = 0x04A85805;
    m_bits[3] = 0x04A85801;
    m_bits[4] = *a;
    m_bits[5] = *b;
    m_bits[1] ^= key * key;
    m_bits[2] ^= m_bits[1] * key;
    m_bits[3] ^= m_bits[2] * key;
    m_bits[4] ^= m_bits[3] * key;
    m_bits[5] ^= m_bits[4] * key;
    m_bits[6] ^= m_bits[5] * key;
    m_bits[7] ^= m_bits[6] * key;
}

struct Rva00597790HookArguments
{
    void *pa, *pb;
    __forceinline Rva00597790HookArguments(void *a, void *b) : pa(a), pb(b) {}
};

int __cdecl Gen0058C7F0(int, int);

static __forceinline int Rva00597790Arithmetic(int a, int b)
{
    BigObfHook hook = g_Slot012BC6C8.m_hook;
    if (hook)
        goto hot;
    if (g_Slot012BC6C8.m_alt)
    {
    hot:
        Rva00597790HookArguments args(g_Slot012BC6C8.m_a, g_Slot012BC6C8.m_b);
        Obf00590B50 o(&a, &b);
        return hook(args.pa, args.pb, (__int64)(int)&o);
    }
    return Gen0058C7F0(a, b);
}

struct Rva00597790Record
{
    int at00, at04, at08;
    float at0c;
    int at10;
    bool at14;

    __forceinline Rva00597790Record()
        : at00(0), at08(Rva00597790Arithmetic(0, 0)), at0c(1.0f), at10(0), at14(false) {}
};

class Rva00597790;

struct Rva00597790OwnerBinding
{
    Rva00597790 *owner;
    int index;
    Rva00597790OwnerBinding(Rva00597790 *p, int i) : owner(p), index(i) {}
};

struct Rva00597790TimerBinding
{
    float *first;
    int *second;
    Rva00597790TimerBinding(float &p, int &q) : first(&p), second(&q) {}
};

class FunctorWrapperHead
{
public:
    virtual ~FunctorWrapperHead();
    int m_refCount;
    FunctorWrapperHead() : m_refCount(0) {}
};

struct Rva0046C000Mapped
{
    FunctorWrapperHead *m_ptr;
    ~Rva0046C000Mapped();
};

class Rva0050F8B0FunctorHolder
{
    FunctorWrapperHead *value;

public:
    ~Rva0050F8B0FunctorHolder()
    {
        reinterpret_cast<Rva0046C000Mapped *>(&value)->~Rva0046C000Mapped();
    }
    Rva0050F8B0FunctorHolder(Rva00597790OwnerBinding);
    Rva0050F8B0FunctorHolder(Rva00597790TimerBinding);
    Rva0050F8B0FunctorHolder(const Rva0050F8B0FunctorHolder &other)
    {
        value = other.value;
        if (value)
            ++value->m_refCount;
    }
    Rva0050F8B0FunctorHolder(FunctorWrapperHead *p)
    {
        value = p;
        if (p)
            ++p->m_refCount;
    }
};

class Rva0058CFD0FunctorSingleWrapper : public FunctorWrapperHead
{
    Rva00597790OwnerBinding m_binding;

public:
    Rva0058CFD0FunctorSingleWrapper(const Rva00597790OwnerBinding &binding) : m_binding(binding) {}
    virtual ~Rva0058CFD0FunctorSingleWrapper();
    virtual void invoke(void *);
};

typedef Rva0058CFD0FunctorSingleWrapper Rva0110BCA0Callback;

struct Rva0058CFB0Pair
{
    int first, second;
};

class Rva0058CF80FunctorSingleWrapper : public FunctorWrapperHead
{
    Rva00597790TimerBinding m_binding;

public:
    Rva0058CF80FunctorSingleWrapper(const Rva00597790TimerBinding &binding) : m_binding(binding) {}
    virtual ~Rva0058CF80FunctorSingleWrapper();
    virtual Rva0058CFB0Pair invoke(const void *) const;
};

typedef Rva0058CF80FunctorSingleWrapper Rva0110BC94Callback;

__forceinline Rva0050F8B0FunctorHolder::Rva0050F8B0FunctorHolder(Rva00597790OwnerBinding binding)
{
    FunctorWrapperHead *p = new Rva0110BCA0Callback(binding);
    value = p;
    if (p)
        ++p->m_refCount;
}

__forceinline Rva0050F8B0FunctorHolder::Rva0050F8B0FunctorHolder(Rva00597790TimerBinding binding)
{
    FunctorWrapperHead *p = new Rva0110BC94Callback(binding);
    value = p;
    if (p)
        ++p->m_refCount;
}

class WindowManager
{
public:
    void bfmeBindRva004650F0(const AsciiString &, Rva0050F8B0FunctorHolder);
    void registerPalantirCallback(const AsciiString &, Rva0050F8B0FunctorHolder);
};

// Retail 0x012F19E8 is ?g_rva012F19E8WindowManager@@3PAVWindowManager@@A
// (data_rows.csv, GUI/WindowManager.cpp); g_theWindowManager was only a pin.
extern WindowManager *g_rva012F19E8WindowManager;
#define g_theWindowManager g_rva012F19E8WindowManager

class Rva00597790
{
    int at00, at04;
    bool at08[20];
    Rva00597790Record at1c[12];

public:
    Rva00597790();
};

// ??0Rva00597790@@QAE@XZ
Rva00597790::Rva00597790() : at00(0), at04(0)
{
    std::fill(at08, at08 + 20, true);
    for (int i = 0; i < 12; ++i)
    {
        AsciiString name;
        name.format("SpellBookUI/Spell%d/", i + 1);
        g_theWindowManager->bfmeBindRva004650F0(AsciiString("Palantir/") + name, Rva0050F8B0FunctorHolder(Rva00597790OwnerBinding(this, i)));
        name.StringBase<char>::concat("Timer", 5);
        g_theWindowManager->registerPalantirCallback(name, Rva0050F8B0FunctorHolder(Rva00597790TimerBinding(at1c[i].at0c, at1c[i].at10)));
    }
}

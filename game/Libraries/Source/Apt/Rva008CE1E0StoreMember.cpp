// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// RVA 008CE1E0, 549 bytes. Two cdecl stack arguments; see analyst 008985C0.
// Value +4 flags/+8 string/+20 indirect string; stack +0 count/+8 values.
extern "C" int __cdecl strcmp(const char *, const char *);
#pragma intrinsic(strcmp)
struct BfmeStringData3AF0 { unsigned short m_refCount, m_length, m_capacity, m_unknown06; };
struct BfmeStringPool3AF0 { void *m_unknown00; void (__cdecl *free)(void *); };
extern BfmeStringData3AF0 g_bfmeDefaultString1284;
extern BfmeStringPool3AF0 *g_bfmeStringPool1284;
class Rva8CD130String {
public:
    __forceinline Rva8CD130String() { m_data = &g_bfmeDefaultString1284; ++m_data->m_refCount; }
    __forceinline ~Rva8CD130String() {
        BfmeStringData3AF0 *old = m_data;
        if (--old->m_refCount == 0) g_bfmeStringPool1284->free(old);
    }
    BfmeStringData3AF0 *m_data;
};
class AptValue { public: int toInteger() const; };
class Rva8CD130Value { public: void getName(Rva8CD130String *); };
class Rva008CE1E0Value {
public:
    virtual void slot00();
    virtual void release();
    virtual void slot08();
    virtual void slot0c();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1c();
    virtual void slot20(int);
    virtual unsigned char slot24();
    __forceinline bool undefined() const { return (~(m_flags >> 15) & 1) != 0; }
    __forceinline int kind() const { return m_flags & 63; }
    __forceinline bool kindRange() const { return kind() >= 12 && kind() <= 19 && !undefined(); }
    __forceinline bool held() const { return ((m_flags >> 30) & 1) != 0; }
    unsigned m_flags;
    Rva8CD130String m_string08;
    char m_gap0c[0x14];
    Rva008CE1E0Value *m_value20;
};
class Rva008A9B00;
class Rva008CF3C0String;
class Rva008CF3C0State {
public:
    void append(void *owner, void *scope, Rva008CF3C0String *name, Rva008A9B00 *node, int a, int b, int c);
};
class BfmeG1211 { public: void bfmeStep1211C(); };
struct Rva008CE1E0Registry { int m_capacity, m_count; };
struct Rva00899560Pool;
extern Rva00899560Pool *g_rva8CD130IdleHook;
struct Rva008CE1E0State { int m_count, m_unknown04; Rva008CE1E0Value **m_values; };
struct Rva008CE1E0Context { char m_gap00[8]; void *m_scope08; };
// 0x008B8E10 landed as BfmeN1242::rva008B8E10(int, BfmeE1242 *) (thiscall,
// ret 8); this caller only needs its exact mangled symbol, reached through
// the same member-pointer reinterpretation as before.
class BfmeE1242;
class BfmeN1242 { public: void rva008B8E10(int, BfmeE1242 *); };
typedef void (Rva008CE1E0Value::*Rva008B8E10Store)(int, Rva008CE1E0Value *);
typedef void (__cdecl *Rva008CE1E0Notify)(const char *, const char *);

void rva008CE1E0StoreMember(Rva008CE1E0State *state, Rva008CE1E0Context *context)
{
    Rva008CE1E0Value *owner = state->m_values[state->m_count - 3];
    Rva008CE1E0Value *key = state->m_values[state->m_count - 2];
    Rva008CE1E0Value *value = state->m_values[state->m_count - 1];
    if (owner->kind() == 22 && !owner->undefined() &&
        ((key->kind() == 7 && !key->undefined()) || (key->kind() == 6 && !key->undefined()))) {
        union { void (BfmeN1242::*bound)(int, BfmeE1242 *); Rva008B8E10Store member; } call;
        call.bound = &BfmeN1242::rva008B8E10;
        (owner->*call.member)(((AptValue *)key)->toInteger(), value);
    } else if (owner->slot24() || owner->kindRange()) {
        Rva8CD130String name;
        ((Rva8CD130Value *)key)->getName(&name);
        ((Rva008CF3C0State *)state)->append(owner, context->m_scope08,
            (Rva008CF3C0String *)&name, (Rva008A9B00 *)value, 1, 0, 1);
        if (strcmp((const char *)name.m_data + 8, "__proto__") == 0 &&
            ((owner->kind() == 27 && !owner->undefined()) || owner->kindRange()))
            owner->slot20(1);
    } else if (owner->kind() == 11 && !owner->undefined()) {
        Rva8CD130String text;
        ((Rva8CD130Value *)value)->getName(&text);
        int keyKind = key->kind();
        if (keyKind != 1) key = key->m_value20;
        (*(Rva008CE1E0Notify *)0x01337864)((const char *)key->m_string08.m_data + 8,
            (const char *)text.m_data + 8);
    }
    for (int index = 1; index <= 3; ++index) {
        Rva008CE1E0Value *old = state->m_values[state->m_count - index];
        if (!old->held()) old->release();
    }
    state->m_count -= 3;
    int count = state->m_count;
    if (((Rva008CE1E0Registry *)g_rva8CD130IdleHook)->m_count != 0 && count == 0)
        ((BfmeG1211 *)g_rva8CD130IdleHook)->bfmeStep1211C();
}

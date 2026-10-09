// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// RVA 008AB0E0: Apt string property dispatch (__stdcall owner, key; ret 8).
// The key is hashed through the string-method table Rva008A9710; id 1 returns
// the owner's name length as a pooled integer (getName + bfmeUtf8Length), ids
// 2..13 lazily build and cache one native callable (0x24 bytes, ctor 0x00899FC0)
// per string method -- the landed callbacks 0x008A9E20..0x008AAFD0 (substring,
// slice, codepoint and string-builder bodies). No symbol names the function,
// so it keeps the address token. Model: ArrayProperties008BA0B0.cpp (pooled
// integer and callable caches) and SubstringValue008AAB20.cpp (string handle).
struct Rva00899560Value;
struct Rva00899560Pool {
    int m_capacity, m_count;
    Rva00899560Value **m_items;
    template <class T> __forceinline void addPooled(T *v) {
        int &count = m_count;
        if (count >= m_capacity) {
            v->m_flags &= 0xBFFFFFFF;
            return;
        }
        m_items[count] = (Rva00899560Value *)v;
        ++count;
    }
};
extern Rva00899560Pool *g_rva01337810GcRoots;
extern void *(__cdecl *Rva008C5D70Alloc)(unsigned);
struct Rva00899560Value {
    virtual ~Rva00899560Value();
    unsigned m_flags;
    __forceinline Rva00899560Value(int type) {
        unsigned flags = (((m_flags & ~0x3f) | type) & 0xF000803F) | 0x8000;
        m_flags = flags;
        if (type != 0x1c && type != 0xa) {
            m_flags = flags | 0x40000000;
            g_rva01337810GcRoots->addPooled(this);
        } else
            m_flags = flags & 0xBFFFFFFF;
    }
    static void *operator new(unsigned n) { return Rva008C5D70Alloc(n); }
};
struct Rva008A1110Value : Rva00899560Value {
    union {
        int m_value;
        Rva008A1110Value *m_next;
    };
    __forceinline Rva008A1110Value(int x) : Rva00899560Value(7), m_value(x) {}
};
extern Rva008A1110Value *Rva013387D0;
static __forceinline Rva008A1110Value *pooledInteger(int value) {
    Rva008A1110Value *v = Rva013387D0;
    if (v) {
        Rva013387D0 = v->m_next;
        g_rva01337810GcRoots->addPooled(v);
        v->m_value = value;
        return v;
    }
    return new Rva008A1110Value(value);
}

struct BfmeStringData3AF0 {
    unsigned short m_refCount, m_length, m_capacity, m_unknown06;
};
struct BfmeStringPool3AF0 {
    void *m_unknown00;
    void (__cdecl *free)(void *);
};
extern BfmeStringData3AF0 g_bfmeDefaultString1284;
extern BfmeStringPool3AF0 *g_rva01337A30AllocPair;
class Rva8CD130String {
public:
    __forceinline Rva8CD130String() {
        m_data = &g_bfmeDefaultString1284;
        ++m_data->m_refCount;
    }
    __forceinline ~Rva8CD130String() {
        BfmeStringData3AF0 *old = m_data;
        if (--old->m_refCount == 0) g_rva01337A30AllocPair->free(old);
    }
    BfmeStringData3AF0 *m_data;
};
class Rva8CD130Value { public: void getName(Rva8CD130String *output); };
class EAStringC { public: int bfmeUtf8Length() const; };

struct R4Word { const char *name; int id; };
const R4Word *Rva008A9710(const char *, unsigned);
void *Rva00897640(unsigned);
class Rva00897670HeaderedDelete { public: static void operator delete(void *, unsigned); };
class Rva00899FC0 : public Rva00897670HeaderedDelete {
public:
    static void *operator new(unsigned n) { return Rva00897640(n); }
    __declspec(noinline) Rva00899FC0(int);
    void *vtable;
    unsigned flags;
    char field08[0x18];
    int field20;
};
// The defining declaration of this class lives in
// game/GameEngine/Source/Common/Rva008A98B0ReleaseAll.cpp (no header covers it);
// the layout members this TU needs are TU-local extensions of that name.
class Rva008A98B0Releasable {
public:
    virtual void slot00();
    virtual void slot04();
    unsigned flags;
};
struct StringBuffer008AB0E0 { unsigned short field00, field02; char field04[4]; };
struct String008AB0E0 { StringBuffer008AB0E0 *field00; };

// The twelve string-method callbacks, by retail VA.
extern char Va00CA9E20[];
extern char Va00CA9F70[];
extern char Va00CAA130[];
extern char Va00CAA2B0[];
extern char Va00CA9C30[];
extern char Va00CA99C0[];
extern char Va00CAA420[];
extern char Va00CAA650[];
extern char Va00CAAB20[];
extern char Va00CAACF0[];
extern char Va00CAAEC0[];
extern char Va00CAAFD0[];

// Retail 0x01337AC8..0x01337AF4: one cached callable per string method.
// These are the twelve release-loop slots released by
// ?rva008A98B0ReleaseAll@@YAXXZ, so they carry its defining names.
extern Rva008A98B0Releasable *g_rva008A98B0_0;
extern Rva008A98B0Releasable *g_rva008A98B0_1;
extern Rva008A98B0Releasable *g_rva008A98B0_2;
extern Rva008A98B0Releasable *g_rva008A98B0_3;
extern Rva008A98B0Releasable *g_rva008A98B0_4;
extern Rva008A98B0Releasable *g_rva008A98B0_5;
extern Rva008A98B0Releasable *g_rva008A98B0_6;
extern Rva008A98B0Releasable *g_rva008A98B0_7;
extern Rva008A98B0Releasable *g_rva008A98B0_8;
extern Rva008A98B0Releasable *g_rva008A98B0_9;
extern Rva008A98B0Releasable *g_rva008A98B0_10;
extern Rva008A98B0Releasable *g_rva008A98B0_11;

#define CACHED_METHOD(cache, callback) \
    if (!cache) { \
        cache = (Rva008A98B0Releasable *)new Rva00899FC0((int)callback); \
        cache->flags = (cache->flags & 0xffffc07f) | 0x40; \
        cache->slot00(); \
    } \
    return cache;

void *__stdcall Rva008AB0E0StringProperties(Rva8CD130Value *owner, String008AB0E0 *key)
{
    if (owner) {
        const R4Word *word = Rva008A9710((char *)key->field00 + 8, key->field00->field02);
        if (word) {
            switch (word->id) {
            case 1: {
                Rva8CD130String name;
                owner->getName(&name);
                return pooledInteger(((EAStringC *)&name)->bfmeUtf8Length());
            }
            case 2: CACHED_METHOD(g_rva008A98B0_0, Va00CA9E20)
            case 3: CACHED_METHOD(g_rva008A98B0_1, Va00CA9F70)
            case 4: CACHED_METHOD(g_rva008A98B0_2, Va00CAA130)
            case 5: CACHED_METHOD(g_rva008A98B0_3, Va00CAA2B0)
            case 6: CACHED_METHOD(g_rva008A98B0_4, Va00CA9C30)
            case 7: CACHED_METHOD(g_rva008A98B0_5, Va00CA99C0)
            case 8: CACHED_METHOD(g_rva008A98B0_6, Va00CAA420)
            case 9: CACHED_METHOD(g_rva008A98B0_7, Va00CAA650)
            case 10: CACHED_METHOD(g_rva008A98B0_8, Va00CAAB20)
            case 11: CACHED_METHOD(g_rva008A98B0_9, Va00CAACF0)
            case 12: CACHED_METHOD(g_rva008A98B0_10, Va00CAAEC0)
            case 13: CACHED_METHOD(g_rva008A98B0_11, Va00CAAFD0)
            }
        }
    }
    return 0;
}

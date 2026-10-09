// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// RVA 008A73E0 (1252 B incl. jump table): property lookup, vtable 0x01137270 slot 10
// (the vtable 0x008CBB30 installs; +0x20 is the field that constructor zeroes).
// The perfect-hash table at 0x012D5490 used by 0x008A44A0 proves the keys:
// 1 load, 2 send, 3 sendAndLoad, 4 getBytesTotal, 5 getBytesLoaded, 6 loaded,
// 7 toString, 8 contentType (default "application/x-www-form-urlencoded").
// Entry 0x012D5510 is the final accepted hash index (16), not a separate table.
// The member set is Flash LoadVars; class and method names stay
// address-derived.
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
struct Rva008995E0Value : Rva00899560Value {
    union { bool m_value; Rva008995E0Value *m_next; };
    __forceinline Rva008995E0Value(bool x) : Rva00899560Value(5), m_value(x) {}
};
class Rva008D2A80;
extern Rva008D2A80 *g_rva008D2A80;
static __forceinline Rva008995E0Value *pooledBoolean(bool value) {
    Rva008995E0Value *v = (Rva008995E0Value *)g_rva008D2A80;
    if (v) {
        g_rva008D2A80 = (Rva008D2A80 *)v->m_next;
        g_rva01337810GcRoots->addPooled(v);
        v->m_value = value;
        return v;
    }
    return new Rva008995E0Value(value);
}

struct R4Word { const char *name; int value; };
const R4Word *Rva008A44A0(const char *, unsigned);
void *Rva00897640(unsigned);
class Rva00897670HeaderedDelete {
public:
    static void operator delete(void *, unsigned);
};
class Rva00899FC0 : public Rva00897670HeaderedDelete {
public:
    static void *operator new(unsigned n) { return Rva00897640(n); }
    __declspec(noinline) Rva00899FC0(int callback);
    void *vtable;
    unsigned flags;
    char gap08[0x18];
    int callback;
};
class Rva008A48D0Item {
public:
    virtual void unused0();
    virtual void release();
};
extern Rva008A48D0Item *g_rva008A48D0_0;
extern Rva008A48D0Item *g_rva008A48D0_1;
extern Rva008A48D0Item *g_rva008A48D0_2;
extern Rva008A48D0Item *g_rva008A48D0_3;
extern Rva008A48D0Item *g_rva008A48D0_4;
extern Rva008A48D0Item *g_rva008A48D0_5;

struct Boolean008A58C0;
struct Owner008A5560;
struct Owner008A5BF0;
class KeyValuePairs00898D80;
class AptValue;
Boolean008A58C0 *aptReplacePairs008A5560(Owner008A5560 *, int);
Boolean008A58C0 *aptCallStrings008A58C0(KeyValuePairs00898D80 *, int);
Boolean008A58C0 *aptReplacePairs008A5BF0(Owner008A5BF0 *, int);
AptValue *aptCallbackFloat008A60A0();
AptValue *aptCallbackFloat008A60D0();
void d_008a6100();

struct StringBlock008A73E0 { unsigned short refs, length; };
struct String008A73E0 { StringBlock008A73E0 *data; };
extern StringBlock008A73E0 g_default012D5298;
class BfmeStrVKK { public: void bfmeTruncVKK(unsigned); };
class Rva008A9B00 {
public:
    static void *operator new(unsigned n) { return Rva008C5D70Alloc(n); }
    Rva008A9B00();
    static void operator delete(void *, unsigned);
    void *vtable;
    unsigned m_flags;
    StringBlock008A73E0 *field08;
    Rva008A9B00 *field0C;
};
// The Apt global node free list at 0x01338478, defined once by
// game/GameEngine/Source/Common/Data/Rva01338478.cpp.  This TU keeps its own
// view of a node (Rva008A9B00) and reaches the next link through it.
struct Rva008C3B60Node;
extern Rva008C3B60Node *g_rva01338478NodeHead;
static __forceinline Rva008A9B00 *&rva01338478FreeHead() {
    return *(Rva008A9B00 **)&g_rva01338478NodeHead;
}
static __forceinline Rva008A9B00 *pooledString() {
    Rva008A9B00 *v = rva01338478FreeHead();
    if (v) {
        rva01338478FreeHead() = v->field0C;
        g_rva01337810GcRoots->addPooled(v);
        if (v->field08 != &g_default012D5298)
            ((BfmeStrVKK *)&v->field08)->bfmeTruncVKK(0);
    } else v = new Rva008A9B00;
    return v;
}
class Rva008B2EA0Node { public: void append(void *); };

class Rva008A73E0Properties {
public:
    void *field00;
    unsigned field04;
    char field08[0x18];
    int field20;
    Rva00899560Value *lookup(void *owner, const String008A73E0 *key);
};

Rva00899560Value *Rva008A73E0Properties::lookup(void *owner, const String008A73E0 *key)
{
    if (!owner) return 0;
    const R4Word *word = Rva008A44A0((const char *)key->data + 8, key->data->length);
    if (!word) return 0;
    switch (word->value) {
    case 1:
        if (!g_rva008A48D0_0) {
            g_rva008A48D0_0 = (Rva008A48D0Item *)new Rva00899FC0((int)aptReplacePairs008A5560);
            Rva00899FC0 *value = (Rva00899FC0 *)g_rva008A48D0_0;
            value->flags = (value->flags & 0xffffc07f) | 0x40;
            g_rva008A48D0_0->unused0();
        }
        return (Rva00899560Value *)g_rva008A48D0_0;
    case 2:
        if (!g_rva008A48D0_1) {
            g_rva008A48D0_1 = (Rva008A48D0Item *)new Rva00899FC0((int)aptCallStrings008A58C0);
            Rva00899FC0 *value = (Rva00899FC0 *)g_rva008A48D0_1;
            value->flags = (value->flags & 0xffffc07f) | 0x40;
            g_rva008A48D0_1->unused0();
        }
        return (Rva00899560Value *)g_rva008A48D0_1;
    case 3:
        if (!g_rva008A48D0_2) {
            g_rva008A48D0_2 = (Rva008A48D0Item *)new Rva00899FC0((int)aptReplacePairs008A5BF0);
            Rva00899FC0 *value = (Rva00899FC0 *)g_rva008A48D0_2;
            value->flags = (value->flags & 0xffffc07f) | 0x40;
            g_rva008A48D0_2->unused0();
        }
        return (Rva00899560Value *)g_rva008A48D0_2;
    case 4:
        if (!g_rva008A48D0_3) {
            g_rva008A48D0_3 = (Rva008A48D0Item *)new Rva00899FC0((int)aptCallbackFloat008A60A0);
            Rva00899FC0 *value = (Rva00899FC0 *)g_rva008A48D0_3;
            value->flags = (value->flags & 0xffffc07f) | 0x40;
            g_rva008A48D0_3->unused0();
        }
        return (Rva00899560Value *)g_rva008A48D0_3;
    case 5:
        if (!g_rva008A48D0_4) {
            g_rva008A48D0_4 = (Rva008A48D0Item *)new Rva00899FC0((int)aptCallbackFloat008A60D0);
            Rva00899FC0 *value = (Rva00899FC0 *)g_rva008A48D0_4;
            value->flags = (value->flags & 0xffffc07f) | 0x40;
            g_rva008A48D0_4->unused0();
        }
        return (Rva00899560Value *)g_rva008A48D0_4;
    case 6:
        return pooledBoolean(field20 != 0);
    case 7:
        if (!g_rva008A48D0_5) {
            g_rva008A48D0_5 = (Rva008A48D0Item *)new Rva00899FC0((int)d_008a6100);
            Rva00899FC0 *value = (Rva00899FC0 *)g_rva008A48D0_5;
            value->flags = (value->flags & 0xffffc07f) | 0x40;
            g_rva008A48D0_5->unused0();
        }
        return (Rva00899560Value *)g_rva008A48D0_5;
    case 8: {
        Rva008A9B00 *v = pooledString();
        ((Rva008B2EA0Node *)v)->append((void *)"application/x-www-form-urlencoded");
        return (Rva00899560Value *)v;
    }
    }
    return 0;
}

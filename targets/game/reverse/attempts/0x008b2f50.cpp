// ?lookup@PropertyLookup008B2F50@@QAEPAURva00899560Value@@PAVNativeProperties008B3C40@@PAUString008B3C40@@@Z
// partial score=0.986 date=2026-09-28
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// RVA 008B2F50: base native-property dispatch of the Rva008B2EF0 wrapper class
// (vtable 0x011369F0 slot 10, installed by the matched constructor 0x008B2EF0).
// Called by the matched derived dispatcher 0x008B3C40 before its own lookup.
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
extern Rva00899560Pool *g_rva8CD130IdleHook;
extern void *(__cdecl *Rva008C5D70Alloc)(unsigned);
struct Rva00899560Value {
    virtual ~Rva00899560Value();
    unsigned m_flags;
    __forceinline Rva00899560Value(int type) {
        unsigned flags = (((m_flags & ~0x3f) | type) & 0xF000803F) | 0x8000;
        m_flags = flags;
        if (type != 0x1c && type != 0xa) {
            m_flags = flags | 0x40000000;
            g_rva8CD130IdleHook->addPooled(this);
        } else
            m_flags = flags & 0xBFFFFFFF;
    }
    Rva00899560Value() {}
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
        g_rva8CD130IdleHook->addPooled(v);
        v->m_value = value;
        return v;
    }
    return new Rva008A1110Value(value);
}

struct R4Word { const char *name; int id; };
const R4Word *Rva008D5DC0(const char *, unsigned);
void *Rva00897640(unsigned);
void *Rva008A90F0(unsigned);
void *Rva008B2AE0(unsigned);
void *Rva008B2B40(unsigned);
class Rva00897670HeaderedDelete { public: static void operator delete(void *, unsigned); };
class Rva00899FC0 : public Rva00897670HeaderedDelete {
public:
    static void *operator new(unsigned n) { return Rva00897640(n); }
    Rva00899FC0(int);
    virtual void retain();
    unsigned m_flags;
    char m_unmodelled08[0x18];
    int m_value20;
};

struct StringBlock008B3C40 { unsigned short refs, length; };
struct String008B3C40 { StringBlock008B3C40 *data; };
extern StringBlock008B3C40 g_default012D5298;
extern void (__cdecl **Rva01337A30ReleaseTable)(void *);
class BfmeStrVKK { public: void bfmeTruncVKK(unsigned); };
class BfmeStrVKI { public: void bfmeSetVKI(const char *); };
class Rva8D0D80String {
public:
    Rva8D0D80String(const char *text) { ((BfmeStrVKI *)this)->bfmeSetVKI(text); }
    __forceinline ~Rva8D0D80String() {
        StringBlock008B3C40 *block = m_block;
        --block->refs;
        if (block->refs == 0)
            Rva01337A30ReleaseTable[1](block);
    }
    StringBlock008B3C40 *m_block;
};
class Rva8D0D80Value;
class Rva8D0D80Table {
public:
    void add(Rva8D0D80String *name, Rva8D0D80Value *value);
};

class Rva008A9B00 : public Rva00899560Value {
public:
    Rva008A9B00();
    static void operator delete(void *, unsigned);
    StringBlock008B3C40 *field08;
    Rva008A9B00 *field0C;
};
extern Rva008A9B00 *Rva01338478FreeHead;
static __forceinline Rva008A9B00 *pooledString() {
    Rva008A9B00 *v = Rva01338478FreeHead;
    if (v) {
        Rva01338478FreeHead = v->field0C;
        g_rva8CD130IdleHook->addPooled(v);
        if (v->field08 != &g_default012D5298)
            ((BfmeStrVKK *)&v->field08)->bfmeTruncVKK(0);
    } else v = new Rva008A9B00;
    return v;
}
class Rva008B2EA0Node { public: void append(void *); };
extern void *g_rva008B2EA0Base;

// Allocated wrappers: each class's out-of-line operator new is its own
// eight-byte-headered allocator. Rva008D5750Object's constructor is the body
// ledgered as ?bfmeGo911F@BfmeThing911F@@ (base ctor with kind+8, vtable,
// +0x20 = native); landing needs a ??0Rva008D5750Object@@QAE@HPAX@Z ABI pin.
class Rva008B2EF0 : public Rva00899560Value {
public:
    static void *operator new(unsigned n) { return Rva008B2AE0(n); }
    static void operator delete(void *, unsigned);
    Rva008B2EF0(unsigned, unsigned);
    char m_unmodelled08[0x18];
    unsigned m_value20;
    unsigned m_value24;
};
class Rva008D5750Object : public Rva00899560Value {
public:
    static void *operator new(unsigned n) { return Rva008B2B40(n); }
    static void operator delete(void *, unsigned);
    Rva008D5750Object(int, void *);
    Rva8D0D80Table m_table;
    char m_unmodelled09[0x17];
    void *m_value20;
};
class BfmeE1242;
class BfmeN1242 { public: void rva008B8E10(int, BfmeE1242 *); };
class ArrayValue008B9C60 : public Rva00899560Value {
public:
    static void *operator new(unsigned n) { return Rva008A90F0(n); }
    static void operator delete(void *, unsigned);
    ArrayValue008B9C60();
    char m_unmodelled08[0x24];
};

struct NativePair008B2F50 { const char *name; const char *value; };
struct NativeSlots008B2F50 {
    virtual void slot00();
    virtual void slot04();
    virtual NativePair008B2F50 slot08();
    virtual NativePair008B2F50 slot0C();
    virtual void slot10();
    virtual void *slot14();
    virtual void *slot18();
    virtual void slot1C();
    virtual void *slot20();
    virtual void slot24();
    virtual void slot28();
    virtual void *slot2C();
    virtual void *slot30();
    virtual const void *slot34();
    virtual void slot38();
    virtual int slot3C();
    virtual const void *slot40();
    virtual void slot44();
    virtual void *slot48();
    virtual void *slot4C();
};
class NativeProperties008B3C40;
class PropertyLookup008B2F50 {
public:
    char m_unmodelled00[0x20];
    NativeSlots008B2F50 *m_value20;
    Rva00899560Value *lookup(NativeProperties008B3C40 *, String008B3C40 *);
};
extern Rva00899560Value *g_bfmeFallbackDB;
extern Rva00899FC0 *g_rva01338360;
extern Rva00899FC0 *g_rva01338364;
extern Rva00899FC0 *g_rva01338368;
extern Rva00899FC0 *g_rva0133836C;
extern Rva00899FC0 *g_rva01338370;
extern Rva00899FC0 *g_rva01338374;
extern char Va00CB2DB0[];
extern char Va00CB2DC0[];
extern char Va00CB2DD0[];
extern char Va00CB2DE0[];
struct Rva008B2E60Value;
class AptValue *aptQueryBool(Rva008B2E60Value *, int);
class Rva008B2EA0Obj;
void *rva008B2EA0Walk(Rva008B2EA0Obj *);

#define NATIVE_FUNCTION(global, callback)                                   \
    if (!global) {                                                          \
        global = new Rva00899FC0((int)(callback));                          \
        global->m_flags = (global->m_flags & 0xffffc07f) | 0x40;            \
        global->retain();                                                   \
    }                                                                       \
    return (Rva00899560Value *)global;

Rva00899560Value *PropertyLookup008B2F50::lookup(NativeProperties008B3C40 *owner, String008B3C40 *key) {
    if (owner) {
    const R4Word *word = Rva008D5DC0((char *)key->data + 8, key->data->length);
    if (word) {
    switch (word->id) {
    case 1:
        NATIVE_FUNCTION(g_rva01338360, Va00CB2DB0)
    case 2: {
        Rva008D5750Object *object = new Rva008D5750Object(0x22, m_value20);
        if (m_value20) {
            NativePair008B2F50 it = m_value20->slot08();
            while (it.name && it.value) {
                Rva008A9B00 *text = pooledString();
                ((Rva008B2EA0Node *)text)->append((void *)it.value);
                Rva8D0D80String name(it.name);
                object->m_table.add(&name, (Rva8D0D80Value *)text);
                it = m_value20->slot0C();
            }
        }
        if (object) return object;
        return g_bfmeFallbackDB;
    }
    case 3: {
        if (!m_value20) return g_bfmeFallbackDB;
        ArrayValue008B9C60 *array = new ArrayValue008B9C60;
        if (!array) return 0;
        void *item = m_value20->slot14();
        int index = 0;
        while (item) {
            ((BfmeN1242 *)array)->rva008B8E10(index, (BfmeE1242 *)new Rva008B2EF0(0x20, (unsigned)item));
            ++index;
            item = m_value20->slot18();
        }
        return array;
    }
    case 4:
        NATIVE_FUNCTION(g_rva01338364, Va00CB2DC0)
    case 5: {
        if (m_value20) {
            void *item = m_value20->slot20();
            if (item) {
                Rva00899560Value *v = new Rva008B2EF0(0x20, (unsigned)item);
                if (v->m_flags & 0x8000) return v;
                break;
            }
        }
        return g_bfmeFallbackDB;
    }
    case 6:
        NATIVE_FUNCTION(g_rva01338368, aptQueryBool)
    case 7:
        NATIVE_FUNCTION(g_rva0133836C, Va00CB2DD0)
    case 8: {
        if (m_value20) {
            void *item = m_value20->slot2C();
            if (item) {
                Rva00899560Value *v = new Rva008B2EF0(0x20, (unsigned)item);
                if (v->m_flags & 0x8000) return v;
                break;
            }
        }
        return g_bfmeFallbackDB;
    }
    case 9: {
        if (m_value20) {
            void *item = m_value20->slot30();
            if (item) {
                Rva00899560Value *v = new Rva008B2EF0(0x20, (unsigned)item);
                if (v->m_flags & 0x8000) return v;
                break;
            }
        }
        return g_bfmeFallbackDB;
    }
    case 10: {
        Rva008A9B00 *v = pooledString();
        ((Rva008B2EA0Node *)v)->append((char *)g_rva008B2EA0Base + 8);
        if (m_value20) {
            const void *text = m_value20->slot34();
            if (text) ((Rva008B2EA0Node *)v)->append((void *)text);
        }
        return v;
    }
    case 11:
        if (!m_value20) return g_bfmeFallbackDB;
        return pooledInteger(m_value20->slot3C());
    case 12: {
        Rva008A9B00 *v = pooledString();
        ((Rva008B2EA0Node *)v)->append((char *)g_rva008B2EA0Base + 8);
        if (m_value20) {
            const void *text = m_value20->slot40();
            if (text) ((Rva008B2EA0Node *)v)->append((void *)text);
        }
        return v;
    }
    case 13: {
        Rva00899560Value *v = g_bfmeFallbackDB;
        if (m_value20) {
            void *item = m_value20->slot48();
            if (item) {
                v = new Rva008B2EF0(0x20, (unsigned)item);
                if (v->m_flags & 0x8000) return v;
            }
        }
        return v;
    }
    case 14: {
        if (m_value20) {
            void *item = m_value20->slot4C();
            if (item) {
                Rva00899560Value *v = new Rva008B2EF0(0x20, (unsigned)item);
                if (v->m_flags & 0x8000) return v;
                break;
            }
        }
        return g_bfmeFallbackDB;
    }
    case 15:
        NATIVE_FUNCTION(g_rva01338370, Va00CB2DE0)
    case 16:
        NATIVE_FUNCTION(g_rva01338374, rva008B2EA0Walk)
    }
    }
    }
    return 0;
}

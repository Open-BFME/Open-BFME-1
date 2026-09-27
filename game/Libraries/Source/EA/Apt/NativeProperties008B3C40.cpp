// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// RVA 008B3C40: native property dispatch; split from the oversized 008B3AA0 dump.
// Evidence: targets/game/reverse/identity_evidence/008b3aa0-boundaries-and-008b3c40-callee.md
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
class BfmeS1082 {
public:
    virtual void slot00();
    virtual void slot04();
    unsigned flags;
};

struct Rva008995E0Value : Rva00899560Value {
    union { bool m_value; Rva008995E0Value *m_next; };
    __forceinline Rva008995E0Value(bool x) : Rva00899560Value(5), m_value(x) {}
};
extern Rva008995E0Value *Rva013387D4;
static __forceinline Rva008995E0Value *pooledBoolean(bool value) {
    Rva008995E0Value *v = Rva013387D4;
    if (v) {
        Rva013387D4 = v->m_next;
        g_rva8CD130IdleHook->addPooled(v);
        v->m_value = value;
        return v;
    }
    return new Rva008995E0Value(value);
}
struct StringBlock008B3C40 { unsigned short refs, length; };
struct String008B3C40 { StringBlock008B3C40 *data; };
extern StringBlock008B3C40 g_default012D5298;
class BfmeStrVKK { public: void bfmeTruncVKK(unsigned); };
class Rva008A9B00 {
public:
    static void *operator new(unsigned n) { return Rva008C5D70Alloc(n); }
    Rva008A9B00();
    static void operator delete(void *, unsigned);
    void *vtable;
    unsigned m_flags;
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
struct NativeSlots008B3C40 {
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0C();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1C();
    virtual void slot20();
    virtual void slot24();
    virtual void slot28();
    virtual void slot2C();
    virtual void slot30();
    virtual void slot34();
    virtual void slot38();
    virtual void slot3C();
    virtual void slot40();
    virtual void slot44();
    virtual void slot48();
    virtual void slot4C();
    virtual void slot50();
    virtual void slot54();
    virtual void * slot58();
    virtual void slot5C();
    virtual void slot60();
    virtual void slot64();
    virtual void * slot68();
    virtual void slot6C();
    virtual void slot70();
    virtual void slot74();
    virtual void slot78();
    virtual int slot7C();
    virtual void slot80();
    virtual int slot84();
    virtual void slot88();
    virtual void slot8C();
    virtual void slot90();
    virtual int slot94();
};
class NativeProperties008B3C40 {
public:
    void *field00;
    unsigned field04;
    char field08[0x18];
    NativeSlots008B3C40 *field20;
    void *lookup(NativeProperties008B3C40 *, String008B3C40 *);
};
class PropertyLookup008B2F50 {
public:
    Rva00899560Value *lookup(NativeProperties008B3C40 *, String008B3C40 *);
};
extern BfmeS1082 *g_bfmeS1082_0;
extern char Va00CB3A40[];
extern BfmeS1082 *g_bfmeS1082_1;
extern char Va00CB3A70[];
extern BfmeS1082 *g_bfmeS1082_2;
extern char Va00CB3AA0[];
extern BfmeS1082 *g_bfmeS1082_3;
extern char Va00CB3B70[];
void *NativeProperties008B3C40::lookup(NativeProperties008B3C40 *owner, String008B3C40 *key) {
    owner->field04 = (owner->field04 & ~0x3fu) | 0x20;
    Rva00899560Value *inherited = ((PropertyLookup008B2F50 *)this)->lookup(owner, key);
    owner->field04 = (owner->field04 & ~0x3fu) | 0x21;
    if (inherited && (inherited->m_flags & 0x8000)) return inherited;
    const R4Word *word = Rva008D5DC0((char *)key->data + 8, key->data->length);
    if (word) {
        NativeSlots008B3C40 *native = field20;
        switch (word->id) {
        case 100: {
            Rva008A9B00 *v = pooledString();
            ((Rva008B2EA0Node *)v)->append((char *)g_rva008B2EA0Base + 8);
            if (field20) {
                void *text = native->slot58();
                if (text) ((Rva008B2EA0Node *)v)->append(text);
            }
            return v;
        }
        case 103: {
            Rva008A9B00 *v = pooledString();
            ((Rva008B2EA0Node *)v)->append((char *)g_rva008B2EA0Base + 8);
            if (field20) {
                void *text = native->slot68();
                if (text) ((Rva008B2EA0Node *)v)->append(text);
            }
            return v;
        }
        case 104:
            if (!g_bfmeS1082_0) {
                g_bfmeS1082_0 = (BfmeS1082 *)new Rva00899FC0((int)Va00CB3A40);
                g_bfmeS1082_0->flags = (g_bfmeS1082_0->flags & 0xffffc07f) | 0x40;
                g_bfmeS1082_0->slot00();
            }
            return g_bfmeS1082_0;
        case 105:
            if (!g_bfmeS1082_1) {
                g_bfmeS1082_1 = (BfmeS1082 *)new Rva00899FC0((int)Va00CB3A70);
                g_bfmeS1082_1->flags = (g_bfmeS1082_1->flags & 0xffffc07f) | 0x40;
                g_bfmeS1082_1->slot00();
            }
            return g_bfmeS1082_1;
        case 106: return pooledBoolean(native->slot7C() != 0);
        case 107:
            if (!g_bfmeS1082_2) {
                g_bfmeS1082_2 = (BfmeS1082 *)new Rva00899FC0((int)Va00CB3AA0);
                g_bfmeS1082_2->flags = (g_bfmeS1082_2->flags & 0xffffc07f) | 0x40;
                g_bfmeS1082_2->slot00();
            }
            return g_bfmeS1082_2;
        case 108: return pooledBoolean(native->slot84() != 0);
        case 109:
            if (!g_bfmeS1082_3) {
                g_bfmeS1082_3 = (BfmeS1082 *)new Rva00899FC0((int)Va00CB3B70);
                g_bfmeS1082_3->flags = (g_bfmeS1082_3->flags & 0xffffc07f) | 0x40;
                g_bfmeS1082_3->slot00();
            }
            return g_bfmeS1082_3;
        case 112: return pooledInteger(native->slot94());
        }
    }
    return 0;
}

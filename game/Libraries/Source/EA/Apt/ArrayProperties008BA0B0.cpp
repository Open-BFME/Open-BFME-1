// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// RVA 008BA0B0: array property dispatch, callbacks, numeric indexing and table fallback.
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
const R4Word *Rva008B8AD0(const char *, unsigned);
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
class Rva008B8B80Releasable {
public:
    virtual void slot00();
    virtual void slot04();
    unsigned flags;
};
struct StringBuffer008BA0B0 { unsigned short field00, field02; char field04[4]; };
struct String008BA0B0 { StringBuffer008BA0B0 *field00; };
class BfmeTab1024 { public: int bfmeFind1024(int); };
class ArrayProperties008BA0B0 {
public:
    char field00[0x20];
    unsigned *field20;
    int field24, field28;
    void *lookup(ArrayProperties008BA0B0 *, String008BA0B0 *);
};
extern "C" long __cdecl strtol(const char *, char **, int);
extern void *g_bfmeResult1233;
extern Rva008B8B80Releasable *g_rva008B8B80_0;
extern char Va00CB9CC0[];
extern Rva008B8B80Releasable *g_rva008B8B80_1;
extern char Va00CB94F0[];
extern Rva008B8B80Releasable *g_rva008B8B80_2;
extern char Va00CB9020[];
extern Rva008B8B80Releasable *g_rva008B8B80_3;
extern char Va00CB96A0[];
extern Rva008B8B80Releasable *g_rva008B8B80_4;
extern char Va00CB9080[];
extern Rva008B8B80Releasable *g_rva008B8B80_5;
extern char Va00CB9780[];
extern Rva008B8B80Releasable *g_rva008B8B80_6;
extern char Va00CB9330[];
extern Rva008B8B80Releasable *g_rva008B8B80_7;
extern char Va00CB9930[];
extern Rva008B8B80Releasable *g_rva008B8B80_8;
extern char Va00CB9A40[];
extern Rva008B8B80Releasable *g_rva008B8B80_9;
extern char Va00CB9F30[];
extern Rva008B8B80Releasable *g_rva008B8B80_10;
extern char Va00CB99B0[];
void *ArrayProperties008BA0B0::lookup(ArrayProperties008BA0B0 *owner, String008BA0B0 *key) {
    if (owner) {
        const R4Word *word = Rva008B8AD0((char *)key->field00 + 8, key->field00->field02);
        if (word) {
            switch (word->id) {
            case 1: return pooledInteger(field28);
            case 2:
                if (!g_rva008B8B80_0) {
                    g_rva008B8B80_0 = (Rva008B8B80Releasable *)new Rva00899FC0((int)Va00CB9CC0);
                    g_rva008B8B80_0->flags = (g_rva008B8B80_0->flags & 0xffffc07f) | 0x40;
                    g_rva008B8B80_0->slot00();
                }
                return g_rva008B8B80_0;
            case 3:
                if (!g_rva008B8B80_1) {
                    g_rva008B8B80_1 = (Rva008B8B80Releasable *)new Rva00899FC0((int)Va00CB94F0);
                    g_rva008B8B80_1->flags = (g_rva008B8B80_1->flags & 0xffffc07f) | 0x40;
                    g_rva008B8B80_1->slot00();
                }
                return g_rva008B8B80_1;
            case 13:
                if (!g_rva008B8B80_1) {
                    g_rva008B8B80_1 = (Rva008B8B80Releasable *)new Rva00899FC0((int)Va00CB94F0);
                    g_rva008B8B80_1->flags = (g_rva008B8B80_1->flags & 0xffffc07f) | 0x40;
                    g_rva008B8B80_1->slot00();
                }
                return g_rva008B8B80_1;
            case 4:
                if (!g_rva008B8B80_2) {
                    g_rva008B8B80_2 = (Rva008B8B80Releasable *)new Rva00899FC0((int)Va00CB9020);
                    g_rva008B8B80_2->flags = (g_rva008B8B80_2->flags & 0xffffc07f) | 0x40;
                    g_rva008B8B80_2->slot00();
                }
                return g_rva008B8B80_2;
            case 5:
                if (!g_rva008B8B80_3) {
                    g_rva008B8B80_3 = (Rva008B8B80Releasable *)new Rva00899FC0((int)Va00CB96A0);
                    g_rva008B8B80_3->flags = (g_rva008B8B80_3->flags & 0xffffc07f) | 0x40;
                    g_rva008B8B80_3->slot00();
                }
                return g_rva008B8B80_3;
            case 6:
                if (!g_rva008B8B80_4) {
                    g_rva008B8B80_4 = (Rva008B8B80Releasable *)new Rva00899FC0((int)Va00CB9080);
                    g_rva008B8B80_4->flags = (g_rva008B8B80_4->flags & 0xffffc07f) | 0x40;
                    g_rva008B8B80_4->slot00();
                }
                return g_rva008B8B80_4;
            case 7:
                if (!g_rva008B8B80_5) {
                    g_rva008B8B80_5 = (Rva008B8B80Releasable *)new Rva00899FC0((int)Va00CB9780);
                    g_rva008B8B80_5->flags = (g_rva008B8B80_5->flags & 0xffffc07f) | 0x40;
                    g_rva008B8B80_5->slot00();
                }
                return g_rva008B8B80_5;
            case 8:
                if (!g_rva008B8B80_6) {
                    g_rva008B8B80_6 = (Rva008B8B80Releasable *)new Rva00899FC0((int)Va00CB9330);
                    g_rva008B8B80_6->flags = (g_rva008B8B80_6->flags & 0xffffc07f) | 0x40;
                    g_rva008B8B80_6->slot00();
                }
                return g_rva008B8B80_6;
            case 9:
                if (!g_rva008B8B80_7) {
                    g_rva008B8B80_7 = (Rva008B8B80Releasable *)new Rva00899FC0((int)Va00CB9930);
                    g_rva008B8B80_7->flags = (g_rva008B8B80_7->flags & 0xffffc07f) | 0x40;
                    g_rva008B8B80_7->slot00();
                }
                return g_rva008B8B80_7;
            case 10:
                if (!g_rva008B8B80_8) {
                    g_rva008B8B80_8 = (Rva008B8B80Releasable *)new Rva00899FC0((int)Va00CB9A40);
                    g_rva008B8B80_8->flags = (g_rva008B8B80_8->flags & 0xffffc07f) | 0x40;
                    g_rva008B8B80_8->slot00();
                }
                return g_rva008B8B80_8;
            case 11:
                if (!g_rva008B8B80_9) {
                    g_rva008B8B80_9 = (Rva008B8B80Releasable *)new Rva00899FC0((int)Va00CB9F30);
                    g_rva008B8B80_9->flags = (g_rva008B8B80_9->flags & 0xffffc07f) | 0x40;
                    g_rva008B8B80_9->slot00();
                }
                return g_rva008B8B80_9;
            case 12:
                if (!g_rva008B8B80_10) {
                    g_rva008B8B80_10 = (Rva008B8B80Releasable *)new Rva00899FC0((int)Va00CB99B0);
                    g_rva008B8B80_10->flags = (g_rva008B8B80_10->flags & 0xffffc07f) | 0x40;
                    g_rva008B8B80_10->slot00();
                }
                return g_rva008B8B80_10;
            }
        }
    }
    char *end = 0;
    int index = strtol((char *)key->field00 + 8, &end, 10);
    int length = key->field00->field02;
    if (length > 0 && end == (char *)key->field00 + length + 8) {
        if (index >= 0 && index < owner->field28) {
            void *value = (void *)(owner->field20[index] & ~1u);
            if (value) return value;
        }
        return g_bfmeResult1233;
    }
    return (void *)((BfmeTab1024 *)(field00 + 8))->bfmeFind1024((int)key);
}

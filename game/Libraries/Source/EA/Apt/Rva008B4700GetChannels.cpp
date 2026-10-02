// cl: /DNDEBUG /MD /EHsc
// Retail RVA 0x008B4700: builds a type-0x1B object holding the eight channel
// values that the matched 0x008B4480 (aptApplyChannels008B4480) reads back
// through the same eight keys: fields +0x28..+0x34 scaled by 100 and +0x38..+0x44
// scaled by 255, the inverse of that setter's 0.01 and 1/255 factors.  Pooled
// integer and headered-object models follow the matched NativeProperties008B3C40
// and aptRelativeRect008B02A0; identities stay address-derived.
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

class BfmeItemDX;
void bfmePush(BfmeItemDX *);
// Retail unwind funclet 0x00C58CE0 frees the half-built object with
// (storage, 0x20) through the sized headered delete at 0x008A3160.
class Rva008A3160HeaderedDelete { public: static void operator delete(void *storage, unsigned int size); };
class Rva00899F00Base : public Rva008A3160HeaderedDelete {
public:
    Rva00899F00Base(unsigned, int);
    void *operator new(unsigned size) {
        char *raw = (char *)Rva008C5D70Alloc(size + 8);
        char *p = raw + 8;
        bfmePush((BfmeItemDX *)p);
        return p;
    }
    char m_bytes[32];
};
class Rva8D0D80String;
class Rva8D0D80Value;
class Rva8D0D80Table { public: void add(Rva8D0D80String *, Rva8D0D80Value *); };

struct Value008B4700 {
    int m_f0;
    unsigned m_flags;
    char pad08[0x20];
    float m_f28, m_f2C, m_f30, m_f34, m_f38, m_f3C, m_f40, m_f44;
};
struct Owner008B4700 { char pad00[0x20]; Value008B4700 *m_f20; };
// 0x013379BC is the fallback value database pointer, defined as AptValue *
// by Bfme5AppendFallback8CAFF0.cpp (?g_bfmeFallbackDB@@3PAVAptValue@@A).
class AptValue;
extern AptValue *g_bfmeFallbackDB;
extern int key01338668, key01338670, key01338568, key0133856C, key01338514, key01338518, key013384F4, key013384F8;

Rva00899F00Base *aptGetChannels008B4700(Owner008B4700 *self, int argc)
{
    if (argc > 0)
        return (Rva00899F00Base *)g_bfmeFallbackDB;
    Value008B4700 *v = self->m_f20;
    if (v->m_flags & 0x8000)
    {
    Rva00899F00Base *result = new Rva00899F00Base(0x1b, 8);
    Rva8D0D80Value *first = (Rva8D0D80Value *)pooledInteger((int)(v->m_f2C * 100.0f));
    Rva8D0D80Table *table = (Rva8D0D80Table *)((char *)result + 8);
    table->add((Rva8D0D80String *)&key01338668, first);
    table->add((Rva8D0D80String *)&key01338568, (Rva8D0D80Value *)pooledInteger((int)(v->m_f30 * 100.0f)));
    table->add((Rva8D0D80String *)&key01338514, (Rva8D0D80Value *)pooledInteger((int)(v->m_f34 * 100.0f)));
    table->add((Rva8D0D80String *)&key013384F4, (Rva8D0D80Value *)pooledInteger((int)(v->m_f28 * 100.0f)));
    table->add((Rva8D0D80String *)&key01338670, (Rva8D0D80Value *)pooledInteger((int)(v->m_f3C * 255.0f)));
    table->add((Rva8D0D80String *)&key0133856C, (Rva8D0D80Value *)pooledInteger((int)(v->m_f40 * 255.0f)));
    table->add((Rva8D0D80String *)&key01338518, (Rva8D0D80Value *)pooledInteger((int)(v->m_f44 * 255.0f)));
    table->add((Rva8D0D80String *)&key013384F8, (Rva8D0D80Value *)pooledInteger((int)(v->m_f38 * 255.0f)));
    return result;
    }
    return (Rva00899F00Base *)g_bfmeFallbackDB;
}

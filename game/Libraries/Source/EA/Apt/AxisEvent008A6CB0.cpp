// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// RVA 008A6CB0: builds an Apt result with event id and axis-value properties.
// Identity remains address-derived. Retail: 1465 bytes, RET, no argument reads.
struct Rva00899560Value;
struct Rva00899560Pool {
    int m_capacity, m_count;
    Rva00899560Value **m_items;
    template<class T> __forceinline void addPooled(T *v) {
        int &count = m_count;
        if (count >= m_capacity) { v->m_flags &= 0xbfffffff; return; }
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
        unsigned flags = (((m_flags & ~0x3f) | type) & 0xf000803f) | 0x8000;
        m_flags = flags;
        if (type != 0x1c && type != 0xa) {
            m_flags = flags | 0x40000000;
            g_rva8CD130IdleHook->addPooled(this);
        } else m_flags = flags & 0xbfffffff;
    }
    static void *operator new(unsigned n) { return Rva008C5D70Alloc(n); }
};
struct Rva008A1110Value : Rva00899560Value {
    union { int m_value; Rva008A1110Value *m_next; };
    __forceinline Rva008A1110Value(int value) : Rva00899560Value(7), m_value(value) {}
};
struct Rva008A4C00Value : Rva00899560Value {
    union { float m_value; Rva008A4C00Value *m_next; };
    __forceinline Rva008A4C00Value(float value) : Rva00899560Value(6), m_value(value) {}
};
// The pooled-integer free head at 0x013387D0 is the defining Rva008D2A10 list
// (see game/GameEngine/Source/Common/Rva008D2A10Link.cpp); it has no header,
// so forward-declare it and spell the reference with its defining type.
class Rva008D2A10;
extern Rva008D2A10 *g_rva008D2A10;
class Rva008D29A0;
extern Rva008D29A0 *g_rva008D29A0;
static __forceinline Rva008A1110Value *makeInteger(int value) {
    Rva008A1110Value *object = (Rva008A1110Value *)g_rva008D2A10;
    if (object) {
        g_rva008D2A10 = (Rva008D2A10 *)object->m_next;
        g_rva8CD130IdleHook->addPooled(object);
        object->m_value = value;
        return object;
    }
    return new Rva008A1110Value(value);
}
static __forceinline Rva008A4C00Value *makeFloat(float value) {
    Rva008A4C00Value *object = (Rva008A4C00Value *)g_rva008D29A0;
    if (object) {
        g_rva008D29A0 = (Rva008D29A0 *)object->m_next;
        g_rva8CD130IdleHook->addPooled(object);
        object->m_value = value;
        return object;
    }
    return new Rva008A4C00Value(value);
}
class BfmeItemDX;
void bfmePush(BfmeItemDX *);
class Rva00897670HeaderedDelete {
public:
    static void operator delete(void *, unsigned);
};
class Rva00899F00Base : public Rva00897670HeaderedDelete {
public:
    Rva00899F00Base(unsigned, int);
    static void *operator new(unsigned size) {
        char *raw = (char *)Rva008C5D70Alloc(size + 8);
        char *p = raw + 8;
        bfmePush((BfmeItemDX *)p);
        return p;
    }
    char bytes[32];
};
struct BfmeStringData3AF0 { unsigned short m_refCount, m_length, m_capacity, m_unknown06; };
struct BfmeStringPool3AF0 { void *m_unknown00; void (__cdecl *free)(void *); };
extern BfmeStringPool3AF0 *g_rva01337A30AllocPair;
class BfmeStrVKI {
public:
    void bfmeSetVKI(const char *);
    __forceinline BfmeStrVKI(const char *text) { bfmeSetVKI(text); }
    __forceinline ~BfmeStrVKI() {
        BfmeStringData3AF0 *old = m_data;
        if (--old->m_refCount == 0) g_rva01337A30AllocPair->free(old);
    }
    __forceinline BfmeStrVKI &operator=(const BfmeStrVKI &other) {
        ++other.m_data->m_refCount;
        BfmeStringData3AF0 *old = m_data;
        if (--old->m_refCount == 0) g_rva01337A30AllocPair->free(old);
        m_data = other.m_data;
        return *this;
    }
    BfmeStringData3AF0 *m_data;
};
class Rva8D0D80String;
class Rva8D0D80Value;
class Rva8D0D80Table { public: void add(Rva8D0D80String *, Rva8D0D80Value *); };
extern unsigned Rva008A5250LastKey;
// retail 0x013377D8; defining spelling (BfmePicker1284.cpp), declared
// incomplete here because only raw fields at +0x127c.. are read.
struct BfmePickWorld1284;
extern BfmePickWorld1284 *g_bfmeHolderBU;
extern char key0133853C[];
Rva00899F00Base *axisEvent008A6CB0() {
    unsigned event = 0x1f7;
    unsigned id = 0;
    if (Rva008A5250LastKey) {
        event = Rva008A5250LastKey >> 17;
        id = (Rva008A5250LastKey >> 2) & 0xff;
    }
    id -= 2;
    Rva00899F00Base *result = new Rva00899F00Base(0x1b, 8);
    Rva8D0D80Value *integer = (Rva8D0D80Value *)makeInteger(id);
    Rva8D0D80Table *table = (Rva8D0D80Table *)((char *)result + 8);
    table->add((Rva8D0D80String *)key0133853C, integer);
    BfmeStrVKI key("fXAxisValue");
    if (event == 0x1f5) {
        Rva8D0D80Value *x = (Rva8D0D80Value *)makeFloat(*(float *)((char *)g_bfmeHolderBU + 0x127c));
        Rva8D0D80Value *y = (Rva8D0D80Value *)makeFloat(*(float *)((char *)g_bfmeHolderBU + 0x1280));
        table->add((Rva8D0D80String *)&key, x);
        key = "fYAxisValue";
        table->add((Rva8D0D80String *)&key, y);
    } else if (event == 0x1f6) {
        Rva8D0D80Value *x = (Rva8D0D80Value *)makeFloat(*(float *)((char *)g_bfmeHolderBU + 0x128c));
        Rva8D0D80Value *y = (Rva8D0D80Value *)makeFloat(*(float *)((char *)g_bfmeHolderBU + 0x1290));
        key = "fXAxisValue";
        table->add((Rva8D0D80String *)&key, x);
        key = "fYAxisValue";
        table->add((Rva8D0D80String *)&key, y);
    }
    return result;
}

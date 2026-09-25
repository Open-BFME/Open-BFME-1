// ?rva008AF330@@YAPAVRva008A4C00Value@@PAX@Z
// RVA 008AF330: convert an eligible pooled string through the callback at
// VA 013378B8, then return a pooled float value. Retail independently proves
// the callback ABI as int __cdecl(const char*, int): two pushed words,
// caller cleanup, EAX spilled and converted with FILD before a float store.
// Native value constructors preserve vtables 01135D68 and 01136698. The
// typed pool template also preserves the distinct base/derived alias contexts.
// The source kind and callback remain address-qualified: no guessed API name.
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

struct BfmeStringData3AF0 {
    unsigned short m_refCount, m_length, m_capacity, m_flags;
};
struct BfmeStringPool3AF0 {
    void *m_unused;
    void (__cdecl *free)(void *);
};
extern BfmeStringData3AF0 g_bfmeDefaultString1284;
extern BfmeStringPool3AF0 *g_bfmeStringPool1284;

class BfmeStrVKJ {
public:
    BfmeStrVKJ() : m_data(&g_bfmeDefaultString1284) { ++m_data->m_refCount; }
    BfmeStrVKJ *bfmeAssignVKJ(const BfmeStrVKJ &other);
    ~BfmeStrVKJ() {
        BfmeStringData3AF0 *data = m_data;
        if (--data->m_refCount == 0) g_bfmeStringPool1284->free(data);
    }
    BfmeStringData3AF0 *m_data;
};

class Rva00899560Value;
struct Rva00899560Pool {
    int m_capacity, m_count;
    Rva00899560Value **m_items;
    template<class V> __forceinline void addPooled(V *v) {
        int &count=m_count;
        if(count>=m_capacity) {v->m_flags &= 0xBFFFFFFF;return;}
        m_items[count]=v;
        ++count;
    }
};
extern Rva00899560Pool *g_rva8CD130IdleHook;
class Rva00899560Value {
public:
    virtual ~Rva00899560Value();
    unsigned int m_flags;
    __forceinline Rva00899560Value(int type) {
        unsigned int flags = (((m_flags & ~0x3f) | type) & 0xF000803F) | 0x8000;
        m_flags = flags;
        if (type != 0x1c && type != 0xa) {
            m_flags = flags | 0x40000000;
            g_rva8CD130IdleHook->addPooled(this);
        } else {
            m_flags = flags & 0xBFFFFFFF;
        }
    }
};
extern void *(__cdecl *Rva008C5D70Alloc)(unsigned int);

class Rva008A4C00Value : public Rva00899560Value {
public:
    static void *operator new(unsigned int bytes) { return Rva008C5D70Alloc(bytes); }
    __forceinline Rva008A4C00Value(float value) : Rva00899560Value(6), m_value(value) {}
    union { Rva008A4C00Value *m_next; float m_value; };
};

extern Rva008A4C00Value *Rva008AF330Head;
extern int (__cdecl *Rva013378B8)(const char *, int);

static __forceinline Rva008A4C00Value *makeValue(float value)
{
    Rva008A4C00Value *result = (Rva008A4C00Value *)Rva008AF330Head;
    if (result) {
        Rva008AF330Head = result->m_next;
        g_rva8CD130IdleHook->addPooled(result);
        result->m_value = value;
        return result;
    }
    return new Rva008A4C00Value(value);
}

Rva008A4C00Value *rva008AF330(void *owner)
{
    BfmeStrVKJ text;
    unsigned int bits = *(unsigned int *)((char *)owner + 4);
    int type = bits & 0x3f;
    if (type >= 0x0c && type <= 0x13 && !((unsigned char)(~(bits >> 15)) & 1)) {
        if (type == 0x12) {
            void *source = *(void **)((char *)owner + 0x50);
            source = *(void **)((char *)source + 0x34);
            text.bfmeAssignVKJ(*(BfmeStrVKJ *)((char *)source + 4));
        }
    }
    float value = 0.0f;
    bits = *(unsigned int *)((char *)owner + 4);
    type = bits & 0x3f;
    if ((unsigned char)type == 0x12 && !((unsigned char)(~(bits >> 15)) & 1))
        value = (float)Rva013378B8((const char *)text.m_data + 8, 0);

    return makeValue(value);
}

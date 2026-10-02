// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// RVA 008C8500: mixed-value addition. Keep the verified static 008C6C20 helper
// in this TU: VC7.1 uses ECX plus one caller-cleaned stack argument for it.
// Both the 817-byte caller and the copied 413-byte helper were probed exact.

struct BfmeStringData3AF0
{
    unsigned short m_refCount, m_length, m_capacity, m_unknown06;
};

struct BfmeStringPool3AF0
{
    void *m_unknown00;
    void (__cdecl *free)(void *);
};

extern BfmeStringData3AF0 g_bfmeDefaultString1284;
extern BfmeStringPool3AF0 *g_bfmeStringPool1284;
extern BfmeStringData3AF0 *g_stringBlock01338724;

class Rva8CD130String
{
public:
    Rva8CD130String()
    {
        m_data = &g_bfmeDefaultString1284;
        ++m_data->m_refCount;
    }

    ~Rva8CD130String()
    {
        BfmeStringData3AF0 *old = m_data;
        if (--old->m_refCount == 0)
            g_bfmeStringPool1284->free(old);
    }

    void assign(const Rva8CD130String &other)
    {
        ++other.m_data->m_refCount;
        BfmeStringData3AF0 *old = m_data;
        if (--old->m_refCount == 0)
            g_bfmeStringPool1284->free(old);
        m_data = other.m_data;
    }

    BfmeStringData3AF0 *m_data;
};

class BfmeStrVKK
{
public:
    void bfmeTruncVKK(unsigned int);
};

class BfmeStrVKJ
{
public:
    BfmeStrVKJ *bfmeAssignVKJ(const BfmeStrVKJ &);
};

class Rva8CD130Value
{
public:
    void getName(Rva8CD130String *);
    virtual void slot00();
    virtual void release();
    unsigned m_flags;
    BfmeStringData3AF0 *m_data;
    char m_unknown0C[0x14];
    Rva8CD130Value *m_indirect;

    bool isUndefined() const
    {
        return ((unsigned char)~(m_flags >> 15) & 1) != 0;
    }

    bool isString() const
    {
        return ((m_flags & 63) == 1 || (m_flags & 63) == 42) && !isUndefined();
    }

    __forceinline bool isType(int t) const { return (m_flags & 63) == t && !isUndefined(); }

    bool maxRefCountHit() const
    {
        return ((m_flags >> 30) & 1) != 0;
    }

    Rva8CD130String &string()
    {
        return *(Rva8CD130String *)&(((m_flags & 63) == 1 ? this : m_indirect)->m_data);
    }
};

struct Rva008C3B60Node
{
    void *m_unknown00;
    unsigned m_flags;
    BfmeStringData3AF0 *m_data;
    Rva008C3B60Node *m_next;
};

struct Rva00899560Pool
{
    int m_capacity, m_count;
    Rva008C3B60Node **m_items;

    void add(Rva008C3B60Node *node)
    {
        int &count = m_count;
        if (count >= m_capacity)
            node->m_flags &= 0xbfffffff;
        else
        {
            m_items[count] = node;
            ++count;
        }
    }
};

extern Rva008C3B60Node *Rva008C3B60Head;
// 0x01337810: the Apt GC-root registry vector pointer, defined in
// game/Libraries/Source/Apt/Apt.cpp. The view type here is this TU's own.
extern Rva00899560Pool *g_rva01337810GcRoots;
extern void *(__cdecl *Rva008C5D70Alloc)(unsigned);

class Rva008A9B00
{
public:
    static void *operator new(unsigned n) { return Rva008C5D70Alloc(n); }
    static void operator delete(void *, unsigned);
    Rva008A9B00();
    void *m_unknown00;
    unsigned m_flags;
    BfmeStringData3AF0 *m_data;
    Rva008A9B00 *m_next;
};

class Rva008B2EA0Node
{
public:
    void append(void *);
};

static __forceinline Rva008C3B60Node *CreateStringRva008C6C20()
{
    Rva008C3B60Node *node = Rva008C3B60Head;
    if (node)
    {
        Rva008C3B60Head = node->m_next;
        g_rva01337810GcRoots->add(node);
        if (node->m_data != &g_bfmeDefaultString1284)
            ((BfmeStrVKK *)&node->m_data)->bfmeTruncVKK(0);
        return node;
    }
    return (Rva008C3B60Node *)new Rva008A9B00;
}

// ?StringConcatRva008C6C20@@YAPAURva008C3B60Node@@PAVRva8CD130Value@@0@Z
static __declspec(noinline) Rva008C3B60Node *StringConcatRva008C6C20(
    Rva8CD130Value *first, Rva8CD130Value *second)
{
    Rva008C3B60Node *node = CreateStringRva008C6C20();
    if (first->isString())
        ((Rva8CD130String *)&node->m_data)->assign(first->string());
    else
        first->getName((Rva8CD130String *)&node->m_data);
    if (second->isString())
        ((BfmeStrVKJ *)&node->m_data)->bfmeAssignVKJ(*(BfmeStrVKJ *)&second->string());
    else
    {
        Rva8CD130String text;
        second->getName(&text);
        ((BfmeStrVKJ *)&node->m_data)->bfmeAssignVKJ(*(BfmeStrVKJ *)&text);
    }
    return node;
}

class AptValue { public: int toInteger() const; float toNumber(); };
class AptInteger { public: static AptInteger *Create(int); };
AptValue *Rva008A4EA0MakeFloat(float);
extern AptValue *g_bfmeFallbackDB;
unsigned int AptGetSwfVersion();
Rva008B2EA0Node *rva008B2EA0Create();
struct Stack008C8500 {
    int m_count, m_capacity;
    Rva8CD130Value **m_values;
    __forceinline void pop(int n) {
        for(int i=1;i<=n;++i) {
            Rva8CD130Value *v=m_values[m_count-i];
            if (!v->maxRefCountHit()) v->release();
        }
        m_count-=n;
    }
    __forceinline void push(Rva8CD130Value *v) {
        m_values[m_count++]=v;
        if(!v->maxRefCountHit()) v->slot00();
    }
};
void AddValues008C8500(Stack008C8500 *state) {
    Rva8CD130Value *under=state->m_values[state->m_count-2];
    Rva8CD130Value *top=state->m_values[state->m_count-1];
    int version=AptGetSwfVersion();
    if (top->isString() || under->isString()) {
        if(version==7) {
            Rva008B2EA0Node *created=rva008B2EA0Create();
            created->append(g_stringBlock01338724+1);
            if(top->isUndefined()) top=(Rva8CD130Value *)created;
            if(under->isUndefined()) under=(Rva8CD130Value *)created;
        }
        Rva008C3B60Node *result=StringConcatRva008C6C20(under,top);
        state->pop(2); state->push((Rva8CD130Value *)result);
    } else if ((top->isType(7) || under->isType(7)) && !top->isType(6) && !under->isType(6)) {
        if(version==7 && (top->isUndefined() || under->isUndefined())) {
            state->pop(2); state->push((Rva8CD130Value *)g_bfmeFallbackDB); return;
        }
        int right=((AptValue *)top)->toInteger();
        int left=((AptValue *)under)->toInteger();
        state->pop(2);
        state->push((Rva8CD130Value *)AptInteger::Create(left+right));
    } else {
        if(version==7 && (top->isUndefined() || under->isUndefined())) {
            state->pop(2); state->push((Rva8CD130Value *)g_bfmeFallbackDB); return;
        }
        float right=((AptValue *)top)->toNumber();
        float left=((AptValue *)under)->toNumber();
        state->pop(2);
        state->push((Rva8CD130Value *)Rva008A4EA0MakeFloat(left+right));
    }
}

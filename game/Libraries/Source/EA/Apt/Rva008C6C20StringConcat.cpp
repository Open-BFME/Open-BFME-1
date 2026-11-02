// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Both bodies retain address-derived identities; the caller is the complete 174-byte retail body.

struct BfmeStringData3AF0
{
    unsigned short m_refCount, m_length, m_capacity, m_unknown06;
};

struct BfmeStringPool3AF0
{
    void *m_unknown00;
    void (__cdecl *free)(void *);
};

class EAStringC { public: class StringDataC; };
extern EAStringC::StringDataC g_rva012D5298Empty;	// shared empty string block 0x012D5298
static inline BfmeStringData3AF0 *sharedEmptyString012D5298()
{
	return (BfmeStringData3AF0 *)&g_rva012D5298Empty;
}
extern BfmeStringPool3AF0 *g_rva01337A30AllocPair;
extern BfmeStringData3AF0 *g_stringBlock01338724;

class Rva8CD130String
{
public:
    // Retain inline code without emitting another shared constructor copy.
    __declspec(dllimport) __forceinline Rva8CD130String()
    {
        m_data = sharedEmptyString012D5298();
        ++m_data->m_refCount;
    }

    ~Rva8CD130String()
    {
        BfmeStringData3AF0 *old = m_data;
        if (--old->m_refCount == 0)
            g_rva01337A30AllocPair->free(old);
    }

    void assign(const Rva8CD130String &other)
    {
        ++other.m_data->m_refCount;
        BfmeStringData3AF0 *old = m_data;
        if (--old->m_refCount == 0)
            g_rva01337A30AllocPair->free(old);
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
        return ((m_flags >> 15) & 1) == 0;
    }

    bool isString() const
    {
        return ((m_flags & 63) == 1 || (m_flags & 63) == 42) && !isUndefined();
    }

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

extern Rva008C3B60Node *g_rva01338478NodeHead;
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
    Rva008C3B60Node *node = g_rva01338478NodeHead;
    if (node)
    {
        g_rva01338478NodeHead = node->m_next;
        g_rva01337810GcRoots->add(node);
        if (node->m_data != sharedEmptyString012D5298())
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

struct Rva008C7C80State
{
    int m_count;
    int m_unknown04;
    Rva8CD130Value **m_values;
};

extern unsigned int AptGetSwfVersion();
extern Rva008B2EA0Node *rva008B2EA0Create();

// ?Rva008C7C80@@YAXPAURva008C7C80State@@@Z
void Rva008C7C80(Rva008C7C80State *state)
{
    Rva8CD130Value *first = state->m_values[state->m_count - 2];
    Rva8CD130Value *second = state->m_values[state->m_count - 1];
    if (AptGetSwfVersion() == 7)
    {
        Rva008C3B60Node *created = (Rva008C3B60Node *)rva008B2EA0Create();
        ((Rva008B2EA0Node *)created)->append(g_stringBlock01338724 + 1);
        if (second->isUndefined())
            second = (Rva8CD130Value *)created;
        if (first->isUndefined())
            first = (Rva8CD130Value *)created;
    }
    Rva008C3B60Node *result = StringConcatRva008C6C20(first, second);

    int index = 1;
    do
    {
        Rva8CD130Value *old = state->m_values[state->m_count - index];
        if (!old->maxRefCountHit())
            old->release();
        ++index;
    } while (index <= 2);

    state->m_count -= 2;
    state->m_values[state->m_count] = (Rva8CD130Value *)result;
    ++state->m_count;
    Rva8CD130Value *value = (Rva8CD130Value *)result;
    if (!value->maxRefCountHit())
        value->slot00();
}

// Retail 0x008C3C00 (510 bytes): the Apt string-pool lookup-or-insert that the
// action-stream parser 0x008CBDF0 calls. Open BFME 2 59e3f8f8
// Code/Libraries/Source/EA/Apt/Rva0070DBB0StringPool.cpp (its StringPool
// GetFromPool) supplies the flow; BFME 1 has no usage counters, inlines the
// lowercase FNV hash (hashLower 0x0089DC90) and this unit's string create.
class BfmeStrVKI
{
public:
    void bfmeSetVKI(const char *);
};

class BfmeThing929G
{
public:
    void bfmeInit929G();
};

class Rva008C3C00Text
{
public:
    __forceinline Rva008C3C00Text(const char *text) { ((BfmeStrVKI *)this)->bfmeSetVKI(text); }
    __forceinline ~Rva008C3C00Text()
    {
        BfmeStringData3AF0 *old = m_data;
        if (--old->m_refCount == 0)
            g_rva01337A30AllocPair->free(old);
    }
    BfmeStringData3AF0 *m_data;
};

extern "C" int __cdecl strcmp(const char *, const char *);
#pragma intrinsic(strcmp)

static __forceinline unsigned short hashLowerRva008C3C00(const char *text)
{
    unsigned int hash = 0x811c9dc5;
    const char *s = text;
    for (;;) {
        int c = *s;
        if (!c)
            break;
        ++s;
        if (c <= 0x5a && c >= 0x41)
            c += 0x20;
        hash = (hash ^ c) * 16777619;
    }
    if ((unsigned short)hash == 0)
        return 0x4567;
    return (unsigned short)hash;
}

// Retail 0x01338470/0x01338474 are the recorded string-pool bucket table
// and bucket count.
class BfmeNode3AF0;
extern BfmeNode3AF0 **g_bfmeHashArr3AF0;
extern int g_bfmeHashCount3AF0;
#define g_rva008C3C00Buckets ((Rva008C3B60Node **&)g_bfmeHashArr3AF0)

struct Rva008C3C00VNode
{
    virtual void addRef();
};

Rva008C3B60Node *rva008C3C00(const char *text)
{
    unsigned short hash = hashLowerRva008C3C00(text);
    unsigned short bucket = (unsigned short)((int)hash % g_bfmeHashCount3AF0);
    for (Rva008C3B60Node *node = g_rva008C3C00Buckets[bucket]; node; node = node->m_next)
    {
        if (node->m_data->m_unknown06 == hash && strcmp((const char *)(node->m_data + 1), text) == 0)
        {
            if ((node->m_flags & 0x3fc0) != 0x3fc0)
                node->m_flags += 0x40;
            return node;
        }
    }
    Rva008C3B60Node *node = CreateStringRva008C6C20();
    {
        Rva008C3C00Text temp(text);
        ((Rva8CD130String *)&node->m_data)->assign(*(Rva8CD130String *)&temp);
    }
    ((BfmeThing929G *)&node->m_data)->bfmeInit929G();
    node->m_next = g_rva008C3C00Buckets[bucket];
    g_rva008C3C00Buckets[bucket] = node;
    ((Rva008C3C00VNode *)node)->addRef();
    node->m_flags += 0x40;
    return node;
}

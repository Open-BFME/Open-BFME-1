// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail 008C7D30, 433 bytes; address-derived name, not recovered identity.
// Layouts and hub ABI: docs/analysis/0x008985c0.md, sections B/C/E.
// +DD calls the landed char-input setter at 008927C0. +128 appends text
// through 0089EA60 (ECX handle, one char pointer, EAX receiver, ret4).

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

class BfmeStrVKI
{
public:
    void bfmeSetVKI(const char *);
};

class Rva8CD130String
{
public:
    Rva8CD130String(const char *text)
    {
        ((BfmeStrVKI *)this)->bfmeSetVKI(text);
    }
    Rva8CD130String &rva0089EA60Append(const char *);

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

    bool maxRefCountHit() const { return ((m_flags >> 30) & 1) != 0; }
    bool isUndefined() const { return ((unsigned char)~(m_flags >> 15) & 1) != 0; }
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
extern Rva00899560Pool *g_rva8CD130IdleHook;
extern void *(__cdecl *Rva008C5D70Alloc)(unsigned);

class Rva008A9B00
{
public:
    static void *operator new(unsigned n) { return Rva008C5D70Alloc(n); }
    Rva008A9B00();
    void *m_unknown00;
    unsigned m_flags;
    BfmeStringData3AF0 *m_data;
    Rva008A9B00 *m_next;
};

static __forceinline Rva008C3B60Node *CreateStringRva008C7D30()
{
    Rva008C3B60Node *node = Rva008C3B60Head;
    if (node)
    {
        Rva008C3B60Head = node->m_next;
        g_rva8CD130IdleHook->add(node);
        if (node->m_data != &g_bfmeDefaultString1284)
            ((BfmeStrVKK *)&node->m_data)->bfmeTruncVKK(0);
        return node;
    }
    return (Rva008C3B60Node *)new Rva008A9B00;
}

class Rva008B2EA0Node
{
public:
    void append(void *);
};

struct TraceStateRva008C7D30
{
    int m_count, m_capacity;
    Rva8CD130Value **m_values;
};

int Rva00892370Get();

void TraceRva008C7D30(TraceStateRva008C7D30 *state)
{
    Rva8CD130Value *value = state->m_values[state->m_count - 1];
    Rva8CD130String text;
    Rva008C3B60Node *fallback;
    if (Rva00892370Get() == 7 && value->isUndefined())
    {
        fallback = CreateStringRva008C7D30();
        // The global holds a string block, whose characters begin at +8.
        ((Rva008B2EA0Node *)fallback)->append((char *)*(void **)0x01338724 + 8);
        ((Rva8CD130Value *)fallback)->getName(&text);
        if (fallback)
            goto converted;
    }
    value->getName(&text);

converted:
    Rva8CD130String line("AptTrace: ");
    ((BfmeStrVKJ *)&line)->bfmeAssignVKJ(*(BfmeStrVKJ *)&text);
    line.rva0089EA60Append("\n");
    (*(void (__cdecl **)(const char *, ...))0x0133783c)("%s", (char *)line.m_data + 8);

    Rva8CD130Value *old = state->m_values[state->m_count - 1];
    if (!old->maxRefCountHit())
        old->release();
    --state->m_count;
}

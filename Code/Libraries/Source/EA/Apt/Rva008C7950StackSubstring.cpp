// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// RVA 008C7950, 587 bytes. Opaque name: retail state +0 count, +8 array.
// String layout and conversion ABI: docs/analysis/0x008985c0.md.
// 0089FAC0 ret8 and 0089FBC0 ret12 construct a hidden string result.
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
extern void *(__cdecl *WideAllocPtr)(unsigned);

class Rva8CD130String
{
public:
    Rva8CD130String() : m_data(&g_bfmeDefaultString1284) { ++m_data->m_refCount; }
    ~Rva8CD130String()
    {
        BfmeStringData3AF0 *old = m_data;
        if (--old->m_refCount == 0) g_bfmeStringPool1284->free(old);
    }
    Rva8CD130String &operator=(const Rva8CD130String &source)
    {
        ++source.m_data->m_refCount;
        BfmeStringData3AF0 *old = m_data;
        if (--old->m_refCount == 0) g_bfmeStringPool1284->free(old);
        m_data = source.m_data;
        return *this;
    }
    void clear()
    {
        BfmeStringData3AF0 *old = m_data;
        if (--old->m_refCount == 0) g_bfmeStringPool1284->free(old);
        m_data = &g_bfmeDefaultString1284;
        ++m_data->m_refCount;
    }
    Rva8CD130String suffix0089FAC0(int start) const;
    Rva8CD130String slice0089FBC0(int start, int count) const;
    BfmeStringData3AF0 *m_data;
};
class Rva8CD130Value
{
public:
    void getName(Rva8CD130String *output);
};
class AptValue
{
public:
    int toInteger() const;
};
class BfmeStrVKK
{
public:
    void bfmeTruncVKK(unsigned);
};
class Value008C7950
{
public:
    virtual void retain();
    virtual void release();
    bool flag30() const { return ((m_flags >> 30) & 1) != 0; }
    unsigned m_flags;
};
class Rva008A9B00 : public Value008C7950
{
public:
    Rva008A9B00();
    void *operator new(unsigned bytes) { return WideAllocPtr(bytes); }
    // Retail unwind state 1 calls 00891A80(pointer, 16); caller pops 8.
    void operator delete(void *storage, unsigned bytes);
    Rva8CD130String m_string;
    Rva008A9B00 *m_next;
};
struct BfmeRegistryKind1
{
    int m_capacity, m_count;
    void **m_entries;
    void addOrClear(Rva008A9B00 *obj)
    {
        int index = m_count;
        int *pcount = &m_count;
        int cap = m_capacity;
        if (index >= cap) { obj->m_flags &= ~0x40000000; return; }
        m_entries[index] = obj;
        ++*pcount;
    }
};
extern "C" BfmeRegistryKind1 *g_bfmeRegistryVNF;
extern Rva008A9B00 *g_rva008AAFD0Free;
struct Stack008C7950
{
    int m_count;
    unsigned m_unknown04;
    Value008C7950 **m_entries;
};

void stackSubstring008C7950(Stack008C7950 *state)
{
    Value008C7950 *topValue = state->m_entries[state->m_count - 1];
    Value008C7950 *value = state->m_entries[state->m_count - 3];
    Value008C7950 *startValue = state->m_entries[state->m_count - 2];
    int count = reinterpret_cast<AptValue *>(topValue)->toInteger();
    int start = reinterpret_cast<AptValue *>(startValue)->toInteger() - 1;
    if (start < 0) start = 0;
    Rva8CD130String text;
    reinterpret_cast<Rva8CD130Value *>(value)->getName(&text);
    Rva008A9B00 *result = g_rva008AAFD0Free;
    if (result)
    {
        g_rva008AAFD0Free = result->m_next;
        g_bfmeRegistryVNF->addOrClear(result);
        if (result->m_string.m_data != &g_bfmeDefaultString1284)
            reinterpret_cast<BfmeStrVKK *>(&result->m_string)->bfmeTruncVKK(0);
    }
    else result = new Rva008A9B00;
    if (count == 0) result->m_string.clear();
    else if (count < 0) result->m_string = text.suffix0089FAC0(start);
    else result->m_string = text.slice0089FBC0(start, count);
    for (int i = 1; i <= 3; ++i)
    {
        Value008C7950 *old = state->m_entries[state->m_count - i];
        if (!old->flag30()) old->release();
    }
    state->m_count -= 3;
    state->m_entries[state->m_count++] = result;
    if (!result->flag30()) result->retain();
}

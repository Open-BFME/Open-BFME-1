// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// RVA 008C7F70: convert the top integer to one repeated byte in a pooled string.
// 0089E030 initializes the string and returns this; its constructor ABI controls EH state 1.
// String layout and conversion ABI: docs/analysis/0x008985c0.md.
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
    BfmeStringData3AF0 *m_data;
};
class RepeatedByteString0089E030 : public Rva8CD130String {
public:
    RepeatedByteString0089E030(int, unsigned);
};
class AptValue { public: int toInteger() const; };
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
    bool isUndefined() const { return ((m_flags >> 15) & 1) == 0; }
    bool flag30() const { return ((m_flags >> 30) & 1) != 0; }
    unsigned m_flags;
};
class Rva008A9B00 : public Value008C7950
{
public:
    Rva008A9B00();
    void *operator new(unsigned bytes) { return WideAllocPtr(bytes); }
    // Sized deallocation for construction failure; same 16-byte value as 008C7950.
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
    __forceinline void pop() {
        Value008C7950 *old = m_entries[m_count - 1];
        if (!old->flag30()) old->release();
        --m_count;
    }
    __forceinline void push(Value008C7950 *v) {
        m_entries[m_count++] = v;
        if (!v->flag30()) v->retain();
    }
};

extern AptValue *g_bfmeFallbackDB;
void IntegerString008C7F70(Stack008C7950 *state)
{
    Value008C7950 *value = state->m_entries[state->m_count - 1];
    if (!value->isUndefined()) {
        Rva008A9B00 *result = g_rva008AAFD0Free;
        if (result) {
            g_rva008AAFD0Free = result->m_next;
            g_bfmeRegistryVNF->addOrClear(result);
            if (result->m_string.m_data != &g_bfmeDefaultString1284)
                reinterpret_cast<BfmeStrVKK *>(&result->m_string)->bfmeTruncVKK(0);
        } else result = new Rva008A9B00;
        {
            result->m_string = RepeatedByteString0089E030(((AptValue *)value)->toInteger(), 1);
        }
        state->pop();
        state->push(result);
    } else {
        state->pop();
        state->push((Value008C7950 *)g_bfmeFallbackDB);
    }
}

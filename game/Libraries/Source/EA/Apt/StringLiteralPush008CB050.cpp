// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// RVA 008CB050: aligned string literal decode and pooled value push.
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
class EAStringC { public: class StringDataC; };
extern EAStringC::StringDataC g_rva012D5298Empty;	// shared empty string block 0x012D5298
static inline BfmeStringData3AF0 *sharedEmptyString012D5298()
{
	return (BfmeStringData3AF0 *)&g_rva012D5298Empty;
}
extern BfmeStringPool3AF0 *g_rva01337A30AllocPair;
extern void *(__cdecl *Rva008C5D70Alloc)(unsigned);

class BfmeStrVKI { public: void bfmeSetVKI(const char *); };
class Rva8CD130String
{
public:
    Rva8CD130String(const char *p) { ((BfmeStrVKI *)this)->bfmeSetVKI(p); }
    Rva8CD130String() : m_data(sharedEmptyString012D5298()) { ++m_data->m_refCount; }
    ~Rva8CD130String()
    {
        BfmeStringData3AF0 *old = m_data;
        if (--old->m_refCount == 0) g_rva01337A30AllocPair->free(old);
    }
    Rva8CD130String &operator=(const Rva8CD130String &source)
    {
        ++source.m_data->m_refCount;
        BfmeStringData3AF0 *old = m_data;
        if (--old->m_refCount == 0) g_rva01337A30AllocPair->free(old);
        m_data = source.m_data;
        return *this;
    }
    BfmeStringData3AF0 *m_data;
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
    void *operator new(unsigned bytes) { return Rva008C5D70Alloc(bytes); }
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
struct Rva00899560Pool;
extern Rva00899560Pool *g_rva01337810GcRoots;
struct Rva008C3B60Node;
extern Rva008C3B60Node *g_rva01338478NodeHead;
struct Stack008C7950
{
    int m_count;
    unsigned m_unknown04;
    Value008C7950 **m_entries;
};

void StringLiteralPush008CB050(Stack008C7950 *state, const char **cursor)
{
    const char **literal = (const char **)(((unsigned)*cursor + 3) & ~3);
    *cursor = (const char *)(literal + 1);
    Rva008A9B00 *result = (*(Rva008A9B00 **)&g_rva01338478NodeHead);
    if (result)
    {
        (*(Rva008A9B00 **)&g_rva01338478NodeHead) = result->m_next;
        ((BfmeRegistryKind1 *)g_rva01337810GcRoots)->addOrClear(result);
        if (result->m_string.m_data != sharedEmptyString012D5298())
            reinterpret_cast<BfmeStrVKK *>(&result->m_string)->bfmeTruncVKK(0);
    }
    else result = new Rva008A9B00;
    result->m_string = Rva8CD130String(*literal);
    state->m_entries[state->m_count++] = result;
    if (!result->flag30()) result->retain();
}

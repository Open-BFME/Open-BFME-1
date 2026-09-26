// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// RVA 008C6840: cdecl callback; no incoming arguments are read.
// Layout witnesses: docs/analysis/0x008985c0.md, sections B/C/E.
// 008C54A0 reads its sole stack argument at +30 and returns with plain ret
// at +104. It mutates the one-pointer handle; its return is unused here.

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
extern void *(__cdecl *Rva008C5D70Alloc)(unsigned int);

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
    BfmeStringData3AF0 *m_data;
};
class Rva8CD130Value
{
public:
    void getName(Rva8CD130String *output);
    bool isUndefined() const { return ((m_flags >> 15) & 1) == 0; }
    void *m_unknown00;
    unsigned m_flags;
};
class BfmeStrVKK
{
public:
    void bfmeTruncVKK(unsigned n);
};
class BfmeStrVKJ
{
public:
    BfmeStrVKJ *bfmeAssignVKJ(const BfmeStrVKJ &other);
};
// Existing opaque sized-deallocator pin. Retail EH state 0 pushes 16 and
// the allocation pointer, calls 00891A80, then removes eight argument bytes.
// 00891A80 is the six-byte jump through callback VA 01337830.
class Gen_uws16_00891a80
{
public:
    static void operator delete(void *memory, unsigned bytes);
};
class Rva008A9B00 : public Gen_uws16_00891a80
{
public:
    Rva008A9B00();
    void *operator new(unsigned bytes) { return Rva008C5D70Alloc(bytes); }
    void *m_unknown00;
    unsigned m_flags;
    BfmeStringData3AF0 *m_data;
    Rva008A9B00 *m_next;
};
struct Rva00899560Pool
{
    int m_capacity, m_count;
    void **m_items;
    __forceinline void addPooled(Rva008A9B00 *object)
    {
        int index = m_count;
        int *count = &m_count;
        if (index >= m_capacity)
            object->m_flags &= ~0x40000000;
        else
        {
            m_items[index] = object;
            ++*count;
        }
    }
};
extern Rva00899560Pool *g_rva8CD130IdleHook;
extern Rva008A9B00 *Rva008C3B60Head;
extern Rva8CD130Value **g_bfmeArr1233;
extern int g_bfmeCount1233;
extern void d_008c54a0();

Rva008A9B00 *rva008C6840StringTransform()
{
    Rva008A9B00 *result = Rva008C3B60Head;
    if (result)
    {
        Rva008C3B60Head = result->m_next;
        g_rva8CD130IdleHook->addPooled(result);
        if (result->m_data != &g_bfmeDefaultString1284)
            ((BfmeStrVKK *)&result->m_data)->bfmeTruncVKK(0);
    }
    else
        result = new Rva008A9B00;
    {
        Rva8CD130Value *value = g_bfmeArr1233[g_bfmeCount1233 - 1];
        unsigned type = value->m_flags & 0x3f;
        if ((type == 1 || type == 42) && !value->isUndefined())
        {
            Rva8CD130String text;
            value->getName(&text);
            ((void (__cdecl *)(Rva8CD130String *))d_008c54a0)(&text);
            ++text.m_data->m_refCount;
            BfmeStringData3AF0 *old = result->m_data;
            if (--old->m_refCount == 0)
                g_bfmeStringPool1284->free(old);
            result->m_data = text.m_data;
        }
    }
    return result;
}

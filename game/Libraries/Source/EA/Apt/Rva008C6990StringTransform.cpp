// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// RVA 008C6990: cdecl callback; entry slot 2 is a count guard.
// Layout witnesses: docs/analysis/0x008985c0.md, sections B/C/E.
// 008C5360 reads its sole stack argument at +41 and returns with plain ret
// at +10e. It mutates the one-pointer handle; its return is unused here.

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
extern BfmeStringPool3AF0 *g_rva01337A30AllocPair;
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
            g_rva01337A30AllocPair->free(old);
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
// The Apt global node free list at 0x01338478, defined once by
// game/GameEngine/Source/Common/Data/Rva01338478.cpp.  This body keeps its own
// view of a node (Rva008A9B00) and reaches the next link through it.
struct Rva008C3B60Node;
extern Rva008C3B60Node *g_rva01338478NodeHead;
static __forceinline Rva008A9B00 *&rva01338478FreeHead() {
    return *(Rva008A9B00 **)&g_rva01338478NodeHead;
}
extern Rva8CD130Value **g_bfmeArr1233;
// 0x01338748: the Apt stack depth global, defined in Rva00C6DCC0StaticInit.cpp.
struct Rva008AE770Stack { int m_count; };
extern Rva008AE770Stack Rva008AE770TheStack;
extern void d_008c5360();

Rva008A9B00 *rva008C6990StringTransform(void *unknown, int count)
{
    Rva008A9B00 *result = rva01338478FreeHead();
    if (result)
    {
        rva01338478FreeHead() = result->m_next;
        g_rva8CD130IdleHook->addPooled(result);
        if (result->m_data != &g_bfmeDefaultString1284)
            ((BfmeStrVKK *)&result->m_data)->bfmeTruncVKK(0);
    }
    else
        result = new Rva008A9B00;
    if (count)
    {
        Rva8CD130Value *value = g_bfmeArr1233[Rva008AE770TheStack.m_count - 1];
        unsigned type = value->m_flags & 0x3f;
        if ((type == 1 || type == 42) && !value->isUndefined())
        {
            Rva8CD130String text;
            value->getName(&text);
            ((void (__cdecl *)(Rva8CD130String *))d_008c5360)(&text);
            ((BfmeStrVKJ *)&result->m_data)->bfmeAssignVKJ(*(BfmeStrVKJ *)&text);
        }
    }
    return result;
}

// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
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
extern void *(*WideAllocPtr)(unsigned int bytes);
class Rva8CD130String
{
public:
    ~Rva8CD130String()
    {
        BfmeStringData3AF0 *old = m_data;
        if (--old->m_refCount == 0) g_rva01337A30AllocPair->free(old);
    }
    const char *text() const { return reinterpret_cast<const char *>(m_data) + 8; }
    BfmeStringData3AF0 *m_data;
};
class KeyValuePairs00898D80
{
public:
    Rva8CD130String keyValuePairs00898D80();
};
class BfmeStrVKK
{
public:
    void bfmeTruncVKK(unsigned n);
};
class Rva008B2EA0Node
{
public:
    void append(void *text);
};
class Rva008A9B00
{
public:
    Rva008A9B00();
    void *operator new(unsigned int bytes) { return WideAllocPtr(bytes); }
    void operator delete(void *, unsigned int);
    __forceinline void clearRegistered() { m_flags &= ~0x40000000; }
    void *m_vptr;
    unsigned m_flags;
    BfmeStringData3AF0 *m_block;
    Rva008A9B00 *m_next;
};
struct BfmeRegistryKind1
{
    int m_capacity;
    int m_count;
    void **m_entries;
    __forceinline void addOrClear(Rva008A9B00 *obj)
    {
        int index = m_count;
        int *pcount = &m_count;
        int cap = m_capacity;
        if (index >= cap) { obj->clearRegistered(); return; }
        m_entries[index] = obj;
        ++*pcount;
    }
};
extern "C" BfmeRegistryKind1 *g_bfmeRegistryVNF;
extern Rva008A9B00 *g_rva008AAFD0Free;

// ?aptCallbackString008A6100@@YAPAVRva008A9B00@@PAVKeyValuePairs00898D80@@H@Z
Rva008A9B00 *aptCallbackString008A6100(KeyValuePairs00898D80 *src, int)
{
    Rva008A9B00 *obj = g_rva008AAFD0Free;
    if (obj)
    {
        g_rva008AAFD0Free = obj->m_next;
        g_bfmeRegistryVNF->addOrClear(obj);
        if (obj->m_block != &g_bfmeDefaultString1284)
            reinterpret_cast<BfmeStrVKK *>(&obj->m_block)->bfmeTruncVKK(0);
    }
    else
        obj = new Rva008A9B00();
    reinterpret_cast<Rva008B2EA0Node *>(obj)->append(const_cast<char *>(src->keyValuePairs00898D80().text()));
    return obj;
}

// ?aptCallbackString008A62A0@@YAPAVRva008A9B00@@PAVKeyValuePairs00898D80@@H@Z
Rva008A9B00 *aptCallbackString008A62A0(KeyValuePairs00898D80 *src, int)
{
    Rva008A9B00 *obj = g_rva008AAFD0Free;
    if (obj)
    {
        g_rva008AAFD0Free = obj->m_next;
        g_bfmeRegistryVNF->addOrClear(obj);
        if (obj->m_block != &g_bfmeDefaultString1284)
            reinterpret_cast<BfmeStrVKK *>(&obj->m_block)->bfmeTruncVKK(0);
    }
    else
        obj = new Rva008A9B00();
    reinterpret_cast<Rva008B2EA0Node *>(obj)->append(const_cast<char *>(src->keyValuePairs00898D80().text()));
    return obj;
}

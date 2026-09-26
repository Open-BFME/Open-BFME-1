// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// RVA 00898D80, 467B. Member returns a constructed four-byte string (ret4).
// Opaque identity; sibling of 0x00898F60 (same flags word, slot 0x18 list).
// Retail literals: __proto__ at VA01136040, prototype at VA01136034, = and &.
extern "C" int __cdecl _strcmpi(const char *, const char *);
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
class BfmeStrVKJ
{
public:
    BfmeStrVKJ *bfmeAssignVKJ(const BfmeStrVKJ &);
};
class EAStringC
{
public:
    bool rva0089F730(const char *);
};
class Rva8CD130String
{
public:
    Rva8CD130String() : m_data(&g_bfmeDefaultString1284) { ++m_data->m_refCount; }
    Rva8CD130String(const Rva8CD130String &source) : m_data(source.m_data) { ++m_data->m_refCount; }
    ~Rva8CD130String()
    {
        BfmeStringData3AF0 *old = m_data;
        if (--old->m_refCount == 0) g_bfmeStringPool1284->free(old);
    }
    Rva8CD130String &rva0089EA60Append(const char *text);
    void append(const Rva8CD130String &source)
    { reinterpret_cast<BfmeStrVKJ *>(this)->bfmeAssignVKJ(reinterpret_cast<const BfmeStrVKJ &>(source)); }
    const char *text() const { return reinterpret_cast<const char *>(m_data) + 8; }
    BfmeStringData3AF0 *m_data;
};
struct BfmeIterator1285
{
    Rva8CD130String m_key;
    unsigned m_taggedValue;
};
class BfmeIteratorList1285
{
public:
    BfmeIterator1285 *bfmeFirst1285();
    BfmeIterator1285 *bfmeNext1285(BfmeIterator1285 *);
};
class Rva8CD130Value
{
public:
    void getName(Rva8CD130String *output);
    bool isUndefined() const { return ((m_flags >> 15) & 1) == 0; }
    enum Type { type9 = 9 };
    Type type() const { return static_cast<Type>(m_flags & 0x3f); }
    void *m_unknown00;
    unsigned m_flags;
};
class KeyValuePairs00898D80
{
public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0C();
    virtual void slot10();
    virtual void slot14();
    virtual BfmeIteratorList1285 *slot18();
    unsigned m_flags;
    Rva8CD130String keyValuePairs00898D80();
};

Rva8CD130String KeyValuePairs00898D80::keyValuePairs00898D80()
{
    Rva8CD130String result;
    if ((m_flags & 0x8000) == 0) return result;
    BfmeIteratorList1285 *list = slot18();
    if (!list) return result;
    Rva8CD130String text;
    for (BfmeIterator1285 *it = list->bfmeFirst1285(); it; it = list->bfmeNext1285(it))
    {
        if (_strcmpi(it->m_key.text(), "__proto__") != 0 && _strcmpi(it->m_key.text(), "prototype") != 0)
        {
            Rva8CD130Value *value = reinterpret_cast<Rva8CD130Value *>(it->m_taggedValue & ~1u);
            value->getName(&text);
            result.append(it->m_key);
            result.rva0089EA60Append("=");
            result.append(text);
            result.rva0089EA60Append("&");
        }
    }
    reinterpret_cast<EAStringC *>(&result)->rva0089F730("&");
    return result;
}

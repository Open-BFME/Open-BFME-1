// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ?rva008A9E20CodepointStringValue@@YAPAVRva008A9B00@@PAVAptValue@@@Z
struct BfmeStringData3AF0 {
    unsigned short m_refCount, m_length, m_capacity, m_unknown06;
};
struct BfmeStringPool3AF0 {
    void *m_unknown00;
    void (__cdecl *free)(void *);
};
extern BfmeStringData3AF0 g_bfmeDefaultString1284;
extern BfmeStringPool3AF0 *g_bfmeStringPool1284;
class EAStringC {
public:
    __forceinline EAStringC() {
        m_data = &g_bfmeDefaultString1284;
        ++m_data->m_refCount;
    }
    __forceinline ~EAStringC() {
        BfmeStringData3AF0 *old = m_data;
        if (--old->m_refCount == 0) g_bfmeStringPool1284->free(old);
    }
    EAStringC &rva0089FDA0(const char *source, int limit);
    BfmeStringData3AF0 *m_data;
};
class BfmeUtf8Cursor0089F810 {
public:
    const unsigned char *after(int index) const;
};
class BfmeStrVKK {
public:
    void bfmeTruncVKK(unsigned int size);
};
class AptValue {
public:
    int toInteger() const;
    void *m_vtable;
    unsigned int m_flags;
    EAStringC m_string;
    unsigned char m_unknown0C[0x14];
    AptValue *m_indirect;
};
extern AptValue **g_bfmeArr1233;
// 0x01338748: the Apt stack depth global, defined in Rva00C6DCC0StaticInit.cpp.
struct Rva008AE770Stack { int m_count; };
extern Rva008AE770Stack Rva008AE770TheStack;
extern void *(__cdecl *WideAllocPtr)(unsigned int);
class Rva008A9B00 {
public:
    __declspec(nothrow) Rva008A9B00();
    __forceinline void *operator new(unsigned int bytes) { return WideAllocPtr(bytes); }
    void *m_vtable;
    unsigned int m_flags;
    EAStringC m_string;
    Rva008A9B00 *m_next;
};
// 0x01337810: the Apt GC-root registry vector pointer, defined in
// game/Libraries/Source/Apt/Apt.cpp. The view type below is this TU's own.
struct Rva00899560Pool {
    int m_capacity, m_count;
    void **m_entries;
    __forceinline void add(Rva008A9B00 *obj) {
        int index = m_count;
        if (index >= m_capacity) { obj->m_flags &= ~0x40000000u; return; }
        m_entries[index] = obj;
        ++m_count;
    }
};
extern Rva00899560Pool *g_rva01337810GcRoots;
extern Rva008A9B00 *g_free01338478;
// 0x013379BC: the Apt undefined-value sentinel, defined as AptValue* in
// Bfme5AppendFallback8CAFF0.cpp.  Retail's byte here is a plain pointer load,
// so the reinterpret_cast below compiles to the same mov.
extern AptValue *g_bfmeFallbackDB;

Rva008A9B00 *rva008A9E20CodepointStringValue(AptValue *value) {
    int index = g_bfmeArr1233[Rva008AE770TheStack.m_count - 1]->toInteger();
    unsigned int type = value->m_flags & 0x3f;
    AptValue *source = value;
    if (type != 1) source = value->m_indirect;
    const BfmeUtf8Cursor0089F810 *cursor = (const BfmeUtf8Cursor0089F810 *)&source->m_string;
    if (index < 0) {
        return (Rva008A9B00 *)g_bfmeFallbackDB;
    } else {
    const unsigned char *p = cursor->after(index);
    if (!p) return (Rva008A9B00 *)g_bfmeFallbackDB;
    {
    EAStringC result;
    result.rva0089FDA0((const char *)p, 1);
    Rva008A9B00 *obj = g_free01338478;
    if (obj) {
        g_free01338478 = obj->m_next;
        g_rva01337810GcRoots->add(obj);
        if (obj->m_string.m_data != &g_bfmeDefaultString1284)
            ((BfmeStrVKK *)&obj->m_string)->bfmeTruncVKK(0);
    } else {
        Rva008A9B00 *fresh = new Rva008A9B00;
        obj = fresh;
    }
    ++result.m_data->m_refCount;
    BfmeStringData3AF0 *old = obj->m_string.m_data;
    if (--old->m_refCount == 0) g_bfmeStringPool1284->free(old);
    obj->m_string.m_data = result.m_data;
    return obj;
    }
    }
}

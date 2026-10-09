// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// RVA 008AAB20: cdecl value/count -> string-value pointer. Opaque identity.
// Contracts and layouts: docs/analysis/0x008985c0.md, plus retail 008AAB20.
struct BfmeStringData3AF0 {
    unsigned short m_refCount, m_length, m_capacity, m_unknown06;
};
struct BfmeStringPool3AF0 {
    void *m_unknown00;
    void (__cdecl *free)(void *);
};
extern BfmeStringData3AF0 g_bfmeDefaultString1284;
extern BfmeStringPool3AF0 *g_rva01337A30AllocPair;
class EAStringC {
public:
    __forceinline EAStringC() {
        m_data = &g_bfmeDefaultString1284;
        ++m_data->m_refCount;
    }
    __forceinline ~EAStringC() {
        BfmeStringData3AF0 *old = m_data;
        if (--old->m_refCount == 0) g_rva01337A30AllocPair->free(old);
    }
    __forceinline EAStringC &operator=(const EAStringC &source) {
        ++source.m_data->m_refCount;
        BfmeStringData3AF0 *old = m_data;
        if (--old->m_refCount == 0) g_rva01337A30AllocPair->free(old);
        m_data = source.m_data;
        return *this;
    }
    EAStringC utf8Mid0089FBC0(int start, int count) const;
    int bfmeUtf8Length() const;
    BfmeStringData3AF0 *m_data;
};
class Rva8CD130String;
class Rva8CD130Value { public: void getName(Rva8CD130String *output); };
class AptValue { public: int toInteger() const; };
class BfmeStrVKK { public: void bfmeTruncVKK(unsigned n); };
extern AptValue **g_bfmeArr1233;
struct Rva008AE770Stack { int field00; };
extern Rva008AE770Stack Rva008AE770TheStack;
extern void *(__cdecl *WideAllocPtr)(unsigned int);
struct Rva008C3B60Node;
class Rva008A9B00 {
public:
    __declspec(nothrow) Rva008A9B00();
    __forceinline void *operator new(unsigned int bytes) { return WideAllocPtr(bytes); }
    void *m_unknown00;
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
extern Rva008C3B60Node *g_rva01338478NodeHead;
// 0x013379BC: the Apt undefined-value sentinel, defined as AptValue* in
// Bfme5AppendFallback8CAFF0.cpp.  Retail's byte here is a plain pointer load,
// so the reinterpret_cast below compiles to the same mov.
extern AptValue *g_bfmeFallbackDB;

__forceinline Rva008A9B00 *acquire008AAB20() {
    Rva008A9B00 *result;
    Rva008A9B00 *obj = (Rva008A9B00 *)g_rva01338478NodeHead;
    if (obj) {
        g_rva01338478NodeHead = (Rva008C3B60Node *)obj->m_next;
        g_rva01337810GcRoots->add(obj);
        if (obj->m_string.m_data != &g_bfmeDefaultString1284)
            ((BfmeStrVKK *)&obj->m_string)->bfmeTruncVKK(0);
        result = obj;
    } else {
        Rva008A9B00 *fresh = new Rva008A9B00;
        result = fresh;
    }
    return result;
}

Rva008A9B00 *substringValue008AAB20(Rva8CD130Value *value, int count) {
    EAStringC text;
    int start = -1;
    int length = 9999999;
    if (!count) return (Rva008A9B00 *)g_bfmeFallbackDB;
    if (count >= 1) start = g_bfmeArr1233[Rva008AE770TheStack.field00 - 1]->toInteger();
    if (count >= 2) length = g_bfmeArr1233[Rva008AE770TheStack.field00 - 2]->toInteger();
    value->getName((Rva8CD130String *)&text);
    int total = text.bfmeUtf8Length();
    if (start < 0) start += total;
    Rva008A9B00 *obj = acquire008AAB20();
    obj->m_string = text.utf8Mid0089FBC0(start, length);
    return obj;
}

// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// RVA 008AA420: cdecl value/count -> string-value pointer. Opaque identity.
// Contracts and layouts: docs/analysis/0x008985c0.md, plus retail 008AA420.
struct BfmeStringData3AF0 {
    unsigned short m_refCount, m_length, m_capacity, m_unknown06;
};
struct BfmeStringPool3AF0 {
    void *m_unknown00;
    void (__cdecl *free)(void *);
};
extern BfmeStringData3AF0 g_bfmeDefaultString1284;
extern BfmeStringPool3AF0 *g_bfmeStringPool1284;
class Rva8CD130String {
public:
    __forceinline Rva8CD130String() {
        m_data = &g_bfmeDefaultString1284;
        ++m_data->m_refCount;
    }
    __forceinline ~Rva8CD130String() {
        BfmeStringData3AF0 *old = m_data;
        if (--old->m_refCount == 0) g_bfmeStringPool1284->free(old);
    }
    __forceinline Rva8CD130String &operator=(const Rva8CD130String &source) {
        ++source.m_data->m_refCount;
        BfmeStringData3AF0 *old = m_data;
        if (--old->m_refCount == 0) g_bfmeStringPool1284->free(old);
        m_data = source.m_data;
        return *this;
    }
    // 0089FBC0: receiver is handle; hidden result + two signed indices;
    // +29 initializes [entry+4], returns that address in EAX; +3D ret12.
    Rva8CD130String substring0089FBC0(int start, int count);
    BfmeStringData3AF0 *m_data;
};
class Rva8CD130Value { public: void getName(Rva8CD130String *output); };
class AptValue { public: int toInteger() const; };
class EAStringC { public: int bfmeUtf8Length() const; };
class BfmeStrVKK { public: void bfmeTruncVKK(unsigned n); };
extern AptValue **g_bfmeArr1233;
extern int g_count01338748;
extern void *(__cdecl *WideAllocPtr)(unsigned int);
class Rva008A9B00 {
public:
    __declspec(nothrow) Rva008A9B00();
    __forceinline void *operator new(unsigned int bytes) { return WideAllocPtr(bytes); }
    void *m_unknown00;
    unsigned int m_flags;
    Rva8CD130String m_string;
    Rva008A9B00 *m_next;
};
struct Rva008AA420Registry {
    int m_capacity, m_count;
    void **m_entries;
    __forceinline void add(Rva008A9B00 *obj) {
        int index = m_count;
        if (index >= m_capacity) { obj->m_flags &= ~0x40000000u; return; }
        m_entries[index] = obj;
        ++m_count;
    }
};
extern Rva008AA420Registry *g_registry01337810;
extern Rva008A9B00 *g_free01338478;
extern Rva008A9B00 *g_fallback013379BC;

__forceinline Rva008A9B00 *acquire008AA420() {
    Rva008A9B00 *result;
    Rva008A9B00 *obj = g_free01338478;
    if (obj) {
        g_free01338478 = obj->m_next;
        g_registry01337810->add(obj);
        if (obj->m_string.m_data != &g_bfmeDefaultString1284)
            ((BfmeStrVKK *)&obj->m_string)->bfmeTruncVKK(0);
        result = obj;
    } else {
        Rva008A9B00 *fresh = new Rva008A9B00;
        result = fresh;
    }
    return result;
}

Rva008A9B00 *sliceValue008AA420(Rva8CD130Value *value, int count) {
    Rva8CD130String text;
    int start = -1;
    int length = 9999999;
    if (!count) return g_fallback013379BC;
    if (count >= 1) start = g_bfmeArr1233[g_count01338748 - 1]->toInteger();
    if (count >= 2) length = g_bfmeArr1233[g_count01338748 - 2]->toInteger();
    value->getName(&text);
    int total = ((EAStringC *)&text)->bfmeUtf8Length();
    if (start < 0) start += total;
    if (length < 0) length += total;
    if (start < 0) start = 0;
    if (length < 0) length = 0;
    if (start >= total) start = total;
    if (length >= total) length = total;
    Rva8CD130String result;
    result = text.substring0089FBC0(start, length - start);
    Rva008A9B00 *obj = acquire008AA420();
    obj->m_string = result;
    return obj;
}

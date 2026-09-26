// ?rva008A9F70CodepointStringValue@@YAPAVRva008A9B00@@PAVAptValue@@@Z
// partial score=0.34 date=2026-09-26
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// RVA 008A9F70: cdecl value pointer to codepoint string value.
struct BfmeStringData3AF0 {
    unsigned short m_refCount, m_length, m_capacity, m_unknown06;
};
struct BfmeStringPool3AF0 {
    void *m_unknown00;
    void (__cdecl *free)(void *);
};
extern BfmeStringData3AF0 g_bfmeDefaultString1284;
extern BfmeStringPool3AF0 *g_bfmeStringPool1284;
extern "C" int __cdecl sprintf(char *, const char *, ...);
class Rva8CD130String {
public:
    ~Rva8CD130String() {
        BfmeStringData3AF0 *old = m_data;
        if (--old->m_refCount == 0) g_bfmeStringPool1284->free(old);
    }
    BfmeStringData3AF0 *m_data;
};
class BfmeStrVKI {
public:
    BfmeStrVKI(const char *text) { bfmeSetVKI(text); }
    ~BfmeStrVKI() {
        BfmeStringData3AF0 *old = m_data;
        if (--old->m_refCount == 0) g_bfmeStringPool1284->free(old);
    }
    void bfmeSetVKI(const char *text);
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
    Rva8CD130String m_string;
    unsigned char m_unknown0C[0x14];
    AptValue *m_indirect;
};
extern AptValue **g_bfmeArr1233;
extern int g_count01338748;
extern void *(__cdecl *WideAllocPtr)(unsigned int);
class Rva008A9B00 {
public:
    __declspec(nothrow) Rva008A9B00();
    __forceinline void *operator new(unsigned int bytes) { return WideAllocPtr(bytes); }
    void *m_vtable;
    unsigned int m_flags;
    Rva8CD130String m_string;
    Rva008A9B00 *m_next;
};
struct Rva008A9F70Registry {
    int m_capacity, m_count;
    void **m_entries;
    __forceinline void add(Rva008A9B00 *obj) {
        int index = m_count;
        if (index >= m_capacity) { obj->m_flags &= ~0x40000000u; return; }
        m_entries[index] = obj;
        ++m_count;
    }
};
extern Rva008A9F70Registry *g_registry01337810;
extern Rva008A9B00 *g_free01338478;
extern Rva008A9B00 *g_fallback013379BC;

Rva008A9B00 *rva008A9F70CodepointStringValue(AptValue *value) {
    int index = g_bfmeArr1233[g_count01338748 - 1]->toInteger();
    unsigned int type = value->m_flags & 0x3f;
    AptValue *source = value;
    if (type != 1) source = value->m_indirect;
    const BfmeUtf8Cursor0089F810 *cursor = (const BfmeUtf8Cursor0089F810 *)&source->m_string;
    if (index < 0) return g_fallback013379BC;
    volatile const unsigned char *p = cursor->after(index);
    if (!p) return g_fallback013379BC;
    unsigned char c = *p;
    int code;
    if (c <= 0x7f) code = c;
    else if ((c & 0xe0) == 0xc0) {
        code = c & 0x1f;
        code <<= 6;
        code |= p[1] & 0x3f;
    } else if ((c & 0xf0) == 0xe0) {
        code = ((c & 0x0f) << 6) | (p[1] & 0x3f);
        code = (p[2] & 0x3f) | (code << 6);
    } else {
        unsigned int b1 = p[1];
        unsigned int b2 = p[2];
        unsigned int b3 = p[3];
        code = c & 7;
        code <<= 6;
        code |= b1 & 0x3f;
        code <<= 6;
        code |= b2 & 0x3f;
        code <<= 6;
        code |= b3 & 0x3f;
    }
    char buffer[8];
    sprintf(buffer, "%d", code);
    {
    BfmeStrVKI result(buffer);
    Rva008A9B00 *obj = g_free01338478;
    if (obj) {
        g_free01338478 = obj->m_next;
        g_registry01337810->add(obj);
        if (obj->m_string.m_data != &g_bfmeDefaultString1284)
            ((BfmeStrVKK *)&obj->m_string)->bfmeTruncVKK(0);
    } else {
        obj = new Rva008A9B00;
    }
    ++result.m_data->m_refCount;
    BfmeStringData3AF0 *old = obj->m_string.m_data;
    if (--old->m_refCount == 0) g_bfmeStringPool1284->free(old);
    obj->m_string.m_data = result.m_data;
    return obj;
    }
}

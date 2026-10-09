// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ?rva008A9F70CodepointStringValue@@YAPAVRva008A9B00@@PAVAptValue@@@Z
// RVA 008A9F70: decimal code point at an index of a UTF-8 Apt string, as a new string value.
struct BfmeStringData3AF0 {
    unsigned short m_refCount, m_length, m_capacity, m_unknown06;
};
struct BfmeStringPool3AF0 {
    void *m_unknown00;
    void (__cdecl *free)(void *);
};
extern BfmeStringData3AF0 g_bfmeDefaultString1284;
extern BfmeStringPool3AF0 *g_rva01337A30AllocPair;
extern "C" int __cdecl sprintf(char *, const char *, ...);
class Rva8CD130String {
public:
    ~Rva8CD130String() {
        BfmeStringData3AF0 *old = m_data;
        if (--old->m_refCount == 0) g_rva01337A30AllocPair->free(old);
    }
    BfmeStringData3AF0 *m_data;
};
class BfmeStrVKI {
public:
    BfmeStrVKI(const char *text) { bfmeSetVKI(text); }
    ~BfmeStrVKI() {
        BfmeStringData3AF0 *old = m_data;
        if (--old->m_refCount == 0) g_rva01337A30AllocPair->free(old);
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
struct Rva008AE770Stack
{
	int field00;
	int m_rva0133874C;
	AptValue** m_rva01338750;
};
extern Rva008AE770Stack Rva008AE770TheStack;
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
// Retail's global at 0x01337810 is defined in Apt.cpp under this name and
// canonical pool type. Keep this TU's narrower registry view local.
struct Rva00899560Pool;
extern Rva00899560Pool *g_rva01337810GcRoots;
// The Apt global node free list at 0x01338478, defined once by
// game/GameEngine/Source/Common/Data/Rva01338478.cpp.  This body keeps its own
// view of a node (Rva008A9B00) and reaches the next link through it.
struct Rva008C3B60Node;
extern Rva008C3B60Node *g_rva01338478NodeHead;
static __forceinline Rva008A9B00 *&rva01338478FreeHead() {
    return *(Rva008A9B00 **)&g_rva01338478NodeHead;
}
// 0x013379BC: the Apt undefined-value sentinel, defined as AptValue* in
// Bfme5AppendFallback8CAFF0.cpp.  Retail's byte here is a plain pointer load,
// so the reinterpret_cast below compiles to the same mov.
extern AptValue *g_bfmeFallbackDB;

Rva008A9B00 *rva008A9F70CodepointStringValue(AptValue *value) {
    Rva008AE770Stack& stk = Rva008AE770TheStack;
    AptValue** args = stk.m_rva01338750;
    int index = args[stk.field00 - 1]->toInteger();
    unsigned int type = value->m_flags & 0x3f;
    AptValue *source = value;
    if (type != 1) source = value->m_indirect;
    const BfmeUtf8Cursor0089F810 *cursor = (const BfmeUtf8Cursor0089F810 *)&source->m_string;
    if (index < 0) {
        return (Rva008A9B00 *)g_bfmeFallbackDB;
    } else {
    const unsigned char *p = cursor->after(index);
    if (!p) return (Rva008A9B00 *)g_bfmeFallbackDB;
    unsigned char c = *p;
    int code;
    if (c <= 0x7f) code = c;
    else if ((c & 0xe0) == 0xc0) {
        code = c & 0x1f;
        code <<= 6;
        code |= p[1] & 0x3f;
    } else if ((c & 0xf0) == 0xe0) {
        unsigned char b1 = p[1];
        unsigned char b2 = p[2];
        code = c & 0x0f;
        code <<= 6;
        code |= b1 & 0x3f;
        code <<= 6;
        code |= b2 & 0x3f;
    } else {
        unsigned char b1 = p[1];
        unsigned char b2 = p[2];
        unsigned char b3 = p[3];
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
    Rva008A9B00 *obj = rva01338478FreeHead();
    if (obj) {
        rva01338478FreeHead() = obj->m_next;
        ((Rva008A9F70Registry *)g_rva01337810GcRoots)->add(obj);
        if (obj->m_string.m_data != &g_bfmeDefaultString1284)
            ((BfmeStrVKK *)&obj->m_string)->bfmeTruncVKK(0);
    } else {
        Rva008A9B00 *fresh = new Rva008A9B00;
        obj = fresh;
    }
    ++result.m_data->m_refCount;
    BfmeStringData3AF0 *old = obj->m_string.m_data;
    if (--old->m_refCount == 0) g_rva01337A30AllocPair->free(old);
    obj->m_string.m_data = result.m_data;
    return obj;
    }
    }
}

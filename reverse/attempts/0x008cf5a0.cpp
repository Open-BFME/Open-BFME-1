// ?resolveSubmit@Rva008CF5A0Dispatch@@QAEXPAX0PAVRva8CCCE0Value@@PAVRva8CD130Value@@0H@Z
// partial score=0.2671568627450981 date=2026-09-22
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /G7
// RVA 008CF5A0, 408 bytes; six stack arguments and ret24.
// Matched caller BfmeConv1231.cpp and docs/analysis/0x008985c0.md
// establish the ABI. The incoming receiver is unused; original identity unknown.
struct BfmeStringData3AF0 { unsigned short m_refCount; };
struct BfmeStringPool3AF0 { void *m_unknown00; void (__cdecl *free)(void *); };
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
    BfmeStringData3AF0 *m_data;
};
class Rva8CD130Value { public: void getName(Rva8CD130String *output); };
class BfmeSubmitter1283 {
public:
    void bfmeSubmit1283(int a1, int a2, int a3, int a4, int a5, int a6, int a7,
        float *colors, int a9, int a10, int a11, int a12);
};
class BfmeQuery1279 {
public:
    void bfmeQuery1279(void *key, int name, void **previousResult, void **nodeResult);
};
struct Rva008CF5A0Payload {
    char m_gap00[0xc];
    int m_raw0c;
    char m_gap10[8];
    int m_raw18;
    char m_gap1c[4];
    int m_raw20;
    BfmeQuery1279 *m_query24;
    char m_gap28[4];
    int m_raw2c;
};
class Rva8CCCE0Value {
public:
    __forceinline bool undefined() const { return (~(m_flags >> 15) & 1) != 0; }
    __forceinline int kind() const { return m_flags & 0x3f; }
    __forceinline bool kind17() const { return kind() == 17 && !undefined(); }
    __forceinline bool kind13() const { return kind() == 13 && !undefined(); }
    __forceinline bool kind18() const { return kind() == 18 && !undefined(); }
    __forceinline bool kind12to19() const { return kind() >= 12 && kind() <= 19 && !undefined(); }
    __forceinline Rva8CCCE0Value *parent() const { return m_parent4c; }
    void *m_unknown00;
    unsigned m_flags;
    char m_gap08[8];
    char m_raw10[0x18];
    float m_raw28[9];
    Rva8CCCE0Value *m_parent4c;
    Rva008CF5A0Payload *m_payload50;
};
void rva8CCCE0ResolveValue(void *first, void *second, Rva8CCCE0Value *value, Rva8CCCE0Value **result);
// Thiscall with no stack arguments: callee +1 saves ECX; +7F is plain ret.
// 008AE490 and 008CF5A0 both pass the 013377D8 receiver. Use the existing
// address-derived body symbol through the same typed binding as 008AE490.
class Rva008A18C0Holder {};
extern void d_008a18c0();
extern Rva008A18C0Holder *g_bfmeHolderBU;
class Rva008CF5A0Dispatch {
public:
    void resolveSubmit(void *first, void *second, Rva8CCCE0Value *input, Rva8CD130Value *nameValue, void *key, int last);
};

void Rva008CF5A0Dispatch::resolveSubmit(void *first, void *second, Rva8CCCE0Value *input,
    Rva8CD130Value *nameValue, void *key, int last)
{
    Rva8CCCE0Value *resolved = 0;
    rva8CCCE0ResolveValue(first, second, input, &resolved);
    Rva8CD130String name;
    nameValue->getName(&name);
    Rva8CCCE0Value *value = resolved;
    if (value && value->parent()) {
        int raw18;
        if (value->kind17()) raw18 = value->m_payload50->m_raw18;
        else raw18 = 0;
        int raw20;
        if (value->kind13() || value->kind18()) raw20 = value->m_payload50->m_raw20;
        else raw20 = 0;
        ((BfmeSubmitter1283 *)&value->parent()->m_payload50->m_query24)->bfmeSubmit1283(
            0, (int)key, value->m_payload50->m_raw0c, (int)&name, (int)value->parent(),
            1, -1, value->m_raw28, (int)value->m_raw10, raw20, raw18, last);
        if (value->m_payload50->m_raw2c == 1) {
            Rva8CCCE0Value *node = 0;
            void *previous = 0;
            value->parent()->m_payload50->m_query24->bfmeQuery1279(key, (int)&name, &previous, (void **)&node);
            if (node->kind12to19()) node->m_payload50->m_raw2c = 1;
        }
        typedef void (Rva008A18C0Holder::*HolderCall)();
        union { void (*raw)(); HolderCall method; } callee;
        callee.raw = d_008a18c0;
        (g_bfmeHolderBU->*callee.method)();
    }
}

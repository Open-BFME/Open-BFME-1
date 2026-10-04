// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// RVA 008A7270, 368 bytes; address-only identity.
// Evidence: targets/game/reverse/identity_evidence/008a7270-native-allocation.md
// Two-DWORD allocation header is witnessed by bfmePush at 00897300.
// Explicit vptr uses the existing table identity; no new table or owner is asserted.
// 0x01337828 is owned as ?Rva008C5D70Alloc@@3P6APAXI@ZA by
// game/Libraries/Source/EA/Apt/Rva008C4650HeaderedAlloc.cpp, so this TU uses
// that spelling; `extern "C" ... WideAllocPtr` (symbol _WideAllocPtr) is
// defined by nothing and left the reference unresolved.
extern void *(__cdecl *Rva008C5D70Alloc)(unsigned int bytes);
class BfmeItemDX;
void __cdecl bfmePush(BfmeItemDX *);
extern "C" void *bfmeVft1029A[];
class Rva00897670HeaderedDelete {
public: static void operator delete(void *, unsigned int);
};
class Rva00899F00Base {
public:
    Rva00899F00Base(unsigned int, int);
    void *m_vptr;
    unsigned int m_flags;
    char m_gap08[0x18];
};
class AptValue;
AptValue *aptRegisterFlagged008A5440(void *, int);
AptValue *aptUnregisterFlagged008A5490(void *, int);
typedef AptValue *(*Rva008A7270Callback)(void *, int);
class Rva008A7270Value : public Rva00899F00Base, public Rva00897670HeaderedDelete {
public:
    Rva008A7270Value(Rva008A7270Callback callback) : Rva00899F00Base(9,8) {
        m_vptr = bfmeVft1029A;
        m_callback20 = callback;
    }
    static void *operator new(unsigned int n) {
        unsigned int *raw = (unsigned int *)Rva008C5D70Alloc(n+8);
        void *p = raw + 2;
        bfmePush((BfmeItemDX *)p);
        return p;
    }
    Rva008A7270Callback m_callback20;
};
class BfmeC1062 {
public:
    virtual void bfmeSlot1062C_0();
    virtual void bfmeSlot1062C_1();
};
extern BfmeC1062 *g_bfmeC1062;
extern BfmeC1062 *g_bfmeD1062;
extern "C" int __cdecl strcmp(const char *, const char *);
#pragma intrinsic(strcmp)
void *__stdcall rva008A7270(void *, void **arg2) {
    const char *name = (const char *)*arg2 + 8;
    if (strcmp(name, "addListener") == 0) {
        if (!g_bfmeC1062) {
            g_bfmeC1062 = (BfmeC1062 *)new Rva008A7270Value(aptRegisterFlagged008A5440);
            Rva008A7270Value *p = (Rva008A7270Value *)g_bfmeC1062;
            p->m_flags = (p->m_flags & 0xffffc07f) | 0x40;
            g_bfmeC1062->bfmeSlot1062C_0();
        }
        return g_bfmeC1062;
    }
    if (strcmp(name, "removeListener") == 0) {
        if (!g_bfmeD1062) {
            g_bfmeD1062 = (BfmeC1062 *)new Rva008A7270Value(aptUnregisterFlagged008A5490);
            Rva008A7270Value *p = (Rva008A7270Value *)g_bfmeD1062;
            p->m_flags = (p->m_flags & 0xffffc07f) | 0x40;
            g_bfmeD1062->bfmeSlot1062C_0();
        }
        return g_bfmeD1062;
    }
    return 0;
}

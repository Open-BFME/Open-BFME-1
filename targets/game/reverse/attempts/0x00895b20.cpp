// ?method@Rva00895B20@@QAE_NVRva00895B20Ref@@@Z
// partial score=0.6497 date=2026-10-03
// BANK ONLY: complete retail extent294B through RET4 at895C43.
// This draft emits295B,101 differing non-relocation bytes plus one excess byte;
// normalized shape0.978 is NOT byte quality. Binding895950 is not pinned.
// HandlerC57130 -> FuncInfoE465B0: state0 cleans argument[EBP+4] via
// C57120 ->4463AD ->784A70; state1 cleans string[EBP-18] viaC57128 ->891B80.
// Matched891B80 is EAStringC::~EAStringC. No EAStringC header exists in the
// worktree; the address-qualified storage view preserves its short-ref pool.
// The candidate895950 is independently decoded as thiscall, hidden result
// address plus string reference, RET8, EAX=result, with returned pointer retained.
// Remaining differences: scratch registers and receiver/sret setup, plus
// pool free uses EDX (one byte longer) instead of retail's push/EAX reload.
// Tried plain/refined RAII decrements, accessor/member variants, native-style
// string-base lifetime, constructor declaration, and rotation_sweep (2 toggles).
// No production source, pin, or byte-match claim is made.
// cl: /DNDEBUG /MD /EHsc
struct Rva00895B20Entry { const char *name; char unknown04[12]; };
struct Rva00895B20Data { char unknown00[0x28]; int count; Rva00895B20Entry *entries; };
class BfmeDropObjectA {
public:
    ~BfmeDropObjectA();
    int refs;
    char unknown04[12];
    Rva00895B20Data *data;
    void *unknown14;
};
extern void (*TheBfmeFree)(void *,unsigned);
struct BfmeStringPoolVKI { void *unused; void (__cdecl *free)(void *); };
extern BfmeStringPoolVKI *g_bfmeStringPool1284;
class BfmeStrVKI { public: void __declspec(nothrow) bfmeSetVKI(const char *); };
struct EAStringData { unsigned short refs, length, capacity, flags; };
class Rva00895B20StringBase {
protected:
    EAStringData *data;
    void releaseBuffer() { EAStringData *p=data; if(--p->refs==0) g_bfmeStringPool1284->free(p); }
    ~Rva00895B20StringBase() { releaseBuffer(); }
};
class EAStringC : private Rva00895B20StringBase {
public:
    EAStringC(const char *text) { ((BfmeStrVKI *)this)->bfmeSetVKI(text); }
};
class Rva00895B20Ref {
public:
    Rva00895B20Ref(const Rva00895B20Ref &r):value(r.value) { if(value) ++value->refs; }
    static int decrement(BfmeDropObjectA *p) { return --p->refs; }
    ~Rva00895B20Ref() { if(value && decrement(value)==0) { BfmeDropObjectA *p=value; p->~BfmeDropObjectA(); TheBfmeFree(p,24); } }
    bool operator!() const { return value==0; }
    BfmeDropObjectA *value;
};
class Rva00895B20 {
public:
    Rva00895B20Ref rva00895950(const EAStringC &);
    bool method(Rva00895B20Ref);
};
bool Rva00895B20::method(Rva00895B20Ref input)
{
    bool success=true;
    for(int i=0;i<input.value->data->count;++i) {
        if (!rva00895950(EAStringC(input.value->data->entries[i].name))) {
            success=false;
            break;
        }
    }
    return success;
}

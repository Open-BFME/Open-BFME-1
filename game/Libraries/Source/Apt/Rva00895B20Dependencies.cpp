// cl: /MD /EHsc
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
struct BfmeStringPool3AF0;
extern BfmeStringPool3AF0 *g_rva01337A30AllocPair;
class BfmeStrVKI { public: void __declspec(nothrow) bfmeSetVKI(const char *); };
struct EAStringData { unsigned short refs, length, capacity, flags; };
class Rva00895B20StringBase {
protected:
    EAStringData *data;
    void releaseBuffer() { EAStringData *p=data; if(--p->refs==0) (*(BfmeStringPoolVKI **)&g_rva01337A30AllocPair)->free(p); }
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
    bool isNull() const { return value==0; }
    Rva00895B20Data *getTable() const { return value->data; }
    BfmeDropObjectA *value;
};
class RefHandle008958D0 {
public:
    RefHandle008958D0(BfmeDropObjectA *p=0):m_object(p) { if(p) ++p->refs; }
    RefHandle008958D0(const RefHandle008958D0 &r):m_object(r.m_object) { if(m_object) ++m_object->refs; }
    __declspec(dllimport) __forceinline ~RefHandle008958D0() { if (m_object && Rva00895B20Ref::decrement(m_object)==0) { BfmeDropObjectA *p=m_object; p->~BfmeDropObjectA(); TheBfmeFree(p,24); } }
    bool isNull() const { return m_object==0; }
    BfmeDropObjectA *m_object;
};
class Rva00893030Manager {
public:
    RefHandle008958D0 rva00895950(BfmeStrVKI *key);
};
class Rva00895B20 {
public:
    Rva00895B20Ref rva00895950(const EAStringC &);
    bool method(Rva00895B20Ref);
};
// ?method@Rva00895B20@@QAE_NVRva00895B20Ref@@@Z
// Open BFME 2 donor: Code/Libraries/Source/Apt/Rva006D0C60.cpp.
bool Rva00895B20::method(Rva00895B20Ref input)
{
    bool success = true;
    for (int i=0; i<input.getTable()->count && success; ++i) {
        bool missing = ((Rva00893030Manager *)this)->rva00895950((BfmeStrVKI *)&EAStringC(input.getTable()->entries[i].name)).isNull();
        if (missing) {
            success = false;
            break;
        }
    }
    return success;
}

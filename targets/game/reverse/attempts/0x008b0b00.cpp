// ?aptBuild008B0B32@@YAPAXPAUOwner008B09A0@@H@Z
// partial score=0.0 date=2026-10-09
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

struct BfmeHdrVKI { unsigned short m_bfme00, m_bfme02, m_bfme04, m_bfme06; };
struct BfmeStringPool3AF0 { void *m_unused; void (__cdecl *free)(void *); };
extern BfmeStringPool3AF0 *g_bfmeStringPool1284;
class BfmeStrVKI {
public:
    void bfmeSetVKI(const char *);
    BfmeHdrVKI *m_bfme00;
};
class EAStringC {
public:
    EAStringC(const char *text) { ((BfmeStrVKI *)this)->bfmeSetVKI(text); }
    ~EAStringC() {
        BfmeHdrVKI *data = m_block;
        --data->m_bfme00;
        if (data->m_bfme00 == 0) g_bfmeStringPool1284->free(data);
    }
    __forceinline EAStringC &operator=(const EAStringC &src) {
        ++src.m_block->m_bfme00;
        BfmeHdrVKI *old = m_block;
        --old->m_bfme00;
        if (old->m_bfme00 == 0) g_bfmeStringPool1284->free(old);
        m_block = src.m_block;
        return *this;
    }
    BfmeHdrVKI *m_block;
};
class Rva008AD2C0 {
public:
    Rva008AD2C0(const Rva008AD2C0 &);
    void assign(const Rva008AD2C0 &);
    EAStringC m_str;
    float m_f4;
    int m_f8, m_fC, m_f10, m_f14, m_f18, m_f1C;
};
class Rva8CB820Payload {
public:
    Rva8CB820Payload(int firstValue, int a2, int a3, int a4, int a5,
        int a6, int a7, int a8, int alignmentValue, int a10, int a11,
        int a12, int a13);
    char m_storage[0x20];
};
class BfmeItemDX;
extern void *(__cdecl *Rva008C5D70Alloc)(unsigned int);
void __cdecl bfmePush(BfmeItemDX *);
class Rva008AB870HeaderedDelete {
public:
    static void operator delete(void *, unsigned int);
};
class Rva00899F00Base {
public:
    Rva00899F00Base(unsigned int, int);
    virtual ~Rva00899F00Base();
    static void *operator new(unsigned int bytes) {
        char *raw = (char *)Rva008C5D70Alloc(bytes + 8);
        char *item = raw + 8;
        bfmePush((BfmeItemDX *)item);
        return item;
    }
    char m_pad[0x1c];
};
class Rva008B0170 : public Rva00899F00Base {
public:
    Rva008B0170(const Rva008AD2C0 &);
    static void operator delete(void *, unsigned int);
    Rva008AD2C0 m_str;
};
struct Entry008B0B32 {
    int m_f0, m_f4;
    const char *m_f8;
};
struct Range008B0B32 {
    char m_pad00[0x0c];
    int m_fC;
    Entry008B0B32 **m_f10;
    int count() const { return m_fC; }
    Entry008B0B32 *at(int index) { return m_f10[index]; }
};
struct Table008B0B32 { char m_pad00[8]; Range008B0B32 m_f8; };
struct Cursor008B0B32 {
    int m_f0;
    Table008B0B32 *m_f4;
    char m_pad08[0x10];
    int m_f18;
    int index() const { return m_f18; }
    Range008B0B32 *range() { return &m_f4->m_f8; }
};
struct State008B09A0 {
    char pad00[0x0c];
    Cursor008B0B32 *m_f0C;
    char pad10[0x14];
    int m_f24;
    char pad28[0x14];
    int m_f3C;
    char pad40[0x20];
    float m_f60;
    int m_f64;
    Rva008AD2C0 *m_f68;
    unsigned m_f6C;
};
struct Owner008B09A0 { char pad00[0x50]; State008B09A0 *m_f50; };
class AptValue;
extern AptValue *g_bfmeFallbackDB;

static __forceinline int bits008B0B32(float value) {
    union Bits { float real; int integer; } bits;
    bits.real = value;
    return bits.integer;
}

void *aptBuild008B0B32(Owner008B09A0 *self, int argc) {
    if (argc > 0) return g_bfmeFallbackDB;
    if (!self->m_f50->m_f68) {
        self->m_f50->m_f68 = (Rva008AD2C0 *)new Rva8CB820Payload(
            (int)g_bfmeFallbackDB, -1082130432, -1, -1, -1,
            -1, 0, 0, (int)g_bfmeFallbackDB, -1, -1, -1, -1);
    }
    Rva008B0170 *result = new Rva008B0170(*self->m_f50->m_f68);
    if (result->m_str.m_f8 == -1) result->m_str.m_f8 = self->m_f50->m_f24;
    Range008B0B32 *range = self->m_f50->m_f0C->range();
    if (self->m_f50->m_f0C->index() < range->count() &&
        self->m_f50->m_f0C->index() != -1 &&
        range->at(self->m_f50->m_f0C->index())->m_f0 == 3) {
        EAStringC name(range->at(self->m_f50->m_f0C->index())->m_f8);
        result->m_str.m_str = name;
    } else {
        EAStringC name("");
        result->m_str.m_str = name;
    }
    result->m_str.m_fC = self->m_f50->m_f3C;
    result->m_str.m_f4 = self->m_f50->m_f60;
    return result;
}

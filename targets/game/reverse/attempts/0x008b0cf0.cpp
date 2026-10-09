// ?d_008b0d21@@YAPAVRva008B0170@@PAURva008B0D21Owner@@H@Z
// partial score=0.0 date=2026-10-09
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

typedef unsigned int size_t;
void *__cdecl operator new(size_t);
void __cdecl operator delete(void *);

extern int bfmeTheCBC;
extern void *(__cdecl *Rva008C5D70Alloc)(unsigned int);
extern void (__cdecl **Rva00892ED0ReleaseTable)(void *);
class BfmeItemDX;
void __cdecl bfmePush(BfmeItemDX *);

struct BfmeHdrVKI
{
    unsigned short m_bfme00;
    unsigned short m_bfme02;
    unsigned short m_bfme04;
    unsigned short m_bfme06;
};

class BfmeStrVKI
{
public:
    void bfmeSetVKI(const char *s);
    BfmeHdrVKI *m_bfme00;
};

class EAStringC
{
public:
    EAStringC(const char *text) { ((BfmeStrVKI *)this)->bfmeSetVKI(text); }
    ~EAStringC()
    {
        BfmeHdrVKI *data = m_data;
        if (--data->m_bfme00 == 0)
            Rva00892ED0ReleaseTable[1](data);
    }
    __forceinline EAStringC &operator=(const EAStringC &other)
    {
        ++other.m_data->m_bfme00;
        BfmeHdrVKI *old = m_data;
        if (--old->m_bfme00 == 0)
            Rva00892ED0ReleaseTable[1](old);
        m_data = other.m_data;
        return *this;
    }
    BfmeHdrVKI *m_data;
};

class Rva008AD2C0
{
public:
    Rva008AD2C0(const Rva008AD2C0 &);
    ~Rva008AD2C0();
    void assign(const Rva008AD2C0 &);
    EAStringC m_block;
    float m_f4;
    int m_f8;
    int m_fC;
    int m_f10;
    int m_f14;
    int m_f18;
    int m_f1C;
};

class Rva8CB820Payload
{
public:
    Rva8CB820Payload(int firstValue, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int alignmentValue, int a10, int a11, int a12, int a13);
    ~Rva8CB820Payload();
    char m_storage[0x20];
};

class Rva00899F00Base
{
public:
    Rva00899F00Base(unsigned int, int);
    virtual ~Rva00899F00Base();
    static void *operator new(size_t bytes)
    {
        char *raw = (char *)Rva008C5D70Alloc(bytes + 8);
        char *block = raw + 8;
        bfmePush((BfmeItemDX *)block);
        return block;
    }
    char m_pad[0x1c];
};

class Rva008B0170 : public Rva00899F00Base
{
public:
    Rva008B0170(const Rva008AD2C0 &src);
    static void operator delete(void *, size_t);
    Rva008AD2C0 m_str;
};

struct Rva008B0D21Record
{
    int field00;
    int field04;
    const char *field08;
};

struct Rva008B0D21Array
{
    char padding00[0xc];
    int field0c;
    Rva008B0D21Record **field10;
};

struct Rva008B0D21Container
{
    char padding00[8];
    Rva008B0D21Array field08;
};

struct Rva008B0D21Selection
{
    char padding00[4];
    Rva008B0D21Container *field04;
    char padding08[0x10];
    int field18;
};

struct Rva008B0D21Context
{
    char padding00[0xc];
    Rva008B0D21Selection *field0c;
    char padding10[0x14];
    int field24;
    char padding28[0x14];
    int field3c;
    char padding40[0x20];
    float field60;
    char padding64[4];
    Rva8CB820Payload *field68;
};

struct Rva008B0D21Owner
{
    char padding00[0x50];
    Rva008B0D21Context *field50;
};

// ?d_008b0d21@@YAPAVRva008B0170@@PAURva008B0D21Owner@@H@Z
Rva008B0170 *__cdecl d_008b0d21(Rva008B0D21Owner *owner, int count)
{
    if (count > 2)
        return (Rva008B0170 *)bfmeTheCBC;
    if (!owner->field50->field68)
    {
        owner->field50->field68 = new Rva8CB820Payload(bfmeTheCBC, -1082130432, -1, -1, -1, -1, 0, 0, bfmeTheCBC, -1, -1, -1, -1);
    }
    Rva008B0170 *result = new Rva008B0170(*(Rva008AD2C0 *)owner->field50->field68);
    if (result->m_str.m_f8 == -1)
        result->m_str.m_f8 = owner->field50->field24;
    Rva008B0D21Array *array = &owner->field50->field0c->field04->field08;
    if (owner->field50->field0c->field18 < array->field0c && owner->field50->field0c->field18 != -1 && array->field10[owner->field50->field0c->field18]->field00 == 3)
    {
        EAStringC text(array->field10[owner->field50->field0c->field18]->field08);
        result->m_str.m_block = text;
    }
    else
    {
        EAStringC text("");
        result->m_str.m_block = text;
    }
    result->m_str.m_fC = owner->field50->field3c;
    result->m_str.m_f4 = owner->field50->field60;
    return result;
}

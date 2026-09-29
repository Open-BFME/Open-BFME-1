// ?d_008b90f0@@YAXXZ
// partial score=0.212 date=2026-09-29
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// The caller at 0x008B91F0 and pin at 0x008B90F0 identify this tagged-value comparator.
struct BfmeStringData3AF0
{
    unsigned short m_refCount, m_length, m_capacity, m_flags;
};

struct BfmeStringPool3AF0
{
    void *m_unused;
    void (__cdecl *free)(void *);
};

extern BfmeStringData3AF0 g_bfmeDefaultString1284;
extern BfmeStringPool3AF0 *g_bfmeStringPool1284;
extern "C" int __cdecl strcmp(const char *, const char *);
#pragma intrinsic(strcmp)

class Rva8CD130String
{
public:
    Rva8CD130String()
    {
        m_data = &g_bfmeDefaultString1284;
        ++m_data->m_refCount;
    }

    ~Rva8CD130String()
    {
        BfmeStringData3AF0 *old = m_data;
        if (--old->m_refCount == 0)
            g_bfmeStringPool1284->free(old);
    }

    BfmeStringData3AF0 *m_data;
};

class Rva8CD130Value
{
public:
    void getName(Rva8CD130String *);
};

int __cdecl dup_008B90F0(unsigned *left, unsigned *right)
{
    Rva8CD130Value *rightValue = (Rva8CD130Value *)(*right & ~1u);
    Rva8CD130Value *leftValue = (Rva8CD130Value *)(*left & ~1u);
    Rva8CD130String leftName;
    Rva8CD130String rightName;
    leftValue->getName(&leftName);
    rightValue->getName(&rightName);
    return strcmp((const char *)leftName.m_data + 8,
                  (const char *)rightName.m_data + 8);
}

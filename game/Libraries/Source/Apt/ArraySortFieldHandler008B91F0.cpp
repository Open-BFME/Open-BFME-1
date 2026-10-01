// Retail 008B91F0. Existing bfmeHandler1233 comparator callback identity.
// 008B90F0 returns strcmp-style EAX: -1/0/+1 from tagged value arguments.
class BfmeTab1024 { public: int bfmeFind1024(int); };
extern "C" int __cdecl atoi(const char *);
extern "C" int __cdecl compareValues008B90F0(unsigned *, unsigned *);
struct BfmeBuf1233 { unsigned short refs, length; };
struct BfmeStr1233 { BfmeBuf1233 *block; };
extern BfmeStr1233 g_bfmeStr1233;
extern void *g_bfmeResult1233;
struct Value008B91F0 {
    void *vptr;
    unsigned flags;
    char field08[0x18];
    unsigned *field20;
    unsigned field24;
    int field28;
    unsigned char isType(unsigned char t) const { unsigned f = flags; return (f & 0x3f) == t && !((unsigned char)(~(f >> 15)) & 1); }
    unsigned char undefined() const { return (unsigned char)(~(flags >> 15)) & 1; }
    __forceinline unsigned get(int index) {
        if (index >= 0 && index < field28) {
            unsigned v = field20[index] & ~1u;
            if (v) return v;
        }
        return (unsigned)g_bfmeResult1233;
    }
};

struct BfmeStringData3AF0 {
    unsigned short m_refCount, m_length, m_capacity, m_flags;
};
struct BfmeStringPool3AF0 {
    void *m_unknown00;
    void (__cdecl *free)(void *);
};
extern BfmeStringData3AF0 g_bfmeDefaultString1284;
extern BfmeStringPool3AF0 *g_bfmeStringPool1284;
extern "C" int __cdecl strcmp(const char *, const char *);
#pragma intrinsic(strcmp)

class Rva8CD130String {
public:
    Rva8CD130String() {
        m_data = &g_bfmeDefaultString1284;
        ++m_data->m_refCount;
    }
    ~Rva8CD130String() {
        BfmeStringData3AF0 *old = m_data;
        if (--old->m_refCount == 0)
            g_bfmeStringPool1284->free(old);
    }
    BfmeStringData3AF0 *m_data;
};

class Rva8CD130Value {
public:
    void getName(Rva8CD130String *);
};

extern "C" int __cdecl compareValues008B90F0(unsigned *left, unsigned *right) {
    unsigned leftTagged = *left;
    unsigned rightTagged = *right;
    Rva8CD130Value *leftValue = (Rva8CD130Value *)(leftTagged & ~1u);
    Rva8CD130Value *rightValue = (Rva8CD130Value *)(rightTagged & ~1u);
    Rva8CD130String leftName;
    Rva8CD130String rightName;
    leftValue->getName(&leftName);
    rightValue->getName(&rightName);
    return strcmp((const char *)leftName.m_data + 8,
                  (const char *)rightName.m_data + 8);
}

extern "C" int bfmeHandler1233(unsigned *a, unsigned *b) {
    Value008B91F0 *left = (Value008B91F0 *)(*a & ~1u);
    Value008B91F0 *right = (Value008B91F0 *)(*b & ~1u);
    if ((left->flags & 0x3f) == 0x1b && !left->undefined() &&
        right->isType(0x1b)) {
        b = (unsigned *)((BfmeTab1024 *)&left->field08)->bfmeFind1024((int)&g_bfmeStr1233);
        if (!b) return 0;
        a = (unsigned *)((BfmeTab1024 *)&right->field08)->bfmeFind1024((int)&g_bfmeStr1233);
        if (!a) return 0;
        return compareValues008B90F0((unsigned *)&b, (unsigned *)&a);
    }
    if ((left->flags & 0x3f) == 0x16 && !left->undefined() &&
        right->isType(0x16)) {
        b = (unsigned *)left->get(atoi((char *)g_bfmeStr1233.block + 8));
        a = (unsigned *)right->get(atoi((char *)g_bfmeStr1233.block + 8));
        return compareValues008B90F0((unsigned *)&b, (unsigned *)&a);
    }
    return 0;
}

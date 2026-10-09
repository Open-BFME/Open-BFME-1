// cl: /O2 /Ob1 /G6 /GX-

// ??2@YAPAXIPAX@Z absent-from-retail
inline void *operator new(unsigned int, void *p) { return p; }

struct BfmeFalseBE {};

struct BfmeTailBE
{
    char *m_p;
    BfmeTailBE(const BfmeTailBE &);
    void copyFrom(const BfmeTailBE *src);
};

struct BfmeGroup10BE
{
    int m_10;
    int m_14;
    int m_18;
    BfmeTailBE m_1C;
    char m_20;
};

struct BfmeElemBE
{
    int m_00;
    int m_04;
    int m_08;
    int m_0C;
    BfmeGroup10BE m_10;
};

// ?bfmeCopyBE@@YAPAUBfmeElemBE@@PBU1@0PAU1@ABUBfmeFalseBE@@@Z
// Open BFME 2: Code/GameEngine/Source/Common/Rva006BE840Construction.cpp.
BfmeElemBE *bfmeCopyBE(const BfmeElemBE *first, const BfmeElemBE *last,
    BfmeElemBE *result, const BfmeFalseBE &)
{
    BfmeElemBE *cur = result;
    for (; first != last; ++first, ++cur)
        if (cur != 0)
            new (cur) BfmeElemBE(*first);
    return cur;
}

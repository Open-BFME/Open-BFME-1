// ?bfmeReportBT@BfmeHostBT@@QAEXHH@Z
// partial score=0.99 date=2026-09-09
// ?bfmeReportBT@BfmeHostBT@@QAEXHH@Z
// cl: /DNDEBUG /MD /EHs-c- /O2 /Ob2
// Retail 0x007F7C00, 103 bytes. Identity is backed by the existing relocation
// pin and by direct matched caller Rva007F7C70@BfmeHostBT; that caller builds
// the LID/GID pair which this method uses to find and clear one FESL slot.
// The nested Ids view deliberately preserves retail's induction pointer at
// slot+0x1c. The remaining six byte differences are solely the placement of
// pop edi around the two final zero stores; all operations and size match.
typedef unsigned char Byte;

extern const char g_Rva0107301CEmptyString[];

class Rva00800290Buffer
{
public:
    void append(const char *);
private:
    int data;
};

class BfmeReportTarget
{
public:
    virtual void s0() = 0; virtual void s1() = 0; virtual void s2() = 0;
    virtual void s3() = 0; virtual void s4() = 0; virtual void s5() = 0;
    virtual void s6() = 0; virtual void s7() = 0; virtual void s8() = 0;
    virtual void s9() = 0; virtual void s10() = 0; virtual void s11() = 0;
    virtual void report(int, int, int) = 0;
};

struct BfmeBTSlot
{
    int active;
    int f04;
    int f08;
    Byte f0c;
    Byte pad0d[3];
    int f10;
    Rva00800290Buffer text;
    int f18;
    struct Ids { int idB; int idA; } ids;
    Byte pad24[0x64 - 0x24];
    Byte flag64;
    Byte tail[0x94 - 0x65];
};

class BfmeHostBT
{
public:
    void bfmeReportBT(int a, int b);
private:
    Byte head[0x1c];
    BfmeReportTarget *target;
    Byte gap20[0x60 - 0x20];
    BfmeBTSlot slots[4];
};

void BfmeHostBT::bfmeReportBT(int a, int b)
{
    int i = 0;
    BfmeBTSlot::Ids *ids = &slots[0].ids;
    for (; i < 4; ++i, ids = (BfmeBTSlot::Ids *)((char *)ids + sizeof(BfmeBTSlot))) {
        BfmeBTSlot *slot = (BfmeBTSlot *)((char *)ids - 0x1c);
        if (slot->active != 0 && ids->idB == b && ids->idA == a) {
            target->report(a, b, 0);
            slot->active = 0;
            slot->f04 = 0;
            slot->f08 = 0;
            slot->f0c = 0;
            slot->f10 = 0;
            slot->text.append(g_Rva0107301CEmptyString);
            ids->idB = 0;
            ids->idA = 0;
            slot->flag64 = 0;
            return;
        }
    }
}

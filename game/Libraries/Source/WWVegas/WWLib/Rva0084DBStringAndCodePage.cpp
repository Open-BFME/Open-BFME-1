// cl: /MD /D_STLP_USE_STATIC_LIB
// stlport

struct Rva0084DBText
{
    char unused[0x14];
    const char *text;
};

const char *Rva0084DBC0GetText(const Rva0084DBText *owner)
{
    const char *text = owner->text;
    return text ? text : "";
}

// 0x0084DBE0, between the two text getters: returns the dword at 0x012C8390.
// No call, jump or pointer in the image reaches it; owner and type unproven.
extern "C" const unsigned char bfmeStrDYF[] = "true";
void *g_Va012C8390 = const_cast<unsigned char *>(bfmeStrDYF);

void *Rva0084DBE0()
{
    return g_Va012C8390;
}

const char *Rva0084DC40GetText(const Rva0084DBText *owner)
{
    const char *text = owner->text;
    return text ? text : "";
}

struct Rva0084D860CodePage
{
    unsigned int unknown;
    unsigned int codePage;
};

struct CPINFO
{
    unsigned int MaxCharSize;
    unsigned char remainder[16];
};
extern "C" {
__declspec(dllimport) int __stdcall GetCPInfo(unsigned int, CPINFO *);
}

bool Rva0084D860IsSingleByte(const Rva0084D860CodePage *owner)
{
    CPINFO info;
    GetCPInfo(owner->codePage, &info);
    return info.MaxCharSize == 1;
}

unsigned int Rva0084D820(const Rva0084D860CodePage *owner)
{
    CPINFO info;
    if (GetCPInfo(owner->codePage, &info))
        return info.MaxCharSize;
    return 0;
}

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

struct Rva0084D860CpInfo
{
    unsigned int MaxCharSize;
    unsigned char remainder[16];
};
extern "C" {
__declspec(dllimport) int __stdcall GetCPInfo(unsigned int, Rva0084D860CpInfo *);
}

bool Rva0084D860IsSingleByte(const Rva0084D860CodePage *owner)
{
    Rva0084D860CpInfo info;
    GetCPInfo(owner->codePage, &info);
    return info.MaxCharSize == 1;
}

unsigned int Rva0084D820(const Rva0084D860CodePage *owner)
{
    Rva0084D860CpInfo info;
    if (GetCPInfo(owner->codePage, &info))
        return info.MaxCharSize;
    return 0;
}

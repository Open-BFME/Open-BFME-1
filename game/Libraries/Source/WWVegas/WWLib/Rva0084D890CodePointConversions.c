// cl: /MD /D_STLP_USE_STATIC_LIB
// stlport

typedef struct Rva0084D890CodePage
{
    unsigned long locale;
    unsigned int codePage;
} Rva0084D890CodePage;

__declspec(dllimport) int __stdcall MultiByteToWideChar(
    unsigned int, unsigned long, const char *, int, unsigned short *, int);
__declspec(dllimport) int __stdcall WideCharToMultiByte(
    unsigned int, unsigned long, const unsigned short *, int, char *, int,
    const char *, int *);

unsigned short Rva0084D890ByteToWide(Rva0084D890CodePage *locale, int character)
{
    unsigned short converted;
    if (character == -1)
        return (unsigned short)-1;
    MultiByteToWideChar(locale->codePage, 1, (const char *)&character, 1, &converted, 1);
    return converted;
}

int Rva0084D8D0WideToByte(Rva0084D890CodePage *locale, unsigned short character)
{
    char converted;
    int result = WideCharToMultiByte(locale->codePage, 0x240,
        &character, 1, &converted, 1, 0, 0);
    if (!result)
        return 0xffff;
    return (signed char)converted;
}

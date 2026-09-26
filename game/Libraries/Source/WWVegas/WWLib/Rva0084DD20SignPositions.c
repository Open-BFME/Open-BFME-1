// cl: /MD /D_STLP_USE_STATIC_LIB
// stlport

typedef struct Rva0084DD20Locale
{
    unsigned long lcid;
} Rva0084DD20Locale;

__declspec(dllimport) int __stdcall GetLocaleInfoA(unsigned long, unsigned long, char *, int);
__declspec(dllimport) int __cdecl atoi(const char *);

#define BFME_LOCALE_SIGN(ADDR, FLAG)                                     \
int Rva##ADDR##Sign(Rva0084DD20Locale *locale)                           \
{                                                                       \
    char text[2];                                                       \
    GetLocaleInfoA(locale->lcid, FLAG, text, 2);                        \
    return atoi(text);                                                  \
}

BFME_LOCALE_SIGN(0084DD20, 0x52)
BFME_LOCALE_SIGN(0084DDD0, 0x53)

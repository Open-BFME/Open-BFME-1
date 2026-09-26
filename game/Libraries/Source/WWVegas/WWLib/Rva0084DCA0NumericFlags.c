// cl: /MD /D_STLP_USE_STATIC_LIB
// stlport

__declspec(dllimport) int __stdcall GetLocaleInfoA(unsigned long, unsigned long, char *, int);

typedef struct Rva0084DCALocale
{
    unsigned long lcid;
} Rva0084DCALocale;


#define BFME_LOCALE_FLAG(ADDR, FLAG)                                      \
int Rva##ADDR##Flag(Rva0084DCALocale *locale)                             \
{                                                                        \
    char value[2];                                                       \
    GetLocaleInfoA(locale->lcid, FLAG, value, 2);                        \
    if (value[0] == '0')                                                  \
        return 0;                                                        \
    return value[0] == '1' ? 1 : -1;                                     \
}

BFME_LOCALE_FLAG(0084DCA0, 0x54)
BFME_LOCALE_FLAG(0084DCE0, 0x55)
BFME_LOCALE_FLAG(0084DD50, 0x56)
BFME_LOCALE_FLAG(0084DD90, 0x57)

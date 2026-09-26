// STLport 4.5.3 Win32 _Locale_wctomb.

typedef struct _Locale_ctype_t
{
    unsigned long lcid;
    unsigned int cp;
} _Locale_ctype_t;

typedef int mbstate_t;

__declspec(dllimport) int __stdcall WideCharToMultiByte(
    unsigned int codePage, unsigned long flags, const unsigned short *source,
    int sourceCount, char *destination, int destinationCount,
    const char *defaultChar, int *usedDefaultChar);

unsigned int _Locale_wctomb(_Locale_ctype_t *ltype, char *to, unsigned int n,
    const unsigned short c, mbstate_t *st)
{
    int size;

    size = WideCharToMultiByte(ltype->cp, 0x220, &c, 1, 0, 0, 0, 0);
    if ((unsigned int)size > n)
        return (unsigned int)-2;

    size = WideCharToMultiByte(ltype->cp, 0x220, &c, 1, to, n, 0, 0);
    if (size == 0)
        return (unsigned int)-1;
    return (unsigned int)size;
}

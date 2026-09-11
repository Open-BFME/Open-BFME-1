// cl: /O2 /MD
// STLport 4.5.3 Win32 _Locale_mbtowc.

typedef unsigned int size_t;
typedef unsigned long LCID;
typedef unsigned int UINT;
typedef int mbstate_t;
typedef unsigned short wchar_t;

#define _LEADBYTE 0x8000
#define MB_PRECOMPOSED 1

typedef struct _CPINFO
{
    UINT MaxCharSize;
    unsigned char DefaultChar[2];
    unsigned char LeadByte[12];
} CPINFO;

typedef struct _Locale_ctype
{
    LCID lcid;
    UINT cp;
    unsigned int ctable[257];
} _Locale_ctype_t;

__declspec(dllimport) int __stdcall GetCPInfo(UINT codePage, CPINFO *info);
__declspec(dllimport) int __stdcall MultiByteToWideChar(
    UINT codePage, unsigned long flags, const char *source, int sourceCount,
    wchar_t *destination, int destinationCount);

static int __isleadbyte(int c, unsigned int *ctable)
{
    return (ctable[(unsigned char)c] & _LEADBYTE);
}

static size_t __mbtowc(_Locale_ctype_t *l, wchar_t *destination, char source,
    mbstate_t *shiftState)
{
    int result;

    if (*shiftState == 0)
    {
        if (__isleadbyte(source, l->ctable))
        {
            ((unsigned char *)shiftState)[0] = source;
            return (size_t)-2;
        }
        result = MultiByteToWideChar(l->cp, MB_PRECOMPOSED, &source, 1,
            destination, 1);
        if (result == 0)
            return (size_t)-1;
        return 1;
    }

    ((unsigned char *)shiftState)[1] = source;
    result = MultiByteToWideChar(l->cp, MB_PRECOMPOSED,
        (const char *)shiftState, 2, destination, 1);
    *shiftState = 0;
    if (result == 0)
        return (size_t)-1;
    return 1;
}

size_t _Locale_mbtowc(_Locale_ctype_t *ltype, wchar_t *to,
    const char *from, size_t n, mbstate_t *shiftState)
{
    CPINFO ci;
    int result;

    GetCPInfo(ltype->cp, &ci);
    if (ci.MaxCharSize == 1)
    {
        *shiftState = (mbstate_t)0;
        result = MultiByteToWideChar(ltype->cp, MB_PRECOMPOSED, from, 1,
            to, 1);
        if (result == 0)
            return (size_t)-1;
        return result;
    }

    {
        size_t retval;
        size_t count = 0;
        while (n--)
        {
            retval = __mbtowc(ltype, to, *from, shiftState);
            if (retval == (size_t)-2)
            {
                ++from;
                ++count;
            }
            else if (retval == (size_t)-1)
                return (size_t)-1;
            else
                return count + retval;
        }
        if (retval == (size_t)-2)
            return (size_t)-2;
        return n;
    }
}

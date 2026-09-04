// cl: /O2 /MD
// STLport 4.5.3 _Locale_toupper/_Locale_tolower/_Locale_strcmp.
typedef unsigned long LCID;
typedef unsigned int UINT;

__declspec(dllimport) int __stdcall GetLocaleInfoA(
    LCID locale, unsigned long type, char *data, int count);
__declspec(dllimport) int __cdecl atoi(const char *text);
__declspec(dllimport) int __stdcall LCMapStringA(
    LCID locale, unsigned long flags, const char *src, int srcCount,
    char *dest, int destCount);
__declspec(dllimport) int __stdcall MultiByteToWideChar(
    unsigned int codePage, unsigned long flags, const char *source, int sourceCount,
    unsigned short *destination, int destinationCount);
__declspec(dllimport) int __stdcall WideCharToMultiByte(
    unsigned int codePage, unsigned long flags, const unsigned short *source,
    int sourceCount, char *destination, int destinationCount,
    const char *defaultChar, int *usedDefaultChar);
__declspec(dllimport) int __stdcall CompareStringA(
    LCID locale, unsigned long flags, const char *a, int aCount,
    const char *b, int bCount);
__declspec(dllimport) void *__cdecl malloc(unsigned int size);
__declspec(dllimport) void __cdecl free(void *memory);

typedef struct _Locale_ctype_t {
    LCID lcid;
    UINT cp;
} _Locale_ctype_t;

typedef struct _Locale_collate_t {
    LCID lcid;
    char cp[6];
} _Locale_collate_t;

typedef unsigned int bfme_size_t;

static int __intGetACP(LCID lcid)
{
    char cp[6];
    GetLocaleInfoA(lcid, 0x1004, cp, 6);
    return atoi(cp);
}

static int __intGetOCP(LCID lcid)
{
    char cp[6];
    GetLocaleInfoA(lcid, 0xb, cp, 6);
    return atoi(cp);
}

static int __GetDefaultCP(LCID lcid)
{
    int cp = __intGetACP(lcid);
    if (cp == 0)
        return __intGetOCP(lcid);
    return cp;
}

static char *__ConvertToCP(int from_cp, int to_cp, const char *from,
    bfme_size_t size, bfme_size_t *ret_buf_size)
{
    int wideSize;
    int bufferSize;
    unsigned short *wideBuffer;
    char *buffer;

    wideSize = MultiByteToWideChar(from_cp, 1, from, (int)size, 0, 0);
    wideBuffer = (unsigned short *)malloc(sizeof(unsigned short) * wideSize);
    MultiByteToWideChar(from_cp, 1, from, (int)size, wideBuffer, wideSize);
    bufferSize = WideCharToMultiByte(to_cp, 0x220, wideBuffer, wideSize, 0, 0, 0, 0);
    buffer = (char *)malloc(bufferSize);
    WideCharToMultiByte(to_cp, 0x220, wideBuffer, wideSize, buffer, bufferSize, 0, 0);
    free(wideBuffer);
    *ret_buf_size = bufferSize;
    return buffer;
}

int _Locale_toupper(_Locale_ctype_t *ltype, int c)
{
    char buf[2], out_buf[2];
    buf[0] = (char)c;
    buf[1] = 0;
    if ((UINT)__GetDefaultCP(ltype->lcid) == ltype->cp) {
        LCMapStringA(ltype->lcid, 0x01000200, buf, 2, out_buf, 2);
        return (signed char)out_buf[0];
    } else {
        unsigned short wbuf[2];
        MultiByteToWideChar(ltype->cp, 1, buf, 2, wbuf, 2);
        WideCharToMultiByte(__GetDefaultCP(ltype->lcid), 0x220, wbuf, 2, buf, 2, 0, 0);
        LCMapStringA(ltype->lcid, 0x01000200, buf, 2, out_buf, 2);
        MultiByteToWideChar(__GetDefaultCP(ltype->lcid), 1, out_buf, 2, wbuf, 2);
        WideCharToMultiByte(ltype->cp, 0x220, wbuf, 2, out_buf, 2, 0, 0);
        return (signed char)out_buf[0];
    }
}

int _Locale_tolower(_Locale_ctype_t *ltype, int c)
{
    char buf[2], out_buf[2];
    buf[0] = (char)c;
    buf[1] = 0;
    if ((UINT)__GetDefaultCP(ltype->lcid) == ltype->cp) {
        LCMapStringA(ltype->lcid, 0x01000100, buf, 2, out_buf, 2);
        return (signed char)out_buf[0];
    } else {
        unsigned short wbuf[2];
        MultiByteToWideChar(ltype->cp, 1, buf, 2, wbuf, 2);
        WideCharToMultiByte(__GetDefaultCP(ltype->lcid), 0x220, wbuf, 2, buf, 2, 0, 0);
        LCMapStringA(ltype->lcid, 0x01000100, buf, 2, out_buf, 2);
        MultiByteToWideChar(__GetDefaultCP(ltype->lcid), 1, out_buf, 2, wbuf, 2);
        WideCharToMultiByte(ltype->cp, 0x220, wbuf, 2, out_buf, 2, 0, 0);
        return (signed char)out_buf[0];
    }
}

int _Locale_strcmp(_Locale_collate_t *lcol,
    const char *s1, bfme_size_t n1,
    const char *s2, bfme_size_t n2)
{
    int result;
    if (__GetDefaultCP(lcol->lcid) == atoi(lcol->cp)) {
        result = CompareStringA(lcol->lcid, 0, s1, (int)n1, s2, (int)n2);
    } else {
        char *buf1, *buf2;
        bfme_size_t size1, size2;
        buf1 = __ConvertToCP(atoi(lcol->cp), __GetDefaultCP(lcol->lcid), s1, n1, &size1);
        buf2 = __ConvertToCP(atoi(lcol->cp), __GetDefaultCP(lcol->lcid), s2, n2, &size2);
        result = CompareStringA(lcol->lcid, 0, buf1, (int)size1, buf2, (int)size2);
        free(buf1);
        free(buf2);
    }
    return (result == 2) ? 0 : (result == 1) ? -1 : 1;
}

int KeepDefaultCPA(LCID lcid) { return __GetDefaultCP(lcid); }
int KeepDefaultCPB(LCID lcid) { return __GetDefaultCP(lcid) + 1; }

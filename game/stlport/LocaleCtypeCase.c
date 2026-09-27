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

// OPAQUE: 0x0084EBC0 (224 B). IDENTITY IS NOT RECOVERED: no caller,
// string or vtable names the holder, so the name is derived from its own
// address. Same-TU STLport _Locale_strcmp twin above, proved slot by slot:
// the arg-1 object pointer arrives first in ebx (mov ebx,[esp+0x18]) with
// the LCID at +0 and the code-page text at +4; the inline
// GetLocaleInfoA(LOCALE_IDEFAULTANSICODEPAGE)/atoi pair with the
// LOCALE_IDEFAULTCODEPAGE fallback computes the default, and equality with
// atoi([ebx+4]) takes the single LCMapStringA(..., 0x400, ...) direct map.
// Else __GetDefaultCP + __ConvertToCP convert src into a malloced buffer,
// LCMapStringA maps that buffer, and the buffer is freed. The destination
// pair precedes the source pair in the argument list (retail reads dest at
// [esp+0x2c] before src at [esp+0x34]). Probed EXACT (modulo relocations).
//
// _dup_0084EBC0
int dup_0084EBC0(_Locale_collate_t *lcol, char *s2, bfme_size_t n2,
    const char *s1, bfme_size_t n1)
{
    int result;
    if (__GetDefaultCP(lcol->lcid) == atoi(lcol->cp)) {
        result = LCMapStringA(lcol->lcid, 0x400, s1, (int)n1, s2, (int)n2);
    } else {
        char *buf1;
        bfme_size_t size1;
        buf1 = __ConvertToCP(atoi(lcol->cp), __GetDefaultCP(lcol->lcid), s1, n1, &size1);
        result = LCMapStringA(lcol->lcid, 0x400, buf1, (int)size1, s2, (int)n2);
        free(buf1);
    }
    return result;
}

int KeepDefaultCPA(LCID lcid) { return __GetDefaultCP(lcid); }
int KeepDefaultCPB(LCID lcid) { return __GetDefaultCP(lcid) + 1; }

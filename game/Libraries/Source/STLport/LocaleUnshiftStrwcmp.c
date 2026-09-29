/* STLport 4.5.3 c_locale_win32.c: _Locale_unshift (0x0084DAF0, 63 B) and
   _Locale_strwcmp (0x0084DB30, 58 B). Both follow the matched _Locale_wctomb
   (0x0084DA90); neither has a reference left in retail. The former 122-byte
   gen-dump covered both: _Locale_unshift ends at a ret plus int3 padding, and
   _Locale_strwcmp starts at the next 16-byte boundary (CompareStringW). */
typedef unsigned int size_t;
typedef unsigned short wchar_t;
typedef int mbstate_t;
typedef unsigned long LCID;
__declspec(dllimport) int __stdcall CompareStringW(LCID, unsigned long, const wchar_t *, int, const wchar_t *, int);

#define CSTR_LESS_THAN 1
#define CSTR_EQUAL 2

struct _Locale_ctype;
struct _Locale_collate { LCID lcid; };

size_t _Locale_unshift(struct _Locale_ctype *ltype, mbstate_t *st,
                       char *buf, size_t n, char **next)
{
  if (*st == 0) {
    *next = buf;
    return 0;
  }
  else {
    if (n < 1) { *next = buf; return (size_t)-2; }
    *next = buf + 1;
    return 1;
  }
}

int _Locale_strwcmp(struct _Locale_collate *lcol,
                    const wchar_t *s1, size_t n1, const wchar_t *s2, size_t n2)
{
  int result;
  result = CompareStringW(lcol->lcid, 0, s1, n1, s2, n2);
  if (result == CSTR_EQUAL) return 0;
  return result == CSTR_LESS_THAN ? -1 : 1;
}

/* STLport 4.5.3 c_locale_win32.c: __Extract_locale_name (0x0084E440, 153 B).
   Retail keeps only this static, with a compiler-private ABI (loc in EAX,
   category in ECX, buf in EBX) and no remaining references. The
   _Locale_extract_*_name callers that gave it that ABI were not linked into
   retail; they are kept here, marked absent-from-retail, so the compiler still
   sees its call sites. The table and ";" literal are retail's (0x012C8398:
   LC_ALL, LC_COLLATE, LC_CTYPE, LC_MONETARY, LC_NUMERIC, LC_TIME). */
typedef unsigned int size_t;
__declspec(dllimport) char *__cdecl strstr(const char *, const char *);
__declspec(dllimport) char *__cdecl strchr(const char *, int);
__declspec(dllimport) size_t __cdecl strcspn(const char *, const char *);
__declspec(dllimport) char *__cdecl strncpy(char *, const char *, size_t);

#define LC_ALL 0
#define LC_MAX 5
#define _Locale_MAX_SIMPLE_NAME 256

/* Retail 0x012C8398, six pointers: c_locale_win32.c's category-name table,
   indexed by the LC_* category this file range-checks. */
const char *__category_name[] = {"LC_ALL", "LC_COLLATE", "LC_CTYPE", "LC_MONETARY", "LC_NUMERIC", "LC_TIME"};

static const char *__Extract_locale_name(const char *loc, int category, char *buf)
{
  char *expr;
  size_t len_name;
  buf[0] = 0;

  if (category < LC_ALL || category > LC_MAX) return 0;

  if (loc[0] == 'L' && loc[1] == 'C' && loc[2] == '_') {
    expr = strstr((char*)loc, __category_name[category]);
    if (expr == 0) return 0; /* Category not found. */
    expr = strchr(expr, '=');
    if (expr == 0) return 0;
    ++expr;
    len_name = strcspn(expr, ";");
    len_name = len_name > _Locale_MAX_SIMPLE_NAME ? _Locale_MAX_SIMPLE_NAME : len_name;
    strncpy(buf, expr, len_name); buf[len_name] = 0;
    return buf;
  }
  else {
    return strncpy(buf, loc, _Locale_MAX_SIMPLE_NAME);
  }
}

// _Locale_extract_ctype_name absent-from-retail
const char *_Locale_extract_ctype_name(const char *cname, char *buf) { return __Extract_locale_name(cname, 2, buf); }
// _Locale_extract_numeric_name absent-from-retail
const char *_Locale_extract_numeric_name(const char *cname, char *buf) { return __Extract_locale_name(cname, 4, buf); }
// _Locale_extract_time_name absent-from-retail
const char *_Locale_extract_time_name(const char *cname, char *buf) { return __Extract_locale_name(cname, 5, buf); }
// _Locale_extract_collate_name absent-from-retail
const char *_Locale_extract_collate_name(const char *cname, char *buf) { return __Extract_locale_name(cname, 1, buf); }
// _Locale_extract_monetary_name absent-from-retail
const char *_Locale_extract_monetary_name(const char *cname, char *buf) { return __Extract_locale_name(cname, 3, buf); }

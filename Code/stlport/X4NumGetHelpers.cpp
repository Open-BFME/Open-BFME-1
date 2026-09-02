// stlport
// STLport 4.5.3 numeric-input helpers from src/num_get.cpp.

#include <algorithm>
#include <locale>

_STLP_BEGIN_NAMESPACE

bool _STLP_CALL __valid_grouping(const char *first1, const char *last1,
                                 const char *first2, const char *last2)
{
  if (first1 == last1 || first2 == last2)
    return true;

  --last1;
  --last2;

  while (first1 != last1) {
    if (*last1 != *first2)
      return false;
    --last1;
    if (first2 != last2)
      ++first2;
  }

  return *last1 <= *first2;
}

#ifndef _STLP_NO_WCHAR_T

bool _STLP_CALL __get_fdigit(wchar_t &c, const wchar_t *digits)
{
  const wchar_t *p = find(digits, digits + 10, c);
  if (p != digits + 10) {
    c = (char)('0' + (p - digits));
    return true;
  }
  return false;
}

bool _STLP_CALL __get_fdigit_or_sep(wchar_t &c, wchar_t sep,
                                    const wchar_t *digits)
{
  if (c == sep) {
    c = (char)',';
    return true;
  }
  return __get_fdigit(c, digits);
}

#endif

_STLP_END_NAMESPACE

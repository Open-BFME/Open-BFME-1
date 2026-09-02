// stlport
// STLport 4.5.3 ctype scan helpers, reduced to the retail bodies recovered
// from src/ctype.cpp.

#include <algorithm>
#include <stl/_ctype.h>
#include <stl/_function.h>

_STLP_BEGIN_NAMESPACE

#ifndef _STLP_NO_WCHAR_T

struct _Ctype_w_is_mask
{
  typedef wchar_t argument_type;
  typedef bool result_type;

  ctype_base::mask M;
  const ctype_base::mask *table;

  _Ctype_w_is_mask(ctype_base::mask m, const ctype_base::mask *t)
    : M(m), table(t) {}

  bool operator()(wchar_t c) const
  {
    return c >= 0 && size_t(c) < ctype<char>::table_size && (table[c] & M);
  }
};

template const wchar_t *__find_if(
  const wchar_t *, const wchar_t *, unary_negate<_Ctype_w_is_mask>,
  const random_access_iterator_tag &);

#endif

_STLP_END_NAMESPACE

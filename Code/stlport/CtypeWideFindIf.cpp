// cl: /EHsc /MD
// stlport
// STLport 4.5.3 ctype wide scan_is helper: __find_if + mask table.

#include <algorithm>
#include <stl/_ctype.h>
#include <stl/_iterator_base.h>

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
  const wchar_t *, const wchar_t *, _Ctype_w_is_mask,
  const random_access_iterator_tag &);

#endif

_STLP_END_NAMESPACE

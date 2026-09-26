// cl: /O2 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
// STLport 4.5.3 src/ctype.cpp: ctype<wchar_t>::do_scan_is/do_scan_not.

#include <algorithm>
#include <functional>
#include <stl/_ctype.h>

_STLP_BEGIN_NAMESPACE

#ifndef _STLP_NO_WCHAR_T

struct _Ctype_w_is_mask : public unary_function<wchar_t, bool>
{
	ctype_base::mask M;
	const ctype_base::mask *table;

	_Ctype_w_is_mask(ctype_base::mask m, const ctype_base::mask *t)
		: M(m), table(t) {}

	bool operator()(wchar_t c) const
	{
		return c >= 0 && size_t(c) < ctype<char>::table_size && (table[c] & M);
	}
};

const wchar_t *ctype<wchar_t>::do_scan_is(ctype_base::mask m,
	const wchar_t *low, const wchar_t *high) const
{
	return find_if(low, high,
		_Ctype_w_is_mask(m, ctype<char>::classic_table()));
}

const wchar_t *ctype<wchar_t>::do_scan_not(ctype_base::mask m,
	const wchar_t *low, const wchar_t *high) const
{
	return find_if(low, high,
		not1(_Ctype_w_is_mask(m, ctype<char>::classic_table())));
}

#endif

_STLP_END_NAMESPACE

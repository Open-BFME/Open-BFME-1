// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport
// STLport 4.5.3 src/ctype.cpp: ctype<char>::scan_not, retail 0x00840F00.
// Callers: _M_ignore_buffered<char, _Is_not_wspace, _Scan_for_not_wspace>
// (0x00539BC0) and the _Scan_for_not_wspace forwarder 0x005381C0, which passes
// ctype_base::space (8). symbols.csv pins ?scan_not@?$ctype@D@_STL at this
// address. Same shape as scan_is (CtypeCharFindIf.cpp) under unary_negate.

#include <algorithm>
#include <stl/_function.h>
#include <stl/_iterator_base.h>
#include <stl/_ctype.h>

_STLP_BEGIN_NAMESPACE

struct _Ctype_c_is_mask
{
	typedef char argument_type;
	typedef bool result_type;
	unsigned int M;
	const ctype_base::mask *table;

	_Ctype_c_is_mask(unsigned int mask, const ctype_base::mask *value)
		: M(mask), table(value) {}

	bool operator()(unsigned char c) const
	{
		return (table[c] & M) != 0;
	}
};

extern template const char *__find_if(const char *, const char *,
	unary_negate<_Ctype_c_is_mask>, const random_access_iterator_tag &);

const char *ctype<char>::scan_not(mask m, const char *first,
	const char *last) const
{
	return __find_if(first, last, not1(_Ctype_c_is_mask(m, table())),
		random_access_iterator_tag());
}

_STLP_END_NAMESPACE

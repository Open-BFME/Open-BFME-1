// cl: /EHsc /MD
// stlport
// STLport 4.5.3 ctype<char> scan_not helper: __find_if + unary_negate mask.

#include <algorithm>
#include <stl/_iterator_base.h>
#include <stl/_function.h>

_STLP_BEGIN_NAMESPACE

struct _Ctype_c_is_mask
{
	typedef char argument_type;
	typedef bool result_type;
	unsigned int M;
	const unsigned int *table;
	bool operator()(unsigned char c) const
	{
		return (table[c] & M) != 0;
	}
};

template const char *__find_if(
	const char *, const char *, unary_negate<_Ctype_c_is_mask>,
	const random_access_iterator_tag &);

_STLP_END_NAMESPACE

const char *Rva00840D70(const char *first, const char *last,
	_STL::unary_negate<_STL::_Ctype_c_is_mask> predicate)
{
	return _STL::find_if(first, last, predicate);
}

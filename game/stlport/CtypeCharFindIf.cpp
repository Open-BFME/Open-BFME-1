// cl: /EHsc /MD
// stlport
// STLport 4.5.3 ctype<char> scan_is helper: __find_if + mask table.

#include <algorithm>
#include <stl/_iterator_base.h>

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
	const char *, const char *, _Ctype_c_is_mask,
	const random_access_iterator_tag &);

_STLP_END_NAMESPACE

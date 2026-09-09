// ?invoke@Open2381C0Impl@@QAEXHPAX0@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport

#include <algorithm>
#include <stl/_function.h>
#include <stl/_iterator_base.h>

_STLP_BEGIN_NAMESPACE

struct _Ctype_c_is_mask
{
	typedef char argument_type;
	typedef bool result_type;
	unsigned int M;
	const unsigned int *table;

	_Ctype_c_is_mask(unsigned int mask, const unsigned int *value)
		: M(mask), table(value) {}

	bool operator()(unsigned char c) const
	{
		return (table[c] & M) != 0;
	}
};

extern template const char *__find_if(const char *, const char *,
	unary_negate<_Ctype_c_is_mask>, const random_access_iterator_tag &);

_STLP_END_NAMESPACE

class Open2381C0Impl
{
public:
	void invoke(int kind, void *first, void *last);

	char m_pad00[0xc];
	const unsigned int *m_table;
};

void Open2381C0Impl::invoke(int kind, void *first, void *last)
{
	_STL::_Ctype_c_is_mask mask((unsigned int)kind, m_table);
	_STL::__find_if((const char *)first, (const char *)last, _STL::not1(mask), _STL::random_access_iterator_tag());
}

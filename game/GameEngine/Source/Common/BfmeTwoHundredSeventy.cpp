// cl: /Od
// The retail 0x3DA4B ILT reaches the matched STLport find_last_not_of body at
// 0x00654BE0. This passes a pair of ends as the start and length, built without
// optimisation.

// stlport
#include <string>

namespace _STL
{
	template <> basic_string<char, char_traits<char>, allocator<char> >::size_type
	basic_string<char, char_traits<char>, allocator<char> >::find_last_not_of(
		const char *, size_type, size_type) const;
}

struct BfmeRangePJ
{
	char *m_bfmeAt;				// 0x0
	char *m_bfmeEnd;			// 0x4
};

class BfmeThingPJ
{
public:
	void bfmeGoPJ(const BfmeRangePJ *span, void *what);
};

void BfmeThingPJ::bfmeGoPJ(const BfmeRangePJ *span, void *what)
{
	((const _STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > *)this)
		->find_last_not_of(span->m_bfmeAt, (unsigned int)what,
			(unsigned int)(span->m_bfmeEnd - span->m_bfmeAt));
}

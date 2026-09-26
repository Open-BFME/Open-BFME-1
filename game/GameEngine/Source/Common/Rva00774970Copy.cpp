// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

// Open-BFME: anonymous STLport copy helper at retail 0x00774970.
//
// The named vector erase caller at 0x00777EE0 calls ILT 0x00044EE5 at
// 0x00777EFB; that ILT jumps directly here. The wrapper at 0x007762A0
// also calls the same ILT. The retail loop walks
// 0x2c-byte records forward, so this body is the STLport __copy helper despite
// the stale generated __copy_backward labels.  Each record has three
// 12-byte basic_string<char> objects followed
// by two dwords; the three string assignments all call the same
// _M_assign_dispatch<char> body.

#include <string>

struct Rva00774970Element
{
	_STL::basic_string<char> m_first;
	_STL::basic_string<char> m_second;
	_STL::basic_string<char> m_third;
	int m_tail0;
	int m_tail1;
};

namespace _STL
{
template Rva00774970Element *__copy<
	Rva00774970Element *, Rva00774970Element *, int>(
	Rva00774970Element *, Rva00774970Element *, Rva00774970Element *,
	const random_access_iterator_tag &, int *);
}

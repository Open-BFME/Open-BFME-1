// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/stringinline
// stlport
//
// Retail 0x003AAFE0 is the STLport vector copy constructor for the
// sixteen-byte Gen_t_003aafe0 record: one AsciiString at +0 and three
// integers at +4/+8/+12. The element copy reads forward from &other.m_first;
// the backward-from-last spelling leaves four operand bytes off.

#define _STLP_NO_EXCEPTIONS 1
#include <vector>
#include "StringInline.h"

struct Gen_t_003aafe0
{
	AsciiString m_text;
	int m_first;
	int m_second;
	int m_third;
	Gen_t_003aafe0(const Gen_t_003aafe0 &other) : m_text(other.m_text)
	{
		const int *first = &other.m_first;
		m_first = first[0];
		m_second = first[1];
		m_third = first[2];
	}
};

template _STL::vector<Gen_t_003aafe0, _STL::allocator<Gen_t_003aafe0> >::vector(
	const _STL::vector<Gen_t_003aafe0, _STL::allocator<Gen_t_003aafe0> > &);

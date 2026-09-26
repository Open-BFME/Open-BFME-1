// ??0?$vector@UGen_t_003aafe0@@V?$allocator@UGen_t_003aafe0@@@_STL@@@_STL@@QAE@ABV01@@Z
// partial score=0.98 date=2026-09-26
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/stringinline
// stlport
// Retail 0x003AAFE0: vector copy for a sixteen-byte record with a string and three integers.
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
		const int *last = &other.m_third;
		m_first = last[-2];
		m_second = last[-1];
		m_third = last[0];
	}
};

template _STL::vector<Gen_t_003aafe0, _STL::allocator<Gen_t_003aafe0> >::vector(
	const _STL::vector<Gen_t_003aafe0, _STL::allocator<Gen_t_003aafe0> > &);

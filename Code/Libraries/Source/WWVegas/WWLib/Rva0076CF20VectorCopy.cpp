// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <new>
#include "../../../../../reference/shims/stringinline/StringInline.h"
#include <vector>

struct Open2Elem7716A0
{
	int m_word00;
	int m_word04;
	int m_word08;
	AsciiString m_room0C;
	int m_word10;

	~Open2Elem7716A0();
};

template class _STL::vector<Open2Elem7716A0>;

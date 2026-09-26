// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

// Out-of-line STLport random-access copy specialization at retail 0x007748D0.
// The vector<Gen_t_00777e90_p32cd>::erase instantiation at 0x00777E90 reaches
// this body through ILT 0x0001C4DB.  Its 0x20-byte element contains an int,
// a basic_string<char>, three further ints, and a final int.  Using the real
// STLport string is significant: its assignment gives MSVC 7.1 the same
// dead-stack-slot coalescing as retail.

#include <string>

struct Gen_t_00777e90_p32cd
{
	struct Tail3
	{
		int words[3];
	};

	int m_first;
	_STL::basic_string<char> m_string;
	Tail3 m_tail;
	int m_last;
};

namespace _STL
{
template Gen_t_00777e90_p32cd *__copy<Gen_t_00777e90_p32cd *,
	Gen_t_00777e90_p32cd *, int>(Gen_t_00777e90_p32cd *,
	Gen_t_00777e90_p32cd *, Gen_t_00777e90_p32cd *,
	const random_access_iterator_tag &, int *);
}

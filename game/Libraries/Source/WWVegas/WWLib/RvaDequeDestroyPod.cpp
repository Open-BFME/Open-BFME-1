// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// The retail loop advances a deque iterator by a 20-byte value over 0x78-byte
// nodes and performs no destructor call; this is the trivial-payload overload
// of STLport's range __destroy.

#include <deque>

struct Gen_t_008fb350_p12pod { char m_body[20]; };

namespace _STL
{
template void __destroy<
	_Deque_iterator<Gen_t_008fb350_p12pod,
		_Nonconst_traits<Gen_t_008fb350_p12pod> >,
	Gen_t_008fb350_p12pod>(
	_Deque_iterator<Gen_t_008fb350_p12pod,
		_Nonconst_traits<Gen_t_008fb350_p12pod> >,
	_Deque_iterator<Gen_t_008fb350_p12pod,
		_Nonconst_traits<Gen_t_008fb350_p12pod> >,
	Gen_t_008fb350_p12pod *);
}

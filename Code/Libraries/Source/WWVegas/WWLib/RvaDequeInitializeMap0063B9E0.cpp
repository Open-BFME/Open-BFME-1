// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /D_STLP_USE_STATIC_LIB
// stlport

// ?_M_initialize_map@?$_Deque_base@UGen_t_0063bd90_p12cd@@V?$allocator@UGen_t_0063bd90_p12cd@@@_STL@@@_STL@@IAEXI@Z

#define _STLP_NO_EXCEPTIONS 1
#include <deque>

struct Gen_t_0063bd90_p12cd
{
	char m_body[0x864];
};

namespace _STL
{
template void _Deque_base<Gen_t_0063bd90_p12cd,
	allocator<Gen_t_0063bd90_p12cd> >::_M_initialize_map(unsigned int);
}

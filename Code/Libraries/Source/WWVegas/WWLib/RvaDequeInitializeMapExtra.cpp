// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /D_STLP_USE_STATIC_LIB
// stlport

// These two retail bodies are the same STLport _M_initialize_map template
// instantiated for two independent 20-byte deque element layouts.  The
// retail divide-by-six and 0x78 node span fix that element width exactly.

#define _STLP_NO_EXCEPTIONS 1
#include <deque>
#include <new>

struct Gen_t_0065f6f0_p12cd { char m_body[20]; };
struct Gen_t_0065f750_p12cd { char m_body[20]; };
struct Gen_t_0058f2f0_p12cd { char m_body[12]; };
struct Gen_t_00590820_p12cd { char m_body[12]; };
struct Gen_t_00640d30_p12cd { char m_body[28]; };
struct Gen_t_00653850_p12cd { char m_body[0x210]; };

void BfmeDequeInitAnchor0065f230(void *place)
{
	new (place) _STL::deque<Gen_t_0065f6f0_p12cd>();
}

void BfmeDequeInitAnchor0065f3a0(void *place)
{
	new (place) _STL::deque<Gen_t_0065f750_p12cd>();
}

void BfmeDequeInitAnchor0058cb10(void *place)
{
	new (place) _STL::deque<Gen_t_0058f2f0_p12cd>();
}

namespace _STL
{
template void _Deque_base<Gen_t_0065f6f0_p12cd,
	allocator<Gen_t_0065f6f0_p12cd> >::_M_initialize_map(unsigned int);
template void _Deque_base<Gen_t_0065f750_p12cd,
	allocator<Gen_t_0065f750_p12cd> >::_M_initialize_map(unsigned int);
template void _Deque_base<Gen_t_0058f2f0_p12cd,
	allocator<Gen_t_0058f2f0_p12cd> >::_M_initialize_map(unsigned int);
template void _Deque_base<Gen_t_00590820_p12cd,
	allocator<Gen_t_00590820_p12cd> >::_M_initialize_map(unsigned int);
template void _Deque_base<Gen_t_00640d30_p12cd,
	allocator<Gen_t_00640d30_p12cd> >::_M_initialize_map(unsigned int);
template void _Deque_base<Gen_t_00653850_p12cd,
	allocator<Gen_t_00653850_p12cd> >::_M_initialize_map(unsigned int);
}

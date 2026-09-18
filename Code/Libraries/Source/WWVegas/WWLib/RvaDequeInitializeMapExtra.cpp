// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /D_STLP_USE_STATIC_LIB
// stlport

// These retail bodies are STLport _M_initialize_map template instantiations
// for the element layouts named below.  The node allocation and division
// shapes fix each element width exactly.

#define _STLP_NO_EXCEPTIONS 1
#include <deque>
#include <new>

struct Gen_t_0065f6f0_p12cd { char m_body[20]; };
struct Gen_t_0065f750_p12cd { char m_body[20]; };
struct Gen_t_0058f2f0_p12cd { char m_body[12]; };
struct Gen_t_00590820_p12cd { char m_body[12]; };
struct Gen_t_00640d30_p12cd { char m_body[28]; };
struct Gen_t_00653850_p12cd { char m_body[0x210]; };
struct Gen_t_006538b0_p12cd { char m_body[0x1f0]; };
struct Gen_t_006543a0_p12cd { char m_body[0x1f0]; };
// GameSpyBuddyMessageQueue calls this body for its 0x2B8-byte BuddyRequest
// deque, and retail allocates one 0x2B8-byte element per node.
class BuddyRequest { char m_bfmeBody[0x2B8]; };

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
template void _Deque_base<Gen_t_006538b0_p12cd,
	allocator<Gen_t_006538b0_p12cd> >::_M_initialize_map(unsigned int);
template void _Deque_base<Gen_t_006543a0_p12cd,
	allocator<Gen_t_006543a0_p12cd> >::_M_initialize_map(unsigned int);
template void _Deque_base<BuddyRequest,
	allocator<BuddyRequest> >::_M_initialize_map(unsigned int);
}

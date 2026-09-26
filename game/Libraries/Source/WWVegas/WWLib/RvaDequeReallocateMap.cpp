// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// Open-BFME5: STLport deque::_M_reallocate_map, nine generated bodies. Their
// decorated identities and boundaries are established by the retail call
// sites; the element type affects only the deque's node width.

#include <deque>

// The p12cd suffix is a generated shape label, not sizeof(T).  The retail
// _M_set_node increments pin these four payload sizes directly.
struct Gen_t_00646a10_p12cd { char m_body[404]; };
struct Gen_t_00646a40_p12cd { char m_body[816]; };
struct Gen_t_00654750_p12cd { char m_body[528]; };
struct Gen_t_00654780_p12cd { char m_body[496]; };
struct Gen_t_0063c490_p12cd { char m_body[696]; };
struct Gen_t_0063c4c0_p12cd { char m_body[2148]; };
struct Gen_t_0065fd10_p12cd { char m_body[12]; };
struct Gen_t_0065fd40_p12cd { char m_body[12]; };
struct Gen_t_00593270_p12cd { char m_body[12]; };

namespace _STL
{
template void deque<Gen_t_00646a10_p12cd, allocator<Gen_t_00646a10_p12cd> >::_M_reallocate_map(
	unsigned int, bool);
template void deque<Gen_t_00646a40_p12cd, allocator<Gen_t_00646a40_p12cd> >::_M_reallocate_map(
	unsigned int, bool);
template void deque<Gen_t_00654750_p12cd, allocator<Gen_t_00654750_p12cd> >::_M_reallocate_map(
	unsigned int, bool);
template void deque<Gen_t_00654780_p12cd, allocator<Gen_t_00654780_p12cd> >::_M_reallocate_map(
	unsigned int, bool);
template void deque<Gen_t_0063c490_p12cd, allocator<Gen_t_0063c490_p12cd> >::_M_reallocate_map(
	unsigned int, bool);
template void deque<Gen_t_0063c4c0_p12cd, allocator<Gen_t_0063c4c0_p12cd> >::_M_reallocate_map(
	unsigned int, bool);
template void deque<Gen_t_0065fd10_p12cd, allocator<Gen_t_0065fd10_p12cd> >::_M_reallocate_map(
	unsigned int, bool);
template void deque<Gen_t_0065fd40_p12cd, allocator<Gen_t_0065fd40_p12cd> >::_M_reallocate_map(
	unsigned int, bool);
template void deque<Gen_t_00593270_p12cd, allocator<Gen_t_00593270_p12cd> >::_M_reallocate_map(
	unsigned int, bool);
}

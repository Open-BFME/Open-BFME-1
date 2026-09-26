// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME7: STLport _Deque_iterator_base<8-byte POD>::_M_increment at
// 0x008F9180 (42 B gap claimed by its shape: 16 elements per 128-byte node).
#define _STLP_NO_EXCEPTIONS 1
#include <deque>
struct Rva008F9180Elem { int m_0; int m_4; };
template class _STL::deque<Rva008F9180Elem>;
template class _STL::_Deque_iterator_base<Rva008F9180Elem>;

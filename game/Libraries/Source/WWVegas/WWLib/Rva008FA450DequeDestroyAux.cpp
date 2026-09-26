// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME7: STLport __destroy_aux over a deque<20-byte POD> iterator range at
// 0x008FA450 (43 B gap claimed by its shape: the element destructor is trivial
// so only the buffer-hopping iterator increment survives; 6 elements per node).
#define _STLP_NO_EXCEPTIONS 1
#include <deque>
struct Rva008FA450Elem { int m_v[5]; };
template class _STL::deque<Rva008FA450Elem>;

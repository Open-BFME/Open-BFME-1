// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME7: STLport vector<28-byte POD>::~vector at 0x002E4F50 (64 B gap
// claimed by its shape: element count via the 0x92492493 magic divide, buffers
// over 0x80 bytes go to operator delete, smaller ones to the node allocator).
#define _STLP_NO_EXCEPTIONS 1
#include <vector>
struct Rva002E4F50Elem { int m_v[7]; };
template class _STL::vector<Rva002E4F50Elem>;

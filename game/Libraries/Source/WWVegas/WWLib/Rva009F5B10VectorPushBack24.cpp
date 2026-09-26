// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME7: STLport vector<24-byte POD>::push_back at 0x009F5B10 (82 B gap
// claimed by its shape: in-place 6-dword copy when there is room else
// _M_insert_overflow).
#define _STLP_NO_EXCEPTIONS 1
#include <vector>
struct Rva009F5B10Elem { int m_v[6]; };
template class _STL::vector<Rva009F5B10Elem>;

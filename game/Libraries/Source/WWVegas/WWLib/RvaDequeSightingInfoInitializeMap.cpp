// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /D_STLP_USE_STATIC_LIB
// stlport
// Retail 009ED640, 203 bytes. Matched PartitionManager.cpp callers at
// 009ED980 and 009EDFB0 instantiate the deque of SightingInfo pointers.
// Emit the native vendored STLport template without an unwind frame,
// as in the retail allocation loop. Only the pointer type is needed here.
class SightingInfo;

#define _STLP_NO_EXCEPTIONS 1
#include <deque>

namespace _STL
{
template void _Deque_base<SightingInfo *,
    allocator<SightingInfo *> >::_M_initialize_map(unsigned int);
}

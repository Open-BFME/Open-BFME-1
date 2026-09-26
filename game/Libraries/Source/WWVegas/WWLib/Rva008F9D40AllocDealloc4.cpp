// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <memory>
template void _STL::allocator<int>::deallocate(int*, size_t) const;

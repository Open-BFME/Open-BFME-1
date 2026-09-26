// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <algorithm>

template void _STL::sort_heap<int *, _STL::less<int> >(int *, int *, _STL::less<int>);

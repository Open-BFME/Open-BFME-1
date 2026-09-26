// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME7: STLport __insertion_sort over int with a function-pointer
// comparator (112 B gap at 0x00483B90 claimed by its shape).
#define _STLP_NO_EXCEPTIONS 1
#include <algorithm>
typedef bool (__cdecl* Rva00483B90Cmp)(int, int);
template void _STL::__insertion_sort<int*, Rva00483B90Cmp>(int*, int*, Rva00483B90Cmp);

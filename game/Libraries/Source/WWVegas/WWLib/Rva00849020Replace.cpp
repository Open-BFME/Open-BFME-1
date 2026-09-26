// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME7: STLport replace<char*, char> at 0x00849020 (40 B gap claimed by
// its shape: compares each char against the old value by reference and stores
// the new value).
#define _STLP_NO_EXCEPTIONS 1
#include <algorithm>
template void _STL::replace<char*, char>(char*, char*, const char&, const char&);

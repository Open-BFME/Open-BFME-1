// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: STLport hash_set<int>'s hashtable clear loop.  Each bucket is
// walked and its eight-byte (next pointer + int value) nodes are released.
#define _STLP_NO_EXCEPTIONS 1
#include <hash_set>

typedef _STL::hash_set<int, _STL::hash<int>, _STL::equal_to<int> > BfmeIntHashSet;

template void BfmeIntHashSet::clear();

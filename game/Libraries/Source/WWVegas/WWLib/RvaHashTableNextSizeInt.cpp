// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Clean STLport hash_map<int, int> instantiation used to verify _M_next_size.
#include <hash_map>

typedef _STL::pair<const int, int> BfmeHashIntIntPair;
template class _STL::hash_map<int, int, _STL::hash<int>, _STL::equal_to<int>,
    _STL::allocator<BfmeHashIntIntPair> >;

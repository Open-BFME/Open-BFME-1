// cl: /Od /Ob2 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// RVA 0x0082EA80: counted four-byte vector construction. Retail calls the
// existing _Vector_base<int, allocator<int> > constructor through 0x00026085.
// Keep the local copy's ledger identity address-derived; the native header
// supplies the allocator temporary, POD fill loop, and exception cleanup.
#include <vector>

template _STL::vector<int, _STL::allocator<int> >::vector(unsigned int);

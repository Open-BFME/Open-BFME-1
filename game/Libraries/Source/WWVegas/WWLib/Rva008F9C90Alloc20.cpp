// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <memory>
struct Rva008F9C90Elem20 { unsigned char bytes[20]; };
template Rva008F9C90Elem20* _STL::allocator<Rva008F9C90Elem20>::allocate(size_t, const void*) const;
template void _STL::allocator<Rva008F9C90Elem20>::deallocate(Rva008F9C90Elem20*, size_t) const;

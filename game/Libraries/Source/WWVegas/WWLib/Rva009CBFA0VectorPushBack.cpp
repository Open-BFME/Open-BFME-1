// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// RVA 0x009CBFA0: STLport vector append of an opaque eight-byte element.
#define _STLP_NO_EXCEPTIONS 1
#include <vector>

struct Rva009CBFA0Elem
{
    int m_words[2];
};

template class _STL::vector<Rva009CBFA0Elem,
    _STL::allocator<Rva009CBFA0Elem> >;

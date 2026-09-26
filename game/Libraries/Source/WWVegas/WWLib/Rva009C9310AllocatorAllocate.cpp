// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// The 49-byte body at 0x009C9310 is STLport allocator<T>::allocate for an
// unknown 48-byte element. Its body proves the element width and allocator
// behavior, but it does not prove the element's semantic type.

#include <memory>

struct Rva009C9310Elem
{
	char m_body[0x30];
};

template class _STL::allocator<Rva009C9310Elem>;

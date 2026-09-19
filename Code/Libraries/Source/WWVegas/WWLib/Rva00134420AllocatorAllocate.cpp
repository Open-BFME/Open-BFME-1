// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// The 49-byte body at 0x00134420 is STLport allocator<T>::allocate for an
// unknown 24-byte element. Its body proves the element width and allocator
// behavior, but it does not prove the element's semantic type.

#include <memory>

struct Rva00134420Elem
{
	char m_body[0x18];
};

template class _STL::allocator<Rva00134420Elem>;

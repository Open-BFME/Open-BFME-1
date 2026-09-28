// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// The 49-byte body at 0x009CED00 is STLport allocator<T>::allocate for an
// unknown 36-byte element. Its body proves the element width and allocator
// behavior, but it does not prove the element's semantic type.

#include <memory>

struct Rva009CED00Element
{
	char m_data[0x24];
};

template class _STL::allocator<Rva009CED00Element>;

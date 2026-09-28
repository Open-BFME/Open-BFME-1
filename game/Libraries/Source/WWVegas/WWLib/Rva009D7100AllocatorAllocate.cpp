// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// The 49-byte bodies at 0x009D7100 and 0x009D7150 are STLport
// allocator<T>::allocate for unknown 20-byte and 12-byte elements. Their
// bodies prove the element widths and allocator behavior, but not the
// elements' semantic types.

#include <memory>

struct Rva009D7100Element
{
	char m_data[0x14];
};

template class _STL::allocator<Rva009D7100Element>;

struct Rva009D7150Element
{
	char m_data[0x0c];
};

template class _STL::allocator<Rva009D7150Element>;

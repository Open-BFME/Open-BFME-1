// cl: /O2 /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

// STLport vector assignment at retail 0x00136C10.  The body proves only a
// 0xEC-byte trivially copied element: its three copy paths are raw 0xEC-stride
// loops and its shrink path has no element-destruction call.  Keep the element
// address-derived because the surrounding ThingTemplate caller does not prove
// a semantic element name.

#include <vector>

struct Rva00136C10Element
{
	char m_body[0xEC];
};

template class _STL::vector<Rva00136C10Element>;

// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
#include <stl/_ctype.h>

// The two matched lookup wrappers push these native locale::id objects at
// retail VA012C7430 and VA012C7450. Each is one four-byte _M_index;
// the shipped indices are2 (narrow ctype) and21 (wide ctype).
_STL::locale::id _STL::ctype<char>::id = {2};
_STL::locale::id _STL::ctype<wchar_t>::id = {21};

_STL::locale::facet *Rva00844E40WideFacet(const _STL::locale &loc)
{
    return loc._M_use_facet(_STL::ctype<wchar_t>::id);
}

_STL::locale::facet *Rva00844E50NarrowFacet(const _STL::locale &loc)
{
    return loc._M_use_facet(_STL::ctype<char>::id);
}

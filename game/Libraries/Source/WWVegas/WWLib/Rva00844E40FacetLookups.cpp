// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
#include <locale>

_STL::locale::facet *Rva00844E40WideFacet(const _STL::locale &loc)
{
    return loc._M_use_facet(_STL::ctype<wchar_t>::id);
}

_STL::locale::facet *Rva00844E50NarrowFacet(const _STL::locale &loc)
{
    return loc._M_use_facet(_STL::ctype<char>::id);
}

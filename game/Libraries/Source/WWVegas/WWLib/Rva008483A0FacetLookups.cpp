// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
#include <locale>

// Four adjacent locale facet lookups. Retail carved them as one 75-byte
// span, but each 15-byte lookup ends in its own ret with an int3 pad (the
// precedent at 0x00844E40 landed the same shape as two 15-byte bodies).
// The four ids are consecutive facet-id statics; the final 11 bytes of
// the span belong to the next body and are out of scope here. Opaque
// names: the _M_use_facet call shape and id addresses are proved by the
// bytes, the facet semantic identities are not claimed.
_STL::locale::facet *Rva008483A0Facet0(const _STL::locale &loc)
{
    return loc._M_use_facet(*(const _STL::locale::id *)0x012C7440);
}

_STL::locale::facet *Rva008483B0Facet1(const _STL::locale &loc)
{
    return loc._M_use_facet(*(const _STL::locale::id *)0x012C743C);
}

_STL::locale::facet *Rva008483C0Facet2(const _STL::locale &loc)
{
    return loc._M_use_facet(*(const _STL::locale::id *)0x012C7458);
}

_STL::locale::facet *Rva008483D0Facet3(const _STL::locale &loc)
{
    return loc._M_use_facet(*(const _STL::locale::id *)0x012C7454);
}

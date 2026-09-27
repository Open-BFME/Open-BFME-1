// cl: /O2 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// Six cdecl range copies in the STLport codecvt/collate block
// (0x00843FB0..0x008440C2): three char -> wchar_t and three wchar_t -> char.
// Each compiles byte-exact from STLport 4.5.3 _STL::copy (random-access
// __copy loop). The retail image holds several distinct instantiations
// (copy / __copy_aux, const / non-const iterators) that all emit these
// bytes, and no caller or symbol says which one sits at which address, so
// each keeps its retail address in the name.

#include <algorithm>

#define WIDEN(NAME) \
wchar_t *NAME(const char *first, const char *last, wchar_t *result) \
{ \
	return _STL::copy(first, last, result); \
}

#define NARROW(NAME) \
char *NAME(const wchar_t *first, const wchar_t *last, char *result) \
{ \
	return _STL::copy(first, last, result); \
}

// ?Rva00843FB0Narrow@@YAPADPBG0PAD@Z
NARROW(Rva00843FB0Narrow)
// ?Rva00843FE0Widen@@YAPAGPBD0PAG@Z
WIDEN(Rva00843FE0Widen)
// ?Rva00844010Narrow@@YAPADPBG0PAD@Z
NARROW(Rva00844010Narrow)
// ?Rva00844040Widen@@YAPAGPBD0PAG@Z
WIDEN(Rva00844040Widen)
// ?Rva00844070Narrow@@YAPADPBG0PAD@Z
NARROW(Rva00844070Narrow)
// ?Rva008440A0Widen@@YAPAGPBD0PAG@Z
WIDEN(Rva008440A0Widen)

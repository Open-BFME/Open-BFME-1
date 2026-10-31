// cl: /MD /D_STLP_USE_STATIC_LIB
// stlport
// Two distinct retail wrappers call the already matched STLport __copy
// specialization at 0x00846E00. Their individual template identities are
// unproved, so each name retains its own address. Native return-by-value
// supplies the hidden result pointer and the empty iterator-tag temporary.
// See targets/game/reverse/identity_evidence/0x00846e80-0x00846eb0.md.
#include <string>
#include <iterator>
#include <algorithm>

typedef _STL::back_insert_iterator<_STL::string> Rva00846E80Iterator;
// Retail calls this body out of line; do not instantiate another provider.
namespace _STL {
template<> back_insert_iterator<string> __copy<const char *, back_insert_iterator<string>, int>(const char *, const char *, back_insert_iterator<string>, const random_access_iterator_tag &, int *);
}
Rva00846E80Iterator Rva00846E80(const char *first, const char *last, Rva00846E80Iterator output)
{
    return _STL::__copy(first, last, output, _STL::random_access_iterator_tag(), (int *)0);
}
Rva00846E80Iterator Rva00846EB0(const char *first, const char *last, Rva00846E80Iterator output)
{
    return _STL::copy(first, last, output);
}

// 0x00846B40 calls the address-owned duplicate at 0x008460D0, not the
// canonical __copy body at 0x00835590. The existing duplicate ledger row
// names its native object symbol; use that verified ABI with one address pin.
// See identity_evidence/0x00846b40.md.
typedef _STL::ostreambuf_iterator<char> Rva00846B40Iterator;
Rva00846B40Iterator Rva008460D0(const char *, const char *, Rva00846B40Iterator, const _STL::random_access_iterator_tag &, int *);
Rva00846B40Iterator Rva00846B40(const char *first, const char *last, Rva00846B40Iterator output)
{
    return Rva008460D0(first, last, output, _STL::random_access_iterator_tag(), (int *)0);
}

// 0x00846AA0 (45 B) is an unreferenced second retail copy of the same
// wrapper, byte-identical to 0x00846B40 and calling the same 0x008460D0
// duplicate; retail has no identical-COMDAT folding, so it keeps its own
// address-derived name.
Rva00846B40Iterator Rva00846AA0(const char *first, const char *last, Rva00846B40Iterator output)
{
    return Rva008460D0(first, last, output, _STL::random_access_iterator_tag(), (int *)0);
}

// Retail 0x008460D0 (114 B): the duplicate random-access __copy into an
// ostreambuf_iterator that 0x00846B40 calls. Its row was a gen-alias to the
// NumFacetsInstantiations COMDAT copy; the body follows STLport's
// random-access __copy loop under the address-derived name above.
// ?Rva008460D0@@YA?AV?$ostreambuf_iterator@DV?$char_traits@D@_STL@@@_STL@@PBD0V12@ABUrandom_access_iterator_tag@2@PAH@Z
__declspec(noinline) Rva00846B40Iterator Rva008460D0(const char *first, const char *last, Rva00846B40Iterator result, const _STL::random_access_iterator_tag &, int *)
{
    for (int n = last - first; n > 0; --n) {
        *result = *first;
        ++first;
        ++result;
    }
    return result;
}

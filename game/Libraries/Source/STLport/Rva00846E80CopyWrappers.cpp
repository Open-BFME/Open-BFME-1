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

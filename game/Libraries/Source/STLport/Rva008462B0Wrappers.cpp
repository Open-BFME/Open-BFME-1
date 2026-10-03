// cl: /MD /D_STLP_USE_STATIC_LIB
// stlport
// Three independent retail wrappers formerly merged into one dump.
// Their exact template identities are not established; keep address names.
// Native STLport types preserve iterator references and hidden return ABI.
// Evidence: targets/game/reverse/identity_evidence/0x008462b0-wrappers.md.
#include <locale>
#include <algorithm>

typedef _STL::istreambuf_iterator<char> Rva008462B0Input;
typedef _STL::ostreambuf_iterator<char> Rva008462F0Output;
namespace _STL {
template<> string *__match<Rva008462B0Input, string *, long>(Rva008462B0Input &, Rva008462B0Input &, string *, string *, long *);
template<> string *__match<Rva008462B0Input, string *, int>(Rva008462B0Input &, Rva008462B0Input &, string *, string *, int *);
}
_STL::string *Rva008462B0(Rva008462B0Input &first, Rva008462B0Input &last, _STL::string *names, _STL::string *end)
{
    return _STL::__match(first, last, names, end, (long *)0);
}
_STL::string *Rva008462D0(Rva008462B0Input &first, Rva008462B0Input &last, _STL::string *names, _STL::string *end)
{
    return _STL::__match(first, last, names, end, (int *)0);
}
Rva008462F0Output Rva008460D0(const char *, const char *, Rva008462F0Output, const _STL::random_access_iterator_tag &, int *);
Rva008462F0Output Rva008462F0(const char *first, const char *last, Rva008462F0Output output)
{
    return Rva008460D0(first, last, output, _STL::random_access_iterator_tag(), (int *)0);
}

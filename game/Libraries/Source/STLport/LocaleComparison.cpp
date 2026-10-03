// cl: /O2 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
// Native STLport 4.5.3 declarations; retail locale name/equality operations.
// Evidence: targets/game/reverse/identity_evidence/20261003-locale-comparison.md
#include <string>

// Retail keeps the narrow copy constructor and destructor out of line.
// The A5120 deallocation body cannot throw. Retaining that contract matters
// to both the conditional temporary flags and the parent's unwind states.
namespace _STL {
template <>
basic_string<char, char_traits<char>, allocator<char> >::~basic_string() throw();
template <>
basic_string<char, char_traits<char>, allocator<char> >::basic_string(const basic_string &);
}

#include <locale>
#pragma intrinsic(memcmp)

namespace _STL {

// The canonical public header leaves the implementation opaque. Getter
// 836580 witnesses its narrow string at +C; no other field is modeled.
class _Locale_impl
{
public:
    unsigned char m_bfmeHead[12];
    string name;
};

__declspec(noinline) string locale::name() const
{
    return _M_impl->name;
}

// C6D8B0 constructs this string from "*" and registers C70CC0 to destroy it.
extern string Rva0130BCB4;

template <>
__declspec(noinline) bool operator!=(const string &a, const string &b)
{
    return !(a == b);
}

bool locale::operator==(const locale &that) const
{
    return _M_impl == that._M_impl ||
        (name() == that.name() && name() != Rva0130BCB4);
}

} // namespace _STL

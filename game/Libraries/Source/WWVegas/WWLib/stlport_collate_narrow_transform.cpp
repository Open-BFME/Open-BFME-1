// stlport
// cl: /O2 /EHsc /MD /D_STLP_USE_STATIC_LIB
// STLport 4.5.3 collate<char>::do_transform, retail RVA 0x00844400 (87B).
// RTTI COL VA 0x011DE028 names collate<char>; its vtable VA 0x0112EAD4
// slot 2 holds this body, between the independently matched compare/hash.
#include <locale>

namespace _STL
{
// Preserve the native helper body for side-effect analysis, but keep the
// retail call through ILT 0x0002A531 -> 0x002D8760. The complete helper is
// independently byte-exact at 97B. A declaration alone prevents VC7.1 from
// reusing the hidden return-pointer home for the empty iterator tag.
template <> template <> __declspec(noinline)
void basic_string<char, char_traits<char>, allocator<char> >::_M_range_initialize<const char *>(
    const char *first, const char *last, const forward_iterator_tag &)
{
    difference_type count = distance(first, last);
    this->_M_allocate_block(count + 1);
    this->_M_finish = uninitialized_copy(first, last, this->_M_start);
    _M_terminate_string();
}

// Retail tracks the partially constructed string base in its unwind map:
// handler C55AE8 -> FuncInfo E44CC4 -> state 0 cleanup C55AE0 -> A41C0.
template <> __declspec(noinline) _String_base<char, allocator<char> >::~_String_base()
{
    _M_deallocate_block();
}

collate<char>::string_type
collate<char>::do_transform(const char *low, const char *high) const
{
    return string_type(low, high);
}
}

// cl: /O2 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport

#include <streambuf>

template <>
_STL::locale
_STL::basic_streambuf<wchar_t, _STL::char_traits<wchar_t> >::pubimbue(const _STL::locale &);

template class _STL::basic_streambuf<wchar_t, _STL::char_traits<wchar_t> >;

// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport

// The retail basic_ios<char>::init uses the generic ctype<char>::widen
// virtual, rather than STLport's optional char widening specialization.

#define _STLP_NO_METHOD_SPECIALIZATION
#include <istream>
#include <ostream>

template class _STL::basic_istream<char, _STL::char_traits<char> >;
template class _STL::basic_istream<wchar_t, _STL::char_traits<wchar_t> >;
template class _STL::basic_ostream<char, _STL::char_traits<char> >;
template class _STL::basic_ostream<wchar_t, _STL::char_traits<wchar_t> >;

// cl: /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 basic_istream/basic_ostream instantiations used by retail.
// This proper source-tree owner replaces the retired generated inventory.

#define _STLP_NO_EXCEPTIONS 1
#include <istream>
#include <ostream>

template class _STL::basic_istream<char, _STL::char_traits<char> >;
template class _STL::basic_istream<wchar_t, _STL::char_traits<wchar_t> >;
template class _STL::basic_ostream<char, _STL::char_traits<char> >;
template class _STL::basic_ostream<wchar_t, _STL::char_traits<wchar_t> >;

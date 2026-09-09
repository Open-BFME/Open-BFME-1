// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 time_get/time_put facet instantiations used by the retail
// executable.  These definitions replace claims formerly owned by the
// retired generated-source inventory with readable C++ in the source tree.

#include <locale>

template class _STL::time_put<char, _STL::ostreambuf_iterator<char, _STL::char_traits<char> > >;
template class _STL::time_get<char, _STL::istreambuf_iterator<char, _STL::char_traits<char> > >;
template class _STL::time_put<wchar_t, _STL::ostreambuf_iterator<wchar_t, _STL::char_traits<wchar_t> > >;
template class _STL::time_get<wchar_t, _STL::istreambuf_iterator<wchar_t, _STL::char_traits<wchar_t> > >;

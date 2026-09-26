// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// Per-translation-unit STLport instantiation used by FX particle INI writers.

#include <ostream>

template _STL::basic_ostream<char, _STL::char_traits<char> > &
_STL::basic_ostream<char, _STL::char_traits<char> >::put(char);

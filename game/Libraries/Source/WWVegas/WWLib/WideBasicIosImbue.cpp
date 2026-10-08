// cl: /MD /D_STLP_USE_STATIC_LIB
// stlport

// STLport 4.6 emits the retail wide basic_ios::imbue body when this TU
// exposes the node allocator implementation before instantiating the method.
// The node allocator lock is STLport's own _STLP_mutex_base: retail calls
// _STLP_mutex_spin<0>::_M_do_lock(&_S_lock) and releases it inline.

#define _STLP_NO_EXCEPTIONS 1
#define _STLP_MUTEX_INITIALIZER
#define _STLP_EXPOSE_GLOBALS_IMPLEMENTATION 1

#include <istream>

template <>
_STL::locale
_STL::basic_streambuf<wchar_t, _STL::char_traits<wchar_t> >::pubimbue(const _STL::locale &);

template _STL::locale _STL::basic_ios<wchar_t, _STL::char_traits<wchar_t> >::imbue(
	const _STL::locale&);

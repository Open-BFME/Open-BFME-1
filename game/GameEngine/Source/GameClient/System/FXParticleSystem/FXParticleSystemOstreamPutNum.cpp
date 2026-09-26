// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// STLport 4.5.3 formatted numeric output helper used by the FX stream path.

#include <ostream>

template _STL::basic_ostream<char, _STL::char_traits<char> >&
_STL::_M_put_num<char, _STL::char_traits<char>, long>(
	_STL::basic_ostream<char, _STL::char_traits<char> >&, long);

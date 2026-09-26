// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// Near twin (diff 1 byte) of _M_put_num<char, char_traits<char>, long> at 0x005F0120
// (FXParticleSystemOstreamPutNum.cpp): identical body except the num_put facet vtable
// slot called is one slot earlier (0x18 vs 0x1c) -- the unsigned long put() overload.

#include <ostream>

template _STL::basic_ostream<char, _STL::char_traits<char> >&
_STL::_M_put_num<char, _STL::char_traits<char>, unsigned long>(
	_STL::basic_ostream<char, _STL::char_traits<char> >&, unsigned long);

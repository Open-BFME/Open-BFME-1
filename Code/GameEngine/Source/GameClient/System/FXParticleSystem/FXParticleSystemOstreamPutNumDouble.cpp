// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// Fuzzy twin (ratio 0.957) of _M_put_num<char, char_traits<char>, long> at
// 0x005F0120 (FXParticleSystemOstreamPutNum.cpp): identical shape, but the
// value is a double (fld/fstp qword instead of an integer push) formatted
// through the num_put facet's double put() overload (vtable slot 0x14).

#include <ostream>

template _STL::basic_ostream<char, _STL::char_traits<char> >&
_STL::_M_put_num<char, _STL::char_traits<char>, double>(
	_STL::basic_ostream<char, _STL::char_traits<char> >&, double);

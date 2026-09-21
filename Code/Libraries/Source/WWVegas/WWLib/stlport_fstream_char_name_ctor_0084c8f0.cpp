// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
// STLport 4.5 basic_fstream<char>(const char*, openmode, long) pathname
// constructor, retail RVA 0x0084C8F0. Forwards its own `protection`
// argument straight through to _M_open(name, mode, protection), matching
// the wide-character twin at 0x0084D0A0 (StreamConstructorInstantiations.cpp).
// A neighbouring address (0x0084C6F0) carries an ICF-similar body that
// hardcodes 0x80 for the protection argument instead of forwarding it and
// is NOT this symbol; that address stays address-derived elsewhere.
#include <fstream>

template <>
_STL::basic_fstream<char, _STL::char_traits<char> >::basic_fstream(
	const char *__s, _STL::ios_base::openmode __m, long __protection) :
	_STL::basic_ios<char, _STL::char_traits<char> >(),
	_STL::basic_iostream<char, _STL::char_traits<char> >(0),
	_M_buf()
{
	this->init(&_M_buf);
	if (!_M_buf.open(__s, __m, __protection))
		this->setstate(_STL::ios_base::failbit);
}

// force emission of the specialization above
template _STL::basic_fstream<char, _STL::char_traits<char> >::basic_fstream(
	const char*, _STL::ios_base::openmode, long);

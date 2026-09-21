// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
// STLport 4.5 basic_fstream<T>(const char*, openmode) pathname constructors,
// retail RVAs 0x0084C6F0 (char, 248B) and 0x0084CEA0 (wchar_t, 249B).
//
// These are the TWO-argument overloads, distinct from the three-argument
// pathname constructors already matched at 0x0084C8F0 (char,
// stlport_fstream_char_name_ctor_0084c8f0.cpp) and 0x0084D0A0 (wchar_t,
// StreamConstructorInstantiations.cpp), which forward a caller-supplied
// protection. Retail's `ret 0xc` proves two declared arguments plus the
// hidden virtual-base-init flag basic_ios picks up through the
// basic_istream/basic_ostream diamond -- the three-argument bodies clean up
// 0x10. That is also why these push a literal 0x80: retail's
// basic_filebuf::open carries the default protection, so the two-argument
// constructor reaches _M_open(name, mode, 0x80) with the default folded in.
// The vendored header instead offers a two-argument open() overload that
// stops one argument short, so each constructor needs its own explicit
// member specialization rather than a plain explicit instantiation.
#include <fstream>

template <>
_STL::basic_fstream<char, _STL::char_traits<char> >::basic_fstream(
	const char *__s, _STL::ios_base::openmode __m) :
	_STL::basic_ios<char, _STL::char_traits<char> >(),
	_STL::basic_iostream<char, _STL::char_traits<char> >(0),
	_M_buf()
{
	this->init(&_M_buf);
	if (!_M_buf.open(__s, __m, 0x80))
		this->setstate(_STL::ios_base::failbit);
}

template <>
_STL::basic_fstream<wchar_t, _STL::char_traits<wchar_t> >::basic_fstream(
	const char *__s, _STL::ios_base::openmode __m) :
	_STL::basic_ios<wchar_t, _STL::char_traits<wchar_t> >(),
	_STL::basic_iostream<wchar_t, _STL::char_traits<wchar_t> >(0),
	_M_buf()
{
	this->init(&_M_buf);
	if (!_M_buf.open(__s, __m, 0x80))
		this->setstate(_STL::ios_base::failbit);
}

// force emission of the specializations above
template _STL::basic_fstream<char, _STL::char_traits<char> >::basic_fstream(
	const char*, _STL::ios_base::openmode);
template _STL::basic_fstream<wchar_t, _STL::char_traits<wchar_t> >::basic_fstream(
	const char*, _STL::ios_base::openmode);

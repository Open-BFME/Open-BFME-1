// ??0?$basic_fstream@DV?$char_traits@D@_STL@@@_STL@@QAE@PBDHJ@Z
// partial score=0.94 date=2026-09-21
// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
// STLport 4.5 basic_fstream<char>(const char*, openmode, long) pathname
// constructor, retail RVA 0x0084C6F0.  Its wide-character twin
// (0x0084D0A0, StreamConstructorInstantiations.cpp) forwards its own
// `protection` argument straight through to _M_open(name, mode, protection).
// This narrow instantiation does not: it always passes the literal 0x80
// default (filebuf_type::_S_default_pmode) to _M_open regardless of what
// the caller passed, so it needs its own explicit specialization instead of
// the generic vendored template body.
#include <fstream>

template <>
_STL::basic_fstream<char, _STL::char_traits<char> >::basic_fstream(
	const char *__s, _STL::ios_base::openmode __m, long /*__protection*/) :
	_STL::basic_ios<char, _STL::char_traits<char> >(),
	_STL::basic_iostream<char, _STL::char_traits<char> >(0),
	_M_buf()
{
	this->init(&_M_buf);
	if (!_M_buf.open(__s, __m, 0x80))
		this->setstate(_STL::ios_base::failbit);
}

// force emission of the specialization above
template _STL::basic_fstream<char, _STL::char_traits<char> >::basic_fstream(
	const char*, _STL::ios_base::openmode, long);

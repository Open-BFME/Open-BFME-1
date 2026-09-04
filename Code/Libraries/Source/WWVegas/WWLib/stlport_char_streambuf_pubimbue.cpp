// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// Open-BFME5: STLport 4.5.3 char basic_streambuf::pubimbue at 0x0083FC10.
// The char specialization is declared as a concrete class in _streambuf.h,
// so its member is defined without the primary-template specialization tag.

#include <streambuf>

_STL::locale
_STL::basic_streambuf<char, _STL::char_traits<char> >::pubimbue(const _STL::locale &loc)
{
	this->imbue(loc);
	_STL::locale previous = _M_locale;
	_M_locale = loc;
	return previous;
}

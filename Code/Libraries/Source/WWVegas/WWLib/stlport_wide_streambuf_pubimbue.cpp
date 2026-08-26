// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 wide basic_streambuf instantiation. The upstream class-template
// body is specialized here because VC7.1 rejects explicit instantiation of the
// library's wchar_t specialization while emitting the same member definition.

#include <streambuf>

template <>
_STL::locale
_STL::basic_streambuf<wchar_t, _STL::char_traits<wchar_t> >::pubimbue(const _STL::locale &loc)
{
	this->imbue(loc);
	_STL::locale previous = _M_locale;
	_M_locale = loc;
	return previous;
}

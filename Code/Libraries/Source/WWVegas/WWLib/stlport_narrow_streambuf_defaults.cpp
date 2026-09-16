// cl: /O2 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// Open-BFME5: the seven do-nothing virtuals of the char basic_streambuf.
// STLport 4.5.3 declares the char form as a concrete specialization in
// _streambuf.h, so these members are written out by hand instead of coming
// from an explicit instantiation the way the wide form does.

#include <streambuf>

int _STL::basic_streambuf<char, _STL::char_traits<char> >::sync()
{
	return 0;
}

_STL::streamsize _STL::basic_streambuf<char, _STL::char_traits<char> >::showmanyc()
{
	return 0;
}

_STL::basic_streambuf<char, _STL::char_traits<char> >::int_type
_STL::basic_streambuf<char, _STL::char_traits<char> >::underflow()
{
	return _STL::char_traits<char>::eof();
}

void _STL::basic_streambuf<char, _STL::char_traits<char> >::imbue(const _STL::locale &)
{
}

_STL::basic_streambuf<char, _STL::char_traits<char> > *
_STL::basic_streambuf<char, _STL::char_traits<char> >::setbuf(char *, _STL::streamsize)
{
	return this;
}

_STL::basic_streambuf<char, _STL::char_traits<char> >::int_type
_STL::basic_streambuf<char, _STL::char_traits<char> >::pbackfail(int_type)
{
	return _STL::char_traits<char>::eof();
}

_STL::basic_streambuf<char, _STL::char_traits<char> >::int_type
_STL::basic_streambuf<char, _STL::char_traits<char> >::overflow(int_type)
{
	return _STL::char_traits<char>::eof();
}

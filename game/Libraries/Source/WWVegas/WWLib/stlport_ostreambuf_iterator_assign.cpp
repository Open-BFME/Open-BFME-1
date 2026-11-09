// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 ostreambuf_iterator<char>::operator=(char), retail 0x00835550,
// 52 bytes.  The streambuf's sputc stays the external member the retail body
// reaches through ILT 0x00022D4F (retail 0x005BD380), so the iterator body is
// the whole conversion.
//
// Provenance: [BFME 2 donor] Open-BFME-2 2bac16a6
// Code/Libraries/Source/WWVegas/WWLib/stlport_ostreambuf_iterator_assign.cpp
// BFME1 wide assignment is 0x00835E90 (53 bytes) and calls the
// native wide sputc at 0x00835ED0.

typedef unsigned short wchar_t;

namespace _STL
{

template <class T>
class char_traits {};

template <>
class char_traits<char>
{
public:
	typedef int int_type;
};

template <>
class char_traits<wchar_t>
{
public:
	typedef wchar_t int_type;
};

template <class CharT, class Traits>
class basic_streambuf
{
public:
	typename Traits::int_type sputc(CharT value);
};

template <class CharT, class Traits>
class ostreambuf_iterator
{
public:
	ostreambuf_iterator &operator=(CharT value);

private:
	basic_streambuf<CharT, Traits> *_M_buf;
	bool _M_ok;
};

template <class CharT, class Traits>
ostreambuf_iterator<CharT, Traits> &
ostreambuf_iterator<CharT, Traits>::operator=(CharT value)
{
	_M_ok = _M_ok &&
			_M_buf->sputc(value) != static_cast<typename Traits::int_type>(-1);
	return *this;
}

template class ostreambuf_iterator<char, char_traits<char> >;
template class ostreambuf_iterator<wchar_t, char_traits<wchar_t> >;

}

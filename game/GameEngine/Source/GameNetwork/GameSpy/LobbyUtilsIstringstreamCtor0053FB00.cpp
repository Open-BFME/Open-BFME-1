// stlport
// Retail LobbyUtils constructors use the STLport stream virtual-base layout.
// Keep library implementations out of this constructor-only TU.
#define _STLP_LINK_TIME_INSTANTIATION 1
#include <sstream>

namespace _STL {
// The upstream basic_ios default constructor is visible here so the narrow
// stream constructors retain their witnessed inlined initialization.
template <>
inline basic_ios<char, char_traits<char> >::basic_ios()
	: ios_base(), _M_fill(0), _M_streambuf(0), _M_tied_ostream(0)
{}

template <>
basic_istringstream<char, char_traits<char>, allocator<char> >::basic_istringstream(
	const basic_string<char, char_traits<char>, allocator<char> > &str,
	ios_base::openmode mode)
	: basic_istream<char, char_traits<char> >(0), _M_buf(str, mode | ios_base::in)
{
	this->init(&_M_buf);
}

template <>
inline basic_istringstream<char, char_traits<char>, allocator<char> >::~basic_istringstream()
{}

template basic_istream<char, char_traits<char> >::basic_istream(
	basic_streambuf<char, char_traits<char> > *);
}

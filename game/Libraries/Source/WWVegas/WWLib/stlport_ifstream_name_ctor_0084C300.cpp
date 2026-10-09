// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Retail library name constructor 0084C300 keeps its address-qualified class.
// Use the actual STLport bases and filebuf layout; instantiate only this body.
#define _STLP_LINK_TIME_INSTANTIATION 1
// The internal declaration header avoids the wrapper's per-TU locale initializer.
#include <stl/_fstream.h>

namespace _STL {
template <>
inline basic_ios<char, char_traits<char> >::basic_ios()
	: ios_base(), _M_fill(0), _M_streambuf(0), _M_tied_ostream(0)
{}

template <class CharT, class Traits>
class basic_ifstream_lib0084C300 : public basic_istream<CharT, Traits> {
public:
	basic_ifstream_lib0084C300(const char *name, ios_base::openmode mode)
		: basic_ios<CharT, Traits>(), basic_istream<CharT, Traits>(0), buf_()
	{
		this->init(&buf_);
		// The witnessed library open call takes explicit protection 0x80.
		if (!buf_.open(name, mode | ios_base::in, 0x80))
			this->setstate(ios_base::failbit);
	}
private:
	basic_filebuf<CharT, Traits> buf_;
};

template basic_ifstream_lib0084C300<char, char_traits<char> >::basic_ifstream_lib0084C300(
	const char *, ios_base::openmode);
}

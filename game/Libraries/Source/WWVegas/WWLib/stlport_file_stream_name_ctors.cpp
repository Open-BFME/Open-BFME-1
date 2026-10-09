// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Retail STLport narrow file-stream name and descriptor constructors.
#define _STLP_LINK_TIME_INSTANTIATION 1
#include <stl/_fstream.h>

namespace _STL {
template <> inline basic_ios<char, char_traits<char> >::basic_ios()
    : ios_base(), _M_fill(0), _M_streambuf(0), _M_tied_ostream(0) {}

template <> inline basic_ostream<char, char_traits<char> >::basic_ostream(
    basic_streambuf<char, char_traits<char> > *buf)
    : basic_ios<char, char_traits<char> >()
{
    this->init(buf);
}

template <> inline basic_ostream<char, char_traits<char> >::~basic_ostream() {}
template <> inline basic_ofstream<char, char_traits<char> >::~basic_ofstream() {}

// The retail two-argument name overload uses Win32 protection 0x80.
template <> basic_ofstream<char, char_traits<char> >::basic_ofstream(
    const char *name, ios_base::openmode mode)
    : basic_ostream<char, char_traits<char> >(0), _M_buf()
{
    this->init(&_M_buf);
    if (!_M_buf.open(name, mode | ios_base::out, 0x80))
        this->setstate(ios_base::failbit);
}

template basic_ifstream<char, char_traits<char> >::basic_ifstream(int, ios_base::openmode);
template basic_ifstream<char, char_traits<char> >::basic_ifstream(const char *, ios_base::openmode, long);
template basic_ofstream<char, char_traits<char> >::basic_ofstream(const char *, ios_base::openmode);
template basic_ofstream<char, char_traits<char> >::basic_ofstream(const char *, ios_base::openmode, long);
}

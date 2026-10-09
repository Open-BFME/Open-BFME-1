// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Retail STLport narrow ifstream default constructor 0084C240.
#define _STLP_LINK_TIME_INSTANTIATION 1
#include <stl/_fstream.h>

namespace _STL {
template <> inline basic_ios<char, char_traits<char> >::basic_ios()
    : ios_base(), _M_fill(0), _M_streambuf(0), _M_tied_ostream(0) {}

template basic_ifstream<char, char_traits<char> >::basic_ifstream();
}

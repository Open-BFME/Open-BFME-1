// cl: /O2 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 narrow istreambuf_iterator constructor from a basic_istream,
// retail 0x00845150: reads rdbuf() through the virtual basic_ios base and
// runs the inline _M_init.

#include <istream>

template _STL::istreambuf_iterator<char, _STL::char_traits<char> >::istreambuf_iterator(_STL::basic_istream<char, _STL::char_traits<char> > &);

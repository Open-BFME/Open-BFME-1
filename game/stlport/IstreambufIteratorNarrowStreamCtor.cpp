// cl: /O2 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 narrow istreambuf_iterator constructor from a basic_istream,
// retail 0x00845150: reads rdbuf() through the virtual basic_ios base and
// runs the inline _M_init.

#include <istream>

template _STL::istreambuf_iterator<char, _STL::char_traits<char> >::istreambuf_iterator(_STL::basic_istream<char, _STL::char_traits<char> > &);

// Wide twin, retail 0x008450E0: _M_c is a wchar_t, so _M_eof/_M_have_c sit
// at +6/+7 instead of the narrow +5/+6.
template _STL::istreambuf_iterator<wchar_t, _STL::char_traits<wchar_t> >::istreambuf_iterator(_STL::basic_istream<wchar_t, _STL::char_traits<wchar_t> > &);

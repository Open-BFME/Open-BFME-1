// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
// STLport 4.5 basic_fstream(int fd, ios_base::openmode) constructors
// instantiated by the retail binary (twin: Code/stlport/StreamConstructorInstantiations.cpp
// basic_fstream(const char*, openmode, long) at 0x0084D0A0/0x0084C630 -- these
// targets call _M_open(int,int) instead of _M_open(const char*,int,long), the
// file-descriptor overload in vendor/stlport/stl/_fstream.h.
#include <fstream>

template _STL::basic_fstream<wchar_t, _STL::char_traits<wchar_t> >::basic_fstream(
    int, _STL::ios_base::openmode);

template _STL::basic_fstream<char, _STL::char_traits<char> >::basic_fstream(
    int, _STL::ios_base::openmode);

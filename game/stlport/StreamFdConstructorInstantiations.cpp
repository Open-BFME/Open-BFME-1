// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
// STLport 4.5 basic_fstream(int fd, ios_base::openmode) constructors
// instantiated by the retail binary (twin: game/stlport/StreamConstructorInstantiations.cpp
// basic_fstream(const char*, openmode, long) at 0x0084D0A0/0x0084C630 -- these
// targets call _M_open(int,int) instead of _M_open(const char*,int,long), the
// file-descriptor overload in inputs/vendor/stlport/stl/_fstream.h.
#include <fstream>

// basic_filebuf::_M_allocate_buffers(_CharT *, streamsize) is retail 0x008416C0
// (char) and 0x008420B0 (wchar_t), a body without an EH frame
// (stlport_narrow_filebuf_allocate_buffers.cpp, stlport_filebuf_allocate_buffers.cpp).
// Instantiated under /EHsc here it came out as a different COMDAT copy that the
// link kept ahead of retail's, so this TU only declares it.
template <>
bool _STL::basic_filebuf<char, _STL::char_traits<char> >::_M_allocate_buffers(
	char *, _STL::streamsize);
template <>
bool _STL::basic_filebuf<wchar_t, _STL::char_traits<wchar_t> >::_M_allocate_buffers(
	wchar_t *, _STL::streamsize);

template _STL::basic_fstream<wchar_t, _STL::char_traits<wchar_t> >::basic_fstream(
    int, _STL::ios_base::openmode);

template _STL::basic_fstream<char, _STL::char_traits<char> >::basic_fstream(
    int, _STL::ios_base::openmode);

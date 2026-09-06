// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
// STLport 4.5 stream constructor instantiated by the retail binary.
// Fuzzy-twin lane: sibling of Code/stlport/StreamConstructorInstantiations.cpp
// (twin 0x0084D0A0 basic_fstream<wchar_t> pathname ctor) and of the already
// landed narrow basic_ifstream<char> pathname ctor at 0x0084C520
// (Code/Libraries/Source/WWVegas/WWLib/stlport_file_stream_name_ctors.cpp).
// Identity proven by vtable_lookup.py: 0x0112FC40 is pinned as the
// basic_ifstream<unsigned short> vftable, and 0x0112F2FC is the pinned
// basic_istream<unsigned short> g_bfme918VftC stand-in -- both installed by
// this ctor's body, not by basic_iostream's (which the fstream twin calls).
#include <fstream>

template class _STL::basic_ifstream<wchar_t, _STL::char_traits<wchar_t> >;

template _STL::basic_ifstream<wchar_t, _STL::char_traits<wchar_t> >::basic_ifstream(
    const char*, _STL::ios_base::openmode, long);

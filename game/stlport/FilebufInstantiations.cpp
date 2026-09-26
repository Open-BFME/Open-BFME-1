// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 basic_filebuf template instantiations used by the retail
// executable.  These definitions move exact bodies out of the retired
// generated-source inventory and into readable source-tree C++.

#include <fstream>

// BFME's two-argument filebuf opens forward to the three-argument Win32
// implementation with the retail default protection constant (0x80).
template <>
_STL::basic_filebuf<char, _STL::char_traits<char> > *
_STL::basic_filebuf<char, _STL::char_traits<char> >::open(
    const char *name, _STL::ios_base::openmode mode)
{
    return _M_base._M_open(name, mode, 0x80) ? this : 0;
}

template <>
_STL::basic_filebuf<wchar_t, _STL::char_traits<wchar_t> > *
_STL::basic_filebuf<wchar_t, _STL::char_traits<wchar_t> >::open(
    const char *name, _STL::ios_base::openmode mode)
{
    return _M_base._M_open(name, mode, 0x80) ? this : 0;
}

template class _STL::basic_filebuf<char, _STL::char_traits<char> >;
template class _STL::basic_filebuf<wchar_t, _STL::char_traits<wchar_t> >;

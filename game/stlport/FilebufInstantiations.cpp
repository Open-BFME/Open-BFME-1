// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 basic_filebuf template instantiations used by the retail
// executable.  These definitions move exact bodies out of the retired
// generated-source inventory and into readable source-tree C++.

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

// NarrowFilebufInputError.cpp owns the independently byte-verified error
// transition at 0x0084A5D0. Avoid selecting the different vendor copy here.
template <>
int _STL::basic_filebuf<char, _STL::char_traits<char> >::_M_input_error();

// The 96-byte wide input transition at 0x00843680 also has a verified
// provider; keep its copy rather than the generic allocation-call variant.
template <>
bool _STL::basic_filebuf<wchar_t, _STL::char_traits<wchar_t> >::_M_switch_to_input_mode();

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

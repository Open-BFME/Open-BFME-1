// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 numeric-facet template instantiations used by the retail
// executable.  Keeping these in the normal source tree lets matched bodies
// be owned by readable C++ instead of the retired generated-source inventory.

#include <locale>

namespace _STL {
typedef ostreambuf_iterator<char, char_traits<char> > BfmeNarrowPointerIterator;

// This overload is owned by NumPutPointerNarrow.cpp.  Declare its explicit
// specialization before the class instantiation so this TU does not emit a
// second definition.
template <>
BfmeNarrowPointerIterator
num_put<char, BfmeNarrowPointerIterator>::do_put(
	BfmeNarrowPointerIterator, ios_base &, char, const void *) const;
}

template class _STL::num_put<char, _STL::ostreambuf_iterator<char, _STL::char_traits<char> > >;
template class _STL::num_get<char, _STL::istreambuf_iterator<char, _STL::char_traits<char> > >;
template class _STL::num_put<wchar_t, _STL::ostreambuf_iterator<wchar_t, _STL::char_traits<wchar_t> > >;
template class _STL::num_get<wchar_t, _STL::istreambuf_iterator<wchar_t, _STL::char_traits<wchar_t> > >;

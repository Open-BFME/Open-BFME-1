// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 basic_filebuf template instantiations used by the retail
// executable.  These definitions move exact bodies out of the retired
// generated-source inventory and into readable source-tree C++.

#include <fstream>

template class _STL::basic_filebuf<char, _STL::char_traits<char> >;
template class _STL::basic_filebuf<wchar_t, _STL::char_traits<wchar_t> >;

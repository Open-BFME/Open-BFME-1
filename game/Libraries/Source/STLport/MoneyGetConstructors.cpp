// cl: /O2 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
// STLport 4.5.3. Retail constructors 00832200 and 00832280 install
// vtables 0112E95C and 0112E9D8, whose RTTI names these specializations.
// Both starts follow INT3 padding; RET 4 ends each 30-byte body.
#include <locale>

template class _STL::money_get<char, _STL::istreambuf_iterator<char, _STL::char_traits<char> > >;
template class _STL::money_get<wchar_t, _STL::istreambuf_iterator<wchar_t, _STL::char_traits<wchar_t> > >;

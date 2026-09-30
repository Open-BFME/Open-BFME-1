// cl: /MD /EHsc /D_STLP_USE_STATIC_LIB /vd0
// stlport
// STLport stream vbase destructors install their own vtable and destroy basic_ios.
// Retail 0x00841220 installs basic_ostream<char>'s vtable at VA 0x0112F304.
// The positive four-byte adjustment identifies the complete-object ??_D entry.
// Retail 0x00841240 installs basic_istream<wchar_t>'s vtable at VA 0x0112F2FC
// and adjusts eight bytes to the wide basic_ios virtual base.
// Retail 0x00841260 is the four-byte basic_ostream<wchar_t> counterpart.
// The old 53-byte 0x008411E0 row spans two codecvt use_facet leaves (15 bytes
// each) and the 21-byte narrow basic_istream vbase destructor at 0x00841200.
// Single INT3 separators at 0x008411EF and 0x008411FF are alignment, not code.
#include <locale>
#include <istream>
#include <ostream>

template class _STL::basic_ostream<char, _STL::char_traits<char> >;
template class _STL::basic_istream<wchar_t, _STL::char_traits<wchar_t> >;
template class _STL::basic_ostream<wchar_t, _STL::char_traits<wchar_t> >;
template class _STL::basic_istream<char, _STL::char_traits<char> >;

template const _STL::codecvt<char, char, int> &
_STL::use_facet<_STL::codecvt<char, char, int> >(const _STL::locale &);
template const _STL::codecvt<wchar_t, char, int> &
_STL::use_facet<_STL::codecvt<wchar_t, char, int> >(const _STL::locale &);

// cl: /MD /EHsc /D_STLP_USE_STATIC_LIB /vd0
// stlport
// STLport stream vbase destructors install their own vtable and destroy basic_ios.
// Retail 0x00841220 installs basic_ostream<char>'s vtable at VA 0x0112F304.
// The positive four-byte adjustment identifies the complete-object ??_D entry.
// Retail 0x00841240 installs basic_istream<wchar_t>'s vtable at VA 0x0112F2FC
// and adjusts eight bytes to the wide basic_ios virtual base.
// Retail 0x00841260 is the four-byte basic_ostream<wchar_t> counterpart.
#include <istream>
#include <ostream>

template class _STL::basic_ostream<char, _STL::char_traits<char> >;
template class _STL::basic_istream<wchar_t, _STL::char_traits<wchar_t> >;
template class _STL::basic_ostream<wchar_t, _STL::char_traits<wchar_t> >;

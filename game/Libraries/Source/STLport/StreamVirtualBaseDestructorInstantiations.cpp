// cl: /MD /EHsc /D_STLP_USE_STATIC_LIB /vd0
// stlport
// STLport stream vbase destructors install their own vtable and destroy basic_ios.
// Retail 0x00841220 installs basic_ostream<char>'s vtable at VA 0x0112F304.
// The positive four-byte adjustment identifies the complete-object ??_D entry.
#include <ostream>

template class _STL::basic_ostream<char, _STL::char_traits<char> >;

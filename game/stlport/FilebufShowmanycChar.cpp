// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
// STLport 4.5.3 basic_filebuf<char>::showmanyc (FILE-backed get area).

// This TU only supplies one member-function instantiation.  Do not emit the
// header's per-TU locale initializer here: `ios_base::_Loc_init`'s constructor
// and destructor have no body anywhere in this STLport snapshot for MSVC
// (stl/_ios_base.h spells them only under `__BORLANDC__ && _RTLDLL`), so the
// static `ios_base::_Loc_init _LocInit;` that <fstream> declares would leave
// this object with two unresolved externals.  Same convention as
// game/Libraries/Source/STLport/WideFilebufFdOpen0084AAB0.cpp.  The macro
// only guards a separate .CRT$XCU initializer, not the matched showmanyc body.
#define __LOCALE_INITIALIZED
#include <fstream>

_STLP_BEGIN_NAMESPACE

template streamsize basic_filebuf<char, char_traits<char> >::showmanyc();

_STLP_END_NAMESPACE

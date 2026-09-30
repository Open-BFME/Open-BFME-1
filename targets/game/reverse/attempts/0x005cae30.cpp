// ??$?HDV?$char_traits@D@_STL@@V?$allocator@D@1@@_STL@@YA?AV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@0@ABV10@PBD@Z
// partial score=1.0 date=2026-09-30
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
#include <string>
namespace _STL {
template basic_string<char, char_traits<char>, allocator<char> > operator+(const basic_string<char, char_traits<char>, allocator<char> > &, const char *);
}

// ??A?$map@V?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@HU?$less@V?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@@2@V?$allocator@U?$pair@$$CBV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@H@_STL@@@2@@_STL@@QAEAAHABV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@1@@Z
// partial score=1.0 date=2026-09-30
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
#include <map>
#include <string>
typedef _STL::map<_STL::string, int> NarrowStringIntMap;
template int &NarrowStringIntMap::operator[](const _STL::string &key);

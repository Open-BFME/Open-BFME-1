// ??A?$map@VAsciiString@@V1@U?$less@VAsciiString@@@_STL@@V?$allocator@U?$pair@$$CBVAsciiString@@V1@@_STL@@@3@@_STL@@QAEAAVAsciiString@@ABV2@@Z
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Iinputs/vendor/stlport /Igame/Libraries/Source/WWVegas/WWLib
#include <stl/_config.h>
#undef _STLP_DEFAULT_CONSTRUCTOR_BUG
#include <map>

#include "ascii_string.h"

class Rva0007DF70MapLess
{
public:
    bool operator()(const AsciiString &left, const AsciiString &right) const
    {
        return left.compare(right) < 0;
    }
};

namespace _STL
{
template <> struct less<AsciiString> : public Rva0007DF70MapLess
{
};
}

typedef _STL::map<AsciiString, AsciiString> Rva0007DF70Map;
template AsciiString &Rva0007DF70Map::operator[](const AsciiString &);

// ??A?$map@VAsciiString@@VMapMetaData@@U?$less@VAsciiString@@@_STL@@V?$allocator@U?$pair@$$CBVAsciiString@@VMapMetaData@@@_STL@@@4@@_STL@@QAEAAVMapMetaData@@ABVAsciiString@@@Z
// partial score=0.95 date=2026-09-28
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/vendor/stlport /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/Generals/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/Generals/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/Generals/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/Generals/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWLib
#define _STLP_NO_EXCEPTIONS 1
#include <stl/_config.h>
#undef _STLP_DEFAULT_CONSTRUCTOR_BUG
#include "PreRTS.h"
#include "Common/AsciiString.h"

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

class MapMetaData
{
public:
    MapMetaData() {}
private:
    AsciiString m_value;
};

typedef _STL::map<AsciiString, MapMetaData> Rva0007DF70Map;
template MapMetaData &Rva0007DF70Map::operator[](const AsciiString &);

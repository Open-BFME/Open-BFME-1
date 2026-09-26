// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringbaseascii /Iinputs/reference/shims/sweep /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas
// stlport
#define __PLACEMENT_VEC_NEW_INLINE
#include "Common/Dict.h"
#include "Common/WellKnownKeys.h"

typedef char StringSizeCheck[(sizeof(AsciiString) == 4) ? 1 : -1];
typedef char KeySizeCheck[(sizeof(StaticNameKey) == 8) ? 1 : -1];

inline AsciiString::~AsciiString()
{
    ((StringBase<char> *)this)->releaseBuffer();
}

template<> inline int StringBase<char>::getLength() const
{
    return m_data ? m_data->length : 0;
}
template<> inline const char *StringBase<char>::str() const
{
    return m_data ? m_data->data : "";
}
template<> inline void StringBase<char>::concat(char c)
{
    concat(&c, 1);
}
template<> inline void StringBase<char>::concat(const StringBase<char> &s)
{
    concat(s.str(), s.getLength());
}

// Original free-function name is unresolved; full retail extent is
// 00195580..00195693, with a hidden owning AsciiString result.
// StaticNameKey initializers independently identify teamOwner at VA012A75C0
// (name VA0107C834) and teamName at VA012A75B8 (name VA0107C828).
AsciiString composeTeamNameAt00195580(const Dict *dict, bool *exists)
{
    AsciiString name = dict->getAsciiString(TheKey_teamOwner.key(), exists);
    if (exists && !*exists)
        return AsciiString::TheEmptyString;
    name.concat('/');
    name.concat(dict->getAsciiString(TheKey_teamName.key(), 0));
    if (exists && !*exists)
        return AsciiString::TheEmptyString;
    return name;
}

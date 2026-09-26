// Full266B 25C7C0..25C8CA. File identity from shipped random-site filename;
// exact member name remains unresolved. The caller passes this unchanged to
// 25C010 through ILT28C5E with a location pointer and an AsciiString reference.
// That full382B callee returns a created object pointer or null and ends RET8.
// Indexed vector access preserves retail's extent reload and x87 accumulation;
// hoisting a separate entries pointer changes both the loop and register layout.
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/Libraries/Source/WWVegas/WWLib
// stlport
#include <vector>
#include "ascii_string.h"
extern "C" unsigned int __cdecl strlen(const char *);
#pragma intrinsic(strlen)
inline AsciiString::~AsciiString() { ((StringBase<char> *)this)->releaseBuffer(); }
template<> inline bool StringBase<char>::isEmpty() const {
    return m_data==0 || m_data->length==0;
}
template<> inline const char *StringBase<char>::str() const {
    return m_data ? m_data->data : "";
}
template<> inline void StringBase<char>::set(const char *s) {
    set(s,s ? strlen(s) : 0);
}
extern int GetGameLogicRandomValue(int,int,const char *,int);
struct Rva0025C7C0Entry { AsciiString name; float weight; };
struct Rva0025C7C0Data {
    char prefix[0x210];
    _STL::vector<Rva0025C7C0Entry> choices;
};
class Rva0025C7C0Location;
class Rva0025C7C0Owner {
public:
    void chooseAt0025C7C0(Rva0025C7C0Location *);
    void *applyAt0025C010(Rva0025C7C0Location *,const AsciiString &);
    void *vtable;
    Rva0025C7C0Data *data;
};
void Rva0025C7C0Owner::chooseAt0025C7C0(Rva0025C7C0Location *location)
{
    AsciiString chosen;
    Rva0025C7C0Data *settings=data;
    int random=GetGameLogicRandomValue(0,99,"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\SpecialPower\\ElvenWoodSpecialPower.cpp",232);
    int cumulative=0;
    for (unsigned int i=0;i<settings->choices.size();++i) {
        cumulative=static_cast<int>(cumulative+settings->choices[i].weight);
        if (random<cumulative) {
            if (settings->choices[i].name.isEmpty()) return;
            chosen.set(settings->choices[i].name.str());
            break;
        }
    }
    applyAt0025C010(location,chosen);
}

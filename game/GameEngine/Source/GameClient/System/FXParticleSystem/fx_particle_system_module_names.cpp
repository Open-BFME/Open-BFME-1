// cl: /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// FXParticleSystem::DefaultModuleName<N>::GetValue -- the module display names.
// This is the name-side twin of DefaultModuleKey<N>::GetValue: a function-local
// AsciiString starts as "Default", appends the category name once, and returns
// its character data.
#include "string_base.h"

extern "C" unsigned int __cdecl strlen(const char *str);

// Upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString {
public:
    AsciiString(const char *s) { ((StringBase<char> *)this)->StringBase<char>::StringBase(s); }
    ~AsciiString() { ((StringBase<char> *)this)->releaseBuffer(); }
    void concat(const char *s) { ((StringBase<char> *)this)->concat(s, s ? strlen(s) : 0); }
    const char *str() const { return m_text ? m_text + 8 : ""; }

private:
    char *m_text;
};

namespace FXParticleSystem {

enum ModuleCategory {};
const char *GetName(ModuleCategory category);

template <int N>
struct DefaultModuleName {
private:
    static const char *GetValue();
};

template <int N>
const char *DefaultModuleName<N>::GetValue()
{
    static AsciiString value("Default");
    static bool once;
    if (!once) {
        value.concat(GetName((ModuleCategory)N));
        once = true;
    }
    return value.str();
}

template const char *DefaultModuleName<0>::GetValue();
template const char *DefaultModuleName<1>::GetValue();
template const char *DefaultModuleName<2>::GetValue();
template const char *DefaultModuleName<3>::GetValue();
template const char *DefaultModuleName<6>::GetValue();
template const char *DefaultModuleName<7>::GetValue();

}  // namespace FXParticleSystem

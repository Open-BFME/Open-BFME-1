// cl: /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// FXParticleSystem::DefaultModuleName<N>::GetValue -- the module display names.
// This is the name-side twin of DefaultModuleKey<N>::GetValue: a function-local
// AsciiString starts as "Default " (including the separator), appends the category name, and returns
// its character data.
#include "ascii_string.h"

extern "C" unsigned int __cdecl strlen(const char *str);

template<> inline void StringBase<char>::concat(const char *str)
{
    concat(str, str ? strlen(str) : 0);
}

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
    static AsciiString value("Default ");
    static bool once;
    if (!once) {
        value.StringBase<char>::concat(GetName((ModuleCategory)N));
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

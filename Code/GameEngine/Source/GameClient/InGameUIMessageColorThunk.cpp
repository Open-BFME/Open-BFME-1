// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib
// readable body of ?messageColor@InGameUI@@UAAXPBURGBColor@@VUnicodeString@@ZZ: Code/GameEngine/Source/GameClient/InGameUI.cpp

#include "PreRTS.h"

struct RGBColor;
class UnicodeString {};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/InGameUI.h
class InGameUI
{
public:
    virtual void messageColor(const RGBColor *, UnicodeString, ...);
};

__declspec(naked) void InGameUI::messageColor(const RGBColor *, UnicodeString, ...)
{
    __asm {
        _emit 08Dh
        _emit 04Ch
        _emit 024h
        _emit 00Ch
        _emit 0E9h
        _emit 0D7h
        _emit 0A2h
        _emit 044h
        _emit 000h
    }
}

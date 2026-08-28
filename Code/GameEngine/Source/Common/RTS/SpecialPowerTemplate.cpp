// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib
#include "PreRTS.h"
#include "ascii_string.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SpecialPower.h
class SpecialPowerTemplate
{
public:
    AsciiString getName() const;
    UnsignedInt getViewObjectDuration() const;
};

__declspec(naked) AsciiString SpecialPowerTemplate::getName() const
{
    __asm {
        _emit 051h
        _emit 08Bh
        _emit 041h
        _emit 004h
        _emit 085h
        _emit 0C0h
        _emit 0C7h
        _emit 004h
        _emit 024h
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 074h
        _emit 00Eh
        _emit 08Bh
        _emit 048h
        _emit 004h
        _emit 085h
        _emit 0C9h
        _emit 074h
        _emit 005h
        _emit 0E8h
        _emit 0C6h
        _emit 0FCh
        _emit 0FAh
        _emit 0FFh
        _emit 08Bh
        _emit 0C8h
        _emit 056h
        _emit 08Bh
        _emit 074h
        _emit 024h
        _emit 00Ch
        _emit 083h
        _emit 0C1h
        _emit 00Ch
        _emit 051h
        _emit 08Bh
        _emit 0CEh
        _emit 0E8h
        _emit 0B3h
        _emit 0EBh
        _emit 07Eh
        _emit 000h
        _emit 08Bh
        _emit 0C6h
        _emit 05Eh
        _emit 059h
        _emit 0C2h
        _emit 004h
        _emit 000h
    }
}

__declspec(naked) UnsignedInt SpecialPowerTemplate::getViewObjectDuration() const
{
    __asm {
        _emit 08Bh
        _emit 041h
        _emit 004h
        _emit 085h
        _emit 0C0h
        _emit 074h
        _emit 013h
        _emit 08Bh
        _emit 048h
        _emit 004h
        _emit 085h
        _emit 0C9h
        _emit 074h
        _emit 005h
        _emit 0E8h
        _emit 0FEh
        _emit 002h
        _emit 0DEh
        _emit 0FFh
        _emit 08Bh
        _emit 080h
        _emit 008h
        _emit 001h
        _emit 000h
        _emit 000h
        _emit 0C3h
        _emit 08Bh
        _emit 081h
        _emit 008h
        _emit 001h
        _emit 000h
        _emit 000h
        _emit 0C3h
    }
}

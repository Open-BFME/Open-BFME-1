// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib
#include "PreRTS.h"
#include "ascii_string.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SpecialPower.h
class Overridable
{
public:
    const Overridable *friend_getFinalOverride() const
    {
        if (m_nextOverride)
            return m_nextOverride->m_nextOverride
                ? m_nextOverride->m_nextOverride->friend_getFinalOverride()
                : m_nextOverride;
        return this;
    }

    void *m_vtable;
    const Overridable *m_nextOverride;
};

class SpecialPowerTemplate : public Overridable
{
public:
    AsciiString getName() const;
    UnsignedInt getViewObjectDuration() const;

private:
    char m_unreconstructed_08[0x100];
    UnsignedInt m_viewObjectDuration;
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

UnsignedInt SpecialPowerTemplate::getViewObjectDuration() const
{
    return ((const SpecialPowerTemplate *)friend_getFinalOverride())->m_viewObjectDuration;
}

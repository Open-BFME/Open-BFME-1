// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWLib
#include "PreRTS.h"
#include "ascii_string.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SpecialPower.h
class Overridable
{
public:
    const Overridable *friend_getFinalOverride() const
    {
        if (m_nextOverride)
            return m_nextOverride->friend_getFinalOverride();
        return this;
    }

    Overridable *friend_getFinalOverride()
    {
        if (m_nextOverride)
            return m_nextOverride->friend_getFinalOverride();
        return this;
    }

    void *m_vtable;
    Overridable *m_nextOverride;
    Bool m_isOverride;
};

class SpecialPowerTemplate : public Overridable
{
public:
    AsciiString getName() const;
    UnsignedInt getViewObjectDuration() const;

private:
    AsciiString m_name;
    char m_unreconstructed_10[0xF8];
    UnsignedInt m_viewObjectDuration;
};

AsciiString SpecialPowerTemplate::getName() const
{
    return ((const SpecialPowerTemplate *)friend_getFinalOverride())->m_name;
}

UnsignedInt SpecialPowerTemplate::getViewObjectDuration() const
{
    return ((const SpecialPowerTemplate *)friend_getFinalOverride())->m_viewObjectDuration;
}

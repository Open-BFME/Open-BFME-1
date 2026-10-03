// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#include "PreRTS.h"
#include "GameLogic/Object.h"
#include "GameLogic/Weapon.h"

// Complete retail50B; old five-argument signature is refuted by RET16.
// See identity_evidence/001d5ea0-001d63b0-complete-dispatch.md.
class Rva001D5EA0 {
public:
    void method(const Object *owner, const Coord3D *first, const Coord3D *second, unsigned int value) const;
private:
    void *m_rva001D5EA0_field00;
    const WeaponTemplate *m_rva001D5EA0_field04;
};
void Rva001D5EA0::method(const Object *owner, const Coord3D *first, const Coord3D *second, unsigned int value) const
{
    if (!owner || !first || !second) return;
    if (m_rva001D5EA0_field04)
        TheWeaponStore->createAndFireTempWeapon(m_rva001D5EA0_field04, owner, second);
}

// Slot+0C and four stack arguments are independently witnessed in the
// table installed at001D5E80. No semantic callback name is inferred.
class Rva001D63B0 {
public:
    virtual void rva001D63B0_slot00();
    virtual void rva001D63B0_slot04();
    virtual void rva001D63B0_slot08();
    virtual void rva001D63B0_slot0C(const Object *, const Coord3D *, const Coord3D *, unsigned int) const;
    void method(const Object *primary, const Object *secondary, unsigned int value) const;
};
void Rva001D63B0::method(const Object *primary, const Object *secondary, unsigned int value) const
{
    rva001D63B0_slot0C(primary, primary ? primary->getPosition() : 0,
                     secondary ? secondary->getPosition() : 0, value);
}

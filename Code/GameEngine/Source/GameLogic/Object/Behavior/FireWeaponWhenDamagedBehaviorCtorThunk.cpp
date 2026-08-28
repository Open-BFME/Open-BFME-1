// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class Thing;
class ModuleData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/FireWeaponWhenDamagedBehavior.h
class FireWeaponWhenDamagedBehavior
{
public:
    FireWeaponWhenDamagedBehavior(Thing *, const ModuleData *);
};

__declspec(naked) FireWeaponWhenDamagedBehavior::FireWeaponWhenDamagedBehavior(Thing *, const ModuleData *)
{
    __asm {
        _emit 0E9h
        _emit 052h
        _emit 012h
        _emit 01Dh
        _emit 000h
    }
}

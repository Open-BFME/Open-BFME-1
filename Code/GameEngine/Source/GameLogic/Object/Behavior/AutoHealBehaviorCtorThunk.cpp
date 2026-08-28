// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib
// readable body of ??0AutoHealBehavior@@: Code/GameEngine/Source/GameLogic/Object/Behavior/AutoHealBehavior.cpp

class Thing;
class ModuleData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AutoHealBehavior.h
class AutoHealBehavior
{
public:
    AutoHealBehavior(Thing *, const ModuleData *);
};

__declspec(naked) AutoHealBehavior::AutoHealBehavior(Thing *, const ModuleData *)
{
    __asm {
        _emit 0E9h
        _emit 0ADh
        _emit 05Dh
        _emit 01Ah
        _emit 000h
    }
}

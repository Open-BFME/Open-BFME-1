// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib
// readable body of ??0BoneFXUpdate@@QAE@PAVThing@@PBVModuleData@@@Z: Code/GameEngine/Source/GameLogic/Object/Update/BoneFXUpdate.cpp

class Thing;
class ModuleData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BoneFXUpdate.h
class BoneFXUpdate
{
public:
    BoneFXUpdate(Thing *, const ModuleData *);
};

__declspec(naked) BoneFXUpdate::BoneFXUpdate(Thing *, const ModuleData *)
{
    __asm {
        _emit 0E9h
        _emit 0FDh
        _emit 065h
        _emit 028h
        _emit 000h
    }
}

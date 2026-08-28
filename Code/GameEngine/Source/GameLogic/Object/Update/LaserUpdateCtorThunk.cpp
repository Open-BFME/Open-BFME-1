// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib
// readable body of ??0LaserUpdate@@: Code/GameEngine/Source/GameLogic/Object/Update/LaserUpdate.cpp

class Thing;
class ModuleData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/LaserUpdate.h
class LaserUpdate
{
public:
    LaserUpdate(Thing *, const ModuleData *);
};

__declspec(naked) LaserUpdate::LaserUpdate(Thing *, const ModuleData *)
{
    __asm {
        _emit 0E9h
        _emit 0CAh
        _emit 0B2h
        _emit 027h
        _emit 000h
    }
}

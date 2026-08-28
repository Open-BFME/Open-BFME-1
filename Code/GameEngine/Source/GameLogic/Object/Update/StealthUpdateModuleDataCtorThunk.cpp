// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib
// readable body of ??0StealthUpdateModuleData@@: Code/GameEngine/Source/GameLogic/Object/Update/StealthUpdate.cpp

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/StealthUpdate.h
class StealthUpdateModuleData
{
public:
    StealthUpdateModuleData();
};

__declspec(naked) StealthUpdateModuleData::StealthUpdateModuleData()
{
    __asm {
        _emit 0E9h
        _emit 078h
        _emit 0F2h
        _emit 00Dh
        _emit 000h
    }
}

// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib
// readable body of ??0BridgeScaffoldBehavior@@QAE@PAVThing@@PBVModuleData@@@Z: Code/GameEngine/Source/GameLogic/Object/Behavior/BridgeScaffoldBehavior.cpp

class Thing;
class ModuleData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BridgeScaffoldBehavior.h
class BridgeScaffoldBehavior
{
public:
    BridgeScaffoldBehavior(Thing *, const ModuleData *);
};

__declspec(naked) BridgeScaffoldBehavior::BridgeScaffoldBehavior(Thing *, const ModuleData *)
{
    __asm {
        _emit 0E9h
        _emit 0BEh
        _emit 059h
        _emit 01Eh
        _emit 000h
    }
}

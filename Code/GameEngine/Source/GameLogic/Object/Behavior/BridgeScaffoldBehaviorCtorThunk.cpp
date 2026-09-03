// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib
// readable body of ??0BridgeScaffoldBehavior@@QAE@PAVThing@@PBVModuleData@@@Z: Code/GameEngine/Source/GameLogic/Object/Behavior/BridgeScaffoldBehavior.cpp
// This row was re-homed to a ?j_ name and then RESTORED, and the reason is worth
// keeping: retail really did fold several module constructors onto one body, and
// the argument that it could not was wrong.
//
// I reasoned that ICF needs identical bodies WITH identical relocations, so two
// classes storing different vftables could never fold -- and concluded the stub
// belonged to whichever class owned the body it jumps to. CALL SITES REFUTE THAT.
// Several classes' ?friend_newModuleInstance@ factories, each a matched row, call
// this same stub to construct their object. A factory calling it to build an
// instance of its own class is direct evidence of what the stub constructs, and
// several of them naming one stub is direct evidence of a real fold.
//
// A call site that names the symbol beats any inference from stub topology. The
// unique-stub test says which body a stub reaches; it cannot say whose the body
// is when the body is shared.

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

// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib
// DO NOT FOLD THIS INTO AutoHealBehavior.cpp -- the cluster marker that said so is
// removed. The 5 bytes below are a jmp to 0x001EE950, which functions.csv has
// matched as a 276-byte ??0SpyVisionUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, and
// this is the only stub in .text jumping there. So this is SpyVisionUpdate's
// import thunk under the wrong name; the row survives only because a jmp's rel32
// is masked and every 5-byte tail-call thunk matches every other. Retiring it
// means deleting this file, which is a ledger decision. Logged mis-anchored?.
// (Do not write the cluster marker's phrase in prose here -- merge_cluster scans
// every line for it and hard-fails tree-wide on one that does not parse.)

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

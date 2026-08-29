// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib
// DO NOT FOLD THIS INTO AutoHealBehavior.cpp -- the cluster marker that said so is
// removed. The 5 bytes below are a jmp to 0x001EE950, which functions.csv has
// matched as a 276-byte ??0SpyVisionUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, and
// this is the only stub in .text jumping there. So this is SpyVisionUpdate's
// import thunk under the wrong name; the row survives only because a jmp's rel32
// is masked and every 5-byte tail-call thunk matches every other. Retiring it
// RE-HOMED. The row is now ?j_00048b9e@@YAXXZ -- the address-derived ILT
// convention gen_small already uses for 1,048 slots -- with an object-symbol
// note pointing at the ctor symbol this file emits. The five bytes keep their
// coverage, because they are real, and the row no longer asserts an identity
// the binary contradicts. The old name is tombstoned in deleted_rows.csv so a
// union merge cannot bring it back.
//
// This file survives only to emit those five bytes. Its C++ still spells
// AutoHealBehavior's constructor because that is what makes the compiler emit a
// tail-call thunk of the right shape; do not read the name as a claim.
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

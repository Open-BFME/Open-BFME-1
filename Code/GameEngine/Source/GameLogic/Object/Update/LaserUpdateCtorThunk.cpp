// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib
// THE NAME OF THIS FILE IS NOT A CLAIM. Its row is ?j_00035d91@@YAXXZ -- the
// address-derived ILT convention gen_small already uses for 1,048 slots -- with
// an object-symbol note pointing at the constructor symbol this C++ emits. The
// C++ still spells that constructor because that is what makes the compiler emit
// a tail-call thunk of the right shape, and for no other reason.
//
// 0x00035D91 is a 5-byte jmp to 0x002B1060, a 187-byte matched ??0ToppleUpdate@@, and
// exactly one stub in .text jumps there, so it is that function's import thunk.
// One class's constructor does not tail-call another's, and ICF cannot explain it:
// folding needs identical bodies WITH identical relocations, and two module
// constructors store different vftables -- 187 bytes could not fold in any case.
// The old name is tombstoned in deleted_rows.csv; retail's is UNLOCATED.
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

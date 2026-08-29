// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib
// THE NAME OF THIS FILE IS NOT A CLAIM. Its row is ?j_0000dafd@@YAXXZ -- the
// address-derived ILT convention gen_small already uses for 1,048 slots -- with
// an object-symbol note pointing at the constructor symbol this C++ emits. The
// C++ still spells that constructor because that is what makes the compiler emit
// a tail-call thunk of the right shape, and for no other reason.
//
// 0x0000DAFD is a 5-byte jmp to 0x0063E080, a 190-byte matched ??0GameSpyBuddyMessageQueue@@, and
// exactly one stub in .text jumps there, so it is that function's import thunk.
// One class's constructor does not tail-call another's, and ICF cannot explain it:
// folding needs identical bodies WITH identical relocations, and two module
// constructors store different vftables -- 190 bytes could not fold in any case.
// The old name is tombstoned in deleted_rows.csv; retail's is UNLOCATED.
// readable body of ??0GameResultsQueue@@QAE@XZ: Code/GameEngine/Source/GameNetwork/GameSpy/Thread/GameResultsThread.cpp

class GameResultsQueue
{
public:
    GameResultsQueue();
};

__declspec(naked) GameResultsQueue::GameResultsQueue()
{
    __asm {
        _emit 0E9h
        _emit 07Eh
        _emit 005h
        _emit 063h
        _emit 000h
    }
}

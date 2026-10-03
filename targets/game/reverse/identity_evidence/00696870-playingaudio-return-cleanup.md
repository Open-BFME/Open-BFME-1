# PlayingAudio returned-handle destructor at RVA 00696870

The prior row `?dup_00696870@@YAXXZ` used the `ThingRef` destructor emitted
by `GateOpenAndCloseBehaviorModuleDataDestructorThunk.cpp` as a byte provider.
It deliberately claimed no original type identity. Equal generic reference
release bytes alone do not identify this retail copy.

The independently matched native `MilesAudioManager::allocatePlayingAudio`
(0069AAA0, 158 bytes) returns `PlayingAudioRef` by value. Its retail prologue
pushes handler VA 010478E4; that handler loads FuncInfo VA 012371D4.
Unwind state 0 has predecessor -1 and action RVA 00C478CB. This action tests
bit 1 at EBP-14, clears it, loads the hidden returned-handle pointer EBP+4,
and jumps through ILT 000046F6 to 00696870. RET at C478E3 completes the
25-byte action before the handler. Both native predecessor states agree;
the state-0 emitted action is `$L433` and names `??1PlayingAudioRef@@QAE@XZ`.
Thus the matched typed caller's return lifetime selects this particular copy,
independently of the unrelated ThingRef provider.

The destructor independently decodes as 35 bytes, 00696870 through RET 00696892,
followed by INT3 at 00696893. It loads the handle pointee, skips null, calls
KERNEL32 InterlockedDecrement on pointee+4, and on a nonpositive result invokes
the pointee's virtual deleting destructor with flag 1. The native returned
handle destructor in the allocation TU emits that same body. Ghidra's
FUN_00a96870 agrees with the raw retail decode.

The proposed correction preserves the exact extent and one identity. It reuses
the matched caller's type spelling, does not add a symbol pin or rename the
unrelated ThingRef class, and does not claim that Zero Hour (which returns a raw
PlayingAudio pointer) supplies the BFME handle spelling. This is a provider and
identity correction, not newly recovered coverage for the existing 35-byte row.

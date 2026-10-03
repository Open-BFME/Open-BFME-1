# C253D0 counted-pointer cleanup

Parent `46B840` is the matched address-named hash_map operator[] instantiation
in `Rva0046C2A0HashIndex.cpp`. Independently matched
`WindowManager::registerPalantirCallback` (`46C930`) calls that operator on
its map at +94. It installs a reference-counted callback pointer in the
mapped value: count at pointee+4, deleting virtual call at slot zero.
The opaque mapped type keeps its existing `Rva0046AF20Mapped` identity.

Parent prologue -> handler `C25402` -> FuncInfo `E15608` -> unwind map
`E155F8` state 0 predecessor -1 proves action `C253D0`. Ghidra pointer search
finds VA `012155FC`. Bit 1 of EBP-18 guards the mapped temporary at EBP+4.
The action tail jumps to ILT `179CC`, reaching body `4673F0`. RET `C253E8`
proves the 25-byte action extent before the separate state-1 action.

The complete dependency body at `4673F0` loads the pointer, checks null,
decrements the pointee count, and calls deleting slot zero if count <= 0.
RET `467409` and following INT3 establish 26 bytes. There are no direct
call relocations. The native destructor originally reloaded the pointer
and produced a different instruction sequence. Caching the pointer and
using assignment-expression decrement reproduces all 26 bytes under the
ordinary strict selected-row verifier, independently of cleanup matching.

The change is TU-local and only alters that mapped destructor. One body pin
binds `??1Rva0046AF20Mapped@@QAE@XZ` to `4673F0`; the existing opaque body row
is retained, with no extra ledger claim or semantic rename. Parent source
and cleanup gates, plus pin consistency, are required before committing.

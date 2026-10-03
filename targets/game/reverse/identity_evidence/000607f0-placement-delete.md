# Standard placement delete at RVA 000607F0

The matched native LivingWorldPlayerArmy::xfer at 00365880 pushes handler
C1A152. Its FuncInfo E0A420 has state1 -> 0 at action C1A13B. Both native
predecessor states agree and the exact compiler label $L5813 calls
`??3@YAXPAX0@Z`, the standard void __cdecl operator delete(void*, void*).
The STLport vector placement-construction exception cleanup supplies both
arguments from EBP-CC and EBP-C4; caller cleanup is eight bytes. Retail
calls ILT2AAA9, whose E9 goes to 000607F0. This proves the specific copy
through the native parent lifetime, not by comparing generic empty bodies.

The canonical operator is emitted by the unchanged parent translation unit.
Retail is one RET at 607F0, then INT3 from 607F1 through 607FF. Ghidra creates
a one-byte function. The old generated ret-void member-method placeholder
has no supported member identity and should be replaced rather than aliased. The full
parent and native one-byte operator pass strict verification. No pin or
header/source edit is needed.

The separate OnlineChat action C30DBC calls the same operator with its own
frame offsets; that action remains blocked while its parent5337E0 is still
an unconverted1382-byte dump. The common callee binding does not prove its
parent frame.

## Session disposition

Both proposed rows passed scoped strict verification, but the normal commit
hook selected123 affected callers and waited behind a53-minute full build
and another queued gate. At the session deadline only this worker's waiting
build was terminated; the commit failed and all uncommitted ledger changes
were restored. No commit was bypassed or rewritten. The ledger still points
to its prior generated bodies. The exact verified proposal is saved locally
as build/b1/placement-delete-verified.patch; rerun its normal gates before
landing it in a later session. Both607F0 and C1A13B claims were released.

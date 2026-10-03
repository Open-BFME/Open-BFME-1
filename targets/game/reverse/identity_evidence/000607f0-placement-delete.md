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

## Session 3 independent confirmation and gate disposition

PeerRequest deque growth648810 pushes handlerC42102; FuncInfoE31BC0
state1 -> 0 selects C420EB. Its two native predecessor states agree, and
$L722 passes pointers from EBP-1A4/EBP-1A8 to the same standard placement
delete through ILT2AAA9, then pops8 and returns at C42101. Native
parseConditionState77D150 -> C5075D -> E3FE64 state2 -> 1 likewise selects
C50746/$L6579, with all three predecessors agreeing and RETC5075C.
These are independent construction-lifetime witnesses for the canonical
operator and exact23-byte actions, not merely identical empty bodies.

The operator, LivingWorld action and PeerRequest action passed strict scoped
verification again. The normal hook selected122 affected callers and waited
for the host-wide build lock. At the per-body budget, only this worker's
waiting build1163335 was terminated; the hook failed normally and the
three uncommitted ledger changes were restored. No commit was created or
bypassed. The proposal is build/b1/placement3-verified.patch for a future
normal gate. C50746 remains a prepared native action awaiting this binding.

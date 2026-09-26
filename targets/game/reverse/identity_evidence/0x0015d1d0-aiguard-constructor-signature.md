# AIGuardMachine constructor ABI at 0x0015D1D0

## Evidence and current claim

Before correction, the matched 691-byte ledger row called this body
`AIGuardMachine::AIGuardMachine(Object*)`. A separate existing pin names the
same physical address
`??0AIGuardMachine@@QAE@PAVObject@@VAsciiString@@@Z` -- `Object*` plus a
by-value `AsciiString`. The retail body ends in `C2 08 00` (`ret 8`) at
`0x0015D480`, which requires two stack words beyond the implicit `this`.

Two independently matched retail callers reach the same ILT 0x00026C15,
which targets 0x0015D1D0. AIStateMachine's 99-byte slot-10 factory at
0x0016FAA0 constructs the literal `AIGuardMachine` in a by-value string slot
at +0x36, pushes its owner pointer at +0x47, and calls at +0x4D.
GiantBirdGuardMachine's 429-byte constructor at 0x002C05C0 similarly
constructs `GiantBirdGuardMachine` in a string slot at +0x1B, pushes the owner
at +0x36, and calls at +0x39. The callee copies that string, then passes the
owner/name plus a `false` flag to the three-argument StateMachine base
constructor. This is an ABI
finding, not an inference from `ret 8` alone. `callers_of.py` finds these two
current callers.

The Zero Hour AIGuardMachine declaration has a one-argument constructor and
the historical BFME thunk source was written with that signature. The BFME
call sites and callee body are the authority for this binary's ABI. The
historical source symbol can remain as the physical emitter alias; it is not
the corrected retail identity.

## Design checkpoint before ledger changes

Independent review confirmed both matched retail call paths and the base
constructor's third flag. Proceed with
`correct_match_identity.py` to replace the matched ledger name at the same
0x0015D1D0/691B source with the existing two-argument pin name. Its normal
`object-symbol=<old one-argument source symbol>` note will keep selecting the
unchanged verified emitter, and its exact `(name, RVA)` tombstone will prevent
union merges from reviving the false signature. Do not edit the historical
naked source body or invent a new C++ implementation for this ABI correction.
The alternative of changing the thunk declaration would rename its emitted
symbol and add a new naked-function diff, risking byte and anti-lift checks
for no byte benefit. Retaining the one-argument row leaves an incorrect ABI
claim even though the pin happens to target the right address.

The correction must pass the constructor's scoped byte/relocation gate, both
callers' affected source gates, `check_csv`, pin and identity consistency,
name-history checks, and normal hooks. A successful byte comparison alone
does not establish the ABI; the two call sites and direct retail return do.
Expected byte progress is zero. The adversarial review rejected a hidden
argument alternative: both callers construct the named string in the outgoing
slot and the callee copies it before its base call. It also checked that no
existing ledger name or tombstone collides with the proposed two-argument
name. The Zero Hour signature describes an older source version, not this
BFME call. The old emitted one-argument symbol remains only an alias, scoped
to its existing source and byte gate.

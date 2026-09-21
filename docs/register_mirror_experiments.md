# Register-mirror (this vs. secondary-pointer) experiments, 2026-09-21

Follow-up to the shape_levers.md row "Register assignment follows local
DEFINITION ORDER" (line 17), which the fleet had already found ineffective
on eight banked bodies that differ from retail *only* in which
callee-saved register letter (ESI/EDI/EBX/EBP) holds `this` versus a
second long-lived pointer. This session built a micro-harness to find the
real rule. It found a real, reproducible trigger for one whole sub-class of
the symptom, confirmed it resists every reordering lever the fleet had
already tried (declaration order, this-alias hoist, unconditional
promotion, guard reordering, `/Ob1`, `pragma optimize`), and could not find
a source shape that reverses it. No body was landed this session. Recorded
here per WORKER_RULES step 9/10 so the next seat does not repeat the same
dead ends.

## Harness

`build/regmirror/` (untracked, gitignored under `build/*`, same pattern as
`build/sib_experiment/` documented in `docs/sib_lea_experiments.md`).
`build/regmirror/compile.py` wraps `tools/build.py`'s
`compiler_command`/`compiler_environment` (same wine/cl.exe path, same
`INCLUDE`/`LIB` env) and inserts `-FAcs -Fa<name>.cod` before the trailing
`-Fo`/source pair. Usage: `python3 build/regmirror/compile.py <name>` reads
`build/regmirror/<name>.cpp`, writes `<name>.obj` and `<name>.cod` (assembly-
with-source listing). No retail bytes exist for these scratch functions —
read the `.cod` directly, there is nothing to diff with `tools/probe.py`.
Six probe files (`probe1.cpp`..`probe6.cpp`, ~25 variant functions total)
were written and compiled; each function `__declspec(noinline)`, values
kept alive past their last "natural" use via an extern `use2`/`use3` call
or a second read, so the allocator is actually forced to pick homes.

## Finding 1 (negative, confirms existing note): field-read order follows
memory offset, not source declaration order

`probe1.cpp` v1/v2, v5/v6: two member fields loaded through the same base
pointer, with the two reads' SOURCE STATEMENT order swapped between
variants. In every pair the compiled instruction order was identical —
lower struct offset loads first, regardless of which local was declared or
read first in the C++ text. This reproduces, with a cleaner two-line
repro, the same conclusion `docs/sib_lea_experiments.md` Experiment 1
already reached for SIB base selection ("declaration order of the two
locals never changed anything"). Consistent with why the fleet's plain
"reorder the local declarations" lever already failed on all eight bodies.

## Finding 2 (positive, reproducible): `this` copies into a callee-saved
register unconditionally, at the EARLIEST point on ANY path that needs it
— not at its first source-level use

`probe1.cpp` v1: `this` is not read anywhere in the source until after the
first call (`sideEffect()`), yet the compiled prologue is `push esi; push
edi; mov esi,ecx` — `this` is copied to ESI immediately, before the call,
regardless of where the C++ text first mentions it. `probe2.cpp` w1-w5
confirm this holds across five different guard-chain shapes (early-out
count, order, extra calls): `this` is always copied to a register in the
prologue, and with only one long-lived value it is always **ESI**. This
matches candidate (a) from the brief ("materialized at the first
instruction that copies it, not at declaration") but is not sufficient by
itself to predict WHICH letter, as findings 3-4 show.

## Finding 3 (positive, reproducible, the real trigger): an interior
sub-object pointer reused across 2+ virtual/member calls outranks `this`
for ESI, evicting `this` to EDI — but only when the pointer is an
ADJUSTED (`this+N`) address, not an independent pointer

`probe4.cpp`/`probe5.cpp` (`Owner::y2`/`z1`/`z2`/`z3`, 5 variants): a class
with an embedded polymorphic `Interior m_interior` at `this+0x20` (exactly
the layout of the landed neighbour `Rva21ABF0RingDispatch.cpp` and the
banked `0x0021AC30` stash), called through `m_interior.slotX()` 2-3 times
(never cached into a named local — same as the real stash). In **every**
variant tried:

```
push edi
mov  edi, ecx        ; this -> EDI (demoted)
...
lea  esi, [edi+28]   ; &m_interior -> ESI (the interior sub-object wins)
```

Tried and INEFFECTIVE at reversing it (all still produced this=EDI,
interior=ESI):
- unconditional interior use vs. gated by an early-return (`z1` vs `y2`);
- interior guard moved to be the FIRST test instead of the second (`z2`);
- the early-return moved to AFTER the interior block instead of before it
  (`z3`).

This exactly reproduces the mis-color the fleet already sees on
`0x0021AC30` (`Owner::invoke`, our compile: this=edi/interior=esi; retail:
this=esi). The "explicit self-local" and `shape_family_levers.py
--families register` attempts already recorded in `reverse/re_attempts.log`
for that RVA are the same reversal this session also tried and also could
not reverse — this session's contribution is pinning down that it is
specifically the **2+ calls through an adjusted sub-object address** that
causes it, not the guard structure around it.

`probe6.cpp` isolates the two necessary conditions:
- `OwnerAdjOne::q1` — same adjusted `this+0x20` interior, but only ONE
  call through it: `this` stays ESI, no eviction.
- `OwnerUnadj::q2` — TWO calls, same call pattern as the real stash, but
  through an independent (already-a-pointer, no `lea this+N` needed)
  member `Interior *m_shapePtr` instead of an embedded sub-object: `this`
  stays ESI, the second value (`a`, a call return) gets EDI as expected,
  no eviction.

So the trigger is specifically: **an address computed as `this` plus a
nonzero constant offset (a `lea` into an embedded sub-object), used as the
implicit receiver of 2 or more calls, is cached into ESI ahead of the
function's own `this`.** A plain independent pointer member used the same
way (2+ calls) does NOT evict `this`. A single call through the adjusted
pointer does NOT evict `this` either.

## Finding 4 (positive, same class, different flavor): a loop-induction
pointer walked via `cur = cur->next` and read again after a call also
outranks `this` for ESI

`probe1.cpp` v3 vs v4: identical two competing values (`this`-derived
scalar `a = m_scalar`, and a list-walk pointer `cur = m_list` that is
dereferenced in a loop and read again after the intervening call), only
the **statement order relative to the call** differs.
- v3 (scalar read before the call, loop pointer read only after): `this`
  gets ESI, the scalar gets EDI, the loop pointer needs no persistent
  register at all (lives briefly in EAX after the call).
- v4 (loop pointer read before the call, scalar read only after): `this`
  gets **EDI**, the loop pointer gets **ESI**, and the scalar is folded
  back into `this`'s dying register.

So whenever the loop-induction pointer itself must be READ THROUGH `this`
*before* the call (forcing it to also survive the call, i.e. it becomes a
second genuinely call-crossing value derived from `this`), it wins ESI and
`this` is bumped to EDI — the same shape of eviction as Finding 3, just
triggered by a mutating loop pointer instead of a static `this+N` address.
This plausibly explains the `0x00150A70` (AIGroup) and `0x00372E40`
mirrors, where a member-list walk pointer / `object` local plays the same
role, though this session did not build a dedicated harness reproduction
for those two specifically (time budget) — flagging this as the first
thing to try reproducing next.

## What this does NOT explain

- `0x0027ACF0`: three callee-saved registers are in play (retail
  this=EBX, ours this=EDI) with several candidate receivers (`this`,
  `TheAI->m_pathfinder`, the vtable-slot-128 cast) but none of them is an
  adjusted `this+N` sub-object called 2+ times, so Finding 3 doesn't
  directly predict it. Not reproduced this session.
- `0x0024E990`: EBP/EBX swap between two ordinary locals (a long-lived
  name-address pointer and a short-lived argument pointer), not an
  ESI/EDI pair and not `this`-related at all — this is very likely the
  liveness-duration class the existing shape_levers.md rule already
  targets, just still unresolved; out of scope for this session's harness.
- `0x001A6370`: the residue is described as an ECX/EDX, EAX/ECX
  scratch-register swap inside a delta computation, not a callee-saved
  letter mirror — a different symptom class entirely (more likely related
  to the existing SIB-operand-order note in shape_levers.md than to this
  one).

## Conclusion / guidance for the next seat

Do not re-try plain local-declaration reordering, this-alias hoisting, or
guard-order changes on `0x0021AC30`, `0x0027ACF0`, or `0x00150A70` — this
session and the banked evidence together cover that space and it is dead
per Finding 1 and Finding 3's negative sub-results. The one lever that DID
reproduce the failure mode (Finding 3: an embedded sub-object address
reused across 2+ calls always wins ESI over `this`, with no reversal found
across 8 structural variants) suggests the fix, if one exists, is not a
source respelling within the current reconstructed shape at all — it
implies retail's real source avoids caching the interior/loop pointer
across multiple calls in the first place (e.g. a difference in how many
times the sub-object is genuinely dereferenced, or an intermediate value
retail's original code computes that this reconstruction's field/callee
identification hasn't found yet). That is an identification problem, not
a register-lever problem, and further sessions should look for a MISSING
call or field read in the current stashes rather than more register
spellings.

No new bodies landed. `reverse/re_attempts.log` is unchanged by this
session; this file documents scratch-only work in the untracked
`build/regmirror/` directory.

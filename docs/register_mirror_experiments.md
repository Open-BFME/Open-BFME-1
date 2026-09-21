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

## R2b follow-up, 2026-09-21: testing a WEIGHT-based allocator hypothesis

R2's Finding 3 pinned the trigger (an adjusted `this+N` sub-object address
reused as receiver for 2+ calls evicts `this` from ESI to EDI) but found no
source respelling that reverses it. This session's hypothesis: the
allocator ranks candidates by a WEIGHT (use count, multiplied by loop
depth) into a fixed register preference order, so changing the RELATIVE
weight of `this` vs. the interior pointer — without changing the emitted
instructions — might flip the assignment. Reused R2's harness
(`build/regmirror/`, new `probe7.cpp`, 11 variants) on the probe4 `Owner::y2`
shape (baseline: this=EDI, interior=ESI, 3 interior calls).

| variant | uses(this) | uses(interior) | loop | this-reg | interior-reg | stream identical to y2? |
|---|---|---|---|---|---|---|
| y2 (baseline) | ~4 (2 fields, re-read on divergent paths) | 3 calls | no | EDI | ESI | (baseline) |
| t1 (+1 real this-use, opaque call) | 5 | 3 | no | EDI | ESI | no (extra call) |
| t2 (+2) | 6 | 3 | no | EDI | ESI | no |
| t3 (+3) | 7 | 3 | no | EDI | ESI | no |
| f1 (dup field read, CSE'd to 0 net loads) | +1 syntactic / 0 net | 3 | no | EDI | ESI | no (opaque call on the dup remains) |
| f2 (`this` into empty `__forceinline` helper, fully eliminated) | +1 syntactic / 0 net asm | 3 | no | EDI | ESI | **yes, byte-identical** |
| l1 (interior called once, in a real 2-iteration loop) | ~3 | 1 static / 2 dynamic | yes (real) | **EBX** | EDI | no |
| l2 (same loop, trip count 1, compiler-unrolled away) | ~3 | 1 call, not cached | no (unrolled) | **ESI** | (not cached; re-`lea`'d inline) | no |
| e1 (this-use first, equalized weight) | 2 | 3 | no | EDI | ESI | no (branch removed) |
| e2 (interior calls first, this-use only after) | 2 | 3 | no | EDI | ESI | no |
| g1 (3-way: this, interior, independent `m_other` ptr via 2 calls) | ~3 | interior 2 / m_other 2 | no | EDI | ESI (interior); **m_other gets no register at all**, reloaded from `[this+N]` at each call site | no |

### Conclusions

1. **Real extra uses of `this` don't matter, up to +3.** t1-t3 show the
   allocator's decision is insensitive to `this`'s raw use count over this
   range; the interior keeps ESI regardless. The "weight" is not a simple
   use-count tally that source-level padding can tip.
2. **Uses that the optimizer folds away have zero effect, confirmed with a
   byte-identical control** (f2: `ignoreThis(this)` through an empty
   `__forceinline` vanishes completely — 0x21..0x51 in `f2`'s listing is
   instruction-for-instruction identical to `y2`'s, including the register
   assignment). This proves the allocator's ranking runs on the
   **post-DCE/post-CSE live IR**, not raw source use counts — so *no*
   optimizer-folded-use lever (dead branch, redundant read, no-op helper,
   `(void)this`) can ever move the needle, because by the time the
   allocator ranks candidates the fold has already happened. This closes
   off that entire branch of the hypothesis definitively rather than just
   empirically for these two probes.
3. **First-use order doesn't matter** (e1 vs e2: interior-first still
   loses to nothing — `this` is EDI and interior is ESI either way),
   confirming/extending R2's guard-order-invariance finding: it is not a
   tie-break-by-order rule, because there is no tie to break — the interior
   unconditionally outranks `this` once it is called 2+ times through an
   adjusted address, independent of textual position.
4. **Loop depth is the one lever that actually moves the needle, but only
   when the loop survives to final code.** `l1` (genuine 2-iteration loop)
   is dramatic: `this` drops two full slots to EBX, the loop induction
   variable — a trivial `int i`, otherwise the lowest-weight value in the
   function — claims ESI outright, and the loop-invariant interior address
   takes EDI. `l2` (same source shape, but a constant trip count of 1 that
   the compiler recognizes and unrolls before allocation) collapses back to
   the single-call outcome (`this` keeps ESI, interior isn't cached at
   all) — matching R2's `probe6.cpp` `q1`. So loop-depth weighting, like
   the fold case above, is computed on the **final optimized loop
   structure**, not on the presence of `for`/`while` syntax. This is a
   real, reproducible lever in the abstract, but it requires the function
   to actually iterate — it cannot be added to a body whose real control
   flow is a fixed sequence of distinct calls (as both target RVAs are)
   without changing the instruction stream, so it is not usable as a
   same-bytes respelling trick here.
5. **A plain (non-adjusted) pointer member reused across 2+ calls competes
   for nothing** (g1's `m_other`): even with two calls exactly like the
   interior's, it never earns a callee-saved register at all when an
   adjusted sub-object is already in play — it's simply reloaded from
   `[this+N]` at each call site. This reinforces R2's probe6 result and
   suggests the real ranking is closer to a **rematerialization-cost
   model** (cache only what's nontrivial/expensive to recompute — an
   arithmetic `lea this+N` — not a free memory load) than a naive
   use-count weight, which independently explains why `this` itself
   (equally "free" to reload, it's the incoming `ecx`) can still lose its
   preferred register: the model isn't ranking `this` against the interior
   by cost, it's specifically privileging the adjusted-address value.

**Overall: the WEIGHT-based hypothesis as stated is refuted for the
non-loop case.** Every lever that only changes source-level use counts,
use order, or adds-then-removes instructions (folded uses) left the
assignment untouched. The single lever that does work (real loop
iteration) is a structural/semantic change, not a respelling, and doesn't
fit either target body's actual control flow (distinct calls to different
vtable slots, not a repeated call over an index). This corroborates R2's
closing guidance: the fix is not a source-shape lever inside the current
reconstructed body at all.

### Applied to the two banked targets

- `0x0021AC30` (`Owner::invoke`, `reverse/attempts/0x0021ac30.cpp`, score
  0.77): body shape is exactly the probe4/probe7 `y2`/`t*`/`e*` case (this
  + interior called via `slot49`/`slot64`/`slot68`, no loop, no
  candidate for a real iteration) — none of this session's positive or
  negative results give it a usable lever. Not re-attempted past the
  harness stage; still banked at 0.77, no new probe.py run needed since no
  new lever applies.
- `0x0027ACF0` (`AIUpdateInterface::...MoodTargetCheck`,
  `reverse/attempts/0x0027acf0.cpp`, score 0.5): three-register case
  (retail this=EBX, ours=EDI), which is the same class `g1` models here,
  but g1 shows the third competing pointer just doesn't get cached at all
  rather than reproducing a three-way EBX/EDI/ESI split — this session's
  harness doesn't reproduce that residue's exact shape, so no lever from
  this table applies to it either without a dedicated repro (left for a
  future seat, not attempted here given the time budget).

No bodies landed this session. `build/regmirror/probe7.cpp` is
untracked scratch (same pattern as probe1-6), not part of this commit.

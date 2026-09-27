# Allocation-only near misses: dataset, model, and one general lever (2026-09-26)

39 banked bodies (27 KB) probe at `shape 1.000`: retail's instruction
sequence once register names and constants are normalised, with bytes that
still differ. The earlier permuter (1,871 random mutations, 0 improvements),
about 25 hand respellings of `buildUpgrade`, and the full switch sweep
(`flag_sweep.py`, see `shape_levers.md`) had not moved any of them. This
session built a dataset of what actually differs, derived a model of how
MSVC 7.1 hands out scratch registers, and tested it. The model predicted a
lever. The lever landed four bodies, it has a control in each, and it is
specific enough to point at the one site in a body where it applies.

**Result:** the scratch registers (EAX/ECX/EDX) are handed out round-robin,
and whether a value that is loaded and then pushed as a call argument takes a
turn depends on how the source spells the argument. `f(m_x)` and
`T x = m_x; f(x)` (or `f(getX())`) compile to the same `mov r,[mem]; push r`,
but only the copied form advances the rotation. Toggling that spelling at the
one pushed load **upstream** of the first mismatch fixed 0x00271630,
0x0021B310, 0x0029BDE0 and 0x0024C420 (453 B). It does not reach the
callee-saved, stack-slot or SIB classes, and 0x0020DF90 has no upstream site.

## Tooling

- `tools/alloc_residue.py <stash> <mangled> 0xRVA` (or `--list FILE`):
  pairs retail and ours instruction by instruction (it refuses a body whose
  shape is not identical), splits retail's registers into def-use webs by
  reaching definitions over the CFG, and prints each web whose register
  differs, with the kind of def (this, stack argument, load, lea, call result,
  copy), use count, span, calls crossed and loop membership. It lists
  differing stack displacements and two-register SIB base/index swaps
  separately, because those are different residues.
- Scratch harness (untracked, `build/alloc/`): `cod.py` compiles a probe TU
  with `-FAsc` and prints the listing; `exp.py` applies literal source edits
  to a bank and diffs each variant against retail; `autorot.py` generates the
  push-copy toggles described below, one site per variant. Both are now one
  tracked tool, `tools/rotation_sweep.py`.

## The dataset

Classes over the 39 bodies (`alloc_residue.py --list`):

| class | bodies | what differs |
|---|---|---|
| scratch | 17 | EAX/ECX/EDX assignment of short-lived temps (span 1-7 instructions, 1-3 uses, no call crossed) |
| callee-saved | 6 | ESI/EDI or EBX/EBP swapped between two long-lived values |
| slot | 6 | stack displacements only |
| sib | 4 | two-register `lea`/address base and index exchanged (documented, exhausted) |
| mixed | 6 | two or more of the above (the 14 KB `Render` body has all four) |

Per body (webs whose retail register differs; `u` uses, `s` span in
instructions, `c` calls crossed, `L` inside a loop):

| rva | size | ins | differing ins | class | webs |
|---|---|---|---|---|---|
| 0x00960a30 | 14081 | 3787 | 236 | sib+slot+callee-saved | edi->ecx/edi/edx arith +1ea2 u45 s657 c4 L1; edx->edi/edx lea,load +1f45 u19 s391 c4 L1; ecx->ecx/edi callret,lea +1f61 u22 s274 c2 L1; slots -328x1,+328x1; 45 SIB swaps |
| 0x0019c920 | 1810 | 538 | 108 | slot+scratch | eax->ecx lea +04d8 u1 s2 c0 L1; slots +4x4 |
| 0x00721380 | 1557 | 505 | 32 | slot+callee-saved | ebx->ebx/edi copy,stackload +0027 u19 s463 c52 L1; edi->ebx/edi const,stackload +0272 u7 s241 c25 L1; slots -4x1,+4x1 |
| 0x0091be00 | 1059 | 247 | 86 | callee-saved+scratch | byte loads of four flags into al/bl/cl/dl permuted (+0069..+0091) |
| 0x0078d410 | 557 | 169 | 20 | sib | sib +0088 |
| 0x0078ff40 | 546 | 176 | 12 | sib | sib +0118,+0179 |
| 0x003e3650 | 538 | 177 | 22 | callee-saved | ebp->ebx load +000a u2 s47; ebx->ebp +0011 u8 s146 c3 L1; ebp->ebx copy +00c4 u6 s85 c3 L1 |
| 0x009c0a30 | 524 | 169 | 24 | slot | slots -8x6,-4x3,+8x1,+20x1 |
| 0x00796480 | 519 | 174 | 18 | sib+slot | slots -8x2,+8x2; sib +00bf,+0119,+014a |
| 0x001649b0 | 486 | 141 | 47 | slot | slots -4x11,+16x2,+20x4 |
| 0x00893f10 | 457 | 147 | 19 | scratch | edx->ecx stackload +0197 u1 s7; ecx->edx lea +019e u1 s2 |
| 0x000ff290 | 452 | 131 | 37 | slot | slots -4x19,+100x2 |
| 0x005a0450 | 363 | 144 | 7 | sib | sib +00de |
| 0x003f5c70 | 335 | 128 | 26 | callee-saved | ebp->ebx stackload +0004 u4 s68 c5; ebx->ebp load +009b u1 s13 c1 |
| 0x0047e010 | 325 | 111 | 19 | scratch | cyclic -1 over +009e..+00ce (ecx->eax, edx->ecx, eax->edx) |
| 0x0035f600 | 295 | 82 | 16 | slot | slots +4x1 |
| 0x007f71b0 | 286 | 103 | 7 | scratch | vtable temp eax->edx +0029 |
| 0x0069d620 | 285 | 99 | 16 | scratch | mixed eax/edx over +001c..+00ea, in a loop |
| 0x0078fde0 | 274 | 106 | 12 | sib | sib +00cb |
| 0x001aba80 | 235 | 68 | 36 | callee-saved | esi->edi copy(this) +0017 u13 s54 c6; edi->esi lea +0059 u7 s16 c1 |
| 0x0023c4d0 | 217 | 80 | 14 | callee-saved+scratch | edx/esi and eax/ecx over +004a..+0082, in a loop |
| **0x0024c420** | 210 | 72 | 6 | scratch | eax->edx stackload +00b0 u1 s3 — **landed** |
| 0x0023cdd0 | 184 | 74 | 16 | scratch | cyclic +1 over +007e..+00ac (eax->ecx, ecx->edx, edx->eax) |
| **0x0024e990** | 163 | 53 | 26 | callee-saved | EBP/EBX swap: lea +001b, stackload +002f, two call results — **landed** with a shared inline controlling-player accessor |
| 0x0048d460 | 159 | 70 | 24 | callee-saved | esi/edi swap between two call results |
| 0x0023d850 | 147 | 49 | 5 | scratch | ecx->eax load +0065 u1 s2 L1 |
| 0x0083f1c0 | 132 | 48 | 5 | scratch | edx->ecx load +0065, add +006b |
| 0x00618a00 | 112 | 43 | 5 | scratch | edx->ecx load +0042 (reuses its dying source register) |
| **0x0029bde0** | 98 | 43 | 5 | scratch | ecx->eax +0043, vtable eax->edx +0046 L1 — **landed** |
| 0x00844400 | 87 | 28 | 3 | slot | slots -8x1 |
| 0x00844460 | 87 | 28 | 3 | slot | slots -8x1 |
| 0x0084ada0 | 81 | 31 | 10 | scratch | eax/ecx swapped over +0028..+0035 |
| 0x0084af80 | 81 | 31 | 10 | scratch | eax/ecx swapped over +0028..+0035 |
| **0x0021b310** | 75 | 32 | 4 | scratch | eax->ecx load +002c u1 s2 — **landed** |
| **0x00271630** | 70 | 30 | 4 | scratch | vtable temp eax->edx +0025 — **landed** |
| 0x002d9f90 | 67 | 27 | 2 | scratch | eax/edx swap +0024..+002d |
| 0x006eb000 | 54 | 23 | 3 | scratch | eax/ecx swap +0023..+0029 |
| 0x009f2ae0 | 46 | 17 | 1 | callee-saved | esi->edx copy +0010 L1 |
| 0x0020df90 | 38 | 14 | 5 | scratch | eax->ecx load +000c, ecx->edx stackload +000f |

What the features show. None of the per-web features separates retail's
choice from ours inside a body: the mismatched scratch webs are almost all
one or two uses, span under eight instructions, cross no call and sit outside
loops, the same profile as the scratch webs that match. The separating fact
is not a property of the web. It is the **phase**: in 0x0023CDD0 every
scratch temp over a 46-byte stretch is shifted one place along
EAX→ECX→EDX→EAX, and in 0x0047E010 every one is shifted the other way. A
constant cyclic shift over a run of unrelated temps means some state carries
from one temp to the next, so the cause sits before the first mismatch.

## Model: MSVC 7.1 hands out scratch registers round-robin

Probe TUs compiled with the project's own `cl.exe` (`/O2`), then read from
the `.cod` listing:

| probe | source | scratch registers in order |
|---|---|---|
| P0 | `g2(ga, gb)` | eax, ecx |
| P1 | `g1(gc); g2(ga, gb)` | eax \| ecx, edx |
| P2 | `g1(gc); g1(gd); g2(ga, gb)` | eax \| ecx \| edx, eax |
| P3 | three `g1` then `g2` | eax \| ecx \| edx \| eax, ecx |
| V2 | `h->v(); g2(ga, gb)` | vtable eax \| ecx, edx |
| V4 | `h->v(); h->v(); g2(ga, gb)` | vtable eax \| vtable **edx** (ECX holds the receiver) \| eax, ecx |
| T1 | `if (gc) g0(); g2(ga, gb)` | gc eax (tested) \| eax, ecx |
| V1 | `h->v(); if (gc) g0(); g2(ga, gb)` | vtable eax \| gc eax (tested) \| ecx, edx |
| A3/A4/A5 | dead local, copy chains, split locals before the call | no change from V2 |
| M1-M5, N1-N3, S1-S3, O1-O2 | `p->m++`, `+= 1`, `= p->m + 1`, reference, local copy, … | identical code and registers across each group |

Read together:

1. A single pointer walks EAX→ECX→EDX→EAX in program order across the whole
   function. It is not reset at calls or at block boundaries (V1). At a join
   the state is the one the code falls into.
2. A temp skips a register that another value holds over its live range (V4:
   ECX is the receiver, so the second vtable load takes EDX).
3. A value used only by `test`/`cmp` feeding a branch takes EAX without
   moving the pointer (T1, V1).
4. The pointer counts **code-generation temporaries**, not final
   instructions. `p->m++` compiles to `inc [eax]` and still moves the pointer
   as if three temps had been used. Front-end-equivalent spellings (M, N, S,
   O groups) normalise to the same temps, so they never differ.
5. Allocation order inside one statement is not always emission order (Q4:
   the vtable temp of `gh->x(gc)` is allocated before the pushed `gc`). Pairs
   swapped inside one expression (0x0084ADA0, 0x002D9F90, 0x006EB000) are
   this, not a phase shift.

This explains the earlier negative results. Declaration order, first-use
order and use counts do not enter at all, and a folded use cannot matter
because folding happens before allocation (the R2b finding in
`register_mirror_experiments.md`). It also explains why the
`__fastcall` vtable adapter (RegallocLever-2/3) sometimes works: the dummy
EDX argument is one more allocation. When it failed on the seven sites in
`shape_levers.md`, the missing step was somewhere else.

## Hypotheses and experiments

**H1. The residue is a phase difference in the rotation, caused upstream of
the first mismatch.** Test: in banks whose mismatches look like a constant
cyclic shift, change a construct before the first mismatch that could change
the temp count, and nothing else.

**H2. The upstream difference is how a pushed call argument is spelled.**
`f(m_x)` lets MSVC take the load's register outside the rotation. It
probably pushes the memory operand and splits it late. A copy
(`T x = m_x; f(x)`, an inline getter, or an identity inline `rot(m_x)`)
allocates the register inside the rotation, one step. The effect is binary:
`rot(rot(x))` equals `rot(x)`.

**H3. Callee-saved swaps follow the same rotation over ESI/EDI/EBX/EBP.**
Not established. The toggles did not move any of the six callee-saved bodies.

| experiment | bodies | change (one at a time) | effect |
|---|---|---|---|
| return type of the preceding call (void/int/bool) | 0x0020DF90 | declaration only | none |
| real multiple inheritance instead of `this-0x10` arithmetic | 0x0020DF90 | model | none |
| inline wrappers around each call, reference/int/bool/char argument types, qualified calls | 0x0020DF90 | 17 spellings | none |
| typed `__fastcall` vtable call with a dummy EDX argument | 0x0020DF90 | adapter | vtable temp moves to EDX and the **following** temps become retail's EAX/ECX (2 bytes left): the pointer state carries forward |
| guard spelling: `!f()`, `== false`, nested if, int return, `unsigned char` local | 0x00271630 | plain virtual calls | none, 6 bytes each |
| **owner through `getObject()` / `Object *me = m_object`** | 0x00271630 | the pushed first argument | **exact**, without the adapter; direct read is the control (6 bytes) |
| local for relationship, count, list reference, data or capacity getter, `volatile` removed | 0x0021B310 | downstream values | none (two moved the byte to ESI) |
| **owner through `getOwner()` / local / `rot(owner)`** | 0x0021B310 | the pushed argument | **exact**; `rot(rot(owner))` also exact; `rot(object)` (parameter) and `rot(data)` (downstream) none |
| `rot()` on each of type, head, next, payload, receiver | 0x0029BDE0 | seven sites | none |
| **`rot(node->m_key)` / local `key`** | 0x0029BDE0 | the argument pushed to `isEquivalentTo` | **exact**; direct is the control (4 bytes) |
| generator: every call argument and memory-reading local initialiser, one per variant | 15 scratch/callee-saved banks | 2-24 variants each | **0x0024C420 exact** (the sibling argument `*(this-0x18)` of the same call); the others no change |
| `rot()` on head, this, member, arg, receiver and pairs | 0x0020DF90 | 8 variants | none: the only upstream construct is the first vtable call |
| `rot()`/local on the chain feeding the pushed argument | 0x00618A00 | 9 variants | the local gets retail's EDX but the scheduler sinks the load below the pushes (12 bytes); the bank's `volatile` aliases are load-bearing |

## Bodies landed

| rva | size | symbol | lever | commit |
|---|---|---|---|---|
| 0x00271630 | 70 | `AIUpdateInterface::privateMoveToObject` | `getObject()` for the pushed owner; the adapter was removed | d67be57683 |
| 0x0021B310 | 75 | `Rva21B310RelationshipCapacity::accepts` | `getOwner()` for the pushed owner; `volatile` removed | 970ee2da7b |
| 0x0029BDE0 | 98 | `Gen0029BDE0::walk` | local `key` before `isEquivalentTo` | 7332c5679e |
| 0x0024C420 | 210 | `Rva0024C420Owner::notifyNested` | local `owner` for the sibling pushed argument | 4178f79620 |
| 0x0024E990 | 163 | `Rva0024E990Owner::rva0024e990` | shared inline controlling-player accessor resolved the EBP/EBX mirror | 3ac61f1f99 |

## What it does not solve

- **Callee-saved swaps** (5 bodies, plus 3 mixed). ESI/EDI/EBX/EBP are
  chosen by a different mechanism: priority by live range across calls, with
  the adjusted-`this` and loop-pointer triggers already documented in
  `register_mirror_experiments.md`. The generic mirror toggles still leave
  these five and the mixed cases unresolved; 0x0024e990 was a target-specific
  exception, landed with an inline controlling-player accessor.
- **Stack slots** (6 plus 4 mixed) and **SIB order** (4 plus 2 mixed) are
  separate residues with their own `shape_levers.md` sections.
- **No upstream site.** 0x0020DF90 mismatches right after its first
  statement, so there is nothing before it to toggle.
- **Source-register reuse.** At 0x00618A00 ours loads `[ecx+8]` back into
  ECX and retail takes the next register. The copy form gets the register
  right, but the scheduler then moves the load below the pushes.

## Recommendations for the fleet

1. Run `tools/alloc_residue.py` on a shape-1.000 bank first. If the
   differing webs are scratch registers, look for a constant cyclic shift and
   find the **first** mismatch. Do not respell the mismatched instruction.
2. Walk back to the nearest call argument pushed from memory above that
   point, including other arguments of the same call. Toggle its spelling
   between direct (`f(p->m)`) and copied (`T v = p->m; f(v)`, or the Zero
   Hour accessor such as `getObject()`), and probe. Try each site in turn,
   nearest first. Four of the first five scratch bodies tried this way landed.
3. Remove old workarounds for the same byte, such as `volatile` members or a
   `__fastcall` table adapter, and re-probe. At 0x00271630 and 0x0021B310 the
   plain form plus the toggle was exact.
4. Do not use this on callee-saved, slot or SIB residues. Nothing in this
   session moved them.

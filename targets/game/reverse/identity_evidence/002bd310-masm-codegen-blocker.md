# 0x002BD310 GiantBirdGuardOuterState::onEnter -- MASM landing with a measured codegen blocker

Target: RVA 0x002BD310..0x002BD525, 525 bytes, name
`?onEnter@GiantBirdGuardOuterState@@UAE?AW4StateReturnType@@XZ`.
Source: `game/masm_dumps/Rva002BD310GiantBirdGuardOuterOnEnter.asm`, converted
from the gen-dump scaffold row `?d_002bd310@@YAXXZ` in
`game/gen_asm/d_002baa40.asm` (notes: gen-dump;ghidra=FUN_006bd310).

## Identity (confirmed, not address-derived)

The complete `GiantBirdGuardOuterState` vtable 0x010C7C28 is installed at
0x002C04D0; its slot 4 ILT 0x00040142 reaches this body, and
`python3 tools/ilt_oracle.py check '?onEnter@GiantBirdGuardOuterState@@UAE?AW4StateReturnType@@XZ' 0x00040142`
returns `CONFIRMED  p_false=2.61e-04  (exact)`. No other functions.csv row pins
this name. The `?j_00040142@@YAXXZ` thunk pin (0x00040142,
`game/gen_small/gthunks_071.cpp`) stays the entry for the ILT slot.

## Body and ABI (first-hand)

`ret 4` __thiscall member, SEH frame `push -1; push g_Va0101377B`. It finds the
nemesis object and its team (`TheBfmeGameLogic` +0x1C frame, `TheTeamFactory`),
reads the team position, resolves the guard area via
`AI::getAdjustedVisionRangeForObject` and `BfmeA1263::bfmeGet1263`, clamps the
chase distance to a minimum 8.0f, stamps the exit conditions
(center/radiusSqr/attackGiveUpFrame/conditionsToConsider=7), allocates an
`AIAttackState(m_machine, false, true, false, &m_exitConditions)` and enters it,
mapping STATE_CONTINUE through and collapsing everything else to STATE_SUCCESS.

## Why this lands as a MASM dump (measured)

The reconstructible C++ body (`targets/game/reverse/attempts/0x002bd310.cpp`)
compiles to exactly 525 bytes with 25 relocations and shape 1.000 (probe:
`EXACT (modulo relocation slots)`); its whole residue is one register
tie-break in the AIAttackState ctor argument materialization:

- retail: `8b 4e 1c` (mov ecx,[esi+1C]) / `8d 56 24` (lea edx,[esi+24]) /
  `52` (push edx) / `51` (push ecx)
- ours: `8b 56 1c` (mov edx,[esi+1C]) / `8d 4e 24` (lea ecx,[esi+24]) /
  `51` (push ecx) / `52` (push edx)

Four non-relocation bytes at +0x1C1 +0x1C4 +0x1C6 +0x1CD survive 80+ measured
spellings (2026-09-24..2026-10-13): direct member, this->, state->, same-class
and base-class `getMachine()` accessors, a free inline helper, ternaries,
reinterpret/static casts, int and (Bool) literals, placement new, one-line and
two-line forms, hoisted locals, upstream reorderings (giveUpFrame /
conditionsToConsider swap reallocates 35 bytes; cond7 earlier 163; no-AI-locals
or ternary 121; owner-inline 173), flag sweeps (/Oa /Ow /Ob0 /Ob2 /Os /Ot) and
micro-mutations (n1-n14, o2-o7, p1-p10, q1-q5; 2026-10-13 w_loc_machine2 /
w_loc_ec2 / w_loc_both2 land at 36/26/281 diffs). A tail-only bisect flips
machine to ECX with `getMachine()`, but any embedding containing the guardMode
prologue pins EDX/ECX. The byte-exact sibling
`GiantBirdGuardAttackAggressorState` (0x002BD6F0) reaches retail's ECX/EDX
through `new AIAttackState(getMachine(), ...)`, and flipping that landed
sibling to the direct-member form reproduces exactly these four swapped bytes
(+0x116 +0x119 +0x11B +0x122 there). Blocker class: allocator register
tie-break (two live values swapped in call-argument materialization), not
source-spellable.

The dump body is byte-identical to retail outside its relocation slots
(`tools/probe.py` prints `result   EXACT (modulo relocation slots)`); the
20-vs-25 relay-count delta is only the five SEH `__except_list` sites that the
gen dump encodes as raw zeros, exactly as in the landed 0x0048FC90 and
0x006A6080 dumps. The 20 dump relocations are the 9 calls and 11 DIR32 data
sites (ehhandler push as `g_Va0101377B`, `TheBfmeGameLogic` x3,
`TheTeamFactory`, `TheAI`, `__real@4f800000` x3, `__real@41000000` x2); all
call symbols resolve through `targets/game/reverse/symbols.csv`, and
`verify_dir32_addresses` / `verify_string_refs` / `verify_constant_refs` /
`body_guard.verify` all pass scoped to the row.

## Reopen condition

Only with a C++ reconstruction that compiles byte-identical, or a detected
caller/string that pins the name better.

## Resolved (s548, 2026-11-03)

The 4-byte ECX/EDX wall fell to the BFME 2 donor's statement order (open-bfme-2
45afcff3 Code/GameEngine/Source/GameLogic/AI/AIGuardStates.cpp), compiled with BFME 1's
flags and BFME 1's layout read off this body. Source:
game/GameEngine/Source/GameLogic/AI/GiantBirdGuardOuterStateOnEnter.cpp (exact, 525 B). The MASM
dump is deleted.

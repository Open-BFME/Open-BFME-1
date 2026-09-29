# 0x000B4020 `resolveOwnerPosition` — SOLVED (byte-exact, landed)

Landed as `game/GameEngine/Source/Common/Audio/AudioEventRTSResolveOwnerPosition.cpp`.
`tools/probe.py` reports **0 non-reloc byte differences** over all 367 retail
bytes and `add_match.py` byte-verified OK. The negative list below is kept for
the record but is now HISTORICAL: every rejected shape was rejected under a
skeleton that was itself wrong. Re-test against the landed source, not against
the shapes here.

Read `targets/game/reverse/identity_evidence/000b4020-resolve-owner-position.md`
for the identity evidence (unchanged; the identity was never the problem).

## What was actually blocking, in order of payoff

The four prior sessions all named `codegen-order/switch-tail-merge` and all
worked on the tail-merge wall. The tail merge was real, but it was a symptom.
Two independent fixes, in the order they were found:

### 1. The case tail belongs OUTSIDE the null test (biggest single win)

Retail's `je` at `+0x4d`, `+0x9f`, `+0xec` and `+0xf9` branch to **+0x69,
+0xbf, +0x124, +0x124** — that is, to *each case's own tail*, not to the
zero-fill at `+0x149`. Every earlier attempt put the tail inside
`if (object != 0) { ... }` and `break`, so each null path fell out of the
switch to the shared zero-fill. That is a different control-flow graph, and it
is why nothing downstream lined up.

Case 5 is the sharpest evidence: its *outer* null test on `Glo012F1028` and
its *inner* owner null test both land on `+0x124`. Two different tests, one
shared tail, so the tail is textually after both.

Measured: 404 B / 0 diffs 221 / shape 0.794 (banked partial) → 388 B / 0.856.

### 2. The position copy needs a reference-returning `getPosition`, in case 2 only

Retail case 2 holds both pointers in registers:

    add eax, 0x38          ; &object->m_position
    lea ecx, [esi + 0x34]  ; &this->m_position
    mov [ecx], edx ...

A pointer-returning `getPosition()` folds the `+0x38` into each load and gives
`mov ecx,[eax+0x38]; mov [esi+0x34],ecx` instead. The fix is a
**reference**-returning `getPosition()` on `Object`, which is inlined (no call,
no pin). Measured 0.856 → 0.894.

**The asymmetry that costs an hour if you miss it:** case 1 needs the *same*
`add`/`lea` shape, but its callee is the pinned retail ILT `0x0004B12D`,
spelled `?getPosition@Drawable@@QBEPBUCoord3D@@XZ` — genuinely pointer-returning.
Declaring `const Coord3D &getPosition() const` there compiles and matches bytes
in isolation, but `add_match` fails at link with `unresolved call(s)`. So:
**case 2 uses a reference (inlined), case 1 uses a pointer and dereferences**
(`m_position = *drawable->getPosition();`). Both then match.

### 3. Case 5's tail is field-wise, not an aggregate assign

`*pos = m_position` makes MSVC materialise the destination and emit
`add esi,0x34`. Retail reads `[esi+0x34]`, `[esi+0x38]`, `[esi+0x3c]` field-wise
like every other tail. Writing `pos->x = m_position.x; pos->y = ...; pos->z = ...`
matches. 0.856 → 0.856 for case 5 alone but it is required for the tail to stay
byte-identical to retail's.

## Still required (carried over from the partial, confirmed)

Distinct barrier intrinsics on the last statement before each `return`:
`_WriteBarrier()` in the ObjectID (type 2) arm, `_ReadWriteBarrier()` in the
DrawableID (type 1) arm, BOTH in the LivingWorld (type 5) arm. Retail keeps
four byte-identical 34-byte tails; MSVC 7.1 cross-jumps them. Neither intrinsic
emits an instruction or a relocation.

**New fact:** the barrier rule from the prior session ("must sit on the last
statement before the `return`") holds, but it is independent of fix #1 and they
compose. Do not test barriers against a tail-inside-the-`if` skeleton; every such
measurement is invalid.

Case 5's owner-position build needs a **non-volatile** `Coord3D` local filled
through `set(x, y, z)` and copied back. A `volatile` one forces an x87
`fld`/`fst`/`fstp` triple where retail uses plain dword moves.

## Measurement trail

| body | bytes | non-reloc diffs | byte LCS | shape |
|---|---|---|---|---|
| prior stash (all four tails merged) | 288 | 208 | 0.507 | 0.568 |
| barrier partial (banked last pass) | 404 | 221 | 0.752 | 0.794 |
| tail moved outside the null test | 388 | — | 0.856 | 0.788 |
| + case-5 field-wise tail | 388 | — | 0.856 | 0.788 |
| + case 2 reference `getPosition` | 392 | — | 0.894 | 0.864 |
| + case 1 reference `getPosition` | 392 | — | 0.921 | 0.932 |
| + case 5 tail outside its outer null test | 392 | **0** | **1.000** | **1.000** |

The final step is worth noting: it moved the byte LCS only 0.921 → 1.000 but it
is the step that made the row landable. Partial scores near 0.9 were measuring
the *wrong skeleton*, not a near miss on the right one.

## Tooling left behind

`build/scratch/score.py` — scores a source against the 367-byte retail body with
relocations masked: prints size, byte LCS score, instruction-shape score, and
instruction count. **Fault-tolerant**: a compile failure prints nothing and the
run continues, so one bad variant does not abort a 45-file sweep.

    python3 build/scratch/score.py build/scratch/gen2/*.cpp

`build/scratch/idiff.py <source>` — unified diff of the instruction stream
against retail. This is the tool that found fix #1; the byte diff could not,
because the divergence was a control-flow-graph difference that happened to
score well on LCS.

`build/scratch/ourdis.py <source>` — plain annotated disassembly (pre-existing,
from the last session).

`build/scratch/mk*.py` — variant generators. `mk5.py` builds the final landed
skeleton from `gen3/W1_drawref_agg.cpp`; the chain is
`T1_tailoutside` → `gen/U1_c5field` → `gen2/V_plain__agg` → `gen3/W1_drawref_agg`
→ `gen4/X1_c5tail_outside`.

## Settled, do not re-derive

* Owner-type constants: 0 positional, 1 DrawableID, 2 ObjectID, 5 LivingWorldID.
  Types 3 and 4 share the zero-fill tail at `+0x149`.
* Case 0's tail and the whole dispatch block are byte-exact.
* The frame is `sub esp,0xc` with the case-5 temporary at `[esp+4..0xF]`.
* The three lookup callees are the pinned ILT thunks from the brief; their
  routing is proven, so the calls are correct even though the thunks are dumps.
* `float` members, not `unsigned int`. The landed sibling
  `AudioEventRTSThinExtraCtor.cpp` uses `unsigned int` and that shape is wrong
  here: it turns case 5 into `fild` and adds a `push ebp` (measured 468 B).
  The two files legitimately disagree — each body has one identity and its own
  proven member types.
* Our object is 392 B for a 367 B retail body: 368 B of code plus a 24-byte
  jump table and alignment padding after the final `ret 8`. The jump table
  entries carry relocations and the table itself is not retail code, so this is
  not a size discrepancy to chase.

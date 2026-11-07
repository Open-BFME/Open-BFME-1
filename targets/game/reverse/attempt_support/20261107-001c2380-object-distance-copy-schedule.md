> Scratch paths under `build/wf/001c2380/` below are untracked session files and are not kept.

# 0x001C2380 `?rva001c2380Distance@Object@@QBEMPBUCoord3D@@PBV1@0@Z` (727 B): handoff

Status: still 13 non-reloc bytes. Not exact. The bank (score 0.9821) reproduces exactly as logged.

## Baseline
- Bank `targets/game/reverse/attempts/0x001c2380.cpp`, copied to `build/wf/001c2380/base.cpp`. Its include prefix was rewritten from `../../../../game/` to `../../../game/` for the new directory.
- Result: ours=727, retail=727, 11 relocs, 13 diffs, first diff at +0xA6. One relocation site drifts (the moved `fld [0.0f]`).
- Compiler: MSVC 7.1 with `/O2 /Ob2 /G6` plus the WWLib/WWMath/WWDebug includes. These are the same flags as the matched sibling 0x001C2070 (`Object_bfmeSingleBoxBoundaryDistanceSquared2D.cpp`).

## Remaining mismatch (unchanged)
```
retail                                   ours
a2 fstp [esp+28]   (delta.Y)             fstp [esp+28]
a6 fld  [0x1075350] (direction.Z = 0)    mov  ecx,[esp+28]
ac mov  ecx,[esp+28]                     fld  [0.0f]
b0 fld  [esi+8]                          mov  [esp+34],ecx
b3 mov  [esp+34],ecx                     fld  [esi+8]
```
The `fld 0.0` value is direction.Z. It stays on the x87 stack across the whole block: the two simple branches pop it, and the else branch uses it (`fmul [0]` after the Inv_Sqrt call gives inv*0). The integer copy of delta.Y into direction.Y comes directly after the `fstp` in ours. Retail puts it one slot later.

## Measured compiler behaviour (new this session)
- **Copies follow the store.** When a free register exists, the integer copy `mov r,[slot]` always comes directly after the `fstp` of the copied value. This held in every form tried:
  - copy constructor and field-wise copies
  - the copy placed after the projections (i5)
  - direction built as three scalar locals (d3)
  - copy through `const Vector3*` (u1) and `Set(const Vector3&)` (u3)
  
  In r1 and f3 the X copy uses ECX and also comes directly after `fstp [24]`, so the store-to-load latency here is 1 slot. Retail's `mov eax,[24]` is one slot late only because EAX still holds otherPosition.
- **The `fld 0` goes where the source puts it.** It moves with the direction.Z statement: before the dY chain (j4), or after projectedX (i5). It never lands between `fstp dY` and the Y copy.
- **No statement order works.** I generated all 270 dependency-respecting orders of {delta.X, delta.Y, delta.Z, dir.X, dir.Y, dir.Z = delta.Z or 0.0f} (`build/wf/001c2380/perm/`, `perm_results.txt`). None gives the retail order `fstp; fld 0; mov r,[same slot]`.
- **Matched retail bodies that show the retail order:** Line3DClass::Reset 0x951FA0, and the SwayClientUpdate and W3DShrub/TreeBuffer updateSway functions. In each one, the FP load placed between the store and the copy has a use inside the same block (a compare or `fsub`). In the target, direction.Z has no use inside the block. Script: `scratchpad/scan.py`.

## Hypotheses tested and ruled out (all left 13 diffs or were worse)
- **Control flow / lifetime:**
  - Vector3::Normalize instead of the manual Inv_Sqrt: still 13 (b1, the current best and equally good). direction.Length2: 13.
  - Copy inside the else branch: 709 B. Copy after projectedX: 36.
  - Moving the distanceSquared/radius declarations (r2-r4): 13. `Coord3D center = *position`: 69.
  - Defining delta.Z or direction.Z before the transform call (g1-g4): 13 or worse.
- **Types:**
  - Literal spellings `0`, `0.0`, `(Real)0`, `0.0f*1`: all 13.
  - direction as scalar locals: 198. POD Coord3D delta/direction with a struct copy: 541; it stores z to memory, which retail does not.
  - direction.Z taken from the BfmeZeroRange global: 743/738.
  - Building delta with the Vector3 constructor (h1, i6, m1, u2): 737; this reshuffles the else-branch x87 code.
- **Evaluation order / CSE:**
  - Recomputing direction instead of copying (s1-s4): 495+; it uses `fst`/`fstp` instead of integer copies.
  - Dot_Product operands swapped: 13. Projections taken from direction: 13.
  - Vector `-`/`-=` forms (l4, l5): 31.
  - Compound `-=` per component (l1): 13.
- **Callee visibility:** inline helpers that return delta by value (m1-m3): 13 or worse. The earlier sessions' visible transformCenter/pieceAt results still hold.
- **Compiler flags** (diagnostic only, none justified by a sibling):
  - No change, still 13: /G5, /GB, no /G, /Oa, /Ow, /Ob1, /Ox, /Gr, /QIfist, /Gs.
  - Worse: /G7 (723/635), /Os, /Oi-, /Og-, /Oy-.
- **Earlier sessions (not repeated):** 64-combination shape search, volatile spellings, global zero for delta.Z, reordered statements, constructor variants, STLport vector, and `/Op`.

## Interpretation (hypothesis, not proven)
Retail behaves as if its IR has the direction.Z definition between the delta.Y store and copies that are not tied to the store. That happens when the direction copy is a real memory copy at its own statement position, after the Z definition. VC7.1 instead copy-propagates delta.X/Y into direction in every source shape found so far, which ties the copy to the store. No natural C++ shape tried breaks that tie without changing other code.

## Best candidate
`build/wf/001c2380/b1.cpp`: the bank with `direction.Normalize()`. 727 B, 13 diffs. It is the same as the bank (`base.cpp`), and either one is fine.

# 0x003E6B80 Pathfinder::buildGroundPath (623 B): EXACT in probe

Symbol `?buildGroundPath@Pathfinder@@IAEPAVPath@@PBUCoord3D@@PAVPathfindCell@@_NH@Z`.
Best candidate: `build/wf/003e6b80/best.cpp`. `tools/probe.py ... 0x003E6B80 --size 623`
prints `result EXACT (modulo relocation slots)`, 623/623, 16 relocations.
Compiler line: `// cl: /DNDEBUG /DWIN32 /MD /EHsc`, unchanged from the bank.

## Starting point
The bank `targets/game/reverse/attempts/0x003e6b80.cpp` (score 0.9807) still reproduced
623/623 with 12 non-relocation bytes in two places:
- +0x133: cross product. Retail emits `fld [nextDir.x]; fmul st(3); fsubp st(1)`. Ours emitted
  `fxch st(2); fmul [nextDir.x]; fsubp st(2); fxch st(1)`.
- +0x1E5: final x sum. Retail emits `fld [offset.x]; fadd [adjusted.x]`. Ours had the
  operands the other way round.

## What fixed it (measured with VC7.1, single-function micro TUs plus the full TU)
MSVC 7.1 picks the order of a commutative x87 operation from **when each field symbol
is first accessed directly in the source**. A field written only through an inline member
function (`set`, `add`, `scale`) is not "seen" until the inliner runs. The operand seen
later is loaded first. Source operand order is ignored.
1. Cross product (12 -> 2 bytes). Build the summed direction as
   `Coord3D dir; dir.set(&prevDir); dir.add(&nextDir);`, not as the scalar
   `prevDir.x + nextDir.x`. Then write the product as `prevDir.x * nextDir.y - prevDir.y * nextDir.x`.
   With the scalar sum, all four operand orders gave the fxch form.
2. Final sum (2 -> 0 bytes). Build the perpendicular offset with Coord3D methods only:
   `offset.set(&dir); offset.scale(scale); offset.scale(width + width);`. Then `adjusted.x`
   is accessed directly in the turn arms before `offset.x` is, which gives retail's
   `fld offset.x; fadd adjusted.x`. `offset.scale(m_fieldA0 * 2.0f)` is also EXACT. So is a
   `Coord3D *po = &offset` pointer spelling for x only, but that is a hack and was not used.
   Writing y through a method while width is a plain local swaps the `y*width` product
   (+0x125 `fxch st(1)`). That is why both scale calls go through `scale()`.
3. Clean-up: `lenSq = dir.x*dir.x; lenSq += dir.y*dir.y;` keeps the result EXACT. A single
   expression `dir.x*dir.x + dir.y*dir.y` gives 4 bytes at +0xED. Folding the sum into `sqrt()` gives 619 B.
4. No-asm helper: the visible noinline `worldToCell` now uses `(Int)floor(x/10)` instead of
   the bank's `__asm` copy of `fast_float2long_round`. Both are EXACT, and both are
   semantically identical because the floored value is integral. The `__asm` version is
   `build/wf/003e6b80/cand2.cpp`.

## Ruled out this session (all left the result unchanged or worse)
- Scalar prevDir/nextDir locals: 613-615 B, about 375 bytes differ.
- Moving the prevDir/nextDir declarations to the loop or function scope: unchanged.
- Declaration order of dirs, adjusted and offset: unchanged.
- Computing the cross product early or into a bool: unchanged, or 625 B.
- Pointer, reference and field-pointer views of the cross operands: unchanged.
- Literals `0.0f`, `1.0f` and `0.5f` in place of the extern constants (all 7 combinations): unchanged.
- 1-12 unused locals: unchanged.
- Each commutative operand swap in offset, width and the K scaling (12 forms): unchanged.
- Field-wise forms of the tail copy, sub, add and store (32 combinations): unchanged, or 575-613 B.
- A separate delta or result object, with or without a nested scope: the frame grows to 0x58.
  VC7.1 does not pack locals from disjoint scopes.
- Moving `adjustedPosition.set` earlier: 612-620 B.

## Landing (2026-11-06)

- New TU `game/GameEngine/Source/GameLogic/AI/PathfinderBuildGroundPath.cpp` holds
  the body as `?rva003E6B80@Pathfinder@@QAEPAVPath@@PBUCoord3D@@PAVPathfindCell@@_NH@Z` (row repointed from the gen_asm dump with `--replace-rva`; the existing symbols.csv pin the matched findGroundPath caller binds, since retail's ILT contradicts every Pathfinder decoration including buildGroundPath) and
  snapLine. The 0x003E6AF0 row moved here from PathfinderLineQueries.cpp with
  `--replace-existing`; its definition there was removed. That TU still verifies
  5/5, and nothing in it calls snapLine.
- Measured: with snapLine/worldToCell only declared, buildGroundPath is 623 B
  with 85 differing bytes, so the visible never-inlined bodies are load-bearing.
- worldToCell is the project's accepted per-TU `inline __declspec(noinline)`
  copy, with the authentic REAL_TO_INT_FLOOR / fast_float2long_round body (as
  in PathfinderRva003D84A0.cpp and six other pathfinder TUs). The emitted
  COMDAT probes EXACT against 0x003D7EC0 (156 B), so it is retail's copy, not a
  loser. The scratch `floor()` spelling was not landed: its COMDAT would differ.
- Coord3D comes from WWMath `coord.h` (Zero Hour BaseType.h set/add/sub/scale)
  instead of a private copy.
- The width is spelled `TheAI->getAiData()->m_formationColumnWidth` (TAiData at
  AI+0x14, FormationColumnWidth at +0xA0), per
  `targets/game/reverse/identity_evidence/0x003e6b80-retry-layout-and-abi.md`.
  The bytes are unchanged.
- The 0x01075350 zero reference uses the data ledger's `g_rva01075350` (DIR32
  gate).
- Verified: add_match ./build.sh 2/2 rows and 6 DIR32 references; probe EXACT
  for buildGroundPath 623/623, snapLine 110/110 and worldToCell 156/156.

# 0x00740F60 W3DView::setupWaypointPath: EXACT (599/599)

Best source: `build/wf/00740f60/best.cpp`. It defines `?setupWaypointPath@W3DView@@AAEXH_NMM@Z`.
`tools/probe.py ... 0x00740F60 --size 599` reports `result EXACT (modulo relocation slots)`.
The build used the bank's flags unchanged: `// cl: /DNDEBUG /MD /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib`.

## Starting point
The bank `targets/game/reverse/attempts/0x00740f60.cpp` reproduced as logged: 599/599 bytes with 19 non-reloc diffs. Three spots differed:
1. +0xEA: the `numWaypoints` load and the `cameraAngle[1]` fstp were swapped.
2. +0x186: in the third unrolled smoothing iteration, the operand order of fld and fadd was swapped.
3. +0x1E8: `push 0` (the getGroundHeight normal argument) came after the finalPos.x store instead of before it.

## Changes that reached EXACT (three independent source facts)
1. **startAngles uses begin/end pointers.** It became `Real *begin = cameraAngle; Real *end = begin + numWaypoints + 2; begin[1] = angle; end[-1] = end[-2]; begin[0] = begin[1];`. This fixes spot 1 and keeps retail's dead `lea [edi+eax*4+0x1470]`. The old `Real *p = &cameraAngle[n+2]` form and the variants nlocal, pafter, const-ref arg, nested padEnds, `*(end-1)` with a plain array, and a one-trip loop all kept the swap.
2. **finalPos is `Vector3 finalPos(last.x, last.y, last.z)`.** This fixes spot 3. It keeps a 12-byte frame, and VC7.1 drops the z store. Other forms tested:
   - A Coord3D with x/y assignment, any statement order, a pointer form, or a direct index: push stayed late.
   - `Vector2 finalPos(x,y)` or `Set`: push order fixed, but the frame was 8 bytes instead of 0xC.
   - Vector3 with X/Y assignment only: push stayed late.
   - `Vector3(x, y, 0)`: also exact, but `last.z` is the natural copy.
3. **The segment-length padding is `waySegLength[0] = 0; waySegLength[n] = waySegLength[0]; waySegLength[n+1] = 0;`, with the ZH-literal smoothing body `cameraAngle[i] = (cameraAngle[i] + cameraAngle[i-1]) / 2`.** This fixes spot 2. The unroll operand order (retail P K K P per iteration) proved sensitive to the IR of the earlier zero block:
   - Plain zeroing with the plain body gave K K P P and +1 byte.
   - Plain zeroing with a `Real &a` body gave P K P P.
   - Zeroing through a `seg` pointer gave the retail loop but swapped `mov [0],ebx` and the `n` load (8 diffs).
   - Only the `[n] = [0]` copy gave both orders correctly. The compiler forwards the constant, so the stored value is still `ebx`.

## Ruled out (measured; spot 2 unchanged unless noted)
- **Compiler flags:** /EHsc, /DWIN32 /D_WINDOWS, /G6, /Ob1, /Ox, /Og, /GX- were inert. /G7, /Op, /O1, /Oy- and /arch:SSE broke the body.
- **Smoothing body spellings** (about 25): swap, refs, pointers, sum/prev/cur temps, `*0.5f`, `/2.0f`, `(Real)2`, compound forms, a static-inline `averageAngle` helper (by value or const-ref), and an extern or static const half.
- **Loop forms:** `--i`, a `j` index, a scoped `i`, while loops, and `>=2` or `!=1` (the last two changed size). A member-function smoothing helper produced 475 B.
- **Upstream neutral knobs:** first-loop spelling, configure/`Int i` placement, and refs in the totalDistance accumulation. Of about 1,000 combinations swept (dirs `m/ q/ r/ w/ y/ zz/`), none reached the retail order with the Z block correct before the `[n] = [0]` form.

## Donor
BFME 2 at 2bac16a6 has no setupWaypointPath body. `W3DViewMoveAlongWaypointPath.cpp` and `Rva0008990CArrayOwner.h` only confirm the +0x1468 angle, +0x1864 length and +0x2070 count layout. The Zero Hour GeneralsMD `W3DView.cpp` setupWaypointPath served as the semantic guide.

## Landing notes (read-only checks; not landed)
- **(a)** `tools/ilt_oracle.py check '?setupWaypointPath@W3DView@@AAEXH_NMM@Z' 0x00740F60` returns CONFIRMED (p_false 3.26e-04). The name can be used as is.
- **(b) Emitted COMDAT copies, each probed EXACT against its own row:**
  - `?Sqrt@WWMath@@SAMM@Z` at 0x001EF4C0
  - `??0Vector2@@QAE@MM@Z` at 0x0016A160
  - `?Length2@Vector2@@QBEMXZ` at 0x001A0E90
  - `??0Vector3@@QAE@MMM@Z` at 0x000693F0
  - `?Length@Vector2@@QBEMXZ` at 0x00704A60

  None of them is a link loser. `?startAngles@Rva00740440@@QAEXM@Z` is also emitted as a COMDAT and has no ledger row. It is an inline class-body member, and `find_declared_unmatched.py` flags only setupWaypointPath. Mark it `present-unmatched` or keep it inline-only when landing.
- **(c) Globals:**
  - `TheTerrainLogic` at 0x012EF4CC is referenced as `?TheTerrainLogic@@3PAURva003FD060TerrainLogic@@A`, which is recorded in `dir32_addresses.csv`.
  - The 0.5f compiler literal resolves to `__real@3f000000` at 0x0107533C (`data_rows.csv` row `?g_rva0107533C@@3MB`). It is a literal, so no extern is needed.
  - Out-of-line calls are `Rva00740440::rva00740440` (ILT 0x20266 to 0x740440) and `Rva0045A000::sample` (ILT 0x46FA1 to 0x459B10). Both have matched rows.
- **(d) Home TU:** a new `game/GameEngineDevice/Source/W3DDevice/GameClient/W3DViewSetupWaypointPathBfme.cpp`, following the sibling `W3DView*Bfme.cpp` naming. The other option is `Rva00740440CameraPathAngles.cpp`, which already holds the sole callee. That TU has its own class view (`Rva00740AE0Base` base, `m_cameraAngles`), so reconcile the two views of the +0x280 record before co-locating. Replace the gen-dump row `?d_00740f60@@YAXXZ` with `--replace-rva 0x00740F60`.

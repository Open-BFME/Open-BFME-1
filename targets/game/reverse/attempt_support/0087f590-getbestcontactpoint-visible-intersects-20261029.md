# 0x0087F590 GeometryInfo::getBestContactPoint: exact only beside a visible bfmeIntersects

Session 479, model claude-opus-5-5, 2026-10-29. Bank: targets/game/reverse/attempts/0x0087f590.cpp
(one combined TU holding both bodies; compile flags `/O2 /Ob2 /G6 /DNDEBUG /MD /EHs-c-`).

## Donor

BFME 2 `Code/GameEngine/Source/Common/System/GeometryInfoCollidesWith.cpp` (submodule rev
beed8a16) keeps the transform, CollidesWith and getBestContactPoint in one retail unit and is
byte-matched in BFME 2 (0x006BEF80, 1082 B). Same GeometryInfo layout as BFME 1 (shapes
+0x2C/+0x30 stride 0x24, contacts +0x38 stride 0x10, preferred +0x44, innermost +0x50).
Carried over: the hand-written contact vector view (inline begin/end/size/operator[]), the
per-arm label reference + record pointer, `contactCopy`, the `ContactPoint` copy for the
interpolation arm.

## BFME 1 differences (from retail 0x0087F590, not the donor)

- Trace: `g_bfmeDockingTraceActive` + `TheCRCParameterCheck` sink + `_bfmeRetailCritterDesyncLog`
  (ILT 0x0003A17A), same argument order as the donor.
- Interpolation factor is `t = (float)((seed >> 8) & 255); t *= 1/255.0f` (retail multiplies by
  the 0x0107C64C constant; a one-expression product schedules `fmul` before a field load).
- getMaxHeightAbovePosition is re-called at every use (14 calls); no cached height.
- The shape fallback writes only x and y; every clamp tail is `if (z > max) z = max; else if
  (z < max * 0.1f) z = max * 0.1f; return true;` (an early `return` inverts the block order).
- Collide test: `bfmeIntersects(origin 0x0130E908, 0, g_bfmeStaticAAO, pos, 0)`.

## Result

- With bfmeIntersects only declared: 1066/1066 B, 35 relocs, 16 bytes differ at +0x2EE: retail
  loads all three coordinates of the search candidate before storing them; ours stores x first.
  About 40 spellings of that copy were inert (field order, helpers, copy ctors, temporaries,
  flags /G5 /GB /G7, static/defined origin, visible getMaxHeightAbovePosition).
- With a visible non-capturing definition of bfmeIntersects earlier in the TU (even a stub),
  getBestContactPoint is EXACT. With the real bfmeIntersects body (from
  attempt_history/0x0087f2f0, `BfmeShapeName` string member whose dtor calls
  `?releaseBuffer@?$StringBase@D@@AAEXXZ` through a member-pointer union) it is EXACT too.
- That bfmeIntersects body is still 480/480 B with its known 6-byte reload swap at +0x1BD
  (identity_evidence/0087f2f0-masm-codegen-blocker.md); the row stays the MASM dump.
  Also inert here: the donor's `found = overlap(a, b, found)` forceinline dispatch, a visible
  forceinline transform 0x0087E900.

## Next step

Solve the 6-byte +0x1BD tie of bfmeIntersects inside this combined TU; then both rows
(1066 + 480 B) land together from one new source (getBestContactPoint is the link-queue #28
unresolved name too). Origin 0x0130E908 has no recorded dir32 name yet.

## Landed (same session)

Making `BfmeObjF0::set` 0x0087F0F0 and the transform 0x0087E900 visible in the same TU closed the
bfmeIntersects tie as well; all four bodies landed from
game/GameEngine/Source/Common/System/GeometryInfoCollidesWith.cpp. Spelling changes from the bank,
all forced by ledger names: the shape and position record types are `BfmeShapeF0`/`BfmePosF0`
because the set row is `?set@BfmeObjF0@@QAEPAV1@PBUBfmePosF0@@PBUBfmeShapeF0@@H@Z`; the trace
logger is `_bfmeRetailCritterDesyncLog`, the ledger row at 0x00065C80 that ILT 0x0003A17A reaches.

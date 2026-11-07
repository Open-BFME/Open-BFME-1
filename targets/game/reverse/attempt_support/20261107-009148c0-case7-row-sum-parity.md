# 0x009148C0 PointGroupClass vertex-location fill (9232 B): handoff 2026-11-07

> The best candidate (`build/wf/009148c0/best.cpp`, untracked scratch) is now banked as `targets/game/reverse/attempts/0x009148c0.cpp`. Other `build/wf/009148c0/` paths below are scratch and are not kept.

Symbol: `?rva009148C0@PointGroupClass@@QAEXPAVVector3@@PAMPAEH@Z`.
Bank: `targets/game/reverse/attempts/0x009148c0.cpp`. It still reproduces at
9232/9232 with 42 non-reloc diffs, first at +6431, as logged.
New best: `build/wf/009148c0/best.cpp` at **32 diffs**. It is clean C++ with no
dummies and the same `// cl:` line as the bank (`/O2 /DNDEBUG /MD` + WWVegas includes).
The only change from the bank is the case 7 transform result form (mode `AIII`):

    Vector4 result;  result = view * vertex_loc[0];   // v0: declare, then assign
    Vector4 result1 = view * vertex_loc[1];            // v1..v3: each initialises its own result
    Vector4 result2 = view * vertex_loc[2];
    Vector4 result3 = view * vertex_loc[3];

These other clean spellings also reach 32: `IAII`/`IIAI`/`IIIA` with
`orientedVecX` and `orientedVecY` both declared first and then assigned.
`I` initialises a vertex's own result and `A` assigns the shared `result`.

## Remaining mismatch (32 B, case 7 view transform only)

The bytes match apart from the operand order of the reassociated x87 row sums
(`view[r][c] * vertex[c]`). Each row is emitted as a rotation of X, Y and Z:

    retail   v0 ZYX/ZYX/ZYX  v1 YXZ/YXZ/YXZ  v2 row0 ZYX  v3 XZY/XYZ/XYZ
    best     v0 XZY/XZY/XZY  v1 YXZ/YZX/YZX  v2 row0 XZY  v3 XZY/XYZ/XYZ
    +191c retail: fld [esp+58]; fmul [esi-8] | ours: fld [esp+50]; fmul [esi-10]   (v0 row0..2)
    +19a8 retail: fld [esp+60]; fmul [esi-4] | ours: fld [esp+68]; fmul [esi+4]    (v1 row1,2)
    +19e9 retail: fld [esp+58]; fmul [esi+10]| ours: fld [esp+50]; fmul [esi+8]    (v2 row0)

## Mechanism findings (measured)

* Source term order has no effect. With the transform written out as explicit
  per-row float sums, ZYX and XYZ source orders give identical code
  (`ex_*_nat` = `ex_*_zyx`). VC7.1 canonicalises these sums itself.
* v0's order is a **parity of the number of inline-assignment temporaries in
  the case 7 loop**. Let T = number of `A` modes among v1..v3, plus 1 for
  `orientedVecX` assigned and 1 for `orientedVecY` assigned. With v0 `I`, even T
  gives YXZ and odd T gives XZY. With v0 `A` it is the reverse. The full 64-way
  factorial (g64.py, `g_*` in trials.log) never gives v0 = ZYX (retail).
* Initialised dead ints at function top (k = 0..24) never move v0. They move
  v1 between YXZ/XYZ, YXZ/YZX and ZXY/ZYX. In a case-7-only micro TU
  (`m/k*.cpp`) the pattern repeats every 32 ints.
* `Vector3 &vN = vertex_loc[N]` aliases are the only spelling that gave v0 =
  ZYX (masks x110). They move the ground cursor bias to `lea esi,[eax+0x14]`
  and shift every store (100+ diffs). Rejected.
* The BFME1 WorldBuilder twin (WB VA 0x70A2A0) has asserts in Vector3
  operator* (NaN checks) and its ground cursor bias is 0x14. Its row pattern
  `YXZ YXZ YXZ XYZ XYZ XYZ ? YZX YZX XZY XYZ XYZ` is not directly comparable
  with the game build.

## Ruled out this session (do not repeat)

* Get_Flag defined out of line before the body (pointgr.cpp spelling).
  `Get_Flag(BILLBOARD) == 0`. A named `angle` float. `(D3DXMATRIX*)&rotMat`.
  All four are inert (42).
* Flags `/G5`, `/G6`: inert. `/G7` and `/Op`: break the body.
  `/G6` is used by sibling WW3D2 TUs, but no PointGroupClass sibling uses it.
  The PointGroupClass siblings are `/DNDEBUG /MD`.
* Matrix3D view with the Matrix3D Get_Transform overload: the frame shrinks (9184 B).
* ZH Vector3-operator forms in case 0 and case 8 (`*point_loc + scaled_offset[k]`):
  9520 and 9424 B. `DefaultPointSize * table` in case 0 and case 4: inert.
  `*=` scaling: breaks.
* Case 7 corners spelled inline in the ZH way (with no dx0..dy1 names): 9248 B or 2395 diffs.
  `point_loc->X + dx0` operand order: inert.
* Dead inline temps (diagnostic only):
  * `Vector3 = X + Y` before the loop: 90, the same at any count N≥1.
  * Inside the loop: 40, and v0 does not change.
  * A dead `view * GroundMultiplierX` or `rotMat * GroundMultiplierY`: 82.
  * Dead `Vector4` or `Matrix4` locals: inert.
* Result write-back as Set/ctor, Transform_Vector, rc (result at case scope) x k
  (an earlier session in this directory): 59-172.

## Next hypotheses (untested)

1. Combine the T-parity knob with a second optimizer-temp knob outside case 7.
   An example is an inline call or temporary in another case that is
   byte-neutral there, such as a `Vector3 scaled_offset` copy versus an
   element-wise write. The aim is to move v0 to its third state (ZYX) with no
   aliasing.
2. A source-level difference in how `view` is filled. One option is
   `Matrix4 view = ...` from a by-value Get_Transform that returns Matrix4.
   Another is `view = DX8Wrapper::Get_Transform(...)`. Either changes the
   temporaries of the transposed copy without changing its stores.

Scripts: `par.py` (parallel probe and row-pattern), `g64.py` (result mode x
ox/oy factorial), `alg.py` (alias masks), `micro.py` (micro-TU disassembly),
`rowsum.py` (row-order pattern). The trial log is `trials.log`.
model=claude-opus-5-5, t≈95min.

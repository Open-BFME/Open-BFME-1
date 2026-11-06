# 0x001C1820 Object::getSingleLogicalBonePositionOnTurret (1008 B): EXACT

Symbol: `?getSingleLogicalBonePositionOnTurret@Object@@QBE_NW4WhichTurretType@@PBDPAUCoord3D@@PAVMatrix3D@@@Z`
Extent: ret 0x10 at +0x3ED, so 1008 B (unchanged from earlier sessions).
Context: the body goes into a scratch copy of `game/GameEngine/Source/GameLogic/Object/Object.cpp`
at the `// byte-exact reconstruction: ...OnTurretThunk.cpp` marker, right before
`getMultiLogicalBonePosition`. The TU's own `// cl:` line is unchanged
(`/DNDEBUG /DWIN32 /MD /EHsc` + includes; the build adds `-O2 -GR- -EHsc-`).

- Best candidate (full TU): `build/wf/0x001c1820/best.cpp`. Its body alone is in `build/wf/0x001c1820/best_body.cpp.txt`.
- Probe: `size ours=1008 retail=1008 relocs=20`, `result EXACT (modulo relocation slots)`.
- Baseline bank (`targets/game/reverse/attempts/0x001c1820.cpp`) still reproduces as logged: 1008 B, 8 non-reloc
  bytes at +0x1A7..+0x1AF.

## Cause of the residue
The residue was in the second `turnAdjustment.Translate(-x,-y,-z)`, row 0. Retail evaluates `R02(reg)*(-z)` first
(`fld st(2); fmul st(2); fld [esp+3c]; fmul st(2)`). The bank evaluated `R01(mem)*(-y)` first. MSVC 7.1 orders
the commutative terms by itself, so changing the order in the source has no effect (earlier sessions tested 97 orderings plus
all association variants). What decides the order is **how many local symbols the function has**, as in
`docs/shape_levers.md` (the Transform_Vector entry for 0x0071D5E0).

Diagnostic (dummy `Real dN = 0.0f; (void)dN;` locals, not for landing): +1..+4 gave 8 diffs, **+5 and +6 gave EXACT**,
and +7..+16 gave 8 diffs. The local's type (Int/Real) made no difference, and neither did its position (start or end of the function). An uninitialized
local whose address is taken also counts.

Measured deltas from legitimate spellings, each found by adding dummies until the result became EXACT:
- `Real worldX/Y/Z = tmp.X/Y/Z` feeding `worldPos`: +3
- `Int numBones = ...getPristineBonePositions(...)`: +1
- named `const BFMEDrawableBoneQuery *boneQuery` view pointer: +1
- named `BfmeTurretDrawableView *view` pointer: +1
- named `Real boneX/Y/Z` feeding the Vector3 constructor: 0
- dropping the named `bonePositionVector` (using a temporary instead): -1

These combinations of legitimate spellings came out EXACT: W3+N+A (+5), W3+N+B (+5), W3+A+B (+5), and W3+N+A+B (+6, chosen).
W3 alone, W3+A and W3+B (+4 or less) stay at 8 diffs.

## Ruled out this session (in addition to the earlier log entries)
- Flags /G5 /G6 /G7 /GB /Ob1 /QIfist /Ox /Og /Ot /Oi: no effect (8). /Op gave 1274 B and /Oy- gave 848 B.
- Named negated locals in all 6 declaration orders: 10..483 diffs.
- In_Place_Pre_Rotate_Z(s,c) overload (sinf/cosf, WWMath, named c/s): 994..1032 B.
- Moving the body to the end of the TU, or adding unrelated declarations before it: no effect (8).
- Coord3D::set, Get_Translation(&tmp), and the Vector3 temporary for the bone, in every combination: 8.
  Get_X/Y/Z_Translation without tmp: 1006 B. Turret x/y/z as named Reals: 1010 B.

Still to do before landing: put the body into Object.cpp, run `add_match --replace-existing` (the row currently points
at the naked `ObjectGetSingleLogicalBonePositionOnTurretThunk.cpp` lift), and pass the normal build gate. Then add a
shape_levers note: "locals count +5/+6 flips the Translate row-0 product order".

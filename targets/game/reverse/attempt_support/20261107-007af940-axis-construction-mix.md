# 0x007AF940 projectRangesRva007AF940: EXACT (probe), 2026-11-07

Symbol: `?projectRangesRva007AF940@@YAXABVVector3@@0MMMMAAVVector2@@1@Z`, 282 bytes
(retail `ret` at +0x119, INT3 at +0x11A). Best source:
`build/wf/007af940/best.cpp` (probe: `result EXACT (modulo relocation slots)`,
282/282, 6 relocs). The same TU still reproduces minMax4 0x007AF710 (156 B) and
decalAxes 0x007AF7E0 (276 B) EXACT.

Compiler settings: unchanged from the bank / landed
`W3DProjectedShadowDecalHelpers.cpp` (`/DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc`,
WWMath/WWLib project headers, probe default /O2). No flag change.

## Baseline

Bank `targets/game/reverse/attempts/0x007af940.cpp` reproduced as logged:
282/282, 6 non-reloc bytes at +0xD8 (retail `lea ecx,[esp+0x10]` then
`fstp [esp+0x20]` (c3.Y); bank emits them reversed).

## The lever (measured)

Spell the four scaled axis vectors in two ways. With all four as
`Vector3 v = s * axis;` (operator*(float,const Vector3&), temp + copy) the
residue stays. With all four built directly by the component constructor
(`Vector3 v(axis.X * (s), axis.Y * (s), 0.0f or axis.Z * (s))`, the form the
BFME 2 donor `W3DProjectedShadowDecalHelpers.cpp` uses for its 0x00108FBD body)
the first call comes out right, but the second call's argument loads reorder
(14 bytes off at +0xF0). Full 4^4 sweep over {operator, component+0.0f,
component scalar-first, component with Z} for a0/a1/b0/b1 (256 trials):

| operator-form count | result |
|---|---|
| 4 | 6 bytes (+0xD8 swap; the bank) |
| 3 or 2 | EXACT (every placement, every component spelling: 66 trials) |
| 1 | 18 bytes (+0xEC) |
| 0 | 14 bytes (+0xF0) |

Uniform spellings (`axis * s`, `Set(...)`, copy then `*=`) do not match either
(65, 14, 288 B). The candidate uses a0/b0 as operator form and a1/b1 as
component constructors computing Z (`axis.Z * (s)`), so the arithmetic, including
the dead Z, is the same as the operator form. Cause hypothesis (not proven): the
operator temporaries change the IR tuple count/numbering, which the x87 list
scheduler uses as a tie-break between the independent `lea` and `fstp`.
This is not a semantic claim about EA's spelling; the mix is a measured
codegen lever only.

## Ruled out this session (all inert at 6 bytes unless noted)

- Flags: /Ox /Ob1 /Ob2 /GB /G5 /G7 /Ot /Og /GF /Gy /Oi- /GR- /Gs (6); /Oa /Ow
  (27); /O1 /Os /Oy- /Op /arch:SSE(2) (size changes). None is justified by a sibling anyway.
- TU order minMax4 before decalAxes (retail emission order): 6.
- Scalar float x3/y3 (or x3 only) for the last corner: 270 B.
- `float y3 = c3.Y` extraction: 6. Inline `b1.Y + a0.Y` / `(b1 + a0).Y` / `(b1 + a0).X`
  in a call: 280/283/282 B with 129-159 bytes.
- Prior sessions' families (see re_attempts.log): corner/scale orders, result
  locals, pointer/reference outputs, real caller bank, inline/noinline, const,
  += subsets, placement, derived result views: all inert.

## Retail image observation

21 `lea ecx,[esp+x]; fstp [esp+y]; call` sites vs 9 `fstp; lea; call` sites in
`.text`; matched lea-first examples include W3DView::cameraModFinalLookToward
(+0x19E) and RTS3DScene::castRay (+0x2CB).

## Landing notes (read-only checks; not landed)

a. `tools/ilt_oracle.py check` -> UNTESTABLE (static, not a thunk target). No
   ILT pin needed; the private register ABI (ECX/EAX/EDI/ESI + 4 stack floats,
   caller pops) still needs a same-TU caller. The landed
   `game/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DProjectedShadowDecalHelpers.cpp`
   already carries the identical `exp7AF940Caller` emission anchor and the
   bank's projectRanges body; prior verdicts flagged that synthetic caller as
   the policy blocker (`blocker=callee/private-ABI-real-caller`). Whoever lands
   must decide whether that anchor is acceptable (it already ships for the two
   matched helper rows in that file).
b. Helpers with their own rows: minMax4 0x007AF710 (156 B) and decalAxes
   0x007AF7E0 (276 B) are both matched in that same file, and the candidate TU
   emits both EXACT; they are the authentic home copies, no COMDAT loser.
c. Globals: the only data reference is the 0.5f constant at VA 0x0107533C
   (4 relocs: +0x09, +0x22, +0x41, +0x5A), emitted from the `0.5f` literal
   (`__real@3f000000`). Recorded as `?g_rva0107533C@@3MB` in data_rows.csv and
   as several names (e.g. `?g_bfmeK1253@@3MB`) in dir32_addresses.csv; the
   other two relocs are the two calls to 0x007AF710.
d. Home TU: `game/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DProjectedShadowDecalHelpers.cpp`
   (holds both helpers; replace its projectRanges body with the one in
   best.cpp), landing with `--replace-rva 0x007AF940` over the
   `?d_007af940@@YAXXZ` gen_asm row.

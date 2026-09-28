# 0x001F38A0 ?update@BridgeBehavior@@UAE?AW4UpdateSleepTime@@XZ — frame slot map

Measured 2026-09-28 from the retail body (721 B, `python3 tools/dis_retail.py
0x001F38A0 721`) and from a `/FAsc` listing of the banked stash
`targets/game/reverse/attempts/0x001f38a0.cpp` (read the `_name$ = -NN` table at
the top of the function's COMDAT).

Retail allocates **9** four-byte slots; the stash compiles to **8**. Retail's
`sub esp, 0x30` against our `sub esp, 0x2c` is exactly that one missing slot,
and every one of the 27 differing bytes is a stack displacement shifted by 4.

## Retail slots (dword index from the first local, `sub esp, 0x30` + 4 pushes)

| slot | retail raw `esp+` | object | how it is witnessed |
|------|-------------------|--------|---------------------|
| +0   | 0x10 | `_us` | `+0x44 mov [esp+0x10],eax` after `mov eax,[ebp-8]` |
| +1   | 0x14 | `_boneName` | `+0x32 mov [esp+0x14],esi`; tested at `+0xeb` |
| +2   | 0x18 | `_bridge` | `+0x5e mov [esp+0x18],edi` (findBridgeAt result) |
| +3   | 0x1c | `_bridgeTemplate` | zeroed at `+0x66`, result stored `+0xa4` |
| +4   | 0x20 | `_bridgeInfo` | zeroed at `+0x62`, `+0x76 mov [esp+0x24],eax` (depth 1) |
| +5   | 0x24 | `_this` | `+0x28 mov [esp+0x24],ebp` |
| +6   | 0x28 | `_bridgeTemplateName` | `+0x6c lea ecx,[esp+0x28]` (getString dest) |
| +7   | 0x2c | `$T5274` **and** `_deathTime` | `+0x84 mov [esp+0x30],esp` (depth 1) / `+0xc0 mov [esp+0x2c],eax` |
| +8   | 0x30 | `_modData` | `+0x50 mov [esp+0x34],ebx` (depth 1) / `+0x171 mov ebx,[esp+0x30]` |
| +9   | 0x34 | `_pos` (12 B) | `+0x124 lea edx,[esp+0x34]`, stores at 0x34/0x38/0x3c |
| —    | 0x40 | `__$EHRec$` (12 B) | `+0x22c mov ecx,[esp+0x40]`, `-1` at `+0x21f` |

## Stash slots (same ordering of objects, two pairs collapsed)

```
_us = -56   _boneName = -52   _bridge = -48
$T5274 = -44   _bridgeTemplate = -44      <- retail keeps these apart
_bridgeInfo = -40   _this = -36
_deathTime = -32    _bridgeTemplateName = -32   <- retail keeps these apart
_modData = -28   _pos = -24 (12 B)   __$EHRec$ = -12 (12 B)
```

Two overlaps, not one: `$T5274` sits on `_bridgeTemplate`, and `_deathTime`
sits on `_bridgeTemplateName`. Retail's `$T5274` (the by-value `AsciiString`
argument the unwind funclet must destroy) is on the *same* slot as
`_deathTime`, at +7.

## What has been ruled out (measured, not reasoned)

* Declaration order: a 360-permutation sweep over the six top-of-block
  declarations (`boneName`, `us`, `modData`, `bridge`, `bridgeInfo`,
  `bridgeTemplate`, respecting the `us` -> `bridge` data dependency) produced
  **zero** `sub esp, 0x30` frames. Every permutation compiles to 0x2c. This
  matches docs/shape_levers.md "A run of locals on the wrong slots": order does
  not decide the frame, the object count does.
* Hoisting `bridgeTemplateName` to the top of the `if(m_deathFrame)` block DOES
  reach `sub esp, 0x30` and DOES produce retail's exact 11-slot table
  (`_us=-60 _boneName=-56 _bridge=-52 _bridgeTemplate=-48 _bridgeInfo=-44
  _this=-40 _bridgeTemplateName=-36 _deathTime=-32 $T5274=-32 _modData=-28
  _pos=-24 __$EHRec$=-12`), but the body grows to 766 B / 567 diffs: the
  function-scope `AsciiString` gains a second destructor call and a
  `__$EHRec$` state bump that retail does not have. Adding an explicit
  `.~AsciiString()` to cancel it (variant vB) still gives 766 B / 563 diffs.
  **The slot map is reachable; the lifetime is not.**
* `boneName` per-iteration in either loop: compile error (the OCL loop's
  `boneName` is out of scope), or a different 27-diff body.
* `findBridge` by `const AsciiString&` (p1) drops a relocation and diverges
  (720 B, 519 diffs) — retail really does pass by value.
* `pos.set(getObject()->m_position)` (h1) and `pos=getObject()->m_position`
  (h2): h1 keeps 27 diffs, h2 grows to 732 B. Neither moves the frame.
* `findBridgeAt(&us->getPosition())` with a reference-returning accessor (r1):
  27 diffs, unchanged.
* Declaring `deathTime` and *initialising* it before the `if(bridge)` branch
  (u1, u2) reaches `sub esp, 0x30` but moves the `getFrame()` load above the
  branch: 730 B / 540 diffs. Retail reads `m_deathFrame` at `+0x1c` (before the
  branch) but reads `TheBfmeGameLogic` at `+0xb2` (after it), so `deathTime` is
  genuinely born after the branch. The frame is reachable that way; the code
  order is not.
* Giving `Bridge` a real `AsciiString getBridgeTemplateName() const` member and
  copy-initialising the name from it (v1) instead of the `Rva000EE6D0
  StringAccessor` cast: 27 diffs, frame 0x2c. The accessor's identity is not
  the frame lever. Declaring the name empty first and assigning (v2) grows the
  body to 762 B.
* Passing a *copy* of the name to `findBridge` so the `$T` outlives the local
  (t2), and passing a constructed temporary (t1): 27 and 485 diffs.
* A `Coord3D::set()` inlined accessor (h1): 27 diffs. Plain struct assignment
  (h2): 732 B.
* `tools/eh_levers.py` on the stash (6 choices, 128 combinations) through
  `tools/shape_search.py --max-trials 24`: 9 trials, no improving output. The
  EH family does not move the frame.
* `tools/shape_family_levers.py --families frame` offers exactly one choice and
  it targets the `StringBase<char>::compare` helper, not `update`.
* Splitting `deathTime` into `now` and `deathTime` locals (q2): 27 diffs,
  unchanged. Caching `m_deathFrame` (q1): 730 B, 474 diffs.
* Nesting the `if(bridge)` body, the `if(m_deathFrame)` body, the loop pair, or
  the `deathTime` computation each in its own block (g01-g08, s1, s4, m2, x1,
  w1, n3): all 27 diffs, frame 0x2c.
* Moving `deathTime` before the `if(bridge)` block (x1, n3, w1) or splitting its
  declaration from its assignment (w1, g02, g08): still merged with
  `_bridgeTemplateName` at -32.
* `bridgeInfo` / `bridgeTemplate` zero-initialisation moved inside the branch
  (m1, m2): retail does zero both before the branch (`+0x62`, `+0x66`), so
  this is wrong; m1 gives 29 diffs, m2 gives 27.

## The remaining question

Retail has one more live object than the stash. Given the Zero Hour twin
(`inputs/reference/CnC_Generals_Zero_Hour/Generals/Code/GameEngine/Source/
GameLogic/Object/Behavior/BridgeBehavior.cpp:706-830`) spells the body with
exactly the stash's declarations, the extra object is a **BFME-only**
difference: the `_bridgeTemplateName` local in retail has a scope the stash's
copy-init does not give it (so it does not die before `deathTime` is born),
while its destructor still fires inside the branch at `+0xad`. The next
worker should look for a BFME source form that keeps that lifetime without the
second destructor call — for example a `Bridge::getBridgeTemplateName()` that
returns by value into a caller-provided slot plus a `const&` overload, or a
`StringBase` whose copy assignment does not itself allocate a slot.

## Two facts that narrow it further

1. **The frame size and the code order pull in opposite directions.** Both
   source forms that reach `sub esp, 0x30` do it by *birthing* an object
   before the `if(bridge)` branch — hoisting the whole `AsciiString`
   (`bridgeTemplateName` at the top of the `if(m_deathFrame)` block), or
   initialising `deathTime` before the branch. Retail's code order is fixed
   against both: `m_deathFrame` is read at `+0x1c`, *before* the branch, but
   `TheBfmeGameLogic` is read at `+0xb2`, *after* it, and the `releaseBuffer`
   that destroys the name is at `+0xad`, also after. So retail's frame is 0x30
   with the name dying inside the branch and `deathTime` born after it. The
   compiler kept them apart anyway. That is the one behaviour the source form
   has to reproduce without moving a single instruction.
2. **The Zero Hour twin will not close it.** The ZH body is the same
   declarations, and the ZH build has no `FXList::bfmeIsBlocked` fan-out, so
   its frame is a different question. Porting the ZH text verbatim is what the
   stash already is.

## Files for the next worker

* Stash: `targets/game/reverse/attempts/0x001f38a0.cpp` (721 B, 27 diffs, shape
  1.000, score 0.9626).
* The `/FAsc` slot-table reader used here is
  `tools/build.py:compiler_command` plus a `-FAsc -Fabuild/slot.cod` compile;
  the table is the `_name$ = -NN` block immediately above the function's
  `PROC`. `tools/probe.py --shape` does not print it.
* `tools/dis_retail.py 0x001F38A0 721` prints retail with every store's raw
  `esp+` displacement; matching those against the cod table row by row (as in
  the table above) is what identified `_bridgeTemplateName` and `$T5274` as the
  two collapsed pairs.

## 2026-09-28 follow-up: one-byte near miss

Changing the scalar `deathTime` into
`struct DeathTimeStorage { unsigned unused; unsigned value; };` and assigning
the frame delta to `deathTime.value` reaches the retail `sub esp, 0x30` frame.
The `/FAsc` listing gives `_deathTime = -36` (size 8),
`_bridgeTemplateName = -36`, `_modData = -28`, and `_pos = -24`; the live
`deathTime.value` is at -32, as retail requires. The loops compare the value
field directly, so the added first dword emits no instructions.

The 721-byte probe then has **one** non-relocation difference (shape 1.000,
24 relocations): at byte `+0x87`, the temporary EH pointer store is
`[esp+0x20]` instead of retail's `[esp+0x30]`. Its listing still places
`$T5283` at -48 on `_bridgeTemplate`; retail places `$T5274` with
`_deathTime` at the later slot. The candidate source is retained in
`build/bridge_update_1byte_nearmiss.cpp`; this is diagnostic scratch, not a
landed body. Do not treat the one-byte probe result as a match.

## 2026-09-28 follow-up: LANDED (stack-slot blocker resolved)

One shared `Coord3D pos` declared before the FX loop and reused in the OCL
loop (instead of two per-loop locals) compiles to retail's exact bytes:
721 vs 721, 24 relocations, 0 non-relocation diffs, shape 1.000
(`python3 tools/probe.py ... "?update@BridgeBehavior@@UAE?AW4UpdateSleepTime@@XZ" 0x001F38A0`
prints EXACT). The two-local form packs to `sub esp, 0x2c` with 27
displacement diffs; the shared form packs to retail's `sub esp, 0x30`.
No DeathTimeStorage device, no declaration-order or scope change was needed.

Two landing details, both byte-verified through `tools/add_match.py`:
the bridge name must be fetched as `bridge->getBridgeTemplateName()` with
`AsciiString getBridgeTemplateName();` declared on the local Bridge shim
(the proven pin `?getBridgeTemplateName@Bridge@@QAE?AVAsciiString@@XZ` at
0x001F22A0, reached via ILT 0x0004A83B). A same-shaped
`Rva000EE6D0StringAccessor::getString()` call probes EXACT but resolves to
the 0x000EE6D0 duplicate body and fails the gate at +0x7b; the union
member-pointer `bridgeName()` helper instead grows the body to 730 B.
Landed as game/GameEngine/Source/GameLogic/Object/Behavior/BridgeBehaviorUpdateThunk.cpp
replacing the BridgeBehavior_updateMethodThunk.cpp naked lift (deleted).

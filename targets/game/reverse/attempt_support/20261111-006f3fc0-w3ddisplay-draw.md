# W3DDisplay::draw (0x006F3FC0, 1184 B): EXACT via a TU-local panorama counter

Best candidate: `build/wf/006f3fc0/final.cpp`. It defines `?draw@W3DDisplay@@UAEXXZ`.
`python3 tools/probe.py build/wf/006f3fc0/final.cpp '?draw@W3DDisplay@@UAEXXZ' 0x006F3FC0 --size 1184`
reports `ours=1184 retail=1184 relocs=81 result EXACT (modulo relocation slots)`.
Compiler: MSVC 7.1 (13.10.3077) through probe.py. The `// cl:` line is
`/DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep`.
The sibling flags come from `W3DDisplayRva006EB500.cpp` and `W3DDisplay.cpp`,
which use `/DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc`. The bank's
`/EHs-c-` line is also EXACT (`cand.cpp`), so the EH model does not matter here.
The candidate has no volatile, barriers, asm or pragmas.

## Starting point

The bank `targets/game/reverse/attempts/0x006f3fc0.cpp` (score 0.9975) reproduced as logged:
1184 bytes with 3 non-relocation diffs at +0x3E2/+0x3E9/+0x3EB. In the save-width step, retail
uses EDX and the bank uses EAX. The bank relied on two volatile counter accesses and a
`__fastcall` dispatch-table adapter. Those cannot land under the clean-C++ rules.

## Decisive hypothesis: the counter at 0x012F804C is a file static

Retail evidence:
- A scan of the retail image finds references to VA 0x012F804C only in 0x006EAB10
  (`clamp_006eab10`, the 30-byte setter) and in draw.
- Both functions sit inside W3DDisplay.cpp's address range (0x006E85F0..0x006F3FC0).
- Both decrements in draw are load/dec/store, and each follows a dominating `> 0` test of the
  same global (+0x3D0 and +0x47D).

Declaring the counter `static int g_006eab10;` in the TU makes MSVC 7.1 emit the native
load/dec/store with a plain `--g_006eab10;` in both places. It also emits the native final
`mov edx,[ebp]` / `call [edx+0x124]` schedule through an ordinary virtual call to slot +0x124
(`RvaDrawSlots::slot124`). The volatile reads and writes and the DispatchTable adapter are
gone. With an `extern int`, MSVC emits `dec dword ptr [mem]`: 1174 B, 146 diffs.
Whether `clamp_006eab10` is defined before draw, after it, or absent leaves the result EXACT
in every case. clamp_006eab10 compiled in this TU is EXACT against 0x006EAB10 (30 B).

After that change, the save-width EAX/EDX residue disappears once the save call passes plain
`unsigned` arguments. Use `saveScreenShot(image, ecc*width, height)` and drop the
StrideValue save adapter. With the adapter kept and the counter static, the result is
1186 B with 141 diffs.

## Trials (family, change, result)

| family | change | result |
|---|---|---|
| (d) visibility/linkage | extern counter, plain `--` (volatile removed) | 1174 B, 146 diffs |
| (d) visibility/linkage | **static counter** + save via StrideValue | 1186 B, 141 |
| (d)+(c) | static counter + save with raw unsigned args (`--x`, `x--`, width*ecc both orders) | **EXACT** |
| (a)/(b) | static counter: `x = x - 1`, `x--`, `width*ecc` with save adapter | 1186 B, 141 |
| (d) | clamp writer before, after, or absent | all EXACT |
| (b)/(c)/(f) capture | drop the StrideValue capture adapter: raw call, rowBytes local, dst local, both locals, pos local, `(unsigned)` cast, `3u`, `count*(width*3)`, `3*width*count`, `&image[...]`, no count local, `this->` | all 1186 B, 157 |
| (d) capture | inline wrappers taking (char*,unsigned), const unsigned&, int, (image,index,width,count), static strideOf() | all 1186 B, 157 |
| (e) flags | W3DDisplay.cpp sibling `/DWIN32 /D_WINDOWS /EHsc` instead of `/EHs-c-` | EXACT |
| data naming | positive 2pi as `extern const float g_bfmeDisplayTwoPi` (recorded at 0x0111E36C) | 9 diffs: post-delete reload order edi/esi/ebp is permuted (+0x3FD..+0x40B) |
| data naming | same as `static const float` / defined const / inline getter / no cast / different decl position / negative also named | 9 diffs, or 160 for the reciprocal form |
| data naming | 0x012BAA5C as a file static `= 1` or a function-local static `= 1` (retail .data holds 1; only draw references it) | both EXACT |

The StrideValue006F3FC0 by-value capture adapter stays. It is the one reconstruction utility
that no natural spelling replaced (21 trials). It is ordinary C++ with
`absent-from-retail` markers on its two inline COMDATs.

## Landing notes (read-only checks; nothing landed)

(a) `tools/ilt_oracle.py check '?draw@W3DDisplay@@UAEXXZ' 0x006F3FC0` gives CONFIRMED (exact).
The same check gives CONTRADICTED for the existing row `?clamp_006eab10@@YG_NHH@Z` at
0x006EAB10. That is a pre-existing name issue. Its ILT is `?j_000361e2@@YAXXZ`.

(b) Helper bodies with their own rows:
- `clamp_006eab10` (0x006EAB10, 30 B) is emitted EXACT from final.cpp. It must move into
  draw's TU together with the static counter. Today it lives in
  `game/GameEngineDevice/Source/W3DDevice/GameClient/Gen_006eab10_Clamp.cpp` with an
  external `int g_006eab10;`, so that row needs a rehome.
- The two StrideValue inline COMDATs (`??0StrideValue006F3FC0@@QAE@I@Z` and
  `?captureScreen@W3DDisplay@@IAEXPADUStrideValue006F3FC0@@@Z`) are absent from retail and
  already marked.
- No other helper is defined.

(c) Globals by address, with the recorded names the candidate emits:
- ApplicationHWnd 0x012ED238 `?ApplicationHWnd@@3PAXA`
- TheGlobalData 0x012ED5C8 `?TheGlobalData@@3PAVGlobalData@@A`
- TheGameClient 0x012F1464
- TheGameLogic 0x012F0898 `?TheGameLogic@@3PAVBfmeGameLogicPause@@A`
- TheScriptEngine 0x012F076C
- TheTacticalView 0x012F1600 `?TheTacticalView@@3PAVView@@A`
- TheTerrainTracksRenderObjClassSystem 0x012F9D98
- g_bfmeY1058 0x012BAA2C
- TheW3DFrameLengthInMsec 0x012BB1CC
- `g_rva0075b2e0_value` (unsigned, in data_rows) 0x012F8064. The bank's `g_va012F8064` was
  unrecorded, so it was renamed to this recorded name.
- `__real@c0c90fdb` 0x010A13C4
- imports IsIconic, GetClientRect, ClientToScreen, timeGetTime

Still unrecorded, and these need `add_data_match` or TU-local data records:
1. Static counter `_g_006eab10` at 0x012F804C. dir32 only records the extern spelling
   `?g_006eab10@@3HA`.
2. `Rva012BAA5C` at 0x012BAA5C, a file static initialized to 1.
3. Function-local `prevTime` at 0x012F8220 and its guard `$S1` at 0x012F8224.
4. Open gate conflict: the positive 2pi literal emits `__real@40c90fdb`. dir32 binds that to
   0x01087B10, but draw reads the equal float at 0x0111E36C. That address sits between
   `__real@3faaa993` (0x0111E368) and `__real@3d9d89d9` (0x0111E370), and only W3DDisplay
   code (0x6EBDC0, 0x6ECB1B, 0x6ECBEF, draw) references it. The named-datum form costs
   9 bytes (see the trials above), so this needs a data-record decision, not a source change.

Callees (from `tools/callees.py`):
- Ledger-named: updateAverageFPS, `BfmeQ1087::bfmeGo1087A`,
  `ScriptEngine::isTimeFast`, `BfmeGameLogicPause::isGamePaused`,
  `W3DView::updateCameraMovements`, `TerrainTracksRenderObjClassSystem::update`,
  `WW3D::Sync`, `Debug_Statistics::Begin_Statistics`, `rva006EB500`, `captureScreen`
  (`?captureScreen@W3DDisplay@@IAEXPADI@Z`), `saveScreenShot`
  (`?saveScreenShot@W3DDisplay@@IAEXPADII@Z`), `Rva00754A10`, `??_U`, `??_V`.
- The compared callback addresses are the ledger ILT rows `j_0002f9f0`, `j_0003413f` and
  `j_0000d779`.
- Pins still needed. In each case retail calls through the ILT with ECX=this and pushes
  nothing; callees.py infers thiscall with 0 stack slots and the result unused.
  - `?rva006EE800@W3DDisplay@@QAEXXZ` at 0x006EE800 (ILT `j_0000a03d`). The ledger has only
    `?d_006ee800@@YAXXZ`, a gen_asm row.
  - `?rva006F2CC0@W3DDisplay@@QAEXXZ` at 0x006F2CC0 (ILT `j_00048216`). The ledger has only
    `?d_006f2cc0`.
  - 0x006F0300 (ILT `j_00022bec`). The ledger row is the odd `?gatherDebugStats@W3DDisplay@@`
    (object-symbol `_bfme_W3DDisplay_gatherDebugStats_6F0300`), and its funclet parent is
    `?gatherDebugStats@W3DDisplay@@IAEXXZ`. Prefer calling `gatherDebugStats()` once that
    row's name is reconciled; otherwise pin `?rva006F0300@W3DDisplay@@QAEXXZ`.

(d) TU: put draw where its counter lives, as one unit with `clamp_006eab10` and the file
statics. Ideally that is `game/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplay.cpp`,
where the present-unmatched ZH-style draw currently sits. That needs this body's decoded
class views adapted to the full header context; prior evidence shows the canonical View
header puts slots +0x74/+0xD8 0x14 too early. The alternative is a split TU, for example
`W3DDisplayDraw.cpp`, that absorbs `Gen_006eab10_Clamp.cpp`, as `W3DDisplayRva006EB500.cpp`
does for the render pass.

`tools/class_gate.py build/wf/006f3fc0/final.cpp` passes. The candidate keeps the bank's
descriptive identifiers.

## Landing attempt (2026-11-11): byte-exact, refused by DIR32 on a duplicated literal

The candidate passes the byte check at 1184/1184. For the landing it was placed in a split `W3DDisplayDraw.cpp` with `clamp_006eab10` and the shared static counter, with three callee pins:
- `?gatherDebugStats@W3DDisplay@@IAEXXZ` (ilt_oracle CONFIRMED);
- `?rva006EE800@W3DDisplay@@QAEXXZ`;
- `?rva006F2CC0@W3DDisplay@@QAEXXZ`.

The gate then refuses only one reference: `+0x270 __real@40c90fdb -> 0x0111E36C, but dir32_addresses.csv records 0x01087B10`.

Retail holds two copies of the 2π float. The draw literal reads the W3DDisplay-only copy at 0x0111E36C, which dir32 also records as `?g_bfmeDisplayTwoPi@@3MB` and the matched drawRemainingRectClock reads by that name. Every named spelling costs the same 9 bytes in draw: the extern `g_bfmeDisplayTwoPi`, a local copy of it, a file `static const` or a non-const static. Each moves three unrelated loads at +0x3FD. Only the literal is exact.

No `__real@` name in dir32_addresses.csv has more than one address, so the gate cannot express a duplicated literal pool. This is recorded as `blocked "false-reject dir32"`. The candidate is banked.

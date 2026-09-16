# WHALE-2 recipes

## 0x00960A30 — SegLineRendererClass::Render

- Status: banked partial, not landed. Preferred source is `reverse/attempts/0x00960a30.cpp` with support declarations in `reverse/attempt_support/0x00960a30.inc`.
- Evidence: 14,081 bytes, frame `0x6d84`, 190 relocation tuples, all callees resolved, and 17 canonical sibling emissions exact. The preferred body has 51 non-relocation differences (`0.9963780981464385`); the remaining groups are merge base/index SIB encodings (40), merge X-product order (2), initial-output SIB encodings (5), and expansion TOP-X addition order (4).
- Recipe: include canonical `matrix3d.h` before the TU-local ABI prefix, retain the hidden-result VB ABI, the proven `BoxDynamicVBAccessClass`/lock declarations, `BoxSetTexture` at `0x00905AC0`, the `TILED_TEXTURE_MAP` dead fall-through, the asymmetric `DotSegLineBottomOutput` helper with volatile `point.Y`, and `ScaleSegLineExpansion` for the three component stores. No new pins are required.
- Search: 12 explicit pointer/index alternatives were compiled with `tools/shape_search.py`; all legal alternatives stayed at the same 51-byte shape. Integer-address and reversed-index forms are therefore recorded as exhausted for this bank. Keep the bank; do not edit `Code/gen_asm` until an exact source is found.

## 0x007DF1F0 - TerrainShader8Stage::set

- Status: banked partial, not landed. The function remains anonymous in the ledger; the preferred body is `reverse/attempts/0x007df1f0.cpp`.
- Identity: the 9,305-byte body is `TerrainShader8Stage::set`, supported by the eight-stage terrain state sequence, the long branch to `terrainShader2Stage.set` at `0x007DD180`, nearby landed terrain shader methods, and the ten-callee contract from `tools/callees.py`.
- Best gate: clean C++ compiled through `Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DShaderManager.cpp`; `probe.py` reported 9,282 bytes versus 9,305 retail, 860 relocations, 5,431 non-relocation differences, and 796 relocation-layout sites that do not align. The sampler-state prefix matched through the first direct device call, but the prologue/register allocation and by-value texture-handle/vtable scheduling did not.
- Recipe: preserve the existing `BfmeHandleCX` by-value wrapper and direct slot-65 device call, `BFME_SET_SAMP` for sampler slots 1/2, `setTerrainTextureFilters`, ordinary `BFME_SET_TSS`, and `bfmeSetDX8Texture` for stages 2-7. The best candidate used separate scopes for the two returned handles and direct `m_Buffer[0]` in the snapshot-name wrapper. It still scored only `0.416`; no ledger change or pin is justified.
- Tried: inline versus named wrappers, raw-first and typed sampler calls, helper inlining, no-arg/direct-buffer snapshot construction, scoped and explicit handle/device/vtable locals, a reference-handle form, and an inline handle binder. The reference form lowered the byte diff but was not a safe clean source lifetime. A genuinely new frame/register scheduling lever is required.

# WHALE-3 recipes

## 0x0029E330 — ProductionUpdate candidate

- Status: banked partial, not landed. Preferred source: `reverse/attempts/0x0029e330.cpp`.
- Gate: 943 bytes versus retail 4,685; first divergence is offset `+0x0` (retail SEH prologue versus the normal-frame candidate).
- Recipe: the BFME secondary-interface and queue layouts, callee ABI shims, and production/UI/audio tail were tried against the ZH update body. The remaining factory/upgrade/UI/audio expansion is not byte-convergent; no pin was added.

## 0x00506726 — WOLQuickMatchMenuUpdate

- Status: banked partial, not landed. Preferred source: `reverse/attempts/0x00506726.cpp`.
- Gate: 3,944 bytes versus retail 4,682; frame diverges at `+0x15` (`sub esp,0x9bc` retail versus `0x568` candidate), with the first non-relocation mismatch at `+0x17`.
- Recipe: the ZH twin, BFME object-form ECX wrapper, GameLogic `+0x10c`, `psplayerstats`, PeerResponse `+0x330`, and all 61 direct callees were tried. The remaining blocker is broad GameSpy ABI and response-layout drift.

## 0x00781660 — W3DTruckDraw::doDrawModule candidate

- Status: banked partial, not landed. Preferred source: `reverse/attempts/0x00781660.cpp`.
- Gate: 4,261 bytes versus retail 4,431; frame diverges at `+0x4`, then GlobalData is `+0xa80` in retail versus `+0x714` at `+0x16`, followed by BFME module/drawable offset drift at `+0x25`.
- Recipe: vtable slot 9 and the truck constructor support this owner. The W3DTruckDraw twin and alternate W3DTankTruckDraw route were tried; the BFME eight-wheel, locomotor/AI, and render-layout expansion remains.

## 0x004A4240 — ControlBar::getCommandAvailability candidate

- Status: banked partial, not landed. Preferred source: `reverse/attempts/0x004a4240.cpp`.
- Gate: 2,446 bytes versus retail 4,572; first divergence is `+0x1c`, where retail saves EBX and keeps ECX as `this`, while the candidate saves EBP/ESI.
- Recipe: both caller-derived argument orders, Real output initialization, the ZH twin, EH frame shaping, and the `updateSpecialPowerShortcut` context were tried. The BFME availability ladder and ABI expansion remain.

## 0x004C1C30 — ControlBar tooltip candidate

- Status: banked partial, not landed. Preferred source: `reverse/attempts/0x004c1c30.cpp`.
- Gate: 4,364 bytes versus retail 4,289; raw divergence is `+0x2` (retail SEH setup versus candidate push-zero), and the frame diverges at `+0x15` (`0x28` versus `0x48`).
- Recipe: the ZH tooltip twin, four-output/ret16 ABI, BFME text/global fields, and EH cleanup layout were tried. The probe required a case-compatible `Basetype.h` bridge in ignored build scratch; the source still does not match.

## 0x0089ABC0 — Apt builtin registry initializer

- Status: banked partial, not landed. Preferred source: `reverse/attempts/0x0089abc0.cpp`.
- Gate: 4,310 bytes versus retail 4,137; first divergence is `+0x15` (retail `sub esp,8` versus candidate `push ecx`), with 3,508 non-relocation differences. `tools/callees.py` still reports unnamed direct callee `0x0089D890`.
- Recipe: the 11 callback/11 linked-value construction order, tagged retain/release wiring, allocator/vtable layouts, and registry globals were tried. No identity pin or unlock row was justified.

## 0x0071EEC0 — opaque dump body

- Status: blocked, no source bank.
- Evidence: the W3DSmudge render hypothesis is refuted by the BFME owner class size/layout. The HeightMapRenderTrees buffer call and address-derived scaffold do not define a compilable 4,112-byte body; exact candidate divergence is `+0x0` because no candidate bytes exist.
- Recipe: ZH smudge twin, HeightMap render route, caller/vtable search, and direct-callee ownership review exhausted; no safe semantic name or pin was invented.

## 0x009BFA40 — DeblockLoopFilteredBand_WMT

- Status: banked partial, not landed. Preferred source: `reverse/attempts/0x009bfa40.cpp`.
- Gate: 2,743 bytes versus retail 4,068; divergence begins at `+0x8`, where the retail entry uses the `m_tableIndex`/`g_rva01356A9C` broadcast and the candidate has different field/register order.
- Recipe: corrected context fields (`+0xc`, `+0x24`, `+0x28`), unconditional q broadcast, scalar horizontal/vertical filter, aligned frame, and the `0x009BEBB0` sibling shape were tried. The q>3 and cross-edge SIMD islands remain.

## 0x007D9AA0 — ScreenMotionBlurFilter::postRender

- Status: banked partial, not landed. Preferred source: `reverse/attempts/0x007d9aa0.cpp`.
- Gate: 2,179 bytes versus retail 4,005; divergence is `+0x0`, where retail registers EH and reserves `0x138` bytes while the candidate starts with a `0x98`-byte frame.
- Recipe: complete ZH control flow, BFME texture/state semantics, DynamicVB/DynamicIB quad substitution, and EH cleanup shape were tried. The retail dynamic-buffer/EH expansion remains.

## 0x007CCF50 — FlatTerrainShader2Stage::set

- Status: banked partial, not landed. Preferred source: `reverse/attempts/0x007ccf50.cpp`.
- Gate: 2,274 bytes versus retail 3,931; divergence is `+0x0`, where retail registers EH and reserves `0x1e8` bytes while the candidate starts with a `0x218` frame.
- Recipe: ZH/BFME shader-manager source, flat-shroud projection, stage clears/state cache, and the full 16-callee set were tried. BFME state-cache/EH expansion remains.

## 0x006F2CC0 — W3DDisplay animation-debug candidate

- Status: banked partial, not landed. Preferred source: `reverse/attempts/0x006f2cc0.cpp`.
- Gate: 31 bytes versus retail 3,881; divergence is `+0x0`, where retail begins SEH registration and a `0x5c` frame while the candidate is only a placeholder call sequence.
- Recipe: unique animation/weapon/locked-object strings, protected-member source shape, UnicodeString/FontLibrary callees, and the BFME debug ladder were exhausted without a clean source body.

## 0x009B9700 — VP6 wide reconstruct candidate

- Status: banked partial, not landed. Preferred source: `reverse/attempts/0x009b9700.cpp`.
- Gate: 4,588 bytes versus retail 4,240; frame divergence is `+0x16` (`0x1d8` retail versus `0x1f8` candidate), and the shared scalar reduction diverges at `+0x6e9`.
- Recipe: aligned `/Z7` frame map, explicit EAX mode-index lookup, both transcribed MMX islands, pointer prelude, reverse-order scalar reductions, frame-slot padding/alignment, and register/loop-shape levers were tried. The first MMX island aligns, but frame and remaining scalar/second-island layout do not.
# WHALE-1 recipes

This file records source-level recipes and failed levers for the large dump
bodies worked by the WHALE sessions. A recipe is reusable only when its
callee identity and layout are supported by retail evidence; a banked recipe
is not a byte-match.

## 0x008BF100 — APT route-key registry initializer

Status: banked partial; no exact clean-C++ reconstruction found.

### Callee table

| Retail target | Count | Proven identity | Evidence |
| --- | ---: | --- | --- |
| `0x0089E680` | 178 | `?bfmeSetVKI@BfmeStrVKI@@QAEXPBD@Z` | `tools/callees.py 0x008BF100 18655`; every string block calls the same `thiscall` setter |
| `0x008C5D70` through the IAT | 1 | `Rva008C5D70Alloc` | tail allocates `hashCount * 4` bytes for the hash array |
| `0x00891B80` through EH cleanup funclets | 178 | `?release@Rva00891B80@@QAEXXZ` | retail cleanup funclets at `0x00C593C0` onward jump to the matched release body |

The ledger currently carries the generated placeholder as a no-argument
symbol, but the retail caller at `0x00894800` pushes `[edi+0x38]` before the
call. The clean reconstruction therefore uses `void d_008bf100(int hashCount)`;
that ABI correction is evidence, not a semantic name claim.

### Layout

- `g_bfmeRouteKeys1282` is 178 consecutive 4-byte string handles at
  `0x01338480..0x0133874b`; the first initialization loop fills two null
  handles per iteration from `g_bfmeDefaultString1284` at `0x012D5298`.
- The handle points at a short string header containing 16-bit reference
  count, length, capacity, and flags. The shared pool at `0x01337A30` releases
  the header when the count reaches zero.
- The 178 literals are the exact `reverse/string_xrefs.tsv` order from
  `__proto__` through `yMin`; each assignment constructs a temporary, calls
  `bfmeSetVKI`, retains the new handle, releases the old table handle, then
  releases the temporary.
- Retail reserves `0x2c8` bytes after the EH registration frame and has 178
  distinct cleanup states/temporary stack slots. The final three operations
  allocate, zero, and publish the hash array and count.

### Levers tried

The best bank is the inline `BfmeStrVKI` model in
`reverse/attempts/0x008bf100.cpp`, compiled with `/O2 /DNDEBUG /DWIN32
/D_WINDOWS /MD /EHsc`. It reproduces the literal order, the setter call
contract, the two-slot default initialization, reference-count release, and
hash-array tail, but emits a 16,229-byte body with an 8-byte scratch frame
instead of retail's 18,655-byte body and 0x2c8 frame; the masked score is
0.2615.

The candidate evidence line records the attempted alternatives: direct
implicit assignments; explicit temporaries; renamed exact `BfmeStrVKI`;
named locals and pair walks; raw and aggregate `0x2c8` storage; an empty
destructor frame; `/EHsc`, `/EHa`, `/EHs`, `/GX`, `/Ob1`, `/Og-`, `/O1`,
`/Os`, `/Od`, `/Z7`; `volatile` members/destination; packed storage; a
declaration-only constructor; explicit copy construction/assignment; an
out-of-class forced-inline assignment; helper functions; derived/base
classes; distinct template types; and temporary-return factories. None
produced retail's unique cleanup-slot permutation. Do not add a pin or hand
edit the generated dump; the next useful attack is a source-level ABI/lifetime
shape supported by another matched APT string initializer.

No rows were added to `reverse/unlocked.txt`: this partial establishes the
callee/layout hypothesis for this body, but does not land a shared shim or a
byte-verified source body that would unlock a neighbour.
## 0x007CE290 - TerrainShader2Stage::set

- Status: banked partial, not landed. The preferred source is `reverse/attempts/0x007ce290.cpp`; the retail body is the anonymous `?d_007ce290@@YAXXZ` row in `Code/gen_asm/d_007ccf50.asm`.
- Identity: the 8,147-byte body is `TerrainShader2Stage::set(Int)`. The address neighborhood places `FlatTerrainShader2Stage::set` at 0x007C5690, and this body has five `BoxSetTexture` calls matching Terrain’s five-texture pass sequence, plus the larger Terrain state/noise contract.
- Best gate: the current BFME state-cache/noise candidate compiled and probed at 9,265 bytes versus 8,147 retail, with 821 relocations, 5,045 non-relocation differences, and 802 relocation-layout sites that do not align. The earlier FlatTerrain-labelled candidate was rejected as wrong identity (7,168 bytes, 651 relocations, 4,403 non-relocation differences, 632 relocation-layout drifts).
- Recipe: retain `BFME_SET_TSS` for the proven cache path, `BFME_SET_SAMP` for sampler slot 69, `BFME_SET_RS` for render slot 57, and the `bfmeSetTexture` routes used by the one-texture noise branches. The retail callee contract includes five `BoxSetTexture` calls, slot-67 TSS calls, and helpers at `0x007DCF00` and `0x007DCCE0`.
- Blocker: the BFME handle/EH frame schedule and matrix/noise helper ABI remain unproven; no pin is justified. Do not edit `Code/gen_asm` or replace the anonymous row until a clean source is byte-exact.

## 0x007C7FD0 — FlatTerrainShaderPixelShader::set

Status: banked partial; identity is supported, but no exact clean-C++ body
was found. The preferred function-sized candidate is
`reverse/attempts/0x007c7fd0.cpp`, compiled in the existing
`W3DShaderManager.cpp` TU context.

### Callee table

| Retail target | Count | Proven identity | Evidence |
| --- | ---: | --- | --- |
| `0x009DB890` | 38 | `StringClass::Get_String` | repeated DX8 snapshot-name construction |
| `0x00906FE0` | 36 | `DX8Wrapper::Get_DX8_Texture_Stage_State_Value_Name` | repeated texture-stage state logging |
| `0x009DB7A0` | 38 | `StringClass::Free_String` | snapshot temporary cleanup |
| `0x009FB321` | 7 | `_D3DXMatrixInverse@12` | shroud/noise projection matrices |
| `0x00905AC0` | 1 | `BoxSetTexture` | texture state setup |
| `0x00904890` | 2 | `DX8Wrapper::Apply_Render_State_Changes` | state-cache barriers |
| `0x0090DC60` | 10 | `TextureBaseClass::Peek_D3D_Base_Texture` | texture binding path |
| `0x009EB7A0` | 13 | `TextureClass::Release_Ref` | texture lifetime cleanup |
| `0x009FACAD`, `0x009FB6F4`, `0x009FB784` | 12 total | address-derived/pinned matrix helpers | `tools/callees.py`; ABI is known, semantic names remain constrained |

The remaining direct targets are the already-resolved DX8 ILT/state helpers
listed by `tools/callees.py 0x007C7FD0 12130`; none was pinned by this body.

### Layout

- The body begins with an MSVC EH frame and reserves `0x320` bytes; it takes
  one stack `pass` argument and returns with `ret 4`. ECX is saved at entry,
  so the class-method ABI is consistent with the six-field pixel-shader
  object, including BFME taint shader handles at `this+0x18` and `this+0x1c`.
- Retail reads the terrain render object at `0x012F7FE0`, its shroud at
  `+0x30b8`, and the proven DX8 device/cache globals at `0x01340534`,
  `0x01340568`, `0x01340594`, and `0x0133F451`/related state storage.
- The state sequence is the flat-terrain shroud transform followed by noise
  stages, pixel-shader selection, texture/render-state writes, and a final
  cache barrier. The repeated `Get_String`/state-name calls are the inlined
  DX8 snapshot wrapper, not evidence for a second owner class.

### Levers tried

The source-backed `FlatTerrainShaderPixelShader::set` candidate compiled to
1,811 bytes versus 12,130 retail bytes, with 1,295 non-relocation diffs and
first divergence at `+0` (`sub esp,0x198` versus retail EH registration and
`sub esp,0x320`); 516 masked prefix bytes were equal, for a recorded score of
0.0425. The alternate `FlatTerrainShader2Stage::set` candidate compiled to
2,274 bytes with 1,489 non-relocation diffs and the same `+0` frame mismatch.
Enabling the project snapshot macro did not change either object shape. The
remaining BFME taint/pixel-shader expansion and state-cache/EH ladder are not
represented by the current source. The existing `reverse/unlocked.txt` row
`0x007c7fd0 w3d-render` establishes the shared DX8 family only; no new unlock
row, pin, or guessed class/member name is justified.

## 0x00934940 - expanded Render2D-shaped renderer

Status: banked partial; identity remains unresolved and no clean-C++ body was
byte-exact. The preferred function-sized candidate is
`reverse/attempts/0x00934940.cpp`, compiled in the current
`render2d.cpp` TU context. The anonymous ledger row remains
`?d_00934940@@YAXXZ`; `Render2DClass::Render` is already caller/vtable-proven
at `0x00933E50`, so reusing that semantic name or adding a pin would be an
unsupported identity claim.

### Callee table

| Retail target | Count | Proven identity | Evidence |
| --- | ---: | --- | --- |
| `0x00904 (DX8Wrapper)` family | 1 each except where noted | `Set_Viewport`, `Set_Index_Buffer`, `Apply_Render_State_Changes`, `Draw_Triangles` | `tools/callees.py 0x00934940 8277` |
| `0x00905AC0` | 9 | `BoxSetTexture` | repeated batch texture binding |
| `0x00906FE0` | 26 | `Get_DX8_Texture_Stage_State_Value_Name` | expanded texture-state snapshot |
| `0x00907BE0` | 13 | `Get_DX8_Render_State_Value_Name` | expanded render-state snapshot |
| `0x0091D350`, `0x0091D410`, `0x0091D4E0`, `0x0091D950` | 1 each | `DynamicIBAccessClass` ctor/dtor and `WriteLock` | index-buffer upload |
| `0x0091D9E0`, `0x0091F160`, `0x0091F240`, `0x0091F730` | 1 each | `BoxDynamicVBAccessClass` ctor/dtor and `WriteLock` | vertex-buffer upload |
| `0x009212C0` | 1 | `VertexMaterialClass::Get_Preset` | material setup |
| `0x00934820` | 1 | `Render2DClass::Reset` | renderer reset path |
| `0x009DB890`, `0x009DB7A0` | 37 / 40 | `StringClass::Get_String` / `Free_String` | snapshot temporary strings |
| `0x009EB7A0` | 5 | `TextureClass::Release_Ref` | texture lifetime cleanup |
| `0x0000AE5C`, `0x00029924`, `0x00904510` | 1, 3, 1 | address-derived helpers | target contract is known; semantic names are not |

### Layout

- Retail opens with an MSVC EH frame, reserves `0x120` bytes, saves `this` in
  EDI, and guards on `[this+0x1c]`; an empty collection returns its count.
- The renderer owns a `DynamicIBAccessClass` at approximately `this+0x2c`.
  The later batch collection starts at `this+0x38` and advances in `0x74`-byte
  elements. Vertex and index writes use the paired dynamic-buffer access and
  write-lock lifetimes.
- The expanded state path snapshots DX8 texture/render state through the
  string-name helpers, uses the DX8 transform globals around
  `0x013410CC..0x01341104`, and calls `BoxSetTexture` nine times.
- `d_0079dee0` calls this address at `+0x187` through an object obtained from a
  display vtable slot. That supports a renderer interpretation but does not
  prove the owning class or a safe pin.

### Levers tried

The current BFME `render2d.cpp` `Render2DClass::Render` candidate compiled to
3,743 bytes versus 8,277 retail, with 2,548 non-relocation differences and
1,195 masked-equal bytes, for the recorded score `0.1444`; the first
divergence is `+0` because retail starts with `push -1`, the MSVC EH frame,
and `sub esp,0x120`. The Zero Hour `render2d.cpp` candidate was also 3,743
bytes with 2,553 non-relocation differences. Enabling
`MESH_RENDER_SNAPSHOT_ENABLED` made no shape change. The mechanical EH search
attempted all 128 generated combinations; its `throw()` variants failed
syntax compilation and none beat the baseline. No semantic source owner,
pin, or new unlock row is justified. The existing `reverse/unlocked.txt`
entry `0x00934940 w3d-render` predates this attempt and was not changed.
## 0x007C5690 - FlatTerrainShader2Stage::set

- Status: banked partial, not landed. The preferred source is `reverse/attempts/0x007c5690.cpp`; the retail body is the anonymous `?d_007c5690@@YAXXZ` row in `Code/gen_asm/d_007afaa0.asm`.
- Identity: the 7,909-byte body is `FlatTerrainShader2Stage::set(Int)`, supported by `FlatTerrainShader2Stage::init`/`reset` at `0x007C55B0`/`0x007C5600` and the flat terrain shroud/noise sequence.
- Best gate: the best clean candidate compiled and probed at 7,093 bytes versus 7,909 retail, with 622 relocations, 4,415 non-relocation differences, and 600 relocation-layout mismatches. The target frame is `0x2b4` versus candidate `0x230`; target register setup begins `xor ebp`/`push ebp`/`mov ebx,1`, while the candidate begins `xor ebx`/`push ebx`/`mov ebp,1`.
- Recipe: call `setTerrainTextureFilters(0)` and `(1)`, use `BFME_SET_TSS`/`BFME_SET_SAMP`/`BFME_SET_RS`, and use the proven `bfmeGet` plus direct slot-65 texture binding for the flat/noise texture routes. The retail contract has `setTerrainTextureFilters` at `0x006D4690` x2, `j_0001aded`/`bfmeGet` at `0x007C34A0` x7, `Peek_D3D_Base_Texture` x6, sampler slot 69 x14, TSS slot 67 x34, RS slot 57 x4, and texture slot 65 x6.
- Tried: helper-only expansion (`2128` bytes), full state-cache/sampler expansion (`6696`), explicit address-state shape choices (best `6777`, score `0.3324`), and the handle-aware candidate with both address states as TSS plus the sibling late-state macro pattern (`7093`, score `0.34`). None was exact; no pin or unlock row is justified. The remaining lever is the BFME EH/frame/register and texture-handle scheduling shape.

## 0x009B8130 - VP6 reconstruct / MMX dispatch body

- Status: blocked after bounded review; the existing stale scaffold remains at `reverse/attempts/0x009b8130.cpp` and no generated body was edited.
- Evidence: `tools/callees.py 0x009B8130 5572` resolves zero direct call targets. Retail begins with the proven `/Z7` aligned-frame prologue and `sub esp,0x1f8`, then runs a single fragment loop with one mandatory literal MMX island and a separate branch-controlled island; the context uses the `+0x24` qIndex indirection and packed scratch buffers.
- Candidates: the existing scalar scaffold compiled to 182 versus 5,572 retail with score `0.03`; the available aligned-frame `0x009B9700` sibling compiled to 4,214 versus this target with 23 relocations and 3,794 non-relocation differences, diverging structurally at `+0x16` (`sub esp,0x1f8` versus `sub esp,0x1c8`) and using the wrong index chain/body length. No exact source, pin, or safe dump lift was found.
- Next lever: a dedicated transcription of both retail MMX islands with the 0x1f8 frame-slot order and the qIndex lookup; reusing the sibling would assert the wrong identity.

## 0x009D9D90 - _bfme_dumpXferStream

- Status: blocked after reviewing the existing source-backed stash; `reverse/attempts/0x009d9d90.cpp` remains retained at score `0.55`.
- Identity: `_bfme_dumpXferStream` is supported by the named `GameLogic::_bfme_reportDesync` caller and the BFME RTS1/RTS2 tagged transfer-stream behavior.
- Evidence: the retail contract has 14 direct targets, including parser helpers `0x009D9110` x34 and `0x009D9160` x32, `_bfmeFormatText` x7, vector/string buffer lifetime helpers, and a `0x288` EH frame. The stash probes at 3,046 versus 5,472 bytes with 96 relocations, 2,389 non-relocation differences, 93 relocation-layout mismatches, and a `0x2f0` frame.
- No exact parser/error-ladder source, pin, or unlock row is justified; adding the missing BFME behavior without its live format/throw contract would be invented.

## 0x0057A470 - BfmeAptScreenSkirmish::_bfme_updateProfileDisplay

- Status: blocked at the existing score `0.47`; `reverse/attempts/0x0057a470.cpp` remains the preferred source-backed stash.
- Identity: the BFME Skirmish profile display updater is supported by the three `AptSkirmish::InitGadgets` callsites and its APT-specific labels.
- Evidence: the stash probes at 2,614 versus 5,296 bytes with the exact `0x13c` frame, then diverges at `+0x1c` in callee-saved/register setup. Retail has 27 direct targets, including `_bfmeFormatText`, 19 Unicode formatting calls, 3 translations, and the corresponding string constructor/release ladder; the source models the visible labels but not the retail profile/global dispatch state.
- No exact source, pin, or unlock row is justified.

## 0x0073E050 - W3DView::draw

- Status: blocked at the existing score `0.30`; `reverse/attempts/0x0073e050.cpp` remains scratch evidence only.
- Identity: the body is `W3DView::draw`, supported by the `W3DDisplay::m_3DScene` path, `filterPreRender`/`filterPostRender` calls, and W3DView field accesses.
- Evidence: retail has 13 direct targets including `DX8Wrapper::Clear` x3. The source twin probes at 1,831 versus 5,126 bytes with 57 relocations, 1,527 non-relocation differences, and 56 relocation-layout mismatches; retail begins with a no-EH `0x120` frame while the twin begins with EH and a `0x1bc` frame. The scratch bank’s relative include path is also not independently compilable.
- No exact BFME display-global/filter ladder, pin, or unlock row is justified.

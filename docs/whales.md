# WHALE-2 recipes

## 0x00960A30 — SegLineRendererClass::Render

- Status: banked partial, not landed. Preferred source is `targets/game/reverse/attempts/0x00960a30.cpp` with support declarations in `targets/game/reverse/attempt_support/0x00960a30.inc`.
- Evidence: 14,081 bytes, frame `0x6d84`, 190 relocation tuples, all callees resolved, and 17 canonical sibling emissions exact. The preferred body has 51 non-relocation differences (`0.9963780981464385`); the remaining groups are merge base/index SIB encodings (40), merge X-product order (2), initial-output SIB encodings (5), and expansion TOP-X addition order (4).
- Recipe: include canonical `matrix3d.h` before the TU-local ABI prefix, retain the hidden-result VB ABI, the proven `BoxDynamicVBAccessClass`/lock declarations, `BoxSetTexture` at `0x00905AC0`, the `TILED_TEXTURE_MAP` dead fall-through, the asymmetric `DotSegLineBottomOutput` helper with volatile `point.Y`, and `ScaleSegLineExpansion` for the three component stores. No new pins are required.
- Search: 12 explicit pointer/index alternatives were compiled with `tools/shape_search.py`; all legal alternatives stayed at the same 51-byte shape. Integer-address and reversed-index forms are therefore recorded as exhausted for this bank. Keep the bank; do not edit `game/gen_asm` until an exact source is found.

## 0x007DF1F0 - TerrainShader8Stage::set

- Status: banked partial, not landed. The function remains anonymous in the ledger; the preferred body is `targets/game/reverse/attempts/0x007df1f0.cpp`.
- Identity: the 9,305-byte body is `TerrainShader8Stage::set`, supported by the eight-stage terrain state sequence, the long branch to `terrainShader2Stage.set` at `0x007DD180`, nearby landed terrain shader methods, and the ten-callee contract from `tools/callees.py`.
- Best gate: clean C++ compiled through `game/GameEngineDevice/Source/W3DDevice/GameClient/W3DShaderManager.cpp`; `probe.py` reported 9,282 bytes versus 9,305 retail, 860 relocations, 5,431 non-relocation differences, and 796 relocation-layout sites that do not align. The sampler-state prefix matched through the first direct device call, but the prologue/register allocation and by-value texture-handle/vtable scheduling did not.
- Recipe: preserve the existing `BfmeHandleCX` by-value wrapper and direct slot-65 device call, `BFME_SET_SAMP` for sampler slots 1/2, `setTerrainTextureFilters`, ordinary `BFME_SET_TSS`, and `bfmeSetDX8Texture` for stages 2-7. The best candidate used separate scopes for the two returned handles and direct `m_Buffer[0]` in the snapshot-name wrapper. It still scored only `0.416`; no ledger change or pin is justified.
- Tried: inline versus named wrappers, raw-first and typed sampler calls, helper inlining, no-arg/direct-buffer snapshot construction, scoped and explicit handle/device/vtable locals, a reference-handle form, and an inline handle binder. The reference form lowered the byte diff but was not a safe clean source lifetime. A genuinely new frame/register scheduling lever is required.

# WHALE-3 recipes

## 0x0029E330 — ProductionUpdate candidate

- Status: banked partial, not landed. Preferred source: `targets/game/reverse/attempts/0x0029e330.cpp`.
- Gate: 943 bytes versus retail 4,685; first divergence is offset `+0x0` (retail SEH prologue versus the normal-frame candidate).
- Recipe: the BFME secondary-interface and queue layouts, callee ABI shims, and production/UI/audio tail were tried against the ZH update body. The remaining factory/upgrade/UI/audio expansion is not byte-convergent; no pin was added.

## 0x00506726 — WOLQuickMatchMenuUpdate

- Status: banked partial, not landed. Preferred source: `targets/game/reverse/attempts/0x00506726.cpp`.
- Gate: 3,944 bytes versus retail 4,682; frame diverges at `+0x15` (`sub esp,0x9bc` retail versus `0x568` candidate), with the first non-relocation mismatch at `+0x17`.
- Recipe: the ZH twin, BFME object-form ECX wrapper, GameLogic `+0x10c`, `psplayerstats`, PeerResponse `+0x330`, and all 61 direct callees were tried. The remaining blocker is broad GameSpy ABI and response-layout drift.

## 0x00781660 — W3DTruckDraw::doDrawModule candidate

- Status: banked partial, not landed. Preferred source: `targets/game/reverse/attempts/0x00781660.cpp`.
- Gate: 4,261 bytes versus retail 4,431; frame diverges at `+0x4`, then GlobalData is `+0xa80` in retail versus `+0x714` at `+0x16`, followed by BFME module/drawable offset drift at `+0x25`.
- Recipe: vtable slot 9 and the truck constructor support this owner. The W3DTruckDraw twin and alternate W3DTankTruckDraw route were tried; the BFME eight-wheel, locomotor/AI, and render-layout expansion remains.

## 0x004A4240 — ControlBar::getCommandAvailability candidate

- Status: banked partial, not landed. Preferred source: `targets/game/reverse/attempts/0x004a4240.cpp`.
- Gate: 2,446 bytes versus retail 4,572; first divergence is `+0x1c`, where retail saves EBX and keeps ECX as `this`, while the candidate saves EBP/ESI.
- Recipe: both caller-derived argument orders, Real output initialization, the ZH twin, EH frame shaping, and the `updateSpecialPowerShortcut` context were tried. The BFME availability ladder and ABI expansion remain.

## 0x004C1C30 — ControlBar tooltip candidate

- Status: banked partial, not landed. Preferred source: `targets/game/reverse/attempts/0x004c1c30.cpp`.
- Gate: 4,364 bytes versus retail 4,289; raw divergence is `+0x2` (retail SEH setup versus candidate push-zero), and the frame diverges at `+0x15` (`0x28` versus `0x48`).
- Recipe: the ZH tooltip twin, four-output/ret16 ABI, BFME text/global fields, and EH cleanup layout were tried. The probe required a case-compatible `Basetype.h` bridge in ignored build scratch; the source still does not match.

## 0x0089ABC0 — Apt builtin registry initializer

- Status: banked partial, not landed. Preferred source: `targets/game/reverse/attempts/0x0089abc0.cpp`.
- Gate: 4,310 bytes versus retail 4,137; first divergence is `+0x15` (retail `sub esp,8` versus candidate `push ecx`), with 3,508 non-relocation differences. `tools/callees.py` still reports unnamed direct callee `0x0089D890`.
- Recipe: the 11 callback/11 linked-value construction order, tagged retain/release wiring, allocator/vtable layouts, and registry globals were tried. No identity pin or unlock row was justified.

## 0x0071EEC0 — opaque dump body

- Status: blocked, no source bank.
- Evidence: the W3DSmudge render hypothesis is refuted by the BFME owner class size/layout. The HeightMapRenderTrees buffer call and address-derived scaffold do not define a compilable 4,112-byte body; exact candidate divergence is `+0x0` because no candidate bytes exist.
- Recipe: ZH smudge twin, HeightMap render route, caller/vtable search, and direct-callee ownership review exhausted; no safe semantic name or pin was invented.

## 0x009BFA40 — DeblockLoopFilteredBand_WMT

- Status: banked partial, not landed. Preferred source: `targets/game/reverse/attempts/0x009bfa40.cpp`.
- Gate: 2,743 bytes versus retail 4,068; divergence begins at `+0x8`, where the retail entry uses the `m_tableIndex`/`g_rva01356A9C` broadcast and the candidate has different field/register order.
- Recipe: corrected context fields (`+0xc`, `+0x24`, `+0x28`), unconditional q broadcast, scalar horizontal/vertical filter, aligned frame, and the `0x009BEBB0` sibling shape were tried. The q>3 and cross-edge SIMD islands remain.

## 0x007D9AA0 — ScreenMotionBlurFilter::postRender

- Status: banked partial, not landed. Preferred source: `targets/game/reverse/attempts/0x007d9aa0.cpp`.
- Gate: 2,179 bytes versus retail 4,005; divergence is `+0x0`, where retail registers EH and reserves `0x138` bytes while the candidate starts with a `0x98`-byte frame.
- Recipe: complete ZH control flow, BFME texture/state semantics, DynamicVB/DynamicIB quad substitution, and EH cleanup shape were tried. The retail dynamic-buffer/EH expansion remains.

## 0x007CCF50 — FlatTerrainShader2Stage::set

- Status: banked partial, not landed. Preferred source: `targets/game/reverse/attempts/0x007ccf50.cpp`.
- Gate: 2,274 bytes versus retail 3,931; divergence is `+0x0`, where retail registers EH and reserves `0x1e8` bytes while the candidate starts with a `0x218` frame.
- Recipe: ZH/BFME shader-manager source, flat-shroud projection, stage clears/state cache, and the full 16-callee set were tried. BFME state-cache/EH expansion remains.

## 0x006F2CC0 — W3DDisplay animation-debug candidate

- Status: banked partial, not landed. Preferred source: `targets/game/reverse/attempts/0x006f2cc0.cpp`.
- Gate: 31 bytes versus retail 3,881; divergence is `+0x0`, where retail begins SEH registration and a `0x5c` frame while the candidate is only a placeholder call sequence.
- Recipe: unique animation/weapon/locked-object strings, protected-member source shape, UnicodeString/FontLibrary callees, and the BFME debug ladder were exhausted without a clean source body.

## 0x009B9700 — VP6 wide reconstruct candidate

- Status: banked partial, not landed. Preferred source: `targets/game/reverse/attempts/0x009b9700.cpp`.
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
- The 178 literals are the exact `targets/game/reverse/string_xrefs.tsv` order from
  `__proto__` through `yMin`; each assignment constructs a temporary, calls
  `bfmeSetVKI`, retains the new handle, releases the old table handle, then
  releases the temporary.
- Retail reserves `0x2c8` bytes after the EH registration frame and has 178
  distinct cleanup states/temporary stack slots. The final three operations
  allocate, zero, and publish the hash array and count.

### Levers tried

The best bank is the inline `BfmeStrVKI` model in
`targets/game/reverse/attempts/0x008bf100.cpp`, compiled with `/O2 /DNDEBUG /DWIN32
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

No rows were added to `targets/game/reverse/unlocked.txt`: this partial establishes the
callee/layout hypothesis for this body, but does not land a shared shim or a
byte-verified source body that would unlock a neighbour.
## 0x007CE290 - TerrainShader2Stage::set

- Status: banked partial, not landed. The preferred source is `targets/game/reverse/attempts/0x007ce290.cpp`; the retail body is the anonymous `?d_007ce290@@YAXXZ` row in `game/gen_asm/d_007ccf50.asm`.
- Identity: the 8,147-byte body is `TerrainShader2Stage::set(Int)`. The address neighborhood places `FlatTerrainShader2Stage::set` at 0x007C5690, and this body has five `BoxSetTexture` calls matching Terrain’s five-texture pass sequence, plus the larger Terrain state/noise contract.
- Best gate: the current BFME state-cache/noise candidate compiled and probed at 9,265 bytes versus 8,147 retail, with 821 relocations, 5,045 non-relocation differences, and 802 relocation-layout sites that do not align. The earlier FlatTerrain-labelled candidate was rejected as wrong identity (7,168 bytes, 651 relocations, 4,403 non-relocation differences, 632 relocation-layout drifts).
- Recipe: retain `BFME_SET_TSS` for the proven cache path, `BFME_SET_SAMP` for sampler slot 69, `BFME_SET_RS` for render slot 57, and the `bfmeSetTexture` routes used by the one-texture noise branches. The retail callee contract includes five `BoxSetTexture` calls, slot-67 TSS calls, and helpers at `0x007DCF00` and `0x007DCCE0`.
- Blocker: the BFME handle/EH frame schedule and matrix/noise helper ABI remain unproven; no pin is justified. Do not edit `game/gen_asm` or replace the anonymous row until a clean source is byte-exact.

## 0x007C7FD0 — FlatTerrainShaderPixelShader::set

Status: banked partial; identity is supported, but no exact clean-C++ body
was found. The preferred function-sized candidate is
`targets/game/reverse/attempts/0x007c7fd0.cpp`, compiled in the existing
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
represented by the current source. The existing `targets/game/reverse/unlocked.txt` row
`0x007c7fd0 w3d-render` establishes the shared DX8 family only; no new unlock
row, pin, or guessed class/member name is justified.

## 0x00934940 - expanded Render2D-shaped renderer

Status: banked partial; identity remains unresolved and no clean-C++ body was
byte-exact. The preferred function-sized candidate is
`targets/game/reverse/attempts/0x00934940.cpp`, compiled in the current
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
pin, or new unlock row is justified. The existing `targets/game/reverse/unlocked.txt`
entry `0x00934940 w3d-render` predates this attempt and was not changed.
## 0x007C5690 - FlatTerrainShader2Stage::set

- Status: banked partial, not landed. The preferred source is `targets/game/reverse/attempts/0x007c5690.cpp`; the retail body is the anonymous `?d_007c5690@@YAXXZ` row in `game/gen_asm/d_007afaa0.asm`.
- Identity: the 7,909-byte body is `FlatTerrainShader2Stage::set(Int)`, supported by `FlatTerrainShader2Stage::init`/`reset` at `0x007C55B0`/`0x007C5600` and the flat terrain shroud/noise sequence.
- Best gate: the best clean candidate compiled and probed at 7,093 bytes versus 7,909 retail, with 622 relocations, 4,415 non-relocation differences, and 600 relocation-layout mismatches. The target frame is `0x2b4` versus candidate `0x230`; target register setup begins `xor ebp`/`push ebp`/`mov ebx,1`, while the candidate begins `xor ebx`/`push ebx`/`mov ebp,1`.
- Recipe: call `setTerrainTextureFilters(0)` and `(1)`, use `BFME_SET_TSS`/`BFME_SET_SAMP`/`BFME_SET_RS`, and use the proven `bfmeGet` plus direct slot-65 texture binding for the flat/noise texture routes. The retail contract has `setTerrainTextureFilters` at `0x006D4690` x2, `j_0001aded`/`bfmeGet` at `0x007C34A0` x7, `Peek_D3D_Base_Texture` x6, sampler slot 69 x14, TSS slot 67 x34, RS slot 57 x4, and texture slot 65 x6.
- Tried: helper-only expansion (`2128` bytes), full state-cache/sampler expansion (`6696`), explicit address-state shape choices (best `6777`, score `0.3324`), and the handle-aware candidate with both address states as TSS plus the sibling late-state macro pattern (`7093`, score `0.34`). None was exact; no pin or unlock row is justified. The remaining lever is the BFME EH/frame/register and texture-handle scheduling shape.

## 0x009B8130 - VP6 reconstruct / MMX dispatch body

- Status: blocked after bounded review; the existing stale scaffold remains at `targets/game/reverse/attempts/0x009b8130.cpp` and no generated body was edited.
- Evidence: `tools/callees.py 0x009B8130 5572` resolves zero direct call targets. Retail begins with the proven `/Z7` aligned-frame prologue and `sub esp,0x1f8`, then runs a single fragment loop with one mandatory literal MMX island and a separate branch-controlled island; the context uses the `+0x24` qIndex indirection and packed scratch buffers.
- Candidates: the existing scalar scaffold compiled to 182 versus 5,572 retail with score `0.03`; the available aligned-frame `0x009B9700` sibling compiled to 4,214 versus this target with 23 relocations and 3,794 non-relocation differences, diverging structurally at `+0x16` (`sub esp,0x1f8` versus `sub esp,0x1c8`) and using the wrong index chain/body length. No exact source, pin, or safe dump lift was found.
- Next lever: a dedicated transcription of both retail MMX islands with the 0x1f8 frame-slot order and the qIndex lookup; reusing the sibling would assert the wrong identity.

## 0x009D9D90 - _bfme_dumpXferStream

- Status: blocked after reviewing the existing source-backed stash; `targets/game/reverse/attempts/0x009d9d90.cpp` remains retained at score `0.55`.
- Identity: `_bfme_dumpXferStream` is supported by the named `GameLogic::_bfme_reportDesync` caller and the BFME RTS1/RTS2 tagged transfer-stream behavior.
- Evidence: the retail contract has 14 direct targets, including parser helpers `0x009D9110` x34 and `0x009D9160` x32, `_bfmeFormatText` x7, vector/string buffer lifetime helpers, and a `0x288` EH frame. The stash probes at 3,046 versus 5,472 bytes with 96 relocations, 2,389 non-relocation differences, 93 relocation-layout mismatches, and a `0x2f0` frame.
- No exact parser/error-ladder source, pin, or unlock row is justified; adding the missing BFME behavior without its live format/throw contract would be invented.

## 0x0057A470 - BfmeAptScreenSkirmish::_bfme_updateProfileDisplay

- Status: blocked at the existing score `0.47`; `targets/game/reverse/attempts/0x0057a470.cpp` remains the preferred source-backed stash.
- Identity: the BFME Skirmish profile display updater is supported by the three `AptSkirmish::InitGadgets` callsites and its APT-specific labels.
- Evidence: the stash probes at 2,614 versus 5,296 bytes with the exact `0x13c` frame, then diverges at `+0x1c` in callee-saved/register setup. Retail has 27 direct targets, including `_bfmeFormatText`, 19 Unicode formatting calls, 3 translations, and the corresponding string constructor/release ladder; the source models the visible labels but not the retail profile/global dispatch state.
- No exact source, pin, or unlock row is justified.

## 0x003EEB90 - Pathfinder::internal_findHierarchicalPath

- Status: blocked at the existing score `0.55`; `targets/game/reverse/attempts/0x003eeb90.cpp` remains scratch evidence only.
- Identity: the BFME seven-argument internal hierarchical-path routine is supported by the matched `findGroundPath`/`findPath`/`findClosestPath` callers through thunk `0x001FA14` and the `ret 0x1c` contract.
- Evidence: retail has 34 direct, ledger-resolved helper targets. The Zero Hour `AIPathfind.cpp` twin probes at 3,427 versus 4,836 bytes with 58 relocations, 3,037 non-relocation differences, and 55 relocation-layout mismatches; the first divergence is +0x08 (`0xec` retail frame versus `0xb4`) and the BFME `Object*`/`rawTo` argument layout. No exact BFME hierarchical-path source, pin, or unlock row is justified.

## 0x0073E050 - W3DView::draw

- Status: blocked at the existing score `0.30`; `targets/game/reverse/attempts/0x0073e050.cpp` remains scratch evidence only.
- Identity: the body is `W3DView::draw`, supported by the `W3DDisplay::m_3DScene` path, `filterPreRender`/`filterPostRender` calls, and W3DView field accesses.
- Evidence: retail has 13 direct targets including `DX8Wrapper::Clear` x3. The source twin probes at 1,831 versus 5,126 bytes with 57 relocations, 1,527 non-relocation differences, and 56 relocation-layout mismatches; retail begins with a no-EH `0x120` frame while the twin begins with EH and a `0x1bc` frame. The scratch bank’s relative include path is also not independently compilable.
- No exact BFME display-global/filter ladder, pin, or unlock row is justified.
## 0x007DD180 - TerrainShader2Stage::set

Status: banked partial; identity is supported, but no exact clean-C++ body
was found. The preferred function-sized candidate is
`targets/game/reverse/attempts/0x007dd180.cpp`, compiled in the existing
`W3DShaderManager.cpp` TU context. The anonymous ledger row remains
`?d_007dd180@@YAXXZ`.

### Callee table

| Retail target | Count | Proven identity | Evidence |
| --- | ---: | --- | --- |
| `0x00904890` | 1 | `DX8Wrapper::Apply_Render_State_Changes` | `tools/callees.py 0x007DD180 6636` |
| `0x00038389` | 2 | pinned `Rva006D4690Apply` through the ILT | matched filter-state body at `0x006D4690` and the existing pin |
| `0x009DB890` / `0x009DB7A0` | 35 / 35 | `StringClass::Get_String` / `Free_String` | repeated snapshot-name construction and cleanup |
| `0x00906FE0` / `0x00907BE0` | 28 / 7 | DX8 texture-stage/render-state value names | BFME snapshot expansion in the retail state-cache path |
| `0x009FB321` | 1 | `_D3DXMatrixInverse@12` | view inverse before the noise branches |
| `0x0001ADED` | 6 | `bfmeGet` through the existing ILT | six texture-handle acquisitions in the noise cases |
| `0x0090DC60` / `0x009EB7A0` | 6 / 6 | `Peek_D3D_Base_Texture` / `TextureClass::Release_Ref` | paired device binds and RAII handle cleanup |
| `0x00019BFF` / `0x000051FF` | 2 / 2 | existing j-thunks to `0x007DCCE0` / `0x007DCF00` | direct retail calls; `TerrainTextureMatrix.cpp` is source-backed for `0x007DCF00` |

### Layout

- `TerrainShader8Stage::set` calls `0x007DD180` for its two-stage pass-2
  route, which supports `TerrainShader2Stage::set(Int)` without inventing a
  semantic owner for the anonymous ledger row.
- Retail starts with the MSVC EH handler `0x010540D3`, reserves `0xA4` bytes,
  saves `this` in EDI, and reads the stack `pass` at `[esp+0xCC]` after the
  two filter-helper calls. The best candidate reserves `0x8C`, so its first
  raw divergence is the frame at `+0x15` and its `curView` local is at
  `[esp+0x18]` instead of retail `[esp+0x34]`.
- The pass-2 state ladder contains slot-67 texture-stage writes, slot-69
  sampler writes, slot-57 render-state writes, direct device slot-65 texture
  binds, one view inverse, and six short-lived texture handles. The target's
  35/35 string calls and 28/7 state-name calls are the expanded snapshot
  wrappers, not evidence for another class.

### Levers tried

The best measured candidate expands the BFME cache and sampler paths, uses
the proven `0x006D4690` filter helper, RAII `bfmeGet` handles, and direct
`0x00019BFF`/`0x000051FF` helper routes. It compiles to 7,083 bytes versus
6,636 retail, with 623 relocations, 3,141 non-relocation differences, and
3,495 masked-equal bytes (recorded score `0.5267`); 467 relocation sites do
not align after the frame/layout drift. The alternate render-snapshot form
using the existing `StringClass` constructor is 6,907 bytes with 3,476
non-relocation differences and was retained in immutable attempt history.

The attempted levers were the original ZH state wrappers; BFME slot-67,
slot-69, slot-57, and slot-65 lowering; inline snapshot string construction;
RAII texture lifetimes; the proven filter helper; direct j-thunk calls; and
the two source-backed terrain matrix helper routes. No new pin or unlock row
is justified: `targets/game/reverse/unlocked.txt` already contains `0x007dd180 w3d-render`.

## 0x005674F0 - BfmeConsumerED::bfmeApply

Status: banked partial; the caller and the 24-byte by-value argument layout are
supported, but no exact clean-C++ body was found. The preferred candidate is
`targets/game/reverse/attempts/0x005674f0.cpp`; the anonymous body remains the generated
row in `game/gen_asm/d_00563370.asm`.

### Callee table

| Retail target | Count | Proven identity | Evidence |
| --- | ---: | --- | --- |
| `0x0040BDCA` | 37 | `WindowManager::bfme_setAptText` | one write for each profile/stat APT field |
| `0x00889190` | 35 | `UnicodeString::format` | numeric and four-faction streak formatting |
| `0x00888400` / `0x008881D0` | 37 / 37 | `UnicodeString` copy ctor / dtor | each APT write copies and then destroys the value |
| `0x00888BC0` / `0x00887940` | 41 / 39 | `AsciiString` literal ctor / release | APT variable labels and cleanup ladder |
| `0x000095CA` | 8 | `SkirmishBattleHonors::getLossStreak` | current loss streak and zero-loss branch tests |
| `0x00022273` | 4 | `SkirmishBattleHonors::getWinStreak` | current win streak in the zero-loss branch |
| `0x0003F472` | 4 | `SkirmishBattleHonors::getBestWinStreak` | one best-streak value per faction |
| `0x00040192` / `0x0001CE18` | 4 / 4 | `getWins` / `getLosses` | per-faction and overall counters |
| `0x00010898 -> 0x009FA60` | 1 | `SkirmishPreferences::getUserName` | thunk-mediated call on the by-value preference tail |
| `0x00008602 -> 0x009E130` / `0x000232C2 -> 0x009DBD0` | 1 / 1 | honors ctor / profile-date accessor | local honors object and profile-created label |
| `0x00013403 -> 0x005672C0` / `0x0002099B -> 0x005673A0` | 1 / 1 | preference map/list assignment | caller and target offsets prove the member types |

### Layout

- The matched `0x0057ED70` caller passes `BfmeArgED` by value. Its copy ctor
  at `0x0057ECF0` installs vtable `0x010806B0`, copies the base, and copies a
  string member, proving a 24-byte polymorphic object rather than six scalar
  integers.
- The argument tail is `vptr +0x00`, an 8-byte map-like object at `+0x04`, a
  4-byte gap at `+0x0c`, a Unicode string at `+0x10`, and a list/string-like
  object at `+0x14`. The consumer uses the same preference tail at `this+0x04`:
  map assignment through `this+0x08`, string `set` through `this+0x14`, and
  list assignment through `this+0x18`.
- Retail constructs four side labels (`Gondor`, `Rohan`, `Isengard`, `Mordor`),
  fetches `Apt:Win` and `Apt:Loss`, creates `SkirmishBattleHonors`, and writes
  the profile date, overall counters, player name, favorite side, total games,
  and five fields per faction. The final EH cleanup order is part of the
  byte-shape contract.

### Levers tried

The best candidate is 5,745 bytes versus 5,762 retail, with 420 relocations,
3,796 non-relocation differences, 269 masked-equal bytes, and score `0.06617`.
It gets the manager count (37), Ascii literal count (41), by-value object shape,
preference offsets, and the compact text-first number helper. Its first raw
divergence is the local frame: `sub esp,0x68` versus retail `sub esp,0x64`, with
393 relocation-layout sites drifting afterward.

The tried candidates were an expanded renderer-shaped body; direct versus
returned-`UnicodeString` number formatting; label-first versus text-first
number setup; by-value versus local-copy `SetText`; streak copy-after-label;
and two manager calls versus one factored favorite-side branch. Direct number
formatting and the streak local-copy form enlarged the frame substantially;
the factored favorite branch was the useful lever because it restored the exact
37 manager writes. The partial is banked with all candidate names and measured
evidence in `targets/game/reverse/re_attempts.log`. No shared shim, pin, or layout proof for
a smaller neighbour was established, so `targets/game/reverse/unlocked.txt` is unchanged.

## 0x0095CE80 - StreakRendererClass::RenderStreak

Status: blocked for this pass after rechecking the existing source-backed
bank. The matched `StreakLineRender.cpp` caller proves the identity, but the
clean candidate is not byte-exact; the preferred source remains
`targets/game/reverse/attempts/0x0095ce80.cpp` and the generated dump remains untouched.

### Callee table

| Retail target | Count | Proven identity | Evidence |
| --- | ---: | --- | --- |
| `0x00905AC0` | 1 | `BoxSetTexture` | texture bind before the draw route |
| `0x009045E0` / `0x00906DF0` | 1 / 1 | `DX8Wrapper::Set_Index_Buffer` / `Draw_Triangles` | index setup and unsorted draw path |
| `0x0091D350`, `0x0091D410`, `0x0091D4E0`, `0x0091D950` | 1 each | DynamicIB/WriteLock ctor and dtor | index-buffer lifetime |
| `0x0091D9E0`, `0x0091F160`, `0x0091F240`, `0x0091F730` | 1 each | DynamicVB/WriteLock ctor and dtor | vertex-buffer lifetime |
| `0x009212C0` / `0x0093B340` | 1 / 1 | `VertexMaterialClass::Get_Preset` / `SortingRendererClass::Insert_Triangles` | material and sorting path |
| `0x0095CA00` | 1 | `StreakRendererClass::subdivision_util` | fractal segment subdivision |
| `0x00B001D0` | 1 | `VectorProcessorClass::Transform` | point transform per chunk |
| `0x009DB890` / `0x009DB7A0` | 1 / 1 | `StringClass::Get_String` / `Free_String` | snapshot/debug string wrapper |
| `0x0000AE5C -> 0x005C600` / `0x00027A43 -> 0x0131C90` | 1 / 25 | existing ILT/thunk routes | direct call contract is known; semantic callee ownership remains address-derived |
| `0x00904510` | 1 | address-derived render-state helper | retail call has no safer semantic pin |
| `__chkstk` / `floor` import | 1 / 2 | compiler/runtime and MSVCR71 import | frame probe and UV wrapping |

### Layout

- The body begins with the proven `/Z7`-style EH frame and a retail stack
  reservation of `0x5A84`; the bank reserves `0x5A78`. Retail saves `this` at
  `[ebp-0x68]`, while the bank uses `[ebp-0x6c]` before the larger local arrays.
- `StreakRendererClass` carries the texture/shader/width/color/opacity fields,
  subdivision and noise state, texture scroll state, `Bits`, and the BFME
  vertex-buffer pair at `+0x44/+0x48`. The render path uses the chunked point
  arrays, subdivision stack, intersection arrays, vertex/index arrays, and
  DynamicVB/DynamicIB lock objects.
- The target contract is the world/view reset, UV offset update, chunked
  transform and subdivision, edge-plane/intersection expansion, material and
  shader setup, dynamic-buffer writes, index/vertex/texture binds, then either
  sorted insertion or `Draw_Triangles`, followed by restoring the view matrix.

### Levers tried

The existing bank compiles to 12,095 bytes versus 12,206 retail, with 199
relocations, 9,883 non-relocation differences, and 138 relocation-layout
drifts; the stored author score is `0.6`. It restores the BFME texture-scroll,
tile-factor, last-sync-time, UV, mapping-mode, and output-offset fields and
removes the unsupported index-write try/catch expansion. It is not a 99%
byte match despite the size ratio.

The fresh frame-pad candidate was the only new bounded lever: a volatile
12-byte local compiled to 12,111 bytes but left the frame at `0x5A78` and
increased differences to 10,633 with 185 layout drifts, so it was reverted.
Earlier evidence already covers EH/frame alternatives, clamp-loop forms,
texture-setter visibility, register/local layout, x87 scheduling, and
`ALLOW_TEMPORARIES`/`G7`/`/O1` variants. No unresolved callee was independently
safe to pin, and no shared layout proof for a smaller neighbour was gained;
`targets/game/reverse/unlocked.txt` is unchanged.

## 0x00084510 - GlobalData::GlobalData

Status: blocked after a source-backed constructor recheck. The ranked queue
reported 4,499 bytes, but retail disassembly proves the complete constructor
extent is 4,621 bytes through the `ret` at `+0x120C`; the generated body was
not edited. The preferred structural bank remains
`targets/game/reverse/attempts/0x00084510.cpp`.

### Callee table

| Retail target | Count | Proven identity | Evidence |
| --- | ---: | --- | --- |
| `0x009A1A30` | 1 | `SubsystemInterface::SubsystemInterface` | base constructor at `+0x29` |
| `0x009F6C60` | 1 | `__chkstk` | retail reserves `0x10138` bytes |
| `0x00887940` | 26 | `BFMERetailAsciiString::releaseBuffer` | string cleanup path |
| `0x00887C90` | 1 | `UnicodeString::set` | one trailing Unicode member assignment |
| `0x00887D20` | 3 | `RetailLayoutString::set` | three literal-backed member assignments |
| `0x009F6EE4` | 5 | EH vector-constructor iterator | four-element/18-element destructible arrays |
| `0x00881F30` | 1 | `operator new` | constructor-local allocation path |
| `0x0000A984`, `0x0000BA64`, `0x0001B76B`, `0x00020F45`, `0x0002F923`, `0x0003747A`, `0x0003F508` | 8 | existing address-derived ILT/thunk routes | full-range `tools/callees.py 0x00084510 4621` contract |
| `0x01359000` import | 1 | `USER32!GetDoubleClickTime` | final double-click default |

### Layout

- `GlobalData_newOverride_Thunk.cpp` proves the object size is `0x1290` and
  `m_next` is at `+0x128C`; the constructor inherits an 8-byte
  `SubsystemInterface` prefix and installs GlobalData vtable `0x0107C68C`.
- Retail uses the four-row vertex-water arrays at `+0xAC..+0x17C`, the
  destructible string/array members at the witnessed offsets, the three
  `Coord3D` members at `+0xA04`, and the later string/vector/Unicode members
  through `+0x1288`. The 50 EH states cover the base and destructible members;
  the no-state `+0xEE0` grid ctor is a proven nothrow class.
- The constructor reserves a `0x10138`-byte compiler frame, saves `this` at
  `[esp+0x20]`, calls the base ctor, stores the derived vtable, initializes
  strings/arrays/scalars in retail order, performs the `GetDoubleClickTime`
  tail, and exits through the full EH cleanup ladder. A long `0xEE0` to
  `0xF59` NOP region is present in retail and is not evidence for a CRC/file
  loop; no such behavior was invented.

### Levers tried

The best clean draft is 2,804 bytes versus the corrected 4,621-byte retail
extent, with 25 relocations, 2,331 non-relocation differences, 20
relocation-layout drifts, and author score `0.2`. It includes the empirical
`0x10138` frame, the four-iteration vertex-water initializer, recovered
destructible-member layout, and the full store set, but it diverges at the
first member-initialization schedule (`[esp+0x10]` versus retail `[esp+0x20]`).

The tested alternatives were a virtual-destructor declaration to force the
derived vtable, an explicit witnessed `0x0107C68C` vtable store, and a
distinct constructor-bearing type for the `+0x9C` four-element array. The
explicit store produced 2,813 bytes and 2,395 non-relocation differences; the
other two did not improve the useful shape. The prior bank also records the
discarded CRC/file-loop theory, flat versus looped water initialization, and
frame-first experiments. No exact body or safe pin was found, and no shared
unlock proof was established; `targets/game/reverse/unlocked.txt` is unchanged.

## 0x004DBE80 - PopulatePlayerInfoWindows

- Status: banked partial, not landed. Preferred source is
  `targets/game/reverse/attempts/0x004dbe80.cpp`, with identity supported by the WOL welcome
  callers and the existing `PopulatePlayerInfoWindows` definition.
- Best probe: 3,953 emitted bytes versus the corrected 4,126-byte retail
  extent, 229 relocations, 1,344 masked-equal bytes, 2,609 non-relocation
  differences, first non-relocation difference at `+0x28`, and 199 relocation
  sites whose operands do not align. Honest bank score is `0.326`.

### Callee table

| Retail target | Calls | Resolved role |
| --- | ---: | --- |
| `0x00019371` | 1 | address-derived stats copy/cleanup thunk |
| `0x00021B7A` | 1 | address-derived player-stats thunk |
| `0x00025C1B` | 2 | address-derived stats cleanup thunk |
| `0x00027F2A` | 3 | address-derived UI/stat thunk |
| `0x0002C16F` | 20 | address-derived `GameWindow` update thunk |
| `0x00035E09` | 1 | address-derived stat thunk |
| `0x00037BD2` | 1 | address-derived stat thunk |
| `0x0003AF6C` | 1 | address-derived rank thunk |
| `0x0004B01A` | 1 | `AsciiString::compare(const char *)` alias `bfmeCompare1294` |
| `0x004D9DF0` | 1 | address-derived rank/stat helper |
| `0x004DA630` | 21 | `findWindow` |
| `0x004DA760` | 1 | `lookupRankImage` |
| `0x004DB0B0` | 1 | `readAdditionalDisconnectsFromUserFile`, fastcall reader |
| `0x0082B870` | 11 | STL `_M_increment` |
| `0x00887940` | 5 | BFME retail AsciiString release |
| `0x00887B60` | 26 | `GameSpyGroupRoom` copy construction |
| `0x00887C90` | 1 | `UnicodeString::set` |
| `0x008881D0` | 2 | wide `StringBase` release |
| `0x00888400` | 14 | wide `StringBase` copy construction |
| `0x00888BC0` | 26 | BFME retail AsciiString literal construction |
| `0x00888DE0` | 12 | wide `StringBase` literal construction |
| `0x00888FF0` | 3 | `AsciiString::format` |
| `0x00889190` | 14 | `UnicodeString::format` |
| `0x009F6E38` | 2 | `__ftol2` |

### Layout

- Retail reserves frame `0x3B4`, saves `ebx/ebp/esi/edi`, clears the EH slot
  with `ebp`, and reads `TheGameSpyInfo` through its BFME vtable. The proven
  profile call is slot `+0x70`; cached local stats are slot `+0x90`; the
  additional-disconnect and clear methods are slots `+0x170` and `+0x174`.
- The BFME `PSPlayerStats` shim is required: the local stats object uses the
  witnessed maps at wins `+0x04`, losses `+0x10`, disconnections `+0xB8`, and
  desyncs `+0xC4`; the cached object is copied through the `+0x90` vtable
  return into the local stack view.
- The target's map sums use the local stats at `[esp+0x40]`, with the cached
  return temporary at `[esp+0x200]`, then calls the already matched
  `readAdditionalDisconnectsFromUserFile` body at `0x004DB0B0` before the
  `+0x170/+0x174` GameSpyInfo sequence.

### Levers tried

The Zero Hour PopupPlayerInfo candidate, the BFME WOL-shaped bank, the BFME
`PSPlayerStats` shim, the expanded GameSpyInfo view, the direct
`readAdditionalDisconnectsFromUserFile` call, and `AsciiString::compare` were
compiled as separate candidates. The ZH candidate stayed at a `0x360` frame
and `+0x54` profile slot; the WOL bank had a `0x364` frame; the final candidate
corrected the frame and vtable slots but still diverged in register allocation,
temporary scheduling, and the remaining WOL/UI body. A cached GameSpyInfo
pointer in the helper was retained because it was the best of the tested
helper shapes. No exact candidate, semantic pin, or shared layout proof was
found, so `targets/game/reverse/unlocked.txt` is unchanged.

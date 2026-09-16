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

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

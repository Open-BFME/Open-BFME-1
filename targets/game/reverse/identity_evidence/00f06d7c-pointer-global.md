# Datum identity at VA 0x01306D7C

The datum is `?TheWaterRenderObj@@3PAVWaterRenderObjClass@@A` in `game/GameEngineDevice/Source/W3DDevice/GameClient/Water/W3DWater.cpp`. The global WaterRenderObjClass rendering object.

Retail has a 4-byte extent in `.data`, initialized to `00 00 00 00`. The PE base-relocation directory is absent (RVA and size both zero), and the initial value contains no pointer relocation. The complete range has no overlapping data row and no other DIR32 name strictly inside it. Alternative spellings at the start are preserved additively in the DIR32 ledger.

Terrain visual initialization constructs and publishes the water render object, and terrain visual destruction clears it. Matched resource-release and skybox-settings bodies read this singleton and use the water-specific layout.

Zero Hour GameEngineDevice/Source/W3DDevice/GameClient/Water/W3DWater.cpp:170 defines WaterRenderObjClass *TheWaterRenderObj; Include/W3DDevice/GameClient/W3DWater.h:294 declares it. W3DTerrainVisual.cpp constructs and initializes it with the primary scene.

## Receiver and argument contract

A scalar datum stores one 32-bit pointer. Loads passed in ECX are member receivers; stores publish the constructed or factory-returned pointer or clear it to zero. No wrapper, forwarder, inheritance relationship or second object identity is introduced. Existing locally modeled member-call ABIs remain unchanged through casts at their use sites.

## Competing spellings before correction

| Decorated spelling | Game files declaring it |
|---|---:|
| `?TheWaterRenderObj@@3PAVGen006C6140Water@@A` | 0 |
| `?TheWaterRenderObj@@3PAVGen006C6300Water@@A` | 0 |
| `?TheWaterRenderObj@@3PAVWaterRenderObjClass@@A` | 8 |
| `?TheWaterRenderObj@@3PAVWaterSkyBoxSettingsOwner@@A` | 0 |

Macro-generated S4 declarations and the terrain-track guarded-call declaration are counted in their owning source. The raw contract log lists each counted path; counts decide no identity.

## Retail reads and writes

Readers:

- `?dup_007A5AB0@@YAXXZ` at RVA `0x007A5AB0` (game/GameEngineDevice/Source/W3DDevice/GameClient/Water/Rva007A5AB0SkyBoxDefaults.cpp)
- `?parseSkyBoxSettings007A5BA0@@YA_NAAVDataChunkInput@@PAUDataChunkInfo@@PAX@Z` at RVA `0x007A5BA0` (game/GameEngineDevice/Source/W3DDevice/GameClient/Water/WaterRenderObjReadSkyBoxSettings.cpp)
- `?releaseResources@Gen006C6140Owner@@QAEXXZ` at RVA `0x006C6140` (game/GameEngineDevice/Source/W3DDevice/GameClient/Gen_006C6140_ResourceRelease.cpp)
- `?releaseResources@Gen006C6300Owner@@QAEXXZ` at RVA `0x006C6300` (game/GameEngineDevice/Source/W3DDevice/GameClient/Gen_006C6300_ResourceRelease.cpp)
- `?setTimeOfDay@W3DGameClient@@UAEXW4TimeOfDay@@@Z` at RVA `0x006FBCB0` (game/GameEngineDevice/Source/W3DDevice/GameClient/W3DGameClient.cpp)
- `?updateShorelineTiles@BaseHeightMapRenderObjClass@@QAEXHHHHPAVWorldHeightMap@@@Z` at RVA `0x006C76B0` (game/GameEngineDevice/Source/W3DDevice/GameClient/BaseHeightMap.cpp)

Writers:

- `??0W3DTerrainVisual@@QAE@XZ` at RVA `0x007304E0` (game/GameEngineDevice/Source/W3DDevice/GameClient/W3DTerrainVisualBfme.cpp)
- `??1W3DTerrainVisual@@UAE@XZ` at RVA `0x00731050` (game/GameEngineDevice/Source/W3DDevice/GameClient/W3DTerrainVisualDestructorBfme.cpp)
- `?init@Rva00730590@@UAEXXZ` at RVA `0x00730590` (game/GameEngineDevice/Source/W3DDevice/GameClient/W3DTerrainVisualRva00730590Init.cpp)

## Refutation and verification

A different allocation target, a nonzero initial byte, a pointer adjustment between the published receiver and these accesses, an overlapping datum, or an indexed access beyond the verified extent would refute this storage/type correction. For a reference-derived name, a retail constructor/vtable or member contract inconsistent with that reference type would also refute it. An EA class-name discovery can improve the retained address-derived renderer types without changing the established datum ownership.

Raw evidence is in `build/rlink/pointer-globals-20261005/01306D7C-retail.log`, `01306D7C-routes.log`, `01306D7C-source.log` and `01306D7C-contract.log`. Retail log instructions and route logs preserve bytes and every observed five-byte E9 thunk through its final target. `reference-defs.log`, `selected-pins.log` and the constructor probes provide the supporting reference and pin extracts. The data-match and per-source Functions gates are recorded in `build/worker-final.md`; verified function bytes and function ledger rows remain unchanged.
